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

#ifndef BM_ACT_H
#define BM_ACT_H

#include "BM_DEF.H"


#define PLACESPRITE \
  RF_PlaceSprite(&ob->sprite, ob->x, ob->y, ob->shapenum, \
    ob->dmgflash ? maskdraw : spritedraw, ob->priority);


void C_GrenadeExplosion(objtype* ob, objtype* hit);
void SpawnShot(Uint16 x, Uint16 y, Sint16 dir);


extern Uint16 bounceangle[8][8];
extern boolean firerobopal;

extern statetype far s_grenadeexplosion1;
extern statetype far s_robopalactive1;

extern statetype far s_pickup1;
extern statetype far s_pickup2;
extern statetype far s_pickuprise;
extern statetype far s_robopalwait1;
extern statetype far s_robopalwait2;
extern statetype far s_robopalactive1;
extern statetype far s_robopalactive2;
extern statetype far s_robopal_teleport1;
extern statetype far s_robopal_teleport2;
extern statetype far s_robopal_teleport3;
extern statetype far s_robopal_teleport4;
extern statetype far s_robopal_teleport5;
extern statetype far s_slug_walk1;
extern statetype far s_slug_walk2;
extern statetype far s_slug_attack;
extern statetype far s_running_fire1;
extern statetype far s_running_fire2;
extern statetype far s_ghostlyslug1;
extern statetype far s_ghostlyslug2;
extern statetype far s_ghostlyslug_attack;
extern statetype far s_bomb_idle;
extern statetype far s_bomb_attack1;
extern statetype far s_bomb_attack2;
extern statetype far s_bomb_attack3;
extern statetype far s_fireimp_walk1;
extern statetype far s_fireimp_walk2;
extern statetype far s_fireimp_walk3;
extern statetype far s_fireimp_walk4;
extern statetype far s_fireimp_fireform1;
extern statetype far s_fireimp_fireform2;
extern statetype far s_fireimp_stand;
extern statetype far s_fireimp_jumping;
extern statetype far s_hedgehog_roll1;
extern statetype far s_hedgehog_roll2;
extern statetype far s_hedgehog_roll3;
extern statetype far s_hedgehog_roll4;
extern statetype far s_hedgehog_wait1;
extern statetype far s_hedgehog_wait2;
extern statetype far s_hedgehog_jumping;
extern statetype far s_brawler_stand;
extern statetype far s_brawler_walk1;
extern statetype far s_brawler_walk2;
extern statetype far s_brawler_walk3;
extern statetype far s_brawler_walk4;
extern statetype far s_brawler_attack1;
extern statetype far s_brawler_attack2;
extern statetype far s_ceilwalker_walkceil1;
extern statetype far s_ceilwalker_walkceil2;
extern statetype far s_ceilwalker_walkceil3;
extern statetype far s_ceilwalker_walkceil4;
extern statetype far s_ceilwalker_walkfloor1;
extern statetype far s_ceilwalker_walkfloor2;
extern statetype far s_ceilwalker_walkfloor3;
extern statetype far s_ceilwalker_walkfloor4;
extern statetype far s_ceilwalker_falling;
extern statetype far s_crawlslime1;
extern statetype far s_crawlslime2;
extern statetype far s_crawlslime3;
extern statetype far s_crawlslime_steppedon;

#endif
