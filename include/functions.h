#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "mazeEnv.h"
#include <math.h>
#include <stdlib.h>


extern int min(int a, int b);

extern int max(int a, int b);

int max_i(float* tab,int taille);

int conversion_en_state(int s_row,int s_col);

float max_tab(float* tab,int taille);

void free_tab(float** tab, int num_states);

float** somme_tabs(float** Q1,float** Q2,int num_rows,int num_cols);

#endif
