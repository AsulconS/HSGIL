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

#ifndef HSGIL_KEY_BINDINGS_HPP
#define HSGIL_KEY_BINDINGS_HPP

namespace gil
{
enum Key
{
    /* SPECIAL KEYS 01 */
    KEY_UNKNOWN    = -1,
    KEY_SPACE      = 32,
    KEY_APOSTROPHE = 39,
    KEY_COMMA      = 44,
    KEY_MINUS      = 45,
    KEY_PERIOD     = 46,
    KEY_SLASH      = 47,

    /* NUMERIC KEYS */
    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,

    /* Special KEYS 02 */
    KEY_SEMICOLON = 59,
    KEY_EQUAL     = 61,

    /* ALPHABETIC KEYS */
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,

    /* SPECIAL KEYS 02 */
    KEY_LEFT_BRACKET  = 91,
    KEY_BACKSLASH     = 92,
    KEY_RIGHT_BRACKET = 93,
    KEY_GRAVE_ACCENT  = 96,

    /*------------------- */
    /* GLFW COMPATIBILITY */
    /*------------------- */

    /* SPECIAL KEYS 03 */
    KEY_RETURN    = 257, // 256,
    KEY_ESCAPE    = 256, // 257,
    KEY_DELETE_B  = 259, // 258,
    KEY_TAB       = 258, // 259,
    KEY_CAPS_LOCK = 280, // 260,

    /* F KEYS */
    KEY_F1  = 290, // 261,
    KEY_F2  = 291, // 262,
    KEY_F3  = 292, // 263,
    KEY_F4  = 293, // 264,
    KEY_F5  = 294, // 265,
    KEY_F6  = 295, // 266,
    KEY_F7  = 296, // 267,
    KEY_F8  = 297, // 268,
    KEY_F9  = 298, // 269,
    KEY_F10 = 299, // 270,
    KEY_F11 = 300, // 271,
    KEY_F12 = 301, // 272,

    /* SPECIAL KEYS 04 */
    KEY_PRINT_SCREEN = 283, // 273,
    KEY_SCROLL_LOCK  = 281, // 274,
    KEY_PAUSE        = 284, // 275,

    /* SPECIAL KEYS 05 */
    KEY_INSERT    = 260, // 276,
    KEY_HOME      = 268, // 277,
    KEY_PAGE_UP   = 266, // 278,
    KEY_DELETE_F  = 261, // 279,
    KEY_END       = 269, // 280,
    KEY_PAGE_DOWN = 267, // 281,

    /* DIRECTIONAL KEYS */
    KEY_RIGHT = 262, // 282,
    KEY_LEFT  = 263, // 283,
    KEY_DOWN  = 264, // 284,
    KEY_UP    = 265, // 285,

    /* SPECIAL KEYS 06 */
    KEY_LEFT_CONTROL  = 341, // 286,
    KEY_LEFT_SHIFT    = 340, // 287,
    KEY_LEFT_ALT      = 342, // 288,
    KEY_LEFT_GUI      = 289,
    KEY_RIGHT_CONTROL = 345, // 290,
    KEY_RIGHT_SHIFT   = 344 , // 291,
    KEY_RIGHT_ALT     = 346, // 292,
    KEY_RIGHT_GUI     = 293,

    /* KEY ENUM DELIMITATORS */
    KEY_FIRST = KEY_SPACE,
    KEY_LAST  = KEY_RIGHT_ALT, // KEY_RIGHT_GUI,

    /* ALTERNATIVE NAME KEYS */
    KEY_ENTER     = KEY_RETURN,
    KEY_BACKSPACE = KEY_DELETE_B,
    KEY_DELETE    = KEY_DELETE_F
};

} // namespace gil

#endif // HSGIL_KEY_BINDINGS_HPP
