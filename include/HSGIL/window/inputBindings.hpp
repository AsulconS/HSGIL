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

#ifndef HSGIL_INPUT_BINDINGS_HPP
#define HSGIL_INPUT_BINDINGS_HPP

namespace gil
{
enum InputCode
{
    /* MOUSE BUTTONS */
    MOUSE_BUTTON_LEFT   = 0x01,
    MOUSE_BUTTON_RIGHT  = 0x02,
    MOUSE_BUTTON_MIDDLE = 0x04,
    MOUSE_BUTTON_X1     = 0x05,
    MOUSE_BUTTON_X2     = 0x06,

    KEY_BACKSPACE = 0x08,
    KEY_TAB       = 0x09,
    KEY_CLEAR     = 0x0C,
    KEY_ENTER     = 0x0D,

    KEY_GEN_SHIFT   = 0x10,
    KEY_GEN_CONTROL = 0x11,
    KEY_GEN_ALT     = 0x12,
    KEY_PAUSE       = 0x13,
    KEY_CAPS_LOCK   = 0x14,

    KEY_ESCAPE    = 0x1B,
    KEY_SPACE     = 0x20,
    KEY_PAGE_UP   = 0x21,
    KEY_PAGE_DOWN = 0x22,
    KEY_END       = 0x23,
    KEY_HOME      = 0x24,

    /* DIRECTIONAL KEYS */
    KEY_LEFT  = 0x25,
    KEY_UP    = 0x26,
    KEY_RIGHT = 0x27,
    KEY_DOWN  = 0x28,

    KEY_SELECT       = 0x29,
    KEY_PRINT        = 0x2A,
    KEY_EXECUTE      = 0x2B,
    KEY_PRINT_SCREEN = 0x2C,

    KEY_INSERT = 0x2D,
    KEY_DELETE = 0x2E,
    KEY_HELP   = 0x2F,

    /* NUMERIC KEYS */
    KEY_0 = 0x30,
    KEY_1 = 0x31,
    KEY_2 = 0x32,
    KEY_3 = 0x33,
    KEY_4 = 0x34,
    KEY_5 = 0x35,
    KEY_6 = 0x36,
    KEY_7 = 0x37,
    KEY_8 = 0x38,
    KEY_9 = 0x39,

    /* ALPHABETIC KEYS */
    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,

    KEY_LEFT_WINDOWS  = 0x5B,
    KEY_RIGHT_WINDOWS = 0x5C,
    KEY_APPS          = 0x5D,
    KEY_SLEEP         = 0x5F,

    /* NUMERIC PAD KEYS */
    KEY_NUMPAD_0 = 0x60,
    KEY_NUMPAD_1 = 0x61,
    KEY_NUMPAD_2 = 0x62,
    KEY_NUMPAD_3 = 0x63,
    KEY_NUMPAD_4 = 0x64,
    KEY_NUMPAD_5 = 0x65,
    KEY_NUMPAD_6 = 0x66,
    KEY_NUMPAD_7 = 0x67,
    KEY_NUMPAD_8 = 0x68,
    KEY_NUMPAD_9 = 0x69,

    KEY_MULTIPLY  = 0x6A,
    KEY_ADD       = 0x6B,
    KEY_SEPARATOR = 0x6C,
    KEY_SUBTRACT  = 0x6D,
    KEY_DECIMAL   = 0x6E,
    KEY_DIVIDE    = 0x6F,

    /* F KEYS */
    KEY_F1  = 0x70,
    KEY_F2  = 0x71,
    KEY_F3  = 0x72,
    KEY_F4  = 0x73,
    KEY_F5  = 0x74,
    KEY_F6  = 0x75,
    KEY_F7  = 0x76,
    KEY_F8  = 0x77,
    KEY_F9  = 0x78,
    KEY_F10 = 0x79,
    KEY_F11 = 0x7A,
    KEY_F12 = 0x7B,
    KEY_F13 = 0x7C,
    KEY_F14 = 0x7D,
    KEY_F15 = 0x7E,
    KEY_F16 = 0x7F,
    KEY_F17 = 0x80,
    KEY_F18 = 0x81,
    KEY_F19 = 0x82,
    KEY_F20 = 0x83,
    KEY_F21 = 0x84,
    KEY_F22 = 0x85,
    KEY_F23 = 0x86,
    KEY_F24 = 0x87,

    KEY_NUMLOCK    = 0x90,
    KEY_SCROLLLOCK = 0x91,

    KEY_LEFT_SHIFT    = 0xA0,
    KEY_RIGHT_SHIFT   = 0xA1,
    KEY_LEFT_CONTROL  = 0xA2,
    KEY_RIGHT_CONTROL = 0xA3,

    KEY_LEFT_MENU  = 0xA4,
    KEY_RIGHT_MENU = 0xA5,

    KEY_BROWSER_BACK      = 0xA6,
    KEY_BROWSER_FORWARD   = 0xA7,
    KEY_BROWSER_REFRESH   = 0xA8,
    KEY_BROWSER_STOP      = 0xA9,
    KEY_BROWSER_SEARCH    = 0xAA,
    KEY_BROWSER_FAVORITES = 0xAB,
    KEY_BROWSER_HOME      = 0xAC,

    KEY_VOLUME_MUTE  = 0xAD,
    KEY_VOLUME_DOWN  = 0xAE,
    KEY_VOLUME_UP    = 0xAF,

    KEY_MEDIA_NEXT_TRACK = 0xB0,
    KEY_MEDIA_PREV_TRACK = 0xB1,
    KEY_MEDIA_STOP       = 0xB2,
    KEY_MEDIA_PLAY_PAUSE = 0xB3,

    KEY_LAUNCH_MAIL         = 0xB4,
    KEY_LAUNCH_MEDIA_SELECT = 0xB5,
    KEY_LAUNCH_APP_1        = 0xB6,
    KEY_LAUNCH_APP_2        = 0xB7,

    KEY_SEMICOLON     = 0xBA,
    KEY_EQUAL         = 0xBB,
    KEY_COMMA         = 0xBC,
    KEY_MINUS         = 0xBD,
    KEY_PERIOD        = 0xBE,
    KEY_SLASH         = 0xBF,
    KEY_GRAVE_ACCENT  = 0xC0,

    KEY_LEFT_BRACKET  = 0xDB,
    KEY_BACKSLASH     = 0xDC,
    KEY_RIGHT_BRACKET = 0xDD,
    KEY_APOSTROPHE    = 0xDE,

    UNKNOWN_INPUT_CODE = 0xFF
};

} // namespace gil

#endif // HSGIL_INPUT_BINDINGS_HPP
