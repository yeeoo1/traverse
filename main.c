#include <stdio.h>
#include <math.h>

typedef struct pion {
    int type; // 0:carré, 1:triangle, 2:losange, 3:rond
    int posX; // 0 to 9
    int posY; // 0 to 9
    int joueur; // O or 1
    int nb_pion; // numéro du pion
};

struct pion deplacement_triangle(struct pion joueur[8],struct pion joueuradverse[8],int pion);
struct pion pion_a_deplacer(struct pion joueur[8],struct pion joueuradverse[8],int pion);
struct pion deplacement_carre(struct pion joueur[8],struct pion joueuradverse[8],int pion);
struct pion deplacement_cercle(struct pion joueur[8],struct pion joueuradverse[8],int pion);
struct pion deplacement_losange(struct pion joueur[8],struct pion joueuradverse[8],int pion);
int test_saut(struct pion joueuradverse[8],int posX,int posY,int deplacement_X,int deplacement_Y);

int test_pion_saut(struct pion joueur[8],struct pion joueuradverse[8],int pion,int deplacement_X,int deplacement_Y){
    int impossible=0;
    for(int i=0;i<8;i++){
        if((joueuradverse[i].posX==joueur[pion].posX+deplacement_X) && (joueuradverse[i].posY==joueur[pion].posY+deplacement_Y)) {
            impossible=1;
        } else if((joueur[i].posX==joueur[pion].posX+deplacement_X) && (joueur[i].posY==joueur[pion].posY+deplacement_Y)) {
            impossible=1;
        }
    }
    return(impossible);
}

int test_tour_supplementaire(struct pion joueuradverse[8],struct pion pion){
    int tour_bonus=0;
    for(int i=0;i<8;i++){
        switch(pion.type){
            case 0:
                if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY)) {
                    tour_bonus++;
                }
                if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY)) {
                    tour_bonus++;
                }
                if((joueuradverse[i].posX==pion.posX) && (joueuradverse[i].posY==pion.posY+1)) {
                    tour_bonus++;
                }
                if((joueuradverse[i].posX==pion.posX) && (joueuradverse[i].posY==pion.posY-1)) {
                    tour_bonus++;
                }
                break;
            case 1:
                if(pion.joueur==0){
                    if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY+1)) {
                        tour_bonus++;
                    } else if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY-1)) {
                        tour_bonus++;
                    } else if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY)) {
                        tour_bonus++;
                    }
                } else {
                    if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY+1)) {
                        tour_bonus++;
                    } else if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY-1)) {
                        tour_bonus++;
                    } else if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY)) {
                        tour_bonus++;
                    }
                }
                break;
            case 2:
                if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY-1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY-1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY+1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY+1)) {
                    tour_bonus++;
                }
                break;
            case 3:
                if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX) && (joueuradverse[i].posY==pion.posY+1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX) && (joueuradverse[i].posY==pion.posY-1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY-1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX-1) && (joueuradverse[i].posY==pion.posY-1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY+1)) {
                    tour_bonus++;
                } else if((joueuradverse[i].posX==pion.posX+1) && (joueuradverse[i].posY==pion.posY-1)) {
                    tour_bonus++;
                }
                break;
            default:
                break;
        }
    }
    printf("%d\n",tour_bonus);
    if(tour_bonus<2) {
        tour_bonus=0;
    } else {
        tour_bonus=1;
    }
    printf("%d\n",tour_bonus);
    return(tour_bonus);
}

struct pion deplacement_carre(struct pion joueur[8],struct pion joueuradverse[8],int pion) {
    int encore_une_variable_pour_pas_grand_chose=0;
    int deplacement_choisi;
    int deplacement_X=0;
    int deplacement_Y=0;
    int impossible=0;
    int pion_adverse=0;
    printf("Quel deplacement voulez vous faire?\n");
    printf("1-Vers le bas    2-Vers le haut\n3-A gauche   4-A droite\n");
    scanf("%d",&deplacement_choisi);
    switch(deplacement_choisi) {
        case 1:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY)) {
                    pion_adverse=1;
                }
            }
            if(pion_adverse==1){
                deplacement_X=2;
                deplacement_Y=0;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX+=2;

                }
            } else {
                joueur[pion].posX+=1;
            }
            break;
        case 2:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX-1) && (joueur[i].posY==joueur[pion].posY)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY)) {
                    pion_adverse=1;
                }
            }
            if(pion_adverse==1){
                deplacement_X=-2;
                deplacement_Y=0;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX-=2;
                }
            } else {
                joueur[pion].posX-=1;
            }
            break;
        case 3:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX) && (joueur[i].posY==joueur[pion].posY-1)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY-1<0)){
                printf("Ce deplacement est impossible\n");

                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=0;
                deplacement_Y=-2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posY-=2;
                }
            } else {
                joueur[pion].posY-=1;
            }
            break;
            case 4:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX) && (joueur[i].posY==joueur[pion].posY+1)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX) && (joueuradverse[i].posY==joueur[pion].posY+1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY+1<0)){
                printf("Ce deplacement est impossible\n");
                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=0;
                deplacement_Y=2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posY+=2;
                }
            } else {
                joueur[pion].posY+=1;
            }
            break;
        default:
            printf("Ce deplacement n'existe pas!\n");
            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            break;
        }

    return(joueur[pion]);
}

struct pion deplacement_losange(struct pion joueur[8],struct pion joueuradverse[8],int pion){
    int encore_une_variable_pour_pas_grand_chose=0;
    int test_bordure;
    int impossible=0;
    int deplacement_X;
    int deplacement_Y;
    int deplacement_choisi;
    int pion_adverse=0;
    printf("Quel deplacement voulez vous faire?\n");
    printf("1-En haut a gauche    2-En haut a droite\n3-En bas a gauche   4-En bas a droite\n");
    scanf("%d",&deplacement_choisi);
    switch(deplacement_choisi) {
        case 1:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX-1) && (joueur[i].posY==joueur[pion].posY-1)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=0;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY-1<1)){
                printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=-2;
                deplacement_Y=-2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    deplacement_X=2;
                    deplacement_Y=-2;
                    impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                    if(impossible==1){
                        printf("Deplacement impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        break;
                    } else {
                        joueur[pion].posX-=2;
                        joueur[pion].posY-=2;
                        if(joueur[pion].posY<1){
                            test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                            if(test_bordure==1){
                                break;
                            } else {
                                joueur[pion].posX+=2;
                                joueur[pion].posY+=2;
                                printf("Deplacement impossible\n");
                                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                                break;
                            }
                        }
                    }
                }
            } else {
                    joueur[pion].posX-=1;
                    joueur[pion].posY-=1;
                }
                break;
        case 2:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX-1) && (joueur[i].posY==joueur[pion].posY+1)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=0;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY+1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY+1>8)){
                printf("Ce deplacement est impossible\n");
                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse!=0){
                deplacement_X=-2;
                deplacement_Y=2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX-=2;
                    joueur[pion].posY=2;
                    if(joueur[pion].posY<1){
                        test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                        if(test_bordure==1){
                            break;
                        } else {
                            joueur[pion].posX+=2;
                            joueur[pion].posY-=2;
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        }
                    }
                }
            } else {
                joueur[pion].posX-=1;
                joueur[pion].posY+=1;
            }
            break;
        case 3:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY-1)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY-1<1)){
                printf("Ce deplacement est impossible\n");
                printf("%d",joueur[pion].posX);
                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=2;
                deplacement_Y=-2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX+=2;
                    joueur[pion].posY-=2;
                    if(joueur[pion].posY<1){
                        test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                        if(test_bordure==1){
                            break;
                        } else {
                            joueur[pion].posX-=2;
                            joueur[pion].posY+=2;
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        }
                    }
                }
            } else {
                printf("%d",joueur[pion].posX);
                joueur[pion].posX+=1;
                joueur[pion].posY-=1;
            }
            break;
        case 4:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY+1)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY+1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY+1>8)){
                printf("Ce deplacement est impossible\n");

                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if (pion_adverse==1){
                deplacement_X=2;
                deplacement_Y=-2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX+=2;
                    joueur[pion].posY+=2;
                    if(joueur[pion].posY<1){
                        test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                        if(test_bordure==1){
                            break;
                        } else {
                            joueur[pion].posX-=2;
                            joueur[pion].posY-=2;
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        }
                    }
                }
            } else {
                joueur[pion].posX+=1;
                joueur[pion].posY+=1;
            }
            break;
        default:
            printf("Ce deplacement n'existe pas!\n");
            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            break;
    }

    return(joueur[pion]);
}

struct pion deplacement_cercle(struct pion joueur[8],struct pion joueuradverse[8],int pion){
    int test_bordure;
    int encore_une_variable_pour_pas_grand_chose=0;
    int impossible=0;
    int deplacement_X;
    int deplacement_Y;
    int deplacement_choisi;
    int pion_adverse=0;
    printf("Quel deplacement voulez vous faire?\n");
    printf("1-Vers le bas    2-Vers le haut\n3-A gauche   4-A droite\n");
    printf("5-En haut a gauche    6-En haut a droite\n7-En bas a gauche   8-En bas a droite\n");
    scanf("%d",&deplacement_choisi);
    switch(deplacement_choisi) {
        case 1:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY)) {
                    pion_adverse=1;
                }
            }
            if(pion_adverse==1){
                deplacement_X=2;
                deplacement_Y=0;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX+=2;
                }
            } else {
                joueur[pion].posX+=1;
            }
            break;
        case 2:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX-1) && (joueur[i].posY==joueur[pion].posY)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY)) {
                    pion_adverse=1;
                }
            }
            if(pion_adverse==1){
                deplacement_X=-2;
                deplacement_Y=0;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX-=2;
                }
            } else {
                joueur[pion].posX-=1;
            }
            break;
        case 3:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX) && (joueur[i].posY==joueur[pion].posY-1)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY-1<0)){
                printf("Ce deplacement est impossible\n");

                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=0;
                deplacement_Y=-2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posY-=2;
                }
            } else {
                joueur[pion].posY-=1;
            }
            break;
        case 4:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX) && (joueur[i].posY==joueur[pion].posY+1)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX) && (joueuradverse[i].posY==joueur[pion].posY+1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posY+1<0)){
                printf("Ce deplacement est impossible\n");

                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=0;
                deplacement_Y=2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posY+=2;
                }
            } else {
                joueur[pion].posY+=1;
            }
            break;
        case 5:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX-1) && (joueur[i].posY==joueur[pion].posY-1)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posX-1<1) || (joueur[pion].posY-1<1)){
                printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                } else if(pion_adverse==1){
                    deplacement_X=2;
                deplacement_Y=-2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX-=2;
                    joueur[pion].posY-=2;
                    if(joueur[pion].posY<1){
                        test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                        if(test_bordure==1){
                            break;
                        } else {
                            joueur[pion].posX+=2;
                            joueur[pion].posY+=2;
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        }
                    }
                }
                }else {
                    joueur[pion].posX-=1;
                    joueur[pion].posY-=1;
                }
                break;
        case 6:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX-1) && (joueur[i].posY==joueur[pion].posY+1)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posX-1<1) || (joueur[pion].posY+1>8)){
                printf("Ce deplacement est impossible\n");
                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=-2;
                deplacement_Y=2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX-=2;
                    joueur[pion].posY+=2;
                    if(joueur[pion].posY<1){
                        test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                        if(test_bordure==1){
                            break;
                        } else {
                            joueur[pion].posX+=2;
                            joueur[pion].posY-=2;
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        }
                    }
                }
            } else {
                joueur[pion].posX-=1;
                joueur[pion].posY+=1;
            }
            break;
        case 7:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY-1)) {
                    if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==-1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posX+1>8) || (joueur[pion].posY-1<1)){
                printf("Ce deplacement est impossible\n");
                printf("%d",joueur[pion].posX);
                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if(pion_adverse==1){
                deplacement_X=2;
                deplacement_Y=-2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX+=2;
                    joueur[pion].posY-=2;
                    if(joueur[pion].posY<1){
                        test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                        if(test_bordure==1){
                            break;
                        } else {
                            joueur[pion].posX-=2;
                            joueur[pion].posY+=2;
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        }
                    }
                }
            } else {
                printf("%d",joueur[pion].posX);
                joueur[pion].posX+=1;
                joueur[pion].posY-=1;
            }
            break;
        case 8:
            for(int i=0;i<8;i++){
                if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY+1)) {
                    if(i!=pion){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    encore_une_variable_pour_pas_grand_chose=1;
                    break;
                    }
                }
            }
            if(encore_une_variable_pour_pas_grand_chose==1){
                break;
            }
            for(int i=0;i<8;i++){
                if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY+1)) {
                    pion_adverse=1;
                }
            }
            if((joueur[pion].posX+1>8) || (joueur[pion].posY+1>8)){
                printf("Ce deplacement est impossible\n");

                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            } else if (pion_adverse==1){
                deplacement_X=2;
                deplacement_Y=2;
                impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                if(impossible==1){
                    printf("Deplacement impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else {
                    joueur[pion].posX+=2;
                    joueur[pion].posY+=2;
                    if(joueur[pion].posY<1){
                        test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                        if(test_bordure==1){
                            break;
                        } else {
                            joueur[pion].posX-=2;
                            joueur[pion].posY-=2;
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        }
                    }
                }
            } else {
                joueur[pion].posX+=1;
                joueur[pion].posY+=1;
            }
            break;
        default:
            printf("Ce deplacement n'existe pas!\n");
            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            break;
    }

    return(joueur[pion]);
}

struct pion deplacement_triangle(struct pion joueur[8],struct pion joueuradverse[8],int pion){
    int test_bordure;
    int encore_une_variable_pour_pas_grand_chose=0;
    int impossible=0;
    int deplacement_X;
    int deplacement_Y;
    int deplacement_choisi;
    int pion_adverse=0;
    deplacement_choisi=0;
    if(joueur[pion].joueur==0){
        printf("Quel deplacement voulez vous faire?\n");
        printf("1-En bas a gauche    2-En bas a droite   3-En haut\n");
        scanf("%d",&deplacement_choisi);
        switch(deplacement_choisi) {
            case 1:
                for(int i=0;i<8;i++){
                    if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY-1)) {
                       if(i!=pion){
                            printf("Ce deplacement est impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            encore_une_variable_pour_pas_grand_chose=1;
                            break;
                        }
                    }
                }if(encore_une_variable_pour_pas_grand_chose==1){
                    break;
                }
                for(int i=0;i<8;i++){
                    if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                        pion_adverse=1;
                    }
                }
                if((joueur[pion].posX+1>8) || (joueur[pion].posY-1<1)){
                    printf("Ce deplacement est impossible\n");
                    printf("%d",joueur[pion].posX);
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else if(pion_adverse==1){
                    deplacement_X=2;
                    deplacement_Y=-2;
                    impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                    if(impossible==1){
                        printf("Deplacement impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        break;
                    } else {
                        joueur[pion].posX+=2;
                        joueur[pion].posY-=2;
                        if(joueur[pion].posY<1){
                            test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                            if(test_bordure==1){
                                break;
                            } else {
                                joueur[pion].posX-=2;
                                joueur[pion].posY+=2;
                                printf("Deplacement impossible\n");
                                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                                break;
                            }
                        }
                    }
                } else {
                    printf("%d",joueur[pion].posX);
                    joueur[pion].posX+=1;
                    joueur[pion].posY-=1;
                }
                break;
            case 2:
                for(int i=0;i<8;i++){
                    if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY+1)) {
                       if(i!=pion){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                        }
                    }
                }
                if(encore_une_variable_pour_pas_grand_chose==1){
                    break;
                }
                for(int i=0;i<8;i++){
                    if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY+1)) {
                        pion_adverse=1;
                    }
                }
                if((joueur[pion].posX+1>8) || (joueur[pion].posY+1>8)){
                    printf("Ce deplacement est impossible\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                } else if (pion_adverse==1){
                    deplacement_X=2;
                    deplacement_Y=2;
                    impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                    if(impossible==1){
                        printf("Deplacement impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        break;
                    } else {
                        joueur[pion].posX+=2;
                        joueur[pion].posY+=2;
                        if(joueur[pion].posY<1){
                            test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                            if(test_bordure==1){
                                break;
                            } else {
                                joueur[pion].posX-=2;
                                joueur[pion].posY-=2;
                                printf("Deplacement impossible\n");
                                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                                break;
                            }
                        }
                    }
                } else {
                    joueur[pion].posX+=1;
                    joueur[pion].posY+=1;
                }
                break;
            case 3:
                for(int i=0;i<8;i++){
                    if((joueur[i].posX==joueur[pion].posX-1)) {
                       if(i!=pion){
                        printf("Ce deplacement est impossibleee\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        encore_une_variable_pour_pas_grand_chose=1;
                        break;
                        }
                    }
                }
                if(encore_une_variable_pour_pas_grand_chose==1){
                    break;
                }
                for(int i=0;i<8;i++){
                    if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY)) {
                        pion_adverse=1;
                    }
                }
                if((joueur[pion].posX-1<0)){
                    printf("Ce deplacement est impossibleeeeeee\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
                } else if(pion_adverse==1) {
                    deplacement_X=-2;
                    deplacement_Y=0;
                    impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                    if(impossible==1){
                        printf("Deplacement impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        break;
                    } else {
                        joueur[pion].posX-=2;
                    }
                } else {
                    joueur[pion].posX-=1;
                }
                break;
            default:
                printf("Ce deplacement n'existe pas!\n");
                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                break;
        }
    } else {
            printf("Quel deplacement voulez vous faire?\n");
            printf("1-En haut a gauche    2-En haut a droite   3-En haut\n");
            scanf("%d",&deplacement_choisi);
            switch(deplacement_choisi) {
                case 1:
                    for(int i=0;i<8;i++){
                        if((joueur[i].posX==joueur[pion].posX-1) && (joueur[i].posY==joueur[pion].posY-1)) {
                            if(i!=pion){
                                printf("Ce deplacement est impossible\n");
                                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                                encore_une_variable_pour_pas_grand_chose=1;
                                break;
                            }
                        }
                    }
                    if(encore_une_variable_pour_pas_grand_chose==1){
                        break;
                    }
                    for(int i=0;i<8;i++){
                        if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY-1)) {
                            pion_adverse=1;
                        }
                    }
                    if((joueur[pion].posX-1<1) || (joueur[pion].posY-1<1)){
                        printf("Ce deplacement est impossible\n");
                        printf("%d",joueur[pion].posX);
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    } else if(pion_adverse==1){
                        deplacement_X=-2;
                        deplacement_Y=-2;
                        impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                        if(impossible==1){
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        } else {
                            joueur[pion].posX-=2;
                            joueur[pion].posY-=2;
                            if(joueur[pion].posY<1){
                                test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                                if(test_bordure==1){
                                    break;
                                } else {
                                    joueur[pion].posX+=2;
                                    joueur[pion].posY+=2;
                                    printf("Deplacement impossible\n");
                                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                                    break;
                                }
                            }
                        }
                    } else {
                        printf("%d",joueur[pion].posX);
                        joueur[pion].posX-=1;
                        joueur[pion].posY-=1;
                    }
                    break;
                case 2:
                    for(int i=0;i<8;i++){
                        if((joueur[i].posX==joueur[pion].posX+1) && (joueur[i].posY==joueur[pion].posY+1)) {
                            if(i!=pion){
                            printf("Ce deplacement est impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            encore_une_variable_pour_pas_grand_chose=1;
                            break;
                            }
                        }
                    }
                    if(encore_une_variable_pour_pas_grand_chose==1){
                        break;
                    }
                    for(int i=0;i<8;i++){
                        if((joueuradverse[i].posX==joueur[pion].posX-1) && (joueuradverse[i].posY==joueur[pion].posY+1)) {
                            pion_adverse=1;
                        }
                    }
                    if((joueur[pion].posX-1>8) || (joueur[pion].posY+1>8)){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    } else if (pion_adverse==1){
                        deplacement_X=-2;
                        deplacement_Y=2;
                        impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                        if(impossible==1){
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        } else {
                            joueur[pion].posX-=2;
                            joueur[pion].posY+=2;
                            if(joueur[pion].posY<1){
                                test_bordure=test_tour_supplementaire(joueuradverse,joueur[pion]);
                                if(test_bordure==1){
                                    break;
                                } else {
                                    joueur[pion].posX+=2;
                                    joueur[pion].posY-=2;
                                    printf("Deplacement impossible\n");
                                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                                    break;
                                }
                            }
                        }
                    } else {
                        joueur[pion].posX-=1;
                        joueur[pion].posY+=1;
                    }
                    break;
                case 3:
                    for(int i=0;i<8;i++){
                        if((joueur[i].posX==joueur[pion].posX+1)) {
                            if(i!=pion){
                                printf("Ce deplacement est impossible\n");
                                joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                                encore_une_variable_pour_pas_grand_chose=1;
                                break;
                            }
                        }
                    }
                    if(encore_une_variable_pour_pas_grand_chose==1){
                        break;
                    }
                    for(int i=0;i<8;i++){
                        if((joueuradverse[i].posX==joueur[pion].posX+1) && (joueuradverse[i].posY==joueur[pion].posY)) {
                            pion_adverse=1;
                        }
                    }
                    if((joueur[pion].posX+1>8)){
                        printf("Ce deplacement est impossible\n");
                        joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                        break;
                    } else if (pion_adverse==1){
                        deplacement_X=-2;
                        deplacement_Y=0;
                        impossible=test_pion_saut(joueur,joueuradverse,pion,deplacement_X,deplacement_Y);
                        if(impossible==1){
                            printf("Deplacement impossible\n");
                            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                            break;
                        } else {
                            joueur[pion].posX-=2;
                        }
                    } else {
                        joueur[pion].posX-=1;
                    }
                    break;
                default:
                    printf("Ce deplacement n'existe pas!\n");
                    joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
                    break;
            }
        }
        return(joueur[pion]);
}

struct pion pion_a_deplacer(struct pion joueur[8],struct pion joueuradverse[8],int pion){
    while(pion>7 || pion<0){
        printf("Rejouez votre tour\nChoisissez un pion\n");
        scanf("%d",&pion);
    }
    switch(pion) {
        case 0:
            joueur[pion]=deplacement_carre(joueur,joueuradverse,pion);
            break;
        case 1:
            joueur[pion]=deplacement_triangle(joueur,joueuradverse,pion);
            break;
        case 2:
            joueur[pion]=deplacement_losange(joueur,joueuradverse,pion);
            break;
        case 3:
            joueur[pion]=deplacement_cercle(joueur,joueuradverse,pion);
            break;
        case 4:
            joueur[pion]=deplacement_cercle(joueur,joueuradverse,pion);
            break;
        case 5:
            joueur[pion]=deplacement_losange(joueur,joueuradverse,pion);
            break;
        case 6:
            joueur[pion]=deplacement_triangle(joueur,joueuradverse,pion);
            break;
        case 7:
            joueur[pion]=deplacement_carre(joueur,joueuradverse,pion);
            break;
        default:
            pion=10;
            joueur[pion]=pion_a_deplacer(joueur,joueuradverse,pion);
            break;
    }
    return(joueur[pion]);
}

int main(int argc, char *argv[]){

    /* create plateau */
    struct pion* plateau[10][10];

    /* create player */
    struct pion joueur1[8] = {
        {0, 9, 1, 0, 0},
        {1, 9, 2, 0, 1},
        {2, 9, 3, 0, 2},
        {3, 9, 4, 0, 3},
        {3, 8, 4, 0, 4},
        {2, 9, 6, 0, 5},
        {1, 9, 7, 0, 6},
        {0, 9, 8, 0, 7}
    };

    struct pion joueur2[8] = {
        {0, 1, 1, 1, 0},
        {1, 1, 2, 1, 1},
        {2, 1, 3, 1, 2},
        {3, 1, 4, 1, 3},
        {3, 1, 5, 1, 4},
        {2, 1, 6, 1, 5},
        {1, 1, 7, 1, 6},
        {0, 1, 8, 1, 7}
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
    int preposX,preposY;
    int deplacement_X,deplacement_Y;
    int test_bordure=0;
    int tour_supplementaire,continuer;
    unsigned int tour_joueur = 1; // 1 = joueur1, 2 = joueur2
    unsigned int id_pion_a_deplacer = 0;
    int qui_a_gagne = 0; // 0 = la partie continue, 1 = joueur 1 gange ,2 = joueur 2 gagne , -1= match nul
    int nb_de_tours =0;
    int joueur1_tour30 = 0; // si = 0 le joueur 1 n'a plus de pion dans son camp si > 1 i ly a au moins 1 pion sur la ligne de depart
    int joueur2_tour30 = 0;//  si = 0 le joueur 2 n'a plus de pion dans son camp si > 1 i ly a au moins 1 pion sur la ligne de depart
    int pion_gagnant1 = 0;
    int pion_gagnant2 = 0;
    /* boucle principale */
    while(1) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                plateau[x][y] = NULL;
            }
        }
        for (int i = 0; i < (sizeof(joueur1) / sizeof(struct pion)); i++){
            plateau[joueur1[i].posX][joueur1[i].posY] = &joueur1[i];
        }
        for (int i = 0; i < (sizeof(joueur2) / sizeof(struct pion)); i++){
            plateau[joueur2[i].posX][joueur2[i].posY] = &joueur2[i];
        }

        pion_gagnant1=0;
        pion_gagnant2=0;
        id_pion_a_deplacer=0;
        if(tour_joueur==1){  //Annonce aux joueurs a quel tour ils sont
            nb_de_tours++;
            printf("Tour :%d\n",nb_de_tours);
        }
        /* les pions sont en face */
        for (int i=0;i<10;i++){
            if(plateau[0][i]!=NULL){
                if(plateau[0][i]->joueur == 1){ //Test si le joueur 2 a tous ses pions sur la ligne adverse
                        pion_gagnant2++;
                }
            }
            if(plateau[9][i]!=NULL){
                if(plateau[9][i]->joueur == 0){ //Test si le joueur 1 a tous ses pions sur la ligne adverse
                            pion_gagnant1++;
                }
            }
        }
        if(pion_gagnant1 == 8){
            qui_a_gagne=1;
        }
        if(pion_gagnant2 == 8){
            qui_a_gagne=2;
        }
        // break /* on sort de la boucle principale */

        /* si au 30eme tour, il y a un pion sur sa ligne de départ */
        /* on sort de la boucle principale */
        if (nb_de_tours==30){
            for (int i=0;i<10;i++){
                if(plateau[0][i]!=NULL){
                    if(plateau[0][i]->joueur == 0){ //Test si le joueur 1 a encore ses pions sur sa ligne de départ
                            joueur1_tour30++;
                    }
                }
                if(plateau[9][i]!=NULL){
                    if(plateau[9][i]->joueur == 1){ //Test si le joueur 2 a encore ses pions sur sa ligne de départ
                            joueur2_tour30++;
                    }
                }
            }
            if((joueur1_tour30 >= 1) && (joueur2_tour30 == 0) ){
                qui_a_gagne=2;

            } else if ((joueur2_tour30 >= 1) && (joueur1_tour30 == 0)){
                qui_a_gagne=1;
            } else if ((joueur1_tour30 >= 1) && (joueur2_tour30 >= 0)){
                qui_a_gagne=-1;
            }
        }
        // Test pour savoir si un joueur a gagné
        if(qui_a_gagne==1){
            break;
        } else if(qui_a_gagne==2) {
            break;
        } else if(qui_a_gagne==-1){
            break;
        }
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
            printf("Selectionnez le pion a deplacer: ");
            scanf("%d", &id_pion_a_deplacer);
        } while ((id_pion_a_deplacer < 0) || (id_pion_a_deplacer > 7));// tant que le joueur n'a pas sélectionné un pion entre 0 et 8
        //Déplacement du pion + On garde dans des variables la position du pion avant déplacement
        if(tour_joueur==1){
            preposX=joueur1[id_pion_a_deplacer].posX;
            preposY=joueur1[id_pion_a_deplacer].posY;
            joueur1[id_pion_a_deplacer]=pion_a_deplacer(joueur1,joueur2,id_pion_a_deplacer);
        } else {
            preposX=joueur2[id_pion_a_deplacer].posX;
            preposY=joueur2[id_pion_a_deplacer].posY;
            joueur2[id_pion_a_deplacer]=pion_a_deplacer(joueur2,joueur1,id_pion_a_deplacer);
        }
        // Test pour savoir si le joueur a un tour supplémentaire
        while(tour_joueur==1){
            if((abs(preposX-joueur1[id_pion_a_deplacer].posX)==2 || (abs(preposY-joueur1[id_pion_a_deplacer].posY)==2))){
                tour_supplementaire=0;
                for (int x = 0; x < 10; x++) {
                    for (int y = 0; y < 10; y++) {
                        plateau[x][y] = NULL;
                    }
                }
                for (int i = 0; i < (sizeof(joueur1) / sizeof(struct pion)); i++){
                    plateau[joueur1[i].posX][joueur1[i].posY] = &joueur1[i];
                }
                for (int i = 0; i < (sizeof(joueur2) / sizeof(struct pion)); i++){
                    plateau[joueur2[i].posX][joueur2[i].posY] = &joueur2[i];
                }
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
                tour_supplementaire=test_tour_supplementaire(joueur2,joueur1[id_pion_a_deplacer]);
                if(tour_supplementaire==1){
                    printf("Voulez vous continuer ?\n1-Oui   2-Non\n");
                    scanf("%d",&continuer);
                        if(continuer!=1){
                            break;
                        }
                } else {
                    break;
                }
                preposX=joueur1[id_pion_a_deplacer].posX;
                preposY=joueur1[id_pion_a_deplacer].posY;
                joueur1[id_pion_a_deplacer]=pion_a_deplacer(joueur1,joueur2,id_pion_a_deplacer);
            } else {
                break;
            }
        }
        while(tour_joueur==2){
            if(((abs(preposX-joueur2[id_pion_a_deplacer].posX)==2) || (abs(preposY-joueur2[id_pion_a_deplacer].posY)==2))){
                tour_supplementaire=0;
                for (int x = 0; x < 10; x++) {
                    for (int y = 0; y < 10; y++) {
                        plateau[x][y] = NULL;
                    }
                }
                for (int i = 0; i < (sizeof(joueur1) / sizeof(struct pion)); i++){
                    plateau[joueur1[i].posX][joueur1[i].posY] = &joueur1[i];
                }
                for (int i = 0; i < (sizeof(joueur2) / sizeof(struct pion)); i++){
                    plateau[joueur2[i].posX][joueur2[i].posY] = &joueur2[i];
                }
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
                tour_supplementaire=test_tour_supplementaire(joueur1,joueur2[id_pion_a_deplacer]);
                if(tour_supplementaire==1){
                    printf("Voulez vous continuer ?\n1-Oui   2-Non\n");
                    scanf("%d",&continuer);
                    if(continuer!=1){
                            break;
                    }
                } else {
                    break;
                }
                preposX=joueur2[id_pion_a_deplacer].posX;
                preposY=joueur2[id_pion_a_deplacer].posY;
                joueur2[id_pion_a_deplacer]=pion_a_deplacer(joueur2,joueur1,id_pion_a_deplacer);
            } else {
                break;
            }
        }
        /* changement de joueur */
        if (tour_joueur == 1) {tour_joueur = 2;}
        else {tour_joueur = 1;}

    }
    printf("Congratulation, the player %d win !\n", qui_a_gagne);
    printf("Bye!\n");
    return 0;
}
