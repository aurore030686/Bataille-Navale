#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define LIGNE   18
#define COLONNE 24

#define JOUEUR1 0
#define JOUEUR2 1
#define CORVETTE 1
#define DESTROYER 3
#define CROISEUR 4
#define PORTEAVION 6

#define TOUCHE 9 // marque une case touchée (qu'il y ait navire ou non)



int pvJoueur1 = 1*CORVETTE + 2*DESTROYER + 2*CROISEUR + 1*PORTEAVION;
int pvJoueur2 = 1*CORVETTE + 2*DESTROYER + 2*CROISEUR + 1*PORTEAVION;
int map[LIGNE][COLONNE][2] = {0};

void Color(int couleurDuTexte,int couleurDeFond){
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
void affichemap(int map[LIGNE][COLONNE][2],int joueur, int cacherNavires){
    int i=0;
    int j=0;

    for (i=0;i<LIGNE;i++){
        for(j=0;j<COLONNE;j++){
            if(!cacherNavires) {
                switch(map[i][j][joueur]) {
                    case TOUCHE: case CORVETTE: case DESTROYER: case CROISEUR: case PORTEAVION:
                        Color(7,0);
                        break;

                    default:
                        Color(9,9);
                        break;
                }
            }
            else {
                switch(map[i][j][joueur]) {
                    case TOUCHE:
                        Color(7,0);
                        break;

                    default:
                        Color(9,9);
                        break;
                }
            }
            printf("%2d",map[i][j][joueur]);
        }
    printf("\n");
    }
    Color(7, 0);
}
void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
int doRand(int startVal, int endVal){
    waitFor(0.05);
    srand(time(NULL)*rand());
    if(startVal == 0 && endVal == 1){
        return rand() % 2;
    }else{
        return (rand() % ((endVal - startVal +1)) + startVal);
    }
}

void placementbateaux(int map[LIGNE][COLONNE][2], int joueur,int taillebateau){
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;

    x = doRand(0,LIGNE-1);
    y = doRand(0,COLONNE-1);

     for (i=0;i<taillebateau;i++){

         if (map[x+i][y][joueur]==0 && map[x+i][y][joueur]<LIGNE && map[x+i][y][joueur]>=0){
         map[x+i][y][joueur]=taillebateau;
         }else if (map[x][y+i][joueur]==0 && map[x][y+i][joueur]<COLONNE && map[x][y+i][joueur]>=0){
         map[x][y+i][joueur]=taillebateau;
         }
     }
}

int testsuperposition(int map[LIGNE][COLONNE][2],int joueur, int taillebateau){
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;

    x = doRand(0,LIGNE-1);
    y = doRand(0,COLONNE-1);

    switch(map[LIGNE][COLONNE][2]){
        for (i=0;i<taillebateau;i++){
            case 1: map[x+i][y][joueur]!=0;break;
            case 2: map[x][y+i][joueur]!=0;break;
            case 3: map[x-i][y][joueur]!=0;break;
            case 4: map[x][y-i][joueur]!=0;break;
        }
    }
}

int attaque(int map[LIGNE][COLONNE][2],int attaquant,int defenseur,int tirX, int tirY){
    // On s'assure que les coordonnées où on attaque sont bien définies.
    if(tirX<0||tirX>=LIGNE || tirY<0 || tirY>=COLONNE){
        return 0;  // je defini x et y dans ma map
    }

    // On s'assure que les deux joueurs tirent JOUEUR1 et JOUEUR2
    int ok = (attaquant==JOUEUR1 && defenseur==JOUEUR2) || (attaquant==JOUEUR2 && defenseur==JOUEUR1);
    if(!ok) {
        return 0;
    }

    switch(map[tirX][tirY][defenseur]) {
        case CORVETTE: case DESTROYER: case CROISEUR: case PORTEAVION:
            map[tirX][tirY][defenseur] = TOUCHE;
            switch(defenseur) {
                case JOUEUR1: pvJoueur1--; break;
                case JOUEUR2: pvJoueur2--; break;
            }
            return 1; // OK

        case TOUCHE:
            return 0; // KO

        default:
            map[tirX][tirY][defenseur] = TOUCHE;
            return 0;
    }

    return 0; // KO
}

void afficherStats(int joueur)
{
    if(joueur!=JOUEUR1 && joueur!=JOUEUR2) {
        return;
    }

    printf("Joueur %d\n", joueur+1);
    int pv = pvJoueur1;
    if(joueur==JOUEUR2) {
        pv = pvJoueur2;
    }
    printf("  Navires %d", pv);
}

void afficher_menu_bloquant()
{
    int choix; // contient le menu choisi
    int choixOK = 0; // indique si le menu choisi est valide
    while(!choixOK) {
        system("cls");

        Color(12,0);
        printf("BATAILLE NAVALE\n");
        Color(7,0);

        printf("\n");
        printf("Menu de jeu\n");
        printf("===============\n");

        printf("  1. IA vs IA\n");
        printf("  2. IA vs Joueur\n");
        printf("  3. Quitter\n");

        printf("\n");
        printf("Votre choix ? ");
        scanf("%d", &choix);

        choixOK = (choix==1 || choix==2 || choix==3);
    }

    switch(choix) {
        case 1: lancer_partie(1); break;
        case 2: lancer_partie(0); break;
        case 3: printf("\nAu revoir!\n"); exit(0); break;
    }
}

void lancer_partie(int automatique) // automatique indique si c'st la partie IA vs IA ou IA vs Joueur
{
    int termine = 0; // indique si le jeu est terminé ou non
    while(!termine) {
        system("cls"); // efface l'écran

        Color(12,0);
        printf("~~~~~BATAILLE NAVALE~~~~~\n");
        Color(7,0);

        printf("\n");
        afficherStats(JOUEUR1);
        printf("\n");
        afficherStats(JOUEUR2);
        printf("\n");

        printf("\n");
        printf("MAP JOUEUR 1\n");
        int cacherNavires = 0;
        if(!automatique) {
            cacherNavires = 1;
        }

        affichemap(map,JOUEUR1, cacherNavires);//permet de cacher les navires de l'IA quand je joue contre elle

        printf("\n");
        printf("MAP JOUEUR 2\n");

        affichemap(map,JOUEUR2, 0);

        int tirX, tirY;

        tirX = doRand(0, LIGNE-1);
        tirY = doRand(0, COLONNE-1);
        attaque(map, JOUEUR1, JOUEUR2, tirX, tirY);

        if(automatique) {
            tirX = doRand(0, LIGNE-1);
            tirY = doRand(0, COLONNE-1);
        }
        else {
            printf("\n");
            printf("Ligne a attaquer: ");
            scanf("%d", &tirX);
            printf("Colonne a attaquer: ");
            scanf("%d", &tirY);
        }
        attaque(map, JOUEUR2, JOUEUR1, tirX, tirY);

        termine = (pvJoueur1==0 || pvJoueur2==0);
    }
}

int main()
{
    // Initialisation

    placementbateaux(map,JOUEUR1,CORVETTE);
    placementbateaux(map,JOUEUR1,DESTROYER);
    placementbateaux(map,JOUEUR1,DESTROYER);
    placementbateaux(map,JOUEUR1,CROISEUR);
    placementbateaux(map,JOUEUR1,CROISEUR);
    placementbateaux(map,JOUEUR1,PORTEAVION);

    placementbateaux(map,JOUEUR2,CORVETTE);
    placementbateaux(map,JOUEUR2,DESTROYER);
    placementbateaux(map,JOUEUR2,DESTROYER);
    placementbateaux(map,JOUEUR2,CROISEUR);
    placementbateaux(map,JOUEUR2,CROISEUR);
    placementbateaux(map,JOUEUR2,PORTEAVION);

    // menu de jeu

    afficher_menu_bloquant();

    printf("Partie terminée!\n");
    if(pvJoueur1==0) {
        printf("Vainqueur: Joueur2\n");
    }
    else {
        printf("Vainqueur: Joueur1\n");
    }

    return 0;
}

