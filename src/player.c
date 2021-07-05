#include "../header/player.h"

#include <ncurses.h>

#include <math.h>

void player_init(Player* self, int height) {
    self->pos.y = height-1;
    self->pos.x = round(MAP_WIDTH/2);
    self->dir = up;
}

void player_draw(Player self) {
    move(self.pos.y, self.pos.x);

    attron(COLOR_PAIR(PLAYER_COLOR));
    
    if (self.dir == up) {
        addch('A');
    } else if (self.dir == down) {
        addch('V');
    } else if (self.dir == right) {
        addch('>');
    } else if (self.dir == left) {
        addch('<');
    }
    attroff(COLOR_PAIR(PLAYER_COLOR));
}

void player_move(Player* self, direction dir, int height) {
    self->dir = dir;
    if (dir == up && self->pos.y > 0) {
        self->pos.y--;
    } else if (dir == down && self->pos.y < height-1) {
        self->pos.y++;
    } else if (dir == right && self->pos.x < MAP_WIDTH-1) {
        self->pos.x++;
    } else if (dir == left && self->pos.x > 0) {
        self->pos.x--;
    }
}

void player_die(Player* self, int height) {
    self->deathsPos[self->nbOfDeaths].x = self->pos.x;
    self->deathsPos[self->nbOfDeaths].y = self->pos.y;
    self->nbOfDeaths++;
    player_init(self, height);
}

void player_reset(Player* self, int height) {
    self->nbOfWins = 0;
    self->nbOfDeaths = 0;
    player_init(self, height);
}