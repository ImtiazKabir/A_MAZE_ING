#ifndef WALL_H_6187365
#define WALL_H_6187365

#include "vector.h"

typedef struct {
  Vector *a;
  Vector *b;
} Wall;


Wall *Wall_Create(double x1, double y1, double x2, double y2);
void Wall_Destroy(Wall *self);
void Wall_Render(Wall *self);
void Wall_MiniRender(Wall *self, double mini_dim, double playerX, double playerY, double scaleX, double scaleY);

#endif /* WALL_H_6187365 */
