#include <windows.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "iGraphics.h"
#include "glut.h"
#include "gl.h"
#include "wall.h"
#include "ray.h"
#include "maze.h"
#include "game.h"
#include "sprite.h"
#include "menu.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define RAY_TOTAL 500
#define WALL_TOTAL 1000
#define FPS 60

#define WIDTH 1120
#define HEIGHT 700

#define MINI_DIM 150
#define SCALEX 0.50
#define SCALEY 0.50

#define LIN_VEL 3.5
#define ANG_VEL 0.05

#define FIELD_OF_VIEW M_PI/4
#define INIT_HEADING M_PI/3

#define INIT_ROW 3
#define INIT_COL 3

#define ROW_SPAN 75.0
#define COL_SPAN 75.0

#define ROW_INC 2
#define COL_INC 2

#define BRIGHTNESS_FACTOR 25.0
#define DISTANCE_FROM_PLANE ROW_SPAN/3
#define WALL_HEIGHT 2.0f * HEIGHT


#define PLAYER_SIZE MINI_DIM/20

#define TITLE "A_MAZE_ING"

#define ASSETS_DIR "assets/"

#define MINIMAP_SPRITE "map.bmp"
#define FLAG_SPRITE "flag.bmp"
#define SKY_SPRITE "moon.bmp"

#define FOOTSTEP_SOUND "running.wav"
#define AMBIENCE_SOUND "ambience.wav"


#define MENU_PLAY_SPRITE "play.bmp"
#define MENU_RULES_SPRITE "rules.bmp"
#define MENU_EXIT_SPRITE "exit.bmp"

#define RULE_BOARD_SPRITE "rule_board.bmp"

#define MENU_NAVIGATION_SOUND "navigation.wav"
#define MENU_CONFIRM_SOUND "confirm.wav"


/****** Global variables  ****/
static Wall *walls[WALL_TOTAL];
static int wall_len = 0;
static Ray *rays[RAY_TOTAL];

static int row = INIT_ROW;
static int col = INIT_COL;

static double heading = INIT_HEADING;
static double velocity = 0;
static double omega = 0;


static Sprite *map;
static Sprite *flag;
static Sprite *sky;


static Menu *main_menu;
static bool in_menu = true;

static bool in_rule = false;
static Sprite *rule_board;


static bool can_progress = false;


/* ************************ */
static void update(void);

int main(void) {
	setup(
		row, col,
		ROW_SPAN, COL_SPAN,
		&heading, FIELD_OF_VIEW,
		walls, &wall_len,
		rays, RAY_TOTAL,
		INIT_HEADING,
		&map, ASSETS_DIR MINIMAP_SPRITE,
		&flag, ASSETS_DIR FLAG_SPRITE,
		&sky, ASSETS_DIR SKY_SPRITE,
		&main_menu,
		ASSETS_DIR MENU_PLAY_SPRITE,
		ASSETS_DIR MENU_RULES_SPRITE,
		ASSETS_DIR MENU_EXIT_SPRITE,
		&rule_board, ASSETS_DIR RULE_BOARD_SPRITE
	);

	iSetTimer(1000 / FPS, update);
	iInitialize(WIDTH, HEIGHT, TITLE);

	cleanup(walls, &wall_len, rays, RAY_TOTAL, map, flag, sky, main_menu, rule_board);
	return 0;
}

void iDraw(void) {
	game_draw(
		rays, RAY_TOTAL,
		walls, wall_len,
		heading,
		MINI_DIM,
		SCALEX, SCALEY,
		WIDTH, HEIGHT,
		DISTANCE_FROM_PLANE, WALL_HEIGHT,
		BRIGHTNESS_FACTOR,
		FIELD_OF_VIEW,
		PLAYER_SIZE,
		map, flag, sky,
		row, col,
		ROW_SPAN, COL_SPAN,
		main_menu, in_menu,
		in_rule, rule_board,
		can_progress
	);
}

static void update(void) {
	game_update(
		&row, &col,
		ROW_SPAN, COL_SPAN,
		rays, RAY_TOTAL,
		walls, &wall_len,
		omega, velocity,
		&heading,
		&can_progress
	);
}

void iMouseMove(int state) {}

void iMouse(int button, int state, int mx, int my) {}

void iKeyboard(unsigned char key) {
	game_keyPressed(
		key,
		main_menu, &in_menu,
		ASSETS_DIR AMBIENCE_SOUND, ASSETS_DIR MENU_CONFIRM_SOUND,
		can_progress,
		walls, &wall_len,
		rays, RAY_TOTAL,
		&row, &col,
		ROW_INC, COL_INC,
		ROW_SPAN, COL_SPAN,
		&heading, FIELD_OF_VIEW,
		INIT_HEADING,
		&in_rule
	);
}

void iSpecialKeyboard(unsigned char key) {
	game_specialPressed(
		key,
		&omega, &velocity,
		LIN_VEL, ANG_VEL,
		ASSETS_DIR FOOTSTEP_SOUND,
		main_menu,
		in_menu, ASSETS_DIR MENU_NAVIGATION_SOUND
	);
}

void iSpecialKeyboardUp(unsigned char key) {
	game_specialReleased(key, &omega, &velocity, ASSETS_DIR FOOTSTEP_SOUND, ASSETS_DIR AMBIENCE_SOUND, in_menu);
}
