#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mazeEnv.h"
#include "functions.h"

// Fonction d'initialisation de la table Q
void make_Q(float*** Q, int num_states, int num_actions){
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

int boltzmann_exploration(float* state, int num_actions) {
    float* probs = malloc(num_actions * sizeof(float));
    float sum = 0.0;

    // calcul des poids exponentiels
    for (int i = 0; i < num_actions; ++i) {
        probs[i] = exp(state[i]); 
        sum += probs[i];
    }

    // normalisation en probabilités (on veut que la somme des poids soit égale à 1)
    for (int i = 0; i < num_actions; ++i) {
        probs[i] /= sum;
    }

    float r = (float)rand() / RAND_MAX;
    float cumulative = 0.0;

    for (int i = 0; i < num_actions; ++i) {
        cumulative += probs[i];
        if (r < cumulative) {
            free(probs);
            return i;
        }
    }

    free(probs);
    return num_actions - 1;
}

void Qlearning(float alpha, float gamma, float epsilon, float** Q, 
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

            int a = epsilon_greedy(Q[s], epsilon, num_actions);
            
            envOutput out = mazeEnv_step(a);

            int r = out.reward;
            int new_row = out.new_row;
            int new_col = out.new_col;
            int s_prime = conversion_en_state(new_row, new_col);
            done = out.done;

            // Q-learning update
            float max_Q_s_prime = max_tab(Q[s_prime], num_actions);
            Q[s][a] = Q[s][a] + alpha * (r + gamma * max_Q_s_prime - Q[s][a]);

            // Préparer l’état suivant
            row = new_row;
            col = new_col;
            s = s_prime;
            steps++;
        }

        printf("Épisode %d terminé en %d étapes.\n", episode + 1, steps);

        // Diminution progressive de epsilon (exploration -> exploitation)
        if (epsilon > 0.1f) {
            epsilon *= 0.999f;
        }
        
        // Si dernier épisode réussi, garder les miettes
        if (episode == num_episodes - 1 && done) {
            visited[row][col] = crumb; // dernière case
            add_crumbs();              // dessiner les '.' dans mazeEnv
            printf("Chemin appris affiché ci-dessous :\n");
            mazeEnv_render();
        }
    }
}

void Sarsa(float alpha, float gamma, float epsilon, float** Q,
           int start_row, int start_col, int goal_state,
           int num_states, int num_actions, int num_episodes) {

    for (int episode = 0; episode < num_episodes; ++episode) {

        mazeEnv_reset();
        init_visited();

        int row = start_row;
        int col = start_col;

        // État actuel s
        int s = conversion_en_state(row, col);

        // Dans SARSA, on choisit une première action avant la boucle
        int a = epsilon_greedy(Q[s], epsilon, num_actions);

        int done = 0;
        int steps = 0;

        while (!done && steps < 1000) {
            visited[row][col] = crumb;

            // On exécute l'action actuelle dans l'environnement
            envOutput out = mazeEnv_step(a);

            // On récupère la récompense et la nouvelle position
            int r = out.reward;
            int new_row = out.new_row;
            int new_col = out.new_col;

            // Nouvel état s'
            int s_prime = conversion_en_state(new_row, new_col);

            // Est-ce que l'épisode est terminé ?
            done = out.done;

            if (done) {
                // Si on est arrivé au goal, il n'y a pas de prochaine action utile
                Q[s][a] = Q[s][a] + alpha * (r - Q[s][a]);
            } else {
                // Dans SARSA, on choisit la prochaine action réelle a'
                int a_prime = epsilon_greedy(Q[s_prime], epsilon, num_actions);

                // Mise à jour SARSA :
                // Q(s,a) <- Q(s,a) + alpha * [r + gamma * Q(s',a') - Q(s,a)]
                Q[s][a] = Q[s][a] + alpha * (r + gamma * Q[s_prime][a_prime] - Q[s][a]);

                // On prépare l'étape suivante
                a = a_prime;
            }

            // La nouvelle position devient la position actuelle
            row = new_row;
            col = new_col;
            s = s_prime;

            steps++;
        }

        printf("Épisode SARSA %d terminé en %d étapes.\n", episode + 1, steps);

        // Diminution progressive de epsilon
        if (epsilon > 0.1f) {
            epsilon *= 0.999f;
        }

        // Si c'est le dernier épisode et que l'agent a réussi,
        // on affiche le chemin appris
        if (episode == num_episodes - 1 && done) {
            visited[row][col] = crumb;
            add_crumbs();
            printf("Chemin appris avec SARSA affiché ci-dessous :\n");
            mazeEnv_render();
        }
    }
}