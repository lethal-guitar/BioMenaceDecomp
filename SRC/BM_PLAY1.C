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


Uint32 dword_3FA52;
Uint16 invincible;
Uint16 word_3FA66;
Sint16 doorx;
Sint16 doory;
Uint16 word_3FA6C;
Uint8 byte_3FA6E;

boolean upbutton, downbutton, leftbutton, rightbutton, button0, button1, firebutton;

extern boolean word_3FA2A;
extern boolean godmode;
extern boolean button0held, button1held, fireheld;

extern Sint16 word_399FA;

Uint16 arrowflip[] = {
  arrow_South,     arrow_West,      arrow_North,     arrow_East,
  arrow_SouthWest, arrow_NorthWest, arrow_NorthEast, arrow_SouthEast
};

Sint16 word_391BA = 0;
Sint16 word_391BC = 0;
Sint16 word_391BE = 0;
Sint16 word_391C0 = 0;
Sint16 word_391C2 = 0;
Sint16 word_391C4 = 0;
Sint16 word_391C6 = 0;
Sint16 word_391C8 = 0;
Sint16 word_391CA = 0;

Sint16 TABLE2[] = { -8, 0, 8 };

extern statetype far s_player_dying;
extern statetype far s_player_dead;
extern statetype far s_player_fireball;
extern statetype far s_player_shielded1;
extern statetype far s_player_shielded2;
extern statetype far s_player_standing;
extern statetype far s_player_5;
extern statetype far s_player_6;
extern statetype far s_player_lineup;
extern statetype far s_player_enter_door1;
extern statetype far s_player_enter_door2;
extern statetype far s_player_interact1;
extern statetype far s_player_interact2;
extern statetype far s_player_opendoor1;
extern statetype far s_player_opendoor2;
extern statetype far s_player_crouching;
extern statetype far s_player_place_mine;
extern statetype far s_player_climbing_idle;
extern statetype far s_player_climbing1;
extern statetype far s_player_climbing2;
extern statetype far s_player_walking1;
extern statetype far s_player_walking2;
extern statetype far s_player_walking3;
extern statetype far s_player_walking4;
extern statetype far s_player_throwing_grenade1;
extern statetype far s_player_throwing_grenade2;
extern statetype far s_player_throwing_grenade3;
extern statetype far s_player_throwing_grenade_air1;
extern statetype far s_player_throwing_grenade_air2;
extern statetype far s_player_throwing_grenade_air3;
extern statetype far s_player_in_air1;
extern statetype far s_player_in_air2;
extern statetype far s_player_in_air3;
extern statetype far s_player_shoot_single1;
extern statetype far s_player_shoot_single2;
extern statetype far s_player_shoot_single3;
extern statetype far s_player_shoot_single_air1;
extern statetype far s_player_shoot_single_air2;
extern statetype far s_player_shoot_single_air3;
extern statetype far s_player_shoot_single_crouch1;
extern statetype far s_player_shoot_single_crouch2;
extern statetype far s_player_shoot_single_crouch3;
extern statetype far s_player_shoot1;
extern statetype far s_player_shoot2;
extern statetype far s_player_shoot_crouch1;
extern statetype far s_player_shoot_crouch2;
extern statetype far s_player_shoot_air1;
extern statetype far s_player_shoot_air2;
extern statetype far s_seg197;

void sub_1E21D(Sint16 x, Sint16 y, Sint16 t);
void OpenDoor(objtype* ob);
void SnakeShootThink(objtype* ob);
void SnakeDyingThink(objtype* ob);
void R_Dying(objtype* ob);
void SnakeStandThink(objtype* ob);
void SnakeContactShielded(objtype* ob, objtype* hit);
void R_OnGround(objtype* ob);
void R_Walking(objtype* ob);
void SnakeContact(objtype* ob, objtype* hit);
void SnakeContact2(objtype* ob, objtype* hit);
void R_PlayerInAir(objtype* ob);
void SnakeWalkThink(objtype* ob);
void SnakeClimbIdleThink(objtype* ob);
void SnakeShootSingleThink(objtype* ob);
void SnakeShootSingleThink2(objtype* ob);
void SnakeShootSingleCrouchThink(objtype* ob);
void SnakeShootCrouchThink(objtype* ob);
void SnakeClimbThink(objtype* ob);
void SnakeInteractThink(objtype* ob);
void SnakeAirThink(objtype* ob);
void SnakeShootAirThink(objtype* ob);
void SnakeShootAirThink2(objtype* ob);
void CheckFallOffLadder(objtype* ob);

void AlignPlayer(objtype* ob);
void SnakeThrow(objtype* ob);
void WarpToDoorDest(objtype* ob);
void SnakeDeadThink(objtype* ob);

void ShowCompatibilityInfoMessage();
void BossDialog();

statetype far s_player_dying = {
  PLAYER_DYING1_SPR, PLAYER_DYING1_SPR,
  think, false, ps_none, 0, 0, 0,
  SnakeDyingThink, NULL, R_Dying, &s_player_dead};

statetype far s_player_dead = {
  PLAYER_DYING2_SPR, PLAYER_DYING2_SPR,
  step, false, ps_none, 50, 0, 0,
  SnakeDeadThink, NULL, R_Draw, &s_player_dead};

statetype far s_player_fireball = {
  PLAYER_DYING1_SPR, PLAYER_DYING1_SPR,
  step, false, ps_tofloor, 20, 0, 0,
  NULL, SnakeContact2, R_Draw, &s_player_standing};

statetype far s_player_shielded1 = {
  PLAYER_SHIELDED1_L_SPR, PLAYER_SHIELDED1_R_SPR,
  stepthink, false, ps_tofloor, 10, 0, 0,
  SnakeStandThink, SnakeContactShielded, R_Draw, &s_player_shielded2};

statetype far s_player_shielded2 = {
  PLAYER_SHIELDED2_L_SPR, PLAYER_SHIELDED2_R_SPR,
  stepthink, false, ps_tofloor, 10, 0, 0,
  SnakeStandThink, SnakeContactShielded, R_Draw, &s_player_shielded1};

statetype far s_player_unused = {
  PLAYER_DYING1_SPR, PLAYER_DYING1_SPR,
  step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_player_standing};

statetype far s_player_standing = {
  PLAYER_STANDING_L_SPR, PLAYER_STANDING_R_SPR,
  stepthink, false, ps_tofloor, 4, 0, 16,
  SnakeStandThink, SnakeContact2, R_OnGround, &s_player_standing};

statetype far s_player_5 = {
  PLAYER_STANDING_L_SPR, PLAYER_STANDING_R_SPR,
  step, false, ps_tofloor, 1, 0, 0,
  SnakeInteractThink, NULL, R_OnGround, &s_player_standing};

statetype far s_player_6 = {
  PLAYER_STANDING_L_SPR, PLAYER_STANDING_R_SPR,
  think, false, ps_none, 0, 0, 0,
  AlignPlayer, NULL, R_Draw, NULL};

statetype far s_player_lineup = {
  PLAYER_INTERACTING_SPR, PLAYER_INTERACTING_SPR,
  think, false, ps_none, 0, 0, 0,
  AlignPlayer, NULL, R_Draw, NULL};

statetype far s_player_enter_door1 = {
  PLAYER_INTERACTING_SPR, PLAYER_INTERACTING_SPR,
  step, false, ps_none, 9, 0, 0,
  NULL, NULL, R_Draw, &s_player_enter_door2};

statetype far s_player_enter_door2 = {
  -1, -1,
  step, false, ps_none, 1, 0, 0,
  WarpToDoorDest, NULL, R_Draw, &s_player_standing};

statetype far s_player_interact1 = {
  PLAYER_INTERACTING_SPR, PLAYER_INTERACTING_SPR,
  step, false, ps_tofloor, 8, 0, 0,
  SnakeInteractThink, NULL, R_OnGround, &s_player_interact2};

statetype far s_player_interact2 = {
  PLAYER_INTERACTING_SPR, PLAYER_INTERACTING_SPR,
  step, false, ps_tofloor, 8, 0, 0,
  NULL, NULL, R_OnGround, &s_player_standing};

statetype far s_player_opendoor1 = {
  PLAYER_INTERACTING_SPR, PLAYER_INTERACTING_SPR,
  step, false, ps_tofloor, 30, 0, 0,
  NULL, SnakeContact2, R_OnGround, &s_player_opendoor2};

statetype far s_player_opendoor2 = {
  PLAYER_INTERACTING_SPR, PLAYER_INTERACTING_SPR,
  step, false, ps_tofloor, 1, 0, 0,
  OpenDoor, SnakeContact2, R_OnGround, &s_player_standing};

statetype far s_player_crouching = {
  PLAYER_CROUCH_L_SPR, PLAYER_CROUCH_R_SPR,
  stepthink, false, ps_tofloor, 4, 0, 16,
  SnakeStandThink, SnakeContact2, R_OnGround, &s_player_crouching};

statetype far s_player_place_mine = {
  PLAYER_CROUCH_L_SPR, PLAYER_CROUCH_R_SPR,
  step, false, ps_tofloor, 30, 0, 0,
  SnakeThrow, NULL, R_Draw, &s_player_standing};

statetype far s_player_climbing_idle = {
  PLAYER_CLIMBING1_SPR, PLAYER_CLIMBING1_SPR,
  think, false, ps_none, 0, 0, 0,
  SnakeClimbIdleThink, SnakeContact2, R_Draw, &s_player_climbing_idle};

statetype far s_player_climbing1 = {
  PLAYER_CLIMBING1_SPR, PLAYER_CLIMBING1_SPR,
  slidethink, false, ps_none, 8, 0, 16,
  SnakeClimbThink, SnakeContact2, R_Draw, &s_player_climbing2};

statetype far s_player_climbing2 = {
  PLAYER_CLIMBING2_SPR, PLAYER_CLIMBING2_SPR,
  slidethink, false, ps_none, 8, 0, 16,
  SnakeClimbThink, SnakeContact2, R_Draw, &s_player_climbing1};

//seg58
statetype far s_player_walking1 = {
  PLAYER_WALKING1_L_SPR, PLAYER_WALKING1_R_SPR,
  slidethink, true, ps_tofloor, 6, 24, 0,
  SnakeWalkThink, SnakeContact2, R_Walking, &s_player_walking2};

statetype far s_player_walking2 = {
  PLAYER_WALKING2_L_SPR, PLAYER_WALKING2_R_SPR,
  slidethink, true, ps_tofloor, 6, 24, 0,
  SnakeWalkThink, SnakeContact2, R_Walking, &s_player_walking3};

statetype far s_player_walking3 = {
  PLAYER_WALKING3_L_SPR, PLAYER_WALKING3_R_SPR,
  slidethink, true, ps_tofloor, 6, 24, 0,
  SnakeWalkThink, SnakeContact2, R_Walking, &s_player_walking4};

statetype far s_player_walking4 = {
  PLAYER_WALKING4_L_SPR, PLAYER_WALKING4_R_SPR,
  slidethink, true, ps_tofloor, 6, 24, 0,
  SnakeWalkThink, SnakeContact2, R_Walking, &s_player_walking1};

//seg62
statetype far s_player_throwing_grenade1 = {
  PLAYER_THROW1_L_SPR, PLAYER_THROW1_R_SPR,
  step, true, ps_tofloor, 20, 0, 0,
  NULL, SnakeContact2, R_OnGround, &s_player_throwing_grenade2};

statetype far s_player_throwing_grenade2 = {
  PLAYER_THROW2_L_SPR, PLAYER_THROW2_R_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  SnakeThrow, SnakeContact2, R_OnGround, &s_player_throwing_grenade3};

statetype far s_player_throwing_grenade3 = {
  PLAYER_THROW1_L_SPR, PLAYER_THROW1_R_SPR,
  step, true, ps_tofloor, 6, 0, 0,
  NULL, SnakeContact2, R_OnGround, &s_player_standing};

statetype far s_player_throwing_grenade_air1 = {
  PLAYER_IN_AIR_THROW1_L_SPR, PLAYER_IN_AIR_THROW1_R_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, SnakeContact, R_PlayerInAir, &s_player_throwing_grenade_air2};

statetype far s_player_throwing_grenade_air2 = {
  PLAYER_IN_AIR_THROW2_L_SPR, PLAYER_IN_AIR_THROW2_R_SPR,
  step, false, ps_none, 3, 0, 0,
  SnakeThrow, SnakeContact, R_PlayerInAir, &s_player_throwing_grenade_air3};

statetype far s_player_throwing_grenade_air3 = {
  PLAYER_IN_AIR_THROW1_L_SPR, PLAYER_IN_AIR_THROW1_R_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, SnakeContact, R_PlayerInAir, &s_player_in_air1};

//68
statetype far s_player_in_air1 = {
  PLAYER_IN_AIR_L_SPR, PLAYER_IN_AIR_R_SPR,
  think, false, ps_none, 0, 0, 0,
  SnakeAirThink, SnakeContact, R_PlayerInAir, &s_player_in_air2};

statetype far s_player_in_air2 = {
  PLAYER_IN_AIR_L_SPR, PLAYER_IN_AIR_R_SPR,
  think, false, ps_none, 0, 0, 0,
  SnakeAirThink, SnakeContact, R_PlayerInAir, &s_player_in_air3};

statetype far s_player_in_air3 = {
  PLAYER_IN_AIR_L_SPR, PLAYER_IN_AIR_R_SPR,
  think, false, ps_none, 0, 0, 0,
  SnakeAirThink, SnakeContact, R_PlayerInAir, &s_player_standing};

statetype far s_player_shoot_single1 = {
  PLAYER_SHOOT1_L_SPR, PLAYER_SHOOT1_R_SPR,
  step, false, ps_tofloor, 5, 0, 0,
  SnakeShootSingleThink, SnakeContact2, R_Draw, &s_player_shoot_single2};

statetype far s_player_shoot_single2 = {
  PLAYER_SHOOT2_L_SPR, PLAYER_SHOOT2_R_SPR,
  step, false, ps_tofloor, 5, 0, 0,
  SnakeShootSingleThink2, SnakeContact2, R_Draw, &s_player_shoot_single3};

statetype far s_player_shoot_single3 = {
  PLAYER_SHOOT1_L_SPR, PLAYER_SHOOT1_R_SPR,
  step, false, ps_tofloor, 5, 0, 0,
  NULL, SnakeContact2, R_Draw, &s_player_standing};

statetype far s_player_shoot_single_air1 = {
  PLAYER_IN_AIR_L_SPR, PLAYER_IN_AIR_R_SPR,
  stepthink, false, ps_none, 9, 0, 0,
  SnakeAirThink, SnakeContact, R_PlayerInAir, &s_player_shoot_single_air2};

statetype far s_player_shoot_single_air2 = {
  PLAYER_IN_AIR_SHOOT_L_SPR, PLAYER_IN_AIR_SHOOT_R_SPR,
  step, false, ps_none, 1, 0, 0,
  SnakeShootSingleThink2, SnakeContact, R_PlayerInAir, &s_player_shoot_single_air3};

statetype far s_player_shoot_single_air3 = {
  PLAYER_IN_AIR_L_SPR, PLAYER_IN_AIR_R_SPR,
  stepthink, false, ps_none, 5, 0, 0,
  SnakeAirThink, SnakeContact, R_PlayerInAir, &s_player_in_air1};

statetype far s_player_shoot_single_crouch1 = {
  PLAYER_CROUCH_L_SPR, PLAYER_CROUCH_R_SPR,
  step, false, ps_tofloor, 5, 0, 0,
  SnakeShootSingleThink, SnakeContact2, R_Draw, &s_player_shoot_single_crouch2};

statetype far s_player_shoot_single_crouch2 = {
  PLAYER_CROUCH_SHOOT_L_SPR, PLAYER_CROUCH_SHOOT_R_SPR,
  step, false, ps_tofloor, 5, 0, 0,
  SnakeShootSingleCrouchThink, SnakeContact2, R_Draw, &s_player_shoot_single_crouch3};

statetype far s_player_shoot_single_crouch3 = {
  PLAYER_CROUCH_L_SPR, PLAYER_CROUCH_R_SPR,
  step, false, ps_tofloor, 5, 0, 0,
  NULL, SnakeContact2, R_Draw, &s_player_crouching};

//seg80
statetype far s_player_shoot1 = {
  PLAYER_SHOOT1_L_SPR, PLAYER_SHOOT1_R_SPR,
  step, false, ps_tofloor, 2, 0, 0,
  NULL, SnakeContact, R_Draw, &s_player_shoot2};

statetype far s_player_shoot2 = {
  PLAYER_SHOOT2_L_SPR, PLAYER_SHOOT2_R_SPR,
  step, false, ps_tofloor, 2, 0, 0,
  SnakeShootThink, SnakeContact, R_Draw, &s_player_shoot1};

statetype far s_player_shoot_crouch1 = {
  PLAYER_CROUCH_L_SPR, PLAYER_CROUCH_R_SPR,
  step, false, ps_tofloor, 2, 0, 0,
  NULL, SnakeContact, R_Draw, &s_player_shoot_crouch2};

statetype far s_player_shoot_crouch2 = {
  PLAYER_CROUCH_SHOOT_L_SPR, PLAYER_CROUCH_SHOOT_R_SPR,
  step, false, ps_tofloor, 2, 0, 0,
  SnakeShootCrouchThink, SnakeContact, R_Draw, &s_player_shoot_crouch1};

statetype far s_player_shoot_air1 = {
  PLAYER_IN_AIR_L_SPR, PLAYER_IN_AIR_R_SPR,
  stepthink, false, ps_none, 3, 0, 0,
  SnakeShootAirThink, SnakeContact, R_PlayerInAir, &s_player_shoot_air2};

statetype far s_player_shoot_air2 = {
  PLAYER_IN_AIR_SHOOT_L_SPR, PLAYER_IN_AIR_SHOOT_R_SPR,
  step, false, ps_none, 1, 0, 0,
  SnakeShootAirThink2, SnakeContact, R_PlayerInAir, &s_player_shoot_air1};

// seg86


//seg197
statetype far s_seg197 = {
  // TODO
  348, 350,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, NULL, &s_seg197};


void SpawnPlayer(Sint16 x, Sint16 y, Sint16 xdir)
{
  player->obclass = playerobj;
  player->active = ac_yes;
  player->needtoclip = cl_midclip;
  playerrestorex = player->x = CONVERT_TILE_TO_GLOBAL(x);
  playerrestorey = player->y = CONVERT_TILE_TO_GLOBAL(y) - 384;
  player->xdir = xdir;
  player->ydir = 1;

  if (gamestate.mapon == 0 || word_391C2 == 1)
  {
    word_391C2 = 0;

    switch (gamestate.difficulty)
    {
      case gd_Easy:
        player->health = 8;
        break;

      case gd_Normal:
        player->health = 4;
        break;

      case gd_Hard:
        player->health = 4;
        break;

      default:
        player->health = 4;
        break;
    }

    gamestate.maxhealth = player->health;
  }

  player->health = gamestate.maxhealth;

  invincible = 0;
  byte_3FA6E = 0;

  NewState(player, &s_player_standing);

  if (gamestate.mapon == 12)
  {
    godmode = true;
  }
  else if (!debugok)
  {
    godmode = false;
  }
}


boolean CheckInteraction(objtype* ob)
{
  Uint16 temp;
  Uint16 intile, intile2;

  intile = tinf[INTILE +
    *(mapsegs[1] + mapbwidthtable[ob->tiletop + 1]/2 + ob->tilemidx)];

  if (
    intile == 3 || intile == 19 || intile == 18 || intile == 9 ||
    intile == 10 || intile == 11 ||  intile == 12 || intile == 23 ||
    intile == 14 || intile == 15)
  {
    temp = CONVERT_TILE_TO_GLOBAL(ob->tilemidx) - 4*PIXGLOBAL;

    if (ob->x != temp)
    {
      ob->temp1 = temp;
      ob->state = &s_player_lineup;
    }
    else
    {
      ob->state = &s_player_interact1;
    }

    upheld = true;
    return true;
  }

  if (intile == 7)
  {
    temp = CONVERT_TILE_TO_GLOBAL(ob->tilemidx) - 4*PIXGLOBAL;

    if (ob->x != temp)
    {
      ob->temp1 = temp;
      ob->state = &s_player_lineup;
    }
    else
    {
      ob->state = &s_player_enter_door1;
      ob->priority = 0;
    }

    upheld = true;
    return true;
  }

  if (intile == 4 || intile == 6 || intile == 5)
  {
    if (intile == 4)
    {
      if (gamestate.var14 <= 0)
      {
        SD_PlaySound(SND_NOKEY);
        return true;
      }

      gamestate.var14--;
    }
    else
    {
      if (gamestate.keyitems.keys == 0)
      {
        ShowHelpMessage("You don't have a key for this!\n");
        SD_PlaySound(SND_NOKEY);
        return true;
      }

      gamestate.keyitems.keys--;
    }

    ChangeState(ob, &s_player_opendoor1);
    upheld = true;
    return true;
  }

  if (intile == 8)
  {
    SD_PlaySound(17);

    if (!gamestate.specialkey)
    {
      ShowHelpMessage("You need a SPECIAL key.\n");
      SD_PlaySound(SND_NOKEY);
      return true;
    }

    gamestate.specialkey = false;
    ChangeState(ob, &s_player_opendoor1);
    upheld = true;
    return true;
  }

  if (intile == 148)
  {
    return true;
  }

  if (intile == 21 || intile == 22)
  {
    ob->state = &s_player_5;
    upheld = true;
    return true;
  }

  return false;
}


boolean CheckAttachToLadder(objtype* ob)
{
  Uint16 offset;
  Uint16 far* map;

  if (TimeCount < dword_3FA52)
  {
    dword_3FA52 = 0;
  }
  else if (TimeCount - dword_3FA52 < 19)
  {
    return false;
  }

  if (c.yaxis == -1)
  {
    map = mapsegs[1] + mapbwidthtable[(ob->top + 6*PIXGLOBAL)/TILEGLOBAL] / 2;
  }
  else
  {
    map = mapsegs[1] + mapbwidthtable[ob->tilebottom] / 2;
  }

  offset = CONVERT_GLOBAL_TO_TILE(ob->left + (ob->right - ob->left)/2);
  map += offset;

  if ((tinf[INTILE + *map] & 0x7F) == INTILE_LADDER)
  {
    xtry = CONVERT_TILE_TO_GLOBAL(offset) + -8*PIXGLOBAL - ob->x;
    ytry = c.yaxis * 32;
    ob->temp4 = offset;
    ob->needtoclip = cl_midclip;
    ob->state = &s_player_climbing1;

    return true;
  }

  return false;
}


boolean CheckJump(objtype* ob)
{
  if (c.xaxis)
  {
    ob->xdir = c.xaxis;
  }

  if (c.button0 && !button0held)
  {
    SD_PlaySound(11);

    ob->xspeed = TABLE2[c.xaxis];
    ob->yspeed = -40;
    ob->needtoclip = cl_midclip;
    word_3FA6C = 16;
    ob->state = &s_player_in_air1;
    ob->ydir = 1;
    button0held = true;
    dword_3FA52 = TimeCount;

    return true;
  }

  return false;
}


void AlignPlayer(objtype* ob)
{
  Sint16 var1;

  var1 = ob->temp2 - ob->x;

  if (var1 < 0)
  {
    xtry = xtry - tics*PIXGLOBAL;

    if (xtry > var1)
    {
      return;
    }
  }
  else if (var1 > 0)
  {
    xtry = xtry + tics*PIXGLOBAL;

    if (xtry < var1)
    {
      return;
    }
  }

  xtry = var1;
  ob->temp1 = 0;

  if (!CheckInteraction(ob))
  {
    ob->state = &s_player_standing;
  }
}


void SnakeThrow(objtype* ob)
{
  if (ob->xdir > 0)
  {
    sub_1E21D(ob->x + 24*PIXGLOBAL, ob->y, 2);
  }
  else
  {
    sub_1E21D(ob->x, ob->y, 6);
  }

  if (ob->state == &s_player_throwing_grenade2 ||
      ob->state == &s_player_place_mine)
  {
    return;
  }

  if (ob->state == &s_player_throwing_grenade_air2)
  {
    new->xspeed += ob->xspeed / 2;
    new->yspeed += ob->yspeed / 2;
    return;
  }

  Quit("SnakeThrow: Bad state!");
}


void WarpToDoorDest(objtype* ob)
{
  Uint16 tile;
  Uint16 far* map;

  if (word_391BE) return;

  word_391BE = true;

  map = mapsegs[2] + mapbwidthtable[ob->tilebottom] / 2 + ob->tileleft;
  tile = *map;

  ob->y = CONVERT_TILE_TO_GLOBAL(tile & 0xFF) - 16*PIXGLOBAL + 143;
  ob->x = CONVERT_TILE_TO_GLOBAL(tile >> 8);

  ob->priority = 1;
  ob->needtoclip = cl_noclip;
  ChangeState(ob, ob->state->nextstate);

  ob->needtoclip = cl_midclip;
  CenterActor(ob);
  ytry = 15;
}


void SnakeInteractThink(objtype* ob)
{
  Uint16 intile, maptile, newtile, info, sx, sy, tileoff;
  Uint16 far *map;
  Uint16 tile, x, y;
  Sint8 manim;
  objtype* otherobj;

  tileoff = mapbwidthtable[ob->tiletop + 1]/2 + ob->tilemidx;
  maptile = mapsegs[1][tileoff];
  newtile = maptile + (Sint8)tinf[MANIM + maptile];
  info = mapsegs[2][tileoff];
  sx = info >> 8;
  sy = info & 0xFF;
  intile = tinf[INTILE + maptile];

  switch (intile)
  {
    case 18:
    case 19:
    case 23:
      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      SD_PlaySound(SND_USESWITCH);
      break;

    case 3:
      if (gamestate.keyitems.keycards == 0)
      {
        ShowHelpMessage("You don't have a key for this!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      gamestate.keyitems.keycards--;
      SD_PlaySound(SND_USEKEYCARD);
      break;

    case 9:
      if (!gamestate.blueshard)
      {
        ShowHelpMessage("You don't have the right shard!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      gamestate.blueshard = false;
      SD_PlaySound(SND_USESHARD);
      break;

    case 10:
      if (!gamestate.greenshard)
      {
        ShowHelpMessage("You don't have the right shard!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      gamestate.greenshard = false;
      SD_PlaySound(SND_USESHARD);
      break;

    case 11:
      if (!gamestate.redshard)
      {
        ShowHelpMessage("You don't have the right shard!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      gamestate.redshard = false;
      SD_PlaySound(SND_USESHARD);
      break;

    case 12:
      if (!gamestate.cyanshard)
      {
        ShowHelpMessage("You don't have the right shard!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      gamestate.cyanshard = false;
      SD_PlaySound(SND_USESHARD);
      break;

    case 15:
      if (!gamestate.exitkey)
      {
        ShowHelpMessage("You must rescue the hostage first!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      gamestate.exitkey = false;
      SD_PlaySound(SND_USESHARD);
      break;

    case 14:
      if (gamestate.nukestate != ns_collected)
      {
        ShowHelpMessage("You don't have a nuclear bomb!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      SD_PlaySound(SND_24);
      gamestate.nukestate = ns_placed;

      VW_FixRefreshBuffer();
      US_CenterWindow(35, 3);
      PrintY += 2;
      US_CPrint(
        "The bomb is in place and activated!\n"
        " Now you must leave before it explodes!\n");
      VW_UpdateScreen();
      VW_WaitVBL(60);
      IN_ClearKeysDown();
      IN_Ack();
      RF_ForceRefresh();
      break;

    case 21:
      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      if (word_391C0)
      {
        return;
      }

      for (otherobj = player->next; otherobj; otherobj = otherobj->next)
      {
        if (otherobj->obclass == 13)
        {
          goto found;
        }
      }
      return;

found:
      SD_PlaySound(SND_24);
      BossDialog();

      if (gamestate.mapon != 11)
      {
        for (otherobj = player->next; otherobj; otherobj = otherobj->next)
        {
          if (otherobj->obclass == 13)
          {
            RemoveObj(otherobj);
            return;
          }
        }
      }
      else
      {
        for (otherobj = player->next; otherobj; otherobj = otherobj->next)
        {
          if (otherobj->obclass == 13)
          {
            otherobj->state = &s_seg197;
            otherobj->var1 = true;
            word_391C0 = true;
            return;
          }
        }
      }
      break;

    case 22:
      if (word_391BC == 3)
      {
        return;
      }

      if (word_391BC != 0 && !Keyboard[sc_UpArrow])
      {
        return;
      }

      word_391BC = 1;
      ShowCompatibilityInfoMessage();
      break;

    default:
      return;
  }

  if (intile == 18 || intile == 10)
  {
    if (!gamestate.var37 && intile == 18)
    {
      ShowHelpMessage("This switch activates a bridge.\n");
      gamestate.var37 = true;
    }

    for (y = sy; sy+1 > y; y++)
    {
      map = mapsegs[1] + mapbwidthtable[y]/2 + sx - (y != sy);
      for (x = sx - (y != sy); x < mapwidth; x++)
      {
        tile = *(map++);
        manim = tinf[MANIM + tile];
        if (!manim)
          break;

        tile += manim;

        if (tinf[INTILE + tile] == 144)
          tile = 0;

        RF_MemToMap(&tile, 1, x, y, 1, 1);
      }
    }

    return;
  }

  if (intile == 3 || intile == 9 || intile == 12 || intile == 15)
  {
    for (y = sy; y < mapheight; y++)
    {
      map = mapsegs[1] + mapbwidthtable[y]/2 + sx;
      tile = *map;
      manim = tinf[MANIM + tile];

      if (!manim)
        break;

      tile = 0;

      RF_MemToMap(&tile, 1, sx, y, 1, 1);
    }

    if (gamestate.mapon == 10 && (intile == 9 || intile == 12))
    {
      info = *(mapsegs[2] + mapbwidthtable[sy-1] / 2 + sx);
      x = info >> 8;
      y = info & 0xFF;

      RF_MapToMap(x, y, sx-1, sy-5, 3, 2);
    }

    return;
  }

  if (intile == 19 || intile == 11)
  {
    if (!gamestate.var38 && intile == 19)
    {
      ShowHelpMessage("This switch activates a platform.\n");
      gamestate.var38 = true;
    }

    map = mapsegs[2] + mapbwidthtable[sy]/2 + sx;
    tile = *map;

    if (tile >= DIRARROWSTART && tile < DIRARROWEND)
    {
      *map = arrowflip[tile - DIRARROWSTART] + DIRARROWSTART;
      return;
    }
    else
    {
      *map = tile ^ PLATFORMBLOCK;
    }

    return;
  }

  if (intile == 23)
  {
    if (!gamestate.var39)
    {
      ShowHelpMessage("Find the color sequence in this level.\n");
      gamestate.var39 = true;
    }

    map = mapsegs[2] + mapbwidthtable[sy]/2 + sx;
    tile = *map;

    word_3FA66++;

    if (sx - word_3FA66 == 0 && word_3FA66 != 5)
    {
      return;
    }
    else
    {
      if (word_3FA66 == 5)
      {
        tileoff = mapbwidthtable[ob->tilebottom]/2 + ob->tilemidx;
        info = mapsegs[2][tileoff];
        sx = info >> 8;
        sy = info & 0xFF;
      }
      else
      {
        tileoff = mapbwidthtable[ob->tiletop]/2 + ob->tilemidx;
        info = mapsegs[2][tileoff];
        sx = info >> 8;
        sy = info & 0xFF;

        word_3FA66 = 0;
      }

      for (y = sy; y < sy + 1; y++)
      {
        map = mapsegs[1] + mapbwidthtable[y]/2 + sx - (y != sy);
        for (x = sx - (y != sy); x < mapwidth; x++)
        {
          tile = *(map++);
          manim = tinf[MANIM + tile];
          if (!manim)
            continue;

          tile += manim;
          RF_MemToMap(&tile, 1, x, y, 1, 1);
        }
      }
    }

    return;
  }
}


void OpenDoor(objtype* ob)
{
  Uint16 x;
  Uint16 y;
  Uint16 info;

  (void)ob;

  if (doorx <= 0 || doory <= 0)
    return;

  if (*(mapsegs[1] + mapbwidthtable[doory] / 2 + doorx) == 0)
    return;

  SD_PlaySound(19);

  info = *(mapsegs[2] + mapbwidthtable[doory] / 2 + doorx);
  x = info >> 8;
  y = info & 0xFF;
  RF_MapToMap(x, y, doorx - 1, doory - 1, 2, 3);

  info = *(mapsegs[2] + mapbwidthtable[doory] / 2 + doorx);
  x = info >> 8;
  y = info & 0xFF;

  if (x == 1 && y != 0)
  {
    sub_21473(doorx, doory - 1, y);
  }

  doorx = 0;
  doory = 0;
}


void SnakeShootSingleThink2(objtype* ob)
{
  if (gamestate.difficulty == gd_Easy && gamestate.ammotype == 0)
  {
    gamestate.rapidfire = 1;
    gamestate.ammoinclip = 3;

    if (!ob->hitnorth)
    {
      ChangeState(player, &s_player_shoot_air1);
    }
    else
    {
      ChangeState(player, &s_player_shoot1);
    }
  }
  else if (ob->xdir == 1)
  {
    sub_1D51D(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    sub_1D51D(ob->left, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
}


void SnakeShootSingleCrouchThink(objtype* ob)
{
  if (gamestate.difficulty == gd_Easy && gamestate.ammotype == 0)
  {
    gamestate.rapidfire = 1;
    gamestate.ammoinclip = 3;

    ChangeState(player, &s_player_shoot_crouch1);
  }
  else if (ob->xdir == 1)
  {
    sub_1D51D(ob->right, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    sub_1D51D(ob->left, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
  }
}


void SnakeShootThink(objtype* ob)
{
  if (gamestate.ammoinclip <= 0)
  {
    ChangeState(player, &s_player_standing);

    if (gamestate.difficulty == gd_Easy)
    {
      gamestate.ammoinclip = 3;
    }

    return;
  }

  if (c.xaxis != 0)
  {
    ob->xdir = c.xaxis;
  }

  if (!button1held)
  {
    ChangeState(player, &s_player_standing);
  }
  else
  {
    if (c.button0 && !button0held)
    {
      if (word_391BA)
      {
        word_391BA = false;
      }

      ob->xspeed = 0;
      ob->yspeed = -41;
      xtry = 0;
      ytry = 0;
      word_3FA6C = 16;
      ob->state = &s_player_shoot_air2;
      button0held = true;
      gamestate.riding = NULL;
      return;
    }
    else if (c.yaxis == 1)
    {
      ChangeState(player, &s_player_shoot_crouch2);
    }
  }

  if (ob->xdir == 1)
  {
    sub_1D51D(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    sub_1D51D(ob->left, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
}


void SnakeShootAirThink2(objtype* ob)
{
  if (gamestate.ammoinclip <= 0)
  {
    ChangeState(player, &s_player_in_air1);

    if (gamestate.difficulty == gd_Easy)
    {
      gamestate.ammoinclip = 3;
    }

    return;
  }

  if (!button1held)
  {
    ChangeState(player, &s_player_in_air1);
  }

  if (ob->xdir == 1)
  {
    sub_1D51D(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    sub_1D51D(ob->left, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
}


void SnakeShootCrouchThink(objtype* ob)
{
  if (gamestate.ammoinclip <= 0)
  {
    ChangeState(player, &s_player_crouching);

    if (gamestate.difficulty == gd_Easy)
    {
      gamestate.ammoinclip = 3;
    }

    return;
  }

  if (!button1held)
  {
    ChangeState(player, &s_player_crouching);
  }
  else
  {
    if (c.button0 && !button0held)
    {
      if (word_391BA)
      {
        word_391BA = false;
      }

      ob->xspeed = 0;
      ob->yspeed = -41;
      xtry = 0;
      ytry = 0;
      word_3FA6C = 16;
      ob->state = &s_player_shoot_air2;
      button0held = true;
      gamestate.riding = NULL;
      return;
    }
    else if (c.yaxis != 1)
    {
      ChangeState(player, &s_player_shoot2);
    }
  }

  if (c.xaxis != 0)
  {
    ob->xdir = c.xaxis;
  }

  if (ob->xdir == 1)
  {
    sub_1D51D(ob->right, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    sub_1D51D(ob->left, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
  }
}


void SnakeShootAirThink(objtype* ob)
{
  if (word_3FA6C)
  {
    if (word_3FA6C < tics)
    {
      ytry = ob->yspeed * word_3FA6C;
      word_3FA6C = 0;
    }
    else
    {
      ytry = ob->yspeed * tics;
    }

    if (!word_3FA2A)
    {
      word_3FA6C = word_3FA6C - tics;
    }

    if (!c.button0)
    {
      word_3FA6C = 0;
    }
  }
  else
  {
    DoGravity(ob);
  }

  if (c.xaxis != 0)
  {
    ob->xdir = c.xaxis;
    AccelerateX(ob, c.xaxis * 2, 24);
  }
  else
  {
    FrictionX(ob);
  }
}


void PollControls(void)
{
  upbutton = downbutton = leftbutton = rightbutton = false;

  IN_ReadControl(0, &c);

  if (c.xaxis == -1) leftbutton = true;
  if (c.xaxis ==  1) rightbutton = true;
  if (c.yaxis == -1) upbutton = true;
  if (c.yaxis ==  1) downbutton = true;

  button0 = c.button0;
  button1 = c.button1;

  if (DemoMode != demo_Playback)
  {
    firebutton = Keyboard[firescan];
  }

  if (!upbutton) upheld = false;
  if (!button0) button0held = false;
  if (!button1) button1held = false;
  if (!firebutton) fireheld = false;
}


void sub_1ACA4(objtype* ob)
{
  word_391BA = 0;
  SD_PlaySound(11);
  ob->xspeed = 0;
  ob->yspeed = -41;
  xtry = 0;
  ytry = 0;
  word_3FA6C = 16;
  button0held = true;
  gamestate.riding = NULL;
  ob->state = &s_player_in_air1;
}


void DamagePlayer(objtype* ob, Sint16 damage)
{
  if (godmode) return;

  if (gamestate.hasrobopal)
  {
    gamestate.hasrobopal = false;
  }

  if (player->state == &s_player_dying || player->state == &s_player_dead)
  {
    return;
  }

  ob->health = ob->health - damage;
  if (ob->health < 0)
  {
    ob->health = 0;
  }

  if (ob->health <= 0)
  {
    sub_1D7E4(ob, ob->x, ob->y, 0);
    sub_1D7E4(ob, ob->x, ob->y, 4);
    sub_1D7E4(ob, ob->x, ob->y, 2);
    sub_1D7E4(ob, ob->x, ob->y, 6);
    KillPlayer();
  }
  else
  {
    invincible = 50;
    SD_PlaySound(1);
  }
}


void SnakeDyingThink(objtype* ob)
{
  if (word_3FA6C)
  {
    if (word_3FA6C < tics)
    {
      ytry = ob->yspeed * word_3FA6C;
      word_3FA6C = 0;
    }
    else
    {
      ytry = ob->yspeed * tics;
      word_3FA6C = word_3FA6C - tics;
    }
  }
  else
  {
    DoGravity(ob);
  }
}


void SnakeDeadThink(objtype* ob)
{
  (void)ob;
  playstate = ex_died;
}


void SnakeContactShielded(objtype* ob, objtype* hit)
{
  if (hit->var1 && !hit->dmgflash && hit->obclass != 21 && hit->obclass != 27)
  {
    sub_1D2B5(hit, 5);
    SD_PlaySound(7);
    hit->dmgflash = 25;
  }

  ob++;     // shut up compiler
}


void SnakeStandThink(objtype* ob)
{
  Sint16 startwalking;
  Sint16 i;

  if (word_391BE)
  {
    word_391BE = false;
  }

  if (word_391CA > 0)
  {
    SD_PlaySound(26);
    ob->obclass = 5;

    word_391CA--;
    if (word_391CA <= 0)
    {
      ChangeState(ob, &s_player_standing);
      ob->obclass = playerobj;
    }
    else
    {
      return;
    }
  }

  startwalking = false;

  if (leftbutton)
  {
    if (ob->xdir == -1)
    {
      startwalking = true;
    }
    else
    {
      word_391C4++;
      word_391C6 = 0;
      word_391C8 = 10;
      ob->xdir = -1;
    }
  }

  if (rightbutton)
  {
    if (ob->xdir == 1)
    {
      startwalking = true;
    }
    else
    {
      word_391C4++;
      word_391C6 = 0;
      word_391C8 = 10;
      ob->xdir = 1;
    }
  }

  if (upbutton && !upheld)
  {
    word_391C6++;
    if (word_391C6 >= 75)
    {
      SD_PlaySound(26);
      word_391C6 = 75;
    }

    word_391C4 = 0;
    word_391C8 = 3;

    if (button0 && !button0held)
    {
      word_391C8 = 25;
    }
  }

  if (downbutton && word_391C6 >= 35)
  {
    // Invincibility
    invincible = 99;
    word_391C8 = 0;
    word_391C6 = 0;
  }

  if (word_391C8 <= 0)
  {
    word_391C4 = 0;
    word_391C6 = 0;
    word_391C8 = 0;
  }

  if (firebutton && !fireheld)
  {
    fireheld = true;

    if (firebutton)
    {
      if (gamestate.explosives.landmines > 0)
      {
        if (!gamestate.riding)
        {
          ob->state = &s_player_place_mine;
        }
      }
      else
      {
        ob->state = &s_player_throwing_grenade1;
      }

      return;
    }
  }

  if (button0 && !button0held && button1 && !button1held)
  {
    word_391C6 = 0;
    sub_1ACA4(ob);

    if (startwalking)
    {
      ob->xspeed = ob->xdir * 16;
    }

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == 1)
    {
      ob->state = &s_player_shoot_air1;
    }
    else
    {
      ob->state = &s_player_shoot_single_air1;
    }

    return;
  }

  if (button1 && !button1held)
  {
    button1held = true;

    if (word_391C4 >= 5)
    {
      // Fireball Weapon
      for (i = 0; i < 3; i++)
      {
        sub_1DD25(ob->midx, ob->y + 8*PIXGLOBAL, 22);
        sub_1DD25(ob->midx, ob->y + 8*PIXGLOBAL, 26);
        SD_PlaySound(21);
      }

      ChangeState(ob, &s_player_fireball);
      word_391C8 = 0;
      word_391C4 = 0;
      return;
    }

    if (word_391C6 >= 75)
    {
      // Super Plasma Bolt
      if (ob->xdir == 1)
      {
        sub_1EA04(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir);
      }
      else
      {
        sub_1EA04(ob->left - 48*PIXGLOBAL, ob->y + 12*PIXGLOBAL, ob->xdir);
      }

      DamagePlayer(ob, 1);
      word_391C8 = 0;
      word_391C6 = 0;
      return;
    }
    else
    {
      word_391C6 = 0;
    }

    if (downbutton)
    {
      if (gamestate.ammoinclip > 0 && gamestate.rapidfire == 1)
      {
        ob->state = &s_player_shoot_crouch1;
      }
      else
      {
        ob->state = &s_player_shoot_single_crouch1;
      }

      return;
    }

    if (upbutton)
    {
      if (gamestate.explosives.landmines > 0)
      {
        if (!gamestate.riding)
        {
          ob->state = &s_player_place_mine;
        }
      }
      else
      {
        ob->state = &s_player_throwing_grenade1;
      }

      return;
    }

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == 1)
    {
      ob->state = &s_player_shoot1;
    }
    else
    {
      ob->state = &s_player_shoot_single1;
    }

    return;
  }

  if (button0 && !button0held)
  {
    if (word_391C4 >= 5)
    {
      // Personal Shield
      ChangeState(ob, &s_player_shielded1);
      word_391C8 = 0;
      word_391CA = 45;
      word_391C4 = 0;
      return;
    }

    word_391C6 = 0;
    sub_1ACA4(ob);

    if (startwalking)
    {
      ob->xspeed = ob->xdir * 16;
    }

    return;
  }

  if (upbutton && CheckAttachToLadder(ob))
  {
    return;
  }

  if (upbutton && !upheld && CheckInteraction(ob))
  {
    upheld = true;
    return;
  }

  if (startwalking)
  {
    word_391C6 = 0;
    ob->state = &s_player_walking1;
    xtry = ob->xdir * 16;
    return;
  }

  if (downbutton)
  {
    word_391C6 = 0;

    if (CheckAttachToLadder(ob))
    {
    }
    else
    {
      ob->state = &s_player_crouching;
    }
  }
  else
  {
    ob->state = &s_player_standing;
  }
}


void SnakeWalkThink(objtype* ob)
{
  Sint16 startwalking;

  if (word_391BE)
  {
    word_391BE = false;
  }

  startwalking = false;

  if (leftbutton)
  {
    startwalking = true;
    ob->xdir = -1;
  }

  if (rightbutton)
  {
    startwalking = true;
    ob->xdir = 1;
  }

  if (firebutton && !fireheld)
  {
    fireheld = true;

    if (firebutton)
    {
      if (gamestate.explosives.landmines > 0)
      {
        if (!gamestate.riding)
        {
          ob->state = &s_player_place_mine;
        }
      }
      else
      {
        ob->state = &s_player_throwing_grenade1;
      }

      return;
    }
  }

  if (button0 && !button0held && button1 && !button1held)
  {
    sub_1ACA4(ob);

    ob->xspeed = ob->xdir * 16;

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == 1)
    {
      ob->state = &s_player_shoot_air1;
    }
    else
    {
      ob->state = &s_player_shoot_single_air1;
    }

    return;
  }

  if (button1 && !button1held)
  {
    button1held = true;

    if (downbutton)
    {
      if (gamestate.ammoinclip > 0 && gamestate.rapidfire == 1)
      {
        ob->state = &s_player_shoot_crouch1;
      }
      else
      {
        ob->state = &s_player_shoot_single_crouch1;
      }

      return;
    }

    if (upbutton)
    {
      if (gamestate.explosives.landmines > 0)
      {
        if (!gamestate.riding)
        {
          ob->state = &s_player_place_mine;
        }
      }
      else
      {
        ob->state = &s_player_throwing_grenade1;
      }

      return;
    }

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == 1)
    {
      ob->state = &s_player_shoot1;
    }
    else
    {
      ob->state = &s_player_shoot_single1;
    }

    return;
  }

  if (button0 && !button0held)
  {
    sub_1ACA4(ob);

    if (startwalking)
    {
      ob->xspeed = ob->xdir * 16;
    }

    return;
  }

  if (upbutton && !upheld && CheckInteraction(ob))
  {
    upheld = true;
    return;
  }

  if (!startwalking)
  {
    if (downbutton)
    {
      ob->state = &s_player_crouching;
    }
    else
    {
      ob->state = &s_player_standing;
    }

    return;
  }
}


void SnakeAirThink(objtype* ob)
{
  if (word_3FA6C)
  {
    if (word_3FA6C < tics)
    {
      ytry = ob->yspeed * word_3FA6C;
      word_3FA6C = 0;
    }
    else
    {
      ytry = ob->yspeed * tics;
    }

    if (!word_3FA2A)
    {
      word_3FA6C = word_3FA6C - tics;
    }

    if (!c.button0)
    {
      word_3FA6C = 0;
    }

    if (word_3FA6C == 0)
    {
      ob->temp2 = false;
      ob->state = ob->state->nextstate;
    }
  }
  else
  {
    DoGravity(ob);

    if (ob->yspeed > 0 && !ob->temp2)
    {
      ob->state = ob->state->nextstate;
      ob->temp2 = true;
    }
  }

  if (c.xaxis != 0)
  {
    ob->xdir = c.xaxis;
    AccelerateX(ob, c.xaxis * 2, 24);
  }
  else
  {
    FrictionX(ob);
  }

  if (firebutton && !fireheld)
  {
    fireheld = true;

    if (firebutton)
    {
      if (gamestate.explosives.landmines <= 0)
      {
        ob->state = &s_player_throwing_grenade_air1;
      }

      return;
    }
  }

  if (button1 && !button1held)
  {
    button1held = true;

    if (c.yaxis == -1)
    {
      if (gamestate.explosives.landmines <= 0)
      {
        ob->state = &s_player_throwing_grenade_air1;
      }
      else
      {
        return;
      }
    }
    else
    {
      if (gamestate.ammoinclip > 0 && gamestate.rapidfire == 1)
      {
        ob->state = &s_player_shoot_air1;
      }
      else
      {
        ob->state = &s_player_shoot_single_air1;
      }
    }
  }

  if (c.yaxis)
  {
    CheckAttachToLadder(ob);
  }
}


void SnakeClimbIdleThink(objtype* ob)
{
  Uint16 far* map;

  if (CheckJump(ob))
  {
    return;
  }

  map = mapsegs[1] + mapbwidthtable[ob->tiletop] / 2 + ob->temp4;

  switch (c.yaxis)
  {
    case -1:
      if ((tinf[INTILE + *map] & 0x7F) != INTILE_LADDER)
      {
        ob->state = &s_player_climbing1;
      }
      else
      {
        ob->state = &s_player_climbing2;
      }

      ob->ydir = -1;
      break;

    case 1:
      ob->state = &s_player_climbing2;
      ob->ydir = 1;
      CheckFallOffLadder(ob);
      break;
  }
}


void SnakeClimbThink(objtype* ob)
{
  Uint16 far* map;

  if (CheckJump(ob))
  {
    return;
  }

  map = mapsegs[1] + mapbwidthtable[ob->tiletop] / 2 + ob->temp4;
  if ((tinf[INTILE + *map] & 0x7F) != INTILE_LADDER && c.yaxis != 1)
  {
    ytry = 0;
    ob->state = &s_player_climbing_idle;
  }
  else
  {
    switch (c.yaxis)
    {
      case -1:
        ob->ydir = -1;
        break;

      case 0:
        ob->state = &s_player_climbing_idle;
        ob->ydir = 0;
        break;

      case 1:
        ob->ydir = 1;
        CheckFallOffLadder(ob);
        break;
    }
  }
}


void CheckFallOffLadder(objtype* ob)
{
  Uint16 far* map;

  if (CheckJump(ob))
  {
    return;
  }

  map = mapsegs[1] + mapbwidthtable[ob->tilebottom] / 2 + ob->temp4;
  if ((tinf[INTILE + *map] & 0x7F) != INTILE_LADDER)
  {
    ob->state = &s_player_in_air3;
    word_3FA6C = 0;
    ob->temp2 = 1;
    ob->xspeed = TABLE2[c.xaxis];
    ob->yspeed = 0;
    ob->needtoclip = cl_midclip;
    ob->tilebottom--;
    return;
  }
}


void SnakeShootSingleThink(objtype* ob)
{
  if (leftbutton)
  {
    ob->xdir = -1;
  }

  if (rightbutton)
  {
    ob->xdir = 1;
  }

  if (button0 && !button0held)
  {
    sub_1ACA4(ob);
    ob->state = &s_player_shoot_single_air2;
  }
  else if (downbutton)
  {
    ob->state = &s_player_shoot_single_crouch2;
  }
  else
  {
    ob->state = &s_player_shoot_single2;
  }
}


void KillPlayer(void)
{
  if (godmode) return;

  if (player->state == &s_player_dying || player->state == &s_player_dead)
  {
    return;
  }

  SD_PlaySound(5);
  gamestate.lives--;
  player->xspeed = 0;
  player->yspeed = -41;
  xtry = 0;
  ytry = 0;
  word_3FA6C = 16;
  button0held = true;
  gamestate.riding = NULL;
  word_391C2 = true;
  ChangeState(player, &s_player_dying);
}


void SnakeContact2(objtype* ob, objtype* hit)
{
  SnakeContact(ob, hit);
}


void R_OnGround(objtype* ob)
{
  if (!ob->hitnorth)
  {
    ob->xspeed = ob->xdir * 8;
    ChangeState(ob, &s_player_in_air3);
    ob->temp2 = true;
    word_3FA6C = 0;
  }

  RF_PlaceSprite(
    &ob->sprite,
    ob->x,
    ob->y,
    ob->shapenum,
    ob->dmgflash ? maskdraw : spritedraw,
    ob->priority);
}


void R_Walking(objtype* ob)
{
  if (!ob->hitnorth)
  {
    ob->xspeed = ob->xdir * 8;
    ob->yspeed = 0;
    ChangeState(ob, &s_player_in_air3);
    ob->temp2 = true;
    word_3FA6C = 0;
  }
  else if (ob->hiteast || ob->hitwest)
  {
    ChangeState(ob, &s_player_standing);
  }

  RF_PlaceSprite(
    &ob->sprite,
    ob->x,
    ob->y,
    ob->shapenum,
    ob->dmgflash ? maskdraw : spritedraw,
    ob->priority);
}


void R_PlayerInAir(objtype* ob)
{
  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed = 0;
  }

  if (ob->hitsouth)
  {
    if (ob->hitsouth > 1)
    {
      ob->yspeed += 16;

      if (ob->yspeed < 0)
      {
        ob->yspeed = 0;
      }
    }
    else
    {
      ob->yspeed = 0;
    }

    word_3FA6C = 0;
  }

  if (ob->hitnorth)
  {
    if (ob->hitnorth != 23 || !word_3FA6C)
    {
      ob->temp1 = ob->temp2 = 0;

      if (ob->state == &s_player_throwing_grenade_air1)
      {
        ChangeState(ob, &s_player_throwing_grenade1);
      }
      else if (ob->state == &s_player_throwing_grenade_air2)
      {
        ChangeState(ob, &s_player_throwing_grenade2);
      }
      else if (ob->state == &s_player_throwing_grenade_air3)
      {
        ChangeState(ob, &s_player_throwing_grenade3);
      }
      else if (ob->state == &s_player_shoot_single_air1)
      {
        ChangeState(ob, &s_player_shoot_single1);
      }
      else if (ob->state == &s_player_shoot_single_air2)
      {
        ChangeState(ob, &s_player_shoot_single2);
      }
      else if (ob->state == &s_player_shoot_single_air3)
      {
        ChangeState(ob, &s_player_shoot_single3);
      }
      else if (ob->state == &s_player_shoot_air1)
      {
        ChangeState(ob, &s_player_shoot1);
      }
      else if (ob->state == &s_player_shoot_air2)
      {
        ChangeState(ob, &s_player_shoot2);
      }
      else
      {
        ChangeState(ob, &s_player_standing);
      }
    }
  }

  RF_PlaceSprite(
    &ob->sprite,
    ob->x,
    ob->y,
    ob->shapenum,
    ob->dmgflash ? maskdraw : spritedraw,
    ob->priority);
}


void R_Dying(objtype* ob)
{
  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_player_dead);
  }

  RF_PlaceSprite(
    &ob->sprite,
    ob->x,
    ob->y,
    ob->shapenum,
    ob->dmgflash ? maskdraw : spritedraw,
    ob->priority);
}


void CheckInTiles(objtype *ob)
{
  Uint16 x, y;
  Uint16 far *map;
  Uint16 rowdelta, intile, midx;

  if (player->health <= 0) return;

  map = mapsegs[1] + mapbwidthtable[ob->tiletop]/2 + ob->tileleft;
  rowdelta = mapwidth - (ob->tileright - ob->tileleft + 1);

  for (y = ob->tiletop; y <= ob->tilebottom; y++, map += rowdelta)
  {
    for (x = ob->tileleft; x <= ob->tileright; x++, map++)
    {
      intile = tinf[INTILE + *map] & INTILE_TYPEMASK;

      if (intile != 0)
      {
        switch (intile)
        {
          case 4:
          case 5:
          case 6:
          case 8:
            if (!gamestate.var40)
            {
              ShowHelpMessage("Push <UP> to enter or open a door.\n");
              gamestate.var40 = true;
            }

            doorx = x;
            doory = y;
            break;

          case 2:
            if (ob->health > 0)
            {
              if (invincible == 0)
              {
                DamagePlayer(ob, 1);
              }
            }
            else
            {
              return;
            }
            break;

          case 16:
            if (ob->health > 0)
            {
              DamagePlayer(ob, 50);
            }
            else
            {
              return;
            }
            break;

          case 13:
            if (gamestate.radpill == true)
            {
              return;
            }

            if (ob->health > 0)
            {
              DamagePlayer(ob, 50);
            }
            else
            {
              return;
            }
            break;

          case 21:
            if (ob->hitnorth == 1)
            {
              CheckInteraction(ob);
            }
            break;

          case 22:
            if (word_391BC == 3)
            {
              return;
            }

            if (ob->hitnorth == 1 && (word_391BC == 0 || Keyboard[sc_UpArrow]))
            {
              CheckInteraction(ob);
            }
            break;

          case 25:
            if (word_399FA != -1)
            {
              word_399FA = 1;
            }
            break;
        }
      }
    }
  }
}

extern boolean nopan;


void HandleRiding(objtype *ob)
{
  objtype *plat;

  plat = gamestate.riding;
  if (ob->right < plat->left || ob->left > plat->right)
  {
    gamestate.riding = NULL;
  }
  else if (ob->ymove < 0)
  {
    gamestate.riding = NULL;
    if (plat->ymove < 0)
    {
      xtry = 0;
      ytry = plat->ymove;
      PushObj(ob);
    }
  }
  else
  {
    xtry = plat->xmove;
    ytry = plat->top - ob->bottom - 16;
    PushObj(ob);

    if (nopan)
    {
      ob->x &= ~0x7F;
      ob->x |= plat->x & 0x7F;
    }
    else
    {
      ob->x |= plat->x & 0x1F;
    }

    if (ob->hitsouth)
    {
      gamestate.riding = NULL;
    }
    else
    {
      ob->hitnorth = 23;
    }
  }
}
