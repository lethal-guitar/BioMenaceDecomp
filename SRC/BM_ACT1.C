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


Sint16 pdirx[] = {  0, 1, 0, -1,  1, 1, -1, -1 };
Sint16 pdiry[] = { -1, 0, 1,  0, -1, 1,  1, -1 };


void R_EnemyProjectile(objtype* ob);
void T_Platform(objtype* ob);
void T_GoPlat(objtype* ob);
void R_Helicopter(objtype* ob);
void T_ParachuteBot(objtype* ob);
void C_ParachuteBotAttack(objtype* ob, objtype* hit);
void R_ParachuteBot(objtype* ob);
void R_ParachuteBotAttack(objtype* ob);
void T_SpitterSnake2(objtype* ob);
void SpitterSnakeSpit(objtype* ob);
void T_SpitterSnake(objtype* ob);
void SewerMutantThrow(objtype* ob);
void T_SewerMutant(objtype* ob);
void T_DrMangleHologram(objtype* ob);
void T_DrMangleHologramAttacking(objtype* ob);
void R_DrMangleHologramAttacking(objtype* ob);
void T_DrMangle();
void DrMangleDefeated(objtype* ob);
void R_DrMangleJumping();


statetype far s_platform = { /* 32250 */
  PLATFORMSPR, PLATFORMSPR,
  think, false, ps_none, 0, 0, 0,
  T_Platform, NULL, R_Draw, NULL};

statetype far s_apogeelogo = { /* 32270 */
  APOGEELOGOSPR, APOGEELOGOSPR,
  think, false, ps_none, 0, 0, 0,
  T_Platform, NULL, R_Draw, NULL};

statetype far s_helicopter1 = { /* 32290 */
  HELICOPTER2_SPR, HELICOPTER2_SPR,
  stepthink, false, ps_none, 1, 0, 0,
  T_GoPlat, NULL, R_Helicopter, &s_helicopter1};

statetype far s_helicopter2 = { /* 322b0 */
  HELICOPTER1_SPR, HELICOPTER1_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_GoPlat, NULL, R_Helicopter, &s_helicopter1};

statetype far s_helicopter_spawnbot = { /* 322d0 */
  HELICOPTER1_SPR, HELICOPTER1_SPR,
  stepthink, false, ps_none, 1, 0, 0,
  T_GoPlat, NULL, SpawnParachuteBot, &s_helicopter1};

statetype far s_parachutebot_walk1 = { /* 322f0 */
  PARACHUTEBOT_WALK1_L_SPR, PARACHUTEBOT_WALK1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_ParachuteBot, NULL, R_Walk, &s_parachutebot_walk2};

statetype far s_parachutebot_walk2 = { /* 32310 */
  PARACHUTEBOT_WALK2_L_SPR, PARACHUTEBOT_WALK2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_ParachuteBot, NULL, R_Walk, &s_parachutebot_walk1};

statetype far s_parachutebot_attack = { /* 32330 */
  PARACHUTEBOT_WALK2_L_SPR, PARACHUTEBOT_WALK2_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, C_ParachuteBotAttack, R_ParachuteBotAttack, &s_parachutebot_attack};

statetype far s_parachutebot_falling = { /* 32350 */
  PARACHUTEBOT_FALLING_L_SPR, PARACHUTEBOT_FALLING_R_SPR,
  stepthink, false, ps_none, 10, 8, 32,
  NULL, C_ParachuteBotAttack, R_ParachuteBot, &s_parachutebot_falling};

statetype far s_spitsnake_walk1 = { /* 32370 */
  SPITSNAKE_WALK1_L_SPR, SPITSNAKE_WALK1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_SpitterSnake, NULL, R_Walk, &s_spitsnake_walk2};

statetype far s_spitsnake_walk2 = { /* 32390 */
  SPITSNAKE_WALK2_L_SPR, SPITSNAKE_WALK2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_SpitterSnake, NULL, R_Walk, &s_spitsnake_walk1};

statetype far s_spitsnake_wait1 = { /* 323b0 */
  SPITSNAKE_WALK1_L_SPR, SPITSNAKE_WALK1_R_SPR,
  step, true, ps_tofloor, 5, 128, 0,
  T_SpitterSnake2, NULL, R_Walk, &s_spitsnake_wait2};

statetype far s_spitsnake_wait2 = { /* 323d0 */
  SPITSNAKE_WALK2_L_SPR, SPITSNAKE_WALK2_R_SPR,
  step, true, ps_tofloor, 5, 128, 0,
  T_SpitterSnake2, NULL, R_Walk, &s_spitsnake_wait1};

statetype far s_spitsnake_attack1 = { /* 323f0 */
  SPITSNAKE_ATTACK_L_SPR, SPITSNAKE_ATTACK_R_SPR,
  step, false, ps_none, 10, 0, 0,
  SpitterSnakeSpit, NULL, R_Draw, &s_spitsnake_attack2};

statetype far s_spitsnake_attack2 = { /* 32410 */
  SPITSNAKE_ATTACK_L_SPR, SPITSNAKE_ATTACK_R_SPR,
  step, false, ps_none, 10, 65408, 0,
  NULL, NULL, R_Draw, &s_spitsnake_walk1};

statetype far s_spitsnake_projectile1 = { /* 32430 */
  SPITSNAKE_SPIT1_L_SPR, SPITSNAKE_SPIT1_R_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_spitsnake_projectile2};

statetype far s_spitsnake_projectile2 = { /* 32450 */
  SPITSNAKE_SPIT2_L_SPR, SPITSNAKE_SPIT2_R_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_spitsnake_projectile1};

statetype far s_sewermutant1 = { /* 32470 */
  SEWERMUTANT_WALK1_L_SPR, SEWERMUTANT_WALK1_R_SPR,
  step, false, ps_tofloor, 20, 128, 0,
  T_SewerMutant, NULL, R_Walk, &s_sewermutant2};

statetype far s_sewermutant2 = { /* 32490 */
  SEWERMUTANT_WALK2_L_SPR, SEWERMUTANT_WALK2_R_SPR,
  step, false, ps_tofloor, 20, 128, 0,
  T_SewerMutant, NULL, R_Walk, &s_sewermutant1};

statetype far s_sewermutant_attack = { /* 324b0 */
  SEWERMUTANT_ATTACK_L_SPR, SEWERMUTANT_ATTACK_R_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  SewerMutantThrow, NULL, R_Walk, &s_sewermutant1};

statetype far s_sewermutant_projectile1 = { /* 324d0 */
  SEWERMUTANT_SPIT1_SPR, SEWERMUTANT_SPIT1_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_sewermutant_projectile2};

statetype far s_sewermutant_projectile2 = { /* 324f0 */
  SEWERMUTANT_SPIT2_SPR, SEWERMUTANT_SPIT2_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_sewermutant_projectile1};

statetype far s_hostage1_1 = { /* 32510 */
  HOSTAGE1_1_SPR, HOSTAGE1_1_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_hostage1_2};

statetype far s_hostage1_2 = { /* 32530 */
  HOSTAGE1_2_SPR, HOSTAGE1_2_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_hostage1_1};

statetype far s_hostage2_1 = { /* 32550 */
  HOSTAGE2_1_SPR, HOSTAGE2_1_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_hostage2_2};

statetype far s_hostage2_2 = { /* 32570 */
  HOSTAGE2_2_SPR, HOSTAGE2_2_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_hostage2_1};

statetype far s_hostage3_1 = { /* 32590 */
  HOSTAGE3_1_SPR, HOSTAGE3_1_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_hostage3_2};

statetype far s_hostage3_2 = { /* 325b0 */
  HOSTAGE3_2_SPR, HOSTAGE3_2_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_hostage3_1};

statetype far s_drmangle_hologram1 = { /* 325d0 */
  MANGLE_HOLOGRAM1_SPR, MANGLE_HOLOGRAM1_SPR,
  step, false, ps_none, 10, 0, 0,
  T_DrMangleHologram, NULL, R_Draw, &s_drmangle_hologram1};

statetype far s_drmangle_hologram2 = { /* 325f0 */
  MANGLE_HOLOGRAM2_SPR, MANGLE_HOLOGRAM2_SPR,
  step, false, ps_none, 10, 0, 0,
  T_DrMangleHologram, NULL, R_Draw, &s_drmangle_hologram1};

statetype far s_drmangle_hologram3 = { /* 32610 */
  MANGLE_HOLOGRAM3_SPR, MANGLE_HOLOGRAM3_SPR,
  step, false, ps_none, 200, 0, 0,
  T_DrMangleHologram, NULL, R_Draw, &s_drmangle_hologram1};

statetype far s_drmangle_hologram1_faded = { /* 32630 */
  MANGLE_HOLOGRAM_FADE1_SPR, MANGLE_HOLOGRAM_FADE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_drmangle_hologram1};

statetype far s_drmangle_hologram2_faded = { /* 32650 */
  MANGLE_HOLOGRAM_FADE2_SPR, MANGLE_HOLOGRAM_FADE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_drmangle_hologram2};

statetype far s_drmangle_hologram3_faded = { /* 32670 */
  MANGLE_HOLOGRAM_FADE3_SPR, MANGLE_HOLOGRAM_FADE3_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_drmangle_hologram3};

statetype far s_drmangle_hologram_attacking = { /* 32690 */
  MANGLE_HOLOGRAM_ATTACK_SPR, MANGLE_HOLOGRAM_ATTACK_SPR,
  step, false, ps_none, 3, 0, 0,
  T_DrMangleHologramAttacking, NULL, R_DrMangleHologramAttacking, &s_drmangle_hologram_attacking};

statetype far s_drmangle_typing1 = { /* 326b0 */
  MANGLE_TYPING1_SPR, MANGLE_TYPING1_SPR,
  step, false, ps_tofloor, 20, 0, 0,
  T_DrMangle, NULL, R_Draw, &s_drmangle_typing2};

statetype far s_drmangle_typing2 = { /* 326d0 */
  MANGLE_TYPING2_SPR, MANGLE_TYPING2_SPR,
  step, false, ps_tofloor, 20, 0, 0,
  T_DrMangle, NULL, R_Draw, &s_drmangle_typing1};

statetype far s_drmangle_monster1 = { /* 326f0 */
  MANGLE_MONSTER1_L_SPR, MANGLE_MONSTER1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_DrMangle, NULL, R_Walk, &s_drmangle_monster2};

statetype far s_drmangle_monster2 = { /* 32710 */
  MANGLE_MONSTER2_L_SPR, MANGLE_MONSTER2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_DrMangle, NULL, R_Walk, &s_drmangle_monster1};

statetype far s_drmangle_monster_jumping = { /* 32730 */
  MANGLE_MONSTER2_L_SPR, MANGLE_MONSTER2_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_DrMangleJumping, &s_drmangle_monster_jumping};

statetype far s_drmangle_dying = { /* 32750 */
  MANGLE_DEFEATED_SPR, MANGLE_DEFEATED_SPR,
  step, false, ps_tofloor, 200, 0, 0,
  NULL, NULL, R_Draw, &s_drmangle_dead};

statetype far s_drmangle_dead = { /* 32770 */
  MANGLE_DEFEATED_SPR, MANGLE_DEFEATED_SPR,
  step, false, ps_tofloor, 2, 0, 0,
  DrMangleDefeated, NULL, R_Draw, &s_drmangle_dead};

statetype far s_drmangle_dead2 = { /* 32790 */
  MANGLE_DEFEATED_SPR, MANGLE_DEFEATED_SPR,
  think, false, ps_tofloor, 0, 0, 0,
  NULL, NULL, R_Draw, &s_drmangle_dead2};



void R_EnemyProjectile(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed = -ob->xspeed/2;
  }

  if (ob->hitsouth)
  {
    ob->yspeed = -ob->yspeed/2;
  }

  wall = ob->hitnorth;
  if (wall)
  {
    if (ob->yspeed < 0)
      ob->yspeed = 0;

    absx = abs(ob->xspeed);
    absy = ob->yspeed;
    if (absx>absy)
    {
      if (absx>absy*2)  // 22 degrees
      {
        angle = 0;
        speed = absx*286; // x*sqrt(5)/2
      }
      else        // 45 degrees
      {
        angle = 1;
        speed = absx*362; // x*sqrt(2)
      }
    }
    else
    {
      if (absy>absx*2)  // 90 degrees
      {
        angle = 3;
        speed = absy*256;
      }
      else
      {
        angle = 2;    // 67 degrees
        speed = absy*286; // y*sqrt(5)/2
      }
    }
    if (ob->xspeed > 0)
      angle = 7-angle;

    speed >>= 1;
    newangle = bounceangle[ob->hitnorth][angle];
    switch (newangle)
    {
    case 0:
      ob->xspeed = speed / 286;
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 1:
      ob->xspeed = speed / 362;
      ob->yspeed = -ob->xspeed;
      break;
    case 2:
      ob->yspeed = -(speed / 286);
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 3:

    case 4:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 5:
      ob->yspeed = -(speed / 286);
      ob->xspeed = ob->yspeed / 2;
      break;
    case 6:
      ob->xspeed = ob->yspeed = -(speed / 362);
      break;
    case 7:
      ob->xspeed = -(speed / 286);
      ob->yspeed = ob->xspeed / 2;
      break;

    case 8:
      ob->xspeed = -(speed / 286);
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 9:
      ob->xspeed = -(speed / 362);
      ob->yspeed = -ob->xspeed;
      break;
    case 10:
      ob->yspeed = speed / 286;
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 11:

    case 12:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 13:
      ob->yspeed = speed / 286;
      ob->xspeed = ob->yspeed / 2;
      break;
    case 14:
      ob->xspeed = speed / 362;
      ob->yspeed = speed / 362;
      break;
    case 15:
      ob->xspeed = speed / 286;
      ob->yspeed = ob->xspeed / 2;
      break;
    }

    if (speed < 256*16)
    {
      RemoveObj(ob);
    }
  }
}


void SpawnElevator(Sint16 x, Sint16 y, arrowdirtype dir)
{
  GetNewObj(false);

  new->obclass = platformobj;
  new->active = ac_allways;
  new->priority = 1;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);

  switch (dir)
  {
    case arrow_North:
      new->xdir = 0;
      new->ydir = -1;
      break;

    case arrow_East:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case arrow_South:
      new->xdir = 0;
      new->ydir = 1;
      break;

    case arrow_West:
      new->xdir = -1;
      new->ydir = 0;
      break;

  }

  NewState(new, &s_platform);
}


void SpawnApogeeLogo(Sint16 x, Sint16 y, arrowdirtype dir)
{
  GetNewObj(false);

  new->obclass = platformobj;
  new->active = ac_allways;
  new->priority = 0;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);

  switch (dir)
  {
    case arrow_North:
      new->xdir = 0;
      new->ydir = -1;
      break;

    case arrow_East:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case arrow_South:
      new->xdir = 0;
      new->ydir = 1;
      break;

    case arrow_West:
      new->xdir = -1;
      new->ydir = 0;
      break;

  }

  NewState(new, &s_apogeelogo);
}


void T_Platform(objtype* ob)
{
  Uint16 newpos, newtile;

  if (xtry || ytry)
    return;

  xtry = ob->xdir * 12 * tics;
  ytry = ob->ydir * 12 * tics;

  if (ob->ydir == 1)
  {
    newpos = ob->bottom + ytry;
    newtile = CONVERT_GLOBAL_TO_TILE(newpos);

    if (ob->tilebottom != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) == PLATFORMBLOCK)
      {
        ytry = 0;
        ob->needtoreact = true;
        return;
      }
    }

    if (ob->tilebottom != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) ==
          PLATFORMBLOCK-1)
      {
        if (*(mapsegs[2]+mapbwidthtable[newtile-2]/2+ob->tileleft) ==
            PLATFORMBLOCK-1)
        {
          ytry = 0;
          ob->needtoreact = true;
          return;
        }
        else
        {
          ob->ydir = -1;
          ytry = ytry - (newpos & 0xFF);
        }
      }
    }
  }
  else if (ob->ydir == -1)
  {
    newpos = ob->top + ytry;
    newtile = CONVERT_GLOBAL_TO_TILE(newpos);

    if (ob->tiletop != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) == PLATFORMBLOCK)
      {
        ytry = 0;
        ob->needtoreact = true;
        return;
      }
    }

    if (ob->tiletop != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) == PLATFORMBLOCK-1)
      {
        if (*(mapsegs[2]+mapbwidthtable[newtile+2]/2+ob->tileleft) == PLATFORMBLOCK-1)
        {
          ytry = 0;
          ob->needtoreact = true;
          return;
        }
        else
        {
          ob->ydir = 1;
          ytry = ytry + (0x100 - (newpos & 0xFF));
        }
      }
    }
  }
}


void SpawnHelicopter(Sint16 x, Sint16 y, arrowdirtype dir)
{
  GetNewObj(false);

  new->obclass = helicopterobj;
  new->active = ac_allways;
  new->priority = 3;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 0;
  new->ydir = 1;
  new->needtoclip = cl_noclip;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 50;
      break;

    default:
      new->health = 25;
      break;
  }

  new->temp6 = 15;
  new->temp7 = 40;

  NewState(new, &s_helicopter1);

  *(mapsegs[2] + mapbwidthtable[y]/2 + x) = DIRARROWSTART + dir;

  new->temp1 = dir;
  new->temp2 = 0x100;
}


void T_GoPlat(objtype* ob)
{
  Uint16 move;
  Uint16 tx, ty;
  Sint16 dir;

  //
  // this code could be executed twice during the same frame because the
  // object's animation/state changed during that frame, so don't update
  // anything if we already have movement for the current frame i.e. the
  // update code has already been executed this frame
  if (xtry || ytry)
    return;

  move = tics * 24;
  if (ob->temp2 > move)
  {
    ob->temp2 = ob->temp2 - move;

    dir = pdirx[ob->temp1];
    if (dir == 1)
    {
      xtry = xtry + move;
    }
    else if (dir == -1)
    {
      xtry = xtry + -move;
    }

    dir = pdiry[ob->temp1];
    if (dir == 1)
    {
      ytry = ytry + move;
    }
    else if (dir == -1)
    {
      ytry = ytry + -move;
    }
  }
  else
  {
    dir = pdirx[ob->temp1];
    if (dir == 1)
    {
      xtry += ob->temp2;
    }
    else if (dir == -1)
    {
      xtry += -ob->temp2;
    }

    dir = pdiry[ob->temp1];
    if (dir == 1)
    {
      ytry += ob->temp2;
    }
    else if (dir == -1)
    {
      ytry += -ob->temp2;
    }

    tx = CONVERT_GLOBAL_TO_TILE(ob->x + xtry);
    ty = CONVERT_GLOBAL_TO_TILE(ob->y + ytry);
    ob->temp1 = *(mapsegs[2]+mapbwidthtable[ty]/2 + tx) - DIRARROWSTART;
    if (ob->temp1 < arrow_North || ob->temp1 > arrow_None)
    {
      char error[60] = "Goplat moved to a bad spot: ";
      char buf[5] = "";

      strcat(error, itoa(ob->x, buf, 16));
      strcat(error, ",");
      strcat(error, itoa(ob->y, buf, 16));
      Quit(error);
    }

    move -= ob->temp2;
    ob->temp2 = TILEGLOBAL - move;

    dir = pdirx[ob->temp1];
    if (dir == 1)
    {
      xtry = xtry + move;
    }
    else if (dir == -1)
    {
      xtry = xtry - move;
    }

    dir = pdiry[ob->temp1];
    if (dir == 1)
    {
      ytry = ytry + move;
    }
    else if (dir == -1)
    {
      ytry = ytry - move;
    }
  }
}


void R_Helicopter(objtype* ob)
{
  if (--ob->temp6 <= 0)
  {
    ob->state = &s_helicopter2;
    ob->temp6 = 15;
  }

  if (--ob->temp7 <= 0)
  {
    ob->temp7 = 40;

    if (OnScreen(ob))
    {
      SpawnParachuteBot(ob);
    }
  }

  PLACESPRITE;
}


void SpawnParachuteBot(objtype* ob)
{
  SD_PlaySound(13);

  GetNewObj(true);

  new->obclass = parachutebotobj;
  new->priority = 2;
  new->active = ac_allways;
  new->x = ob->x + 24*PIXGLOBAL;
  new->y = ob->y + 8*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 20;
      break;

    default:
      new->health = 10;
      break;
  }

  new->temp5 = 75;

  NewState(new, &s_parachutebot_falling);
}


void T_ParachuteBot(objtype* ob)
{
  Sint16 xdelta;

  if (--ob->temp5 <= 0)
  {
    ob->shootable = false;
    ChangeState(ob, &s_grenadeexplosion1);
    return;
  }

  if (ob->top > player->bottom || ob->bottom < player->top)
    return;

  if (ob->xdir == -1)
  {
    xdelta = ob->left - player->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = 1;
      return;
    }

    ob->yspeed = -24 - US_RndT() / 16;
    ob->xspeed = -32;
    ob->state = &s_parachutebot_attack;
    return;
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = -1;
      return;
    }

    ob->yspeed = -24 - US_RndT() / 16;
    ob->xspeed = 32;
    ob->state = &s_parachutebot_attack;
    return;
  }
}


void C_ParachuteBotAttack(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj)
  {
    ob->shootable = false;
    ChangeState(ob, &s_grenadeexplosion1);
  }
}


void R_ParachuteBot(objtype* ob)
{
  if (!ob->hitnorth)
  {
    if (US_RndT() < 100)
    {
      ob->xdir = -ob->xdir;
    }
  }
  else
  {
    ChangeState(ob, &s_parachutebot_walk1);
    ob->y += 16*PIXGLOBAL;
  }

  PLACESPRITE;
}


void R_ParachuteBotAttack(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_grenadeexplosion1);
    ob->shootable = false;
    ob->nothink = 12;
  }

  PLACESPRITE;
}


void SpawnSpitterSnake(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = spittersnakeobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 8*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 6;
      break;

    default:
      new->health = 3;
      break;
  }

  NewState(new, &s_spitsnake_walk1);
}


void T_SpitterSnake2(objtype* ob)
{
  ob->state = &s_spitsnake_walk1;
}


void SpitterSnakeSpit(objtype* ob)
{
  GetNewObj(true);

  new->obclass = enemyprojectileobj;

  if (ob->xdir == 1)
  {
    new->x = ob->x + 24*PIXGLOBAL;
    new->y = ob->y + 8*PIXGLOBAL;
  }
  else
  {
    new->x = ob->x;
    new->y = ob->y + 8*PIXGLOBAL;
  }

  new->xdir = ob->xdir;
  new->ydir = 1;
  new->xspeed = ob->xdir * 40 - (US_RndT() >> 4);
  new->yspeed = -20;
  new->active = ac_removable;

  NewState(new, &s_spitsnake_projectile1);

  ob->nothink = 2;
}


void T_SpitterSnake(objtype* ob)
{
  Sint16 xdelta;

  if (abs(ob->y - player->y) > 48*PIXGLOBAL)
  {
    if (US_RndT() < 8)
    {
      ob->xdir = -ob->xdir;
    }
  }
  else
  {
    xdelta = player->x - ob->x;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = -1;
    }

    if (xdelta < -64*PIXGLOBAL)
    {
      SD_PlaySound(9);
      ob->xdir = -1;
      ob->state = &s_spitsnake_attack1;
      return;
    }

    if (xdelta < 0)
    {
      ob->xdir = 1;
      ob->state = &s_spitsnake_wait1;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 64*PIXGLOBAL)
    {
      ob->xdir = -1;
      ob->state = &s_spitsnake_wait1;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 128*PIXGLOBAL)
    {
      SD_PlaySound(9);
      ob->xdir = 1;
      ob->state = &s_spitsnake_attack1;
      return;
    }

    ob->xdir = 1;
  }
}


void SpawnSewerMutant(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = sewermutantobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 32*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 30;
      break;

    default:
      new->health = 15;
      break;
  }

  NewState(new, &s_sewermutant1);
}


void SewerMutantThrow(objtype* ob)
{
  GetNewObj(true);

  new->obclass = enemyprojectileobj;

  if (ob->xdir == 1)
  {
    new->x = ob->x + 24*PIXGLOBAL;
    new->y = ob->y + 8*PIXGLOBAL;
  }
  else
  {
    new->x = ob->x;
    new->y = ob->y + 8*PIXGLOBAL;
  }

  new->xdir = ob->xdir;
  new->ydir = 1;
  new->xspeed = ob->xdir * 30 - (US_RndT() >> 4);
  new->yspeed = -20;
  new->active = ac_removable;

  NewState(new, &s_sewermutant_projectile1);

  ob->nothink = 2;
}


void T_SewerMutant(objtype* ob)
{
  Sint16 xdelta;

  if (abs(ob->y - player->y) > 48*PIXGLOBAL)
  {
    if (US_RndT() < 8)
    {
      ob->xdir = -ob->xdir;
    }
  }
  else
  {
    xdelta = player->x - ob->x;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = -1;
    }

    if (xdelta < -64*PIXGLOBAL)
    {
      SD_PlaySound(38);
      ob->xdir = -1;
      ob->state = &s_sewermutant_attack;
      return;
    }

    if (xdelta < 0)
    {
      ob->xdir = 1;
      ob->state = &s_sewermutant1;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 64*PIXGLOBAL)
    {
      ob->xdir = -1;
      ob->state = &s_sewermutant1;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 128*PIXGLOBAL)
    {
      SD_PlaySound(38);
      ob->xdir = 1;
      ob->state = &s_sewermutant_attack;
      return;
    }

    ob->xdir = 1;
  }
}


void SpawnHostage(Sint16 x, Sint16 y, Sint16 type)
{
  GetNewObj(false);

  new->obclass = hostageobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 24*PIXGLOBAL;

  switch (type)
  {
    case 0:
      NewState(new, &s_hostage1_1);
      break;

    case 1:
      NewState(new, &s_hostage2_1);
      break;

    case 2:
      NewState(new, &s_hostage3_1);
      break;
  }

  new->hitnorth = 1;
  new->shootable = false;
}


void SpawnDrMangleHologram(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = drmangleobj;
  new->active = ac_allways;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 16*PIXGLOBAL;
  NewState(new, &s_drmangle_hologram1);
  new->priority = 3;
  new->shootable = false;
  new->needtoclip = cl_noclip;
  drmangleactive = false;
}


void T_DrMangleHologram(objtype* ob)
{
  // Randomized animation
  if (US_RndT() > 220)
  {
    if (ob->state == &s_drmangle_hologram1)
    {
      ChangeState(ob, &s_drmangle_hologram1_faded);
      return;
    }

    if (ob->state == &s_drmangle_hologram2)
    {
      ChangeState(ob, &s_drmangle_hologram2_faded);
      return;
    }

    if (ob->state == &s_drmangle_hologram3)
    {
      ChangeState(ob, &s_drmangle_hologram3_faded);
      return;
    }
  }
  else if (US_RndT() > 110)
  {
    ChangeState(ob, &s_drmangle_hologram2);
    return;
  }

  if (US_RndT() > 250 && ob->state != &s_drmangle_hologram3)
  {
    ChangeState(ob, &s_drmangle_hologram3);
  }

  // Never true, unless the actor were to be placed in level 11, which is not
  // the case in the shipping game. See code in SnakeInteractThink().
  if (drmangleactive)
  {
    Sint16 rand = US_RndT();

    if (rand > 120)
    {
      // What the heck?
      ThrowGrenade(ob->midx, ob->top, dir_West);
    }
    else
    {
      sub_22db0(ob);
    }

    ob->state = &s_drmangle_hologram_attacking;
  }
}


void T_DrMangleHologramAttacking(objtype* ob)
{
  Sint16 rand, xdelta;

  rand = US_RndT();

  AccelerateY(ob, ob->y > player->y ? -1 : 1, US_RndT() / 8 + 4);

  if (ob->yspeed > 0)
  {
    ob->ydir = 1;
  }
  else
  {
    ob->ydir = -1;
  }

  AccelerateX(ob, ob->xdir, US_RndT() / 8 + 4);

  if (ob->xspeed < 0)
  {
    xdelta = ob->left - player->right;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = 1;
    }
    else
    {
      ob->xdir = -1;
    }
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = -1;
    }
    else
    {
      ob->xdir = 1;
    }
  }

  if (rand > 150 && rand < 200)
  {
    if (ob->top > player->bottom || ob->bottom < player->top)
      return;

    if (SpawnEnemyShot(ob->midx, ob->y + 15*PIXGLOBAL, &s_252) == -1)
      return;

    {
      new->xspeed = ob->xdir * 60;
      new->yspeed = 0;
      SD_PlaySound(6);
    }
  }
  else if (rand > 250)
  {
    // What the heck?
    ThrowGrenade(ob->midx, ob->top, dir_West);
    ThrowGrenade(ob->midx, ob->top, dir_East);
  }
}


void R_DrMangleHologramAttacking(objtype* ob)
{
  if (ob->top > player->top + 24)
  {
    ob->ydir = -1;
  }
  else if (ob->top < player->top + 24)
  {
    ob->ydir = 1;
  }

  PLACESPRITE;
}


void SpawnDrMangle(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = drmangleobj;
  new->active = ac_allways;
  new->priority = 2;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 24*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_drmangle_typing1);

  new->hitnorth = 1;
  new->ticcount = US_RndT() / 32;

  new->shootable = false;
  new->health = bosshealth = 200;
  lastbosshealth = -1;
  hbardivisor = bosshealth / 20 - 1;
}


void T_DrMangle(objtype* ob)
{
  Sint16 shotorigin, xdelta;

  if (ob->health != bosshealth)
  {
    lastbosshealth = bosshealth;
    bosshealth = ob->health;
  }

  if (ob->obclass == inertobj)
  {
    ob->state = &s_drmangle_dying;
    ob->y += 32*PIXGLOBAL;
    ob->shootable = false;
    return;
  }

  if (ob->top > player->bottom || ob->bottom < player->top)
    return;

  if (US_RndT() > 230 && ob->shootable == true)
  {
    if (ob->xdir == 1)
    {
      shotorigin = ob->x + 112*PIXGLOBAL;
    }
    else
    {
      shotorigin = ob->x;
    }

    if (SpawnEnemyShot(shotorigin, ob->y + 32*PIXGLOBAL, &s_255) == -1)
    {
      return;
    }

    new->xspeed = ob->xdir * 60;

    if (US_RndT() < 70)
    {
      new->yspeed = 0;
    }
    else
    {
      if (ob->temp1 & 1)
      {
        new->yspeed = 4;
      }
      else
      {
        new->yspeed = -4;
      }
    }

    SD_PlaySound(21);
  }

  if (ob->xdir == -1)
  {
    xdelta = ob->left - player->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = 1;
      return;
    }

    ob->yspeed = -24 - US_RndT() / 16;
    ob->xspeed = -32;

    SD_PlaySound(23);
    ob->shootable = true;
    ob->state = &s_drmangle_monster_jumping;
    return;
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = -1;
      return;
    }

    ob->yspeed = -24 - US_RndT() / 16;
    ob->xspeed = 32;

    SD_PlaySound(23);
    ob->shootable = true;
    ob->state = &s_drmangle_monster_jumping;
    return;
  }
}


void DrMangleDefeated(objtype* ob)
{
  gamestate.mapon = 11;
  ob->hitnorth = 1;
  ob->state = &s_drmangle_dead2;
  ob->dmgflash = 0;
  playstate = ex_completed;
}


void R_DrMangleJumping(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_drmangle_monster1);
  }

  PLACESPRITE;
}
