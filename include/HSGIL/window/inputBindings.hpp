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
    MOUSE_BUTTON_LEFT   = 0x001,
    MOUSE_BUTTON_RIGHT  = 0x002,
    MOUSE_BUTTON_MIDDLE = 0x004,
    MOUSE_BUTTON_X1     = 0x005,
    MOUSE_BUTTON_X2     = 0x006,

    KEY_BACKSPACE = 0x008,
    KEY_TAB       = 0x009,
    KEY_CLEAR     = 0x00C,
    KEY_ENTER     = 0x00D,

    KEY_GEN_SHIFT   = 0x010,
    KEY_GEN_CONTROL = 0x011,
    KEY_GEN_ALT     = 0x012,
    KEY_PAUSE       = 0x013,
    KEY_CAPS_LOCK   = 0x014,

    KEY_ESCAPE    = 0x01B,
    KEY_SPACE     = 0x020,
    KEY_PAGE_UP   = 0x021,
    KEY_PAGE_DOWN = 0x022,
    KEY_END       = 0x023,
    KEY_HOME      = 0x024,

    /* DIRECTIONAL KEYS */
    KEY_LEFT  = 0x025,
    KEY_UP    = 0x026,
    KEY_RIGHT = 0x027,
    KEY_DOWN  = 0x028,

    KEY_SELECT       = 0x029,
    KEY_PRINT        = 0x02A,
    KEY_EXECUTE      = 0x02B,
    KEY_PRINT_SCREEN = 0x02C,

    KEY_INSERT = 0x02D,
    KEY_DELETE = 0x02E,
    KEY_HELP   = 0x02F,

    /* NUMERIC KEYS */
    KEY_0 = 0x030,
    KEY_1 = 0x031,
    KEY_2 = 0x032,
    KEY_3 = 0x033,
    KEY_4 = 0x034,
    KEY_5 = 0x035,
    KEY_6 = 0x036,
    KEY_7 = 0x037,
    KEY_8 = 0x038,
    KEY_9 = 0x039,

    /* ALPHABETIC KEYS */
    KEY_A = 0x041,
    KEY_B = 0x042,
    KEY_C = 0x043,
    KEY_D = 0x044,
    KEY_E = 0x045,
    KEY_F = 0x046,
    KEY_G = 0x047,
    KEY_H = 0x048,
    KEY_I = 0x049,
    KEY_J = 0x04A,
    KEY_K = 0x04B,
    KEY_L = 0x04C,
    KEY_M = 0x04D,
    KEY_N = 0x04E,
    KEY_O = 0x04F,
    KEY_P = 0x050,
    KEY_Q = 0x051,
    KEY_R = 0x052,
    KEY_S = 0x053,
    KEY_T = 0x054,
    KEY_U = 0x055,
    KEY_V = 0x056,
    KEY_W = 0x057,
    KEY_X = 0x058,
    KEY_Y = 0x059,
    KEY_Z = 0x05A,

    KEY_LEFT_WINDOWS  = 0x05B,
    KEY_RIGHT_WINDOWS = 0x05C,
    KEY_APPS          = 0x05D,
    KEY_SLEEP         = 0x05F,

    /* NUMERIC PAD KEYS */
    KEY_NUMPAD_0 = 0x060,
    KEY_NUMPAD_1 = 0x061,
    KEY_NUMPAD_2 = 0x062,
    KEY_NUMPAD_3 = 0x063,
    KEY_NUMPAD_4 = 0x064,
    KEY_NUMPAD_5 = 0x065,
    KEY_NUMPAD_6 = 0x066,
    KEY_NUMPAD_7 = 0x067,
    KEY_NUMPAD_8 = 0x068,
    KEY_NUMPAD_9 = 0x069,

    KEY_MULTIPLY  = 0x06A,
    KEY_ADD       = 0x06B,
    KEY_SEPARATOR = 0x06C,
    KEY_SUBTRACT  = 0x06D,
    KEY_DECIMAL   = 0x06E,
    KEY_DIVIDE    = 0x06F,

    /* F KEYS */
    KEY_F1  = 0x070,
    KEY_F2  = 0x071,
    KEY_F3  = 0x072,
    KEY_F4  = 0x073,
    KEY_F5  = 0x074,
    KEY_F6  = 0x075,
    KEY_F7  = 0x076,
    KEY_F8  = 0x077,
    KEY_F9  = 0x078,
    KEY_F10 = 0x079,
    KEY_F11 = 0x07A,
    KEY_F12 = 0x07B,
    KEY_F13 = 0x07C,
    KEY_F14 = 0x07D,
    KEY_F15 = 0x07E,
    KEY_F16 = 0x07F,
    KEY_F17 = 0x080,
    KEY_F18 = 0x081,
    KEY_F19 = 0x082,
    KEY_F20 = 0x083,
    KEY_F21 = 0x084,
    KEY_F22 = 0x085,
    KEY_F23 = 0x086,
    KEY_F24 = 0x087,

    KEY_NUM_LOCK    = 0x090,
    KEY_SCROLL_LOCK = 0x091,

    KEY_LEFT_SHIFT    = 0x0A0,
    KEY_RIGHT_SHIFT   = 0x0A1,
    KEY_LEFT_CONTROL  = 0x0A2,
    KEY_RIGHT_CONTROL = 0x0A3,

    KEY_LEFT_MENU  = 0x0A4,
    KEY_RIGHT_MENU = 0x0A5,

/*
    Not available yet

    KEY_BROWSER_BACK      = 0x0A6,
    KEY_BROWSER_FORWARD   = 0x0A7,
    KEY_BROWSER_REFRESH   = 0x0A8,
    KEY_BROWSER_STOP      = 0x0A9,
    KEY_BROWSER_SEARCH    = 0x0AA,
    KEY_BROWSER_FAVORITES = 0x0AB,
    KEY_BROWSER_HOME      = 0x0AC,

    KEY_VOLUME_MUTE  = 0x0AD,
    KEY_VOLUME_DOWN  = 0x0AE,
    KEY_VOLUME_UP    = 0x0AF,

    KEY_MEDIA_NEXT_TRACK = 0x0B0,
    KEY_MEDIA_PREV_TRACK = 0x0B1,
    KEY_MEDIA_STOP       = 0x0B2,
    KEY_MEDIA_PLAY_PAUSE = 0x0B3,

    KEY_LAUNCH_MAIL         = 0x0B4,
    KEY_LAUNCH_MEDIA_SELECT = 0x0B5,
    KEY_LAUNCH_APP_1        = 0x0B6,
    KEY_LAUNCH_APP_2        = 0x0B7,
*/

    KEY_SEMICOLON     = 0x0BA,
    KEY_EQUAL         = 0x0BB,
    KEY_COMMA         = 0x0BC,
    KEY_MINUS         = 0x0BD,
    KEY_PERIOD        = 0x0BE,
    KEY_SLASH         = 0x0BF,
    KEY_GRAVE_ACCENT  = 0x0C0,

    KEY_LEFT_BRACKET  = 0x0DB,
    KEY_BACKSLASH     = 0x0DC,
    KEY_RIGHT_BRACKET = 0x0DD,
    KEY_APOSTROPHE    = 0x0DE,

// Free from 0x03A to 0x040

    KEY_LESS_GREATER_THAN = 0x03A,

    KEY_LEFT_ALT = 0x03B,
    KEY_RIGHT_ALT = 0x03C,

    KEY_NUMPAD_ENTER = 0x03D,
    KEY_NUMPAD_EQUAL = 0x03E,

// Form Buttons from 0x040 to 0x0A4

    BUTTON_000 = 0x040,
    BUTTON_001 = 0x041,
    BUTTON_002 = 0x042,
    BUTTON_003 = 0x043,
    BUTTON_004 = 0x044,
    BUTTON_005 = 0x045,
    BUTTON_006 = 0x046,
    BUTTON_007 = 0x047,
    BUTTON_008 = 0x048,
    BUTTON_009 = 0x049,
    BUTTON_010 = 0x04A,
    BUTTON_011 = 0x04B,

// --------------------------------

// Aliases

    KEY_RETURN = KEY_ENTER,
    KEY_MENU   = KEY_APPS,

// --------------------------------

    UNKNOWN_INPUT_CODE = 0xFFF
};

} // namespace gil

#endif // HSGIL_INPUT_BINDINGS_HPP
