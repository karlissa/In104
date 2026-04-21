#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qlearning.h"

int main() {
    // Charger le labyrinthe depuis le fichier
    mazeEnv_make("../data/maze.txt");

    // Paramètres de Q-learning
    float alpha = 0.5;
    float gamma = 0.9;
    float epsilon = 0.9;
    int num_episodes = 1500;
    int num_states = rows * cols;
    int num_actions = 4;
    int goal_state = conversion_en_state(goal_row, goal_col);

    // Affichage info sur le labyrinthe
    printf("Taille du labyrinthe : %d lignes x %d colonnes\n", rows, cols);
    printf("Nombre d'actions possibles : %d\n", num_actions);

    // Initialisation de la table Q
    float** Q = NULL;
    make_Q(&Q, num_states, num_actions);

    // Lancement de l'apprentissage
    printf("\n[ DÉBUT DE L'APPRENTISSAGE Q-LEARNING ]\n");
    Qlearning(alpha, gamma, epsilon, Q, start_row, start_col,
              goal_state, num_states, num_actions, num_episodes);

     

    
    printf("\n[ POLITIQUE APPPRISE AFFICHÉE SUR LE LABYRINTHE ]\n");
    
    free(Q);

    return 0;
}