#ifndef DFS_H
#define DFS_H

#include "mazeEnv.h"
#include "functions.h"
#include "qlearning.h"

int dfs(int row, int col);
void follow_Qpolicy(float** Q, int start_row, int start_col);

#endif