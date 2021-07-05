#include "vector.h"
#include "player.h"

#ifndef MAP_H
#define MAP_H

#define WATER_COLOR 1
#define END_COLOR 2
#define SIDEWALK_COLOR 3
#define START_COLOR 4
#define DOCK_COLOR 4
#define ROAD_COLOR 5
#define CAR_COLOR 7
#define LOG_COLOR 8

typedef enum rowType {
    water,
    road,
    sidewalk,
    green,
    dock,
    // default VV
    end,
    start,
} rowType;


typedef struct Ob {
    int x;
    int size;
} Ob;

typedef struct Environement {
    rowType type;
    int color;
    char ch;
    int speed;
    int size;
    Ob ob;
} Environement;

void map_draw(Environement map[], int height, Player player);

void map_update(Environement* map, int height, Player* player);

void map_reset(Environement* map, int height);

#endif