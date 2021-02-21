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

#include <HSGIL/window/win32WindowManager.hpp>

namespace gil
{
uint32 WindowManager::s_activeSessions  {0u};
uint32 WindowManager::s_wmInstanceCount {0u};
WMLazyPtr WindowManager::s_wmInstances[MAX_WINDOW_INSTANCES] {};

std::unordered_map<HWND, uint32> WindowManager::s_hwndMap {};

WNDCLASSEXA WindowManager::s_gldcc {};
const char  WindowManager::s_gldccName[GLDCC_NAME_SIZE] {"GLDCC"};

PIXELFORMATDESCRIPTOR WindowManager::s_pfd;
const int WindowManager::s_attribs[ATTRIB_LIST_SIZE]
{
    WGL_DRAW_TO_WINDOW_ARB  , GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB  , GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB   , GL_TRUE,
    WGL_ACCELERATION_ARB    , WGL_FULL_ACCELERATION_ARB,
    WGL_PIXEL_TYPE_ARB      , WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB      , 32,
    WGL_DEPTH_BITS_ARB      , 24,
    WGL_STENCIL_BITS_ARB    , 8,
    0
};

int WindowManager::s_keyPhysicStates[NUM_KEYS_SIZE] {};

MSG WindowManager::s_msg {};
HINSTANCE WindowManager::s_procInstanceHandle {nullptr};

bool WindowManager::s_vSyncCompat {true};
bool WindowManager::s_attribCtxCompat {true};
bool WindowManager::s_pixelFormatCompat {true};

PFNWGLCHOOSEPIXELFORMATARBPROC WindowManager::wglChoosePixelFormatARB {nullptr};
PFNWGLGETEXTENSIONSSTRINGARBPROC WindowManager::wglGetExtensionsStringARB {nullptr};
PFNWGLCREATECONTEXTATTRIBSARBPROC WindowManager::wglCreateContextAttribsARB {nullptr};

PFNWGLSWAPINTERVALEXTPROC WindowManager::wglSwapIntervalEXT {nullptr};
PFNWGLGETSWAPINTERVALEXTPROC WindowManager::wglGetSwapIntervalEXT {nullptr};

WindowManager* WindowManager::createInstance()
{
    if(!s_wmInstanceCount)
    {
        s_procInstanceHandle = GetModuleHandleW(nullptr);
        registerGLDCC();
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
    if(index > 0 && index < (MAX_WINDOW_INSTANCES - 1))
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
        m_windowHandle = CreateWindowExA
        (
            0L,                               // Extended Window Style
            s_gldcc.lpszClassName,            // Window Class Name
            title,                            // Window Title
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Window Style

            x, y, width, height,

            nullptr,              // Parent Window Handle
            nullptr,              // Menu Handle
            s_procInstanceHandle, // Handle to current instance
            nullptr               // Additional Application Data
        );
        m_active = true;
        ++s_activeSessions;
        s_hwndMap[m_windowHandle] = m_index;
    }
}

void WindowManager::destroyWindow()
{
    if(m_active)
    {
        DestroyWindow(m_windowHandle);
        m_active = false;
    }
}

void WindowManager::setEventCallbackFunction(IWindow* t_windowCallbackInstance, EventCallbackFunction tf_eventCallbackFunction)
{
    m_windowCallbackInstance = t_windowCallbackInstance;
    mf_eventCallbackFunction = tf_eventCallbackFunction;
}

void WindowManager::pollEvents()
{
    if(PeekMessageW(&s_msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&s_msg);
        DispatchMessageW(&s_msg);
    }
}

void WindowManager::swapBuffers()
{
    SwapBuffers(m_deviceContextHandle);
}

WindowManager::WindowManager(const uint32 t_index)
    : m_active                   {false},
      m_index                    {t_index},
      m_windowHandle             {nullptr},
      m_deviceContextHandle      {nullptr},
      m_glRenderingContextHandle {nullptr}
{
}

WindowManager::~WindowManager()
{
}

void WindowManager::registerGLDCC()
{
    s_gldcc.cbSize        = sizeof(WNDCLASSEXA);
    s_gldcc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    s_gldcc.lpfnWndProc   = HSGILProc;
    s_gldcc.cbClsExtra    = 0;
    s_gldcc.cbWndExtra    = 0;
    s_gldcc.hInstance     = s_procInstanceHandle;
    s_gldcc.hIcon         = nullptr;
    s_gldcc.hCursor       = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512));
    s_gldcc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    s_gldcc.lpszMenuName  = nullptr;
    s_gldcc.lpszClassName = s_gldccName;
    s_gldcc.hIconSm       = nullptr;

    if(!RegisterClassExA(&s_gldcc))
    {
        fatalError("Failed to register Rendering Window.");
    }
}

void WindowManager::loadGLExtensions()
{
    WNDCLASSEXA dWindowClass;
    dWindowClass.cbSize         = sizeof(WNDCLASSEXA);
    dWindowClass.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    dWindowClass.lpfnWndProc    = DefWindowProcA;
    dWindowClass.cbClsExtra     = 0;
    dWindowClass.cbWndExtra     = 0;
    dWindowClass.hInstance      = s_procInstanceHandle;
    dWindowClass.hIcon          = nullptr;
    dWindowClass.hCursor        = nullptr;
    dWindowClass.hbrBackground  = nullptr;
    dWindowClass.lpszMenuName   = nullptr;
    dWindowClass.lpszClassName  = "DWC";
    dWindowClass.hIconSm        = nullptr;

    if(!RegisterClassExA(&dWindowClass))
    {
        fatalError("Failed to register dummy OpenGL window.");
    }

    HWND dWindow = CreateWindowExA
    (
        0L,                         // Extended Window Style
        dWindowClass.lpszClassName, // Window Class Name
        "DWC",                      // Window Title
        0,                          // Window Style

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        nullptr,                // Parent Window Handle
        nullptr,                // Menu Handle
        dWindowClass.hInstance, // Handle to current instance
        nullptr                 // Additional Application Data
    );

    if(!dWindow)
    {
        fatalError("Failed to create dummy OpenGL window.");
    }

    HDC ddc = GetDC(dWindow);

    PIXELFORMATDESCRIPTOR dpfd;
    dpfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
    dpfd.nVersion        = 1;
    dpfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    dpfd.iPixelType      = PFD_TYPE_RGBA;
    dpfd.cColorBits      = 32;
    dpfd.cRedBits        = 0;
    dpfd.cRedShift       = 0;
    dpfd.cBlueBits       = 0;
    dpfd.cBlueShift      = 0;
    dpfd.cGreenBits      = 0;
    dpfd.cGreenShift     = 0;
    dpfd.cAlphaBits      = 0;
    dpfd.cAlphaShift     = 0;
    dpfd.cAccumBits      = 0;
    dpfd.cAccumRedBits   = 0;
    dpfd.cAccumBlueBits  = 0;
    dpfd.cAccumGreenBits = 0;
    dpfd.cAccumAlphaBits = 0;
    dpfd.cDepthBits      = 24;
    dpfd.cStencilBits    = 8;
    dpfd.cAuxBuffers     = 0;
    dpfd.iLayerType      = PFD_MAIN_PLANE;
    dpfd.bReserved       = 0;
    dpfd.dwLayerMask     = 0;
    dpfd.dwVisibleMask   = 0;
    dpfd.dwDamageMask    = 0;

    int dPixelformat = ChoosePixelFormat(ddc, &dpfd);
    if(!dPixelformat)
    {
        fatalError("Failed to find a suitable pixel format.");
    }
    if(!SetPixelFormat(ddc, dPixelformat, &dpfd))
    {
        fatalError("Failed to set the pixel format.");
    }

    HGLRC dContext = wglCreateContext(ddc);
    if(!dContext)
    {
        fatalError("Failed to create a dummy OpenGL rendering context.");
    }

    if(!wglMakeCurrent(ddc, dContext))
    {
        fatalError("Failed to activate dummy OpenGL rendering context.");
    }

    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
    const char* wglExtensions = wglGetExtensionsStringARB(ddc);

    if(!isExtensionSupported(wglExtensions, "WGL_ARB_create_context"))
    {
        s_attribCtxCompat = false;
        warning("WGL_ARB_create_context not supported.");
    }
    else
    {
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    }

    if(!isExtensionSupported(wglExtensions, "WGL_ARB_pixel_format"))
    {
        s_pfd = dpfd;
        s_pixelFormatCompat = false;
        warning("WGL_ARB_pixel_format not supported.");
    }
    else
    {
        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    }

    if(!isExtensionSupported(wglExtensions, "WGL_EXT_swap_control"))
    {
        s_vSyncCompat = false;
        warning("WGL_EXT_swap_control not supported (V-Sync not supported).");
    }
    else
    {
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
    }

    wglMakeCurrent(ddc, nullptr);
    wglDeleteContext(dContext);
    ReleaseDC(dWindow, ddc);
    DestroyWindow(dWindow);
}

void WindowManager::warning(const char* msg)
{
    MessageBoxA(nullptr, msg, "Warning", MB_OK | MB_ICONWARNING);
}

void WindowManager::fatalError(const char* msg)
{
    MessageBoxA(nullptr, msg, "Fatal Error", MB_OK | MB_ICONERROR);
    exit(EXIT_FAILURE);
}

LRESULT CALLBACK WindowManager::HSGILProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                HDC& hdc = windowInstance->m_deviceContextHandle;
                hdc = GetDC(hWnd);

                int pixelFormat;

                if(s_pixelFormatCompat)
                {
                    uint32 numFormats;
                    wglChoosePixelFormatARB(hdc, s_attribs, nullptr, 1, &pixelFormat, &numFormats);
                    DescribePixelFormat(hdc, pixelFormat, sizeof(s_pfd), &s_pfd);
                }
                else
                {
                    pixelFormat = ChoosePixelFormat(hdc, &s_pfd);
                }

                SetPixelFormat(hdc, pixelFormat, &s_pfd);

                HGLRC& glContext = windowInstance->m_glRenderingContextHandle;

                if(s_attribCtxCompat)
                {
                    int glContextAttribs[] =
                    {
                        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                        0
                    };

                    glContext = wglCreateContextAttribsARB(hdc, 0, glContextAttribs);
                }
                else
                {
                    glContext = wglCreateContext(hdc);
                }
                wglMakeCurrent(hdc, glContext);

                gladLoadGL();

                if(s_vSyncCompat)
                {
                    wglSwapIntervalEXT(1);
                }

                memset(s_keyPhysicStates, 0, sizeof(s_keyPhysicStates));

                MessageBoxA(0, (char*)glGetString(GL_VERSION), "OpenGL Version", 0);
                MessageBoxA(0, (char*)glGetString(GL_SHADING_LANGUAGE_VERSION), "GLSL Version", 0);
            }
            break;

        case WM_DESTROY:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                --s_activeSessions;
                windowInstance->m_active = false;
                wglMakeCurrent(windowInstance->m_deviceContextHandle, nullptr);
                wglDeleteContext(windowInstance->m_glRenderingContextHandle);
                if(!s_activeSessions)
                {
                    PostQuitMessage(0);
                }
            }
            break;

        case WM_PAINT:
            {
                SwapBuffers(s_wmInstances[s_hwndMap[hWnd]]->m_deviceContextHandle);
            }
            break;

        case WM_KEYDOWN:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                windowInstance->mf_eventCallbackFunction(windowInstance->m_windowCallbackInstance, KEY_PRESSED, static_cast<InputCode>(wParam), s_keyPhysicStates[wParam]);
                s_keyPhysicStates[wParam] = 1;
            }
            break;

        case WM_KEYUP:
            {
                s_keyPhysicStates[wParam] = 0;
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                windowInstance->mf_eventCallbackFunction(windowInstance->m_windowCallbackInstance, KEY_RELEASED, static_cast<InputCode>(wParam), false);
            }
            break;

        case WM_KILLFOCUS:
            {
                std::cout << "Lost focus" << std::endl;
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                for(uint32 i = 0; i < NUM_KEYS_SIZE; ++i)
                {
                    if(s_keyPhysicStates[i])
                    {
                        s_keyPhysicStates[i] = 0;
                        windowInstance->mf_eventCallbackFunction(windowInstance->m_windowCallbackInstance, KEY_RELEASED, static_cast<InputCode>(i), false);
                    }
                }
            }
            break;

        case WM_SYSKEYDOWN:
            {
                std::cout << "WM_SYSKEYDOWN" << std::endl;
            }
            break;

        case WM_SYSKEYUP:
            {
                std::cout << "WM_SYSKEYUP" << std::endl;
            }
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

} // namespace gil
