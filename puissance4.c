/**
 * @file puissance4.c
 * @brief Jeu du Puissance 4
 * @author Colin
 * @version 1
 * @date 20/11/2022
 *
 * Puissance 4 informatique avec plein de fonctionnalités incluses :
 * - Véritable grille adaptative
 * - Couleurs
 * - Noms des joueurs
 * - Utilisation facile
 * - Beaucoup d'options de personnalisation disponibles
 * - Et plein d'autres...
 * Jouez désormais au Puissance 4 comme en vrai !
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Pour l'aléatoire
#include <stdbool.h>

#define NBLIG 6
#define NBCOL 7

const char COULEUR_A='1';
const char COULEUR_B='3';
const char COULEUR_R[5]="\e[0m";
const char COULEUR[5]="\e[0;";
const char PION_A='X';
const char PION_B='O';
const char VIDE=' ';

typedef int Grille[NBLIG][NBCOL];

/**
 * @brief Procédure d'effacement de la console
 */
void effacer()
{
  /*
  * Séquences d'échappement ANSI qui permettent de revenir au début de la
  * console, puis de tout effacer
  */
  printf("\e[H\e[0J"); 
}

/**
 * @brief Initialise la grille en affectant 0 à chacun de ses éléments
 * @param g de type Grille en entrée/sortie, représente la grille de jeu
 */
void initGrille(Grille g)
{
  int i, j;
  for (i = 0; i < NBLIG; i++)
  {
    for (j = 0; j < NBCOL; j++)
    {
      g[i][j] = 0;
    }
  }
}

/**
 * @brief Procédure qui affiche une Grille
 * @param g de type Grille en entrée/sortie: la grille à afficher
 */
void afficher(Grille g) {
  int i, j;
  printf("┌");
  for (j = 1; j < NBCOL; j++)
  {
    printf("───┬");
  }
  printf("───┐\n");
  for (i = 0; i < NBLIG; i++)
  {
    printf("│ ");
    for (j = 0; j < NBCOL; j++)
    {
      if (g[i][j] == 1)
      {
        printf("%s3%cm%c%s", COULEUR, COULEUR_A, PION_A, COULEUR_R);
      }
      else if (g[i][j] == 2)
      {
        printf("%s3%cm%c%s", COULEUR, COULEUR_B, PION_B, COULEUR_R);
      }
      else
      {
        printf("%c", VIDE);
      }
      printf(" │ ");
    }
    printf("\n");
    if (i != NBLIG - 1)
    {
      printf("├");
      for (j = 1; j < NBCOL; j++)
      {
        printf("───┼");
      }
      printf("───┤\n");
    }
  }
  printf("└");
  for (j = 1; j < NBCOL; j++)
  {
    printf("───┴");
  }
  printf("───┘\n");
  for (i = 1; i <= NBCOL; i++)
  {
    printf("  %d ",i);
  }
  printf("\n");
};

int trouverLigne(Grille g, int colonne)
{
  int ligne = -1;
  if (g[0][colonne] == 0)
  {
    ligne = NBLIG - 1;
    while (g[ligne][colonne] != 0) {
      ligne--;
    }
  }
  return ligne;
}

int choisirColonne(Grille g, char joueur[100])
{
  int choix, ligne;
  choix = 0;
  ligne = 0;
  while (choix < 1 || choix > NBCOL) {
    printf("\n%s > ", joueur);
    scanf("%d", &choix); // (On suppose que le type de l'entrée est le bon)
    /* Effacement de l'affichage de l'entrée et ce qu'il y a en dessous */
    printf("\e[%d;1H\e[0J", (2*NBLIG)+5); 
    /* Préparation de l'affichage du message d'erreur en dessous de l'entrée */
    printf("\e[%d;1H", (2*NBLIG)+6);
    if (choix < 1 || choix > NBCOL)
    {
      printf("Le nombre doit être compris entre 1 et %d ! Rejouez\n", NBCOL);
      choix = 0;
    }
    else
    {
      ligne = trouverLigne(g, choix-1);
      if (ligne == -1)
      {
        printf("La colonne n°%d est pleine ! Rejouez\n", choix);
        choix = 0;
      }
    }
    /* Retour en position pour redemander l'entrée */
    printf("\e[%d;1H", (2*NBLIG)+4); 
  }
  return choix-1;
}

bool estVainqueur(Grille g, int ligne, int colonne) {
  /* hold sert à retenir le nombre pour définir la limite de la boucle for */
  int pos, hold; 
  bool gagnant;
  gagnant = true;
  /* Recherche verticale */
  for (hold = 0; hold < NBLIG - 2; hold++)
  {
    for (pos = hold; pos < hold + 4; pos++)
    {
      if (g[pos][colonne] != g[ligne][colonne])
      {
        /*
        * Dépasse pour forcer l'arrêt de la boucle et signaler qu'il n'y a pas
        * de gagnant sur cette sélection de 4 pions à la suite
        */
        pos = NBLIG;
      }
    }
    /*
    * Si il n'y a pas eu de signal d'arrêt forcé de la boucle
    * Note: NBLIG + 1 car la boucle va quand même rajouter 1 avant de s'arrêter
    */
    if (pos != NBLIG + 1) 
    {
      /* Arrête la boucle et signale qu'on a trouvé une combinaison gagnante */
      hold = NBLIG; 
    }
  }
  /* Si on n'a pas trouvé de gagnant sur la méthode de recherche verticale */
  if (hold != NBLIG + 1)
  {
    /* Recherche horizontale */
    for (hold = 0; hold < NBCOL - 2; hold++)
    {
      for (pos = hold; pos < hold + 4; pos++)
      {
        if (g[ligne][pos] != g[ligne][colonne])
        {
          pos = NBCOL;
        }
      }
      if (pos != NBCOL + 1)
      {
        hold = NBCOL;
      }
    }
    /* Si on n'a pas trouvé de gagnant sur la méthode de recherche horizontale */
    if (hold != NBCOL + 1)
    {
      /* Recherche diagonale de haut-gauche à bas-droite */
      if (ligne < colonne)
      {
        hold = ligne;
      }
      else
      {
        hold = colonne;
      }
      while (((ligne - hold) < (NBLIG - 3)) && ((colonne - hold) < (NBCOL - 3))) {
        for (pos = hold; pos > hold - 4; pos--)
        {
          if (g[ligne - pos][colonne - pos] != g[ligne][colonne])
          {
            pos = -NBLIG;
          }
        }
        if (pos != -NBLIG - 1)
        {
          hold = -NBLIG;
        }
        hold--;
      }
      if (hold != -NBLIG - 1)
      {
        /* Recherche diagonale de bas-gauche à haut-droite */
        if ((NBLIG - ligne) < colonne)
        {
          hold = (NBLIG - ligne);
        }
        else
        {
          hold = colonne;
        }
        while (((ligne + hold) > 2) && ((colonne - hold) < (NBCOL - 3))) {
          for (pos = hold; pos > hold - 4; pos--)
          {
            if (g[ligne + pos][colonne - pos] != g[ligne][colonne])
            {
              pos = -NBCOL;
            }
          }
          if (pos != -NBCOL - 1)
          {
            hold = -NBCOL;
          }
          hold--;
        }
        if (hold != -NBCOL - 1)
        {
          /* Si aucune des recherches n'a fonctionné, le pion n'est pas gagnant */
          gagnant = false;
        }
      }
    }
  }
  return gagnant;
}

bool grillePleine(Grille g)
{
  int i;
  i = 0;
  while ((g[0][i] != 0) && (i < NBCOL)) {
    i++;
  }
  return (i == NBCOL);
}

void jouer(Grille g, int joueur, char nomJoueur[100], int *ligne, int *colonne)
{
  printf("Jouer dans quelle colonne ? (1 à 7)\n");
  afficher(g);
  *colonne = choisirColonne(g, nomJoueur);
  *ligne = trouverLigne(g, *colonne);
  g[*ligne][*colonne] = joueur;
}

void finDePartie(char gagnant[100])
{
  if (strcmp(gagnant, "") != 0)
  {
    printf("%s a gagné !\n", gagnant);
  }
  else
  {
    printf("La grille est pleine, égalité !\n");
  }
}

int main()
{
  Grille g;
  char j1[100],j2[100];
  int choix, vainqueur, joueur;
  int ligne, colonne;
  choix = 0;
  /* Répéter tant que "Arrêter le programme ?" n'a pas été confirmé */
  while (choix != 1) {
    effacer();
    printf("  _____       _                                _  _   \n");
    printf(" |  __ \\     (_)                              | || |  \n");
    printf(" | |__) |   _ _ ___ ___  __ _ _ __   ___ ___  | || |_ \n");
    printf(" |  ___/ | | | / __/ __|/ _` | '_ \\ / __/ _ \\ |__   _|\n");
    printf(" | |   | |_| | \\__ \\__ \\ (_| | | | | (_|  __/    | |  \n");
    printf(" |_|    \\__,_|_|___/___/\\__,_|_| |_|\\___\\___|    |_|  \n\n");
    printf("Entrez le nom du joueur 1 : ");
    scanf("%s",j1);
    printf("\nEntrez le nom du joueur 2 : ");
    scanf("%s",j2);
    choix = 1;
    /* Répéter tant que "Rejouer ensemble ?" n'a pas été dénié */
    while (choix != 0) {
      initGrille(g);
      srand(time(NULL)); // Initialisation de la graine aléatoire
      joueur = rand() % 2 + 1; // Définition aléatoire du joueur de départ
      vainqueur = 0;
      while (!(vainqueur) && !(grillePleine(g))) {
        effacer();
        if (joueur == 1)
        {
          jouer(g, joueur, j1, &ligne, &colonne);
        }
        else if (joueur == 2)
        {
          jouer(g, joueur, j2, &ligne, &colonne);
        }
        if (estVainqueur(g, ligne, colonne))
        {
          /* Si le pion placé est gagnant, alors le gagnant est le joueur actuel */
          vainqueur = joueur;
        }
        joueur = (joueur % 2) + 1; // Changement de joueur
      }
      effacer();
      afficher(g);
      switch (vainqueur)
      {
        case 1:
          finDePartie(j1);
          break;
        case 2:
          finDePartie(j2);
          break;
        default:
          finDePartie("");
          break;
      }
      choix = 2;
      while (choix != 0 && choix != 1) {
        printf("\nRejouer ensemble ? (1 = Oui, 0 = Non) ");
        scanf("%d",&choix);
      }
    }
    choix = 2;
    while (choix != 0 && choix != 1) {
      printf("\nArrêter le programme ? (1 = Oui, 0 = Non) ");
      scanf("%d",&choix);
    }
  }
  return EXIT_SUCCESS;
}