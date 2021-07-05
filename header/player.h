
// for env
#define MAP_WIDTH 31
#include "vector.h"

#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_COLOR 6

typedef enum direction {
    up,
    down,
    right,
    left
} direction;

typedef struct Player {
    Vector pos;
    direction dir;
    int nbOfDeaths;
    Vector deathsPos[5];
    int nbOfWins;
    Vector winPos[MAP_WIDTH];
} Player;

void player_init(Player* self, int height);

void player_draw(Player self);

void player_move(Player* self, direction dir, int height);

void player_update(Player* self);

void player_reset(Player* self, int height);

void player_die(Player* self, int height);

// check water and car


#endif