#include "game.h"
#include "maze.h"
#include "menu.h"
#include "sprite.h"

#include <time.h>
#include <stdlib.h>


static void initiate_walls(
	int row, int col,
	double rowSpan, double colSpan,
	Wall *walls[], int *wall_len
);

static void initiate_rays(Ray *rays[], int ray_len, double *heading, double init_heading, double field_of_view);

void setup(
	int row, int col,
	double rowSpan, double colSpan,
  double *heading, double field_of_view,
  Wall *walls[], int *wall_len, 
  Ray *rays[], int ray_len,
	double init_heading,
	Sprite **map, char const *map_file,
	Sprite **flag, char const *flag_file,
	Sprite **sky, char const *sky_file,
	Menu **main_menu,
	char const *menu_play_file,
	char const *menu_rules_file,
	char const *menu_exit_file,
	Sprite **rule_board, char const *rule_board_file
) {
	srand((unsigned int) time(NULL));

	*map = Sprite_Create(map_file);
	*flag = Sprite_Create(flag_file);
	*sky = Sprite_Create(sky_file);
	*main_menu = Menu_Create(3, menu_play_file, menu_rules_file, menu_exit_file);

	*rule_board = Sprite_Create(rule_board_file);

	initiate_world(row, col, rowSpan, colSpan, heading, field_of_view, walls, wall_len, rays, ray_len, init_heading);
}


void initiate_world(
  int row, int col,
	double rowSpan, double colSpan,
  double *heading, double field_of_view,
  Wall *walls[], int *wall_len, 
  Ray *rays[], int ray_len,
	double init_heading
) {
	initiate_walls(row, col, rowSpan, colSpan, walls, wall_len);
	initiate_rays(rays, ray_len, heading, init_heading, field_of_view);
}


static void initiate_walls(
	int row, int col,
	double rowSpan, double colSpan,
	Wall *walls[], int *wall_len
) {
	Cell ***maze;
	double width, height;

	width = col * colSpan;
	height = row * rowSpan;

	walls[0] = Wall_Create(0,0, width,0);
	walls[1] = Wall_Create(width,0, width,height);
	walls[2] = Wall_Create(width,height, 0,height);
	walls[3] = Wall_Create(0,height, 0,0);
	*wall_len = 4;

	Maze_Init(&maze, row, col);
	Maze_ConverToWalls(maze, row, col, walls, wall_len, rowSpan, colSpan);
	Maze_Destroy(maze, row, col);
}



static void initiate_rays(Ray *rays[], int ray_len, double *heading, double init_heading, double field_of_view) {
	int i;
	double theta, increase;

	*heading = init_heading;
	theta = *heading - field_of_view/2;
	increase = field_of_view / ray_len;
	for (i = 0; i < ray_len; ++i) {
		rays[i] = Ray_Create(1, 1, theta + i * increase);
	}
}


void level_cleanup(Wall *walls[], int *wall_len, Ray *rays[], int ray_len) {
  int i;
	for (i = 0; i < *wall_len; ++i) {
		if (NULL != walls[i]) {
			Wall_Destroy(walls[i]);
		}
	}
	*wall_len = 0;

	for (i = 0; i < ray_len; ++i) {
		if (NULL != rays[i]) {
			Ray_Destroy(rays[i]);
		}
	}
}

void cleanup(
	Wall *walls[], 
	int *wall_len, 
	Ray *rays[], 
	int ray_len,
	Sprite *map,
	Sprite *flag,
	Sprite *sky,
	Menu *main_menu,
	Sprite *rule_board
) {
	level_cleanup(walls, wall_len, rays, ray_len);

	Sprite_Destroy(map);
	Sprite_Destroy(flag);
	Sprite_Destroy(sky);

	Menu_Destroy(main_menu);

	Sprite_Destroy(rule_board);
}



