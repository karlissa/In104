# Reinforcement Learning Project : Maze
# Projet Labyrinthe - DFS, Q-learning, SARSA et Double Q-learning

## Présentation

Ce projet implémente un environnement de labyrinthe en C et plusieurs méthodes de résolution ou d’apprentissage :

- DFS pour vérifier l’existence d’un chemin ;
- Q-learning ;
- SARSA ;
- Double Q-learning ;
- politiques d’exploration `epsilon_greedy` et `boltzmann_exploration`.

L’agent part de la case `s` et doit atteindre la case `g` en évitant les murs `+`.

---

## Structure du projet

```text
In104/
├── data/
│   ├── maze.txt
│   ├── maze_deadends_17x33.txt
│   ├── maze_hard_21x41.txt
│   ├── maze_loops_15x31.txt
│   ├── maze_very_hard_25x51.txt
│   └── README.txt
│
├── new_maze_tests/
│   ├── maze_easy_7x15.txt
│   ├── maze_medium_11x21.txt
│   ├── maze_loops_15x31.txt
│   ├── maze_deadends_17x33.txt
│   ├── maze_hard_21x41.txt
│   ├── maze_very_hard_25x51.txt
│   └── README.txt
│
├── include/
│   ├── dfs.h
│   ├── doubleqlearning.h
│   ├── functions.h
│   ├── main.h
│   ├── mazeEnv.h
│   └── qlearning.h
│
├── src/
│   ├── dfs.c
│   ├── doubleqlearning.c
│   ├── functions.c
│   ├── main.c
│   ├── mazeEnv.c
│   └── qlearning.c
│
├── Makefile
└── README.md
```

---

## Compilation

La compilation du programme principal se fait avec :

```bash
make
```

L’exécutable généré est :

```text
src/main
```

Le `Makefile` compile le programme principal avec :

- `main.c`
- `functions.c`
- `mazeEnv.c`
- `qlearning.c`
- `doubleqlearning.c`

La librairie mathématique est liée avec `-lm`, nécessaire pour `exp()` dans la politique de Boltzmann.

---

## Lancement

Le programme utilise des chemins relatifs du type :

```c
mazeEnv_make("../data/maze_hard_21x41.txt");
```

Il faut donc lancer l’exécutable depuis le dossier `src` :

```bash
cd src
./main
```

---

## Fichiers de labyrinthes

Les labyrinthes sont stockés dans `data/` et `new_maze_tests/`.

Format attendu :

```text
nombre_lignes,nombre_colonnes
labyrinthe
```

Symboles utilisés :

```text
+ : mur
s : départ
g : objectif
  : case libre
. : chemin affiché après apprentissage ou DFS
```

Exemple :

```text
7,15
+++++++++++++++
+s+   +       +
+ + + + + +++ +
+   +   +   +g+
+++ +++++ +++ +
+             +
+++++++++++++++
```

Labyrinthes ajoutés :

- `maze_easy_7x15.txt`
- `maze_medium_11x21.txt`
- `maze_loops_15x31.txt`
- `maze_deadends_17x33.txt`
- `maze_hard_21x41.txt`
- `maze_very_hard_25x51.txt`

Pour tester un autre labyrinthe, il suffit de modifier le fichier lu dans `main.c`, par exemple :

```c
mazeEnv_make("../data/maze_very_hard_25x51.txt");
```

---

## `mazeEnv.c`

Ce fichier gère l’environnement du labyrinthe.

Fonctions principales :

- `alloc_mazeEnv()` : alloue la matrice du labyrinthe ;
- `mazeEnv_make(char* file_name)` : lit un fichier de labyrinthe, récupère les dimensions, le départ et l’objectif ;
- `mazeEnv_render()` : affiche le labyrinthe ;
- `mazeEnv_render_pos()` : affiche le labyrinthe avec la position actuelle de l’agent ;
- `mazeEnv_reset()` : remet l’agent au départ ;
- `mazeEnv_step(action a)` : applique une action et renvoie la récompense, la nouvelle position et `done` ;
- `env_action_sample()` : retourne une action aléatoire ;
- `alloc_visited()` : alloue la matrice `visited` ;
- `init_visited()` : initialise `visited` à partir du labyrinthe ;
- `add_crumbs()` : ajoute les points `.` sur les cases marquées comme chemin.

Dans `mazeEnv_step`, les récompenses utilisées sont :

```text
Déplacement normal : -1
Mur / mouvement impossible : -10
Objectif atteint : +1000
```

---

## `functions.c`

Fonctions utilitaires :

- `min(int a, int b)` ;
- `max(int a, int b)` ;
- `max_i(float* tab, int taille)` : retourne l’indice du maximum ;
- `max_tab(float* tab, int taille)` : retourne la valeur maximale ;
- `conversion_en_state(int s_row, int s_col)` : convertit une position `(row, col)` en état ;
- `free_tab(float** tab, int num_states)` : libère une table allouée dynamiquement ;
- `somme_tabs(float** Q1, float** Q2, int num_rows, int num_cols)` : retourne la somme de deux tables Q.

---

## `dfs.c`

Ce fichier contient une résolution classique par recherche en profondeur.

Fonctions présentes :

- `dfs(int row, int col)` : explore récursivement les cases du labyrinthe ;
- `main()` : charge `../data/maze.txt`, initialise `visited`, lance DFS et affiche le chemin.

Le DFS utilise `visited` pour éviter les murs et les cases déjà explorées.

---

## `qlearning.c`

Ce fichier contient les méthodes d’apprentissage principales.

Fonctions présentes :

- `make_Q(float*** Q, int num_states, int num_actions)` : alloue et initialise une table Q ;
- `epsilon_greedy(float* state, float epsilon, int num_actions)` : choisit une action avec exploration/exploitation ;
- `boltzmann_exploration(float* state, int num_actions)` : choisit une action avec une probabilité basée sur `exp(Q)` ;
- `Qlearning(...)` : entraîne l’agent avec Q-learning ;
- `Sarsa(...)` : entraîne l’agent avec SARSA.

### Q-learning

La mise à jour utilisée est :

```text
Q(s,a) <- Q(s,a) + alpha * [r + gamma * max Q(s',a') - Q(s,a)]
```

### SARSA

SARSA choisit aussi l’action suivante avant la mise à jour :

```text
Q(s,a) <- Q(s,a) + alpha * [r + gamma * Q(s',a') - Q(s,a)]
```

### Boltzmann

La fonction `boltzmann_exploration` calcule des probabilités à partir des valeurs Q avec :

```c
exp(state[i])
```

Elle est présente dans le code, et peut être utilisée à la place de `epsilon_greedy` dans `Qlearning`.

---

## `doubleqlearning.c`

Ce fichier contient l’algorithme Double Q-learning.

Fonction présente :

- `DoubleQlearning(...)`

Le Double Q-learning utilise deux tables :

```text
Q1
Q2
```

L’action est choisie à partir de la somme :

```text
Q1 + Q2
```

Puis, à chaque étape, une seule table est mise à jour avec une probabilité de 50 %.

---

## `main.c`

Le `main` actif charge actuellement :

```c
mazeEnv_make("../data/maze_hard_21x41.txt");
```

Paramètres actuels :

```c
alpha = 0.5
gamma = 0.9
epsilon = 1.0
num_episodes = 1000
num_actions = 4
```

Le programme crée deux tables `Q1` et `Q2`, puis lance :

```c
DoubleQlearning(...)
```

Un ancien bloc de code pour `Qlearning` et `Sarsa` est présent en commentaire dans `main.c`.

---

## Changer d’algorithme

Le programme principal lance actuellement Double Q-learning.

Pour utiliser Q-learning ou SARSA, il faut modifier le `main.c` en utilisant les appels déjà présents dans le bloc commenté :

```c
Qlearning(...)
Sarsa(...)
```

---

## Paramètres importants

- `alpha` : taux d’apprentissage ;
- `gamma` : importance des récompenses futures ;
- `epsilon` : niveau d’exploration ;
- `num_episodes` : nombre d’épisodes d’entraînement ;
- `steps < 1000` ou `steps < 3000` : limite maximale d’étapes par épisode selon l’algorithme.

Pour les grands labyrinthes, il peut être utile d’augmenter `num_episodes`.

---

## Résumé

Le projet permet de :

- charger plusieurs labyrinthes depuis des fichiers texte ;
- résoudre un labyrinthe par DFS ;
- entraîner un agent avec Q-learning ;
- entraîner un agent avec SARSA ;
- entraîner un agent avec Double Q-learning ;
- tester epsilon-greedy et Boltzmann comme politiques d’exploration ;
- comparer les performances sur différents labyrinthes.
