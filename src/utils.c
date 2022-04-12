#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

bool line_line_intersection(
  double *x, double *y,
  double x1, double y1,
  double x2, double y2,
  double x3, double y3,
  double x4, double y4
) {
  double denominator, cross1, cross2;

  denominator = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
  if (0 == denominator) {
    return false;
  }
  
  cross1 = x1*y2 - x2*y1;
  cross2 = x3*y4 - x4*y3;

  *x = cross1 * (x3-x4) - cross2 * (x1-x2);
  *x /= denominator;

  *y = cross1 * (y3-y4) - cross2 * (y1-y2);
  *y /= denominator;

  return true;
}

bool point_in_segment(
  double x, double y,
  double x1, double y1,
  double x2, double y2
) {
  double sqaured_length, dot_product;

  if (false == are_aligned(x,y, x1,y1, x2,y2)) {
    return false;
  }

  sqaured_length = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
  dot_product = (x2-x1)*(x-x1) + (y2-y1)*(y-y1);


  return 0 < dot_product && dot_product <= sqaured_length;
}


bool are_aligned(
  double x1, double y1,
  double x2, double y2,
  double x3, double y3
) {
  double det = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
  return are_equal(det, 0.0, 1.0);
}


bool point_in_ray(
  double x, double y,
  double x1, double y1,
  double x2, double y2
) {
  double dot_product;

  if (false == are_aligned(x,y, x1,y1, x2,y2)) {
    return false;
  }

  dot_product = (x2-x1)*(x-x1) + (y2-y1)*(y-y1);

  return 0 < dot_product;
}


bool are_equal(double a, double b, double threshold) {
  return b-threshold < a && a < b+threshold;
}


bool ray_intersect_with_segment(
  double *x, double *y,
  double x1, double y1,
  double x2, double y2,
  double x3, double y3,
  double x4, double y4
) {
  if (
    true == line_line_intersection(x,y,x1,y1,x2,y2,x3,y3,x4,y4) &&
    true == point_in_ray(*x,*y,x1,y1,x2,y2) &&
    true == point_in_segment(*x,*y,x3,y3,x4,y4) 
  ) {
    return true;
  } else {
    return false;
  }
}

bool segment_intersect_with_segment(
  double *x, double *y,
  double x1, double y1,
  double x2, double y2,
  double x3, double y3,
  double x4, double y4
) {
  if (
    true == line_line_intersection(x,y,x1,y1,x2,y2,x3,y3,x4,y4) &&
    true == point_in_segment(*x,*y,x1,y1,x2,y2) &&
    true == point_in_segment(*x,*y,x3,y3,x4,y4)
  ) {
    return true;
  } else {
    return false;
  }
}

double linear_map(double x, double minX, double maxX, double minY, double maxY) {
  double factor = (maxY-minY) / (maxX-minX);
  return minY + (x-minX) * factor;
}

