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
std::unordered_map<XWindow, uint32> WindowManager::s_hwndMap {};

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

XEvent WindowManager::s_event {};
Display* WindowManager::s_display {nullptr};
Screen*  WindowManager::s_screen  {nullptr};
int WindowManager::s_screenID {-1};

bool WindowManager::s_repeatFlag {false};

int WindowManager::s_fbCount {0};
GLXFBConfig* WindowManager::s_fbConfigs {nullptr};

bool WindowManager::s_vSyncCompat {true};
bool WindowManager::s_attribCtxCompat {true};

glXCreateContextAttribsARBProc WindowManager::glXCreateContextAttribsARB {nullptr};

glXSwapIntervalProc WindowManager::glXSwapInterval {nullptr};

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
        m_windowAttributes.event_mask = ExposureMask;

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
        XFree(m_visual);
	    XFreeColormap(s_display, m_windowAttributes.colormap);
	    XDestroyWindow(s_display, m_windowHandle);
        m_active = false;
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
    : m_active                   {false},
      m_index                    {t_index}
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
        glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
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
                glXSwapInterval = (glXSwapIntervalProc)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalMESA");
                std::cout << "MESA Swap Control supported\n\n";
            }
        }
        else
        {
            glXSwapInterval = (glXSwapIntervalProc)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalSGI");
            std::cout << "SGI Swap Control supported\n\n";
        }
	}
	else
    {
        glXSwapInterval = (glXSwapIntervalProc)glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalEXT");
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
            if(s_event.xclient.data.l[0] == s_wmInstances[s_hwndMap[s_event.xany.window]]->m_atomWmDeleteWindow)
            {
				break;
			}

        case DestroyNotify:
            break;

        default:
            break;
    }
}

} // namespace gil
