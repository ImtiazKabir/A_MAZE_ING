#ifndef UTILS_H_35876
#define UTILS_H_35876

#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool line_line_intersection(
  double *x, double *y,
  double x1, double y1,
  double x2, double y2,
  double x3, double y3,
  double x4, double y4
);

bool point_in_segment(
  double x, double y,
  double x1, double y1,
  double x2, double y2
);

bool point_in_ray(
  double x, double y,
  double x1, double y1,
  double x2, double y2
);

bool are_aligned(
  double x1, double y1,
  double x2, double y2,
  double x3, double y3
);

bool ray_intersect_with_segment(
  double *x, double *y,
  double x1, double y1,
  double x2, double y2,
  double x3, double y3,
  double x4, double y4
);


bool segment_intersect_with_segment(
  double *x, double *y,
  double x1, double y1,
  double x2, double y2,
  double x3, double y3,
  double x4, double y4
);


bool are_equal(double a, double b, double threshold);


double linear_map(double x, double minX, double maxX, double minY, double maxY);


#endif /* UTILS_H_35876 */