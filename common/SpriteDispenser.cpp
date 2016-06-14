//
// Created by marcos on 22/05/16.
//

#include "SpriteDispenser.h"

#include <gdkmm/general.h>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "../entities.h"
#include "MegamanBeginsConstants.h"

#define IMG_PATH "../sprites"
#define MOB_PATH (string) IMG_PATH + "/mobs/"
#define BSS_PATH (string) IMG_PATH + "/bosses/"
#define BCK_PATH (string) IMG_PATH + "/level/background/"
#define TLE_PATH (string) IMG_PATH + "/level/tiles/"
#define WEP_PATH (string) IMG_PATH + "/weapons/"
#define ITM_PATH (string) IMG_PATH + "/items/"

SpriteDispenser::SpriteDispenser() {
	double tileWidth = ceil((double)Gdk::screen_width()/(double)TILES_HORIZONTAL)+1;
	double tileHeight = ceil((double)Gdk::screen_height()/(double)TILES_VERTICAL)+1;
	tileSize = std::max(tileHeight,tileWidth);

	//PATHS
	//megaman
	paths[MEGAMAN_IDLE_0] = (string) IMG_PATH + "/megaman pc/megaman_idle.png";
	paths[MEGAMAN_IDLE_1] = (string) IMG_PATH + "/megaman pc/megaman_idle1.png";
	paths[MEGAMAN_IDLE_2] = (string) IMG_PATH + "/megaman pc/megaman_idle2.png";
	paths[MEGAMAN_ATTACK] = (string) IMG_PATH + "/megaman pc/megaman_attack0.png";
	paths[MEGAMAN_ATTACK_CLIMB] = (string) IMG_PATH + "/megaman pc/megaman_attack_climbing.png";
	paths[MEGAMAN_ATTACK_JUMP] = (string) IMG_PATH + "/megaman pc/megaman_attack_jumping.png";
	paths[MEGAMAN_ATTACK_RUN_0] = (string) IMG_PATH + "/megaman pc/megaman_running.png";
	paths[MEGAMAN_ATTACK_RUN_1] = (string) IMG_PATH + "/megaman pc/megaman_running1.png";
	paths[MEGAMAN_ATTACK_RUN_2] = (string) IMG_PATH + "/megaman pc/megaman_running2.png";
	paths[MEGAMAN_BOMB_THROW] = (string) IMG_PATH + "/megaman pc/megaman_bomb_throw.png";
	paths[MEGAMAN_CLIMB] = (string) IMG_PATH + "/megaman pc/megaman_climb.png";
	paths[MEGAMAN_CLIMB_TOP] = (string) IMG_PATH + "/megaman pc/megaman_climb_ontop.png";
	paths[MEGAMAN_FALL] = (string) IMG_PATH + "/megaman pc/megaman_fall.png";
	paths[MEGAMAN_JUMP] = (string) IMG_PATH + "/megaman pc/megaman_jump.png";
	paths[MEGAMAN_RUN_0] = (string) IMG_PATH + "/megaman pc/megaman_run0.png";
	paths[MEGAMAN_RUN_1] = (string) IMG_PATH + "/megaman pc/megaman_run1.png";
	paths[MEGAMAN_RUN_2] = (string) IMG_PATH + "/megaman pc/megaman_run2.png";
	paths[MEGAMAN_SWIPE] = (string) IMG_PATH + "/megaman pc/megaman_swipe.png";
	//tiles
	paths[BOSS_DOOR] = TLE_PATH + "boss_door.png";
	paths[CABLE_EDGE_0] = TLE_PATH + "cable_edge0.png";
	paths[CABLE_EDGE_1] = TLE_PATH + "cable_edge1.png";
	paths[CABLE_FLOOR_0] = TLE_PATH + "cable_floor0.png";
	paths[STONE_WALL] = TLE_PATH + "stone_wall.png";
	paths[STONE_LADDER] = TLE_PATH + "stone_ladder.png";
	paths[SPIKE] = TLE_PATH + "stone_spike.png";
	paths[SKY_PLATFORM] = TLE_PATH + "sky_platform.png";
	paths[BOSS_DOOR] = TLE_PATH + "boss_door.png";

	//weapons
	paths[BOMB] = WEP_PATH + "bombman_weapon.png";
	paths[FIREMAN_FLAME] = WEP_PATH + "fireman_weapon0.png";
	paths[MEGAMAN_FLAME] = WEP_PATH + "cable_floor0.png";
	paths[MEGAMAN_WEAPON] = WEP_PATH + "megaman_weapon.png";
	paths[MET_WEAPON] = WEP_PATH + "met_weapon.png";
	paths[SNIPER_WEAPON] = WEP_PATH + "sniper_weapon.png";
	paths[RINGMAN_WEAPON] = WEP_PATH + " ringman_weapon0.png";
	paths[MAGNETMAN_WEAPON] = WEP_PATH + "sparkman_weapon1_0.png";
	paths[SPARKMAN_SPARKS] = WEP_PATH + "stone_spike.png";
	paths[SPARKMAN_GENKIDAMA] = WEP_PATH + "sky_platform.png";
	//Items
	//los sprites de esto no son los correctos, despues lo arreglo
	paths[BIG_ENERGY] = ITM_PATH + "big_energy_capsule.png";
	paths[SMALL_ENERGY] = ITM_PATH + "small_energy_capsule.png";
	paths[BIG_PLASMA] = ITM_PATH + "big_plasma_capsule.png";
	paths[SMALL_PLASMA] = ITM_PATH + "small_plasma_capsule.png";
	paths[LIFE] = ITM_PATH + "life.png";
	//Mobs
	paths[BUMBY_0] = MOB_PATH + "bumby0.png";
	paths[BUMBY_1] = MOB_PATH + "bumby1.png";
	paths[MET_HIDDEN] = MOB_PATH + "met_hidden.png";
	paths[MET_TRANSITION] = MOB_PATH + "met_transition.png";
	paths[MET_VULNERABLE] = MOB_PATH + "met_vulnerable.png";
	paths[SNIPER_ATTACK] = MOB_PATH + "sniper_attacking.png";
	paths[SNIPER_DEFEND] = MOB_PATH + "sniper_defended.png";
	paths[SNIPER_JUMP] = MOB_PATH + "sniper_jumping.png";
	paths[SNIPER_VULNERABLE] = MOB_PATH + "sniper_vulnerable.png";
	paths[JUMPING_SNIPER] = MOB_PATH + "sniper_jumping.png";
	//BombMan
	paths[BOMBMAN_ATTACK] = BSS_PATH + "bombman/bombman_cast_attack.png";
	paths[BOMBMAN_CAST] = BSS_PATH + "bombman/bombman_cast_attack1.png";
	paths[BOMBMAN_IDLE] = BSS_PATH + "bombman/bombman_idle.png";
	paths[BOMBMAN_JUGGLE] = BSS_PATH + "bombman/bombman_juggle.png";
	paths[BOMBMAN_JUMP] = BSS_PATH + "bombman/bombman_jump.png";
	paths[BOMBMAN_JUMP_FRONT] = BSS_PATH + "bombman/bombman_jump_ahead.png";
	paths[BOMBMAN_JUMP_BACK] = BSS_PATH + "bombman/bombman_jump_back.png";
	//FireMan
	paths[FIREMAN_CAST_0] = BSS_PATH + "fireman.json/fireman_cast0.png";
	paths[FIREMAN_CAST_1] = BSS_PATH + "fireman.json/fireman_cast1.png";
	paths[FIREMAN_IDLE_0] = BSS_PATH + "fireman.json/fireman_idle.png";
	paths[FIREMAN_IDLE_1] = BSS_PATH + "fireman.json/fireman_idle1.png";
	paths[FIREMAN_JUMP] = BSS_PATH + "fireman.json/fireman_jump.png";
	paths[FIREMAN_RUN_0] = BSS_PATH + "fireman.json/fireman_run0.png";
	paths[FIREMAN_RUN_1] = BSS_PATH + "fireman.json/fireman_run1.png";
	paths[FIREMAN_RUN_2] = BSS_PATH + "fireman.json/fireman_run2.png";
	paths[FIREMAN_RUN_3] = BSS_PATH + "fireman.json/fireman_run3.png";
	//MagnetMan
	paths[MAGNETMAN_ATTACK] = BSS_PATH + "magnetman/magnetman_attack.png";
	paths[MAGNETMAN_CELEBRATE] = BSS_PATH + "magnetman/magnetman_celebrate.png";
	paths[MAGNETMAN_DEFEND_0] = BSS_PATH + "magnetman/magnetman_defend0.png";
	paths[MAGNETMAN_DEFEND_1] = BSS_PATH + "magnetman/magnetman_defend1.png";
	paths[MAGNETMAN_DEFEND_2] = BSS_PATH + "magnetman/magnetman_defend2.png";
	paths[MAGNETMAN_IDLE] = BSS_PATH + "magnetman/magnetman_idle.png";
	paths[MAGNETMAN_JUMP_0] = BSS_PATH + "magnetman/magnetman_jump0.png";
	paths[MAGNETMAN_JUMP_1] = BSS_PATH + "magnetman/magnetman_jump1.png";
	paths[MAGNETMAN_PREPARED] = BSS_PATH + "magnetman/magnetman_prepared.png";
	//RingMan
	paths[RINGMAN_CAST] = BSS_PATH + "ringman/ringman_cast_standing.png";
	paths[RINGMAN_IDLE] = BSS_PATH + "ringman/ringman_idle.png";
	paths[RINGMAN_JUMP] = BSS_PATH + "ringman/ringman_jump.png";
	paths[RINGMAN_PREPARE_JUMP_0] = BSS_PATH + "ringman/ringman_prepare_jumping0.png";
	paths[RINGMAN_PREPARE_JUMP_1] = BSS_PATH + "ringman/ringman_prepare_jumping1.png";
	paths[RINGMAN_PREPARE_STAND_0] = BSS_PATH + "ringman/ringman_prepare_standing_0.png";
	paths[RINGMAN_PREPARE_STAND_1] = BSS_PATH + "ringman/ringman_prepare_standing_1.png";
	paths[RINGMAN_RUN_0] = BSS_PATH + "ringman/ringman_run0.png";
	paths[RINGMAN_RUN_1] = BSS_PATH + "ringman/ringman_run1.png";
	paths[RINGMAN_RUN_2] = BSS_PATH + "ringman/ringman_run2.png";
	paths[RINGMAN_RUN_3] = BSS_PATH + "ringman/ringman_run3.png";
	//SparkMan
	paths[SPARKMAN_CAST_ATTACK_1] = BSS_PATH + "sparkman/sparkman_cast_attack1.png";
	paths[SPARKMAN_CAST_ATTACK_2] = BSS_PATH + "sparkman/sparkman_cast_attack2.png";
	paths[SPARKMAN_IDLE] = BSS_PATH + "sparkman/sparkman_idle.png";
	paths[SPARKMAN_JUMP] = BSS_PATH + "sparkman/sparkman_jump.png";
	paths[SPARKMAN_PREPARE_0_ATTACK_1] = BSS_PATH + "sparkman/sparkman_prepare0_attack1.png";
	paths[SPARKMAN_PREPARE_0_ATTACK_2] = BSS_PATH + "sparkman/sparkman_prepare0_attack2.png";
	paths[SPARKMAN_PREPARE_1_ATTACK_1] = BSS_PATH + "sparkman/sparkman_prepare1_attack1.png";
	paths[SPARKMAN_PREPARE_1_ATTACK_2] = BSS_PATH + "sparkman/sparkman_prepare1_attack2.png";
	paths[SPARKMAN_PREPARE_2_ATTACK_1] = BSS_PATH + "sparkman/sparkman_prepare2_attack1.png";
	paths[SPARKMAN_PREPARE_2_ATTACK_2] = BSS_PATH + "sparkman/sparkman_prepare2_attack2.png";
	//Backgrounds
	paths[CITY] = BCK_PATH + "city.png";
    paths[SNOW] = BCK_PATH + "snow.png";
    paths[SPOOKY] = BCK_PATH + "spooky.png";
    paths[ROCK] = BCK_PATH + "rock.png";
    paths[VALLEY] = BCK_PATH + "valley.png";

	//SIZES
	heigths[MEGAMAN_IDLE_0] = tileSize*1.0;//tileSide*1.5625;
	heigths[MEGAMAN_IDLE_1] = tileSize*1.5625;
	heigths[MEGAMAN_IDLE_2] = tileSize*1.5625;
	heigths[MEGAMAN_ATTACK] = tileSize*1.0;
	heigths[MEGAMAN_ATTACK_CLIMB] = tileSize*1.0;
	heigths[MEGAMAN_ATTACK_JUMP] = tileSize*1.0;
	heigths[MEGAMAN_ATTACK_RUN_0] = tileSize*1.0;
	heigths[MEGAMAN_ATTACK_RUN_1] = tileSize*1.0;
	heigths[MEGAMAN_ATTACK_RUN_2] = tileSize*1.0;
	heigths[MEGAMAN_BOMB_THROW] = tileSize*1.0;
	heigths[MEGAMAN_CLIMB] = tileSize*1.0;
	heigths[MEGAMAN_CLIMB_TOP] = tileSize*1.0;
	heigths[MEGAMAN_FALL] = tileSize*1.0;
	heigths[MEGAMAN_JUMP] = tileSize*1.0;
	heigths[MEGAMAN_RUN_0] = tileSize*1.0;
	heigths[MEGAMAN_RUN_1] = tileSize*1.0;
	heigths[MEGAMAN_RUN_2] = tileSize*1.0;
	heigths[MEGAMAN_SWIPE] = tileSize*1.0;
	//weapons
	heigths[BOMB] = tileSize*0.2;
	heigths[FIREMAN_FLAME] = tileSize*0.2;
	heigths[MEGAMAN_FLAME] = tileSize*0.2;
	heigths[MEGAMAN_WEAPON] = tileSize*0.2;
	heigths[MET_WEAPON] = tileSize*0.2;
	heigths[SNIPER_WEAPON] = tileSize*0.2;
	heigths[RINGMAN_WEAPON] = tileSize*0.2;
	heigths[MAGNETMAN_WEAPON] = tileSize*0.2;
	heigths[SPARKMAN_SPARKS] = tileSize*0.2;
	heigths[SPARKMAN_GENKIDAMA] =tileSize*0.2;
	//Items
	//los sprites de esto no son los correctos, despues lo arreglo
	heigths[BIG_ENERGY] = tileSize*0.2;
	heigths[SMALL_ENERGY] = tileSize*0.2;
	heigths[BIG_PLASMA] = tileSize*0.2;
	heigths[SMALL_PLASMA] = tileSize*0.2;
	heigths[LIFE] = tileSize*0.2;
	//tiles
	heigths[BOSS_DOOR] = tileSize*1.0;
	heigths[CABLE_EDGE_0] = tileSize*1.0;
	heigths[CABLE_EDGE_1] = tileSize*1.0;
	heigths[CABLE_FLOOR_0] = tileSize*1.0;
	heigths[STONE_WALL] = tileSize*1.0;
	heigths[STONE_LADDER] = tileSize*1.0;
	heigths[SPIKE] = tileSize*1.0;
	heigths[SKY_PLATFORM] = tileSize*1.0;
	//Mobs
	heigths[BUMBY_0] = tileSize*1.0;
	heigths[BUMBY_1] = tileSize*1.0;
	heigths[MET_HIDDEN] = tileSize*1.0;
	heigths[MET_TRANSITION] = tileSize*1.0;
	heigths[MET_VULNERABLE] = tileSize*1.0;
	heigths[SNIPER_ATTACK] = tileSize*1.0;
	heigths[SNIPER_DEFEND] = tileSize*1.0;
	heigths[SNIPER_JUMP] = tileSize*1.0;
	heigths[SNIPER_VULNERABLE] = tileSize*1.0;
	heigths[JUMPING_SNIPER] = tileSize*1.0;
	//BombMan
	heigths[BOMBMAN_ATTACK] = tileSize*1.0;
	heigths[BOMBMAN_CAST] = tileSize*1.0;
	heigths[BOMBMAN_IDLE] = tileSize*1.0;
	heigths[BOMBMAN_JUGGLE] = tileSize*1.0;
	heigths[BOMBMAN_JUMP] = tileSize*1.0;
	heigths[BOMBMAN_JUMP_FRONT] = tileSize*1.0;
	heigths[BOMBMAN_JUMP_BACK] = tileSize*1.0;
	//FireMan
	heigths[FIREMAN_CAST_0] = tileSize*1.0;
	heigths[FIREMAN_CAST_1] = tileSize*1.0;
	heigths[FIREMAN_IDLE_0] = tileSize*1.0;
	heigths[FIREMAN_IDLE_1] = tileSize*1.0;
	heigths[FIREMAN_JUMP] = tileSize*1.0;
	heigths[FIREMAN_RUN_0] = tileSize*1.0;
	heigths[FIREMAN_RUN_1] = tileSize*1.0;
	heigths[FIREMAN_RUN_2] = tileSize*1.0;
	heigths[FIREMAN_RUN_3] = tileSize*1.0;
	//MagnetMan
	heigths[MAGNETMAN_ATTACK] = tileSize*1.0;
	heigths[MAGNETMAN_CELEBRATE] = tileSize*1.0;
	heigths[MAGNETMAN_DEFEND_0] = tileSize*1.0;
	heigths[MAGNETMAN_DEFEND_1] = tileSize*1.0;
	heigths[MAGNETMAN_DEFEND_2] = tileSize*1.0;
	heigths[MAGNETMAN_IDLE] = tileSize*1.0;
	heigths[MAGNETMAN_JUMP_0] = tileSize*1.0;
	heigths[MAGNETMAN_JUMP_1] = tileSize*1.0;
	heigths[MAGNETMAN_PREPARED] = tileSize*1.0;
	//RingMan
	heigths[RINGMAN_CAST] = tileSize*1.0;
	heigths[RINGMAN_IDLE] = tileSize*1.0;
	heigths[RINGMAN_JUMP] = tileSize*1.0;
	heigths[RINGMAN_PREPARE_JUMP_0] = tileSize*1.0;
	heigths[RINGMAN_PREPARE_JUMP_1] = tileSize*1.0;
	heigths[RINGMAN_PREPARE_STAND_0] = tileSize*1.0;
	heigths[RINGMAN_PREPARE_STAND_1] = tileSize*1.0;
	heigths[RINGMAN_RUN_0] = tileSize*1.0;
	heigths[RINGMAN_RUN_1] = tileSize*1.0;
	heigths[RINGMAN_RUN_2] = tileSize*1.0;
	heigths[RINGMAN_RUN_3] = tileSize*1.0;
	//SparkMan
	heigths[SPARKMAN_CAST_ATTACK_1] = tileSize*1.0;
	heigths[SPARKMAN_CAST_ATTACK_2] = tileSize*1.0;
	heigths[SPARKMAN_IDLE] = tileSize*1.0;
	heigths[SPARKMAN_JUMP] = tileSize*1.0;
	heigths[SPARKMAN_PREPARE_0_ATTACK_1] = tileSize*1.0;
	heigths[SPARKMAN_PREPARE_0_ATTACK_2] = tileSize*1.0;
	heigths[SPARKMAN_PREPARE_1_ATTACK_1] = tileSize*1.0;
	heigths[SPARKMAN_PREPARE_1_ATTACK_2] = tileSize*1.0;
	heigths[SPARKMAN_PREPARE_2_ATTACK_1] = tileSize*1.0;
	heigths[SPARKMAN_PREPARE_2_ATTACK_2] = tileSize*1.0;

	//WIDTHS
	widths[MEGAMAN_IDLE_0] = tileSize*1.0;//tileSide*1.625;
	widths[MEGAMAN_IDLE_1] = tileSize*1.625;
	widths[MEGAMAN_IDLE_2] = tileSize*1.625;
	widths[MEGAMAN_ATTACK] = tileSize*1.0;
	widths[MEGAMAN_ATTACK_CLIMB] = tileSize*1.0;
	widths[MEGAMAN_ATTACK_JUMP] = tileSize*1.0;
	widths[MEGAMAN_ATTACK_RUN_0] = tileSize*1.0;
	widths[MEGAMAN_ATTACK_RUN_1] = tileSize*1.0;
	widths[MEGAMAN_ATTACK_RUN_2] = tileSize*1.0;
	widths[MEGAMAN_BOMB_THROW] = tileSize*1.0;
	widths[MEGAMAN_CLIMB] = tileSize*1.0;
	widths[MEGAMAN_CLIMB_TOP] = tileSize*1.0;
	widths[MEGAMAN_FALL] = tileSize*1.0;
	widths[MEGAMAN_JUMP] = tileSize*1.0;
	widths[MEGAMAN_RUN_0] = tileSize*1.0;
	widths[MEGAMAN_RUN_1] = tileSize*1.0;
	widths[MEGAMAN_RUN_2] = tileSize*1.0;
	widths[MEGAMAN_SWIPE] = tileSize*1.0;
	//weapons
	widths[BOMB] = tileSize*0.2;
	widths[FIREMAN_FLAME] = tileSize*0.2;
	widths[MEGAMAN_FLAME] = tileSize*0.2;
	widths[MEGAMAN_WEAPON] = tileSize*0.2;
	widths[MET_WEAPON] = tileSize*0.2;
	widths[SNIPER_WEAPON] = tileSize*0.2;
	widths[RINGMAN_WEAPON] = tileSize*0.2;
	widths[MAGNETMAN_WEAPON] = tileSize*0.2;
	widths[SPARKMAN_SPARKS] = tileSize*0.2;
	widths[SPARKMAN_GENKIDAMA] =tileSize*0.2;
	//Items
	//los sprites de esto no son los correctos, despues lo arreglo
	widths[BIG_ENERGY] = tileSize*0.2;
	widths[SMALL_ENERGY] = tileSize*0.2;
	widths[BIG_PLASMA] = tileSize*0.2;
	widths[SMALL_PLASMA] = tileSize*0.2;
	widths[LIFE] = tileSize*0.2;
	//tiles
	widths[BOSS_DOOR] = tileSize*1.0;
	widths[CABLE_EDGE_0] = tileSize*1.0;
	widths[CABLE_EDGE_1] = tileSize*1.0;
	widths[CABLE_FLOOR_0] = tileSize*1.0;
	widths[STONE_WALL] = tileSize*1.0;
	widths[STONE_LADDER] = tileSize*1.0;
	widths[SPIKE] = tileSize*1.0;
	widths[SKY_PLATFORM] = tileSize*1.0;
	//Mobs
	widths[BUMBY_0] = tileSize*1.0;
	widths[BUMBY_1] = tileSize*1.0;
	widths[MET_HIDDEN] = tileSize*1.0;
	widths[MET_TRANSITION] = tileSize*1.0;
	widths[MET_VULNERABLE] = tileSize*1.0;
	widths[SNIPER_ATTACK] = tileSize*1.0;
	widths[SNIPER_DEFEND] = tileSize*1.0;
	widths[SNIPER_JUMP] = tileSize*1.0;
	widths[SNIPER_VULNERABLE] = tileSize*1.0;
	widths[JUMPING_SNIPER] = tileSize*1.0;
	//BombMan
	widths[BOMBMAN_ATTACK] = tileSize*1.0;
	widths[BOMBMAN_CAST] = tileSize*1.0;
	widths[BOMBMAN_IDLE] = tileSize*1.0;
	widths[BOMBMAN_JUGGLE] = tileSize*1.0;
	widths[BOMBMAN_JUMP] = tileSize*1.0;
	widths[BOMBMAN_JUMP_FRONT] = tileSize*1.0;
	widths[BOMBMAN_JUMP_BACK] = tileSize*1.0;
	//FireMan
	widths[FIREMAN_CAST_0] = tileSize*1.0;
	widths[FIREMAN_CAST_1] = tileSize*1.0;
	widths[FIREMAN_IDLE_0] = tileSize*1.0;
	widths[FIREMAN_IDLE_1] = tileSize*1.0;
	widths[FIREMAN_JUMP] = tileSize*1.0;
	widths[FIREMAN_RUN_0] = tileSize*1.0;
	widths[FIREMAN_RUN_1] = tileSize*1.0;
	widths[FIREMAN_RUN_2] = tileSize*1.0;
	widths[FIREMAN_RUN_3] = tileSize*1.0;
	//MagnetMan
	widths[MAGNETMAN_ATTACK] = tileSize*1.0;
	widths[MAGNETMAN_CELEBRATE] = tileSize*1.0;
	widths[MAGNETMAN_DEFEND_0] = tileSize*1.0;
	widths[MAGNETMAN_DEFEND_1] = tileSize*1.0;
	widths[MAGNETMAN_DEFEND_2] = tileSize*1.0;
	widths[MAGNETMAN_IDLE] = tileSize*1.0;
	widths[MAGNETMAN_JUMP_0] = tileSize*1.0;
	widths[MAGNETMAN_JUMP_1] = tileSize*1.0;
	widths[MAGNETMAN_PREPARED] = tileSize*1.0;
	//RingMan
	widths[RINGMAN_CAST] = tileSize*1.0;
	widths[RINGMAN_IDLE] = tileSize*1.0;
	widths[RINGMAN_JUMP] = tileSize*1.0;
	widths[RINGMAN_PREPARE_JUMP_0] = tileSize*1.0;
	widths[RINGMAN_PREPARE_JUMP_1] = tileSize*1.0;
	widths[RINGMAN_PREPARE_STAND_0] = tileSize*1.0;
	widths[RINGMAN_PREPARE_STAND_1] = tileSize*1.0;
	widths[RINGMAN_RUN_0] = tileSize*1.0;
	widths[RINGMAN_RUN_1] = tileSize*1.0;
	widths[RINGMAN_RUN_2] = tileSize*1.0;
	widths[RINGMAN_RUN_3] = tileSize*1.0;
	//SparkMan
	widths[SPARKMAN_CAST_ATTACK_1] = tileSize*1.0;
	widths[SPARKMAN_CAST_ATTACK_2] = tileSize*1.0;
	widths[SPARKMAN_IDLE] = tileSize*1.0;
	widths[SPARKMAN_JUMP] = tileSize*1.0;
	widths[SPARKMAN_PREPARE_0_ATTACK_1] = tileSize*1.0;
	widths[SPARKMAN_PREPARE_0_ATTACK_2] = tileSize*1.0;
	widths[SPARKMAN_PREPARE_1_ATTACK_1] = tileSize*1.0;
	widths[SPARKMAN_PREPARE_1_ATTACK_2] = tileSize*1.0;
	widths[SPARKMAN_PREPARE_2_ATTACK_1] = tileSize*1.0;
	widths[SPARKMAN_PREPARE_2_ATTACK_2] = tileSize*1.0;
}

string SpriteDispenser::get(uint id) {
	Lock l(m);
	string sprite = paths[id];
	if (sprite == ""){
		throw std::runtime_error("Requested invalid sprite");
	} else {
		return sprite;
	}
}

double SpriteDispenser::getHeight(uint id) {
	Lock l(m);
	double size = heigths[id];
	if (size == 0){
		throw std::runtime_error("Requested invalid sprite");
	} else {
		return size;
	}
}

double SpriteDispenser::getWidth(uint id) {
	Lock l(m);
	double size = widths[id];
	if (size == 0){
		throw std::runtime_error("Requested invalid sprite");
	} else {
		return size;
	}
}



