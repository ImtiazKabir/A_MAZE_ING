#include "maze.h"

#include <stdlib.h>
#include <stdio.h>

static bool Maze_IsPossible(int row, int col, int i, int j);
static void Maze_RemoveWallBetween(Cell ***maze, int i, int j, int r, int c);
static int Maze_RandUnvisitedNeighbor(Cell ***maze, int row, int col, int r, int c, int chosen[2]);
static void Maze_Create(Cell ***maze, int row, int col, int i, int j);

static Cell *Cell_Create(int i, int j);
static void Cell_Destroy(Cell *self);

static Cell *Cell_Create(int i, int j) {
  Cell *self = (Cell *) malloc(sizeof(Cell));
  self->visited = false;

  if (0 == i) {
    self->bottom_wall = false;
  } else {
    self->bottom_wall = true;
  }

  if (0 == j) {
    self->left_wall = false;
  } else {
    self->left_wall = true;
  }

  return self;
}

static void Cell_Destroy(Cell *self) {
  free(self);
}


int Maze_Init(Cell ****maze, int row, int col) {
  int i, j;
  (*maze) = (Cell ***) calloc((size_t) row, sizeof *(*maze));

  for (i = 0; i < row; ++i) {
    (*maze)[i] = (Cell **) calloc((size_t) col, sizeof *((*maze)[i]));
    for (j = 0; j < col; ++j) {
      (*maze)[i][j] = Cell_Create(i, j);
    }
  }

  
  Maze_Create(*maze, row, col, 0, 0);

  return EXIT_SUCCESS;
}

void Maze_Destroy(Cell ***maze, int row, int col) {
  int i, j;

  for (i = 0; i < row; ++i) {
    for (j = 0; j < col; ++j) {
      Cell_Destroy(maze[i][j]);
    }
    free(maze[i]);
  }

  free(maze);
}

static bool Maze_IsPossible(int row, int col, int i, int j) {
  if (i < 0 || j < 0) {
    return false;
  }
  if (i >= row || j >= col) {
    return false;
  }
  return true;
}

static int Maze_RandUnvisitedNeighbor(Cell ***maze, int row, int col, int r, int c, int chosen[2]) {
  int dir[4][2] = {
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}
  };


  int i, possibles[4], len = 0, pick;


  for (i = 0; i < 4; ++i) {
    int m, n;

    m = r + dir[i][0];
    n = c + dir[i][1];

    if (false == Maze_IsPossible(row, col, m, n)) {
      continue;
    }
    if (false == (maze[m][n])->visited) {
      ++len;
      possibles[len-1] = i;
    }
  }


  if (0 == len) {
    return -1;
  }

  pick = rand() % len;
  i = possibles[pick];
  chosen[0] = r + dir[i][0];
  chosen[1] = c + dir[i][1];
  return 0;
}


static void Maze_Create(Cell ***maze, int row, int col, int i, int j) {
  int chosen[2];


  maze[i][j]->visited = true;

  while ( -1 != Maze_RandUnvisitedNeighbor(maze, row, col, i, j, chosen) ) {
    int r = chosen[0], c = chosen[1];
    Maze_RemoveWallBetween(maze, i, j, r, c);
    Maze_Create(maze, row, col, r, c);
  }
}


static void Maze_RemoveWallBetween(Cell ***maze, int i, int j, int r, int c) {
  if (i > r) {
    maze[i][j]->bottom_wall = false;
    return;
  }

  if (i < r) {
    maze[r][c]->bottom_wall = false;
    return;
  }

  if (j > c) {
    maze[i][j]->left_wall = false;
    return;
  }

  if (j < c) {
    maze[r][c]->left_wall = false;
    return;
  }
}


void Maze_ConverToWalls(Cell ***maze, int row, int col, Wall *walls[], int *wall_len, double rowSpan, double colSpan) {
  int i, j;


  for (i = 0; i < row; ++i) {
    for (j = 0; j < col; ++j) {
      double cornerX, cornerY;
      cornerX = j * colSpan;
      cornerY = i * rowSpan;
      if (true == maze[i][j]->bottom_wall) {
        ++(*wall_len);
        walls[*wall_len-1] = Wall_Create(cornerX, cornerY, cornerX + colSpan, cornerY);
      }
      if (true == maze[i][j]->left_wall) {
        ++(*wall_len);
        walls[*wall_len-1] = Wall_Create(cornerX, cornerY, cornerX, cornerY + rowSpan);
      }
    }
  }
}
