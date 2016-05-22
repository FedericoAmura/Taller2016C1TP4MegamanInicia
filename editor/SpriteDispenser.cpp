//
// Created by marcos on 22/05/16.
//

#include "SpriteDispenser.h"
#include "../entities.h"

#define IMG_PATH "../sprites"
#define MOB_PATH (string) IMG_PATH + "/mobs/"
#define BSS_PATH (string) IMG_PATH + "/bosses/"
#define BCK_PATH (string) IMG_PATH + "/level/background/"
#define TLE_PATH (string) IMG_PATH + "/level/tiles/"

SpriteDispenser::SpriteDispenser() {
    //tiles
    paths[BOSS_DOOR] = TLE_PATH + "boss_door.png";
    paths[CABLE_EDGE_0] = TLE_PATH + "cable_edge0.png";
    paths[CABLE_EDGE_1] = TLE_PATH + "cable_edge1.png";
    paths[CABLE_FLOOR_0] = TLE_PATH + "cable_floor0.png";
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
    //Backgrounds
    paths[CAVE] = BCK_PATH + "cave_b.png";
    paths[CAVE_EDGE] = BCK_PATH + "cave_edge_b.png";
    paths[PLANET] = BCK_PATH + "planet_b.png";
    paths[MOSS_STONE] = BCK_PATH + "moss_stone_b.png";
    paths[CLOUD] = BCK_PATH + "cloud_b.png";
    paths[CLOUD_EDGE] = BCK_PATH + "cloud_edge_b.png";
}

string SpriteDispenser::get(uint id) {
    string sprite = paths[id];
    if (sprite == ""){
        throw std::runtime_error("Requested invalid sprite");
    } else {
        return sprite;
    }
}



