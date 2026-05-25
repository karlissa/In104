#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "doubleqlearning.h"

int main() {
    mazeEnv_make("../data/maze_hard_21x41.txt");

    float alpha = 0.5;
    float gamma = 0.9;
    float epsilon = 1.0;
    int num_episodes = 1000;
    int num_states = rows * cols;
    int num_actions = 4;
    int goal_state = conversion_en_state(goal_row, goal_col);

    printf("Taille du labyrinthe : %d lignes x %d colonnes\n", rows, cols);
    printf("Nombre d'actions possibles : %d\n", num_actions);

    float** Q1 = NULL;
    float** Q2 = NULL;

    make_Q(&Q1, num_states, num_actions);
    make_Q(&Q2, num_states, num_actions);

    DoubleQlearning(alpha, gamma, epsilon, Q1, Q2,
        start_row, start_col, goal_state,
        num_states, num_actions, num_episodes);

    printf("\n[ POLITIQUE APPPRISE AFFICHÉE SUR LE LABYRINTHE ]\n");

    free(Q1);
    free(Q2);
    return 0;
}

/*
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

    Sarsa(alpha, gamma, epsilon, Q, start_row, start_col,
              goal_state, num_states, num_actions, num_episodes);
    
    printf("\n[ POLITIQUE APPPRISE AFFICHÉE SUR LE LABYRINTHE ]\n");
    
    free(Q);

    return 0;
}
*/