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

    case 37:
      ClipToSpriteSide(ob, hit);
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
#if EPISODE == 2
      // TODO: Use correct state (player slug form)
      if ((ob->state == &s_player_standing || ob->state == &s_player_standing)
          && hit->shootable && hit->dmgflash == 0)
      {
        DealDamage(hit, 1);
        break;
      }
#endif

      if (hit->spawnedby == sb_player) break;

      if (!invincible)
      {
        DamagePlayer(ob, 1);
      }
      break;
  }
}
