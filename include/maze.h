#ifndef MAZE_H_784325
#define MAZE_H_784325

#include "wall.h"

#include <stdbool.h>

typedef struct {
  bool visited;
  bool bottom_wall;
  bool left_wall;
} Cell;

int Maze_Init(Cell ****maze, int row, int col);
void Maze_Destroy(Cell ***maze, int row, int col);
void Maze_ConverToWalls(Cell ***maze, int row, int col, Wall *walls[], int *wall_len, double rowSpan, double colSpan);

#endif /* MAZE_H_784325 */
