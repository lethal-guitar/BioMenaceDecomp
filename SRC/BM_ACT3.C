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

extern statetype far s_230;
extern statetype far s_231;
extern statetype far s_232;
extern statetype far s_233;
extern statetype far s_234;
extern statetype far s_235;
extern statetype far s_236;
extern statetype far s_237;
extern statetype far s_238;
extern statetype far s_239;
extern statetype far s_240;
extern statetype far s_241;
extern statetype far s_242;
extern statetype far s_243;
extern statetype far s_244;
extern statetype far s_245;
extern statetype far s_246;
extern statetype far s_247;
extern statetype far s_248;
extern statetype far s_249;
extern statetype far s_250;
extern statetype far s_251;
extern statetype far s_252;
extern statetype far s_253;
extern statetype far s_254;
extern statetype far s_255;
extern statetype far s_256;
extern statetype far s_257;
extern statetype far s_258;
extern statetype far s_259;
extern statetype far s_260;
extern statetype far s_261;
extern statetype far s_262;
extern statetype far s_263;
extern statetype far s_264;
extern statetype far s_265;
extern statetype far s_266;
extern statetype far s_267;
extern statetype far s_268;
extern statetype far s_269;
extern statetype far s_270;
extern statetype far s_271;
extern statetype far s_272;
extern statetype far s_273;
extern statetype far s_274;
extern statetype far s_275;
extern statetype far s_276;
extern statetype far s_277;
extern statetype far s_278;
extern statetype far s_279;
extern statetype far s_280;
extern statetype far s_281;
extern statetype far s_282;
extern statetype far s_283;
extern statetype far s_284;
extern statetype far s_285;
extern statetype far s_286;
extern statetype far s_287;
extern statetype far s_288;
extern statetype far s_289;
extern statetype far s_290;
extern statetype far s_291;
extern statetype far s_292;
extern statetype far s_293;
extern statetype far s_294;
extern statetype far s_295;
extern statetype far s_296;
extern statetype far s_297;
extern statetype far s_298;
extern statetype far s_299;
extern statetype far s_300;
extern statetype far s_301;
extern statetype far s_302;
extern statetype far s_303;
extern statetype far s_304;
extern statetype far s_305;
extern statetype far s_306;
extern statetype far s_307;
extern statetype far s_308;


Sint16 skullmanactivestate = -2;
Sint16 crusheractive = 0;


void T_ExplodingEnemy();
void sub_22b98();
void sub_22be7();
void sub_22d16();
void sub_22db0();
void sub_22e5c();
void sub_22f1a();
void sub_22f3f();
void sub_22fa5();
void T_LaserGunner_Idle();
void T_LaserGunner_Shooting();
void C_EnemyLaserShot();
void R_EnemyLaserShot();
void R_PushBlock_OnGround();
void R_PushBlock_Falling();
void C_PushBlock();
void T_FallingBlock();
void R_FallingBlock();
void C_FallingBlock();
void T_Crusher_Waiting();
void T_Crusher_Moving();
void R_Crusher();
void C_Crusher();
void sub_2370e();
void sub_237bf();
void SpawnSlimeDrop();
void SlimeDropperDropSlime(objtype* ob);
void T_SlimeDropEmerging();
void R_SlimeDrop();
void T_LaserTurret();
void LaserTurretFireShot();
void C_LandMine();
void R_BounceAround();
void R_SkullmanHand();
void R_SkullmanHand_Attack_L();
void R_SkullmanHand_Attack_R();
void T_SkullmanHand_R();
void T_SkullmanHand_L();
void T_SkullmanHand_R2();
void T_SkullmanHand_L2();
void T_SkullMan();
void T_SparkShooter();
void R_SparkShot();
void C_RespawnBeacon();

statetype far s_230 = { /* 32f10 */
  BIG_EXPLOSION1_SPR, BIG_EXPLOSION1_SPR,
  step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_231};

statetype far s_231 = { /* 32f30 */
  BIG_EXPLOSION2_SPR, BIG_EXPLOSION2_SPR,
  step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_232};

statetype far s_232 = { /* 32f50 */
  BIG_EXPLOSION3_SPR, BIG_EXPLOSION3_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_233 = { /* 32f70 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  stepthink, false, ps_tofloor, 6, 0, 0,
  T_ExplodingEnemy, NULL, R_Draw, &s_233};

statetype far s_234 = { /* 32f90 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  sub_22b98, NULL, R_Draw, &s_234};

statetype far s_235 = { /* 32fb0 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  slide, false, ps_tofloor, 20, 8, 0,
  NULL, NULL, R_Walk, &s_236};

statetype far s_236 = { /* 32fd0 */
  TANKBOT2_SPR, TANKBOT2_SPR,
  slide, false, ps_tofloor, 20, 8, 0,
  sub_22be7, NULL, R_Walk, &s_235};

statetype far s_237 = { /* 32ff0 */
  TANKBOT_SHOOT_SPR, TANKBOT_SHOOT_SPR,
  step, false, ps_tofloor, 7, 0, 0,
  sub_22d16, NULL, R_Draw, &s_234};

statetype far s_238 = { /* 33010 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  step, false, ps_tofloor, 7, 0, 0,
  sub_22db0, NULL, R_Draw, &s_234};

statetype far s_239 = { /* 33030 */
  TANKBOT_SHOT_FLYING_SPR, TANKBOT_SHOT_FLYING_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, sub_22f3f, &s_239};

statetype far s_240 = { /* 33050 */
  TANKBOT_SHOT_LANDING_SPR, TANKBOT_SHOT_LANDING_SPR,
  stepthink, false, ps_none, 5, 8, 65504,
  NULL, NULL, sub_22fa5, &s_240};

statetype far s_241 = { /* 33070 */
  TANKBOT_BIG_SHOT_SPR, TANKBOT_BIG_SHOT_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, sub_22e5c, &s_241};

statetype far s_242 = { /* 33090 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_243};

statetype far s_243 = { /* 330b0 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_244 = { /* 330d0 */
  SMALL_FIRE1_SPR, SMALL_FIRE1_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_245};

statetype far s_245 = { /* 330f0 */
  SMALL_FIRE2_SPR, SMALL_FIRE2_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_246};

statetype far s_246 = { /* 33110 */
  SMALL_FIRE3_SPR, SMALL_FIRE3_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_244};

statetype far s_247 = { /* 33130 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  T_LaserGunner_Idle, NULL, R_Draw, &s_247};

statetype far s_248 = { /* 33150 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_249};

statetype far s_249 = { /* 33170 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_250};

statetype far s_250 = { /* 33190 */
  LASERGUNNER_SHOOT_L_SPR, LASERGUNNER_SHOOT_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  T_LaserGunner_Shooting, NULL, R_Draw, &s_249};

statetype far s_251 = { /* 331b0 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  stepthink, false, ps_tofloor, 6, 0, 0,
  T_ExplodingEnemy, NULL, R_Draw, &s_251};

statetype far s_252 = { /* 331d0 */
  LASER_BLAST_BLUE_SPR, LASER_BLAST_BLUE_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, C_EnemyLaserShot, R_EnemyLaserShot, &s_252};

statetype far s_253 = { /* 331f0 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_254};

statetype far s_254 = { /* 33210 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_255 = { /* 33230 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, C_EnemyLaserShot, R_EnemyLaserShot, &s_256};

statetype far s_256 = { /* 33250 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, C_EnemyLaserShot, R_EnemyLaserShot, &s_255};

statetype far s_257 = { /* 33270 */
  PUSHBLOCKSPR, PUSHBLOCKSPR,
  stepthink, false, ps_tofloor, 6, 0, 1,
  NULL, C_PushBlock, R_PushBlock_OnGround, &s_257};

statetype far s_258 = { /* 33290 */
  PUSHBLOCKSPR, PUSHBLOCKSPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, C_PushBlock, R_PushBlock_Falling, &s_257};

statetype far s_259 = { /* 332b0 */
  FALLINGBLOCKSPR, FALLINGBLOCKSPR,
  stepthink, false, ps_none, 1, 0, 0,
  T_FallingBlock, C_FallingBlock, R_Draw, &s_259};

statetype far s_260 = { /* 332d0 */
  FALLINGBLOCKSPR, FALLINGBLOCKSPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_FallingBlock, &s_260};

statetype far s_261 = { /* 332f0 */
  CRUSHERBLOCKSPR, CRUSHERBLOCKSPR,
  stepthink, false, ps_none, 6, 0, 0,
  T_Crusher_Waiting, NULL, R_Draw, &s_261};

statetype far s_262 = { /* 33310 */
  CRUSHERBLOCKSPR, CRUSHERBLOCKSPR,
  stepthink, false, ps_none, 5, 0, 8,
  T_Crusher_Moving, C_Crusher, R_Crusher, &s_262};

statetype far s_263 = { /* 33330 */
  BOUNCEBOT1_SPR, BOUNCEBOT1_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_264};

statetype far s_264 = { /* 33350 */
  BOUNCEBOT3_SPR, BOUNCEBOT3_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_265};

statetype far s_265 = { /* 33370 */
  BOUNCEBOT4_SPR, BOUNCEBOT4_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_266};

statetype far s_266 = { /* 33390 */
  BOUNCEBOT5_SPR, BOUNCEBOT5_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_263};

statetype far s_267 = { /* 333b0 */
  BOUNCEBOT2_SPR, BOUNCEBOT2_SPR,
  stepthink, false, ps_none, 15, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_263};

statetype far s_268 = { /* 333d0 */
  SLIME_DROPPER1_SPR, SLIME_DROPPER1_SPR,
  step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_269};

statetype far s_269 = { /* 333f0 */
  SLIME_DROPPER2_SPR, SLIME_DROPPER2_SPR,
  step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_270};

statetype far s_270 = { /* 33410 */
  SLIME_DROPPER3_SPR, SLIME_DROPPER3_SPR,
  step, false, ps_none, 1, 0, 0,
  SlimeDropperDropSlime, NULL, R_Draw, &s_268};

statetype far s_271 = { /* 33430 */
  SLIME_DROP1_SPR, SLIME_DROP1_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_272};

statetype far s_272 = { /* 33450 */
  SLIME_DROP2_SPR, SLIME_DROP2_SPR,
  step, false, ps_none, 5, 0, 0,
  T_SlimeDropEmerging, NULL, R_Draw, &s_271};

statetype far s_273 = { /* 33470 */
  SLIME_DROP3_SPR, SLIME_DROP3_SPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_SlimeDrop, &s_273};

statetype far s_274 = { /* 33490 */
  SLIME_DROP_SPLAT1_SPR, SLIME_DROP_SPLAT1_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_275};

statetype far s_275 = { /* 334b0 */
  SLIME_DROP_SPLAT2_SPR, SLIME_DROP_SPLAT2_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_276};

statetype far s_276 = { /* 334d0 */
  SLIME_DROP_SPLAT3_SPR, SLIME_DROP_SPLAT3_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_277};

statetype far s_277 = { /* 334f0 */
  SLIME_DROP_SPLAT4_SPR, SLIME_DROP_SPLAT4_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_278 = { /* 33510 */
  TURRET_IDLE_L_SPR, TURRET_IDLE_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  T_LaserTurret, NULL, R_Draw, &s_278};

statetype far s_279 = { /* 33530 */
  TURRET_READY_L_SPR, TURRET_READY_R_SPR,
  step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_280};

statetype far s_280 = { /* 33550 */
  TURRET_READY_L_SPR, TURRET_READY_R_SPR,
  step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_281};

statetype far s_281 = { /* 33570 */
  TURRET_SHOOT_L_SPR, TURRET_SHOOT_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  LaserTurretFireShot, NULL, R_Draw, &s_280};

statetype far s_282 = { /* 33590 */
  ASTEROID1_SPR, ASTEROID1_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_283};

statetype far s_283 = { /* 335b0 */
  ASTEROID2_SPR, ASTEROID2_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_284};

statetype far s_284 = { /* 335d0 */
  ASTEROID3_SPR, ASTEROID3_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_285};

statetype far s_285 = { /* 335f0 */
  ASTEROID4_SPR, ASTEROID4_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, R_BounceAround, &s_282};

statetype far s_286 = { /* 33610 */
  LANDMINE1_SPR, LANDMINE1_SPR,
  slide, false, ps_none, 10, 0, 0,
  NULL, C_LandMine, R_BounceAround, &s_287};

statetype far s_287 = { /* 33630 */
  LANDMINE2_SPR, LANDMINE2_SPR,
  slide, false, ps_none, 10, 0, 0,
  NULL, C_LandMine, R_BounceAround, &s_286};

statetype far s_288 = { /* 33650 */
  SKULLMAN1_SPR, SKULLMAN1_SPR,
  stepthink, false, ps_none, 35, 0, 0,
  T_SkullMan, NULL, R_Draw, &s_288};

statetype far s_289 = { /* 33670 */
  SKULLMAN2_SPR, SKULLMAN2_SPR,
  stepthink, false, ps_none, 35, 0, 0,
  T_SkullMan, NULL, R_Draw, &s_289};

statetype far s_290 = { /* 33690 */
  SKULLMAN_HAND_R_SPR, SKULLMAN_HAND_R_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_SkullmanHand_R, NULL, R_Draw, &s_290};

statetype far s_291 = { /* 336b0 */
  SKULLMAN_HAND_L_SPR, SKULLMAN_HAND_L_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_SkullmanHand_L, NULL, R_Draw, &s_291};

statetype far s_292 = { /* 336d0 */
  SKULLMAN_HAND_R_SPR, SKULLMAN_HAND_R_SPR,
  slide, false, ps_none, 10, 24, 24,
  T_SkullmanHand_R2, NULL, R_SkullmanHand, &s_292};

statetype far s_293 = { /* 336f0 */
  SKULLMAN_HAND_L_SPR, SKULLMAN_HAND_L_SPR,
  slide, false, ps_none, 10, 24, 24,
  T_SkullmanHand_L2, NULL, R_SkullmanHand, &s_293};

statetype far s_294 = { /* 33710 */
  SKULLMAN_HAND_ATTACK1_SPR, SKULLMAN_HAND_ATTACK1_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_L, &s_295};

statetype far s_295 = { /* 33730 */
  SKULLMAN_HAND_ATTACK2_SPR, SKULLMAN_HAND_ATTACK2_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_L, &s_294};

statetype far s_296 = { /* 33750 */
  SKULLMAN_HAND_ATTACK1_SPR, SKULLMAN_HAND_ATTACK1_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_R, &s_297};

statetype far s_297 = { /* 33770 */
  SKULLMAN_HAND_ATTACK2_SPR, SKULLMAN_HAND_ATTACK2_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, R_SkullmanHand_Attack_R, &s_296};

statetype far s_298 = { /* 33790 */
  0, 0, step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_299};

statetype far s_299 = { /* 337b0 */
  0, 0, step, false, ps_none, 1, 0, 0,
  T_SparkShooter, NULL, R_Draw, &s_298};

statetype far s_300 = { /* 337d0 */
  SPARKSHOT1_SPR, SPARKSHOT1_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, R_SparkShot, &s_301};

statetype far s_301 = { /* 337f0 */
  SPARKSHOT2_SPR, SPARKSHOT2_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, R_SparkShot, &s_300};

statetype far s_302 = { /* 33810 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_303};

statetype far s_303 = { /* 33830 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_304 = { /* 33850 */
  RESPAWN_BEACON_INACTIVE_SPR, RESPAWN_BEACON_INACTIVE_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, C_RespawnBeacon, R_Draw, &s_304};

statetype far s_305 = { /* 33870 */
  RESPAWN_BEACON_ACTIVE1_SPR, RESPAWN_BEACON_ACTIVE1_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_306};

statetype far s_306 = { /* 33890 */
  RESPAWN_BEACON_ACTIVE2_SPR, RESPAWN_BEACON_ACTIVE2_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_307};

statetype far s_307 = { /* 338b0 */
  RESPAWN_BEACON_ACTIVE3_SPR, RESPAWN_BEACON_ACTIVE3_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_308};

statetype far s_308 = { /* 338d0 */
  RESPAWN_BEACON_ACTIVE4_SPR, RESPAWN_BEACON_ACTIVE4_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_305};


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
    SD_PlaySound(30);

    ob->nothink = US_RndT() / 16;
    return;
  }

  SD_PlaySound(23);
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

  NewState(new, &s_230);
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

  NewState(new, &s_234);

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


void sub_22b98(objtype* ob)
{
  ob->needtoreact = true;

  if (ob->health <= 0)
  {
    ob->temp1 = US_RndT() / 8;
    ob->shootable = false;
    ChangeState(ob, &s_233);
    return;
  }

  if (US_RndT() < 160)
  {
    ob->state = &s_235;
  }
}


void sub_22be7(objtype* ob)
{
  ob->needtoreact = true;

  if (ob->health <= 0)
  {
    ob->temp1 = US_RndT() / 8;
    ob->shootable = false;
    ob->state = &s_233;
    return;
  }

  if (US_RndT() < 20)
  {
    ob->state = &s_234;
  }
  else
  {
    if (US_RndT() < 100)
    {
      ob->state = &s_237;
    }

    if (US_RndT() > 200)
    {
      ob->state = &s_238;
    }
  }
}


void sub_22c59(objtype* ob)
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
    ob->state = &s_233;
  }

  PLACESPRITE;
}


void sub_22d16(objtype* ob)
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

  NewState(new, &s_241);

  SD_PlaySound(30);
}


void sub_22db0(objtype* ob)
{
  SD_PlaySound(13);

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

  NewState(new, &s_239);
}


void sub_22e5c(objtype* ob)
{
  PLACESPRITE;

  if (ob->hiteast || ob->hitwest || ob->hitsouth)
  {
    ChangeState(ob, &s_242);
    return;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_242);

    GetNewObj(true);

    new->obclass = enemyprojectileobj;
    new->active = ac_allways;
    new->x = ob->x;
    new->y = ob->y + 8*PIXGLOBAL;
    new->temp7 = 100;

    NewState(new, &s_244);
  }
}


void sub_22f1a(objtype* ob)
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


void sub_22f3f(objtype* ob)
{
  if (ob->temp1 > 0)
  {
    ob->temp1--;
  }

  if (ob->temp1 <= 0 || ob->yspeed > 0)
  {
    ob->temp1 = US_RndT() / 8;

    ChangeState(ob, &s_240);
  }

  PLACESPRITE;
}


void sub_22fa5(objtype* ob)
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
    ChangeState(ob, &s_242);

    FragBloom(ob->x, ob->y, dir_North);
    FragBloom(ob->x, ob->y, dir_South);
    FragBloom(ob->x, ob->y, dir_East);
    FragBloom(ob->x, ob->y, dir_West);
    SD_PlaySound(21);
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

  NewState(new, &s_247);
}


void T_LaserGunner_Idle(objtype* ob)
{
  ob->needtoreact = true;

  if (ob->health <= 0)
  {
    ob->temp1 = US_RndT() / 16;
    ob->shootable = false;
    ChangeState(ob, &s_251);
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
      ob->state = &s_248;
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
    ob->state = &s_247;
  }

  if (ob->xdir == 1)
  {
    shotx = ob->x + 48*PIXGLOBAL;
  }
  else
  {
    shotx = ob->x;
  }

  if (SpawnEnemyShot(shotx, ob->y + 26*PIXGLOBAL, &s_252) == -1)
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

  SD_PlaySound(21);
}


void C_EnemyLaserShot(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj || hit->obclass == pushblockobj)
  {
    ob->y -= 8*PIXGLOBAL;
    ChangeState(ob, &s_253);
    return;
  }
}


void R_EnemyLaserShot(objtype* ob)
{
  if (ob->hitnorth || ob->hiteast || ob->hitsouth || ob->hitwest)
  {
    SD_PlaySound(29);
    ob->y -= 8*PIXGLOBAL;
    ChangeState(ob, &s_253);
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

  NewState(new, &s_257);
}


void R_PushBlock_OnGround(objtype* ob)
{
  if (!ob->hitnorth)
  {
    ChangeState(ob, &s_258);
  }

  PLACESPRITE;
}


void R_PushBlock_Falling(objtype* ob)
{
  if (ob->hitnorth)
  {
    ChangeState(ob, &s_257);
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
      SD_PlaySound(37);
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

  NewState(new, &s_259);
}


void T_FallingBlock(objtype* ob)
{
  if (ob->temp7 != 35)
  {
    if (--ob->temp7 <= 0)
    {
      ChangeState(ob, &s_260);
      SD_PlaySound(36);
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

  NewState(new, &s_261);
}


void T_Crusher_Waiting(objtype* ob)
{
  if (crusheractive == 1)
  {
    ChangeState(ob, &s_262);
  }
}


void T_Crusher_Moving(objtype* ob)
{
  if (--ob->temp7 <= 0)
  {
    ob->temp7 = 15;
    SD_PlaySound(35);
  }
}


void R_Crusher(objtype* ob)
{
  if (ob->hitnorth)
  {
    crusheractive = -1;
    ChangeState(ob, &s_261);
    SD_PlaySound(8);
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

  NewState(new, &s_263);
}


void sub_2370e(objtype* ob)
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


void sub_237bf(objtype* ob)
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
      SD_PlaySound(0);
    }

    ob->yspeed = -ob->yspeed;
  }

  if (ob->hitnorth)
  {
    if (ob->tileright >= originxtile && ob->tileleft <= originxtilemax &&
        ob->tiletop >= originytile && ob->tilebottom <= originytilemax)
    {
      SD_PlaySound(0);
    }

    ob->yspeed = -64 - (US_RndT() >> 4);
    ob->temp1 = 2;

    ChangeState(ob, &s_267);
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

  NewState(new, &s_268);

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

  NewState(new, &s_271);

  SD_PlaySound(39);
}


void T_SlimeDropEmerging(objtype* ob)
{
  if (US_RndT() < 100)
  {
    ob->state = &s_273;
  }
}


void R_SlimeDrop(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->state = &s_274;
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

  NewState(new, &s_278);
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
      ob->state = &s_279;
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
    ob->state = &s_278;
  }

  if (ob->xdir == 1)
  {
    shotx = ob->x + 32*PIXGLOBAL;
  }
  else
  {
    shotx = ob->x;
  }

  if (SpawnEnemyShot(shotx, ob->y + 8*PIXGLOBAL, &s_252) == -1)
    return;

  new->xspeed = ob->xdir * 60;
  new->yspeed = 0;

  SD_PlaySound(6);
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

  NewState(new, &s_282);
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

  NewState(new, &s_286);
}


void C_LandMine(objtype* ob, objtype* hit)
{
  if (hit->shootable && hit->obclass != pushblockobj)
  {
    FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_East + 10);
    FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, dir_West + 10);

    ob->obclass = fireballobj;
    ob->temp6 = 1;
    SD_PlaySound(7);

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
      NewState(new, &s_290);
      break;

    case 1:
      NewState(new, &s_291);
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
    ob->state = &s_292;
    ob->ydir = -1;
  }

  PLACESPRITE;
}


void R_SkullmanHand_Attack_R(objtype* ob)
{
  if (ob->hitnorth)
  {
    ob->state = &s_293;
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
    ob->state = &s_294;
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
    ob->state = &s_294;
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

  ob->state = &s_294;
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

  ob->state = &s_296;
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

  NewState(new, &s_289);
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
    if (ob->state == &s_288)
    {
      ob->state = &s_289;
    }
    else
    {
      ob->state = &s_288;
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

  NewState(new, &s_298);
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

  NewState(new, &s_300);
  SD_PlaySound(21);
}


void R_SparkShot(objtype* ob)
{
  if (ob->hitnorth || ob->hiteast || ob->hitsouth || ob->hitwest)
  {
    SD_PlaySound(29);
    ChangeState(ob, &s_302);
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

  NewState(new, &s_304);
}


void C_RespawnBeacon(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj)
  {
    playerrestorex = player->x;
    playerrestorey = player->y;
    ChangeState(ob, &s_305);
    SD_PlaySound(40);

    if (!gamestate.helpmsgbeacon)
    {
      ShowHelpMessage("Continue from beacons when you get killed.\n");
      gamestate.helpmsgbeacon = true;
    }
  }

  ob++;
}
