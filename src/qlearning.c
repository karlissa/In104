#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mazeEnv.h"
#include "functions.h"

// Fonction d'initialisation de la table Q
void init_Q(float*** Q, int num_states, int num_actions){
    srand(time(NULL)); // Initialisation du générateur aléatoire

    // Allocation dynamique de la Q-table (matrice de float)
    *Q = malloc(sizeof(float*) * num_states);
    if(*Q==NULL) exit(EXIT_FAILURE);

    for(int i = 0; i < num_states; ++i){
        (*Q)[i] = malloc(sizeof(float) * num_actions);
        if((*Q)[i]==NULL){
            for (int j = 0; j < i; ++j) {
                free((*Q)[j]);
            }
            free(*Q);
            exit(EXIT_FAILURE);
        }
    }
    // Initialisation des valeurs de Q
    for(int i = 0; i < num_states; ++i){
        for(int j = 0; j < num_actions; ++j){
            (*Q)[i][j] = 0.0;
        }
    }
}

// Politique epsilon-greedy pondérée
int epsilon_greedy(float* state, float epsilon, int num_actions){
    // Étape 1 : tirage aléatoire pour décider si on explore ou on exploite
    float r = (float)rand() / RAND_MAX;

    if (r < epsilon) {
        // Avec probabilité epsilon, on choisit une action complètement aléatoire
        return rand() % num_actions;
    } else {
        // Étape 2 : on suit une politique pondérée
        //  - action optimale (greedy) avec proba 1 - epsilon
        //  - autres actions avec proba epsilon / (n - 1), avec n: le nombre d'actions

        int best_action = max_i(state, num_actions); // index de l'action optimale

        float r2 = (float)rand() / RAND_MAX; // nouveau tirage aléatoire
        float cumulative = 0.0;

        // Tirage selon distribution pondérée
        for (int a = 0; a < num_actions; ++a) {
            //boucle qui marche pour le cas général-pour le maze, on a 4 actions
            float prob = (a == best_action) 
                         ? (1 - epsilon) 
                         : (epsilon / (num_actions - 1));
            cumulative += prob;
            if (r2 < cumulative) {   
                // On additionne les probabilités (cumulative) jusqu'à dépasser r2,
                // ce qui revient à tirer une action selon cette distribution discrète.
                return a;
            }
        }

        // Sécurité en cas de problème d'arrondi
        return best_action;
    }
}