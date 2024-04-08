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
  SND_ROBOTBOUNCE,
  SND_TAKEDAMAGE,
  SND_PLAYERSLUGJUMP,
  SND_CEILWALKERFALL,
  SND_CEILWALKERLAND,
  SND_PLAYERDIE,
  SND_TURRETSHOOT,
  SND_EXPLOSION,
  SND_SQUISH,
  SND_SNAKESPIT,
  SND_SLUGATTACK,
  SND_PLAYERJUMP,
  SND_PLAYERGUN,
  SND_RICOCHET,
  SND_COLLECTAMMO,
  SND_COLLECTKEY,
  SND_COLLECTONEUP,
  SND_USEKEYCARD,
  SND_NOKEY,
  SND_OPENDOOR,
  SND_USESWITCH,
  SND_LASERSHOT,
  SND_USESHARD,
  SND_ROAR,
  SND_DANGER,
  SND_BLEEPBLOOP,
  SND_SPECIALMOVE,
  SND_COLLECTBONUS,
  SND_COLLECTHEALTH,
  SND_ZING,
  SND_BOOM,
  SND_COLLECTPOTION,
  SND_32,
  SND_COLLECTVALUABLEITEM,
  SND_34,
  SND_CRUSHERMOVE,
  SND_FALLINGBLOCK,
  SND_BLOCKPUSHED,
  SND_SEWERMUTANTTHROW,
  SND_DROPSLIME,
  SND_BEACONACTIVE,
  SND_NAGTIMERTICK,
  LASTSOUND
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
  CRUISING_MUS,
  WEASEL_MUS,
  BIOTHEME1_MUS,
  SNAKESAVE_MUS,
  DIRTYWATER_MUS,
  ROCKINIT_MUS,
  ROBOTY_MUS,
  BAYOU_MUS,
  PRISONER_MUS,
  DRSHOCK_MUS,
  CHASING_MUS,
  LIKEITWAS_MUS,
  FANFARE_MUS,
  SAVED_MUS,
  RESTING_MUS,
  CANTGET_MUS,
  NONVINCE_MUS,
  THECITY_MUS,
  LASTMUSIC = 18
} musicnames;

/////////////////////////////////////////////////
//
// Thanks for playing with MUSE!
//
/////////////////////////////////////////////////

#endif
