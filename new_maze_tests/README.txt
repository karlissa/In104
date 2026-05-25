Nouveaux labyrinthes pour IN104

Format : première ligne = rows,cols puis le labyrinthe.
Symboles : + = mur, s = départ, g = objectif, espace = case libre.

Utilisation rapide :
1) Copier un fichier dans data/maze.txt, par exemple :
   cp data/maze_medium_11x21.txt data/maze.txt
2) Recompiler/lancer normalement :
   make realclean && make
   cd src && ./main

Ordre conseillé pour tester :
1. maze_easy_7x15.txt
2. maze_medium_11x21.txt
3. maze_loops_15x31.txt
4. maze_deadends_17x33.txt
5. maze_hard_21x41.txt
6. maze_very_hard_25x51.txt
