/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2021 Adrian Bedregal and Gabriela Chipana                      *
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

int WindowManager::s_keyCodesMap[NUM_KEYS_SIZE] {};
int WindowManager::s_keyPhysicStates[NUM_KEYS_SIZE] {};

XEvent WindowManager::s_event {};
XkbDescPtr WindowManager::s_kbDesc {nullptr};
Display* WindowManager::s_display {nullptr};
Screen*  WindowManager::s_screen  {nullptr};
int WindowManager::s_screenID {-1};

int WindowManager::s_fbCount {0};
GLXFBConfig* WindowManager::s_fbConfigs {nullptr};

bool WindowManager::s_vSyncCompat {true};
bool WindowManager::s_attribCtxCompat {true};

PFNGLXCREATECONTEXTATTRIBSARBPROC WindowManager::glXCreateContextAttribsARB {nullptr};

bool WindowManager::glXSwapIntervalEXTMode {false};
PFNGLXSWAPINTERVALPROC1 WindowManager::glXSwapInterval1 {nullptr};
PFNGLXSWAPINTERVALPROC2 WindowManager::glXSwapInterval2 {nullptr};

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
        XFlush(s_display);

        m_active = true;
        ++s_activeSessions;
        s_hwndMap[m_windowHandle] = m_index;
    }
}

void WindowManager::destroyWindow()
{
    if(m_active)
    {
        glXDestroyContext(s_display, m_context);

        XFree(m_visual);
        XFreeColormap(s_display, m_windowAttributes.colormap);
        XDestroyWindow(s_display, m_windowHandle);

        --s_activeSessions;
        m_active = false;

        if(!s_activeSessions)
        {
            XCloseDisplay(s_display);
        }
    }
}

void WindowManager::setKeyCallbackFunction(IWindow* t_windowCallbackInstance, KeyCallbackFunction tf_keyCallbackFunction)
{
    m_windowCallbackInstance = t_windowCallbackInstance;
    mf_keyCallbackFunction = tf_keyCallbackFunction;
}

void WindowManager::pollEvents()
{
    if(s_activeSessions && XPending(s_display) > 0)
    {
        XNextEvent(s_display, &s_event);
        HSGILProc();
    }
}

void WindowManager::swapBuffers()
{
    if(m_active)
    {
        glXSwapBuffers(s_display, m_windowHandle);
    }
}

WindowManager::WindowManager(const uint32 t_index)
    : m_active      {false},
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
        if(glXSwapIntervalEXTMode)
            glXSwapInterval1(glXGetCurrentDisplay(), glXGetCurrentDrawable(), 1);
        else
            glXSwapInterval2(1);
    }
    std::cout << "Context Created" << std::endl;
}

void WindowManager::loadKeyboardMap()
{
    s_kbDesc = XkbGetMap(s_display, 0, XkbUseCoreKbd);
    XkbGetNames(s_display, XkbKeyNamesMask, s_kbDesc);

    int rawCode;
    int keyCode;
    char keyName[XkbKeyNameLength + 1];

    memset(s_keyCodesMap, -1, sizeof(s_keyCodesMap));
    memset(s_keyPhysicStates, 0, sizeof(s_keyPhysicStates));
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
        else if(strcmp(keyName, "AB09") == 0) keyCode = KEY_PERIOD;
        else if(strcmp(keyName, "AB10") == 0) keyCode = KEY_SLASH;
        else if(strcmp(keyName, "LSGT") == 0) keyCode = KEY_LESS_GREATER_THAN;
        else
        {
            keyCode = -1;
        }

        s_keyCodesMap[rawCode] = keyCode;
    }

    XkbFreeNames(s_kbDesc, XkbKeyNamesMask, true);
    XkbFreeKeyboard(s_kbDesc, 0, true);

    for(rawCode = 0; rawCode < 256; ++rawCode)
    {
        if(s_keyCodesMap[rawCode] < 0)
        {
            s_keyCodesMap[rawCode] = rawToStandard(rawCode);
        }
    }

    XkbSetDetectableAutoRepeat(s_display, true, nullptr);
}

int WindowManager::rawToStandard(int rawCode)
{
    int keySym;

    keySym = XkbKeycodeToKeysym(s_display, rawCode, 0, 0);
    switch(keySym)
    {
        case XK_Escape:         return KEY_ESCAPE;
        case XK_BackSpace:      return KEY_BACKSPACE;
        case XK_Return:         return KEY_ENTER;
        case XK_Tab:            return KEY_TAB;
        case XK_space:          return KEY_SPACE;

        case XK_Shift_L:        return KEY_LEFT_SHIFT;
        case XK_Shift_R:        return KEY_RIGHT_SHIFT;
        case XK_Control_L:      return KEY_LEFT_CONTROL;
        case XK_Control_R:      return KEY_RIGHT_CONTROL;
        case XK_Alt_L:          return KEY_LEFT_ALT;
        case XK_Alt_R:          return KEY_RIGHT_ALT;
        case XK_Super_L:        return KEY_LEFT_WINDOWS;
        case XK_Super_R:        return KEY_RIGHT_WINDOWS;
        case XK_Menu:           return KEY_MENU;

        case XK_Num_Lock:       return KEY_NUM_LOCK;
        case XK_Caps_Lock:      return KEY_CAPS_LOCK;
        case XK_Scroll_Lock:    return KEY_SCROLL_LOCK;

        case XK_Select:         return KEY_SELECT;
        case XK_Print:          return KEY_PRINT_SCREEN;
        case XK_Execute:        return KEY_EXECUTE;
        case XK_Help:           return KEY_HELP;

        case XK_Pause:          return KEY_PAUSE;
        case XK_Clear:          return KEY_CLEAR;
        case XK_Delete:         return KEY_DELETE;

        case XK_Home:           return KEY_HOME;
        case XK_End:            return KEY_END;
        case XK_Page_Up:        return KEY_PAGE_UP;
        case XK_Page_Down:      return KEY_PAGE_DOWN;
        case XK_Insert:         return KEY_INSERT;

        case XK_Left:           return KEY_LEFT;
        case XK_Up:             return KEY_UP;
        case XK_Right:          return KEY_RIGHT;
        case XK_Down:           return KEY_DOWN;

        case XK_F1:             return KEY_F1;
        case XK_F2:             return KEY_F2;
        case XK_F3:             return KEY_F3;
        case XK_F4:             return KEY_F4;
        case XK_F5:             return KEY_F5;
        case XK_F6:             return KEY_F6;
        case XK_F7:             return KEY_F7;
        case XK_F8:             return KEY_F8;
        case XK_F9:             return KEY_F9;
        case XK_F10:            return KEY_F10;
        case XK_F11:            return KEY_F11;
        case XK_F12:            return KEY_F12;
        case XK_F13:            return KEY_F13;
        case XK_F14:            return KEY_F14;
        case XK_F15:            return KEY_F15;
        case XK_F16:            return KEY_F16;
        case XK_F17:            return KEY_F17;
        case XK_F18:            return KEY_F18;
        case XK_F19:            return KEY_F19;
        case XK_F20:            return KEY_F20;
        case XK_F21:            return KEY_F21;
        case XK_F22:            return KEY_F22;
        case XK_F23:            return KEY_F23;
        case XK_F24:            return KEY_F24;

        case XK_KP_Add:         return KEY_ADD;
        case XK_KP_Subtract:    return KEY_SUBTRACT;
        case XK_KP_Multiply:    return KEY_MULTIPLY;
        case XK_KP_Divide:      return KEY_DIVIDE;

        default:                break;
    }

    keySym = XkbKeycodeToKeysym(s_display, rawCode, 0, 1);
    switch(keySym)
    {
        case XK_KP_0:           return KEY_NUMPAD_0;
        case XK_KP_1:           return KEY_NUMPAD_1;
        case XK_KP_2:           return KEY_NUMPAD_2;
        case XK_KP_3:           return KEY_NUMPAD_3;
        case XK_KP_4:           return KEY_NUMPAD_4;
        case XK_KP_5:           return KEY_NUMPAD_5;
        case XK_KP_6:           return KEY_NUMPAD_6;
        case XK_KP_7:           return KEY_NUMPAD_7;
        case XK_KP_8:           return KEY_NUMPAD_8;
        case XK_KP_9:           return KEY_NUMPAD_9;

        case XK_KP_Separator:   return KEY_SEPARATOR;
        case XK_KP_Decimal:     return KEY_DECIMAL;
        case XK_KP_Enter:       return KEY_NUMPAD_ENTER;
        case XK_KP_Equal:       return KEY_NUMPAD_EQUAL;

        default:                return UNKNOWN_INPUT_CODE;
    }
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
                glXSwapInterval2 = (PFNGLXSWAPINTERVALPROC2)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalMESA");
                std::cout << "MESA Swap Control supported\n\n";
            }
        }
        else
        {
            glXSwapInterval2 = (PFNGLXSWAPINTERVALPROC2)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalSGI");
            std::cout << "SGI Swap Control supported\n\n";
        }
	}
	else
    {
        glXSwapIntervalEXTMode = true;
        glXSwapInterval1 = (PFNGLXSWAPINTERVALPROC1)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalEXT");
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
                    std::cout << "CInternal Window Destroy Request" << std::endl;
                    windowInstance->destroyWindow();
                }
            }
            break;

        case DestroyNotify:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[s_event.xany.window]];
                std::cout << "DInternal Window Destroy Request" << std::endl;
                windowInstance->destroyWindow();
            }
            break;

        case KeyPress:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[s_event.xany.window]];
                windowInstance->mf_keyCallbackFunction(windowInstance->m_windowCallbackInstance, KEY_PRESSED, static_cast<InputCode>(s_keyCodesMap[s_event.xkey.keycode]), s_keyPhysicStates[s_event.xkey.keycode]);
                s_keyPhysicStates[s_event.xkey.keycode] = 1;
            }
            break;

        case KeyRelease:
            {
                s_keyPhysicStates[s_event.xkey.keycode] = 0;
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[s_event.xany.window]];
                windowInstance->mf_keyCallbackFunction(windowInstance->m_windowCallbackInstance, KEY_RELEASED, static_cast<InputCode>(s_keyCodesMap[s_event.xkey.keycode]), false);
            }
            break;

        default:
            break;
    }
}

} // namespace gil
