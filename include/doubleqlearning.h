#ifndef DOUBLEQLEARNING_H
#define DOUBLEQLEARNING_

#include "mazeEnv.h"
#include "qlearning.h"


void DoubleQlearning(float alpha, float gamma, float epsilon, float** Q1, float** Q2, 
    int start_row, int start_col, int goal_state, 
    int num_states, int num_actions, int num_episodes);


#endif