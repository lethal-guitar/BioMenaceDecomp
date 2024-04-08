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



Sint16 unused[] = {
  700, 700, 350, 175
};


Sint16 pickupshapenums[] = {
  140, 144, 154, 156, 158, 160,
  162, 164, 195, 197, 193, 185, 187, 189, 191, 209, 199,
  200, 201, 202, 203, 204, 205, 206, 207, 208, 166, 168,
  170, 172, 174, 176, 178, 211, 142, 217, 219, 215, 180
};


void R_WalkCeiling();
void T_Pickup();
void T_PickupRise();
void T_RoboPal();
void R_RoboPal();
void RoboPalTeleport_DoWarp();
void T_Slug();
void T_GhostlySlug();
void T_RunningFire();
void R_SlugAttack();
void R_GhostlySlugAttack();
void R_RunningFire();
void T_Bomb();
void R_Bomb();
void T_FireImp();
void T_FireImpFireForm();
void R_FireImp();
void R_FireImpJumping();
void T_HedgeHogRolling();
void T_HedgeHogWaiting();
void T_HedgeHogWaiting2();
void R_HedgeHog();
void R_HedgeHogJumping();
void T_Brawler();
void T_CeilingWalkerOnCeiling();
void T_CeilingWalkerOnFloor();
void R_CeilingWalkerFalling();
void T_CrawlingSlime();


statetype far s_pickup1 = { /* 327b0 */
  0, 0, step, false, ps_none, 20, 0, 0,
  T_Pickup, NULL, R_Draw, &s_pickup2};

statetype far s_pickup2 = { /* 327d0 */
  0, 0, step, false, ps_none, 20, 0, 0,
  T_Pickup, NULL, R_Draw, &s_pickup1};

statetype far s_pickuprise = { /* 327f0 */
  0, 0, slide, false, ps_none, 40, 0, 8,
  T_PickupRise, NULL, R_Draw, NULL};

statetype far s_robopalwait1 = { /* 32810 */
  ROBOPAL1_SPR, ROBOPAL1_SPR,
  step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_robopalwait2};

statetype far s_robopalwait2 = { /* 32830 */
  ROBOPAL2_SPR, ROBOPAL2_SPR,
  step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_robopalwait1};

statetype far s_robopalactive1 = { /* 32850 */
  ROBOPAL1_SPR, ROBOPAL1_SPR,
  stepthink, false, ps_none, 5, 0, 0,
  T_RoboPal, NULL, R_RoboPal, &s_robopalactive2};

statetype far s_robopalactive2 = { /* 32870 */
  ROBOPAL2_SPR, ROBOPAL2_SPR,
  stepthink, false, ps_none, 5, 0, 0,
  T_RoboPal, NULL, R_RoboPal, &s_robopalactive1};

statetype far s_robopal_teleport1 = { /* 32890 */
  ROBOPAL_TELEPORT1_SPR, ROBOPAL_TELEPORT1_SPR,
  step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_robopal_teleport2};

statetype far s_robopal_teleport2 = { /* 328b0 */
  ROBOPAL_TELEPORT2_SPR, ROBOPAL_TELEPORT2_SPR,
  step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_robopal_teleport3};

statetype far s_robopal_teleport3 = { /* 328d0 */
  -1, -1, step, false, ps_none, 1, 0, 0,
  RoboPalTeleport_DoWarp, NULL, R_Draw, &s_robopal_teleport4};

statetype far s_robopal_teleport4 = { /* 328f0 */
  ROBOPAL_TELEPORT2_SPR, ROBOPAL_TELEPORT2_SPR,
  step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_robopal_teleport5};

statetype far s_robopal_teleport5 = { /* 32910 */
  ROBOPAL_TELEPORT1_SPR, ROBOPAL_TELEPORT1_SPR,
  step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_robopalactive1};

statetype far s_slug_walk1 = { /* 32930 */
  SLUG_WALK1_L_SPR, SLUG_WALK1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_Slug, NULL, R_Walk, &s_slug_walk2};

statetype far s_slug_walk2 = { /* 32950 */
  SLUG_WALK2_L_SPR, SLUG_WALK2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_Slug, NULL, R_Walk, &s_slug_walk1};

statetype far s_slug_attack = { /* 32970 */
  SLUG_ATTACK_L_SPR, SLUG_ATTACK_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_SlugAttack, &s_slug_walk1};

statetype far s_running_fire1 = { /* 32990 */
  RUNNING_FIRE1_SPR, RUNNING_FIRE1_SPR,
  step, false, ps_tofloor, 5, 64, 0,
  T_RunningFire, C_GrenadeExplosion, R_RunningFire, &s_running_fire2};

statetype far s_running_fire2 = { /* 329b0 */
  RUNNING_FIRE2_SPR, RUNNING_FIRE2_SPR,
  step, false, ps_tofloor, 5, 64, 0,
  T_RunningFire, C_GrenadeExplosion, R_RunningFire, &s_running_fire1};

statetype far s_ghostlyslug1 = { /* 329d0 */
  GHOSTSLUG1_L_SPR, GHOSTSLUG1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_GhostlySlug, NULL, R_Walk, &s_ghostlyslug2};

statetype far s_ghostlyslug2 = { /* 329f0 */
  GHOSTSLUG2_L_SPR, GHOSTSLUG2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_GhostlySlug, NULL, R_Walk, &s_ghostlyslug1};

statetype far s_ghostlyslug_attack = { /* 32a10 */
  GHOSTSLUG1_L_SPR, GHOSTSLUG1_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_GhostlySlugAttack, &s_ghostlyslug1};

statetype far s_bomb_idle = { /* 32a30 */
  BOMB_WAIT_L_SPR, BOMB_WAIT_R_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  T_Bomb, NULL, R_Draw, &s_bomb_idle};

statetype far s_bomb_attack1 = { /* 32a50 */
  BOMB_JUMP1_L_SPR, BOMB_JUMP1_R_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_Draw, &s_bomb_attack2};

statetype far s_bomb_attack2 = { /* 32a70 */
  BOMB_JUMP2_L_SPR, BOMB_JUMP2_R_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_Bomb, &s_bomb_attack3};

statetype far s_bomb_attack3 = { /* 32a90 */
  BOMB_JUMP3_L_SPR, BOMB_JUMP3_R_SPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_Bomb, &s_bomb_attack3};

statetype far s_fireimp_walk1 = { /* 32ab0 */
  FIREIMP_WALK1_L_SPR, FIREIMP_WALK1_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  T_FireImp, NULL, R_FireImp, &s_fireimp_walk2};

statetype far s_fireimp_walk2 = { /* 32ad0 */
  FIREIMP_WALK2_L_SPR, FIREIMP_WALK2_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, R_FireImp, &s_fireimp_walk3};

statetype far s_fireimp_walk3 = { /* 32af0 */
  FIREIMP_WALK3_L_SPR, FIREIMP_WALK3_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, R_FireImp, &s_fireimp_walk4};

statetype far s_fireimp_walk4 = { /* 32b10 */
  FIREIMP_WALK4_L_SPR, FIREIMP_WALK4_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, R_FireImp, &s_fireimp_walk1};

statetype far s_fireimp_fireform1 = { /* 32b30 */
  RUNNING_FIRE1_SPR, RUNNING_FIRE1_SPR,
  stepthink, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, R_FireImp, &s_fireimp_fireform2};

statetype far s_fireimp_fireform2 = { /* 32b50 */
  RUNNING_FIRE2_SPR, RUNNING_FIRE2_SPR,
  stepthink, false, ps_tofloor, 7, 128, 0,
  T_FireImpFireForm, NULL, R_FireImp, &s_fireimp_fireform1};

statetype far s_fireimp_stand = { /* 32b70 */
  FIREIMP_STAND_SPR, FIREIMP_STAND_SPR,
  stepthink, false, ps_tofloor, 50, 0, 0,
  NULL, NULL, R_Draw, &s_fireimp_walk1};

statetype far s_fireimp_jumping = { /* 32b90 */
  FIREIMP_WALK4_L_SPR, FIREIMP_WALK4_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_FireImpJumping, NULL};

statetype far s_hedgehog_roll1 = { /* 32bb0 */
  HEDGEHOG_ROLL1_L_SPR, HEDGEHOG_ROLL1_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  T_HedgeHogRolling, NULL, R_HedgeHog, &s_hedgehog_roll2};

statetype far s_hedgehog_roll2 = { /* 32bd0 */
  HEDGEHOG_ROLL2_L_SPR, HEDGEHOG_ROLL2_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, R_HedgeHog, &s_hedgehog_roll3};

statetype far s_hedgehog_roll3 = { /* 32bf0 */
  HEDGEHOG_ROLL3_L_SPR, HEDGEHOG_ROLL3_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, R_HedgeHog, &s_hedgehog_roll4};

statetype far s_hedgehog_roll4 = { /* 32c10 */
  HEDGEHOG_ROLL4_L_SPR, HEDGEHOG_ROLL4_R_SPR,
  step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, R_HedgeHog, &s_hedgehog_roll1};

statetype far s_hedgehog_wait1 = { /* 32c30 */
  HEDGEHOG_STAND_L_SPR, HEDGEHOG_STAND_R_SPR,
  stepthink, false, ps_tofloor, 25, 0, 0,
  T_HedgeHogWaiting, NULL, R_HedgeHog, &s_hedgehog_wait1};

statetype far s_hedgehog_wait2 = { /* 32c50 */
  HEDGEHOG_STAND_L_SPR, HEDGEHOG_STAND_R_SPR,
  stepthink, false, ps_tofloor, 75, 0, 0,
  T_HedgeHogWaiting2, NULL, R_Draw, &s_hedgehog_wait2};

statetype far s_hedgehog_jumping = { /* 32c70 */
  HEDGEHOG_STAND_L_SPR, HEDGEHOG_STAND_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_HedgeHogJumping, NULL};

statetype far s_brawler_stand = { /* 32c90 */
  BRAWLER_STAND_L_SPR, BRAWLER_STAND_R_SPR,
  step, true, ps_tofloor, 75, 0, 0,
  NULL, NULL, R_Draw, &s_brawler_walk1};

statetype far s_brawler_walk1 = { /* 32cb0 */
  BRAWLER_WALK1_L_SPR, BRAWLER_WALK1_R_SPR,
  stepthink, false, ps_tofloor, 10, 64, 0,
  T_Brawler, NULL, R_Walk, &s_brawler_walk2};

statetype far s_brawler_walk2 = { /* 32cd0 */
  BRAWLER_WALK2_L_SPR, BRAWLER_WALK2_R_SPR,
  stepthink, false, ps_tofloor, 10, 64, 0,
  T_Brawler, NULL, R_Walk, &s_brawler_walk3};

statetype far s_brawler_walk3 = { /* 32cf0 */
  BRAWLER_WALK3_L_SPR, BRAWLER_WALK3_R_SPR,
  stepthink, false, ps_tofloor, 10, 64, 0,
  T_Brawler, NULL, R_Walk, &s_brawler_walk4};

statetype far s_brawler_walk4 = { /* 32d10 */
  BRAWLER_WALK4_L_SPR, BRAWLER_WALK4_R_SPR,
  stepthink, false, ps_tofloor, 10, 64, 0,
  T_Brawler, NULL, R_Walk, &s_brawler_walk1};

statetype far s_brawler_attack1 = { /* 32d30 */
  BRAWLER_ATTACK1_L_SPR, BRAWLER_ATTACK1_R_SPR,
  step, true, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_brawler_attack2};

statetype far s_brawler_attack2 = { /* 32d50 */
  BRAWLER_ATTACK2_L_SPR, BRAWLER_ATTACK2_R_SPR,
  step, true, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_brawler_walk1};

statetype far s_ceilwalker_walkceil1 = { /* 32d70 */
  CEILWALKER_WALK_CEIL1_L, CEILWALKER_WALK_CEIL1_R,
  step, false, ps_toceiling, 10, 128, 0,
  T_CeilingWalkerOnCeiling, NULL, R_WalkCeiling, &s_ceilwalker_walkceil2};

statetype far s_ceilwalker_walkceil2 = { /* 32d90 */
  CEILWALKER_WALK_CEIL2_L, CEILWALKER_WALK_CEIL2_R,
  step, false, ps_toceiling, 10, 128, 0,
  T_CeilingWalkerOnCeiling, NULL, R_WalkCeiling, &s_ceilwalker_walkceil3};

statetype far s_ceilwalker_walkceil3 = { /* 32db0 */
  CEILWALKER_WALK_CEIL3_L, CEILWALKER_WALK_CEIL3_R,
  step, false, ps_toceiling, 10, 128, 0,
  T_CeilingWalkerOnCeiling, NULL, R_WalkCeiling, &s_ceilwalker_walkceil4};

statetype far s_ceilwalker_walkceil4 = { /* 32dd0 */
  CEILWALKER_WALK_CEIL4_L, CEILWALKER_WALK_CEIL4_R,
  step, false, ps_toceiling, 10, 128, 0,
  T_CeilingWalkerOnCeiling, NULL, R_WalkCeiling, &s_ceilwalker_walkceil1};

statetype far s_ceilwalker_walkfloor1 = { /* 32df0 */
  CEILWALKER_WALK1_L, CEILWALKER_WALK1_R,
  step, false, ps_tofloor, 6, 128, 0,
  T_CeilingWalkerOnFloor, NULL, R_Walk, &s_ceilwalker_walkfloor2};

statetype far s_ceilwalker_walkfloor2 = { /* 32e10 */
  CEILWALKER_WALK2_L, CEILWALKER_WALK2_R,
  step, false, ps_tofloor, 6, 128, 0,
  T_CeilingWalkerOnFloor, NULL, R_Walk, &s_ceilwalker_walkfloor3};

statetype far s_ceilwalker_walkfloor3 = { /* 32e30 */
  CEILWALKER_WALK3_L, CEILWALKER_WALK3_R,
  step, false, ps_tofloor, 6, 128, 0,
  T_CeilingWalkerOnFloor, NULL, R_Walk, &s_ceilwalker_walkfloor4};

statetype far s_ceilwalker_walkfloor4 = { /* 32e50 */
  CEILWALKER_WALK4_L, CEILWALKER_WALK4_R,
  step, false, ps_tofloor, 6, 128, 0,
  T_CeilingWalkerOnFloor, NULL, R_Walk, &s_ceilwalker_walkfloor1};

statetype far s_ceilwalker_falling = { /* 32e70 */
  CEILWALKER_FALL_L, CEILWALKER_FALL_R,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_CeilingWalkerFalling, &s_ceilwalker_falling};

statetype far s_crawlslime1 = { /* 32e90 */
  CRAWLSLIME1_L_SPR, CRAWLSLIME1_R_SPR,
  step, true, ps_tofloor, 25, 0, 0,
  NULL, NULL, R_Draw, &s_crawlslime2};

statetype far s_crawlslime2 = { /* 32eb0 */
  CRAWLSLIME1_L_SPR, CRAWLSLIME1_R_SPR,
  stepthink, false, ps_tofloor, 10, 64, 0,
  T_CrawlingSlime, NULL, R_Walk, &s_crawlslime3};

statetype far s_crawlslime3 = { /* 32ed0 */
  CRAWLSLIME2_L_SPR, CRAWLSLIME2_R_SPR,
  stepthink, false, ps_tofloor, 10, 64, 0,
  T_CrawlingSlime, NULL, R_Walk, &s_crawlslime2};

statetype far s_crawlslime_steppedon = { /* 32ef0 */
  CRAWLSLIME_STEPON_SPR, CRAWLSLIME_STEPON_SPR,
  step, true, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_crawlslime1};


void R_WalkCeiling(objtype* ob)
{
  if (ob->xdir == 1 && ob->hitwest)
  {
    ob->x -= ob->xmove;
    ob->xdir = -1;
    ob->nothink = US_RndT() >> 5;

    ChangeState(ob, ob->state);
  }
  else if (ob->xdir == -1 && ob->hiteast)
  {
    ob->x -= ob->xmove;
    ob->xdir = 1;
    ob->nothink = US_RndT() >> 5;

    ChangeState(ob, ob->state);
  }
  else if (!ob->hitsouth)
  {
    ob->x -= ob->xmove << 1;
    ob->y -= ob->ymove;
    ob->xdir = -ob->xdir;
    ob->nothink = US_RndT() >> 5;

    ChangeState(ob, ob->state);
  }

  PLACESPRITE;
}


void SpawnPickup(Sint16 x, Sint16 y, Sint16 type)
{
  Sint16 shapeindex = 0;

  GetNewObj(false);

  new->needtoclip = cl_noclip;
  new->obclass = pickupobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->ydir = -1;
  new->temp1 = type;

  switch (type)
  {
    case 9: shapeindex = 0; break;
    case 16: shapeindex = 1; break;
    case 17: shapeindex = 2; break;
    case 18: shapeindex = 3; break;
    case 19: shapeindex = 4; break;
    case 20: shapeindex = 5; break;
    case 21: shapeindex = 6; break;
    case 22: shapeindex = 7; break;
    case 23: shapeindex = 8; break;
    case 24: shapeindex = 9; break;
    case 25: shapeindex = 10; break;
    case 26: shapeindex = 11; break;
    case 27: shapeindex = 12; break;
    case 28: shapeindex = 13; break;
    case 29: shapeindex = 14; break;
    case 30: shapeindex = 15; break;
    case 36: shapeindex = 34; break;
    case 37: shapeindex = 35; break;
    case 38: shapeindex = 36; break;
    case 39: shapeindex = 37; break;
    case 52: shapeindex = 26; break;
    case 53: shapeindex = 27; break;
    case 54: shapeindex = 38; break;
    case 75: shapeindex = 28; break;
    case 76: shapeindex = 29; break;
    case 77: shapeindex = 30; break;
    case 78: shapeindex = 31; break;
    case 79: shapeindex = 32; break;
    case 80: shapeindex = 33; break;
  }

  new->temp2 = new->shapenum = pickupshapenums[shapeindex];
  new->temp3 = new->temp2 + 2;

  NewState(new, &s_pickup1);
}


void T_Pickup(objtype* ob)
{
  ob->shapenum++;
  if (ob->shapenum == ob->temp3)
    ob->shapenum = ob->temp2;
}


void T_PickupRise(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->state = &s_pickup1;
  }

  ob->shapenum++;
  if (ob->shapenum == ob->temp3)
    ob->shapenum = ob->temp2;

  DoGravity(ob);
}


void SpawnRobopal(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->active = ac_allways;
  new->obclass = robopalobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 8*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->temp7 = 0;
  new->shootable = false;

  firerobopal = false;

  NewState(new, &s_robopalwait1);

}


void T_RoboPal(objtype* ob)
{
  if (!gamestate.hasrobopal)
  {
    ChangeState(ob, &s_robopal_teleport1);
    return;
  }

  if (ob->needtoclip == cl_noclip)
  {
    ob->needtoclip = cl_midclip;
  }

  if (ob->temp7 > 300)
  {
    ob->state = &s_robopal_teleport1;
    return;
  }

  AccelerateY(ob, ob->y > player->y + 8*PIXGLOBAL ? -1 : 1, 10);
  if (ob->yspeed > 0)
  {
    ob->ydir = 1;
  }
  else
  {
    ob->ydir = -1;
  }

  if (player->xdir == 1)
  {
    if (!ob->hitnorth && !ob->hitsouth)
    {
      if (ob->x > player->x - 18*PIXGLOBAL)
      {
        ob->xdir = -1;
      }
      else if (ob->x > player->x - 40*PIXGLOBAL &&
               ob->x < player->x - 35*PIXGLOBAL)
      {
        ob->xspeed = 0;
        ob->temp7 = 0;
        ob->xdir = player->xdir;
        return;
      }
    }

    ob->temp7++;

    AccelerateX(ob, ob->x > player->x - 40*PIXGLOBAL ? -1 : 1, 16);
  }
  else if (player->xdir == -1)
  {
    if (!ob->hitnorth && !ob->hitsouth)
    {
      if (ob->x < player->x + 40)
      {
        ob->xdir = 1;
      }
      else if (ob->x > player->x + 40*PIXGLOBAL &&
               ob->x < player->x + 45*PIXGLOBAL)
      {
        ob->xspeed = 0;
        ob->temp7 = 0;
        ob->xdir = player->xdir;
        return;
      }
    }

    ob->temp7++;

    AccelerateX(ob, ob->x > player->x + 40*PIXGLOBAL ? -1 : 1, 16);
  }

  if (ob->xspeed > 0)
  {
    ob->xdir = 1;
  }
  else
  {
    ob->xdir = -1;
  }
}


void R_RoboPal(objtype* ob)
{
  if (ob->top > player->top + 8*PIXGLOBAL)
  {
    ob->ydir = -1;
  }
  else if (ob->top < player->top + 8*PIXGLOBAL)
  {
    ob->ydir = 1;
  }

  if (ob->hiteast || ob->hitwest)
  {
    ob->xdir = -ob->xdir;
    ob->xspeed = -ob->xspeed;
  }

  if (ob->hitnorth)
  {
    if (ob->x < player->x)
    {
      ob->xdir = 1;
    }
    else
    {
      ob->xdir = -1;
    }
  }

  if (ob->hitsouth)
  {
    if (ob->x < player->x)
    {
      ob->xdir = 1;
    }
    else
    {
      ob->xdir = -1;
    }
  }

  if (firerobopal)
  {
    if (player->xdir == 1)
    {
      SpawnShot(ob->midx, ob->top + 4*PIXGLOBAL, player->xdir);
    }
    else
    {
      SpawnShot(ob->midx - 8*PIXGLOBAL, ob->top + 4*PIXGLOBAL, player->xdir);
    }

    firerobopal = false;
  }

  PLACESPRITE;
}


void RoboPalTeleport_DoWarp(objtype* ob)
{
  if (!gamestate.hasrobopal)
  {
    RemoveObj(ob);
    return;
  }

  ob->needtoclip = cl_noclip;
  ob->x = player->x;
  ob->y = player->y;
  ob->temp7 = false;
}


void SpawnSlug(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = slugobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 113;
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_slug_walk1);

  new->hitnorth = 1;
  new->ticcount =  US_RndT() / 32;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 3;
      break;

    default:
      new->health = 1;
      break;
  }
}


void SpawnGhostlySlug(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = slugobj;
  new->priority = 2;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_ghostlyslug1);

  new->hitnorth = 1;
  new->ticcount =  US_RndT() / 32;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 10;
      break;

    default:
      new->health = 5;
      break;
  }
}


void T_Slug(objtype* ob)
{
  Sint16 xdelta;

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
    SD_PlaySound(SND_SLUGATTACK);
    ob->state = &s_slug_attack;
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
    SD_PlaySound(SND_SLUGATTACK);
    ob->state = &s_slug_attack;
    return;
  }
}


void T_GhostlySlug(objtype* ob)
{
  Sint16 xdelta;

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

    ob->yspeed = -24 - US_RndT() / 8;
    ob->xspeed = -32 - US_RndT() / 8;
    SD_PlaySound(SND_SLUGATTACK);
    ob->state = &s_ghostlyslug_attack;
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

    ob->yspeed = -24 - US_RndT() / 8;
    ob->xspeed = 32 + US_RndT() / 8;
    SD_PlaySound(SND_SLUGATTACK);
    ob->state = &s_ghostlyslug_attack;
    return;
  }
}


void T_RunningFire(objtype* ob)
{
  if (ob->temp7-- <= 0)
  {
    ChangeState(ob, &s_grenadeexplosion1);
  }

  if (US_RndT() > 230)
  {
    FragBloom(ob->midx + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_East + 10);
    SD_PlaySound(SND_RICOCHET);
  }

  if (US_RndT() > 230)
  {
    FragBloom(ob->midx - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_West + 10);
    SD_PlaySound(SND_RICOCHET);
  }
}


void R_SlugAttack(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_slug_walk1);
    ob->nothink = 12;
  }

  PLACESPRITE;
}


void R_GhostlySlugAttack(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_ghostlyslug1);
    ob->nothink = 12;
  }

  PLACESPRITE;
}


void R_RunningFire(objtype* ob)
{
  if (ob->xdir == 1 && ob->hitwest)
  {
    ChangeState(ob, &s_grenadeexplosion1);
  }
  else if (ob->xdir == -1 && ob->hiteast)
  {
    ChangeState(ob, &s_grenadeexplosion1);
  }
  else if (!ob->hitnorth)
  {
    ChangeState(ob, &s_grenadeexplosion1);
  }

  PLACESPRITE;
}


void SpawnBomb(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = bombobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 113;
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_bomb_idle);

  new->hitnorth = 1;
  new->ticcount =  US_RndT() / 32;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 10;
      break;

    default:
      new->health = 5;
      break;
  }
}


void T_Bomb(objtype* ob)
{
  Sint16 xdelta;

  ob->needtoreact = true;

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

    ob->yspeed = -32 - US_RndT() / 8;
    ob->xspeed = -32;
    ob->state = &s_bomb_attack1;
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

    ob->yspeed = -32 - US_RndT() / 8;
    ob->xspeed = 32;
    ob->state = &s_bomb_attack1;
    return;
  }
}


void R_Bomb(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_grenadeexplosion1);
  }

  PLACESPRITE;
}


void SpawnFireImp(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = fireimpobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 16*PIXGLOBAL;
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

  NewState(new, &s_fireimp_walk1);

  new->hitnorth = 1;
}


void T_FireImp(objtype* ob)
{
  if (player->right < ob->left || player->left > ob->right ||
      player->top > ob->bottom || player->bottom < ob->top)
  {
  }
  else
  {
    ob->state = &s_fireimp_fireform1;
  }
}


void T_FireImpFireForm(objtype* ob)
{
  if (US_RndT() > 240)
  {
    // Return to regular form
    ChangeState(ob, &s_fireimp_stand);
  }
}


void R_FireImp(objtype* ob)
{
  // Randomly turn into fire form - no-op if already in fire form
  if (US_RndT() > 200)
  {
    ChangeState(ob, &s_fireimp_fireform1);
  }

  if (ob->xdir == 1 && ob->hitwest)
  {
    ob->xdir = -1;
  }
  else if (ob->xdir == -1 && ob->hiteast)
  {
    ob->xdir = 1;
  }
  else if (!ob->hitnorth)
  {
    // Jump over gaps
    ob->x -= ob->xmove;
    ob->y -= ob->ymove;

    ob->yspeed = -(US_RndT() / 32 * 20);
    if (ob->yspeed < -60)
    {
      ob->yspeed = -60;
    }
    if (ob->yspeed > -30)
    {
      ob->yspeed = -30;
    }

    ob->xspeed = ob->xdir << 5;

    ChangeState(ob, &s_fireimp_jumping);
  }

  PLACESPRITE;
}


void R_FireImpJumping(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_fireimp_walk1);
  }

  PLACESPRITE;
}


void SpawnHedgehog(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = hedgehogobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 16*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;

  NewState(new, &s_hedgehog_roll1);

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 6;
      break;

    default:
      new->health = 3;
      break;
  }

  new->hitnorth = 1;
}


void T_HedgeHogRolling(objtype* ob)
{
  if (player->right < ob->left || player->left > ob->right ||
      player->top > ob->bottom || player->bottom < ob->top)
  {
  }
  else
  {
    ob->state = &s_hedgehog_wait1;
  }
}


void T_HedgeHogWaiting(objtype* ob)
{
  if (US_RndT() > 200)
  {
    ChangeState(ob, &s_hedgehog_roll1);
  }
}


void T_HedgeHogWaiting2(objtype* ob)
{
  if (US_RndT() > 160)
  {
    ob->xdir = 1;
  }
  else
  {
    ob->xdir = -1;
  }

  if (US_RndT() > 175)
  {
    ob->state = &s_hedgehog_roll1;
  }
}


void R_HedgeHog(objtype* ob)
{
  if (US_RndT() > 200)
  {
    ChangeState(ob, &s_hedgehog_wait1);
  }

  if (ob->xdir == 1 && ob->hitwest)
  {
    ob->xdir = -1;
  }
  else if (ob->xdir == -1 && ob->hiteast)
  {
    ob->xdir = 1;
  }
  else if (!ob->hitnorth)
  {
    // Jump over gaps
    ob->x -= ob->xmove;
    ob->y -= ob->ymove;

    ob->yspeed = -(US_RndT() / 32 * 20);
    if (ob->yspeed < -60)
    {
      ob->yspeed = -60;
    }
    if (ob->yspeed > -30)
    {
      ob->yspeed = -30;
    }

    ob->xspeed = ob->xdir << 5;

    ChangeState(ob, &s_hedgehog_jumping);
  }

  PLACESPRITE;
}


void R_HedgeHogJumping(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_hedgehog_roll1);
  }

  PLACESPRITE;
}


void SpawnBrawler(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = brawlerobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 24*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_brawler_walk1);

  new->hitnorth = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 10;
      break;

    default:
      new->health = 5;
      break;
  }
}


void T_Brawler(objtype* ob)
{
  Sint16 xdelta;

  if (ob->top > player->bottom || ob->bottom < player->top)
    return;

  if (ob->xdir == -1)
  {
    xdelta = ob->left - player->right;

    if (xdelta > 64*PIXGLOBAL)
      return;

    if (xdelta < -16*PIXGLOBAL)
    {
      ob->xdir = 1;
      return;
    }
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta > 64*PIXGLOBAL)
      return;

    if (xdelta < -16*PIXGLOBAL)
    {
      ob->xdir = -1;
      return;
    }
  }

  if (player->right < ob->left || player->left > ob->right ||
      player->top > ob->bottom || player->bottom < ob->top)
    return;

  ob->state = &s_brawler_attack1;
}


void SpawnCeilingWalker(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = ceilingwalkerobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_ceilwalker_walkceil1);

  new->hitnorth = 1;
  new->ticcount =  US_RndT() / 32;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 3;
      break;

    default:
      new->health = 1;
      break;
  }
}


void T_CeilingWalkerOnCeiling(objtype* ob)
{
  if (ob->xdir == -1)
  {
    if (player->right < ob->left || player->left > ob->right ||
        player->bottom < ob->top)
      return;

    if (!ob->hitnorth)
    {
      ob->yspeed = 24 - US_RndT() / 16;
      SD_PlaySound(SND_CEILWALKERFALL);
      ob->state = &s_ceilwalker_falling;
      return;
    }
  }
  else
  {
    if (player->right < ob->left || player->left > ob->right ||
        player->bottom < ob->top)
      return;

    if (!ob->hitnorth)
    {
      ob->yspeed = 24 - US_RndT() / 16;
      SD_PlaySound(SND_CEILWALKERFALL);
      ob->state = &s_ceilwalker_falling;
      return;
    }
  }
}


void T_CeilingWalkerOnFloor(objtype* ob)
{
  if (ob->xdir == -1)
  {
    if (!ob->hitnorth)
    {
      ob->yspeed = 24 - US_RndT() / 16;
      SD_PlaySound(SND_CEILWALKERFALL);
      ob->state = &s_ceilwalker_falling;
      return;
    }
  }
  else
  {
    if (!ob->hitnorth)
    {
      ob->yspeed = 24 - US_RndT() / 16;
      SD_PlaySound(SND_CEILWALKERFALL);
      ob->state = &s_ceilwalker_falling;
      return;
    }
  }
}


void R_CeilingWalkerFalling(objtype* ob)
{
  if (ob->hitnorth)
  {
    SD_PlaySound(SND_CEILWALKERLAND);
    ChangeState(ob, &s_ceilwalker_walkfloor1);
    ob->nothink = 12;
  }

  PLACESPRITE;
}


void SpawnCrawlingSlime(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = crawlingslimeobj;
  new->priority = 2;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_crawlslime2);

  new->hitnorth = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 3;
      break;

    default:
      new->health = 1;
      break;
  }
}


void T_CrawlingSlime(objtype* ob)
{
  if (US_RndT() > 250)
  {
    ob->state = &s_crawlslime1;
  }

  if (ob->top > player->bottom || ob->bottom < player->top)
    return;

  if (player->right < ob->left || player->left > ob->right ||
      player->top > ob->bottom || player->bottom < ob->top)
    return;

  ob->state = &s_crawlslime_steppedon;
}
