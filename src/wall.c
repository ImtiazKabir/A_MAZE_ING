#include "wall.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

#include "iGraphics.h"
#include "gl.h"
#include "utils.h"


Wall *Wall_Create(double x1, double y1, double x2, double y2) {
  Wall *self = (Wall *) malloc(sizeof(Wall));
  self->a = Vector_CreateXY(x1, y1);
  self->b = Vector_CreateXY(x2, y2);
  return self;
}


void Wall_Destroy(Wall *self) {
  Vector_Destroy(self->a);
  Vector_Destroy(self->b);
  free(self);
}


void Wall_Render(Wall *self) {
  iSetColor(139, 79, 57);
  glLineWidth(2.0f);
  iLine(self->a->x, self->a->y, self->b->x, self->b->y);
}


void Wall_MiniRender(Wall *self, double mini_dim, double playerX, double playerY, double scaleX, double scaleY) {
  double x1, y1, x2, y2;
  bool top_wall_intersection, right_wall_intersection;
  double topX, topY, rightX, rightY, x, y;

  iSetColor(0, 20, 120);
  glLineWidth(1.5f);

  x1 = mini_dim/2 + scaleX * (self->a->x - playerX);
  y1 = mini_dim/2 + scaleY * (self->a->y - playerY);

  x2 = mini_dim/2 + scaleX * (self->b->x - playerX);
  y2 = mini_dim/2 + scaleY * (self->b->y - playerY);


  if (x1<=mini_dim && y1<=mini_dim && x2<=mini_dim && y2<=mini_dim) {
    iLine(x1,y1, x2,y2);
    return;
  }

  top_wall_intersection  = segment_intersect_with_segment(&topX,&topY,x1,y1,x2,y2,0.0,mini_dim,mini_dim,mini_dim);
  right_wall_intersection= segment_intersect_with_segment(&rightX,&rightY,x1,y1,x2,y2,mini_dim,0.0,mini_dim,mini_dim);

  if (false == top_wall_intersection && false == right_wall_intersection) {
    return;
  }

  if (true == top_wall_intersection && true == right_wall_intersection) {
    iLine(topX,topY, rightX,rightY);
    return;
  }

  if (true == top_wall_intersection) {
    x = topX;
    y = topY;
  } else {
    x = rightX;
    y = rightY;
  }

  if (x1 <= mini_dim && y1 <= mini_dim) {
    iLine(x1, y1, x, y);
  } else {
    iLine(x2, y2, x, y);
  }
}
