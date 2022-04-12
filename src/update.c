#include "game.h"
#include "ray.h"
#include "wall.h"
#include "utils.h"
#include "vector.h"
#include <math.h>


static bool going_to_collide(double x, double y, double velocity, double heading, Wall *walls[], int wall_len);

static void update_ray_source(
	Ray *rays[], int ray_len,
	double velocity, double omega,
	double *heading,
	Wall *walls[], int wall_len
);

static void update_ray_end(
	int row, int col,
	double rowSpan, double colSpan,
	Ray *rays[], int ray_len,
	Wall *walls[], int wall_len
);

void game_update(
	int *row, int *col,
	double rowSpan, double colSpan,
  Ray *rays[], int ray_len,
  Wall *walls[], int *wall_len,
  double omega, double velocity, 
	double *heading,
	bool *can_progress
) {
	double width, height;
	
	width = *col * colSpan;
	height = *row * rowSpan;

	if (rays[0]->source->x > width - colSpan && rays[0]->source->y > height - rowSpan) {
		*can_progress = true;
	} else {
		*can_progress = false;
	}

	update_ray_source(rays, ray_len, velocity, omega, heading, walls, *wall_len);
	update_ray_end(*row, *col, rowSpan, colSpan, rays, ray_len, walls, *wall_len);
}


static void update_ray_source(
	Ray *rays[], int ray_len,
	double velocity, double omega,
	double *heading,
	Wall *walls[], int wall_len
){
	int i;
	bool colliding;
	if (0 != omega) {
		*heading += omega;
		for (i = 0; i < ray_len; ++i) {
			Ray_RotateBy(rays[i], omega);
		}
	}

  colliding = going_to_collide(rays[0]->source->x, rays[0]->source->y, velocity, *heading, walls, wall_len);
	if (0 != velocity && false == colliding) {
		for (i = 0; i < ray_len; ++i) {
			Ray_MoveBy(rays[i], velocity, *heading);
		}
	}
}

static void update_ray_end(
	int row, int col,
	double rowSpan, double colSpan,
	Ray *rays[], int ray_len,
	Wall *walls[], int wall_len
) {
	int i,j;
	double width, height;

	width = col * colSpan;
	height = row * rowSpan;

	for (i = 0; i < ray_len; ++i) {
		for (j = 0; j < wall_len; ++j) {
			Ray_Intersect(rays[i], walls[j]);
		}
	}

	for (i = 0; i < ray_len; ++i) {
		if (are_equal(rays[i]->end->x, width, 1.0) && rays[i]->end->x && height - rays[i]->end->y < rowSpan) {
			rays[i]->endSpotted = true;
			continue;
		}
		if (are_equal(rays[i]->end->y, height, 1.0) && width - rays[i]->end->x < colSpan) {
			rays[i]->endSpotted = true;
			continue;
		}
		rays[i]->endSpotted = false;
	}
}


static bool going_to_collide(double x, double y, double velocity, double heading, Wall *walls[], int wall_len) {
	double x1,y1, x2,y2, x3,y3, x4,y4, ix,iy;
	int i;

	x1 = x;
	y1 = y;

	x2 = x1 + velocity * cos(heading);
	y2 = y1 + velocity * sin(heading);

	for (i = 0; i < wall_len; ++i) {
		x3 = walls[i]->a->x;
		y3 = walls[i]->a->y;

		x4 = walls[i]->b->x;
		y4 = walls[i]->b->y;

		if (true == segment_intersect_with_segment(&ix,&iy,x1,y1,x2,y2,x3,y3,x4,y4)) {
			return true;
		}
	}
	return false;
}

