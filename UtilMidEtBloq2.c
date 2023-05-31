void IA2(Grille laGrille, char pion, int * ligne, int * colonne ){
    void testerPion(int * j0, int * j1, int * j2, int pion, int nous) {
        if (pion == nous) { *j1 = *j1 + 1; }
        else if (pion != VIDE) { *j2 = *j2 + 1; }
        else { *j0 = *j0 + 1; }
    }
    void checkerAlignements(Grille laGrille, int * importance, int ligne, int colonne, int pion, int tours, bool compterAlignDeux) {
        int j0, j1, j2;
        int j, k;
        *importance = 0;
        j0 = 0;
        j1 = 0;
        j2 = 0;
        if (ligne < 4 && compterAlignDeux != true) { // pcq compterAlignDeux c'est pour le check du pion au dessus, donc on a pas besoin de tester ce qu'il y a en dessous
            // 
            for (j = ligne + 1; j < ligne + 3; j++) {
                testerPion(&j0, &j1, &j2, laGrille[j][colonne], pion);
            }
            // 
            if (j1 == 2 || j2 == 2) { // si possibilité de 3 pions
                if (j < NB_LIGNES) { testerPion(&j0, &j1, &j2, laGrille[j][colonne], pion); } // tester pour voir si il y a un troisième pion
            }
            if (j2 > 2 || j1 > 2) { *importance = 3;  }
            else if (tours == 1 && *importance < 2 && j2 > 1) { *importance = 2;  }
        }
        if (*importance != 3) {
            for (j = -1; j < 2 && *importance != 3; j++) {
                if (colonne + j > 0 && colonne + j < NB_COLONNES - 1) {
                    // 
                    j0 = 0;
                    j1 = 0;
                    j2 = 0;
                    for (k = j - 1; k < j + 2; k++) {
                        testerPion(&j0, &j1, &j2, laGrille[ligne][colonne + k], pion);
                    }
                    // 
                    if (j1 == 2 || j2 == 2 || j0 > (2 - tours + 1 + (tours == 3))) {
                        if (colonne + j - 2 >= 0) { testerPion(&j0, &j1, &j2, laGrille[ligne][colonne + j - 2], pion); }
                        if (colonne + k < NB_COLONNES) { testerPion(&j0, &j1, &j2, laGrille[ligne][colonne + k], pion); }
                    }
                    if (j2 > 2 || j1 > 2) { *importance = 3;  }
                    else if (tours == 1 && *importance < 2 && (j2 > 1 && j2 + j0 > 3)) { *importance = 2;  }
                    if (j1 + j0 > 3 && *importance == 0) { *importance = 1;  } //ne marche pas pcq nouvelle methode consiste à n'en tester que 2 (si on teste 3 à gauche par exemple, ça peut détecter même si pas collé à la colonne actuelle)
                }
            }
            if (*importance != 3) {
                for (j = -1; j < 2 && *importance != 3; j++) {
                    if (ligne + j > 0 && ligne + j < NB_LIGNES - 1 && colonne + j > 0 && colonne + j < NB_COLONNES - 1) {
                        // 
                        j0 = 0;
                        j1 = 0;
                        j2 = 0;
                        for (k = j - 1; k < j + 2; k++) {
                            testerPion(&j0, &j1, &j2, laGrille[ligne + k][colonne + k], pion);
                        }
                        // 
                        if (j1 == 2 || j2 == 2 || j0 > (2 - tours + 1 + (tours == 3))) {
                            if (ligne + (j - 2) >= 0 && colonne + (j - 2) >= 0) { testerPion(&j0, &j1, &j2, laGrille[ligne + (j - 2)][colonne + (j - 2)], pion); }
                            if (ligne + k < NB_LIGNES && colonne + k < NB_COLONNES) { testerPion(&j0, &j1, &j2, laGrille[ligne + k][colonne + k], pion); }
                        }
                        if (j2 > 2 || j1 > 2) { *importance = 3;  }
                        else if (tours == 1 && *importance < 2 && (j2 > 1 && j2 + j0 > 3)) { *importance = 2;  }
                        if (j1 + j0 > 3 && *importance == 0) { *importance = 1;  } //ne marche pas pcq nouvelle methode consiste à n'en tester que 2 (si on teste 3 à gauche par exemple, ça peut détecter même si pas collé à la colonne actuelle)
                    }
                }
                if (*importance != 3) {
                    for (j = -1; j < 2 && *importance != 3; j++) {
                        if (ligne - j > 0 && ligne - j < NB_LIGNES - 1 && colonne + j > 0 && colonne + j < NB_COLONNES - 1) {
                            // 
                            j0 = 0;
                            j1 = 0;
                            j2 = 0;
                            for (k = j - 1; k < j + 2; k++) {
                                testerPion(&j0, &j1, &j2, laGrille[ligne - k][colonne + k], pion);
                            }
                            // 
                            if (j1 == 2 || j2 == 2 || j0 > (2 - tours + 1 + (tours == 3))) { // rique de prioriser un "O |  |  |  | O" si j0 == 3
                                if (ligne - (j - 2) < NB_LIGNES && colonne + (j - 2) >= 0) { testerPion(&j0, &j1, &j2, laGrille[ligne - (j - 2)][colonne + (j - 2)], pion); }
                                if (ligne - k >= 0 && colonne + k < NB_COLONNES) { testerPion(&j0, &j1, &j2, laGrille[ligne - k][colonne + k], pion); }
                            }
                            if (j2 > 2 || j1 > 2) { *importance = 3;  }
                            else if (tours == 1 && *importance < 2 && (j2 > 1 && j2 + j0 > 3)) { *importance = 2;  }
                            if (j1 + j0 > 3 && *importance == 0) { *importance = 1;  } //ne marche pas pcq nouvelle methode consiste à n'en tester que 2 (si on teste 3 à gauche par exemple, ça peut détecter même si pas collé à la colonne actuelle)
                        }
                    }
                }
            }
        }
    }
    int i;
    int tours = 0;
    int colonneUtile = 8;
    *ligne = 8;
    *colonne = 8;
    int ligneDeColonne;
    int importance;
    i = 3;
    while (*ligne == 8 && (i != 3 || tours != 3)) { // il fait les 3 tours même si colonne != 8 et ça fait chier mais il se démerde
        importance = 0;
        ligneDeColonne = chercherLigne(laGrille, i);
        if (i == 3) { tours++; };
        if (ligneDeColonne != -1) {
            checkerAlignements(laGrille, &importance, ligneDeColonne, i, pion, tours, false);
            if (importance == 3) {
                *ligne = ligneDeColonne;
                *colonne = i;
            } else if (importance == 2 && *colonne == 8) {
                if (ligneDeColonne != 0) {
                    checkerAlignements(laGrille, &importance, ligneDeColonne - 1, i, pion, tours, true);
                    if (importance < (2 + (tours == 3))) { // ou !=3 ? ou on fait en fonction du tour ?
                        *colonne = i;
                        
                    }
                } else {
                    *colonne = i; // ou rien ? on ignore la dernière ligne en tant que utile ? comme l'ia ?
                    
                }
            }
        }
        if ((importance == 1 || ligneDeColonne > 2) && colonneUtile == 8) {
            if (ligneDeColonne != 0) {
                checkerAlignements(laGrille, &importance, ligneDeColonne - 1, i, pion, tours, true);
                if (importance < (2 + (tours == 3))) { // ou !=3 ? ou on fait en fonction du tour ?
                    colonneUtile = i;
                    
                }
            } else {
                colonneUtile = i; // ou rien ? on ignore la dernière ligne en tant que utile ? comme l'ia ?
                
            }
        }
        i++;
        i = i % NB_COLONNES;
    }
    if (*colonne == 8) { *colonne = colonneUtile; }
    if (*colonne == 8) {
        for (int rescue = 0; rescue < NB_COLONNES && *colonne == 8; rescue++) {
            if (chercherLigne(laGrille, rescue) != -1) { *colonne = rescue; }
        }
    }
    if (*ligne == 8) { *ligne = chercherLigne(laGrille, *colonne); }
}