#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "mazeEnv.h"
#include <math.h>
#include <stdlib.h>


extern int min(int a, int b);

extern int max(int a, int b);

int conversion_en_state(int s_row,int s_col);

float max_tab(float* tab,int taille);

void free_tab(float** tab, int num_states);

#endif
