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


Sint16 skullmanactivestate = -2;
Sint16 crusheractive = 0;


void T_ExplodingEnemy(objtype* ob);
void T_TankBot_Waiting(objtype* ob);
void T_TankBot_Moving(objtype* ob);
void SpawnTankBotShot(objtype* ob);
void R_TankBotShot(objtype* ob);
void T_NapalmFire(objtype* ob);
void R_NapalmBomb_Flying(objtype* ob);
void R_NapalmBomb_Landing(objtype* ob);
void T_LaserGunner_Idle(objtype* ob);
void T_LaserGunner_Shooting(objtype* ob);
void C_EnemyLaserShot(objtype* ob, objtype* hit);
void R_EnemyLaserShot(objtype* ob);
void R_PushBlock_OnGround(objtype* ob);
void R_PushBlock_Falling(objtype* ob);
void C_PushBlock(objtype* ob, objtype* hit);
void T_FallingBlock(objtype* ob);
void R_FallingBlock(objtype* ob);
void C_FallingBlock(objtype* ob, objtype* hit);
void T_Crusher_Waiting(objtype* ob);
void T_Crusher_Moving(objtype* ob);
void R_Crusher(objtype* ob);
void C_Crusher(objtype* ob, objtype* hit);
void T_BounceBot(objtype* ob);
void R_BounceBot(objtype* ob);
void SpawnSlimeDrop(objtype* ob);
void SlimeDropperDropSlime(objtype* ob);
void T_SlimeDropEmerging(objtype* ob);
void R_SlimeDrop(objtype* ob);
void T_LaserTurret(objtype* ob);
void LaserTurretFireShot(objtype* ob);
void C_LandMine(objtype* ob, objtype* hit);
void R_BounceAround(objtype* ob);
void R_SkullmanHand(objtype* ob);
void R_SkullmanHand_Attack_L(objtype* ob);
void R_SkullmanHand_Attack_R(objtype* ob);
void T_SkullmanHand_R(objtype* ob);
void T_SkullmanHand_L(objtype* ob);
void T_SkullmanHand_R2(objtype* ob);
void T_SkullmanHand_L2(objtype* ob);
void T_SkullMan(objtype* ob);
void T_SparkShooter(objtype* ob);
void R_SparkShot(objtype* ob);
void C_RespawnBeacon(objtype* ob, objtype* hit);


statetype far s_bigexplosion1 = { /* 32f10 */
  BIG_EXPLOSION1_SPR, BIG_EXPLOSION1_SPR,
  step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_bigexplosion2};

statetype far s_bigexplosion2 = { /* 32f30 */
  BIG_EXPLOSION2_SPR, BIG_EXPLOSION2_SPR,
  step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_bigexplosion3};

statetype far s_bigexplosion3 = { /* 32f50 */
  BIG_EXPLOSION3_SPR, BIG_EXPLOSION3_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_tankbot_dying = { /* 32f70 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  stepthink, false, ps_tofloor, 6, 0, 0,
  T_ExplodingEnemy, NULL, R_Draw, &s_tankbot_dying};

statetype far s_tankbot_waiting = { /* 32f90 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  T_TankBot_Waiting, NULL, R_Draw, &s_tankbot_waiting};

statetype far s_tankbot_moving1 = { /* 32fb0 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  slide, false, ps_tofloor, 20, 8, 0,
  NULL, NULL, R_Walk, &s_tankbot_moving2};

statetype far s_tankbot_moving2 = { /* 32fd0 */
  TANKBOT2_SPR, TANKBOT2_SPR,
  slide, false, ps_tofloor, 20, 8, 0,
  T_TankBot_Moving, NULL, R_Walk, &s_tankbot_moving1};

statetype far s_tankbot_shooting = { /* 32ff0 */
  TANKBOT_SHOOT_SPR, TANKBOT_SHOOT_SPR,
  step, false, ps_tofloor, 7, 0, 0,
  SpawnTankBotShot, NULL, R_Draw, &s_tankbot_waiting};

statetype far s_tankbot_launchbomb = { /* 33010 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  step, false, ps_tofloor, 7, 0, 0,
  SpawnNapalmBomb, NULL, R_Draw, &s_tankbot_waiting};

statetype far s_tankbot_bomb_flying = { /* 33030 */
  TANKBOT_SHOT_FLYING_SPR, TANKBOT_SHOT_FLYING_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, R_NapalmBomb_Flying, &s_tankbot_bomb_flying};

statetype far s_tankbot_bomb_landing = { /* 33050 */
  TANKBOT_SHOT_LANDING_SPR, TANKBOT_SHOT_LANDING_SPR,
  stepthink, false, ps_none, 5, 8, -32,
  NULL, NULL, R_NapalmBomb_Landing, &s_tankbot_bomb_landing};

statetype far s_tankbot_shot = { /* 33070 */
  TANKBOT_BIG_SHOT_SPR, TANKBOT_BIG_SHOT_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, R_TankBotShot, &s_tankbot_shot};

statetype far s_tankbot_shot_explode1 = { /* 33090 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_tankbot_shot_explode2};

statetype far s_tankbot_shot_explode2 = { /* 330b0 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_napalmfire1 = { /* 330d0 */
  SMALL_FIRE1_SPR, SMALL_FIRE1_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  T_NapalmFire, NULL, R_Draw, &s_napalmfire2};

statetype far s_napalmfire2 = { /* 330f0 */
  SMALL_FIRE2_SPR, SMALL_FIRE2_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  T_NapalmFire, NULL, R_Draw, &s_napalmfire3};

statetype far s_napalmfire3 = { /* 33110 */
  SMALL_FIRE3_SPR, SMALL_FIRE3_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  T_NapalmFire, NULL, R_Draw, &s_napalmfire1};

statetype far s_lasergunner_idle = { /* 33130 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  T_LaserGunner_Idle, NULL, R_Draw, &s_lasergunner_idle};

statetype far s_lasergunner_attack1 = { /* 33150 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_lasergunner_attack2};

statetype far s_lasergunner_attack2 = { /* 33170 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_lasergunner_attack3};

statetype far s_lasergunner_attack3 = { /* 33190 */
  LASERGUNNER_SHOOT_L_SPR, LASERGUNNER_SHOOT_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  T_LaserGunner_Shooting, NULL, R_Draw, &s_lasergunner_attack2};

statetype far s_lasergunner_attack4 = { /* 331b0 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  stepthink, false, ps_tofloor, 6, 0, 0,
  T_ExplodingEnemy, NULL, R_Draw, &s_lasergunner_attack4};

statetype far s_enemy_laser_shot = { /* 331d0 */
  LASER_BLAST_BLUE_SPR, LASER_BLAST_BLUE_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, C_EnemyLaserShot, R_EnemyLaserShot, &s_enemy_laser_shot};

statetype far s_bigshotimpact1 = { /* 331f0 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_bigshotimpact2};

statetype far s_bigshotimpact2 = { /* 33210 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_drmangleshot1 = { /* 33230 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, C_EnemyLaserShot, R_EnemyLaserShot, &s_drmangleshot2};

statetype far s_drmangleshot2 = { /* 33250 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, C_EnemyLaserShot, R_EnemyLaserShot, &s_drmangleshot1};

statetype far s_pushblock = { /* 33270 */
  PUSHBLOCKSPR, PUSHBLOCKSPR,
  stepthink, false, ps_tofloor, 6, 0, 1,
  NULL, C_PushBlock, R_PushBlock_OnGround, &s_pushblock};

statetype far s_pushblock_falling = { /* 33290 */
  PUSHBLOCKSPR, PUSHBLOCKSPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, C_PushBlock, R_PushBlock_Falling, &s_pushblock};

statetype far s_fallingblock_idle = { /* 332b0 */
  FALLINGBLOCKSPR, FALLINGBLOCKSPR,
  stepthink, false, ps_none, 1, 0, 0,
  T_FallingBlock, C_FallingBlock, R_Draw, &s_fallingblock_idle};

statetype far s_fallingblock_falling = { /* 332d0 */
  FALLINGBLOCKSPR, FALLINGBLOCKSPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_FallingBlock, &s_fallingblock_falling};

statetype far s_crusher_idle = { /* 332f0 */
  CRUSHERBLOCKSPR, CRUSHERBLOCKSPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Crusher_Waiting, NULL, R_Draw, &s_crusher_idle};

statetype far s_crusher_moving = { /* 33310 */
  CRUSHERBLOCKSPR, CRUSHERBLOCKSPR,
  stepthink, false, ps_none, 5, 0, 8,
  T_Crusher_Moving, C_Crusher, R_Crusher, &s_crusher_moving};

statetype far s_bouncebot1 = { /* 33330 */
  BOUNCEBOT1_SPR, BOUNCEBOT1_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_BounceBot, NULL, R_BounceBot, &s_bouncebot2};

statetype far s_bouncebot2 = { /* 33350 */
  BOUNCEBOT3_SPR, BOUNCEBOT3_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_BounceBot, NULL, R_BounceBot, &s_bouncebot3};

statetype far s_bouncebot3 = { /* 33370 */
  BOUNCEBOT4_SPR, BOUNCEBOT4_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_BounceBot, NULL, R_BounceBot, &s_bouncebot4};

statetype far s_bouncebot4 = { /* 33390 */
  BOUNCEBOT5_SPR, BOUNCEBOT5_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_BounceBot, NULL, R_BounceBot, &s_bouncebot1};

statetype far s_bouncebot5 = { /* 333b0 */
  BOUNCEBOT2_SPR, BOUNCEBOT2_SPR,
  stepthink, false, ps_none, 15, 0, 0,
  T_BounceBot, NULL, R_BounceBot, &s_bouncebot1};

statetype far s_slimedropper1 = { /* 333d0 */
  SLIME_DROPPER1_SPR, SLIME_DROPPER1_SPR,
  step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_slimedropper2};

statetype far s_slimedropper2 = { /* 333f0 */
  SLIME_DROPPER2_SPR, SLIME_DROPPER2_SPR,
  step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_slimedropper3};

statetype far s_slimedropper3 = { /* 33410 */
  SLIME_DROPPER3_SPR, SLIME_DROPPER3_SPR,
  step, false, ps_none, 1, 0, 0,
  SlimeDropperDropSlime, NULL, R_Draw, &s_slimedropper1};

statetype far s_slime_drop1 = { /* 33430 */
  SLIME_DROP1_SPR, SLIME_DROP1_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_slime_drop2};

statetype far s_slime_drop2 = { /* 33450 */
  SLIME_DROP2_SPR, SLIME_DROP2_SPR,
  step, false, ps_none, 5, 0, 0,
  T_SlimeDropEmerging, NULL, R_Draw, &s_slime_drop1};

statetype far s_slime_drop3 = { /* 33470 */
  SLIME_DROP3_SPR, SLIME_DROP3_SPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_SlimeDrop, &s_slime_drop3};

statetype far s_slimedrop_splat1 = { /* 33490 */
  SLIME_DROP_SPLAT1_SPR, SLIME_DROP_SPLAT1_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_slimedrop_splat2};

statetype far s_slimedrop_splat2 = { /* 334b0 */
  SLIME_DROP_SPLAT2_SPR, SLIME_DROP_SPLAT2_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_slimedrop_splat3};

statetype far s_slimedrop_splat3 = { /* 334d0 */
  SLIME_DROP_SPLAT3_SPR, SLIME_DROP_SPLAT3_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_slimedrop_splat4};

statetype far s_slimedrop_splat4 = { /* 334f0 */
  SLIME_DROP_SPLAT4_SPR, SLIME_DROP_SPLAT4_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_turret_idle = { /* 33510 */
  TURRET_IDLE_L_SPR, TURRET_IDLE_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  T_LaserTurret, NULL, R_Draw, &s_turret_idle};

statetype far s_turret_attack1 = { /* 33530 */
  TURRET_READY_L_SPR, TURRET_READY_R_SPR,
  step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_turret_attack2};

statetype far s_turret_attack2 = { /* 33550 */
  TURRET_READY_L_SPR, TURRET_READY_R_SPR,
  step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_turret_attack3};

statetype far s_turret_attack3 = { /* 33570 */
  TURRET_SHOOT_L_SPR, TURRET_SHOOT_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  LaserTurretFireShot, NULL, R_Draw, &s_turret_attack2};

statetype far s_asteroid1 = { /* 33590 */
  ASTEROID1_SPR, ASTEROID1_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_asteroid2};

statetype far s_asteroid2 = { /* 335b0 */
  ASTEROID2_SPR, ASTEROID2_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_asteroid3};

statetype far s_asteroid3 = { /* 335d0 */
  ASTEROID3_SPR, ASTEROID3_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_asteroid4};

statetype far s_asteroid4 = { /* 335f0 */
  ASTEROID4_SPR, ASTEROID4_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_asteroid1};

statetype far s_landmine1 = { /* 33610 */
  LANDMINE1_SPR, LANDMINE1_SPR,
  slide, false, ps_none, 10, 0, 0,
  NULL, C_LandMine, R_BounceAround, &s_landmine2};

statetype far s_landmine2 = { /* 33630 */
  LANDMINE2_SPR, LANDMINE2_SPR,
  slide, false, ps_none, 10, 0, 0,
  NULL, C_LandMine, R_BounceAround, &s_landmine1};

statetype far s_skullman1 = { /* 33650 */
  SKULLMAN1_SPR, SKULLMAN1_SPR,
  stepthink, false, ps_none, 35, 0, 0,
  T_SkullMan, NULL, R_Draw, &s_skullman1};

statetype far s_skullman2 = { /* 33670 */
  SKULLMAN2_SPR, SKULLMAN2_SPR,
  stepthink, false, ps_none, 35, 0, 0,
  T_SkullMan, NULL, R_Draw, &s_skullman2};

statetype far s_skullmanhand_r1 = { /* 33690 */
  SKULLMAN_HAND_R_SPR, SKULLMAN_HAND_R_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_SkullmanHand_R, NULL, R_Draw, &s_skullmanhand_r1};

statetype far s_skullmanhand_l1 = { /* 336b0 */
  SKULLMAN_HAND_L_SPR, SKULLMAN_HAND_L_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_SkullmanHand_L, NULL, R_Draw, &s_skullmanhand_l1};

statetype far s_skullmanhand_r2 = { /* 336d0 */
  SKULLMAN_HAND_R_SPR, SKULLMAN_HAND_R_SPR,
  slide, false, ps_none, 10, 24, 24,
  T_SkullmanHand_R2, NULL, R_SkullmanHand, &s_skullmanhand_r2};

statetype far s_skullmanhand_l2 = { /* 336f0 */
  SKULLMAN_HAND_L_SPR, SKULLMAN_HAND_L_SPR,
  slide, false, ps_none, 10, 24, 24,
  T_SkullmanHand_L2, NULL, R_SkullmanHand, &s_skullmanhand_l2};

statetype far s_skullmanhand_attack_r1 = { /* 33710 */
  SKULLMAN_HAND_ATTACK1_SPR, SKULLMAN_HAND_ATTACK1_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_L, &s_skullmanhand_attack_r2};

statetype far s_skullmanhand_attack_r2 = { /* 33730 */
  SKULLMAN_HAND_ATTACK2_SPR, SKULLMAN_HAND_ATTACK2_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_L, &s_skullmanhand_attack_r1};

statetype far s_skullmanhand_attack_l1 = { /* 33750 */
  SKULLMAN_HAND_ATTACK1_SPR, SKULLMAN_HAND_ATTACK1_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_R, &s_skullmanhand_attack_l2};

statetype far s_skullmanhand_attack_l2 = { /* 33770 */
  SKULLMAN_HAND_ATTACK2_SPR, SKULLMAN_HAND_ATTACK2_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_R, &s_skullmanhand_attack_l1};

statetype far s_sparkshooter1 = { /* 33790 */
  0, 0, step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_sparkshooter2};

statetype far s_sparkshooter2 = { /* 337b0 */
  0, 0, step, false, ps_none, 1, 0, 0,
  T_SparkShooter, NULL, R_Draw, &s_sparkshooter1};

statetype far s_sparkshot1 = { /* 337d0 */
  SPARKSHOT1_SPR, SPARKSHOT1_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, R_SparkShot, &s_sparkshot2};

statetype far s_sparkshot2 = { /* 337f0 */
  SPARKSHOT2_SPR, SPARKSHOT2_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, R_SparkShot, &s_sparkshot1};

statetype far s_sparkshot_explode1 = { /* 33810 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_sparkshot_explode2};

statetype far s_sparkshot_explode2 = { /* 33830 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_respawn_beacon_idle = { /* 33850 */
  RESPAWN_BEACON_INACTIVE_SPR, RESPAWN_BEACON_INACTIVE_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, C_RespawnBeacon, R_Draw, &s_respawn_beacon_idle};

statetype far s_respawn_beacon1 = { /* 33870 */
  RESPAWN_BEACON_ACTIVE1_SPR, RESPAWN_BEACON_ACTIVE1_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_respawn_beacon2};

statetype far s_respawn_beacon2 = { /* 33890 */
  RESPAWN_BEACON_ACTIVE2_SPR, RESPAWN_BEACON_ACTIVE2_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_respawn_beacon3};

statetype far s_respawn_beacon3 = { /* 338b0 */
  RESPAWN_BEACON_ACTIVE3_SPR, RESPAWN_BEACON_ACTIVE3_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_respawn_beacon4};

statetype far s_respawn_beacon4 = { /* 338d0 */
  RESPAWN_BEACON_ACTIVE4_SPR, RESPAWN_BEACON_ACTIVE4_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_respawn_beacon1};


void T_ExplodingEnemy(objtype* ob)
{
  Sint16 explosionx;
  Sint16 explosiony;

  if (--ob->temp1 > 0)
  {
    if (US_RndT() < 175)
    {
      explosionx = ob->midx - (US_RndT() / 16 << 4);
    }
    else
    {
      explosionx = ob->midx + (US_RndT() / 16 << 4);
    }

    explosiony = ob->top + (US_RndT() / 16 << 4);

    if (US_RndT() < 175)
    {
      ob->xdir = 1;
    }
    else
    {
      ob->xdir = -1;
    }

    SpawnBigExplosion(explosionx, explosiony);
    ChunkBloom(ob, ob->midx, ob->y, dir_East);
    ChunkBloom(ob, ob->midx, ob->y, dir_West);
    SD_PlaySound(SND_BOOM);

    ob->nothink = US_RndT() / 16;
    return;
  }

  SD_PlaySound(SND_ROAR);
  SpawnBigExplosion(ob->midx, ob->y + 16*PIXGLOBAL);
  RemoveObj(ob);
}


void SpawnBigExplosion(Sint16 x, Sint16 y)
{
  GetNewObj(true);

  new->obclass = inertobj;
  new->active = ac_allways;
  new->x = x;
  new->y = y;
  new->xdir = 1;
  new->ydir = 1;
  new->needtoclip = cl_noclip;
  new->priority = 3;

  NewState(new, &s_bigexplosion1);
}


Sint16 SpawnEnemyShot(Sint16 x, Sint16 y, statetype far* state)
{
  if (GetNewObj(true) == -1)
    return -1;

  new->x = x;
  new->y = y;
  new->obclass = enemyprojectileobj;
  new->active = ac_allways;

  NewState(new, state);

  if (!CheckPosition(new))
  {
    RemoveObj(new);
    return -1;
  }

  return 0;
}


void SpawnTankBot(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = tankbotobj;
  new->active = ac_allways;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 56*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_tankbot_waiting);

  new->hitnorth = 1;
  new->ticcount =  US_RndT() / 32;
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
}


void T_TankBot_Waiting(objtype* ob)
{
  ob->needtoreact = true;

  if (ob->health <= 0)
  {
    ob->temp1 = US_RndT() / 8;
    ob->shootable = false;
    ChangeState(ob, &s_tankbot_dying);
    return;
  }

  if (US_RndT() < 160)
  {
    ob->state = &s_tankbot_moving1;
  }
}


void T_TankBot_Moving(objtype* ob)
{
  ob->needtoreact = true;

  if (ob->health <= 0)
  {
    ob->temp1 = US_RndT() / 8;
    ob->shootable = false;
    ob->state = &s_tankbot_dying;
    return;
  }

  if (US_RndT() < 20)
  {
    ob->state = &s_tankbot_waiting;
  }
  else
  {
    if (US_RndT() < 100)
    {
      ob->state = &s_tankbot_shooting;
    }

    if (US_RndT() > 200)
    {
      ob->state = &s_tankbot_launchbomb;
    }
  }
}


// Unused
void R_TankBot_Moving(objtype* ob)
{
  if (ob->xdir == 1 && ob->hitwest)
  {
    ob->x -= ob->xmove;
    ob->xdir = -1;

    ChangeState(ob, ob->state);
  }
  else if (ob->xdir == -1 && ob->hiteast)
  {
    ob->x -= ob->xmove;
    ob->xdir = 1;

    ChangeState(ob, ob->state);
  }
  else if (!ob->hitnorth)
  {
    ob->x -= ob->xmove << 1;
    ob->y -= ob->ymove;
    ob->xdir = -ob->xdir;

    ChangeState(ob, ob->state);
  }

  if (ob->health <= 0)
  {
    ob->state = &s_tankbot_dying;
  }

  PLACESPRITE;
}


void SpawnTankBotShot(objtype* ob)
{
  GetNewObj(true);

  new->obclass = enemyprojectileobj;
  new->active = ac_allways;
  new->x = ob->x + 8*PIXGLOBAL;
  new->y = ob->y + 23*PIXGLOBAL;
  new->xdir = -1;
  new->ydir = 1;
  new->xspeed = new->xdir*132 + (US_RndT() >> 4);
  new->yspeed = -3;

  NewState(new, &s_tankbot_shot);

  SD_PlaySound(SND_BOOM);
}


void SpawnNapalmBomb(objtype* ob)
{
  SD_PlaySound(SND_RICOCHET);

  GetNewObj(true);

  new->obclass = enemyprojectileobj;
  new->active = ac_allways;
  new->x = ob->x + 40*PIXGLOBAL;
  new->y = ob->y + 8*PIXGLOBAL;
  new->xdir = -1;
  new->ydir = -1;
  new->xspeed = new->xdir*80 + (US_RndT() >> 4);
  new->yspeed = -80;
  new->temp1 = US_RndT() / 4;

  NewState(new, &s_tankbot_bomb_flying);
}


void R_TankBotShot(objtype* ob)
{
  PLACESPRITE;

  if (ob->hiteast || ob->hitwest || ob->hitsouth)
  {
    ChangeState(ob, &s_tankbot_shot_explode1);
    return;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_tankbot_shot_explode1);

    GetNewObj(true);

    new->obclass = enemyprojectileobj;
    new->active = ac_allways;
    new->x = ob->x;
    new->y = ob->y + 8*PIXGLOBAL;
    new->temp7 = 100;

    NewState(new, &s_napalmfire1);
  }
}


void T_NapalmFire(objtype* ob)
{
  if (ob->temp7 > 0 && ob->hitnorth)
  {
    ob->temp7--;
    return;
  }
  else
  {
    RemoveObj(ob);
  }
}


void R_NapalmBomb_Flying(objtype* ob)
{
  if (ob->temp1 > 0)
  {
    ob->temp1--;
  }

  if (ob->temp1 <= 0 || ob->yspeed > 0)
  {
    ob->temp1 = US_RndT() / 8;

    ChangeState(ob, &s_tankbot_bomb_landing);
  }

  PLACESPRITE;
}


void R_NapalmBomb_Landing(objtype* ob)
{
  if (ob->temp1 > 0 && !ob->hitnorth)
  {
    if (US_RndT() < 100)
    {
      ob->xdir = -ob->xdir;
    }

    ob->temp1--;
  }
  else
  {
    ChangeState(ob, &s_tankbot_shot_explode1);

    FragBloom(ob->x, ob->y, dir_North);
    FragBloom(ob->x, ob->y, dir_South);
    FragBloom(ob->x, ob->y, dir_East);
    FragBloom(ob->x, ob->y, dir_West);
    SD_PlaySound(SND_LASERSHOT);
  }

  PLACESPRITE;
}


void SpawnLaserGunner(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = lasergunnerobj;
  new->active = ac_allways;
  new->needtoreact = true;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 40*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->hitnorth = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 40;
      break;

    default:
      new->health = 20;
      break;
  }

  NewState(new, &s_lasergunner_idle);
}


void T_LaserGunner_Idle(objtype* ob)
{
  ob->needtoreact = true;

  if (ob->health <= 0)
  {
    ob->temp1 = US_RndT() / 16;
    ob->shootable = false;
    ChangeState(ob, &s_lasergunner_attack4);
    return;
  }

  if (player->bottom > ob->top && player->top < ob->bottom)
  {
    if (ob->temp2 <= 0)
    {
      if (ob->x > player->x)
      {
        ob->xdir = -1;
      }
      else
      {
        ob->xdir = 1;
      }

      ob->temp1 = 2;
      ob->temp2 = 30;
      ob->state = &s_lasergunner_attack1;
      return;
    }

    ob->temp2--;
  }
}


void T_LaserGunner_Shooting(objtype* ob)
{
  Sint16 shotx;

  ob->needtoreact = true;

  if (--ob->temp1 == 0)
  {
    ob->state = &s_lasergunner_idle;
  }

  if (ob->xdir == 1)
  {
    shotx = ob->x + 48*PIXGLOBAL;
  }
  else
  {
    shotx = ob->x;
  }

  if (SpawnEnemyShot(shotx, ob->y + 26*PIXGLOBAL, &s_enemy_laser_shot) == -1)
    return;

  new->xspeed = ob->xdir * 60;

  if (US_RndT() < 70)
  {
    new->yspeed = 0;
  }
  else if (ob->temp1 & 1)
  {
    new->yspeed = 4;
  }
  else
  {
    new->yspeed = -4;
  }

  SD_PlaySound(SND_LASERSHOT);
}


void C_EnemyLaserShot(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj || hit->obclass == pushblockobj)
  {
    ob->y -= 8*PIXGLOBAL;
    ChangeState(ob, &s_bigshotimpact1);
    return;
  }
}


void R_EnemyLaserShot(objtype* ob)
{
  if (ob->hitnorth || ob->hiteast || ob->hitsouth || ob->hitwest)
  {
    SD_PlaySound(SND_ZING);
    ob->y -= 8*PIXGLOBAL;
    ChangeState(ob, &s_bigshotimpact1);
    ob->obclass = inertobj;
  }

  PLACESPRITE;
}


void SpawnPushBlock(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = pushblockobj;
  new->active = ac_allways;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 32*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->hitnorth = 1;
  new->needtoclip = cl_midclip;
  new->shootable = true;
  new->temp7 = 15;

  NewState(new, &s_pushblock);
}


void R_PushBlock_OnGround(objtype* ob)
{
  if (!ob->hitnorth)
  {
    ChangeState(ob, &s_pushblock_falling);
  }

  PLACESPRITE;
}


void R_PushBlock_Falling(objtype* ob)
{
  if (ob->hitnorth)
  {
    ChangeState(ob, &s_pushblock);
  }

  PLACESPRITE;
}


void C_PushBlock(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj && player->bottom > ob->top)
  {
    if (--ob->temp7 <= 0)
    {
      ob->temp7 = 15;
      SD_PlaySound(SND_BLOCKPUSHED);
    }
  }

  if (hit->obclass == pushblockobj)
  {
    ClipToSprite(ob, hit, false);

    ob->obclass = bounderobj;
    hit->obclass = bounderobj;
  }
  else if (hit->obclass == fireballobj)
  {
    ClipToSprite(hit, ob, false);
    return;
  }
}


void SpawnFallingBlock(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = crushblockobj;
  new->active = ac_removable;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 0;
  new->ydir = -1;
  new->shootable = true;
  new->temp7 = 35;

  NewState(new, &s_fallingblock_idle);
}


void T_FallingBlock(objtype* ob)
{
  if (ob->temp7 != 35)
  {
    if (--ob->temp7 <= 0)
    {
      ChangeState(ob, &s_fallingblock_falling);
      SD_PlaySound(SND_FALLINGBLOCK);
      ob->needtoclip = cl_noclip;
    }
  }
}


void R_FallingBlock(objtype* ob)
{
  PLACESPRITE;
}


void C_FallingBlock(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj && ob->temp7 == 35)
  {
    ob->temp7--;
  }
}


void SpawnCrusher(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = crushblockobj;
  new->priority = 2;
  new->active = ac_allways;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;
  new->needtoclip = cl_fullclip;
  new->temp7 = 15;

  NewState(new, &s_crusher_idle);
}


void T_Crusher_Waiting(objtype* ob)
{
  if (crusheractive == 1)
  {
    ChangeState(ob, &s_crusher_moving);
  }
}


void T_Crusher_Moving(objtype* ob)
{
  if (--ob->temp7 <= 0)
  {
    ob->temp7 = 15;
    SD_PlaySound(SND_CRUSHERMOVE);
  }
}


void R_Crusher(objtype* ob)
{
  if (ob->hitnorth)
  {
    crusheractive = -1;
    ChangeState(ob, &s_crusher_idle);
    SD_PlaySound(SND_SQUISH);
  }

  PLACESPRITE;
}


void C_Crusher(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj && ob->bottom > hit->top)
  {
    jumptime = 0;

    if (!playerdied)
    {
      KillPlayer();
    }
  }
}


void SpawnBounceBot(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = bouncebotobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 24*PIXGLOBAL;
  new->xdir = 1;
  new->xspeed = 8;
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

  NewState(new, &s_bouncebot1);
}


void T_BounceBot(objtype* ob)
{
  Sint16 xdelta;

  AccelerateX(ob, ob->xdir, 8);

  if (ob->temp1)
  {
    if (ob->temp1 < tics)
    {
      ob->ymove = ob->yspeed * ob->temp1;
      ob->temp1 = 0;
    }
    else
    {
      ob->ymove = ob->yspeed * tics;
      ob->temp1 = ob->temp1 - tics;
    }
  }
  else
  {
    DoGravity(ob);
  }

  if (ob->top > player->bottom || ob->bottom < player->top)
    return;

  if (ob->xdir == -1)
  {
    xdelta = ob->left - player->right;

    if (xdelta > 64*PIXGLOBAL)
      return;

    ob->xdir = 1;
    return;
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta > 64*PIXGLOBAL)
      return;

    ob->xdir = -1;
    return;
  }
}


void R_BounceBot(objtype* ob)
{
  if (ob->hiteast || ob->hitwest)
  {
    ob->xdir = -ob->xdir;
    ob->xspeed = -ob->xspeed;
  }

  if (ob->hitsouth)
  {
    if (ob->tileright >= originxtile && ob->tileleft <= originxtilemax &&
        ob->tiletop >= originytile && ob->tilebottom <= originytilemax)
    {
      SD_PlaySound(SND_ROBOTBOUNCE);
    }

    ob->yspeed = -ob->yspeed;
  }

  if (ob->hitnorth)
  {
    if (ob->tileright >= originxtile && ob->tileleft <= originxtilemax &&
        ob->tiletop >= originytile && ob->tilebottom <= originytilemax)
    {
      SD_PlaySound(SND_ROBOTBOUNCE);
    }

    ob->yspeed = -64 - (US_RndT() >> 4);
    ob->temp1 = 2;

    ChangeState(ob, &s_bouncebot5);
  }

  PLACESPRITE;
}


void SpawnSlimeDropper(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = slimedropperobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 1;
  new->ydir = -1;

  NewState(new, &s_slimedropper1);

  new->shootable = true;
  new->health = 10;
}


void SlimeDropperDropSlime(objtype* ob)
{
  SpawnSlimeDrop(ob);
}


void SpawnSlimeDrop(objtype* ob)
{
  GetNewObj(true);

  new->obclass = slimedropperobj;
  new->x = ob->x + 8*PIXGLOBAL;
  new->y = ob->bottom;
  new->xdir = 1;
  new->ydir = 1;
  new->active = ac_removable;
  new->priority = 3;

  NewState(new, &s_slime_drop1);

  SD_PlaySound(SND_DROPSLIME);
}


void T_SlimeDropEmerging(objtype* ob)
{
  if (US_RndT() < 100)
  {
    ob->state = &s_slime_drop3;
  }
}


void R_SlimeDrop(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->state = &s_slimedrop_splat1;
    ob->priority = 0;
    ob->y -= 8*PIXGLOBAL;
    return;
  }

  PLACESPRITE;
}


void SpawnLaserTurret(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = laserturretobj;
  new->priority = 2;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 16*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->hitnorth = true;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 7;
      break;

    default:
      new->health = 4;
      break;
  }

  new->needtoreact = true;

  NewState(new, &s_turret_idle);
}


void T_LaserTurret(objtype* ob)
{
  ob->needtoreact = true;

  if (player->bottom > ob->top && player->top < ob->bottom)
  {
    if (ob->temp2 <= 0)
    {
      if (ob->x > player->x)
      {
        ob->xdir = -1;
      }
      else
      {
        ob->xdir = 1;
      }

      ob->temp1 = 1;
      ob->temp2 = US_RndT() >> 4;
      ob->state = &s_turret_attack1;
      return;
    }

    ob->temp2--;
  }
}


void LaserTurretFireShot(objtype* ob)
{
  Sint16 shotx;

  if (--ob->temp1 == 0)
  {
    ob->state = &s_turret_idle;
  }

  if (ob->xdir == 1)
  {
    shotx = ob->x + 32*PIXGLOBAL;
  }
  else
  {
    shotx = ob->x;
  }

  if (SpawnEnemyShot(shotx, ob->y + 8*PIXGLOBAL, &s_enemy_laser_shot) == -1)
    return;

  new->xspeed = ob->xdir * 60;
  new->yspeed = 0;

  SD_PlaySound(SND_TURRETSHOOT);
}


void SpawnAsteroid(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = inertobj;
  new->active = ac_allways;
  new->priority = 2;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);

  switch (US_RndT() / 64)
  {
    case 0:
      new->xdir = -1;
      new->ydir = -1;
      break;

    case 1:
      new->xdir = 1;
      new->ydir = 1;
      break;

    case 2:
      new->xdir = -1;
      new->ydir = 1;
      break;

    case 3:
      new->xdir = 1;
      new->ydir = -1;
      break;
  }

  NewState(new, &s_asteroid1);
}


void SpawnLandMine(Sint16 x, Sint16 y)
{
  GetNewObj(true);

  new->obclass = grenadeobj;
  new->active = ac_allways;
  new->needtoclip = cl_fullclip;

  if (player->xdir == 1)
  {
    new->x = player->midx - 8*PIXGLOBAL;
  }
  else
  {
    new->x = player->midx;
  }

  new->y = player->bottom - 16*PIXGLOBAL;

  switch (US_RndT() / 64)
  {
    case 0:
      new->xdir = player->xdir;
      new->ydir = -1;
      break;

    case 1:
      new->xdir = player->xdir;
      new->ydir = 1;
      break;

    case 2:
      new->xdir = player->xdir;
      new->ydir = 1;
      break;

    case 3:
      new->xdir = player->xdir;
      new->ydir = -1;
      break;
  }

  NewState(new, &s_landmine1);
}


void C_LandMine(objtype* ob, objtype* hit)
{
  if (hit->shootable && hit->obclass != pushblockobj)
  {
    FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_East + 10);
    FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_West + 10);

    ob->obclass = fireballobj;
    ob->temp6 = 1;
    SD_PlaySound(SND_EXPLOSION);

    ChangeState(ob, &s_grenadeexplosion1);
    ob->needtoclip = cl_midclip;

    DealDamage(hit, 5);
  }
}


void R_BounceAround(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->ydir = -1;
  }
  else if (ob->hitsouth)
  {
    ob->ydir = 1;
  }

  if (ob->hitwest)
  {
    ob->xdir = -1;
  }
  else if (ob->hiteast)
  {
    ob->xdir = 1;
  }

  PLACESPRITE;
}


void SpawnSkullmanHand(Sint16 x, Sint16 y, Sint16 type)
{
  skullmanactivestate = -2;

  GetNewObj(false);

  new->obclass = skullmanhandobj;
  new->needtoreact = true;
  new->active = ac_allways;
  new->priority = 2;
  new->needtoclip = cl_fullclip;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 85;
      break;

    default:
      new->health = 65;
      break;
  }

  switch (US_RndT() / 64)
  {
    case 0:
      new->xdir = -1;
      new->ydir = -1;
      break;

    case 1:
      new->xdir = 1;
      new->ydir = 1;
      break;

    case 2:
      new->xdir = -1;
      new->ydir = 1;
      break;

    case 3:
      new->xdir = 1;
      new->ydir = -1;
      break;
  }

  switch (type)
  {
    case 0:
      NewState(new, &s_skullmanhand_r1);
      break;

    case 1:
      NewState(new, &s_skullmanhand_l1);
      break;
  }
}


void R_SkullmanHand(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->ydir = -1;
  }
  else if (ob->hitsouth)
  {
    ob->ydir = 1;
  }

  if (ob->hitwest)
  {
    ob->xdir = -1;
  }
  else if (ob->hiteast)
  {
    ob->xdir = 1;
  }

  PLACESPRITE;
}


void R_SkullmanHand_Attack_L(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->state = &s_skullmanhand_r2;
    ob->ydir = -1;
  }

  PLACESPRITE;
}


void R_SkullmanHand_Attack_R(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->state = &s_skullmanhand_l2;
    ob->ydir = -1;
  }

  PLACESPRITE;
}


void T_SkullmanHand_R(objtype* ob)
{
  if (skullmanactivestate == -2)
  {
    return;
  }
  else
  {
    ob->state = &s_skullmanhand_attack_r1;
  }
}


void T_SkullmanHand_L(objtype* ob)
{
  if (skullmanactivestate < 0)
  {
    return;
  }
  else
  {
    ob->state = &s_skullmanhand_attack_r1;
  }
}


void T_SkullmanHand_R2(objtype* ob)
{
  if (skullmanactivestate == 1)
  {
    RemoveObj(ob);
  }

  if (player->right < ob->left || player->left > ob->right ||
      player->top < ob->bottom)
    return;

  ob->state = &s_skullmanhand_attack_r1;
  ob->yspeed = 0;
}


void T_SkullmanHand_L2(objtype* ob)
{
  if (skullmanactivestate == 1)
  {
    RemoveObj(ob);
  }

  if (player->right < ob->left || player->left > ob->right ||
      player->top < ob->bottom)
    return;

  ob->state = &s_skullmanhand_attack_l1;
  ob->yspeed = 0;
}


void SpawnSkullman(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = skullmanobj;
  new->active = ac_allways;
  new->priority = 2;
  new->needtoreact = true;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 200;
      break;

    default:
      new->health = 125;
      break;
  }

  bosshealth = new->health;
  lastbosshealth = -1;
  hbardivisor = bosshealth / 20 - 1;

  NewState(new, &s_skullman2);
}


void T_SkullMan(objtype* ob)
{
  if (ob->health != bosshealth)
  {
    lastbosshealth = bosshealth;
    bosshealth = ob->health;
  }

  ob->needtoreact = true;

  if (US_RndT() > 200)
  {
    if (ob->state == &s_skullman1)
    {
      ob->state = &s_skullman2;
    }
    else
    {
      ob->state = &s_skullman1;
    }
  }
}


void SpawnSparkShooter(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = inertobj;
  new->active = ac_yes;
  new->tileright = new->tileleft = x;
  new->tiletop = new->tilebottom = y;
  new->x = new->left = new->right = CONVERT_TILE_TO_GLOBAL(x);
  new->y = new->top = new->bottom = CONVERT_TILE_TO_GLOBAL(y);

  NewState(new, &s_sparkshooter1);
}


void T_SparkShooter(objtype* ob)
{
  GetNewObj(true);

  new->obclass = enemyprojectileobj;
  new->priority = 2;
  new->active = ac_removable;
  new->x = ob->x;
  new->y = ob->y;

  switch (US_RndT() / 64)
  {
    case 0:
      new->yspeed = -64;
      break;

    case 1:
      new->xspeed = 64;
      new->yspeed = 64;
      break;

    case 2:
      new->yspeed = 64;
      break;

    case 3:
      new->xspeed = -64;
      new->yspeed = 64;
      break;
  }

  NewState(new, &s_sparkshot1);
  SD_PlaySound(SND_LASERSHOT);
}


void R_SparkShot(objtype* ob)
{
  if (ob->hitnorth || ob->hiteast || ob->hitsouth || ob->hitwest)
  {
    SD_PlaySound(SND_ZING);
    ChangeState(ob, &s_sparkshot_explode1);
  }

  PLACESPRITE;
}


void SpawnRespawnBeacon(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = inertobj;
  new->priority = 2;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 32*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->hitnorth = 1;

  NewState(new, &s_respawn_beacon_idle);
}


void C_RespawnBeacon(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj)
  {
    playerrestorex = player->x;
    playerrestorey = player->y;
    ChangeState(ob, &s_respawn_beacon1);
    SD_PlaySound(SND_BEACONACTIVE);

    if (!gamestate.helpmsgbeacon)
    {
      ShowHelpMessage("Continue from beacons when you get killed.\n");
      gamestate.helpmsgbeacon = true;
    }
  }

  ob++;
}
