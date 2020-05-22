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

#include <HSGIL/core/config.hpp>
#include <HSGIL/core/common.hpp>

#include <HSGIL/math/mUtils.hpp>

#include <HSGIL/window/inputEvents.hpp>
#include <HSGIL/window/inputBindings.hpp>
#include <HSGIL/window/wUtils.hpp>

#include <windows.h>
#include <GL/wglext.h>

#include <unordered_map>

#define NUM_KEYS_SIZE 256u
#define GLDCC_NAME_SIZE 6u
#define FMDCC_NAME_SIZE 6u
#define ATTRIB_LIST_SIZE 17u
#define MAX_WINDOW_INSTANCES 16u

#define MAX_LABEL_INSTANCES 32u
#define MAX_BUTTON_INSTANCES 32u
#define MAX_TEXT_BOX_INSTANCES 32u

namespace gil
{
class IWindow;
class WindowManager;

class HSGIL_API WMLazyPtr final
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

typedef void (*KeyCallbackFunction)(IWindow*, InputEvent, InputCode, bool);

class HSGIL_API WindowManager final
{
    friend WMLazyPtr;
public:
    static WindowManager* createInstance();
    static WindowManager* getInstance(const uint32 index);

    bool isActive();

    Tag createLabel(int x, int y, int width, int height, const char* text);
    Tag createButton(int x, int y, int width, int height, int command, const char* text);
    Tag createTextBox(int x, int y, int width, int height);

    char* getLabelText(const uint32 index);
    char* getButtonText(const uint32 index);
    char* getTextBoxText(const uint32 index);

    void  setLabelText(const uint32 index, const char* text);
    void  setButtonText(const uint32 index, const char* text);
    void  setTextBoxText(const uint32 index, const char* text);

    void createFormWindow(const char* title, int x, int y, int width, int height);
    void createRenderingWindow(const char* title, int x, int y, int width, int height);
    void destroyWindow();

    void setKeyCallbackFunction(IWindow* t_windowCallbackInstance, KeyCallbackFunction tf_keyCallbackFunction);

    void pollEvents();
    void swapBuffers();

private:
    bool m_active;

    uint32 m_index;
    uint32 m_activeLabels;
    uint32 m_activeButtons;
    uint32 m_activeTextBoxes;

    HWND m_mainWindowHandle;
    HWND m_labelHandles[MAX_LABEL_INSTANCES];
    HWND m_buttonHandles[MAX_BUTTON_INSTANCES];
    HWND m_textBoxHandles[MAX_TEXT_BOX_INSTANCES];

    HDC m_deviceContextHandle;
    HGLRC m_glRenderingContextHandle;

    IWindow* m_windowCallbackInstance;
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
    static WNDCLASSEXA s_fmdcc;
    static const char  s_gldccName[GLDCC_NAME_SIZE];
    static const char  s_fmdccName[FMDCC_NAME_SIZE];

    static PIXELFORMATDESCRIPTOR s_pfd;
    static const int s_attribs[ATTRIB_LIST_SIZE];

    static int s_keyPhysicStates[NUM_KEYS_SIZE];

    static MSG s_msg;
    static HINSTANCE s_procInstanceHandle;

    static bool s_vSyncCompat;
    static bool s_attribCtxCompat;
    static bool s_pixelFormatCompat;

    static void registerGLDCC();
    static void registerFMDCC();
    static void loadGLExtensions();
    static void warning(const char* msg);
    static void fatalError(const char* msg);

    static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    static PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
    static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

    static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
    static PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT;

    static LRESULT CALLBACK GLDCCProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK FMDCCProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /* Deleted Constructors and assignment */

    WindowManager(const WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;

    WindowManager& operator=(const WindowManager&) = delete;
};

} // namespace gil

#endif // HSGIL_WIN32_WINDOW_MANAGER_HPP
