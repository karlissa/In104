#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mazeEnv.h"
#include "functions.h"
#include "doubleqlearning.h"

void DoubleQlearning(float alpha, float gamma, float epsilon, float** Q1, float** Q2, 
    int start_row, int start_col, int goal_state, 
    int num_states, int num_actions, int num_episodes) {

    for (int episode = 0; episode < num_episodes; ++episode) {
        mazeEnv_reset();
        init_visited(); 

        int row = start_row;
        int col = start_col;
        int s = conversion_en_state(row, col);
        int done = 0;
        int steps = 0;

        while (!done && steps < 1000) {
            visited[row][col] = crumb; 

            // Créer Q1 + Q2 pour epsilon-greedy
            float** Q_sum = somme_tabs(Q1, Q2, num_states, num_actions);
            int a = epsilon_greedy(Q_sum[s], epsilon, num_actions);
            // Appliquer l'action
            envOutput out = mazeEnv_step(a);
            int r = out.reward;
            int new_row = out.new_row;
            int new_col = out.new_col;
            int s_prime = conversion_en_state(new_row, new_col);
            done = out.done;

            // Mise à jour avec 50% de chance sur Q1 ou Q2
            float random_choice = (float)rand() / RAND_MAX;
            if (random_choice < 0.5) {
                int a_max = max_i(Q1[s_prime], num_actions);
                Q1[s][a] += alpha * (r + gamma * Q2[s_prime][a_max] - Q1[s][a]);
            } else {
                int a_max = max_i(Q2[s_prime], num_actions);
                Q2[s][a] += alpha * (r + gamma * Q1[s_prime][a_max] - Q2[s][a]);
            }

            // Passage à l’état suivant
            row = new_row;
            col = new_col;
            s = s_prime;
            steps++;
        }

        printf("Épisode %d terminé en %d étapes.\n", episode + 1, steps);

        if (epsilon > 0.1f) {
            epsilon *= 0.995f;
        }

        if (episode == num_episodes - 1) {
        if (done) {
            visited[row][col] = crumb;
            printf("Chemin appris affiché ci-dessous :\n");
        } else {
            printf("Dernier épisode non réussi, chemin partiel affiché ci-dessous :\n");
        }
        add_crumbs();
        mazeEnv_render();
        }
    }
}