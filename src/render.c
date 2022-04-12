#include "game.h"

#include <stdbool.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>

#include "gl.h"
#include "glut.h"
#include "iGraphics.h"
#include "wall.h"
#include "ray.h"
#include "sprite.h"
#include "utils.h"
#include "menu.h"



static void draw_minimap(
	double mini_dim,
  double x, double y,
	double scaleX, double scaleY,
  double heading,
  Wall *walls[], int wall_len,
  Ray *rays[], int ray_len,
	double player_size,
	Sprite *map, Sprite *flag,
	int row, int col,
	double rowSpan, double colSpan
);

static void draw_player(double mini_dim, double heading, double player_size);

static void draw_flag(
	Sprite *flag,
	double mini_dim,
	int row, int col,
	double rowSpan, double colSpan,
	double playerX, double playerY,
	double scaleX, double scaleY
);

static void draw_sky(Sprite *sky, double screenWidth, double screenHeight, double heading);




static void draw_minimap(
	double mini_dim,
  double x, double y,
	double scaleX, double scaleY,
  double heading,
  Wall *walls[], int wall_len,
  Ray *rays[], int ray_len,
	double player_size,
	Sprite *map, Sprite *flag,
	int row, int col,
	double rowSpan, double colSpan
) {
	int i;

	/*
	iRectangle(0, 0, mini_dim, mini_dim);
	iSetColor(80, 137, 255);
	iFilledRectangle(0, 0, mini_dim, mini_dim);
	*/

	Sprite_Render(map, 0, 0);


	for (i = 0; i < wall_len; ++i) {
		Wall_MiniRender(walls[i], mini_dim, x, y, scaleX, scaleY);
	}

	for (i = 0; i < ray_len; ++i) {
		Ray_MiniRender(rays[i], mini_dim, x, y, scaleX, scaleY);
	}

	draw_player(mini_dim, heading, player_size);
	draw_flag(flag, mini_dim, row, col, rowSpan, colSpan, x, y, scaleX, scaleY);
}





static void draw_player(double mini_dim, double heading, double player_size) {
	double degrees = (heading / M_PI) * 180.0;
	double x,y;

	x = mini_dim/2;
	y = mini_dim/2;

	iSetColor(0, 0, 0);
	iRotate(x, y, degrees-90);


	glBegin(GL_POLYGON);
	glVertex2d(x+0.0,y+player_size);
	glVertex2d(x+player_size,y-player_size);
	glVertex2d(x+0.0,y-player_size/2.0);
	glVertex2d(x-player_size,y-player_size);
	glEnd();


	iUnRotate();
}



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
) {
	int i;
	double dtheta;


	iClear();

	if (true == in_rule) {
		Sprite_Render(rule_board, 0.0, 0.0);
		iSetColor(219, 216, 116);
		iFilledRectangle(screenWidth-140,32,140,35);
		iSetColor(0,0,0);
		iText(screenWidth-130, 40, "[Press ENTER]", GLUT_BITMAP_HELVETICA_18);
		return;
	}

	if (true == in_menu) {
		Menu_Render(main_menu);
		return;
	}

	draw_sky(sky, screenWidth, screenHeight, heading);


	dtheta = field_of_view / ray_len;
	for (i = 0; i < ray_len; ++i) {
		double theta = (ray_len/2 - i) * dtheta;
		Ray_Render3D(rays[i], i, ray_len, screenWidth, screenHeight, distance_from_plane, wall_height, brightness_factor, theta);
	}

	draw_minimap(
		mini_dim,
		rays[0]->source->x, rays[0]->source->y,
		scaleX, scaleY,
		heading,
		walls, wall_len,
		rays, ray_len,
		player_size,
		map, flag,
		row, col,
		rowSpan, colSpan
	);

	if (true == can_progress) {
		iSetColor(219, 216, 116);
		iFilledRectangle(screenWidth-140,2,140,35);
		iSetColor(0,0,0);
		iText(screenWidth-130, 10, "[Press ENTER]", GLUT_BITMAP_HELVETICA_18);
	}
}


static void draw_flag(
	Sprite *flag,
	double mini_dim,
	int row, int col,
	double rowSpan, double colSpan,
	double playerX, double playerY,
	double scaleX, double scaleY
) {
	double x1, y1, x2, y2, x, y;

  iSetColor(80, 137, 255);
  glLineWidth(1.0f);

  x1 = mini_dim/2;
  y1 = mini_dim/2;

  x2 = mini_dim/2 + scaleX * (col * colSpan - playerX);
  y2 = mini_dim/2 + scaleY * (row * rowSpan - playerY);

  if (x2 <= mini_dim && y2 <= mini_dim) {
    Sprite_Render(flag, x2 - flag->width/2.0, y2 - flag->height/2.0);
    return;
  }

  if (
		true == ray_intersect_with_segment(&x,&y,x1,y1,x2,y2,0.0,mini_dim,mini_dim,mini_dim) ||
		true == ray_intersect_with_segment(&x,&y,x1,y1,x2,y2,mini_dim,0.0,mini_dim,mini_dim)
	) {
    Sprite_Render(flag, x - flag->width/2.0, y - flag->height/2.0);
    return;
  }
}


static void draw_sky(Sprite *sky, double screenWidth, double screenHeight, double heading) {
	double dir, skyX;
	dir = fmod(heading, 2 * M_PI);
	if (dir < 0) {
		dir += 2 * M_PI;
	}
	skyX = linear_map(dir, 0.0, 2*M_PI, -sky->width, 0.0);

	Sprite_Render(sky, skyX, screenHeight/2.0);
	if (skyX + sky->width < screenWidth) {
		Sprite_Render(sky, skyX+sky->width, screenHeight/2.0);
	}
}
