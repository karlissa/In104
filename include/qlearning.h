#ifndef QLEARNING_H
#define QLEARNING_

#include <math.h>
#include "mazeEnv.h"
#include <stdlib.h>
// Initialise dynamiquement la Q-table avec des valeurs aléatoires sauf pour l'état but
void make_Q(float*** Q, int num_states, int num_actions);

// Politique epsilon-greedy avec distribution pondérée (exploration/exploitation)
int epsilon_greedy(float* state, float epsilon, int num_actions);

int boltzmann_exploration(float* state, int num_actions);

void Qlearning(float alpha, float gamma, float epsilon, float** Q, 
               int start_row, int start_col, int goal_state, 
               int num_states, int num_actions, int num_episodes);

void Sarsa(float alpha, float gamma, float epsilon, float** Q,
           int start_row, int start_col, int goal_state,
           int num_states, int num_actions, int num_episodes);
#endif