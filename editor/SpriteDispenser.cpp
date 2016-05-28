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
    paths[MEGAMAN] = (string) IMG_PATH + "/pc/megaman_idle.png";
    //tiles
    paths[BOSS_DOOR] = TLE_PATH + "boss_door.png";
    paths[CABLE_EDGE_0] = TLE_PATH + "cable_edge0.png";
    paths[CABLE_EDGE_1] = TLE_PATH + "cable_edge1.png";
    paths[CABLE_FLOOR_0] = TLE_PATH + "cable_floor0.png";
    paths[STONE_WALL] = TLE_PATH + "stone_wall.png";
    paths[STONE_LADDER] = TLE_PATH + "stone_ladder.png";
    paths[SPIKE] = TLE_PATH + "stone_spike.png";
    //Mobs
    paths[BUMBY] = MOB_PATH + "bumby0.png";
    paths[MET] = MOB_PATH + "met_vulnerable.png";
    paths[SNIPER] = MOB_PATH + "sniper_vulnerable.png";
    paths[JUMPING_SNIPER] = MOB_PATH + "sniper_jumping.png";
    paths[BOMBMAN] = BSS_PATH + "bombman/bombman_idle.png";
    paths[FIREMAN] = BSS_PATH + "fireman/fireman_idle.png";
    paths[MAGNETMAN] = BSS_PATH + "magnetman/magnetman_idle.png";
    paths[RINGMAN] = BSS_PATH + "ringman/ringman_idle.png";
    paths[SPARKMAN] = BSS_PATH + "sparkman/sparkman_idle.png";
}

string SpriteDispenser::get(uint id) {
    string sprite = paths[id];
    if (sprite == ""){
        throw std::runtime_error("Requested invalid sprite");
    } else {
        return sprite;
    }
}



