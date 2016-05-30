//
// Created by marcos on 22/05/16.
//

#include "SpriteDispenser.h"
#include "../entities.h"

#define IMG_PATH "../sprites"
#define MOB_PATH (string) IMG_PATH + "/mobs/"
#define BSS_PATH (string) IMG_PATH + "/bosses/"
#define LVL_PATH (string) IMG_PATH + "/level/"
#define TLE_PATH (string) IMG_PATH + "/level/tiles/"

SpriteDispenser::SpriteDispenser() {
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
	paths[FIREMAN_CAST_0] = BSS_PATH + "fireman/fireman_cast0.png";
	paths[FIREMAN_CAST_1] = BSS_PATH + "fireman/fireman_cast1.png";
	paths[FIREMAN_IDLE_0] = BSS_PATH + "fireman/fireman_idle.png";
	paths[FIREMAN_IDLE_1] = BSS_PATH + "fireman/fireman_idle1.png";
	paths[FIREMAN_JUMP] = BSS_PATH + "fireman/fireman_jump.png";
	paths[FIREMAN_RUN_0] = BSS_PATH + "fireman/fireman_run0.png";
	paths[FIREMAN_RUN_1] = BSS_PATH + "fireman/fireman_run1.png";
	paths[FIREMAN_RUN_2] = BSS_PATH + "fireman/fireman_run2.png";
	paths[FIREMAN_RUN_3] = BSS_PATH + "fireman/fireman_run3.png";
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
}

string SpriteDispenser::get(uint id) {
	string sprite = paths[id];
	if (sprite == ""){
		throw std::runtime_error("Requested invalid sprite");
	} else {
		return sprite;
	}
}



