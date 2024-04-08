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

#ifndef __AUDIO_H__
#define __AUDIO_H__

//#include "VERSION.H"

/////////////////////////////////////////////////
//
// MUSE Header for .BM1
//
/////////////////////////////////////////////////

#define NUMSOUNDS     LASTSOUND
#define NUMSNDCHUNKS  ((3*LASTSOUND)+LASTMUSIC)

//
// Sound names & indexes
//
typedef enum {
  SND_ROBOTBOUNCE = 0,
  SND_TAKEDAMAGE = 1,
  SND_PLAYERSLUGJUMP = 2,
  SND_CEILWALKERFALL = 3,
  SND_CEILWALKERLAND = 4,
  SND_PLAYERDIE = 5,
  SND_TURRETSHOOT = 6,
  SND_EXPLOSION = 7,
  SND_SQUISHPLAYER = 8,
  SND_SNAKESPIT = 9,
  SND_SLUGATTACK = 10,
  SND_PLAYERJUMP = 11,
  SND_PLAYERGUN = 12,
  SND_RICOCHET = 13,
  SND_COLLECTAMMO = 14,
  SND_COLLECTKEY = 15,
  SND_COLLECTONEUP = 16,
  SND_USEKEYCARD = 17,
  SND_NOKEY = 18,
  SND_OPENDOOR = 19,
  SND_USESWITCH = 20,
  SND_LASERSHOT = 21,
  SND_USESHARD = 22,
  SND_ROAR = 23,
  SND_DANGER = 24,
  SND_BLEEPBLOOP = 25,
  SND_SPECIALMOVE = 26,
  SND_COLLECTBONUS = 27,
  SND_COLLECTHEALTH = 28,
  SND_ZING = 29,
  SND_TANKSHOOT = 30,
  SND_COLLECTPOTION = 31,
  SND_32 = 32,
  SND_COLLECTVALUABLEITEM = 33,
  SND_34 = 34,
  SND_CRUSHERMOVE = 35,
  SND_FALLINGBLOCK = 36,
  SND_BLOCKPUSHED = 37,
  SND_SEWERMUTANTTHROW = 38,
  SND_DROPSLIME = 39,
  SND_BEACONACTIVE = 40,
  SND_NAGTIMERTICK = 41,
  LASTSOUND = 42
} soundnames;

#if LASTSOUND != 42
#error bad sound enum!
#endif

#define NOWAYSND SND_NOKEY

//
// Base offsets
//
#define STARTPCSOUNDS     0
#define STARTADLIBSOUNDS  (STARTPCSOUNDS+NUMSOUNDS)
#define STARTDIGISOUNDS   (STARTADLIBSOUNDS+NUMSOUNDS)
#define STARTMUSIC        (STARTDIGISOUNDS+NUMSOUNDS)

//
// Music names & indexes
//
typedef enum {
  LASTMUSIC = 18
} musicnames;

/////////////////////////////////////////////////
//
// Thanks for playing with MUSE!
//
/////////////////////////////////////////////////

#endif
