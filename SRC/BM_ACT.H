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


void SpawnScoreBox(void);
void FireBullet(Uint16 x, Uint16 y, Sint16 xdir, Sint16 damage);
void DealDamage(objtype* ob, Sint16 amount);
void SpawnSuperPlasmaBolt(Uint16 x, Uint16 y, Sint16 dir);
void HostageDialog(void);
void ShowCompatibilityInfoMessage(void);
void BossDialog(void);

void C_GrenadeExplosion(objtype* ob, objtype* hit);
void ChunkBloom(objtype* ob, Uint16 x, Uint16 y, Direction dir);
void FragBloom(Uint16 x, Uint16 y, Direction dir);
void SpawnPlayer(Sint16 x, Sint16 y, Sint16 xdir);
void ThrowGrenade(Uint16 x, Uint16 y, Direction dir);
void SpawnBulletImpact(Uint16 x, Uint16 y);
void SpawnShot(Uint16 x, Uint16 y, Sint16 dir);
void SpawnLaserShot(Uint16 x, Uint16 y, Sint16 dir);
void SpawnSuperPlasmaBolt(Uint16 x, Uint16 y, Sint16 dir);

void SpawnNapalmBomb(objtype* ob);
Sint16 SpawnEnemyShot(Sint16 x, Sint16 y, statetype far* state);
void SpawnParachuteBot(objtype* ob);
void SpawnElevator(Sint16 x, Sint16 y, arrowdirtype dir);
void SpawnApogeeLogo(Sint16 x, Sint16 y, arrowdirtype dir);
void SpawnHelicopter(Sint16 x, Sint16 y, arrowdirtype dir);
void SpawnParachuteBot(objtype* ob);
void SpawnSpitterSnake(Sint16 x, Sint16 y);
void SpawnSewerMutant(Sint16 x, Sint16 y);
void SpawnHostage(Sint16 x, Sint16 y, Sint16 type);
void SpawnDrMangleHologram(Sint16 x, Sint16 y);
void SpawnDrMangle(Sint16 x, Sint16 y);
void SpawnPickup(Sint16 x, Sint16 y, Sint16 type);
void SpawnRobopal(Sint16 x, Sint16 y);
void SpawnSlug(Sint16 x, Sint16 y);
void SpawnGhostlySlug(Sint16 x, Sint16 y);
void SpawnBomb(Sint16 x, Sint16 y);
void SpawnFireImp(Sint16 x, Sint16 y);
void SpawnHedgehog(Sint16 x, Sint16 y);
void SpawnBrawler(Sint16 x, Sint16 y);
void SpawnCeilingWalker(Sint16 x, Sint16 y);
void SpawnCrawlingSlime(Sint16 x, Sint16 y);
void SpawnBigExplosion(Sint16 x, Sint16 y);
void SpawnTankBot(Sint16 x, Sint16 y);
void SpawnLaserGunner(Sint16 x, Sint16 y);
void SpawnPushBlock(Sint16 x, Sint16 y);
void SpawnFallingBlock(Sint16 x, Sint16 y);
void SpawnCrusher(Sint16 x, Sint16 y);
void SpawnBounceBot(Sint16 x, Sint16 y);
void SpawnSlimeDropper(Sint16 x, Sint16 y);
void SpawnLaserTurret(Sint16 x, Sint16 y);
void SpawnAsteroid(Sint16 x, Sint16 y);
void SpawnLandMine(Sint16 x, Sint16 y);
void SpawnSkullmanHand(Sint16 x, Sint16 y, Sint16 t);
void SpawnSkullman(Sint16 x, Sint16 y);
void SpawnSparkShooter(Sint16 x, Sint16 y);
void SpawnRespawnBeacon(Sint16 x, Sint16 y);


extern Uint16 bounceangle[8][8];
extern boolean firerobopal;
extern boolean drmangleactive;
extern Sint16 hbardivisor;
extern Uint16 invincible;
extern Uint16 colorstep;
extern Sint16 doordestx;
extern Sint16 doordesty;
extern Uint16 jumptime;
extern Uint8 unktime;

extern boolean jumpcheat;
extern boolean godmode;
extern boolean button0held, button1held, fireheld;

extern Sint16 skullmanactivestate;
extern Sint16 crusheractive;


extern statetype far s_player_dying;
extern statetype far s_player_dead;
extern statetype far s_player_fireball;
extern statetype far s_player_shielded1;
extern statetype far s_player_shielded2;
extern statetype far s_player_unused;
extern statetype far s_player_standing;
extern statetype far s_player_activated_trigger;
extern statetype far s_player_unused2;
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

extern statetype far s_score;
extern statetype far s_bulletimpact1;
extern statetype far s_bulletimpact2;
extern statetype far s_bulletimpact3;
extern statetype far s_gib_bone1;
extern statetype far s_gib_bone2;
extern statetype far s_gib_eyeball1;
extern statetype far s_gib_eyeball2;
extern statetype far s_gib_flesh1;
extern statetype far s_gib_flesh2;
extern statetype far s_gibs_on_floor;
extern statetype far s_metal_debris1;
extern statetype far s_metal_debris2;
extern statetype far s_metal_debris3;
extern statetype far s_metal_debris4;
extern statetype far s_metal_debris_on_floor;
extern statetype far s_fireball1;
extern statetype far s_fireball2;
extern statetype far s_fireball3;
extern statetype far s_fireball4;
extern statetype far s_grenade1;
extern statetype far s_grenade2;
extern statetype far s_grenade3;
extern statetype far s_grenade4;
extern statetype far s_redgrenade1;
extern statetype far s_redgrenade2;
extern statetype far s_redgrenade3;
extern statetype far s_redgrenade4;
extern statetype far s_grenadeexplosion1;
extern statetype far s_grenadeexplosion2;
extern statetype far s_grenadeexplosion3;
extern statetype far s_grenadeexplosion4;
extern statetype far s_grenadeexplosion5;
extern statetype far s_grenadeexplosion6;
extern statetype far s_robopalrocket1;
extern statetype far s_robopalrocket2;
extern statetype far s_lasershot;
extern statetype far s_superplasmabolt;
extern statetype far s_rocketimpact1;
extern statetype far s_rocketimpact2;
extern statetype far s_plasmaboltimpact1;
extern statetype far s_plasmaboltimpact2;

extern statetype far s_platform;
extern statetype far s_apogeelogo;
extern statetype far s_helicopter1;
extern statetype far s_helicopter2;
extern statetype far s_helicopter_spawnbot;
extern statetype far s_parachutebot_walk1;
extern statetype far s_parachutebot_walk2;
extern statetype far s_parachutebot_attack;
extern statetype far s_parachutebot_falling;
extern statetype far s_spitsnake_walk1;
extern statetype far s_spitsnake_walk2;
extern statetype far s_spitsnake_wait1;
extern statetype far s_spitsnake_wait2;
extern statetype far s_spitsnake_attack1;
extern statetype far s_spitsnake_attack2;
extern statetype far s_spitsnake_projectile1;
extern statetype far s_spitsnake_projectile2;
extern statetype far s_sewermutant1;
extern statetype far s_sewermutant2;
extern statetype far s_sewermutant_attack;
extern statetype far s_sewermutant_projectile1;
extern statetype far s_sewermutant_projectile2;
extern statetype far s_hostage1_1;
extern statetype far s_hostage1_2;
extern statetype far s_hostage2_1;
extern statetype far s_hostage2_2;
extern statetype far s_hostage3_1;
extern statetype far s_hostage3_2;
extern statetype far s_drmangle_hologram1;
extern statetype far s_drmangle_hologram2;
extern statetype far s_drmangle_hologram3;
extern statetype far s_drmangle_hologram1_faded;
extern statetype far s_drmangle_hologram2_faded;
extern statetype far s_drmangle_hologram3_faded;
extern statetype far s_drmangle_hologram_attacking;
extern statetype far s_drmangle_typing1;
extern statetype far s_drmangle_typing2;
extern statetype far s_drmangle_monster1;
extern statetype far s_drmangle_monster2;
extern statetype far s_drmangle_monster_jumping;
extern statetype far s_drmangle_dying;
extern statetype far s_drmangle_dead;
extern statetype far s_drmangle_dead2;

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

extern statetype far s_bigexplosion1;
extern statetype far s_bigexplosion2;
extern statetype far s_bigexplosion3;
extern statetype far s_tankbot_dying;
extern statetype far s_tankbot_waiting;
extern statetype far s_tankbot_moving1;
extern statetype far s_tankbot_moving2;
extern statetype far s_tankbot_shooting;
extern statetype far s_tankbot_launchbomb;
extern statetype far s_tankbot_bomb_flying;
extern statetype far s_tankbot_bomb_landing;
extern statetype far s_tankbot_shot;
extern statetype far s_tankbot_shot_explode1;
extern statetype far s_tankbot_shot_explode2;
extern statetype far s_napalmfire1;
extern statetype far s_napalmfire2;
extern statetype far s_napalmfire3;
extern statetype far s_lasergunner_idle;
extern statetype far s_lasergunner_attack1;
extern statetype far s_lasergunner_attack2;
extern statetype far s_lasergunner_attack3;
extern statetype far s_lasergunner_attack4;
extern statetype far s_enemy_laser_shot;
extern statetype far s_bigshotimpact1;
extern statetype far s_bigshotimpact2;
extern statetype far s_drmangleshot1;
extern statetype far s_drmangleshot2;
extern statetype far s_pushblock;
extern statetype far s_pushblock_falling;
extern statetype far s_fallingblock_idle;
extern statetype far s_fallingblock_falling;
extern statetype far s_crusher_idle;
extern statetype far s_crusher_moving;
extern statetype far s_bouncebot1;
extern statetype far s_bouncebot2;
extern statetype far s_bouncebot3;
extern statetype far s_bouncebot4;
extern statetype far s_bouncebot5;
extern statetype far s_slimedropper1;
extern statetype far s_slimedropper2;
extern statetype far s_slimedropper3;
extern statetype far s_slime_drop1;
extern statetype far s_slime_drop2;
extern statetype far s_slime_drop3;
extern statetype far s_slimedrop_splat1;
extern statetype far s_slimedrop_splat2;
extern statetype far s_slimedrop_splat3;
extern statetype far s_slimedrop_splat4;
extern statetype far s_turret_idle;
extern statetype far s_turret_attack1;
extern statetype far s_turret_attack2;
extern statetype far s_turret_attack3;
extern statetype far s_asteroid1;
extern statetype far s_asteroid2;
extern statetype far s_asteroid3;
extern statetype far s_asteroid4;
extern statetype far s_landmine1;
extern statetype far s_landmine2;
extern statetype far s_skullman1;
extern statetype far s_skullman2;
extern statetype far s_skullmanhand_r1;
extern statetype far s_skullmanhand_l1;
extern statetype far s_skullmanhand_r2;
extern statetype far s_skullmanhand_l2;
extern statetype far s_skullmanhand_attack_r1;
extern statetype far s_skullmanhand_attack_r2;
extern statetype far s_skullmanhand_attack_l1;
extern statetype far s_skullmanhand_attack_l2;
extern statetype far s_sparkshooter1;
extern statetype far s_sparkshooter2;
extern statetype far s_sparkshot1;
extern statetype far s_sparkshot2;
extern statetype far s_sparkshot_explode1;
extern statetype far s_sparkshot_explode2;
extern statetype far s_respawn_beacon_idle;
extern statetype far s_respawn_beacon1;
extern statetype far s_respawn_beacon2;
extern statetype far s_respawn_beacon3;
extern statetype far s_respawn_beacon4;

#endif
