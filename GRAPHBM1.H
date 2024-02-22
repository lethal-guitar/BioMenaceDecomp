/* Copyright (C) 2024 Nikolai Wuttke-Hohendorf
 *
 * Based on reconstructed Commander Keen 4-6 Source Code
 * Copyright (C) 2021 K1n9_Duk3
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __GFX_H__
#define __GFX_H__

//#include "VERSION.H"

//////////////////////////////////////
//
// Graphics .H file for .BM1
// not IGRAB-ed :)
//
//////////////////////////////////////

//
// Lump creation macros
//

#define START_LUMP(actualname, dummyname) actualname, dummyname=actualname-1,
#define END_LUMP(actualname, dummyname) dummyname, actualname=dummyname-1,

//
// Amount of each data item
//

#define NUMCHUNKS    NUMGRCHUNKS
#define NUMFONT      2
#define NUMFONTM     0
#define NUMPICS      50
#define NUMPICM      1
#define NUMSPRITES   355
#define NUMTILE8     144
#define NUMTILE8M    36
#define NUMTILE16    1512
#define NUMTILE16M   2682
#define NUMTILE32    0
#define NUMTILE32M   0
#define NUMEXTERNS   14

//
// File offsets for data items
//
#define STRUCTPIC    0
#define STRUCTPICM   1
#define STRUCTSPRITE 2

#define STARTFONT    3
#define STARTFONTM   (STARTFONT+NUMFONT)
#define STARTPICS    (STARTFONTM+NUMFONTM)
#define STARTPICM    (STARTPICS+NUMPICS)
#define STARTSPRITES (STARTPICM+NUMPICM)
#define STARTTILE8   (STARTSPRITES+NUMSPRITES)
#define STARTTILE8M  (STARTTILE8+1)
#define STARTTILE16  (STARTTILE8M+1)
#define STARTTILE16M (STARTTILE16+NUMTILE16)
#define STARTTILE32  (STARTTILE16M+NUMTILE16M)
#define STARTTILE32M (STARTTILE32+NUMTILE32)
#define STARTEXTERNS (STARTTILE32M+NUMTILE32M)

typedef enum {
  LASTFONT=STARTPICS-1,

  //
  // PICS
  //

  START_LUMP(CONTROLS_LUMP_START, __CONTROLSSTART)
  CP_MAINMENUPIC,              // 5
  CP_NEWGAMEMENUPIC,           // 6
  CP_LOADMENUPIC,              // 7
  CP_SAVEMENUPIC,              // 8
  CP_CONFIGMENUPIC,            // 9
  CP_SOUNDMENUPIC,             // 10
  CP_MUSICMENUPIC,             // 11
  CP_KEYBOARDMENUPIC,          // 12
  CP_KEYMOVEMENTPIC,           // 13
  CP_KEYBUTTONPIC,             // 14
  CP_JOYSTICKMENUPIC,          // 15
  CP_OPTIONSMENUPIC,           // 16
  CP_QUITPIC,                  // 17
  CP_JOYSTICKPIC,              // 18
  CP_MENUSCREENPIC,            // 19
  END_LUMP(CONTROLS_LUMP_END, __CONTROLSEND)

  TITLESHAREWAREPIC,           // 20
  H_HELPPIC,                   // 21
  H_HANDPIC,                   // 22
  H_FLASHARROW1PIC,            // 23
  H_FLASHARROW2PIC,            // 24
  H_TOPWINDOWPIC,              // 25
  H_LEFTWINDOWPIC,             // 26
  H_RIGHTWINDOWPIC,            // 27
  H_BOTTOMINFOPIC,             // 28
  H_ESCPIC,                    // 29
  H_LARROWPIC,                 // 30
  H_RARROWPIC,                 // 31
  H_ENTERPIC,                  // 32
  ENDOFTEXTPIC,                // 33
  H_VISAPIC,                   // 34
  H_MCPIC,                     // 35
  HOSTAGE1PIC,                 // 36
  HOSTAGE2PIC,                 // 37
  HOSTAGE3PIC,                 // 38
  SNAKETALKPIC,                // 39
  H_ITEMSPIC,                  // 40
  STORY1PIC,                   // 41
  STORY2PIC,                   // 42
  STORY3PIC,                   // 43
  STORY4PIC,                   // 44
  STORY5PIC,                   // 45
  STORY6PIC,                   // 46
  STORY7PIC,                   // 47
  STORY8PIC,                   // 48
  STORY9PIC,                   // 49
  CREDITSPIC,                  // 50
  PREVIEWPIC,                  // 51
  TITLEPIC,                    // 52
  NOTSHAREWAREPIC,             // 53
  TECHHELPPIC,                 // 54

  CP_MENUMASKPICM,             // 55

  //
  // SPRITES
  //

  HANDCURSORSPR,               // 56

  START_LUMP(PLAYER_LUMP_START, __PLAYERSTART)
  SHOT_EXPLODE1_SPR,           // 57
  SHOT_EXPLODE2_SPR,           // 58
  SMALL_FIRE1_SPR,             // 59
  SMALL_FIRE2_SPR,             // 60
  SMALL_FIRE3_SPR,             // 61
  LASER_BLAST_BLUE_SPR,        // 62
  LASER_BLAST_RED_SPR,         // 63
  SUPER_BLAST_R_SPR,           // 64
  SUPER_BLAST_L_SPR,           // 65
  PLAYER_STANDING_R_SPR,       // 66
  PLAYER_WALKING1_R_SPR,       // 67
  PLAYER_WALKING2_R_SPR,       // 68
  PLAYER_WALKING3_R_SPR,       // 69
  PLAYER_WALKING4_R_SPR,       // 70
  PLAYER_STANDING_L_SPR,       // 71
  PLAYER_WALKING1_L_SPR,       // 72
  PLAYER_WALKING2_L_SPR,       // 73
  PLAYER_WALKING3_L_SPR,       // 74
  PLAYER_WALKING4_L_SPR,       // 75
  PLAYER_SHIELDED1_R_SPR,      // 76
  PLAYER_SHIELDED2_R_SPR,      // 77
  PLAYER_SHIELDED1_L_SPR,      // 78
  PLAYER_SHIELDED2_L_SPR,      // 79
  PLAYER_INTERACTING_SPR,      // 80
  PLAYER_CLIMBING1_SPR,        // 81
  PLAYER_CLIMBING2_SPR,        // 82
  PLAYER_DYING1_SPR,           // 83
  PLAYER_DYING2_SPR,           // 84
  PLAYER_THROW1_R_SPR,         // 85
  PLAYER_THROW2_R_SPR,         // 86
  PLAYER_THROW1_L_SPR,         // 87
  PLAYER_THROW2_L_SPR,         // 88
  PLAYER_IN_AIR_THROW1_R_SPR,  // 89
  PLAYER_IN_AIR_THROW2_R_SPR,  // 90
  PLAYER_IN_AIR_THROW1_L_SPR,  // 91
  PLAYER_IN_AIR_THROW2_L_SPR,  // 92
  PLAYER_SHOOT1_R_SPR,         // 93
  PLAYER_SHOOT2_R_SPR,         // 94
  PLAYER_SHOOT1_L_SPR,         // 95
  PLAYER_SHOOT2_L_SPR,         // 96
  PLAYER_CROUCH_R_SPR,         // 97
  PLAYER_CROUCH_SHOOT_R_SPR,   // 98
  PLAYER_CROUCH_L_SPR,         // 99
  PLAYER_CROUCH_SHOOT_L_SPR,   // 100
  PLAYER_IN_AIR_R_SPR,         // 101
  PLAYER_IN_AIR_SHOOT_R_SPR,   // 102
  PLAYER_IN_AIR_L_SPR,         // 103
  PLAYER_IN_AIR_SHOOT_L_SPR,   // 104

  // TODO

  END_LUMP(PLAYER_LUMP_END, __PLAYEREND)

  // last sprite ID
  PLACEHOLDER = 409,

  //
  // TILES (these don't need names)
  //

  LASTTILE=STARTEXTERNS-1,

  //
  // EXTERNS
  //

  //texts
  T_1,                         // 4607
  T_2,                         // 4608
  T_3,                         // 4609
  T_4,                         // 4610
  T_5,                         // 4611
  T_6,                         // 4612
  T_7,                         // 4613

  //demos
  DEMO0,                       // 4614
  DEMO1,                       // 4615
  DEMO2,                       // 4616
  DEMO3,                       // 4617
  DEMO4,                       // 4618

  ORDERSCREEN,                 // 4619
  OUTOFMEM,                    // 4620

  NUMGRCHUNKS
} graphicnums;

#undef START_LUMP
#undef END_LUMP

#endif //__GFX_H__

