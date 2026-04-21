# Reinforcement Learning Project : Maze 
# Projet Labyrinthe - DFS et Q-learning

## Présentation

Ce projet a pour but de résoudre un labyrinthe en C.

Pour le moment, nous avons surtout travaillé sur :
- la création et la gestion de l’environnement du labyrinthe ;
- une recherche de chemin avec DFS ;
- une première implémentation du Q-learning ;
- un `main` qui charge le labyrinthe et lance l’apprentissage.

Le projet n’est pas encore terminé. Ce README décrit uniquement les parties actuellement réalisées.

---

## Objectif

L’idée est de faire évoluer un agent dans un labyrinthe à partir d’une case de départ jusqu’à une case objectif.

Deux approches sont présentes à ce stade :
- une approche classique avec DFS ;
- une approche d’apprentissage par renforcement avec Q-learning.

---

## Fichiers réalisés

### `mazeEnv.c`

Ce fichier gère l’environnement du labyrinthe.

Fonctions présentes :
- `alloc_mazeEnv()` : alloue dynamiquement le labyrinthe ;
- `mazeEnv_make(char* file_name)` : charge le labyrinthe depuis un fichier texte, lit ses dimensions et repère le départ et l’arrivée ;
- `mazeEnv_render()` : affiche le labyrinthe dans le terminal ;
- `mazeEnv_reset()` : remet l’agent sur la case de départ ;
- `mazeEnv_step(action a)` : applique une action et renvoie le nouvel état, la récompense et si l’objectif est atteint ;
- `alloc_visited()` : alloue la matrice des cases visitées ;
- `init_visited()` : initialise cette matrice selon le contenu du labyrinthe ;
- `add_crumbs()` : ajoute des points `.` sur le chemin trouvé.

---

### `functions.c`

Ce fichier contient des fonctions utilitaires utilisées dans le projet.

Fonctions présentes :
- `min(int a, int b)` ;
- `max(int a, int b)` ;
- `max_i(float* tab, int taille)` : retourne l’indice de la plus grande valeur d’un tableau ;
- `max_tab(float* tab, int taille)` : retourne la plus grande valeur d’un tableau ;
- `conversion_en_state(int s_row, int s_col)` : convertit une position du labyrinthe en état ;
- `free_tab(float** tab, int num_states)` : libère une table allouée dynamiquement.

---

### `dfs.c`

Ce fichier contient une recherche en profondeur du labyrinthe.

Fonctions présentes :
- `dfs(int row, int col)` : explore récursivement le labyrinthe jusqu’à trouver la sortie ;
- un `main` de test permettant de charger le labyrinthe, lancer le DFS, puis afficher le chemin trouvé avec des miettes.

Le DFS permet surtout de vérifier que le labyrinthe peut être parcouru et d’afficher un chemin vers la sortie.

---

### `qlearning.c`

Ce fichier contient la partie apprentissage par renforcement.

Fonctions présentes :
- `make_Q(float*** Q, int num_states, int num_actions)` : alloue et initialise la table Q ;
- `epsilon_greedy(float* state, float epsilon, int num_actions)` : choisit une action avec une politique epsilon-greedy ;
- `Qlearning(float alpha, float gamma, float epsilon, float** Q, int start_row, int start_col, int goal_state, int num_states, int num_actions, int num_episodes)` : réalise l’apprentissage sur plusieurs épisodes.

Principe actuel :
- l’agent part de la position de départ ;
- il choisit des actions dans le labyrinthe ;
- il met à jour sa table Q au fur et à mesure ;
- en fin d’apprentissage, si l’objectif est atteint, le chemin appris peut être affiché sur le labyrinthe.

---

### `main.c`

Le `main` actuel :
- charge le labyrinthe depuis `../data/maze.txt` ;
- définit les paramètres principaux du Q-learning (`alpha`, `gamma`, `epsilon`, nombre d’épisodes) ;
- calcule le nombre d’états et le nombre d’actions ;
- crée la table Q avec `make_Q` ;
- lance la fonction `Qlearning(...)` ;
- affiche des informations sur le labyrinthe ;
- libère la mémoire à la fin avec `free_tab`.

---

## Paramètres utilisés actuellement

Dans le `main`, les paramètres choisis sont :
- `alpha = 0.5`
- `gamma = 0.9`
- `epsilon = 0.9`
- `num_episodes = 1500`

Le nombre d’actions possibles est fixé à 4.

---

## Ce que le programme fait actuellement

À ce stade, le projet permet :
- de lire un labyrinthe depuis un fichier ;
- d’afficher le labyrinthe ;
- de tester une résolution avec DFS ;
- de lancer un apprentissage par Q-learning ;
- d’afficher le chemin appris si l’agent atteint l’objectif au dernier épisode.

---

## Avancement du projet

Parties réalisées :
- environnement du labyrinthe ;
- affichage ;
- gestion des états visités ;
- DFS ;
- Q-learning ;
- `main` de lancement pour le Q-learning.

Parties non décrites ici :
- toute autre extension non encore implémentée dans nos fichiers actuels.

---

## Remarque

Ce README correspond uniquement à notre avancement actuel du projet. Il ne décrit pas une version finale complète, mais seulement les éléments que nous avons effectivement codés jusqu’à maintenant.