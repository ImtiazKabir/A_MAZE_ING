#ifndef GAME_H_328745
#define GAME_H_328745

#include "ray.h"
#include "wall.h"
#include "sprite.h"
#include "menu.h"


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
);

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
);

void level_cleanup(
	Wall *walls[], 
	int *wall_len, 
	Ray *rays[], 
	int ray_len
);

void initiate_world(
  int row, int col,
	double rowSpan, double colSpan,
  double *heading, double field_of_view,
  Wall *walls[], int *wall_len, 
  Ray *rays[], int ray_len,
	double init_heading
);

void game_update(
	int *row, int *col,
	double rowSpan, double colSpan,
  Ray *rays[], int ray_len,
  Wall *walls[], int *wall_len,
  double omega, double velocity, 
	double *heading,
	bool *can_progress
);

void game_draw(
	Ray *rays[], int ray_len,
	Wall *walls[], int wall_len,
	double heading,
	double mini_dim, 
	double scaleX, double scaleY,
	double screenWidth, double screenHeight,
	double distance_from_plane, double wall_height,
	double brightness_factor,
	double field_of_view,
	double player_size,
	Sprite *map, Sprite *flag, Sprite *sky,
	int row, int col,
	double rowSpan, double colSpan,
	Menu *main_menu, bool in_menu,
	bool in_rule, Sprite *rule_board,
	bool can_progress
);


void game_specialPressed(
	unsigned char key, 
	double *omega, 
	double *velocity, 
	double lin_vel, 
	double ang_vel, 
	char const *footstep,
	Menu *main_menu,
	bool in_menu, char const *menu_nav_sound
);
void game_specialReleased(
	unsigned char key, 
	double *omega, 
	double *velocity, 
	char const *footstep, char const *ambience,
	bool in_menu
);


void game_keyPressed(
	unsigned char key, 
	Menu *main_menu, bool *in_menu, 
	char const *ambience, char const *menu_confirm_sound, 
	bool can_progress,
	Wall *walls[], int *wall_len,
	Ray *rays[], int ray_len,
	int *row, int *col,
	int rowInc, int colInc,
	double rowSpan, double colSpan,
	double *heading, double field_of_view,
	double init_heading,
	bool *in_rule
);

#endif /* GAME_H_328745 */


