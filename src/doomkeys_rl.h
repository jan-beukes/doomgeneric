//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//       Key definitions
//

#ifndef __DOOMKEYS__
#define __DOOMKEYS__

//
// DOOM keyboard definition.
// This is the stuff configured by Setup.Exe.
// Most key data are simple ascii (uppercased).
//
#define DKEY_RIGHTARROW	0xae
#define DKEY_LEFTARROW	0xac
#define DKEY_UPARROW		0xad
#define DKEY_DOWNARROW	0xaf
#define DKEY_STRAFE_L	0xa0
#define DKEY_STRAFE_R	0xa1
#define DKEY_USE			0xa2
#define DKEY_FIRE		0xa3
#define DKEY_ESCAPE		27
#define DKEY_ENTER		13
#define DKEY_TAB			9
#define DKEY_F1			(0x80+0x3b)
#define DKEY_F2			(0x80+0x3c)
#define DKEY_F3			(0x80+0x3d)
#define DKEY_F4			(0x80+0x3e)
#define DKEY_F5			(0x80+0x3f)
#define DKEY_F6			(0x80+0x40)
#define DKEY_F7			(0x80+0x41)
#define DKEY_F8			(0x80+0x42)
#define DKEY_F9			(0x80+0x43)
#define DKEY_F10			(0x80+0x44)
#define DKEY_F11			(0x80+0x57)
#define DKEY_F12			(0x80+0x58)

#define DKEY_BACKSPACE	0x7f
#define DKEY_PAUSE	0xff

#define DKEY_EQUALS	0x3d
#define DKEY_MINUS	0x2d

#define DKEY_RSHIFT	(0x80+0x36)
#define DKEY_RCTRL	(0x80+0x1d)
#define DKEY_RALT	(0x80+0x38)

#define DKEY_LALT	DKEY_RALT

// new keys:

#define DKEY_CAPSLOCK    (0x80+0x3a)
#define DKEY_NUMLOCK     (0x80+0x45)
#define DKEY_SCRLCK      (0x80+0x46)
#define DKEY_PRTSCR      (0x80+0x59)

#define DKEY_HOME        (0x80+0x47)
#define DKEY_END         (0x80+0x4f)
#define DKEY_PGUP        (0x80+0x49)
#define DKEY_PGDN        (0x80+0x51)
#define DKEY_INS         (0x80+0x52)
#define DKEY_DEL         (0x80+0x53)

#define DKEYP_0          0
#define DKEYP_1          DKEY_END
#define DKEYP_2          DKEY_DOWNARROW
#define DKEYP_3          DKEY_PGDN
#define DKEYP_4          DKEY_LEFTARROW
#define DKEYP_5          '5'
#define DKEYP_6          DKEY_RIGHTARROW
#define DKEYP_7          DKEY_HOME
#define DKEYP_8          DKEY_UPARROW
#define DKEYP_9          DKEY_PGUP

#define DKEYP_DIVIDE     '/'
#define DKEYP_PLUS       '+'
#define DKEYP_MINUS      '-'
#define DKEYP_MULTIPLY   '*'
#define DKEYP_PERIOD     0
#define DKEYP_EQUALS     DKEY_EQUALS
#define DKEYP_ENTER      DKEY_ENTER

#endif          // __DOOMKEYS__

