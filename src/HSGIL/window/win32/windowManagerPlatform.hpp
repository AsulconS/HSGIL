/**
 * HSGIL - Handy Scalable Graphics Integration Library
 * Copyright (c) 2025 Adrian Bedregal
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include <Windows.h>
#include <Windowsx.h>

#include <HSGIL/core/minimal.hpp>

#include <HSGIL/system/utils/lazyPtr.hpp>
#include <HSGIL/system/utils/safePtr.hpp>

//#include <HSGIL/system/dstr/map.hpp>
#include <map>
#define Map std::map

#include <HSGIL/window/inputEvents.hpp>
#include <HSGIL/window/windowParams.hpp>
#include <HSGIL/window/customization.hpp>

#define NUM_KEYS_SIZE 256u
#define GLDCC_NAME_SIZE 6u
#define ATTRIB_LIST_SIZE 17u
#define MAX_WINDOW_INSTANCES 4u

namespace gil
{
class IWindow;

using EventCallbackFunction = void (*)(IWindow*, InputEvent, WindowParams*);
using ExternalTickCallbackFunction = bool (*)(IWindow*);

class HSGIL_API WindowManager final
{
    friend class gil::LazyPtr<WindowManager>;

public:
    static WindowManager* createInstance();
    static WindowManager* getInstance(const uint32 index);

    bool isActive();
    WindowRectParams createRenderingWindow(const char* title, int x, int y, int width, int height, WindowStyle style);
    void destroyWindow();

    void registerWindowInstance(IWindow* windowInstance);
    void setEventCallbackFunction(EventCallbackFunction tf_eventCallbackFunction);
    void setExternalTickCallbackFunction(ExternalTickCallbackFunction tf_externalTickCallbackFunction);

    void pollEvents();
    void swapBuffers();

    /* Win32-Specific functions */

    HWND getRawHandle();
    static HINSTANCE getProcInstanceRawHandle();

private:
    /* Privated constructor and destructor */

    WindowManager(const uint32 t_index);
    ~WindowManager();

    static void registerAppRenderingWindowClass();
    static void warning(const char* msg);
    static void fatalError(const char* msg);
    static bool isInvalidFuncAddress(void* funcAddress);
    static bool isExtensionSupported(const char* extList, const char* extension);
    static void loadGLExtensions();

    static void handleWindowCreateMsg(HWND hWnd);
    static void handleWindowDestroyMsg(HWND hWnd);
    static void handleKeyDownMsg(HWND hWnd, WPARAM wParam);
    static void handleKeyUpMsg(HWND hWnd, WPARAM wParam);
    static void handleKillFocusMsg(HWND hWnd);
    static void handleMouseButtonDownMsg(HWND hWnd, InputCode inputCode);
    static void handleMouseButtonUpMsg(HWND hWnd, InputCode inputCode);
    static void handleMouseMoveMsg(HWND hWnd, LPARAM lParam);
    static void handleTimerMsg(HWND hWnd);

    static InputCode getInputCodeFromMsg(UINT uMsg);

    static void* HsgilGetProcAddress(const char* name);
    static void HsgilMainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK HsgilWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /* Deleted Constructors and assignment */

    WindowManager(const WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;

    WindowManager& operator=(const WindowManager&) = delete;

private:
    bool m_isInstanceActive;

    uint32 m_index;
    HWND m_windowHandle;
    HDC m_deviceContextHandle;

    /* OpenGL Rendering Context */

    HGLRC m_glRenderingContextHandle;

    /* Window instance and callback */

    IWindow* m_windowCallbackInstance;
    EventCallbackFunction mf_eventCallbackFunction;
    ExternalTickCallbackFunction mf_externalTickCallbackFunction;

    /* Static Instances */

    static uint32 s_activeSessions;
    static uint32 s_wmInstanceCount;
    static gil::LazyPtr<WindowManager> s_wmInstances[MAX_WINDOW_INSTANCES];

    /**
     * @brief   Window Hash Table <Window Handler, Instance ID>
     */
    static gil::SafePtr<Map<HWND, uint32>> s_hwndMap;

    /* Static Win32 API Internal Data */

    static WNDCLASSEXA s_appWndClass;
    static const char  s_appWndClassName[GLDCC_NAME_SIZE];

    static PIXELFORMATDESCRIPTOR s_pfd;
    static const int s_attribs[ATTRIB_LIST_SIZE];

    static int s_mouseTrackCount;
    static int s_keyPhysicStates[NUM_KEYS_SIZE];

    static MSG s_msg;
    static HMODULE s_ogl32Module;
    static HINSTANCE s_procInstanceHandle;

    static bool s_vSyncCompat;
    static bool s_attribCtxCompat;
    static bool s_pixelFormatCompat;
};

} // namespace gil
