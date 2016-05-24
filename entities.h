//
// Created by marcos on 13/05/16.
//

#ifndef MEGAMAN_ENTITIES_H
#define MEGAMAN_ENTITIES_H

/*
 * CRITERIO PARA IDs:
 *
 * Numeros decimales de 4 digitos:
 * * 1er digito: tipo
 * * 2do digito: orientacion
 * * 3er y 4to digito: elemento
 *
 */

//PC
#define MEGAMAN 9000

//NPC
#define MET 1001
#define BUMBY 1002
#define SNIPER 1003
#define JUMPING_SNIPER 1004
#define BOMBMAN 1005
#define SPARKMAN 1006
#define MAGNETMAN 1007
#define RINGMAN 1008
#define FIREMAN 1009

//Weapons
#define BOMB 2001
#define FIREMAN_FLAME 2002
#define MEGAMAN_FLAME 2003
#define MEGAMAN_WEAPON 2004
#define MET_WEAPON 2005
#define SNIPER_WEAPON 2006
#define RINGMAN_WEAPON 2007
#define MAGNETMAN_WEAPON 2008
#define SPARKMAN_SPARKS 2009
#define SPARKMAN_GENKIDAMA 2010

//Items
#define BIG_ENERGY 3001 //los sprites de esto no son los correctos, despues lo arreglo
#define SMALL_ENERGY 3002
#define BIG_PLASMA 3003
#define SMALL_PLASMA 3004
#define LIFE 3005

//Tiles
#define BOSS_DOOR 4000
#define CABLE_EDGE_0 4001
#define CABLE_EDGE_1 4002
#define CABLE_FLOOR_0 4003
#define CABLE_FLOOR_0_L 4103
#define CABLE_FLOOR_0_R 4203
#define CABLE_FLOOR_0_D 4303
#define CABLE_FLOOR_1_L 4104
#define CABLE_FLOOR_1_R 4204
#define CABLE_FLOOR_1_D 4304
#define CABLE_FRAME_0 4005
#define CABLE_FRAME_0_L 4105
#define CABLE_FRAME_0_R 4205
#define CABLE_FRAME_0_D 4305
#define CABLE_FRAME_1 4006
#define CABLE_FRAME_1_L 4106
#define CABLE_FRAME_1_R 4206
#define CABLE_FRAME_1_D 4306
#define CABLE_INTERSECTION 4007
#define CABLE_INTERSECTION_L 4107
#define CABLE_INTERSECTION_R 4207
#define CABLE_INTERSECTION_D 4307
#define CERAMIC_EDGE 4008
#define CERAMIC_FLOOR 4009
#define GLASS_FLOOR_0 4010
#define GLASS_FLOOR_1 4011
#define GLASS_WALL_0 4012
#define GLASS_WALL_1 4013
#define METALLIC_PLATFORM 4014
#define METALLIC_WALL 4015
#define SKY_PLATFORM 4016
#define STONE_EDGE 4017
#define STONE_EDGE_F 4117
#define STONE_FLOOR 4118
#define STONE_WALL 4119

//SPECIAL TILES (ladders & spikes)
#define METALLIC_LADDER 5000
#define SKY_LADDER 5001
#define STONE_LADDER 5002
#define STONE_SPIKE 5003

//Backgrounds
#define CAVE 6000
#define CAVE_EDGE 6001
#define CLOUD 6002
#define CLOUD_EDGE 6003
#define MOSS_STONE 6004
#define PLANET 6005

//Others
#define EMPTY 0000

#endif //MEGAMAN_ENTITIES_H
