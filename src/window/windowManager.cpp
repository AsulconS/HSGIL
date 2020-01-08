/********************************************************************************
 *                                                                              *
 * HSGIL - Handy Scalable Graphics Integration Library                          *
 * Copyright (c) 2019 Adrian Bedregal and Gabriela Chipana                      *
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

#include <HSGIL/window/windowManager.hpp>

namespace gil
{
uint32 WindowManager::s_activeSessions  {0u};
uint32 WindowManager::s_wmInstanceCount {0u};
WMLazyPtr WindowManager::s_wmInstances[MAX_WINDOW_INSTANCES] {};
std::unordered_map<HWND, uint32> WindowManager::s_hwndMap {};

WNDCLASSEXA WindowManager::s_gldcc {};
const char  WindowManager::s_gldccName[GLDCC_NAME_SIZE] {"GLDCC"};

PIXELFORMATDESCRIPTOR WindowManager::s_pfd;

MSG WindowManager::s_msg {};
bool WindowManager::s_repeatFlag {false};
HINSTANCE WindowManager::s_procInstanceHandle {nullptr};

/* Window Manager Lazy Pointer Stuff */

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

/* Window Manager Stuff */

WindowManager* WindowManager::createInstance()
{
    if(!s_wmInstanceCount)
    {
        s_procInstanceHandle = GetModuleHandleW(nullptr);
        initGLPFD();
        registerGLDCC();

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
        m_windowHandle = CreateWindowExA
        (
            0L,                                 // Extended Window Style
            s_gldcc.lpszClassName,              // Window Class Name
            title,                              // Window Title
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // Window Style

            x, y, width, height,

            NULL,                   // Parent Window Handle
            NULL,                   // Menu Handle
            s_procInstanceHandle,   // Handle to current instance
            NULL                    // Additional Application Data
        );
        m_active = true;
        ++s_activeSessions;
        s_hwndMap[m_windowHandle] = m_index;
    }
}

void WindowManager::destroyRenderingWindow()
{
    if(m_active)
    {
        DestroyWindow(m_windowHandle);
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
    if(PeekMessageW(&s_msg, NULL, 0, 0, PM_REMOVE))
    {
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

void WindowManager::initGLPFD()
{
    s_pfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR);
    s_pfd.nVersion        = 1;
    s_pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    s_pfd.iPixelType      = PFD_TYPE_RGBA;
    s_pfd.cColorBits      = 32;
    s_pfd.cRedBits        = 0;
    s_pfd.cRedShift       = 0;
    s_pfd.cBlueBits       = 0;
    s_pfd.cBlueShift      = 0;
    s_pfd.cGreenBits      = 0;
    s_pfd.cGreenShift     = 0;
    s_pfd.cAlphaBits      = 0;
    s_pfd.cAlphaShift     = 0;
    s_pfd.cAccumBits      = 0;
    s_pfd.cAccumRedBits   = 0;
    s_pfd.cAccumBlueBits  = 0;
    s_pfd.cAccumGreenBits = 0;
    s_pfd.cAccumAlphaBits = 0;
    s_pfd.cDepthBits      = 24;
    s_pfd.cStencilBits    = 8;
    s_pfd.cAuxBuffers     = 0;
    s_pfd.iLayerType      = PFD_MAIN_PLANE;
    s_pfd.bReserved       = 0;
    s_pfd.dwLayerMask     = 0;
    s_pfd.dwVisibleMask   = 0;
    s_pfd.dwDamageMask    = 0;
}

void WindowManager::registerGLDCC()
{
    s_gldcc.cbSize        = sizeof(WNDCLASSEXW);
    s_gldcc.style         = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    s_gldcc.lpfnWndProc   = HSGILInputProc;
    s_gldcc.cbClsExtra    = 0;
    s_gldcc.cbWndExtra    = 0;
    s_gldcc.hInstance     = s_procInstanceHandle;
    s_gldcc.hIcon         = NULL;
    s_gldcc.hCursor       = LoadCursorA(NULL, MAKEINTRESOURCEA(32512));
    s_gldcc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    s_gldcc.lpszMenuName  = NULL;
    s_gldcc.lpszClassName = s_gldccName;
    s_gldcc.hIconSm       = NULL;

    RegisterClassExA(&s_gldcc);
}

LRESULT CALLBACK WindowManager::HSGILInputProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                HDC& hdc = windowInstance->m_deviceContextHandle;
                hdc = GetDC(hWnd);
                int format = ChoosePixelFormat(hdc, &s_pfd);
                SetPixelFormat(hdc, format, &s_pfd);

                HGLRC& hglrc = windowInstance->m_glRenderingContextHandle;
                hglrc = wglCreateContext(hdc);
                wglMakeCurrent(hdc, hglrc);

                gladLoadGL();
                MessageBoxA(0, (char*)glGetString(GL_VERSION), "OpenGL Version", 0);
                MessageBoxA(0, (char*)glGetString(GL_SHADING_LANGUAGE_VERSION), "GLSL Version", 0);
            }
            break;

        case WM_DESTROY:
            {
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                --s_activeSessions;
                windowInstance->m_active = false;
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
                windowInstance->mf_keyCallbackFunction(windowInstance->m_windowCallbackInstance, WM_KEYDOWN, wParam, s_repeatFlag);
                s_repeatFlag = true;
            }
            break;

        case WM_KEYUP:
            {
                s_repeatFlag = false;
                WindowManager* windowInstance = s_wmInstances[s_hwndMap[hWnd]];
                windowInstance->mf_keyCallbackFunction(windowInstance->m_windowCallbackInstance, WM_KEYUP, wParam, s_repeatFlag);
            }
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

} // namespace gil
