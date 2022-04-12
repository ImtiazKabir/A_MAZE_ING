#include "ray.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "iGraphics.h"
#include "gl.h"
#include "utils.h"


Ray *Ray_Create(double x, double y, double theta) {
  Ray *self = (Ray *) malloc(sizeof(Ray));
  self->source = Vector_CreateXY(x, y);
  self->_dir = Vector_CreateRT(1.0, theta);
  self->end = NULL;
  self->endSpotted = false;
  return self;
}


void Ray_Destroy(Ray *self) {
  Vector_Destroy(self->source);
  Vector_Destroy(self->_dir);
  if (NULL != self->end) {
    Vector_Destroy(self->end);
  }
  free(self);
}

void Ray_Render(Ray *self) {
  if (NULL == self->end) {
    return;
  }
  if (true == self->endSpotted) {
    iSetColor(255, 0, 0);
  }
  else {
    iSetColor(255, 255, 255);
  }
  glLineWidth(1.0f);
  iLine(self->source->x, self->source->y, self->end->x, self->end->y);
}


void Ray_Intersect(Ray *self, Wall *wall) {
  double x1,y1, x2,y2, x3,y3, x4,y4, x,y;
  Vector *intersection;

  x1 = self->source->x;
  y1 = self->source->y;
  x2 = self->source->x + self->_dir->x;
  y2 = self->source->y + self->_dir->y;


  x3 = wall->a->x;
  y3 = wall->a->y;
  x4 = wall->b->x;
  y4 = wall->b->y;


  if (false == ray_intersect_with_segment(&x,&y,x1,y1,x2,y2,x3,y3,x4,y4)) {
    return;
  }

  intersection = Vector_CreateXY(x, y);
  if (NULL == self->end) {
    self->end = Vector_Create();
    Vector_Copy(self->end, intersection);
  } else if (Vector_SqDist(self->source, intersection) < Vector_SqDist(self->source, self->end)) {
    Vector_Copy(self->end, intersection);
  }
  Vector_Destroy(intersection);
}


void Ray_MoveTo(Ray *self, double x, double y) {
  self->source->x = x;
  self->source->y = y;

  if (NULL != self->end) {
    Vector_Destroy(self->end);
    self->end = NULL;
  }
}

void Ray_RotateBy(Ray *self, double theta) {
  Vector_Rotate(self->_dir, self->_dir, theta);

  if (NULL != self->end) {
    Vector_Destroy(self->end);
    self->end = NULL;
  }
}

void Ray_MoveBy(Ray *self, double t, double heading) {
  self->source->x += t * cos(heading);
  self->source->y += t * sin(heading);

  if (NULL != self->end) {
    Vector_Destroy(self->end);
    self->end = NULL;
  }
}

void Ray_MiniRender(Ray *self, double mini_dim, double playerX, double playerY, double scaleX, double scaleY) {
  double x1, y1, x2, y2, x, y;

  if (NULL == self->end) {
    return;
  }

  iSetColor(80, 137, 255);
  glLineWidth(1.0f);

  x1 = mini_dim/2 + scaleX * (self->source->x - playerX);
  y1 = mini_dim/2 + scaleY * (self->source->y - playerY);

  x2 = mini_dim/2 + scaleX * (self->end->x - playerX);
  y2 = mini_dim/2 + scaleY * (self->end->y - playerY);

  if (x2 <= mini_dim && y2 <= mini_dim) {
    iLine(x1,y1, x2,y2);
    return;
  }

  if (true == ray_intersect_with_segment(&x,&y,x1,y1,x2,y2,0.0,mini_dim,mini_dim,mini_dim)) {
    iLine(x1,y1, x,y);
    return;
  }

  if (true == ray_intersect_with_segment(&x,&y,x1,y1,x2,y2,mini_dim,0.0,mini_dim,mini_dim)) {
    iLine(x1,y1, x,y);
    return;
  }
}

void Ray_Render3D(
  Ray *self,
  int index, int ray_len,
  double screenWidth, double screenHeight,
  double distance_from_plane, double wall_height,
  double brightness_factor,
  double angle_with_heading
) {
  double intensity, height, fringe_width, distance, x;

  if (NULL == self->end) {
    return;
  }

  distance = Vector_Dist(self->source, self->end) * cos(angle_with_heading);
  intensity = brightness_factor / distance;

  if (intensity > 1) {
    intensity = 1;
  }


  height = wall_height / distance * distance_from_plane;

  fringe_width = screenWidth / ray_len;
  x = (ray_len - 1 - index) * fringe_width;

  if (false == self->endSpotted) {
    iSetColor(255 * intensity, 255 * intensity, 255 * intensity);
  } else {
    iSetColor(255 * intensity, 0 * intensity, 0 * intensity);
  }

  iFilledRectangle(x, (screenHeight-height)/2.0, fringe_width, height);
}


