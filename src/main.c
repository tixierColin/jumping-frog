#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>

// my headers
#include "../header/map.h"
#include "../header/player.h"



int main() {
    // ncurses init
    initscr();
    raw();
    noecho();
    nodelay(stdscr, TRUE); // prevent getch() from paussing the script
    curs_set(0); // hide cursor

    if (has_colors() == FALSE) {
        exit(1);
    }
    use_default_colors();
    start_color();

    // malloc for player
    Player *player = malloc(sizeof(Player));

    if (player == NULL) {
        endwin();
        exit(1);
    }


    float timer = 0; // seconds
    int interval = 100000; // microseconds
    int maxTime = 30; // seconds
    //player->nbOfDeaths = 0;

    // setup colors :
    init_pair(WATER_COLOR, COLOR_CYAN, COLOR_BLUE);
    init_pair(END_COLOR, COLOR_MAGENTA, COLOR_RED);
    init_pair(DOCK_COLOR, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(ROAD_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(SIDEWALK_COLOR, COLOR_WHITE, COLOR_BLACK);

    // ob color
    init_pair(CAR_COLOR, COLOR_BLUE, COLOR_YELLOW);
    init_pair(LOG_COLOR, COLOR_MAGENTA, COLOR_MAGENTA);


    // player
    init_pair(PLAYER_COLOR, COLOR_BLACK, COLOR_GREEN);

    // percent
    init_pair(9, COLOR_WHITE, COLOR_WHITE);


    // always begin with end and finish with start
    Environement map[] = {
        {end, END_COLOR, ' '},

        {water, WATER_COLOR, '~', 2, 8},
        {water, WATER_COLOR, '~', 1, 7},
        {water, WATER_COLOR, '~', 1, 9},

        {dock, DOCK_COLOR, ' '},

        {road, ROAD_COLOR, '-', 2, 5},
        {road, ROAD_COLOR, '-', 1, 2},

        {sidewalk, SIDEWALK_COLOR, '#'},

        {road, ROAD_COLOR, '-', 2, 3},
        {road, ROAD_COLOR, '-', 1, 4},


        {start, START_COLOR, ' '}
    };
    int mapHeight = sizeof(map)/sizeof(Environement);

    player_init(player, mapHeight);

    bool gameOver = TRUE;
    bool quit = FALSE;
    while (quit == FALSE) {
        erase();
        switch(getch()) {
            case 27:
                quit = TRUE;
                break;
            case 'y':
                // reset
                map_reset(map, mapHeight);
                player_reset(player, mapHeight);
                timer = 0;
                gameOver = FALSE;
                break;
            case 'z':
                player_move(player, up, mapHeight);
                break;
            case 's':
                player_move(player, down, mapHeight);
                break;
            case 'q':
                player_move(player, left, mapHeight);
                break;
            case 'd':
                player_move(player, right, mapHeight);
                break;
        }
        map_draw(map, mapHeight, *player);
        if (gameOver == FALSE) {
            //player_drawDeathAndWins(*player);
            map_update(map, mapHeight, player);

            player_draw(*player);

            // ui
            timer += (float)interval/1000000;
            if (timer >= (float)maxTime) {
                timer = (float)maxTime;
            }
            float percent = timer / maxTime * 100;
            
            // loading bar
            for (int i = 0; i < (float)MAP_WIDTH / 100 * percent; i++) {
                move(mapHeight, i);
                attron(COLOR_PAIR(9));
                addch(' ');
                attroff(COLOR_PAIR(9));
            }
            move(mapHeight+1, 0);
            printw("%d sec/%d sec", (int)timer, maxTime);
            // score
            move(mapHeight+2, 0);
            printw("score : %d", player->nbOfWins * 100);
            // game over
            if (timer >= maxTime) {
                gameOver = TRUE;
            }
        } else {
            // end game
            if (timer > 0) {
                move((int)mapHeight/2 + 1, (int)(MAP_WIDTH/2) - 5);
                printw("score : %d", player->nbOfWins * 100);                
            }
            move((int)mapHeight/2, (int)(MAP_WIDTH/2) - 9);
            printw("press \"y\" to start");
        }
        refresh();
        usleep(interval);
    }
    free(player);

    endwin();
    return 0;
}