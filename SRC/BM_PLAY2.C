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


Uint16 bounceangle[8][8] = {
  { 0,  0,  0,  0,  0,  0,  0,  0},
  { 7,  6,  5,  4,  3,  2,  1,  0},
  { 5,  4,  3,  2,  1,  0, 15, 14},
  { 5,  4,  3,  2,  1,  0, 15, 14},
  { 3,  2,  1,  0, 15, 14, 13, 12},
  { 9,  8,  7,  6,  5,  4,  3,  2},
  { 9,  8,  7,  6,  5,  4,  3,  2},
  {11, 10,  9,  8,  7,  6,  5,  4}
};

Sint16 bonuspoints[] = {
  100, 200, 500, 800, 1000, 1500, 2000, 5000, 20000, 50000
};


Uint8 unktime;
Uint16 colorstep;
Sint16 doordestx;
Sint16 doordesty;
Uint16 jumptime;


void R_Chunk(objtype* ob);
void C_Fireball(objtype* ob, objtype* hit);
void R_Fireball(objtype* ob);
void T_GrenadeExplosion(objtype* ob);
void C_Grenade(objtype* ob, objtype* hit);
void C_GrenadeExplosion(objtype* ob, objtype* hit);
void R_Grenade(objtype* ob);
void C_Shot(objtype* ob, objtype* hit);
void C_LaserShot(objtype* ob, objtype* hit);
void ExplodeShot(objtype* ob);
void T_Shot(objtype* ob);
void R_Shot(objtype* ob);
void R_SuperPlasmaBolt(objtype* ob);


statetype far s_score = { /* 30d00 */
  0, 0, think, false, ps_none, 0, 0, 0,
  NULL, NULL, NULL, NULL};

statetype far s_bulletimpact1 = { /* 30d20 */
  BULLET_IMPACT1_SPR, BULLET_IMPACT1_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_bulletimpact2};

statetype far s_bulletimpact2 = { /* 30d40 */
  BULLET_IMPACT2_SPR, BULLET_IMPACT2_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_bulletimpact3};

statetype far s_bulletimpact3 = { /* 30d60 */
  BULLET_IMPACT3_SPR, BULLET_IMPACT3_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_gib_bone1 = { /* 30d80 */
  GIBS_BONE1_SPR, GIBS_BONE1_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_gib_bone2};

statetype far s_gib_bone2 = { /* 30da0 */
  GIBS_BONE2_SPR, GIBS_BONE2_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_gib_bone1};

statetype far s_gib_eyeball1 = { /* 30dc0 */
  GIBS_EYEBALL1_SPR, GIBS_EYEBALL1_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_gib_eyeball2};

statetype far s_gib_eyeball2 = { /* 30de0 */
  GIBS_EYEBALL2_SPR, GIBS_EYEBALL2_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_gib_eyeball1};

statetype far s_gib_flesh1 = { /* 30e00 */
  GIBS_FLESH1_SPR, GIBS_FLESH1_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_gib_flesh2};

statetype far s_gib_flesh2 = { /* 30e20 */
  GIBS_FLESH2_SPR, GIBS_FLESH2_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_gib_flesh1};

statetype far s_gibs_on_floor = { /* 30e40 */
  GIBS1_SPR, GIBS2_SPR,
  stepthink, false, ps_none, 100, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_metal_debris1 = { /* 30e60 */
  METAL_DEBRIS1_SPR, METAL_DEBRIS5_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_metal_debris2};

statetype far s_metal_debris2 = { /* 30e80 */
  METAL_DEBRIS2_SPR, METAL_DEBRIS6_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_metal_debris3};

statetype far s_metal_debris3 = { /* 30ea0 */
  METAL_DEBRIS3_SPR, METAL_DEBRIS7_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_metal_debris4};

statetype far s_metal_debris4 = { /* 30ec0 */
  METAL_DEBRIS4_SPR, METAL_DEBRIS8_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, R_Chunk, &s_metal_debris1};

statetype far s_metal_debris_on_floor = { /* 30ee0 */
  METAL_DEBRIS4_SPR, METAL_DEBRIS8_SPR,
  stepthink, false, ps_none, 100, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_fireball1 = { /* 30f00 */
  FIREBALL1_SPR, FIREBALL5_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, C_Fireball, R_Fireball, &s_fireball2};

statetype far s_fireball2 = { /* 30f20 */
  FIREBALL2_SPR, FIREBALL6_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, C_Fireball, R_Fireball, &s_fireball3};

statetype far s_fireball3 = { /* 30f40 */
  FIREBALL3_SPR, FIREBALL7_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, C_Fireball, R_Fireball, &s_fireball4};

statetype far s_fireball4 = { /* 30f60 */
  FIREBALL4_SPR, FIREBALL8_SPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, C_Fireball, R_Fireball, &s_fireball1};

statetype far s_grenade1 = { /* 30f80 */
  GRENADE_GREEN1_SPR, GRENADE_GREEN1_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_grenade2};

statetype far s_grenade2 = { /* 30fa0 */
  GRENADE_GREEN2_SPR, GRENADE_GREEN2_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_grenade3};

statetype far s_grenade3 = { /* 30fc0 */
  GRENADE_GREEN3_SPR, GRENADE_GREEN3_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_grenade4};

statetype far s_grenade4 = { /* 30fe0 */
  GRENADE_GREEN4_SPR, GRENADE_GREEN4_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_grenade1};

statetype far s_redgrenade1 = { /* 31000 */
  GRENADE_RED1_SPR, GRENADE_RED1_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_redgrenade2};

statetype far s_redgrenade2 = { /* 31020 */
  GRENADE_RED2_SPR, GRENADE_RED2_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_redgrenade3};

statetype far s_redgrenade3 = { /* 31040 */
  GRENADE_RED3_SPR, GRENADE_RED3_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_redgrenade4};

statetype far s_redgrenade4 = { /* 31060 */
  GRENADE_RED4_SPR, GRENADE_RED4_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_redgrenade1};

statetype far s_grenadeexplosion1 = { /* 31080 */
  GRENADE_EXPLOSION1_SPR, GRENADE_EXPLOSION1_SPR,
  step, false, ps_none, 10, 0, 0,
  T_GrenadeExplosion, C_GrenadeExplosion, R_Draw, &s_grenadeexplosion2};

statetype far s_grenadeexplosion2 = { /* 310a0 */
  GRENADE_EXPLOSION2_SPR, GRENADE_EXPLOSION2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_grenadeexplosion3};

statetype far s_grenadeexplosion3 = { /* 310c0 */
  GRENADE_EXPLOSION3_SPR, GRENADE_EXPLOSION3_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_grenadeexplosion4};

statetype far s_grenadeexplosion4 = { /* 310e0 */
  GRENADE_EXPLOSION4_SPR, GRENADE_EXPLOSION4_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_grenadeexplosion5};

statetype far s_grenadeexplosion5 = { /* 31100 */
  GRENADE_EXPLOSION5_SPR, GRENADE_EXPLOSION5_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_grenadeexplosion6};

statetype far s_grenadeexplosion6 = { /* 31120 */
  GRENADE_EXPLOSION6_SPR, GRENADE_EXPLOSION6_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, NULL};

statetype far s_robopalrocket1 = { /* 31140 */
  ROBOPAL_SHOT1_L_SPR, ROBOPAL_SHOT1_R_SPR,
  slide, false, ps_none, 6, 64, 64,
  T_Shot, C_Shot, R_Shot, &s_robopalrocket2};

statetype far s_robopalrocket2 = { /* 31160 */
  ROBOPAL_SHOT2_L_SPR, ROBOPAL_SHOT2_R_SPR,
  slide, false, ps_none, 6, 64, 64,
  T_Shot, C_Shot, R_Shot, &s_robopalrocket1};

statetype far s_lasershot = { /* 31180 */
  LASER_BLAST_RED_SPR, LASER_BLAST_RED_SPR,
  slide, false, ps_none, 6, 64, 64,
  T_Shot, C_LaserShot, R_Shot, &s_lasershot};

statetype far s_superplasmabolt = { /* 311a0 */
  SUPER_BLAST_L_SPR, SUPER_BLAST_R_SPR,
  slide, false, ps_none, 2, 64, 64,
  T_Shot, C_LaserShot, R_SuperPlasmaBolt, &s_superplasmabolt};

statetype far s_rocketimpact1 = { /* 311c0 */
  ROCKET_IMPACT1_SPR, ROCKET_IMPACT1_SPR,
  step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_rocketimpact2};

statetype far s_rocketimpact2 = { /* 311e0 */
  ROCKET_IMPACT2_SPR, ROCKET_IMPACT2_SPR,
  step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_plasmaboltimpact1 = { /* 31200 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_plasmaboltimpact2};

statetype far s_plasmaboltimpact2 = { /* 31220 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, NULL};



void SnakeContact(objtype* ob, objtype* hit)
{
  switch (hit->obclass)
  {
    case pickupobj:
      switch (hit->temp1)
      {
        case 9:
          SD_PlaySound(SND_COLLECTAMMO);
          hit->shapenum = GRENADE_GREEN1_SPR;

          gamestate.explosives.grenades++;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsggrenades)
          {
            ShowHelpMessage("Throw grenades to blow up monsters!\n");
            gamestate.helpmsggrenades = true;
          }
          break;

        case 16:
          SD_PlaySound(SND_COLLECTAMMO);
          hit->shapenum = PICKUP_GUN1_SPR;

          if (gamestate.ammoinclip > 0 || gamestate.ammotype != 0)
          {
            gamestate.clips++;
          }
          else
          {
            gamestate.rapidfire = 1;

            if (gamestate.difficulty == gd_Hard)
            {
              gamestate.ammoinclip = 45;
            }
            else
            {
              gamestate.ammoinclip = 90;
            }
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsgclips)
          {
            ShowHelpMessage("Collect machine guns for automatic fire.\n");
            gamestate.helpmsgclips = true;
          }
          break;

        case 17:
          if (c.yaxis == -1)
          {
            SD_PlaySound(SND_COLLECTKEY);
            hit->shapenum = PICKUP_KEYCARD1_SPR;

            gamestate.keyitems.keycards++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);

            if (!gamestate.helpmsgkeycards)
            {
              ShowHelpMessage("Use keycards to turn off electric beams.\n");
              gamestate.helpmsgkeycards = true;
            }
          }
          break;

        case 18:
          SD_PlaySound(SND_COLLECTKEY);
          hit->shapenum = PICKUP_KEY1_SPR;

          gamestate.keyitems.keys++;

          hit->obclass = inertobj;
          hit->priority = 3;

          if (!gamestate.helpmsgdoors)
          {
            ShowHelpMessage("Push <UP> and use key to open door.\n");
            gamestate.helpmsgdoors = true;
          }

          ChangeState(hit, &s_pickuprise);
          break;

        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
          if (c.yaxis == -1)
          {
            SD_PlaySound(SND_COLLECTAMMO);
            hit->shapenum = POINTS_100_SPR + hit->temp1 - 19;

            GivePoints(bonuspoints[hit->temp1 - 19]);

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);
          }
          break;

        case 25:
          if (c.yaxis == -1)
          {
            SD_PlaySound(SND_COLLECTONEUP);
            hit->shapenum = ONE_UP_SPR;

            if (gamestate.lives < 9)
            {
              gamestate.lives++;
            }

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);
          }
          break;

        case 26:
          if (c.yaxis == -1 || gamestate.mapon == 6 || gamestate.mapon == 11)
          {
            SD_PlaySound(SND_COLLECTKEY);
            hit->shapenum = PICKUP_SHARD_BLUE1_SPR;

            gamestate.blueshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);

            if (!gamestate.helpmsgshards)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.helpmsgshards = true;
            }
          }
          break;

        case 27:
          if (c.yaxis == -1)
          {
            SD_PlaySound(SND_COLLECTKEY);
            hit->shapenum = PICKUP_SHARD_GREEN1_SPR;

            gamestate.greenshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);

            if (!gamestate.helpmsgshards)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.helpmsgshards = true;
            }
          }
          break;

        case 28:
          if (c.yaxis == -1)
          {
            SD_PlaySound(SND_COLLECTKEY);
            hit->shapenum = PICKUP_SHARD_RED1_SPR;

            gamestate.redshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);

            if (!gamestate.helpmsgshards)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.helpmsgshards = true;
            }
          }
          break;

        case 29:
          if (c.yaxis == -1)
          {
            SD_PlaySound(SND_COLLECTKEY);
            hit->shapenum = PICKUP_SHARD_CYAN1_SPR;

            gamestate.cyanshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);

            if (!gamestate.helpmsgshards)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.helpmsgshards = true;
            }
          }
          break;

        case 30:
          if (c.yaxis == -1)
          {
            SD_PlaySound(SND_COLLECTKEY);
            hit->shapenum = PICKUP_SPECIALKEY1_SPR;

            gamestate.specialkey++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_pickuprise);

            ShowHelpMessage("Hmm....What a strange key!\n");
          }
          break;

        case 36:
          hit->shapenum = PICKUP_GRENADE_RED1_SPR;
          SD_PlaySound(SND_COLLECTAMMO);

          gamestate.explosives.redgrenades++;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsggrenades)
          {
            ShowHelpMessage("Throw grenades to blow up monsters!\n");
            gamestate.helpmsggrenades = true;
          }
          break;

        case 37:
          SD_PlaySound(SND_COLLECTKEY);
          hit->shapenum = PICKUP_AMMO_SUPER1_SPR;

          gamestate.rapidfire = true;
          gamestate.ammotype = AMMO_SUPERBULLET;

          if (gamestate.ammoinclip > 0)
          {
            gamestate.clips++;
          }

          if (gamestate.difficulty == gd_Hard)
          {
            gamestate.ammoinclip = 45;
          }
          else
          {
            gamestate.ammoinclip = 90;
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsgsupergun)
          {
            ShowHelpMessage("Super Gun!  Bullets do 5x the damage!\n");
            gamestate.helpmsgsupergun = true;
          }
          break;

        case 38:
          SD_PlaySound(SND_COLLECTBONUS);
          hit->shapenum = PICKUP_LANDMINES1_SPR;

          if (gamestate.difficulty == gd_Hard)
          {
            gamestate.explosives.landmines = 5;
          }
          else
          {
            gamestate.explosives.landmines = 10;
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsglandmines)
          {
            ShowHelpMessage("Cool!  Land mines!\n");
            gamestate.helpmsglandmines = true;
          }
          break;

        case 39:
          SD_PlaySound(SND_COLLECTBONUS);
          hit->shapenum = PICKUP_AMMO_PLASMA1_SPR;

          gamestate.rapidfire = false;
          gamestate.ammotype = AMMO_PLASMABOLT;

          if (gamestate.ammoinclip > 0)
          {
            gamestate.clips++;
          }

          if (gamestate.difficulty == gd_Hard)
          {
            gamestate.ammoinclip = 10;
          }
          else
          {
            gamestate.ammoinclip = 20;
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsgplasmabolts)
          {
            ShowHelpMessage("Plasma Bolts!  Burn holes through enemies!\n");
            gamestate.helpmsgplasmabolts = true;
          }
          break;

        case 52:
          SD_PlaySound(SND_COLLECTBONUS);
          hit->shapenum = PICKUP_LIFEGEM1_SPR;

          gamestate.gems++;

          hit->obclass = inertobj;
          hit->priority = 3;

          if (gamestate.gems == 50)
          {
            gamestate.lives++;
            gamestate.gems = 0;
            SD_PlaySound(SND_COLLECTONEUP);

            hit->shapenum = ONE_UP_SPR;
          }

          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsggems)
          {
            ShowHelpMessage("Collect 50 gems for an extra life!\n");
            gamestate.helpmsggems = true;
          }
          break;

        case 53:
          SD_PlaySound(SND_COLLECTBONUS); // NOTE: Unnecessary
          hit->shapenum = PICKUP_HEALTH1_SPR;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          SD_PlaySound(SND_COLLECTHEALTH);

          switch (gamestate.difficulty)
          {
            case gd_Easy:
              player->health = 8;
              break;

            case gd_Normal:
              player->health = 4;
              break;

            case gd_Hard:
              player->health = 2;
              break;

            default:
              player->health = 4;
              break;
          }

          gamestate.maxhealth = player->health;

          if (!gamestate.helpmsghealth)
          {
            ShowHelpMessage("First Aid Kit restores you to full health.\n");
            gamestate.helpmsghealth = true;
          }
          break;

        case 54:
          SD_PlaySound(SND_COLLECTONEUP);
          hit->shapenum = PICKUP_SECRETLEVELGEM1_SPR;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          gamestate.secretlevelgem = true;

          if (!gamestate.helpmsgsecretlevelgem)
          {
            ShowHelpMessage("You found a secret level warp gem!\n");
            gamestate.helpmsgsecretlevelgem = true;
          }
          break;

        case 75:
          SD_PlaySound(SND_COLLECTBONUS);
          hit->shapenum = PICKUP_NUKE1_SPR;

          gamestate.nukestate = ns_collected;

          hit->obclass = inertobj;
          hit->priority = 3;

          ShowHelpMessage("Oh look! What a cute little nuclear bomb!\n");

          ChangeState(hit, &s_pickuprise);
          break;

        case 76:
          SD_PlaySound(SND_COLLECTBONUS);
          hit->shapenum = PICKUP_RADPILL1_SPR;

          gamestate.radpill = true;

          hit->obclass = inertobj;
          hit->priority = 3;

          ShowHelpMessage("It's an anti-radiation pill!\n");

          ChangeState(hit, &s_pickuprise);
          break;

        case 77:
          SD_PlaySound(SND_COLLECTPOTION);
          hit->shapenum = PICKUP_INVINCIBILITY1_SPR;

          gamestate.potions++;

          if (gamestate.potions >= 1)
          {
            gamestate.potions = 0;
            invincible = 1500;

            StartMusic(INVINCIBLEMUSIC);
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);

          if (!gamestate.helpmsginvincible)
          {
            ShowHelpMessage("Now you're invincible to monster attacks!\n");
            gamestate.helpmsginvincible = true;
          }
          break;

        case 78:
          SD_PlaySound(SND_COLLECTVALUABLEITEM);
          hit->shapenum = POINTS_5000_SPR;

          GivePoints(5000);

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);
          break;

        case 79:
          SD_PlaySound(SND_COLLECTVALUABLEITEM);
          hit->shapenum = POINTS_50000_SPR;

          GivePoints(50000);

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);
          break;

        case 80:
          SD_PlaySound(SND_COLLECTKEY);

          gamestate.exitkey = true;

          hit->shapenum = PICKUP_EXITKEY1_SPR;
          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_pickuprise);
          break;

      }
      break;

    case platformobj:
      if (!gamestate.riding)
      {
        ClipToSpriteTop(ob, hit);
      }
      break;

    case hostageobj:
      gamestate.hostagerescued = true;

      HostageDialog();

      SD_PlaySound(SND_COLLECTAMMO);

      hit->shapenum = POINTS_5000_SPR;

      GivePoints(bonuspoints[7]);

      hit->obclass = pickupobj;
      hit->ydir = -1;
      ChangeState(hit, &s_pickuprise);
      SpawnPickup(ob->tilemidx, ob->tiletop, 80);
      break;

    case obclass_29:
      gamestate.trianglekeys++;

      SD_PlaySound(SND_COLLECTAMMO);

      hit->shapenum = PICKUP_TRIANGLE2_SPR;
      hit->obclass = pickupobj;
      hit->ydir = -1;
      ChangeState(hit, &s_pickuprise);
      break;

    case robopalobj:
      if (!gamestate.hasrobopal && (invincible == 0 || invincible > 50))
      {
        SD_PlaySound(SND_COLLECTVALUABLEITEM);

        gamestate.hasrobopal = true;

        ChangeState(hit, &s_robopalactive1);
      }

      if (!gamestate.helpmsgrobopal)
      {
        ShowHelpMessage("RoboPal gives you extra fire power!\n");
        gamestate.helpmsgrobopal = true;
      }
      break;

    case tankbotobj:
      DamagePlayer(ob, 50);
      break;

    case pushblockobj:
      if (gamestate.mapon != 13)
      {
        ClipToPushBlock(ob, hit, false);
      }
      break;

    case bounderobj:
      ClipToSprite(ob, hit, false);
      break;

    case crushblockobj:
      ClipToSprite(ob, hit, true);
      break;

    case fireballobj:
    case slugobj:
    case obclass_8:
    case brawlerobj:
    case ceilingwalkerobj:
    case spittersnakeobj:
    case drmangleobj:
    case lasergunnerobj:
    case bouncebotobj:
    case slimedropperobj:
    case enemyprojectileobj:
    case obclass_26:
    case obclass_30:
    case sewermutantobj:
    case hedgehogobj:
    case skullmanobj:
    case skullmanhandobj:
    case bombobj:
    case crawlingslimeobj:
    case fireimpobj:
    case helicopterobj:
    case parachutebotobj:
      if (hit->spawnedby == sb_player) break;

      if (!invincible)
      {
        DamagePlayer(ob, 1);
      }
      break;
  }
}


void SpawnScoreBox(void)
{
  scoreobj->obclass = inertobj;
  scoreobj->active = ac_allways;
  scoreobj->needtoclip = cl_noclip;
  *((Sint32*)&scoreobj->temp1) = -1;
  scoreobj->temp3 = -1;
  scoreobj->temp4 = -1;
  scoreobj->temp5 = -1;
  scoreobj->temp6 = -1;

  NewState(scoreobj, &s_score);
}


void MemDrawChar(Sint16 char8, Uint8 far *dest, Uint16 width, Uint16 planesize)
{
  Uint16 source = (Uint16)grsegs[STARTTILE8];

  asm mov si,[char8]
  asm shl si,1
  asm shl si,1
  asm shl si,1
  asm shl si,1
  asm shl si,1    // index into char 8 segment

  asm mov ds,[WORD PTR source]
  asm mov es,[WORD PTR dest+2]

  asm mov cx,4    // draw four planes
  asm mov bx,[width]
  asm dec bx

planeloop:

  asm mov di,[WORD PTR dest]

  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb

  asm mov ax,[planesize]
  asm add [WORD PTR dest],ax

  asm loop  planeloop

  asm mov ax,ss
  asm mov ds,ax
}


void ShiftScore (void)
{
  spritetabletype far *spr;
  spritetype _seg *dest;

  spr = &spritetable[SCOREBOXSPR-STARTSPRITES];
  dest = (spritetype _seg *)grsegs[SCOREBOXSPR];

  CAL_ShiftSprite (FP_SEG(dest),dest->sourceoffset[0],
    dest->sourceoffset[1],spr->width,spr->height,2);

  CAL_ShiftSprite (FP_SEG(dest),dest->sourceoffset[0],
    dest->sourceoffset[2],spr->width,spr->height,4);

  CAL_ShiftSprite (FP_SEG(dest),dest->sourceoffset[0],
    dest->sourceoffset[3],spr->width,spr->height,6);
}


void ResetScoreBox(void)
{
  scoreobj->temp1 = scoreobj->temp2 = scoreobj->temp3 = scoreobj->temp4 =
    scoreobj->temp5 = scoreobj->temp6 = scoreobj->temp7 = -1;
}


void UpdateScoreBox(objtype *ob)
{
  char str[10];
  char* ch;
  spritetype _seg* block;
  Uint8 far* dest;
  Uint8 far* dest2;
  Uint16 i, width;
  boolean isodd;
  Uint16 length, planesize, number;
  boolean changed;

  changed = false;

  if (!showscorebox || gamestate.mapon == 12 || gamestate.mapon == 13)
    return;

  //
  // score changed, or practice timer active
  //
  if (
    (gamestate.score>>16) != ob->temp1 ||
    (Uint16)gamestate.score != ob->temp2 ||
    practicetimer > 0)
  {
    block = (spritetype _seg *)grsegs[SCOREBOXSPR];
    width = block->width[0];
    planesize = block->planesize[0];
    dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
      planesize + width*4;

    if (practicetimer > 0)
    {
      ltoa(practicetimer / 33, str, 10);
    }
    else
    {
      ltoa(gamestate.score, str, 10);
    }

    // erase leading spaces
    length = strlen(str);
    for (i=7; i>length; i--)
      MemDrawChar(0, dest+=CHARWIDTH, width, planesize);

    // draw digits
    ch = str;
    while (*ch)
      MemDrawChar(*ch++ - '0'+1, dest+=CHARWIDTH, width, planesize);

    // draw "TIME LEFT" label
    if (practicetimer > 0)
    {
      dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
        planesize + width*4 + CHARWIDTH;
      dest -= CHARWIDTH;

      for (i=1; i < 6; i++)
        MemDrawChar(i + 59, dest+=CHARWIDTH, width, planesize);
    }

    ShiftScore();
    ob->needtoreact = true;
    ob->temp1 = gamestate.score>>16;
    ob->temp2 = gamestate.score;
    changed = true;
  }

  //
  // health changed
  //
  number = player->health;
  if (number != ob->temp6)
  {
    if (number > 8)
      number = 8;

    block = (spritetype _seg *)grsegs[SCOREBOXSPR];
    width = block->width[0];
    planesize = block->planesize[0];
    dest2 = dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
      planesize + width*4 + 8*CHARWIDTH;

    for (i=4; i > 0; i--)
      MemDrawChar(0, dest2 += CHARWIDTH, width, planesize);

    if (number > 0)
    {
      for (i = 1; i <= number; i++)
      {
        isodd = i & 1;

        if (isodd)
        {
          if (i == 1)
            dest += CHARWIDTH;

          MemDrawChar(31, dest, width, planesize);
        }
        else
        {
          MemDrawChar(21, dest, width, planesize);
          dest += CHARWIDTH;
        }
      }
    }

    ShiftScore();
    ob->needtoreact = true;
    ob->temp6 = player->health;
    changed = true;
  }

  //
  // explosives type changed
  //
  if (gamestate.explosives.landmines > 0)
    number = gamestate.explosives.landmines;
  else if (gamestate.explosives.redgrenades > 0)
    number = gamestate.explosives.redgrenades;
  else
    number = gamestate.explosives.grenades;
  if (number != ob->temp3)
  {
    block = (spritetype _seg *)grsegs[SCOREBOXSPR];
    width = block->width[0];
    planesize = block->planesize[0];
    dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
      + planesize + width*20 + 4*CHARWIDTH;

    if (gamestate.explosives.landmines > 0)
      MemDrawChar(35, dest, width, planesize);
    else if (gamestate.explosives.redgrenades > 0)
      MemDrawChar(57, dest, width, planesize);
    else
      MemDrawChar(58, dest, width, planesize);

    ShiftScore();
    ob->needtoreact = true;
    changed = true;
  }

  //
  // explosives amount changed
  //
  if (gamestate.explosives.landmines > 0)
    number = gamestate.explosives.landmines;
  else if (gamestate.explosives.redgrenades > 0)
    number = gamestate.explosives.redgrenades;
  else
    number = gamestate.explosives.grenades;
  if (number != ob->temp3)
  {
    block = (spritetype _seg *)grsegs[SCOREBOXSPR];
    width = block->width[0];
    planesize = block->planesize[0];
    dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
      + planesize + width*20 + 5*CHARWIDTH;

    if (number > 99)
      strcpy(str, "99");
    else
      ltoa(number, str, 10);

    // erase leading spaces
    length = strlen(str);
    for (i=2;i >length;i --)
      MemDrawChar(0, dest+=CHARWIDTH, width, planesize);

    // draw digits
    ch = str;
    while (*ch)
      MemDrawChar(*ch++ - '0'+1, dest+=CHARWIDTH, width, planesize);

    ShiftScore();
    ob->needtoreact = true;

    if (gamestate.explosives.landmines)
      ob->temp3 = gamestate.explosives.landmines;
    else if (gamestate.explosives.redgrenades)
      ob->temp3 = gamestate.explosives.redgrenades;
    else
      ob->temp3 = gamestate.explosives.grenades;

    changed = true;
  }

  //
  // ammo type changed
  //
  if (gamestate.ammotype != ob->temp7)
  {
    block = (spritetype _seg *)grsegs[SCOREBOXSPR];
    width = block->width[0];
    planesize = block->planesize[0];
    dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
      + planesize + width*20 + 9*CHARWIDTH;

    if (gamestate.ammotype == AMMO_REGULAR)
      MemDrawChar(33, dest, width, planesize);
    else if (gamestate.ammotype == AMMO_SUPERBULLET)
      MemDrawChar(34, dest, width, planesize);
    else if (gamestate.ammotype == AMMO_PLASMABOLT)
      MemDrawChar(59, dest, width, planesize);

    ShiftScore();
    ob->needtoreact = true;
    ob->temp7 = gamestate.ammotype;
    changed = true;
  }

  //
  // ammo changed
  //
  number = gamestate.ammoinclip;
  if (gamestate.difficulty == gd_Easy && gamestate.ammoinclip <= 3 &&
      gamestate.ammotype == AMMO_REGULAR)
  {
    number = 0;
  }

  if (number != ob->temp5)
  {
    block = (spritetype _seg *)grsegs[SCOREBOXSPR];
    width = block->width[0];
    planesize = block->planesize[0];
    dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
      + planesize + width*20 + 10*CHARWIDTH;

    if (number > 99)
      strcpy(str, "99");
    else
      ltoa(number, str, 10);

    // erase leading spaces
    length = strlen(str);
    for (i=2;i >length;i --)
      MemDrawChar(0, dest+=CHARWIDTH, width, planesize);

    ch = str;
    if (number > 0)
    {
      // draw digits
      while (*ch)
        MemDrawChar(*ch++ - '0'+1, dest+=CHARWIDTH, width, planesize);
    }
    else
    {
      // draw ".."
      MemDrawChar(*ch++ - '0'+20, dest, width, planesize);
      MemDrawChar(0, dest+=CHARWIDTH, width, planesize);
    }

    ShiftScore();
    ob->needtoreact = true;

    if (gamestate.difficulty == gd_Easy)
    {
      ob->temp5 = -1;
    }
    else
    {
      ob->temp5 = gamestate.ammoinclip;
    }

    changed = true;
  }

  //
  // lives changed
  //
  if (gamestate.lives != ob->temp4)
  {
    block = (spritetype _seg *)grsegs[SCOREBOXSPR];
    width = block->width[0];
    planesize = block->planesize[0];
    dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
      + planesize + width*20 + 2*CHARWIDTH;

    if (gamestate.lives > 9)
    {
      MemDrawChar(10, dest, width, planesize);
    }
    else
    {
      MemDrawChar(gamestate.lives + 1, dest, width, planesize);
    }

    ShiftScore();
    ob->needtoreact = true;
    ob->temp4 = gamestate.lives;
    changed = true;
  }

  //
  // boss health bar changed
  //
  if (bosshealth > 0)
  {
    if (!hbardivisor)
      hbardivisor = 1;

    number = bosshealth / hbardivisor;

    if (number != lastbosshealth)
    {
      if (number > 20)
        number = 20;

      if (number <= 0)
        number = 1;

      block = (spritetype _seg *)grsegs[SCOREBOXSPR];
      width = block->width[0];
      planesize = block->planesize[0];
      dest2 = dest = (Uint8 far*)grsegs[SCOREBOXSPR] + block->sourceoffset[0] +
        + planesize + width*32 - 1*CHARWIDTH;
      dest2 += 3*CHARWIDTH;

      if (bosshealth == 999)
      {
        // clear health bar to empty
        bosshealth = -1;
        MemDrawChar(72, dest += CHARWIDTH, width, planesize);

        for (i = 0; i < 12; i++)
        {
          MemDrawChar(71, dest += CHARWIDTH, width, planesize);
        }
      }
      else
      {
        // draw "BOSS" label
        for (i = 0; i < 3; i++)
        {
          MemDrawChar(i + 66, dest += CHARWIDTH, width, planesize);
        }

        dest = dest2;

        // clear bar
        for (i = 0; i < 10; i++)
        {
          MemDrawChar(71, dest2 += CHARWIDTH, width, planesize);
        }

        // draw bar
        if (number > 0)
        {
          for (i = 1; i <= number; i++)
          {
            isodd = i & 1;

            if (isodd)
            {
              if (i == 1)
                dest += CHARWIDTH;

              MemDrawChar(70, dest, width, planesize);
            }
            else
            {
              MemDrawChar(69, dest, width, planesize);
              dest += CHARWIDTH;
            }
          }
        }
      }

      ShiftScore();
      ob->needtoreact = true;
      changed = true;
    }
  }

  if (ob->x != originxglobal || ob->y != originyglobal)
  {
    ob->x = originxglobal;
    ob->y = originyglobal;
    changed = true;
  }

  if (changed)
  {
    RF_PlaceSprite(
       &ob->sprite,
       ob->x + 4*PIXGLOBAL,
       ob->y + 4*PIXGLOBAL,
       SCOREBOXSPR,
       spritedraw,
       3);
  }
}


void DealDamage(objtype* ob, Sint16 amount)
{
  Sint16 points = 0;

  ob->health = ob->health - amount;
  ob->needtoreact = true;

  if (ob->health <= 0)
  {

    switch (ob->obclass)
    {
      case slugobj:
      case ceilingwalkerobj:
      case obclass_29:
      case obclass_30:
      case crawlingslimeobj:
        points = 50;
        break;

      case obclass_8:
      case hedgehogobj:
        points = 100;
        break;

      case spittersnakeobj:
        points = 200;
        break;

      case brawlerobj:
      case sewermutantobj:
      case fireimpobj:
        points = 500;
        break;

      case tankbotobj:
        points = 2000;
        ob->shootable = 0;
        break;

      case lasergunnerobj:
        points = 800;
        ob->shootable = 0;
        break;

      case bouncebotobj:
        points = 350;
        ob->shootable = 0;
        break;

      case laserturretobj:
        points = 500;
        ob->shootable = 0;
        break;

      case slimedropperobj:
        points = 500;
        break;

      case drmangleobj:
        points = 34464;
        ob->shootable = 0;
        SD_PlaySound(SND_ROAR);
        ob->obclass = inertobj;
        bosshealth = 999;
        break;

      case skullmanobj:
        points = 5000;
        ob->shootable = 0;
        SpawnPickup(ob->tilemidx, ob->tiletop, 26);
        StartMusic(VICTORYMUSIC);
        skullmanactivestate = 1;
        bosshealth = 999;
        break;

      case skullmanhandobj:
        points = 1000;
        ob->shootable = 0;
        break;

      case helicopterobj:
        points = 1000;
        ob->shootable = 0;
        break;
    }

    if (
      ob->obclass == bouncebotobj ||
      ob->obclass == laserturretobj ||
      ob->obclass == drmangleobj ||
      ob->obclass == bombobj ||
      ob->obclass == helicopterobj)
    {
      SpawnBigExplosion(ob->x, ob->y + 16*PIXGLOBAL);

      // NOTE: I have no clue why this is done via a `goto` like this, it would
      // be much clearer to move the code in the `else` block to after the
      // `if`/`else` and remove the `else` block.
      //
      // If there is a way to get the compiler to produce identical assembly
      // without using a `goto`, I haven't found it yet.
      goto spawnGibs;
    }
    else
    {
spawnGibs:
      ChunkBloom(ob, ob->midx, ob->y, dir_North);
      ChunkBloom(ob, ob->midx, ob->y, dir_South);
      ChunkBloom(ob, ob->midx, ob->y, dir_East);
      ChunkBloom(ob, ob->midx, ob->y, dir_West);

      if (ob->obclass != tankbotobj && ob->obclass != inertobj)
      {
        RemoveObj(ob);
      }
    }


    GivePoints(points);
  }
  else
  {
    if (player->obclass == 18)
    {
      ob->dmgflash = 10;
    }
    else
    {
      ob->dmgflash = 4;
    }

    if ((ob->obclass == skullmanobj || ob->obclass == skullmanhandobj) &&
        skullmanactivestate < 0)
    {
      skullmanactivestate++;
    }
  }
}


void SpawnBulletImpact(Uint16 x, Uint16 y)
{
  GetNewObj(true);
  new->obclass = inertobj;
  new->active = ac_removable;
  new->x = x - 4*PIXGLOBAL;
  new->y = y - 4*PIXGLOBAL;
  new->priority = 3;

  if (gamestate.ammotype == AMMO_SUPERBULLET ||
      gamestate.ammotype == AMMO_PLASMABOLT)
  {
    NewState(new, &s_bigshotimpact1);
  }
  else
  {
    NewState(new, &s_bulletimpact1);
  }
}


void FireBullet(Uint16 x, Uint16 y, Sint16 xdir, Sint16 damage)
{
  objtype* ob;
  Uint16 tilex, tiley;
  Uint16 maptile;
  Uint16 top, bottom;
  Uint16 i;

  if (gamestate.ammoinclip > 0)
  {
    if (gamestate.difficulty == gd_Easy && gamestate.ammoinclip <= 1)
    {
      if (gamestate.ammotype == AMMO_SUPERBULLET ||
          gamestate.ammotype == AMMO_PLASMABOLT)
      {
        gamestate.ammotype = AMMO_REGULAR;
      }

      if (gamestate.clips > 0)
      {
        gamestate.ammoinclip = 90;
        gamestate.clips--;
      }
    }

    if (gamestate.ammotype != AMMO_PLASMABOLT)
    {
      SD_PlaySound(SND_PLAYERGUN);
    }

    gamestate.ammoinclip--;

    if (gamestate.ammotype == AMMO_REGULAR)
    {
      gamestate.rapidfire = true;
    }

    if ((gamestate.ammoinclip & 1) && gamestate.hasrobopal)
    {
      firerobopal = true;
    }
  }
  else
  {
    if (gamestate.ammotype == AMMO_SUPERBULLET ||
        gamestate.ammotype == AMMO_PLASMABOLT)
    {
      gamestate.ammotype = AMMO_REGULAR;
    }

    if (gamestate.clips > 0)
    {
      gamestate.ammoinclip = 90;
      gamestate.clips--;
      return;
    }

    if (gamestate.ammotype != AMMO_PLASMABOLT)
    {
      SD_PlaySound(SND_PLAYERGUN);
    }

    gamestate.rapidfire = false;

    if (gamestate.hasrobopal)
    {
      firerobopal = true;
    }
  }

  tilex = CONVERT_GLOBAL_TO_TILE(x);
  tiley = CONVERT_GLOBAL_TO_TILE(y);
  top = y - 4*PIXGLOBAL;
  bottom = y + 4*PIXGLOBAL;
  i = 20;

  if (gamestate.ammotype == AMMO_PLASMABOLT)
  {
    SpawnLaserShot(x, y - 2*PIXGLOBAL, xdir);
    return;
  }

  do
  {
    // Check if we've hit an actor
    for (ob = player->next; ob; ob = ob->next)
    {
      if (
        ob->active && ob->shootable &&
        ob->tileleft <= tilex && ob->tileright >= tilex &&
        ob->top <= bottom && ob->bottom >= top)
      {
        SpawnBulletImpact(ob->midx, y);

        // Check if actor is invulnerable to bullets
        switch (ob->obclass)
        {
          case fireimpobj:
            if (ob->state == &s_fireimp_fireform1 ||
                ob->state == &s_fireimp_fireform2)
            {
              return;
            }
            break;

          case bombobj:
          case pushblockobj:
          case crushblockobj:
          case crawlingslimeobj:
            return;
        }

        if (gamestate.ammotype == AMMO_SUPERBULLET)
        {
          DealDamage(ob, 2);
        }
        else
        {
          DealDamage(ob, damage);
        }

        return;
      }
    }

    // Check if we've hit a wall
    maptile = *(mapsegs[1] + mapbwidthtable[tiley]/2 + tilex);

    if ((tinf[NORTHWALL + maptile] & 7) > 1 || (tinf[SOUTHWALL + maptile] & 7) > 1)
    {
      SpawnBulletImpact(CONVERT_TILE_TO_GLOBAL(tilex) + 8*PIXGLOBAL, y);

      if (US_RndT() < 16)
      {
        SD_PlaySound(SND_RICOCHET);
      }

      return;
    }

    if (xdir == -1)
    {
      if (tinf[EASTWALL + maptile])
      {
        SpawnBulletImpact(CONVERT_TILE_TO_GLOBAL(tilex+1), y);

        if (US_RndT() < 16)
        {
          SD_PlaySound(SND_RICOCHET);
        }

        return;
      }
    }
    else
    {
      if (tinf[WESTWALL + maptile])
      {
        SpawnBulletImpact(CONVERT_TILE_TO_GLOBAL(tilex), y);

        if (US_RndT() < 16)
        {
          SD_PlaySound(SND_RICOCHET);
        }

        return;
      }
    }

    // Advance to next tile position
    tilex += xdir;
    i--;
  }
  while (i);
}


void ChunkBloom(objtype* ob, Uint16 x, Uint16 y, Direction dir)
{
  Sint16 temp;

  SD_PlaySound(SND_SQUISH);

  GetNewObj(true);
  new->active = ac_removable;
  new->obclass = inertobj;
  new->x = x;
  new->y = y;
  new->ydir = -1;

  switch (dir)
  {
    case dir_North:
      new->xdir = 1;
      new->xspeed = 6;
      new->yspeed = -30;
      break;

    case dir_East:
      new->xdir = 1;
      new->xspeed = US_RndT() / 8 + 10;
      new->yspeed = US_RndT() / 8 - 20;
      break;

    case dir_South:
      new->xdir = -1;
      new->xspeed = -6;
      new->yspeed = -30;
      break;

    case dir_West:
      new->xdir = -1;
      new->xspeed = -10 - US_RndT() / 8;
      new->yspeed = US_RndT() / 8 - 20;
      break;

    default:
      Quit("ChunkBloom: Bad dir!");
  }

  switch (ob->obclass)
  {
    // Robot/technological enemy
    case tankbotobj:
    case bouncebotobj:
    case laserturretobj:
    case bombobj:
    case helicopterobj:
    case parachutebotobj:
      new->temp1 = true;
      NewState(new, &s_metal_debris1);
      break;

    // Biological enemy
    default:
      temp = US_RndT();

      if (temp < 85)
      {
        NewState(new, &s_gib_bone1);
      }
      else if (temp > 85 && temp < 170)
      {
        NewState(new, &s_gib_eyeball1);
      }
      else
      {
        NewState(new, &s_gib_flesh1);
      }
      break;
  }
}


void R_Chunk(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed = -ob->xspeed/2;
    ob->obclass = pickupobj;
  }

  wall = ob->hitnorth;
  if (wall)
  {
    ob->obclass = pickupobj;

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
      ob->y += 8*PIXGLOBAL;

      if (!ob->temp1)
      {
        ChangeState(ob, &s_gibs_on_floor);
      }
      else
      {
        ChangeState(ob, &s_metal_debris_on_floor);
      }

      return;
    }
  }
}


void FragBloom(Uint16 x, Uint16 y, Direction dir)
{
  Sint16 speed = 1;

  GetNewObj(true);
  new->active = ac_removable;
  new->obclass = fireballobj;
  new->temp1 = -1;
  new->temp2 = dir;
  new->x = x;
  new->y = y;
  new->ydir = -1;

  if (dir >= 20)
  {
    dir -= 20;
    new->spawnedby = sb_player;
    speed = US_RndT() / 4 + 15;
  }

  if (dir >= 10)
  {
    dir -= 10;
    new->spawnedby = sb_player;
  }

  switch (dir)
  {
    case dir_North:
      new->xspeed = 0;
      new->yspeed = -20;
      break;

    case dir_South:
      new->xspeed = 0;
      new->yspeed = 20;
      break;

    case dir_East:
      new->xdir = 1;
      new->xspeed = speed + 20;
      new->yspeed = -20;
      break;

    case dir_West:
      new->xdir = -1;
      new->xspeed = -20 - speed;
      new->yspeed = -20;
      break;

    default:
      Quit("FragBloom: Bad dir!");
  }

  NewState(new, &s_fireball1);
}


void C_Fireball(objtype* ob, objtype* hit)
{
  if (
    hit->shootable && !hit->dmgflash && hit->obclass != pushblockobj &&
    hit->obclass != tankbotobj && hit->obclass != crushblockobj &&
    hit->obclass != fireimpobj)
  {
    if (hit->obclass == playerobj && ob->spawnedby == sb_player)
      return;

    DealDamage(hit, 1);
    hit->dmgflash = 25;
    RemoveObj(ob);
  }
}


void R_Fireball(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed= -ob->xspeed/2;
  }

  if (ob->hitsouth)
  {
    ob->yspeed= -ob->yspeed/2;
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
      return;
    }
  }
}


void T_GrenadeExplosion(objtype* ob)
{
  (void)ob;
  SD_PlaySound(SND_EXPLOSION);
}


void ThrowGrenade(Uint16 x, Uint16 y, Direction dir)
{
  if (!gamestate.explosives.landmines && !gamestate.explosives.grenades &&
      !gamestate.explosives.redgrenades)
  {
    return;
  }

  if (gamestate.explosives.landmines > 0)
  {
    SpawnLandMine(x >> G_T_SHIFT, y >> G_T_SHIFT);
    gamestate.explosives.landmines--;
    ChangeState(player, &s_player_place_mine);
    return;
  }

  GetNewObj(true);
  new->obclass = grenadeobj;
  new->active = ac_allways;
  new->temp2 = dir;
  new->x = x;
  new->y = y;
  new->ydir = -1;

  if (gamestate.explosives.redgrenades > 0)
  {
    gamestate.explosives.redgrenades--;
    new->temp7 = true;
  }
  else
  {
    gamestate.explosives.grenades--;
  }

  switch (dir)
  {
    case dir_East:
      new->xspeed = 45;
      new->yspeed = -16;
      new->xdir = 1;
      break;

    case dir_West:
      new->xspeed = -45;
      new->yspeed = -16;
      new->xdir = -1;
      break;

    default:
      Quit("ThrowPower: Bad dir!");
  }

  new->temp1 = 9;
  new->spawnedby = sb_player;
  new->active = ac_removable;

  if (new->temp7)
  {
    NewState(new, &s_redgrenade1);
    new->active = ac_allways;

    if (!StatePositionOk(new, &s_redgrenade1))
    {
      new->hitnorth = 1;
    }

    return;
  }

  NewState(new, &s_grenade1);

  if (!StatePositionOk(new, &s_grenade1))
  {
    new->hitnorth = 1;
  }
}


void UnusedThinkFunc(objtype* ob)
{
  ob->temp2 = ob->temp2 + tics;
  ob->shapenum = 0;

  if (ob->temp2 > 50)
  {
    RemoveObj(ob);
  }
}


void C_Grenade(objtype* ob, objtype* hit)
{
  if (hit->shootable && hit->obclass != pushblockobj)
  {
    FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_East + 10);
    FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_West + 10);

    ChangeState(ob, &s_grenadeexplosion1);

    ob->obclass = fireballobj;

    SD_PlaySound(SND_EXPLOSION);

    ob->needtoclip = cl_midclip;
  }
}


void C_GrenadeExplosion(objtype* ob, objtype* hit)
{
  if (
    hit->shootable && !hit->dmgflash && hit->obclass != pushblockobj &&
    hit->obclass != crushblockobj && hit->obclass != fireimpobj)
  {
    if (hit->obclass == playerobj && ob->spawnedby == sb_player)
      return;
    DealDamage(hit, 5);
    hit->dmgflash = 25;
  }

  ob++;
}


void R_Grenade(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed= -ob->xspeed/2;
  }

  if (ob->hitsouth)
  {
    ob->yspeed= -ob->yspeed/2;
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
      if (ob->temp7)
      {
        FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_East + 10);
        FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_West + 10);

        ob->obclass = fireballobj;
        ob->needtoclip = cl_midclip;
        ob->x = ob->x - 8*PIXGLOBAL;
        ob->y = ob->y - 24*PIXGLOBAL;
        ob->temp7 = 50;

        ChangeState(ob, &s_running_fire1);
      }
      else
      {
        FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_East + 10);
        FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_West + 10);

        ob->obclass = fireballobj;

        ChangeState(ob, &s_grenadeexplosion1);
      }
    }

    return;
  }
}


void SpawnShot(Uint16 x, Uint16 y, Sint16 dir)
{
  GetNewObj(true);
  new->x = x;
  new->y = y;
  new->priority = 0;
  new->obclass = shotobj;
  new->active = ac_allways;

  SD_PlaySound(SND_ZING);

  switch (dir)
  {
    case 1:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case -1:
      new->xdir = -1;
      new->ydir = 0;
      break;

    default:
      Quit("SpawnShot: Bad dir!");
  }

  NewState(new, &s_robopalrocket1);
}


void SpawnLaserShot(Uint16 x, Uint16 y, Sint16 dir)
{
  GetNewObj(true);
  new->x = x;
  new->y = y;
  new->priority = 0;
  new->obclass = shotobj;
  new->active = ac_allways;

  SD_PlaySound(SND_LASERSHOT);

  new->temp7 = 1;

  switch (dir)
  {
    case 1:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case -1:
      new->xdir = -1;
      new->ydir = 0;
      break;

    default:
      Quit("SpawnLaserShot: Bad dir!");
  }

  NewState(new, &s_lasershot);
}


void SpawnSuperPlasmaBolt(Uint16 x, Uint16 y, Sint16 dir)
{
  GetNewObj(true);
  new->x = x;
  new->y = y;
  new->priority = 2;
  new->obclass = shotobj;
  new->active = ac_allways;

  SD_PlaySound(SND_EXPLOSION);

  new->temp7 = 0;

  switch (dir)
  {
    case 1:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case -1:
      new->xdir = -1;
      new->ydir = 0;
      break;

    default:
      Quit("SpawnLaserShot: Bad dir!");
  }

  NewState(new, &s_superplasmabolt);
}


void C_Shot(objtype* ob, objtype* hit)
{
  if (hit->shootable && hit->obclass != pushblockobj &&
      hit->obclass != crushblockobj)
  {
    DealDamage(hit, 1);
    ChangeState(ob, &s_rocketimpact1);
  }

  ob++;
}


void C_LaserShot(objtype* ob, objtype* hit)
{
  if (hit->shootable && hit->obclass != pushblockobj &&
      hit->obclass != crushblockobj)
  {
    if (ob->temp7 == 1)
    {
      DealDamage(hit, 5);
      ChangeState(ob, &s_plasmaboltimpact1);
    }
    else
    {
      DealDamage(hit, 2);
    }
  }

  ob++;
}


void ExplodeShot(objtype* ob)
{
  ob->obclass = inertobj;

  if (ob->temp7 == 1)
  {
    ChangeState(ob, &s_plasmaboltimpact1);
  }
  else
  {
    ChangeState(ob, &s_rocketimpact1);
  }

  SD_PlaySound(SND_BOOM);
}


void T_Shot(objtype* ob)
{
  objtype *ob2;

  if (ob->tileright >= originxtile && ob->tilebottom >= originytile
    && ob->tileleft <= originxtilemax && ob->tiletop <= originytilemax)
  {
    //object is visible, so do nothing
    return;
  }

  if (ob->tileright+10 < originxtile
    || ob->tileleft-10 > originxtilemax
    || ob->tilebottom+6 < originytile
    || ob->tiletop-6 > originytilemax)
  {
    //shot is off-screen by more than half a screen, so remove it
    RemoveObj(ob);
    return;
  }

  //check for collisions with INACTIVE objects
  for (ob2 = player->next; ob2; ob2 = ob2->next)
  {
    if (!ob2->active && ob->right > ob2->left && ob->left < ob2->right
      && ob->top < ob2->bottom && ob->bottom > ob2->top)
    {
      if (ob2->state->contact)
      {
        ob2->state->contact(ob2, ob);
        ob2->needtoreact = true;
        ob2->active = ac_yes;
      }

      if (ob->obclass == nothing) //BUG: obclass is 'inertobj' for the exploded shot
        break;
    }
  }
}


void R_Shot(objtype* ob)
{
  if (ob->hitnorth || ob->hitsouth || ob->hiteast || ob->hitwest)
  {
    ExplodeShot(ob);
  }

  PLACESPRITE
}


void R_SuperPlasmaBolt(objtype* ob)
{
  if (ob->hitnorth || ob->hitsouth || ob->hiteast || ob->hitwest)
  {
    ChangeState(ob, &s_grenadeexplosion1);
  }

  PLACESPRITE
}
