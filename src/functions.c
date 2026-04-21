#include "functions.h"

int min(int a, int b){
    return (a>b) ? b : a;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

// Fonction qui retourne l'indice de la valeur maximale dans un tableau
int max_i(float* tab,int taille){
    int n = 0;
    for(int i = 0; i < taille; ++i){
        if(tab[i] > tab[n]){
            n = i;
        }
    }
    return n;
}

float max_tab(float* tab,int taille){
    float max=tab[0];
    for(int i=0;i<taille;++i){
        if(tab[i]>max){
            max=tab[i];
        }
    }
    return max;
}

void free_tab(float** tab, int num_states) {
    for (int i = 0; i < num_states; i++) {
        free(tab[i]);
    }
    free(tab);
}

int conversion_en_state(int s_row,int s_col){
    int s=s_row*cols+s_col;
    return s;
}

