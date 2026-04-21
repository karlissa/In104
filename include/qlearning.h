#ifndef QLEARNING_H
#define QLEARNING_

#include <math.h>
#include "mazeEnv.h"
#include <stdlib.h>
// Initialise dynamiquement la Q-table avec des valeurs aléatoires sauf pour l'état but
void init_Q(float*** Q, int num_states, int num_actions);

// Politique epsilon-greedy avec distribution pondérée (exploration/exploitation)
int epsilon_greedy(float* state, float epsilon, int num_actions);

#endif