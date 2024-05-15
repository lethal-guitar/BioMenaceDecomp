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

#include "BM_ACT.H"
#include "BM_DEF.H"


Uint32 leavepoletime;
Uint16 invincible;

boolean cmdup, cmddown, cmdleft, cmdright;
boolean cmdjump, cmdfire, firebutton;

Uint16 arrowflip[] = {
  arrow_South,     arrow_West,      arrow_North,     arrow_East,
  arrow_SouthWest, arrow_NorthWest, arrow_NorthEast, arrow_SouthEast
};

Sint16 unused4 = 0;
Sint16 unknown = 0;
boolean doorwarpInProgress = false;
boolean drmangleactive = false;
boolean playerdied = false;
Sint16 supermoveTurnCount = 0;
Sint16 supermoveHoldUpCount = 0;
Sint16 supermoveTimeout = 0;
Sint16 playerShieldFramesLeft = 0;

Sint16 ladderspeedx[] = { -8, 0, 8 };


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

statetype far s_player_activated_trigger = {
  PLAYER_STANDING_L_SPR, PLAYER_STANDING_R_SPR,
  step, false, ps_tofloor, 1, 0, 0,
  SnakeInteractThink, NULL, R_OnGround, &s_player_standing};

statetype far s_player_unused2 = {
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



void SpawnPlayer(Sint16 x, Sint16 y, Sint16 xdir)
{
  player->obclass = playerobj;
  player->active = ac_yes;
  player->needtoclip = cl_midclip;
  playerrestorex = player->x = CONVERT_TILE_TO_GLOBAL(x);
  playerrestorey = player->y = CONVERT_TILE_TO_GLOBAL(y) - 384;
  player->xdir = xdir;
  player->ydir = 1;

  if (gamestate.mapon == 0 || playerdied == true)
  {
    playerdied = false;

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
  unktime = 0;

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
    intile == INTILE_KEYCARD_SLOT || intile == INTILE_PLATFORM_SWITCH ||
    intile == INTILE_BRIDGE_SWITCH || intile == INTILE_SHARD_SLOT_BLUE ||
    intile == INTILE_SHARD_SLOT_GREEN || intile == INTILE_SHARD_SLOT_RED ||
    intile == INTILE_SHARD_SLOT_CYAN || intile == INTILE_COLOR_SEQ_SWITCH ||
    intile == INTILE_NUKE_SLOT || intile == INTILE_EXITKEY_SLOT)
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

  if (intile == INTILE_DOOR)
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

  if (intile == INTILE_DOORLOCK_TRIANGLE || intile == INTILE_DOORLOCK2 ||
      intile == INTILE_DOORLOCK1)
  {
    if (intile == INTILE_DOORLOCK_TRIANGLE)
    {
      if (gamestate.trianglekeys <= 0)
      {
        SD_PlaySound(SND_NOKEY);
        return true;
      }

      gamestate.trianglekeys--;
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

  if (intile == INTILE_DOORLOCK_SPECIAL)
  {
    SD_PlaySound(SND_USEKEYCARD);

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

  if (intile == (INTILE_UNKNOWN | INTILE_FOREGROUND))
  {
    return true;
  }

#if EPISODE == 1
  if (intile == INTILE_TRIGGER_BOSS || intile == INTILE_TRIGGER_UNKNOWN)
  {
    ob->state = &s_player_activated_trigger;
    upheld = true;
    return true;
  }
#elif EPISODE == 2
  if (intile == INTILE_TRIGGER_BOSS)
  {
    ob->state = &s_player_activated_trigger;
    upheld = true;
    return true;
  }

  if (intile == INTILE_TRIGGER_UNKNOWN && unknown)
  {
    ob->state = &s_player_activated_trigger;
    upheld = true;
    return true;
  }
#endif

  return false;
}


boolean CheckAttachToLadder(objtype* ob)
{
  Uint16 offset;
  Uint16 far* map;

  if (TimeCount < leavepoletime)
  {
    leavepoletime = 0;
  }
  else if (TimeCount - leavepoletime < 19)
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


boolean CheckJumpOffLadder(objtype* ob)
{
  if (c.xaxis)
  {
    ob->xdir = c.xaxis;
  }

  if (c.button0 && !button0held)
  {
    SD_PlaySound(SND_PLAYERJUMP);

    ob->xspeed = ladderspeedx[c.xaxis + 1];
    ob->yspeed = -40;
    ob->needtoclip = cl_midclip;
    jumptime = 16;
    ob->state = &s_player_in_air1;
    ob->ydir = 1;
    button0held = true;
    leavepoletime = TimeCount;

    return true;
  }

  return false;
}


void AlignPlayer(objtype* ob)
{
  Sint16 xmove;

  xmove = ob->temp1 - ob->x;

  if (xmove < 0)
  {
    xtry = xtry - tics*PIXGLOBAL;

    if (xtry > xmove)
    {
      return;
    }
  }
  else if (xmove > 0)
  {
    xtry = xtry + tics*PIXGLOBAL;

    if (xtry < xmove)
    {
      return;
    }
  }

  xtry = xmove;
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
    ThrowGrenade(ob->x + 24*PIXGLOBAL, ob->y, dir_East);
  }
  else
  {
    ThrowGrenade(ob->x, ob->y, dir_West);
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

  if (doorwarpInProgress) return;

  doorwarpInProgress = true;

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
    case INTILE_BRIDGE_SWITCH:
    case INTILE_PLATFORM_SWITCH:
    case INTILE_COLOR_SEQ_SWITCH:
      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      SD_PlaySound(SND_USESWITCH);
      break;

    case INTILE_KEYCARD_SLOT:
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

    case INTILE_SHARD_SLOT_BLUE:
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

    case INTILE_SHARD_SLOT_GREEN:
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

    case INTILE_SHARD_SLOT_RED:
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

    case INTILE_SHARD_SLOT_CYAN:
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

    case INTILE_EXITKEY_SLOT:
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

    case INTILE_NUKE_SLOT:
      if (gamestate.nukestate != ns_collected)
      {
        ShowHelpMessage("You don't have a nuclear bomb!\n");
        SD_PlaySound(SND_NOKEY);
        return;
      }

      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      SD_PlaySound(SND_DANGER);
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

    case INTILE_TRIGGER_BOSS:
      RF_MemToMap(&newtile, 1, ob->tilemidx, ob->tiletop + 1, 1, 1);
      if (drmangleactive)
      {
        return;
      }

      for (otherobj = player->next; otherobj; otherobj = otherobj->next)
      {
        if (otherobj->obclass == drmangleobj)
        {
          goto found;
        }
      }
      return;

found:
      SD_PlaySound(SND_DANGER);
      BossDialog();

      if (gamestate.mapon != 11)
      {
        for (otherobj = player->next; otherobj; otherobj = otherobj->next)
        {
          if (otherobj->obclass == drmangleobj)
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
          if (otherobj->obclass == drmangleobj)
          {
#if EPISODE == 1
            otherobj->state = &s_drmangle_monster_jumping;
#endif
            otherobj->shootable = true;
            drmangleactive = true;

#if EPISODE == 2
            otherobj->health = bosshealth = lastbosshealth = 100;
            hbardivisor = bosshealth / 20;
#endif
            return;
          }
        }
      }
      break;

    case INTILE_TRIGGER_UNKNOWN:
      if (unknown == 3)
      {
        return;
      }

      if (unknown != 0 && !Keyboard[sc_UpArrow])
      {
        return;
      }

      unknown = 1;
      ShowCompatibilityInfoMessage();
      break;

    default:
      return;
  }

  if (intile == INTILE_BRIDGE_SWITCH || intile == INTILE_SHARD_SLOT_GREEN)
  {
    if (!gamestate.helpmsgbridgeswitch && intile == INTILE_BRIDGE_SWITCH)
    {
      ShowHelpMessage("This switch activates a bridge.\n");
      gamestate.helpmsgbridgeswitch = true;
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

        if (tinf[INTILE + tile] == (INTILE_FORCEFIELD | INTILE_FOREGROUND))
          tile = 0;

        RF_MemToMap(&tile, 1, x, y, 1, 1);
      }
    }

    return;
  }

  if (intile == INTILE_KEYCARD_SLOT || intile == INTILE_SHARD_SLOT_BLUE ||
      intile == INTILE_SHARD_SLOT_CYAN || intile == INTILE_EXITKEY_SLOT)
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

#if EPISODE == 1
    // Hack for map "Computer Core": Disable the animating mouths of the
    // robot thingies on top of the force fields along with disabling
    // the force fields
    if (gamestate.mapon == 10 &&
        (intile == INTILE_SHARD_SLOT_BLUE || intile == INTILE_SHARD_SLOT_CYAN))
    {
      info = *(mapsegs[2] + mapbwidthtable[sy-1] / 2 + sx);
      x = info >> 8;
      y = info & 0xFF;

      RF_MapToMap(x, y, sx-1, sy-5, 3, 2);
    }
#endif

    return;
  }

  if (intile == INTILE_PLATFORM_SWITCH || intile == INTILE_SHARD_SLOT_RED)
  {
    if (!gamestate.helpmsgplatformswitch && intile == INTILE_PLATFORM_SWITCH)
    {
      ShowHelpMessage("This switch activates a platform.\n");
      gamestate.helpmsgplatformswitch = true;
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

  if (intile == INTILE_COLOR_SEQ_SWITCH)
  {
    if (!gamestate.helpmsgcolorseq)
    {
      ShowHelpMessage("Find the color sequence in this level.\n");
      gamestate.helpmsgcolorseq = true;
    }

    map = mapsegs[2] + mapbwidthtable[sy]/2 + sx;
    tile = *map;

    colorstep++;

    if (sx - colorstep == 0 && colorstep != 5)
    {
      return;
      return;
    }

    if (colorstep == 5)
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

      colorstep = 0;
    }

    for (y = sy; y < sy + 1; y++)
    {
      map = mapsegs[1] + mapbwidthtable[y]/2 + sx - (y != sy);
      for (x = sx - (y != sy); x < mapwidth; x++)
      {
        tile = *(map++);
        manim = tinf[MANIM + tile];
        if (!manim)
          goto nextY;

        tile += manim;
        RF_MemToMap(&tile, 1, x, y, 1, 1);
      }
nextY:;
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

  if (doordestx <= 0 || doordesty <= 0)
    return;

  if (*(mapsegs[1] + mapbwidthtable[doordesty] / 2 + doordestx) == 0)
    return;

  SD_PlaySound(SND_OPENDOOR);

  info = *(mapsegs[2] + mapbwidthtable[doordesty] / 2 + doordestx);
  x = info >> 8;
  y = info & 0xFF;
  RF_MapToMap(x, y, doordestx - 1, doordesty - 1, 2, 3);

  info = *(mapsegs[2] + mapbwidthtable[doordesty] / 2 + doordestx);
  x = info >> 8;
  y = info & 0xFF;

  if (x == 1 && y != 0)
  {
    SpawnPickup(doordestx, doordesty - 1, y);
  }

  doordestx = 0;
  doordesty = 0;
}


void SnakeShootSingleThink2(objtype* ob)
{
  if (gamestate.difficulty == gd_Easy && gamestate.ammotype == AMMO_REGULAR)
  {
    gamestate.rapidfire = true;
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
    FireBullet(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    FireBullet(ob->left, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
}


void SnakeShootSingleCrouchThink(objtype* ob)
{
  if (gamestate.difficulty == gd_Easy && gamestate.ammotype == AMMO_REGULAR)
  {
    gamestate.rapidfire = true;
    gamestate.ammoinclip = 3;

    ChangeState(player, &s_player_shoot_crouch1);
  }
  else if (ob->xdir == 1)
  {
    FireBullet(ob->right, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    FireBullet(ob->left, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
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
      if (unused4)
      {
        unused4 = false;
      }

      ob->xspeed = 0;
      ob->yspeed = -41;
      xtry = 0;
      ytry = 0;
      jumptime = 16;
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
    FireBullet(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    FireBullet(ob->left, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
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
    FireBullet(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    FireBullet(ob->left, ob->y + 12*PIXGLOBAL, ob->xdir, 1);
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
      if (unused4)
      {
        unused4 = false;
      }

      ob->xspeed = 0;
      ob->yspeed = -41;
      xtry = 0;
      ytry = 0;
      jumptime = 16;
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
    FireBullet(ob->right, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
  }
  else
  {
    FireBullet(ob->left, ob->y + 28*PIXGLOBAL, ob->xdir, 1);
  }
}


void SnakeShootAirThink(objtype* ob)
{
  if (jumptime)
  {
    if (jumptime < tics)
    {
      ytry = ob->yspeed * jumptime;
      jumptime = 0;
    }
    else
    {
      ytry = ob->yspeed * tics;

      if (!jumpcheat)
      {
        jumptime = jumptime - tics;
      }
    }

    if (!c.button0)
    {
      jumptime = 0;
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
  cmdup = cmddown = cmdleft = cmdright = false;

  IN_ReadControl(0, &c);

  if (c.xaxis == -1) cmdleft = true;
  if (c.xaxis ==  1) cmdright = true;
  if (c.yaxis == -1) cmdup = true;
  if (c.yaxis ==  1) cmddown = true;

  cmdjump = c.button0;
  cmdfire = c.button1;

  if (DemoMode != demo_Playback)
  {
    firebutton = Keyboard[firescan];
  }

  if (!cmdup) upheld = false;
  if (!cmdjump) button0held = false;
  if (!cmdfire) button1held = false;
  if (!firebutton) fireheld = false;
}


#if EPISODE == 2
// TODO: 
#endif


void Jump(objtype* ob)
{
  unused4 = 0;
  SD_PlaySound(SND_PLAYERJUMP);
  ob->xspeed = 0;
  ob->yspeed = -41;
  xtry = 0;
  ytry = 0;
  jumptime = 16;
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
    ChunkBloom(ob, ob->x, ob->y, dir_North);
    ChunkBloom(ob, ob->x, ob->y, dir_South);
    ChunkBloom(ob, ob->x, ob->y, dir_East);
    ChunkBloom(ob, ob->x, ob->y, dir_West);
    KillPlayer();
  }
  else
  {
    invincible = 50;
    SD_PlaySound(SND_TAKEDAMAGE);
  }
}


void SnakeDyingThink(objtype* ob)
{
  if (jumptime)
  {
    if (jumptime < tics)
    {
      ytry = ob->yspeed * jumptime;
      jumptime = 0;
    }
    else
    {
      ytry = ob->yspeed * tics;
      jumptime = jumptime - tics;
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
  if (hit->shootable && !hit->dmgflash && hit->obclass != pushblockobj &&
      hit->obclass != crushblockobj)
  {
    DealDamage(hit, 5);
    SD_PlaySound(SND_EXPLOSION);
    hit->dmgflash = 25;
  }

  ob++;     // shut up compiler
}


void SnakeStandThink(objtype* ob)
{
  Sint16 startwalking;
  Sint16 i;

  if (doorwarpInProgress)
  {
    doorwarpInProgress = false;
  }

  if (playerShieldFramesLeft > 0)
  {
    SD_PlaySound(SND_SPECIALMOVE);
    ob->obclass = fireballobj;

    playerShieldFramesLeft--;
    if (playerShieldFramesLeft <= 0)
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

  if (cmdleft)
  {
    if (ob->xdir == -1)
    {
      startwalking = true;
    }
    else
    {
      supermoveTurnCount++;
      supermoveHoldUpCount = 0;
      supermoveTimeout = 10;
      ob->xdir = -1;
    }
  }

  if (cmdright)
  {
    if (ob->xdir == 1)
    {
      startwalking = true;
    }
    else
    {
      supermoveTurnCount++;
      supermoveHoldUpCount = 0;
      supermoveTimeout = 10;
      ob->xdir = 1;
    }
  }

  if (cmdup && !upheld)
  {
    supermoveHoldUpCount++;
    if (supermoveHoldUpCount >= 75)
    {
      SD_PlaySound(SND_SPECIALMOVE);
      supermoveHoldUpCount = 75;
    }

    supermoveTurnCount = 0;
    supermoveTimeout = 3;

    if (cmdjump && !button0held)
    {
      supermoveTimeout = 25;
    }
  }

  if (cmddown && supermoveHoldUpCount >= 35)
  {
    // Invincibility
    invincible = 99;
    supermoveTimeout = 0;
    supermoveHoldUpCount = 0;
  }

  if (supermoveTimeout <= 0)
  {
    supermoveTurnCount = 0;
    supermoveHoldUpCount = 0;
    supermoveTimeout = 0;
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

  if (cmdjump && !button0held && cmdfire && !button1held)
  {
    supermoveHoldUpCount = 0;
    Jump(ob);

    if (startwalking)
    {
      ob->xspeed = ob->xdir * 16;
    }

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == true)
    {
      ob->state = &s_player_shoot_air1;
    }
    else
    {
      ob->state = &s_player_shoot_single_air1;
    }

    return;
  }

  if (cmdfire && !button1held)
  {
    button1held = true;

    if (supermoveTurnCount >= 5)
    {
      // Fireball Weapon
      for (i = 0; i < 3; i++)
      {
        FragBloom(ob->midx, ob->y + 8*PIXGLOBAL, dir_East + 20);
        FragBloom(ob->midx, ob->y + 8*PIXGLOBAL, dir_West + 20);
        SD_PlaySound(SND_LASERSHOT);
      }

      ChangeState(ob, &s_player_fireball);
      supermoveTimeout = 0;
      supermoveTurnCount = 0;
      return;
    }

    if (supermoveHoldUpCount >= 75)
    {
      // Super Plasma Bolt
      if (ob->xdir == 1)
      {
        SpawnSuperPlasmaBolt(ob->right, ob->y + 12*PIXGLOBAL, ob->xdir);
      }
      else
      {
        SpawnSuperPlasmaBolt(ob->left - 48*PIXGLOBAL, ob->y + 12*PIXGLOBAL, ob->xdir);
      }

      DamagePlayer(ob, 1);
      supermoveTimeout = 0;
      supermoveHoldUpCount = 0;
      return;
    }
    else
    {
      supermoveHoldUpCount = 0;
    }

    if (cmddown)
    {
      if (gamestate.ammoinclip > 0 && gamestate.rapidfire == true)
      {
        ob->state = &s_player_shoot_crouch1;
      }
      else
      {
        ob->state = &s_player_shoot_single_crouch1;
      }

      return;
    }

    if (cmdup)
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

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == true)
    {
      ob->state = &s_player_shoot1;
    }
    else
    {
      ob->state = &s_player_shoot_single1;
    }

    return;
  }

  if (cmdjump && !button0held)
  {
    if (supermoveTurnCount >= 5)
    {
      // Personal Shield
      ChangeState(ob, &s_player_shielded1);
      supermoveTimeout = 0;
      playerShieldFramesLeft = 45;
      supermoveTurnCount = 0;
      return;
    }

    supermoveHoldUpCount = 0;
    Jump(ob);

    if (startwalking)
    {
      ob->xspeed = ob->xdir * 16;
    }

    return;
  }

  if (cmdup && CheckAttachToLadder(ob))
  {
    return;
  }

  if (cmdup && !upheld && CheckInteraction(ob))
  {
    upheld = true;
    return;
  }

  if (startwalking)
  {
    supermoveHoldUpCount = 0;
    ob->state = &s_player_walking1;
    xtry = ob->xdir * 16;
    return;
  }

  if (cmddown)
  {
    supermoveHoldUpCount = 0;

    if (CheckAttachToLadder(ob))
      return;

    ob->state = &s_player_crouching;
  }
  else
  {
    ob->state = &s_player_standing;
  }
}


void SnakeWalkThink(objtype* ob)
{
  Sint16 startwalking;

  if (doorwarpInProgress)
  {
    doorwarpInProgress = false;
  }

  startwalking = false;

  if (cmdleft)
  {
    startwalking = true;
    ob->xdir = -1;
  }

  if (cmdright)
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

  if (cmdjump && !button0held && cmdfire && !button1held)
  {
    Jump(ob);

    ob->xspeed = ob->xdir * 16;

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == true)
    {
      ob->state = &s_player_shoot_air1;
    }
    else
    {
      ob->state = &s_player_shoot_single_air1;
    }

    return;
  }

  if (cmdfire && !button1held)
  {
    button1held = true;

    if (cmddown)
    {
      if (gamestate.ammoinclip > 0 && gamestate.rapidfire == true)
      {
        ob->state = &s_player_shoot_crouch1;
      }
      else
      {
        ob->state = &s_player_shoot_single_crouch1;
      }

      return;
    }

    if (cmdup)
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

    if (gamestate.ammoinclip > 0 && gamestate.rapidfire == true)
    {
      ob->state = &s_player_shoot1;
    }
    else
    {
      ob->state = &s_player_shoot_single1;
    }

    return;
  }

  if (cmdjump && !button0held)
  {
    Jump(ob);

    if (startwalking)
    {
      ob->xspeed = ob->xdir * 16;
    }

    return;
  }

  if (cmdup && !upheld && CheckInteraction(ob))
  {
    upheld = true;
    return;
  }

  if (!startwalking)
  {
    if (cmddown)
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
  if (jumptime)
  {
    if (jumptime < tics)
    {
      ytry = ob->yspeed * jumptime;
      jumptime = 0;
    }
    else
    {
      ytry = ob->yspeed * tics;

      if (!jumpcheat)
      {
        jumptime = jumptime - tics;
      }
    }

    if (!c.button0)
    {
      jumptime = 0;
    }

    if (jumptime == 0)
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

  if (cmdfire && !button1held)
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
      if (gamestate.ammoinclip > 0 && gamestate.rapidfire == true)
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

  if (CheckJumpOffLadder(ob))
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

  if (CheckJumpOffLadder(ob))
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

  if (CheckJumpOffLadder(ob))
  {
    return;
  }

  map = mapsegs[1] + mapbwidthtable[ob->tilebottom] / 2 + ob->temp4;
  if ((tinf[INTILE + *map] & 0x7F) != INTILE_LADDER)
  {
    ob->state = &s_player_in_air3;
    jumptime = 0;
    ob->temp2 = 1;
    ob->xspeed = ladderspeedx[c.xaxis + 1];
    ob->yspeed = 0;
    ob->needtoclip = cl_midclip;
    ob->tilebottom--;
    return;
  }
}


void SnakeShootSingleThink(objtype* ob)
{
  if (cmdleft)
  {
    ob->xdir = -1;
  }

  if (cmdright)
  {
    ob->xdir = 1;
  }

  if (cmdjump && !button0held)
  {
    Jump(ob);
    ob->state = &s_player_shoot_single_air2;
  }
  else if (cmddown)
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

  SD_PlaySound(SND_PLAYERDIE);
  gamestate.lives--;
  player->xspeed = 0;
  player->yspeed = -41;
  xtry = 0;
  ytry = 0;
  jumptime = 16;
  button0held = true;
  gamestate.riding = NULL;
  playerdied = true;
  ChangeState(player, &s_player_dying);
}


void SnakeContact2(objtype* ob, objtype* hit)
{
  SnakeContact(ob, hit);
}


#if EPISODE == 2
extern Sint16 bonuspoints[];

#include "contact.c"
#endif

void R_OnGround(objtype* ob)
{
  if (!ob->hitnorth)
  {
    ob->xspeed = ob->xdir * 8;
    ChangeState(ob, &s_player_in_air3);
    ob->temp2 = true;
    jumptime = 0;
  }

  PLACESPRITE;
}


void R_Walking(objtype* ob)
{
  if (!ob->hitnorth)
  {
    ob->xspeed = ob->xdir * 8;
    ob->yspeed = 0;
    ChangeState(ob, &s_player_in_air3);
    ob->temp2 = true;
    jumptime = 0;
  }
  else if (ob->hiteast || ob->hitwest)
  {
    ChangeState(ob, &s_player_standing);
  }

  PLACESPRITE;
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

    jumptime = 0;
  }

  if (ob->hitnorth)
  {
    if (ob->hitnorth != 23 || !jumptime)
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

  PLACESPRITE;
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

  PLACESPRITE;
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
          case INTILE_DOORLOCK_TRIANGLE:
          case INTILE_DOORLOCK1:
          case INTILE_DOORLOCK2:
          case INTILE_DOORLOCK_SPECIAL:
            if (!gamestate.helpmsgenterdoor)
            {
              ShowHelpMessage("Push <UP> to enter or open a door.\n");
              gamestate.helpmsgenterdoor = true;
            }

            doordestx = x;
            doordesty = y;
            break;

          case INTILE_DAMAGING:
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

          case INTILE_FORCEFIELD:
            if (ob->health > 0)
            {
              DamagePlayer(ob, 50);
            }
            else
            {
              return;
            }
            break;

          case INTILE_RADIATION:
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

          case INTILE_TRIGGER_BOSS:
            if (ob->hitnorth == 1)
            {
              CheckInteraction(ob);
            }
            break;

          case INTILE_TRIGGER_UNKNOWN:
            if (unknown == 3)
            {
              return;
            }

            if (ob->hitnorth == 1 && (unknown == 0 || Keyboard[sc_UpArrow]))
            {
              CheckInteraction(ob);
            }
            break;

          case INTILE_TRIGGER_CRUSHER:
            if (crusheractive != -1)
            {
              crusheractive = 1;
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
