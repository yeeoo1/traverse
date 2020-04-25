#include <stdio.h>
#define TAILLE_PLATEAU 10

typedef struct pion {
    int type; // 0:carré, 1:triangle, 2:losange, 3:rond
    int posX;
    int posY;
    int joueur; // 1 ou 2
    int id_pion; // unique id
} pion;

/* return the number of pion for this player for this line */
int GetNbPionOnLineForThisPlayer(int player, int line, struct pion* plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]) {
    int nbPion = 0;
    for (unsigned int i = 0 ; i < 10; i++){
        if (plateau[line][i] != NULL) {
            if (plateau[line][i]->joueur == player) nbPion++;
        }
    }
    return nbPion;
}

/* Draw plateau and pion */
void DrawPlateau(struct pion* plateau[TAILLE_PLATEAU][TAILLE_PLATEAU]){
    printf("     0      1      2      3      4      5      6      7      8      9   \n");
    for (unsigned x = 0; x < 10; x ++){
        printf("  |-----||-----||-----||-----||-----||-----||-----||-----||-----||-----|\n");
        printf("%d ", x);
        for (unsigned y = 0; y < 10; y++){
            if (plateau[x][y] != NULL){
                if (plateau[x][y]->type == 0) { printf("|J%d_C%d|", plateau[x][y]->joueur, plateau[x][y]->id_pion); } // Si pion carré
                if (plateau[x][y]->type == 1) { printf("|J%d_T%d|", plateau[x][y]->joueur, plateau[x][y]->id_pion); } // Si pion triangle
                if (plateau[x][y]->type == 2) { printf("|J%d_L%d|", plateau[x][y]->joueur, plateau[x][y]->id_pion); } // Si pion losange
                if (plateau[x][y]->type == 3) { printf("|J%d_R%d|", plateau[x][y]->joueur, plateau[x][y]->id_pion); } // Si pion rond
            } else {
                printf("|     |");
            }
        }
        printf("\n");
    }
    printf("  |-----||-----||-----||-----||-----||-----||-----||-----||-----||-----|\n");
}

/* main function */
int main(int argc, char *argv[]){

    /* all variables */
    struct pion* plateau[10][10]; /* create plateau */
    unsigned int tours = 0; /* current tours */
    unsigned int current_player = 1; /* 1:joueur1, 2:joueur2 */
    unsigned int stop = 0; /* 0:continue, 1:stop the game */
    unsigned int id_selected_pion = 0;
    int winner = 0; /* -1:match null, 1:joueur1 gagne, 2:joueur2 gagne*/

    /* create player 1 */
    struct pion joueur1[8] = {
        {0, 0, 1, 1, 0},
        {1, 0, 2, 1, 1},
        {2, 0, 3, 1, 2},
        {3, 0, 4, 1, 3},
        {3, 0, 5, 1, 4},
        {2, 0, 6, 1, 5},
        {1, 0, 7, 1, 6},
        {0, 0, 8, 1, 7}
    };

    /* create player 2 */
    struct pion joueur2[8] = {
        {0, 9, 1, 2, 0},
        {1, 9, 2, 2, 1},
        {2, 9, 3, 2, 2},
        {3, 9, 4, 2, 3},
        {3, 9, 5, 2, 4},
        {2, 9, 6, 2, 5},
        {1, 9, 7, 2, 6},
        {0, 9, 8, 2, 7}
    };

    /* efface tous les pions du plateau */
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            plateau[x][y] = NULL;
        }
    }

    /* positionne les pions du joueur 1 sur le plateau */
    for (int i = 0; i < (sizeof(joueur1) / sizeof(struct pion)); i++){
        plateau[joueur1[i].posX][joueur1[i].posY] = &joueur1[i];
    }

    /* positionne les pions du joueur 2 sur le plateau */
    for (int i = 0; i < (sizeof(joueur2) / sizeof(struct pion)); i++){
        plateau[joueur2[i].posX][joueur2[i].posY] = &joueur2[i];
    }


    /* boucle principale */
    while (stop == 0) {

        /***** DESSINE LE PLATEAU *****/
        DrawPlateau(plateau);

        /* nouveau tour */
        tours++;
        printf("C'est le tour numero: %d\n", tours);


        /****** CONDITIONS DE FIN DE MATCH *****/
        /* les pions sont en face */

        /* si au 31eme tour, il y a un pion sur la ligne de départ */
        if (tours == 31){
            int nbPionJ1 = GetNbPionOnLineForThisPlayer(1, 0, plateau);
            int nbPionJ2 = GetNbPionOnLineForThisPlayer(2, 9, plateau);
            if ((nbPionJ1 > 0) & (nbPionJ2 == 0)){ /* le joueur 1 a un pion sur sa ligne de départ */
                winner = 2;
                stop = 1;
                continue; /* force le passage au tour suivant */
            } else if ((nbPionJ1 == 0) & (nbPionJ1 > 0)) { /* le joueur 1 a un pion sur sa ligne de départ */
                winner = 1;
                stop = 1;
                continue;
            } else if ((nbPionJ1 > 0) & (nbPionJ2 > 0)) { /* les deux joueurs on un pion sur leur ligne de départ */
                winner = -1;
                stop = 1;
                continue;
            }
        }

        /* demande une action au joueur */
        printf("C'est au joueur %d de jouer !\n", current_player);
        do{
            printf("Selectionnez le pion à déplacer: ");
            scanf("%d", &id_selected_pion);
        } while ((id_selected_pion < 0) || (id_selected_pion > 7));// tant que le joueur n'a pas sélectionné un pion entre 0 et 8


        /***** CHANGEMENT DE JOUEUR *****/
        if (current_player == 1) current_player = 2;
        else current_player = 1;

    }


    /* affiche le résultat */
    if (winner == -1) {
        printf("Draw...\n");
    } else {
        printf("Congratulation, the player %d win !\n", winner);
    }


    /* fin */
    printf("Bye!\n");
    return 0;
}
