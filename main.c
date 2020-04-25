#include <stdio.h>

typedef struct pion {
    int type; // 0:carré, 1:triangle, 2:losange, 3:rond
    int posX; // 0 to 9
    int posY; // 0 to 9
    int joueur; // O or 1
    int nb_pion; // numéro du pion
};

int main(int argc, char *argv[]){

    /* create plateau */
    struct pion* plateau[10][10];

    /* create player */
    struct pion joueur1[8] = {
        {0, 0, 1, 0, 0},
        {1, 0, 2, 0, 1},
        {2, 0, 3, 0, 2},
        {3, 0, 4, 0, 3},
        {3, 0, 5, 0, 4},
        {2, 0, 6, 0, 5},
        {1, 0, 7, 0, 6},
        {0, 0, 8, 0, 7}
    };

    struct pion joueur2[8] = {
        {0, 9, 1, 1, 0},
        {1, 9, 2, 1, 1},
        {2, 9, 3, 1, 2},
        {3, 9, 4, 1, 3},
        {3, 9, 5, 1, 4},
        {2, 9, 6, 1, 5},
        {1, 9, 7, 1, 6},
        {0, 9, 8, 1, 7}
    };

    // efface toutes les cases du plateau
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            plateau[x][y] = NULL;
        }
    }

    // positionne les pions des joueurs sur le plateau
    for (int i = 0; i < (sizeof(joueur1) / sizeof(struct pion)); i++){
        plateau[joueur1[i].posX][joueur1[i].posY] = &joueur1[i];
    }
    for (int i = 0; i < (sizeof(joueur2) / sizeof(struct pion)); i++){
        plateau[joueur2[i].posX][joueur2[i].posY] = &joueur2[i];
    }

    unsigned int tour_joueur = 0; // 0 = joueur1, 1 = joueur2
    unsigned int pion_a_deplacer = 0;
    int gagne = 0; // 0 = la partie continue, 1 = partie terminée;

    /* boucle principale */
    do {

        /* les pions sont en face */


        /* si au 30eme tour, il y a un pion sur la ligne de départ */


        /* dessine le plateau */
        printf("     0      1      2      3      4      5      6      7      8      9   \n");
        for (unsigned x = 0; x < 10; x ++){
            printf("  |-----||-----||-----||-----||-----||-----||-----||-----||-----||-----|\n");
            printf("%d ", x);
            for (unsigned y = 0; y < 10; y++){
                if (plateau[x][y] != NULL){
                    if (plateau[x][y]->type == 0) { printf("|J%d_C%d|", plateau[x][y]->joueur, plateau[x][y]->nb_pion); } // Si pion carré
                    if (plateau[x][y]->type == 1) { printf("|J%d_T%d|", plateau[x][y]->joueur, plateau[x][y]->nb_pion); } // Si pion triangle
                    if (plateau[x][y]->type == 2) { printf("|J%d_L%d|", plateau[x][y]->joueur, plateau[x][y]->nb_pion); } // Si pion losange
                    if (plateau[x][y]->type == 3) { printf("|J%d_R%d|", plateau[x][y]->joueur, plateau[x][y]->nb_pion); } // Si pion rond
                } else {
                    printf("|     |");
                }
            }
            printf("\n");
        }
        printf("  |-----||-----||-----||-----||-----||-----||-----||-----||-----||-----|\n");


        /* demande une action au joueur */
        printf("C'est au tour du joueur : %d\n", tour_joueur);
        do{
            printf("Selectionnez le pion à déplacer: ");
            scanf("%d", &pion_a_deplacer);
        } while ((pion_a_deplacer < 0) || (pion_a_deplacer > 7));// tant que le joueur n'a pas sélectionné un pion entre 0 et 8


        /* changement de joueur */
        if (tour_joueur == 0) tour_joueur = 1;
        else tour_joueur = 0;

    } while (gagne != 1);

    return 0;
}