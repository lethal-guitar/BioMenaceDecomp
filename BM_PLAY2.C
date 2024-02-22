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

#include "BM_DEF.H"

// PLACEHOLDER

Sint16 TABLE3[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 0, 5, 4,
  3, 2, 1, 0, 15, 14, 5, 4, 3, 2, 1, 0, 15, 14, 3, 2,
  1, 0, 15, 14, 13, 12, 9, 8, 7, 6, 5, 4, 3, 2, 9, 8,
  7, 6, 5, 4, 3, 2, 11, 10, 9, 8, 7, 6, 5, 4, 100, 200,
  500, 800, 1000, 1500, 2000
};

Sint16 word_39476 = 5000;

extern Sint16 word_3FA56;


void sub_1BD88(objtype* ob, objtype* hit)
{
  // TODO

  switch (hit->obclass)
  {
    case 15:
    case 17:
    case 18:
    case 28:
    case 35:
    case 37:
    case 38:
      break;

    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 13:
    case 19:
    case 23:
    case 24:
    case 25:
    case 26:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 36:
    case 39:
    case 40:
    case 41:
    case 42:
      if (!word_3FA56)
      {
        DamagePlayer(ob, 1);
      }
      break;
  }
}


void UpdateScore(objtype *ob)
{
}


void sub_1D2B5(objtype* ob)
{
}


void sub_1E21D(Sint16 x, Sint16 y, Sint16 t)
{
}


void sub_1D51D()
{
}


void sub_1D7E4()
{
}


void sub_1DD25()
{
}


void sub_1EA04()
{
}


void ResetScoreBox(void)
{
// PLACEHOLDER
" NP\xc3Throw grenades to blow up monsters!\n";
"Collect machine guns for automatic fire.\n";
"Use keycards to turn off electric beams.\n";
"Push <UP> and use key to open door.\n";
"Find out where these crystal shards go.\n";
"Find out where these crystal shards go.\n";
"Find out where these crystal shards go.\n";
"Find out where these crystal shards go.\n";
"Hmm....What a strange key!\n";
"Throw grenades to blow up monsters!\n";
"Super Gun!  Bullets do 5x the damage!\n";
"Cool!  Land mines!\n";
"Plasma Bolts!  Burn holes through enemies!\n";
"Collect 50 gems for an extra life!\n";
"First Aid Kit restores you to full health.\n";
"You found a secret level warp gem!\n";
"Oh look! What a cute little nuclear bomb!\n";
"It's an anti-radiation pill!\n";
"Now you're invincible to monster attacks!\n";
"RoboPal gives you extra fire power!\n";
"99";
"99";
"ChunkBloom: Bad dir!";
"FragBloom: Bad dir!";
"ThrowPower: Bad dir!";
"SpawnShot: Bad dir!";
"SpawnLaserShot: Bad dir!";
"SpawnLaserShot: Bad dir!";
}
