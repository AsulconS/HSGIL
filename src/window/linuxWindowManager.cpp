/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2020 Adrian Bedregal and Gabriela Chipana                      *
 *                                                                              *
 * This software is provided 'as-is', without any express or implied            *
 * warranty. In no event will the authors be held liable for any damages        *
 * arising from the use of this software.                                       *
 *                                                                              *
 * Permission is granted to anyone to use this software for any purpose,        *
 * including commercial applications, and to alter it and redistribute it       *
 * freely, subject to the following restrictions:                               *
 *                                                                              *
 * 1. The origin of this software must not be misrepresented; you must not      *
 *    claim that you wrote the original software. If you use this software      *
 *    in a product, an acknowledgment in the product documentation would be     *
 *    appreciated but is not required.                                          *
 * 2. Altered source versions must be plainly marked as such, and must not be   *
 *    misrepresented as being the original software.                            *
 * 3. This notice may not be removed or altered from any source distribution.   *
 *                                                                              *
 ********************************************************************************/

#include <HSGIL/window/linuxWindowManager.hpp>

namespace gil
{
uint32 WindowManager::s_activeSessions  {0u};
uint32 WindowManager::s_wmInstanceCount {0u};
WMLazyPtr WindowManager::s_wmInstances[MAX_WINDOW_INSTANCES] {};

std::unordered_map<XWND, uint32> WindowManager::s_hwndMap {};

const int WindowManager::s_glxAttribs[ATTRIB_LIST_SIZE]
{
    GLX_X_RENDERABLE    , GL_TRUE,
    GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
    GLX_RENDER_TYPE     , GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
    GLX_RED_SIZE        , 8,
    GLX_GREEN_SIZE      , 8,
    GLX_BLUE_SIZE       , 8,
    GLX_ALPHA_SIZE      , 8,
    GLX_DEPTH_SIZE      , 24,
    GLX_STENCIL_SIZE    , 8,
    GLX_DOUBLEBUFFER    , GL_TRUE,
    0
};

int WindowManager::s_keyCodesMap[KEY_CODES_SIZE] {};

Time WindowManager::s_lastKeyRelTime {};
Time WindowManager::s_lastKeyPressTime {};

XEvent WindowManager::s_event {};
XkbDescPtr WindowManager::s_kbDesc {nullptr};
Display* WindowManager::s_display {nullptr};
Screen*  WindowManager::s_screen  {nullptr};
int WindowManager::s_screenID {-1};

bool WindowManager::s_repeatFlag {false};

int WindowManager::s_fbCount {0};
GLXFBConfig* WindowManager::s_fbConfigs {nullptr};

bool WindowManager::s_vSyncCompat {true};
bool WindowManager::s_attribCtxCompat {true};

PFNGLXCREATECONTEXTATTRIBSARBPROC WindowManager::glXCreateContextAttribsARB {nullptr};

PFNGLXSWAPINTERVALPROC WindowManager::glXSwapInterval {nullptr};

// Lazy Pointer Stuff

WMLazyPtr::WMLazyPtr()
    : m_wm {nullptr}
{
}

WMLazyPtr::~WMLazyPtr()
{
    if(m_wm != nullptr)
    {
        delete m_wm;
    }
}

void WMLazyPtr::init(const uint32 index)
{
    if(m_wm == nullptr)
    {
        m_wm = new WindowManager(index);
    }
}

WindowManager& WMLazyPtr::operator*()
{
    return *m_wm;
}

WindowManager* WMLazyPtr::operator->()
{
    return m_wm;
}

bool WMLazyPtr::operator==(const WMLazyPtr& o)
{
    return this->m_wm == o.m_wm;
}

bool WMLazyPtr::operator!=(const WMLazyPtr& o)
{
    return this->m_wm != o.m_wm;
}

bool WMLazyPtr::operator==(const std::nullptr_t nullPtr)
{
    return this->m_wm == nullPtr;
}

bool WMLazyPtr::operator!=(const std::nullptr_t nullPtr)
{
    return this->m_wm != nullPtr;
}

WMLazyPtr::operator WindowManager*()
{
    return m_wm;
}

// Window Manager Stuff

WindowManager* WindowManager::createInstance()
{
    if(!s_wmInstanceCount)
    {
        s_display = XOpenDisplay(nullptr);
        s_screen = DefaultScreenOfDisplay(s_display);
        s_screenID = DefaultScreen(s_display);

        loadKeyboardMap();
        loadGLExtensions();

        s_wmInstances[0u].init(0u);
        ++s_wmInstanceCount;

        return s_wmInstances[0u];
    }

    if(s_wmInstanceCount >= MAX_WINDOW_INSTANCES)
    {
        return nullptr;
    }

    s_wmInstances[s_wmInstanceCount].init(s_wmInstanceCount);
    return s_wmInstances[s_wmInstanceCount++];
}

WindowManager* WindowManager::getInstance(const uint32 index)
{
    if(isBetween(index, 0u, MAX_WINDOW_INSTANCES - 1u))
    {
        if(s_wmInstances[index] != nullptr)
        {
            return s_wmInstances[index];
        }
        else
        {
            return nullptr;
        }
    }
    return nullptr;
}

bool WindowManager::isActive()
{
    if(m_active && m_shouldClose)
    {
        glXDestroyContext(s_display, m_context);

        XFree(m_visual);
        XFreeColormap(s_display, m_windowAttributes.colormap);
        XDestroyWindow(s_display, m_windowHandle);

        --s_activeSessions;
        m_active = false;
        m_shouldClose = false;

        if(!s_activeSessions)
        {
            XCloseDisplay(s_display);
        }
    }
    return m_active;
}

void WindowManager::createRenderingWindow(const char* title, int x, int y, int width, int height)
{
    if(!m_active)
    {
        m_fbConfig = chooseBestFBC();
        m_visual = glXGetVisualFromFBConfig(s_display, m_fbConfig);

        m_windowAttributes.border_pixel = BlackPixel(s_display, s_screenID);
        m_windowAttributes.background_pixel = WhitePixel(s_display, s_screenID);
        m_windowAttributes.override_redirect = true;
        m_windowAttributes.colormap = XCreateColormap(s_display, RootWindow(s_display, s_screenID), m_visual->visual, AllocNone);
        m_windowAttributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;

        m_windowHandle = XCreateWindow
        (
            s_display, RootWindow(s_display, s_screenID),
            x, y,
            width, height,
            0, m_visual->depth, InputOutput, m_visual->visual,
            CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
            &m_windowAttributes
        );
        XStoreName(s_display, m_windowHandle, title);

	    m_atomWmDeleteWindow = XInternAtom(s_display, "WM_DELETE_WINDOW", false);
	    XSetWMProtocols(s_display, m_windowHandle, &m_atomWmDeleteWindow, 1);

        createContext();

        XClearWindow(s_display, m_windowHandle);
        XMapRaised(s_display, m_windowHandle);

        m_active = true;
        ++s_activeSessions;
        s_hwndMap[m_windowHandle] = m_index;
    }
}

void WindowManager::destroyRenderingWindow()
{
    if(m_active)
    {
        m_shouldClose = true;
    }
}

void WindowManager::setKeyCallbackFunction(Window* t_windowCallbackInstance, KeyCallbackFunction tf_keyCallbackFunction)
{
    m_windowCallbackInstance = t_windowCallbackInstance;
    mf_keyCallbackFunction = tf_keyCallbackFunction;
}

void WindowManager::pollEvents()
{
    if(XPending(s_display) > 0)
    {
        XNextEvent(s_display, &s_event);
        HSGILProc();
    }
}

void WindowManager::swapBuffers()
{
    glXSwapBuffers(s_display, m_windowHandle);
}

WindowManager::WindowManager(const uint32 t_index)
    : m_active      {false},
      m_shouldClose {false},
      m_index       {t_index}
{
}

WindowManager::~WindowManager()
{
}

void WindowManager::createContext()
{
    int contextAttribs[] =
    {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 2,
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		None
	};

    if(s_attribCtxCompat)
    {
        m_context = glXCreateContextAttribsARB(s_display, m_fbConfig, 0, true, contextAttribs);
    }
    else
    {
        m_context = glXCreateNewContext(s_display, m_fbConfig, GLX_RGBA_TYPE, 0, true);
    }
	XSync(s_display, false);

	if(!glXIsDirect(s_display, m_context))
    {
		std::cout << "Indirect GLX rendering context obtained\n\n";
	}
	else
    {
		std::cout << "Direct GLX rendering context obtained\n\n";
	}
	glXMakeCurrent(s_display, m_windowHandle, m_context);

    gladLoadGL();

    if(s_vSyncCompat)
    {
        glXSwapInterval(1);
    }
}

void WindowManager::loadKeyboardMap()
{
    s_kbDesc = XkbGetMap(s_display, 0, XkbUseCoreKbd);
    XkbGetNames(s_display, XkbKeyNamesMask, s_kbDesc);

    int rawCode;
    int keyCode;
    char keyName[XkbKeyNameLength + 1];

    memset(s_keyCodesMap, -1, sizeof(s_keyCodesMap));
    for(rawCode = s_kbDesc->min_key_code; rawCode <= s_kbDesc->max_key_code; ++rawCode)
    {
        memcpy(keyName, s_kbDesc->names->keys[rawCode].name, XkbKeyNameLength);
        keyName[XkbKeyNameLength] = '\0';

             if(strcmp(keyName, "TLDE") == 0) keyCode = KEY_GRAVE_ACCENT;
        else if(strcmp(keyName, "AE01") == 0) keyCode = KEY_1;
        else if(strcmp(keyName, "AE02") == 0) keyCode = KEY_2;
        else if(strcmp(keyName, "AE03") == 0) keyCode = KEY_3;
        else if(strcmp(keyName, "AE04") == 0) keyCode = KEY_4;
        else if(strcmp(keyName, "AE05") == 0) keyCode = KEY_5;
        else if(strcmp(keyName, "AE06") == 0) keyCode = KEY_6;
        else if(strcmp(keyName, "AE07") == 0) keyCode = KEY_7;
        else if(strcmp(keyName, "AE08") == 0) keyCode = KEY_8;
        else if(strcmp(keyName, "AE09") == 0) keyCode = KEY_9;
        else if(strcmp(keyName, "AE10") == 0) keyCode = KEY_0;
        else if(strcmp(keyName, "AE11") == 0) keyCode = KEY_MINUS;
        else if(strcmp(keyName, "AE12") == 0) keyCode = KEY_EQUAL;
        else if(strcmp(keyName, "AD01") == 0) keyCode = KEY_Q;
        else if(strcmp(keyName, "AD02") == 0) keyCode = KEY_W;
        else if(strcmp(keyName, "AD03") == 0) keyCode = KEY_E;
        else if(strcmp(keyName, "AD04") == 0) keyCode = KEY_R;
        else if(strcmp(keyName, "AD05") == 0) keyCode = KEY_T;
        else if(strcmp(keyName, "AD06") == 0) keyCode = KEY_Y;
        else if(strcmp(keyName, "AD07") == 0) keyCode = KEY_U;
        else if(strcmp(keyName, "AD08") == 0) keyCode = KEY_I;
        else if(strcmp(keyName, "AD09") == 0) keyCode = KEY_O;
        else if(strcmp(keyName, "AD10") == 0) keyCode = KEY_P;
        else if(strcmp(keyName, "AD11") == 0) keyCode = KEY_LEFT_BRACKET;
        else if(strcmp(keyName, "AD12") == 0) keyCode = KEY_RIGHT_BRACKET;
        else if(strcmp(keyName, "BKSL") == 0) keyCode = KEY_BACKSLASH;
        else if(strcmp(keyName, "AC01") == 0) keyCode = KEY_A;
        else if(strcmp(keyName, "AC02") == 0) keyCode = KEY_S;
        else if(strcmp(keyName, "AC03") == 0) keyCode = KEY_D;
        else if(strcmp(keyName, "AC04") == 0) keyCode = KEY_F;
        else if(strcmp(keyName, "AC05") == 0) keyCode = KEY_G;
        else if(strcmp(keyName, "AC06") == 0) keyCode = KEY_H;
        else if(strcmp(keyName, "AC07") == 0) keyCode = KEY_J;
        else if(strcmp(keyName, "AC08") == 0) keyCode = KEY_K;
        else if(strcmp(keyName, "AC09") == 0) keyCode = KEY_L;
        else if(strcmp(keyName, "AC10") == 0) keyCode = KEY_SEMICOLON;
        else if(strcmp(keyName, "AC11") == 0) keyCode = KEY_APOSTROPHE;
        else if(strcmp(keyName, "AB01") == 0) keyCode = KEY_Z;
        else if(strcmp(keyName, "AB02") == 0) keyCode = KEY_X;
        else if(strcmp(keyName, "AB03") == 0) keyCode = KEY_C;
        else if(strcmp(keyName, "AB04") == 0) keyCode = KEY_V;
        else if(strcmp(keyName, "AB05") == 0) keyCode = KEY_B;
        else if(strcmp(keyName, "AB06") == 0) keyCode = KEY_N;
        else if(strcmp(keyName, "AB07") == 0) keyCode = KEY_M;
        else if(strcmp(keyName, "AB08") == 0) keyCode = KEY_COMMA;
        else if(strcmp(keyName, "AB09") == 0) keyCode = KEY_DECIMAL;
        else if(strcmp(keyName, "AB10") == 0) keyCode = KEY_SLASH;
        else if(strcmp(keyName, "LSGT") == 0) keyCode = KEY_LESS_GREATER_THAN;
        else
        {
            keyCode = UNKNOWN_INPUT_CODE;
        }

        s_keyCodesMap[rawCode] = keyCode;
    }

    XkbFreeNames(s_kbDesc, XkbKeyNamesMask, true);
    XkbFreeKeyboard(s_kbDesc, 0, true);
    XAutoRepeatOff(s_display);
}

void WindowManager::loadGLExtensions()
{
    const char* glxExtensions = glXQueryExtensionsString(s_display, s_screenID);
    std::cout << "\nGLX Extensions Available:\n" << glxExtensions << "\n\n";

    if(!isExtensionSupported(glxExtensions, "GLX_ARB_create_context"))
    {
        s_attribCtxCompat = false;
		std::cout << "GLX_ARB_create_context not supported\n\n";
	}
	else
    {
        glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
	}

    if(!isExtensionSupported(glxExtensions, "GLX_EXT_swap_control"))
    {
        if(!isExtensionSupported(glxExtensions, "GLX_SGI_swap_control"))
        {
            if(!isExtensionSupported(glxExtensions, "GLX_MESA_swap_control"))
            {
                s_vSyncCompat = false;
                std::cout << "Swap Control not supported\n\n";
            }
            else
            {
                glXSwapInterval = (PFNGLXSWAPINTERVALPROC)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalMESA");
                std::cout << "MESA Swap Control supported\n\n";
            }
        }
        else
        {
            glXSwapInterval = (PFNGLXSWAPINTERVALPROC)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalSGI");
            std::cout << "SGI Swap Control supported\n\n";
        }
	}
	else
    {
        glXSwapInterval = (PFNGLXSWAPINTERVALPROC)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalEXT");
        std::cout << "EXT Swap Control supported\n\n";
	}
}

GLXFBConfig WindowManager::chooseBestFBC()
{
    s_fbConfigs = glXChooseFBConfig(s_display, s_screenID, s_glxAttribs, &s_fbCount);
    if(s_fbConfigs == nullptr)
    {
        fatalError("Failed to choose Framebuffer Config.");
    }

    int bestFbConfigIndex = -1;
    int worstFbConfigIndex = -1;
    int bestNumSamples = -1;
    int worstNumSamples = 999;
    for(int i = 0; i < s_fbCount; ++i)
    {
        XVisualInfo* visualInfo = glXGetVisualFromFBConfig(s_display, s_fbConfigs[i]);
        if(visualInfo != nullptr)
        {
            int sampleBuffers;
            int samples;
            glXGetFBConfigAttrib(s_display, s_fbConfigs[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
            glXGetFBConfigAttrib(s_display, s_fbConfigs[i], GLX_SAMPLES, &samples);

            if(bestFbConfigIndex < 0 || (sampleBuffers && samples > bestNumSamples))
            {
                bestFbConfigIndex = i;
                bestNumSamples = samples;
            }
            if(worstFbConfigIndex < 0 || !sampleBuffers || samples < worstNumSamples)
            {
                worstFbConfigIndex = i;
                worstNumSamples = samples;
            }
            XFree(visualInfo);
        }
    }
    GLXFBConfig bestFbConfig = s_fbConfigs[bestFbConfigIndex];
    XFree(s_fbConfigs);

    return bestFbConfig;
}

void WindowManager::fatalError(const char* msg)
{
    std::cerr << "Fatal Error: " << msg << std::endl;
    XCloseDisplay(s_display);
    exit(EXIT_FAILURE);
}

void WindowManager::HSGILProc()
{
    switch(s_event.type)
    {
        case ClientMessage:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[s_event.xany.window]];
                if(s_event.xclient.data.l[0] == windowInstance->m_atomWmDeleteWindow)
                {
                    windowInstance->destroyRenderingWindow();
                }
            }
            break;

        case DestroyNotify:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[s_event.xany.window]];
                windowInstance->destroyRenderingWindow();
            }
            break;

        case KeyPress:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[s_event.xany.window]];
                windowInstance->mf_keyCallbackFunction(windowInstance->m_windowCallbackInstance, KEY_PRESSED, static_cast<InputCode>(s_keyCodesMap[s_event.xkey.keycode]), s_repeatFlag);
            }
            break;

        case KeyRelease:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[s_event.xany.window]];
                windowInstance->mf_keyCallbackFunction(windowInstance->m_windowCallbackInstance, KEY_RELEASED, static_cast<InputCode>(s_keyCodesMap[s_event.xkey.keycode]), false);
            }
            break;

        default:
            break;
    }
}

} // namespace gil
