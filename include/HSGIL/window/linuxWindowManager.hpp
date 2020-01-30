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

#ifndef HSGIL_LINUX_WINDOW_MANAGER_HPP
#define HSGIL_LINUX_WINDOW_MANAGER_HPP

#include <HSGIL/external/glad/glad.h>

#include <HSGIL/core/common.hpp>
#include <HSGIL/core/inputEvents.hpp>
#include <HSGIL/core/inputBindings.hpp>
#include <HSGIL/math/mUtils.hpp>

#include <HSGIL/window/wUtils.hpp>

#include <X11/Xlib.h>

#include <iostream>
#include <unordered_map>

#define ATTRIB_LIST_SIZE 23u
#define MAX_WINDOW_INSTANCES 16u

typedef XID XWindow;

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
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, bool, const int*);

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
    XWindow m_windowHandle;
    Atom m_atomWmDeleteWindow;

    GLXFBConfig m_fbConfig;
    GLXContext m_context;

    XVisualInfo* m_visual;
    XSetWindowAttributes m_windowAttributes;

    Window* m_windowCallbackInstance;
    KeyCallbackFunction mf_keyCallbackFunction;

    /* Privated constructor and destructor */

    WindowManager(const uint32 t_index);
    ~WindowManager();

    /* Static Instances */

    static uint32 s_activeSessions;
    static uint32 s_wmInstanceCount;
    static WMLazyPtr s_wmInstances[MAX_WINDOW_INSTANCES];
    static std::unordered_map<XWindow, uint32> s_hwndMap;

    /* Satatic Win32 API Internal Data */

    static const int s_glxAttribs[ATTRIB_LIST_SIZE];

    static XEvent s_event;
    static Display* s_display;
    static Screen*  s_screen;
    static int s_screenID;
    static bool s_repeatFlag;

    static int s_fbCount;
    static GLXFBConfig* s_fbConfigs;

    static glXCreateContextAttribsARBProc glXCreateContextAttribsARB;

    static void createContext();
    static GLXFBConfig chooseBestFBC();

    static void loadGLExtensions();
    static void fatalError(const char* msg);

    static void HSGILProc();

    /* Deleted Constructors and assignment */

    WindowManager(const WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;

    WindowManager& operator=(const WindowManager&) = delete;
};

} // namespace gil

#endif // HSGIL_LINUX_WINDOW_MANAGER_HPP