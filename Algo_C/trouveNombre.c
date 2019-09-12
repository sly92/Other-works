#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#define TRUE 1
#define FALSE 0

int main()
{ 
    int choix1,choix2,choix3,mode;
    int fini = 0;
    int lvl = 1;
     int continuerPartie = TRUE;
    char rep=' ';
    
    int nbMyst = 0, nb = 0, win = FALSE, coups=0;
    int c, ok;
    int MIN=1,MAX=100;
      system("cls");
       printf("\n\n\nBienvenue dans le jeu :D \n\n");
      system("\n\n\n\n\n\npause");
      system("cls");
      do {
   printf("\n\n\n\n\n  =======     MENU     =======\n\n\n 1 ------    JOUER      ------\n\n 2 ------    DIFFICULTE ------ \n\n 3 ------    AIDE       ------ \n\n 4 ------    QUITTER    ------ \n\n\n");

 	
    scanf("%d",&choix1);  

   switch (choix1) {
    
        case 1: 
        system("cls");
            printf("\n\n\n\n\n\n\n 1 ------    1 JOUEUR      ------\n\n");
            printf(" 2 ------    2 JOUEUR      ------");
            
            scanf("%d",&choix2);
            
            switch (choix2) {
            
                case 1: mode=1;
                break;
                
                case 2: mode=2;
                break;
                
                default: mode=1;
                break;
            }
            break;

        case 2:
            system("\n\n\n\n pause");
            system("cls");       
            printf("\n\n\n\n==== DIFFICULTE ====\n\n\n\n\n 1 ------  Facile  ------\n\n");
            printf(" 2 ------  Moyen  ------\n\n");
            printf(" 3 ------  Difficile  ------\n\n");
            
            scanf("%d",&choix3); 
            

            switch (choix3) {
            
                case 1: MAX=100;
                break;
                
                case 2: MAX=1000;
                break;
                
                case 3: MAX=10000;
                break;
                
                default: printf("entrer une valeur correcte");
                break;
            } 
            break;      
            
        case 3: system("\n\n\n\n\n\n pause");
      system("cls");
      printf("------  Instruction  ------\n\n Vous devez trouvez le nombre cachee.\n\n Saisissez des valeurs en fonction des indications que vous verrez ;) \n\n\n\n\n\n\n\n\n\n");
        system("\n\n\n\n\n\npause \n\n");        
        break;
        
        case 4: fini=1;
        system("\n\n\n\n\n\npause");
      system("cls");
        printf("Vous venez de quitter le jeu\n\n");
        exit(0);
        break;
    	}
        }while(choix1!=1);

    while(continuerPartie==TRUE)  { 
 
     
    if(choix2!=1){
system("cls");
        printf("Un des deux joueurs doit saisir le nombre cachee :");
        scanf("%d",&nbMyst);
        system("cls");
    }
    else{
    srand(time(NULL));
    nbMyst = (rand() % (MAX - MIN + 1)) + MIN;
    }
    
    do {

     
        printf("\n Veuillez saisir un nombre :");
        
      do {
      ok= 1;
       
      /* saisie */
      if(!scanf("%d", &nb))
         ok= 0;
       
      /* vérification de la fin de la saisie
         et vidage du flux par la même occasion */
      while((c = getchar()) != '\n' && c!=EOF) {
         if(c!=' '  &&  c!='\t'  &&  c!='\f'  &&  c!='\r')   /* si ce n'est pas une "caractère blanc" */
            ok= 0;
      }
       
      /* si invalide, on redemande */
      if(!ok){
      	
      system("cls");
         printf("\n\nVeuillez saisir un nombre uniquement.\nRecommencez : ");
    }
   } while(!ok);   /* on recommence si la saisie n'est pas valide */
        
           coups++;
            if(nbMyst>nb){
            	system("cls");
            printf("\n Plus grand !\n\n");
         
       }
            else  if(nbMyst<nb){
            	system("cls"); 
            printf("\n Plus petit !\n\n");
            }
            else {
            
            system("cls");    
            printf("Bravo ! vous avez trouvee en %d coups :D \n\n", coups);
            win=TRUE;
            }
        
    }while(win==FALSE);

   
        printf("\n\n Voulez vous faire une autre partie ? (o/n)\n");
        scanf("%c",&rep);
        system("cls");
        if(rep=='n')
            continuerPartie=FALSE;

        coups=0;
        win=FALSE;
        
    }
    system("cls");
    printf("Merci d'avoir jouee ! Au revoir \n\n");
    return 0;
}











