#include "../header/map.h"

#include <ncurses.h>

void map_draw(Environement map[], int height, Player player) {
    for (int y = 0; y < height; y++) {
        attron(COLOR_PAIR(map[y].color));
        for (int x = 0; x < MAP_WIDTH; x++) {
            move(y, x);

            addch(map[y].ch);
        }
        attroff(COLOR_PAIR(map[y].color));
    }

    // draw wins and deaths

    for (int i = 0; i < player.nbOfWins; i++) {
        move(player.winPos[i].y, player.winPos[i].x);
        attron(COLOR_PAIR(PLAYER_COLOR));
        addch('@');
        attroff(COLOR_PAIR(PLAYER_COLOR));
    }

    for (int i = 0; i < player.nbOfDeaths; i++) {
        if (map[player.deathsPos[i].y].type == water) {
            continue;
        }
        move(player.deathsPos[i].y, player.deathsPos[i].x);
        attron(COLOR_PAIR(2));
        addch('X');
        attroff(COLOR_PAIR(2));
    }
}

void map_update(Environement* map, int height, Player* player) {
    for (int y = 0; y < height; y++) {
        if (map->type == road) {
            attron(COLOR_PAIR(CAR_COLOR));
        }
        if (map->type == water) {
            attron(COLOR_PAIR(LOG_COLOR));
        }
        for (int s = 0; s < map->size; s++) {
            if (map->ob.x + s > MAP_WIDTH - 1) {
                continue;
            } else if (map->ob.x + s < 0) {
                continue;
            }

            move(y, map->ob.x + s);
            if (((s == 0 && y % 2 == 1)
                || (s == map->size-1 && y % 2 == 0))
                && map->type == road) {
                addch('#');
            } else {
                addch(' ');
            }
        }
        if (map->type == road) {
            attroff(COLOR_PAIR(CAR_COLOR));
        }
        if (map->type == water) {
            attroff(COLOR_PAIR(LOG_COLOR));
        }
        
        for (int i = 0; i < map->speed; i++) {
            if (map->ob.x > MAP_WIDTH -1) {
                map->ob.x = -map->size;
                continue;
            } else if (map->ob.x + map->size < 0) {
                map->ob.x = MAP_WIDTH - 1;
            }
            // player stuff

            // cols
            if (player->pos.y == y &&
            (player->pos.x >= map->ob.x && player->pos.x <= map->ob.x + (map->size - 1))) {
                if (map->type == road) {
                    player_die(player, height);
                } else if (map->type == water) {
                    if (y % 2 == 0) {
                        player->pos.x++;
                    } else {
                        player->pos.x--;
                    }
                }
            } else if (player->pos.y == y && map->type == water) {      
                player_die(player, height);
            }

            if (player->pos.x < 0 || player->pos.x > MAP_WIDTH - 1) {
                player_die(player, height);
            }

            if (y % 2 == 0) {
                map->ob.x++;
            } else {
                map->ob.x--;
            }
        }
        // finish
        if (player->pos.y == y && map->type == end) {
            player->winPos[player->nbOfWins].x = player->pos.x;
            player->winPos[player->nbOfWins].y = y;
            player->nbOfWins++;
            player_init(player, height);
        }
        map++; // add + 1 to pionter to select next element
    }
}

void map_reset(Environement* map, int height) {
    for (int i = 0; i < height; i++) {
        map->ob.x = 0;
        map++;
    }
}