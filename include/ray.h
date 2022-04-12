#ifndef RAY_H_209587
#define RAY_H_209587

#include "vector.h"
#include "wall.h"

#include <stdbool.h>

typedef struct {
  Vector *source;
  Vector *_dir;
  Vector *end;
  bool endSpotted;
} Ray;

Ray *Ray_Create(double x, double y, double theta);
void Ray_Destroy(Ray *self);
void Ray_Render(Ray *self);
void Ray_Intersect(Ray *self, Wall *wall);
void Ray_MoveTo(Ray *self, double x, double y);
void Ray_RotateBy(Ray *self, double theta);
void Ray_MoveBy(Ray *self, double t, double heading);
void Ray_MiniRender(Ray *self, double mini_dim, double playerX, double playerY, double scaleX, double scaleY);
void Ray_Render3D(
  Ray *self,
  int index, int ray_len,
  double screenWidth, double screenHeight,
  double distance_from_plane, double wall_height,
  double brightness_factor,
  double angle_with_heading
);

#endif /* RAY_H_209587 */
