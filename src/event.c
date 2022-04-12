#include "game.h"
#include <windows.h>
#include <mmsystem.h>
#include "glut.h"
#include <stdbool.h>
#include "menu.h"

#include "wall.h"
#include "ray.h"

void game_specialPressed(
	unsigned char key, 
	double *omega, 
	double *velocity, 
	double lin_vel, 
	double ang_vel, 
	char const *footstep,
	Menu *main_menu,
	bool in_menu, char const *menu_nav_sound
) {
	bool should_play_sound = false;

	if (true == in_menu) {
		switch(key) {
			case GLUT_KEY_UP: Menu_NavigateUp(main_menu);
			PlaySound(menu_nav_sound, NULL, SND_FILENAME | SND_ASYNC);
			break;
			case GLUT_KEY_DOWN: Menu_NavigateDown(main_menu);
			PlaySound(menu_nav_sound, NULL, SND_FILENAME | SND_ASYNC);
			break;
		}
		return;
	}

	if (0 == *omega) {
		switch(key) {
			case GLUT_KEY_LEFT: *omega = ang_vel;
			break;
			case GLUT_KEY_RIGHT: *omega = - ang_vel;
			break;
		}
	}
	if (0 == *velocity) {
		switch(key) {
			case GLUT_KEY_UP: *velocity = lin_vel;
			should_play_sound = true;
			break;
			case GLUT_KEY_DOWN: *velocity = - lin_vel;
			should_play_sound = true;
			break;
		}
	}

	if (true == should_play_sound) {
		PlaySound(footstep, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}



void game_specialReleased(
	unsigned char key, 
	double *omega, 
	double *velocity, 
	char const *footstep, char const *ambience,
	bool in_menu
) {
	bool should_stop_sound = false;

	if (true == in_menu) {
		return;
	}

	if (0 != *omega) {
		switch(key) {
			case GLUT_KEY_LEFT: *omega = 0;
			break;
			case GLUT_KEY_RIGHT: *omega = 0;
			break;
		}
	}
	if (0 != *velocity) {
		switch(key) {
			case GLUT_KEY_UP: *velocity = 0;
			should_stop_sound = true;
			break;
			case GLUT_KEY_DOWN: *velocity = 0;
			should_stop_sound = true;
			break;
		}
	}
	

	if (true == should_stop_sound) {
		PlaySound(NULL, NULL, SND_ASYNC);
		PlaySound(ambience, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}


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
) {
	if ('\r' != key) {
		return;
	}

	PlaySound(menu_confirm_sound, NULL, SND_FILENAME);

	if (true == *in_rule) {
		*in_rule = false;
		return;
	}

	if (true == *in_menu) {
		if (0 == main_menu->current_sprite_index) {
			*in_menu = false;
			PlaySound(ambience, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		} else if (main_menu->number_of_sprites-1 == main_menu->current_sprite_index) {
			exit(0);
		} else if(1 == main_menu->current_sprite_index) {
			*in_rule = true;
		}
		return;
	}

	if (true == can_progress) {
		level_cleanup(walls, wall_len, rays, ray_len);
		*row += rowInc;
		*col += colInc;
		initiate_world(*row, *col, rowSpan, colSpan, heading, field_of_view, walls, wall_len, rays, ray_len, init_heading);
		PlaySound(ambience, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}
