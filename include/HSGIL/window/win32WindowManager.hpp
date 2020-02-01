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

#ifndef HSGIL_WIN32_WINDOW_MANAGER_HPP
#define HSGIL_WIN32_WINDOW_MANAGER_HPP

#include <HSGIL/external/glad/glad.h>

#include <HSGIL/core/common.hpp>
#include <HSGIL/core/inputEvents.hpp>
#include <HSGIL/core/inputBindings.hpp>
#include <HSGIL/math/mUtils.hpp>

#include <windows.h>
#include <GL/wglext.h>

#include <unordered_map>

#define GLDCC_NAME_SIZE 6u
#define ATTRIB_LIST_SIZE 17u
#define MAX_WINDOW_INSTANCES 16u

namespace gil
{
class Window;
class WindowManager;

class WMLazyPtr final
{
public:
    WMLazyPtr();
    ~WMLazyPtr();

    void init(const uint32 t_index);

    WindowManager& operator*();
    WindowManager* operator->();
    bool operator==(const WMLazyPtr& o);
    bool operator!=(const WMLazyPtr& o);
    bool operator==(const std::nullptr_t nullPtr);
    bool operator!=(const std::nullptr_t nullPtr);
    operator WindowManager*();

private:
    WindowManager* m_wm;
};

typedef void (*KeyCallbackFunction)(Window*, InputEvent, InputCode, bool);

class WindowManager final
{
    friend WMLazyPtr;
public:
    static WindowManager* createInstance();
    static WindowManager* getInstance(const uint32 index);

    bool isActive();
    void createRenderingWindow(const char* title, int x, int y, int width, int height);
    void destroyRenderingWindow();

    void setKeyCallbackFunction(Window* t_windowCallbackInstance, KeyCallbackFunction tf_keyCallbackFunction);

    void pollEvents();
    void swapBuffers();

private:
    bool m_active;

    uint32 m_index;
    HWND m_windowHandle;

    HDC m_deviceContextHandle;
    HGLRC m_glRenderingContextHandle;

    Window* m_windowCallbackInstance;
    KeyCallbackFunction mf_keyCallbackFunction;

    /* Privated constructor and destructor */

    WindowManager(const uint32 t_index);
    ~WindowManager();

    /* Static Instances */

    static uint32 s_activeSessions;
    static uint32 s_wmInstanceCount;
    static WMLazyPtr s_wmInstances[MAX_WINDOW_INSTANCES];
    static std::unordered_map<HWND, uint32> s_hwndMap;

    /* Satatic Win32 API Internal Data */

    static WNDCLASSEXA s_gldcc;
    static const char  s_gldccName[GLDCC_NAME_SIZE];

    static PIXELFORMATDESCRIPTOR s_pfd;
    static const int s_attribs[ATTRIB_LIST_SIZE];

    static MSG s_msg;
    static bool s_repeatFlag;
    static HINSTANCE s_procInstanceHandle;

    static void registerGLDCC();
    static void loadGLExtensions();
    static void fatalError(const char* msg);

    static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    static PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
    static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

    static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
    static PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;

    static LRESULT CALLBACK HSGILProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /* Deleted Constructors and assignment */

    WindowManager(const WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;

    WindowManager& operator=(const WindowManager&) = delete;
};

} // namespace gil

#endif // HSGIL_WIN32_WINDOW_MANAGER_HPP
