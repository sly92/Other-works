#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pizzas {
	
	int numero;
	double prix;
	char clients[5];
} Pizza;


void init_pizza(Pizza **p, int n, double prix, char *c)
{
	Pizza *p1 = *p = malloc(sizeof(*p1));
	p1->numero=n;
	p1->prix=prix;
	strcpy(p1->clients,c);
}

void aff_pizza(Pizza p){
	
	printf("\nnumero: %d \nprix: %5.2f\nclients: %s\n",p.numero,p.prix,p.clients);
}

/* for(;b;) = for(;b!=0;)*/

void affiche_assortiment(int b){
	
	int i;
	printf("L'assortiement %d contient les pizzas : ",b);
	for(i=1;b;i++,b/=2){
		if(b%2) printf(" %d",i);
	}
		printf("\n");
}

void tableau_satisfaction(int b, const char * amis, Pizza **p){
	
	int i;
	int sat[26]={};	// 26 amis au total
	const char *c;
		printf("\n");
	for(;b;b/=2,p++){
	if(b%2){
		for(c =(*p)->clients;*c;c++) // () car -> s'execute avant *p
			sat[*c-'A']=1;
		}
	}

	printf("Tableau de satisfaction de vos amis:\n\n%s\n",amis);
	for(c=amis;*c;c++) printf("%d",sat[*c-'A']);
	printf("\n");
}
	

void calsat(int b, int sat[26], Pizza **p){
	
	int i;
	const char *c;
	
	for(;b;b/=2,p++){
	if(b%2){
		for(c =(*p)->clients;*c;c++) // () car -> s'execute avant *p
			sat[*c-'A']=1;
		}
	}
}

/*  assortiement tout pizza existe
    voir le nombre de personne qui aime ces pizzas 
	Verifier si en achetant moins de pizza tout les personnes aime */


double prix(int b, Pizza **p)
{
	int s=0;

	for(;b;b/=2,p++){
		if(b%2){	
			s+=(*p)->prix;		
		} 
	}
	return s;
}

/* cherche l'assortiement qui satisfont tout le monde et qui a le prix minimum*/
int tous_satisfait_moinsCher(Pizza **p, int n){
	
	int sat[26], sat2[26];	
	int bmin=(1<<n)-1;
	double pmin=prix(bmin,p), pr;
	
	printf("Les assortiments qui satisfont tout le monde sont: \n\n");
	calsat(bmin,sat,p); // 1<<n <=> 2^n ; calcule assortiement pour tout les pizza
	
	int b,i;
	for(b=0;b<1<<n;b++){	
		calsat(b,sat2,p);
		
		for(i=0;i<26 && sat[i]==sat2[i];i++); // ";" corps de boucle vide
		if (i==26){
			if(pr==prix(b,p)<pmin) pmin=pr ,bmin=b;
		}
	}
	
	return bmin;
}

/*heuristique*/

void afft(int t[], int n)
{ while(n--) printf(" ",*t++);
  printf("\n");
}

int main(){
	
	Pizza **p = malloc(sizeof(*p)*10); // <=> *p[10];
	affiche_assortiment(21);
	init_pizza(p,1,10.00,"AHIG");
	init_pizza(&p[1],2,12.00,"XYZW");	// &p[i] = p+i
	init_pizza(p+2,4,7.50,"TRUC");
	init_pizza(p+3,5,2.00,"DFCU");
	init_pizza(p+4,10,3.00,"AHJ");
	init_pizza(p+5,11,5.00,"FGHJ");
	init_pizza(p+6,13,6.00,"ZER");
	init_pizza(p+7,16,8.00,"TYUI");
	init_pizza(p+8,18,8.50,"POIU");
	init_pizza(p+9,20,5.50,"MLKJ");
	
	
	int i;
	for(i=0;i<10;i++)
	aff_pizza(*p[i]);	
	tableau_satisfaction(21,"BRAVO",p);
	int bmin = tous_satisfait_moinsCher(p,10);
	printf("L'assortiment satisfaisant tout le monde le moins cher coute %.2f. C'est :\n",prix(bmin,p));
	affiche_assortiment(bmin);
	return 0;
}



