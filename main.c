#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define joueur1 0
#define joueur2 1
#define CORVETTE 1
#define DESTROYER 3
#define CROISEUR 4
#define PORTEAVION 6



void Color(int couleurDuTexte,int couleurDeFond){
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
void affichemap(int map[18][24][2],int joueur){
    int i=0;
    int j=0;

    for (i=0;i<18;i++){
        for(j=0;j<24;j++){
            if (map[i][j][joueur] == 0){
                Color(9,9);
            }
                printf("%2d",map[i][j][joueur]);
                Color(7,0);
        }
    printf("\n");
    }

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
        return (rand() % ((endVal + startVal -1)) + startVal);
    }
}
void placementbateaux(int map[18][24][2], int joueur,int taillebateau){
    int x = 0;
    int y = 0;
    int i = 0;

    x = doRand(0,17);
    y = doRand(0,23);

     for (i=0;i<taillebateau;i++){
         if (map[x+i][y][joueur]==0 && map[x+i][y][joueur]<18 && map[x+i][y][joueur]>=0){
         map[x+i][y][joueur]=taillebateau;
         }
     }
}
void attaqueIA(int map[18][24][2],int joueur){
    int x = 0;
    int y = 0;
    int viecorvetteJ1 = 1;
    int viecorvetteJ2 = 1;
    int viedestroyerJ1 = 3;
    int viedestroyerJ2 = 3;
    int viecroiseurJ1 = 4;
    int viecroiseurJ2 = 4;
    int vieporteavionJ1 = 6;
    int vieporteavionJ2 = 6;

    x = doRand(0,17);
    y = doRand(0,23);

    while(viecorvetteJ1>0 && viedestroyerJ1>0 && viecroiseurJ1>0 && vieporteavionJ1>0){
        if (map[x][y][joueur]==1){
            if (joueur==0) {viecorvetteJ1=viecorvetteJ1-1;
            }else if (joueur==1){viecorvetteJ2=viecorvetteJ2-1;
            }printf("coulé");
                }
        else if (map[x][y][joueur]==3){
            if (joueur==0) {viedestroyerJ1=viedestroyerJ1-1;
                if (viedestroyerJ1==0){
                }printf("coulé");
                }
                }else if(viedestroyerJ1>0){
                printf("touché");
                }
        else if (map[x][y][joueur]==4){
            if (joueur==0) {viecroiseurJ1=viecroiseurJ1-1;
                if (viecroiseurJ1==0){
                printf("coulé");
                }
                }else if(viecroiseurJ1>0){
                printf("touché");
                }
            }
        else if (map[x][y][joueur]==6){
            if (joueur==0) {vieporteavionJ1=vieporteavionJ1-1;
                if (vieporteavionJ1==0){
                printf("coulé");
                }
                else if(vieporteavionJ1>0){
                printf("touché");
                }
            }
        }
    }
}
j
int main()
{
    int map[18][24][2]={0};
    Color(12,0);
    printf("BATAILLE NAVALE\n");
    Color(7,0);
    printf("\n");
    placementbateaux(map,joueur1,CORVETTE);
    placementbateaux(map,joueur1,DESTROYER);
    placementbateaux(map,joueur1,DESTROYER);
    placementbateaux(map,joueur1,CROISEUR);
    placementbateaux(map,joueur1,CROISEUR);
    placementbateaux(map,joueur1,PORTEAVION);
    printf("\n");
    printf("MAP JOUEUR 1\n");
    placementbateaux(map,joueur2,CORVETTE);

    placementbateaux(map,joueur2,DESTROYER);
    placementbateaux(map,joueur2,DESTROYER);
    placementbateaux(map,joueur2,CROISEUR);
    placementbateaux(map,joueur2,CROISEUR);
    placementbateaux(map,joueur2,PORTEAVION);
    affichemap(map,joueur1);
    printf("\n");
    printf("MAP JOUEUR 2\n");
    affichemap(map,joueur2);
    attaqueIA(map,joueur1);
    attaqueIA(map,joueur2);



    return 0;
}




