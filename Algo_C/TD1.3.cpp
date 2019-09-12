#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Exercice 5

void insere(int *T,int taille, int b)
{
	int k,tmp,i;
	for(i=taille;;i--){
		if(T[i]==b){
			tmp=T[i];
			T[i]=T[i+1];
			T[i+1]=tmp;
		}
		}
	
}

// Exercice 6

void decrypt(char*c, int j){
	
	int i,t,k;
	
	for(i=0;i<27;i++){
		if(c[k]==' ') t=26;
		else
		{
		t = c[k]- 'a';
		t=(t+i)%27;
		}
	if(t==26) printf(" ");
	else printf("%c",t+'a');
	}
	printf("\n");
	
}

// Exercice 6 (prof)

void decryptProf(char c[], int j){
	int i, k;
	for(i=1;i<=26;i++){
		for(k=0;k<j;k++){
		int t=c[k];
		
		t= t==' ' ? 26 : t-'a';
		t=(t+j)%27;
		t= t==26? ' ' : t+'a';
		putchar(t);
		}
	printf("\n");
	}
}

void decomp(double alpha, int n){
	
	int i;
	int a=alpha;
	double e=a;
	
	for(i=0;i<n;i++){
	
	int a= alpha;
	
	if(a=0){
	printf("%f",a);
	exit(0);
	}
	
	printf("%.0f ",alpha);
	
	a-=alpha;
	
	a = 1/a;

	}
	printf("\n");
}

void decompProf(double a, int n){
	while(n-->0)
	{
		int a=a;
		double e=a;
		printf("%.0f ",e);
		a-=e;
		
		if(!a) break;
		a=1/a;
	}
	printf("\n");
}

void decomp_tab(double alpha, int n, int *tableau){
	
	int i=0;
	
	while(i<n){
	int a=alpha;	
	double e=a;
	tableau[i++]=e;
	
	alpha-=e;
	
	if(!alpha) break;
	alpha=1/alpha;
	}
	
	while(i<n){
		tableau[i++]=0;
	}
}

void aff_tab(int n, int t[n]){
	while(n--) printf("%d ",*t++),
	printf("\n");
}


double convergente(int k, int *tableau){
	
	int i;
	double r =tableau[k-1]; 
		
	for(i=k-2;i>=0;i--){
		
		r = tableau[i] + 1/r;		
	}	
	return r;
}

double convergenteProf(int k, int tab[k]){
	double r=tab[--k];
	while(k) r=tab[--k]+1/r;
	return r;
}


/* Utiliser algorithme d'Euclide pour avoir aucune incertitude sur les fractions continu entre deux chiffres */
double decomp2(int k, int tab[k]){
	
	
}


int main() {
	
	int tab[10]={0,3,14,6,15};
	int i;
//	insere(tab,5,4);
	
//	char c[] = "il fait beau aujourdhui";
//	decryptProf(c,strlen(c));
	
	decompProf(2.4,5);
	
	int n2=5, t[n2];
	decomp_tab(2.4,n2,t);
	aff_tab(n2,t);
	
	printf("\n\n\n\n\n\n");
	double a=0? 2.4 : 2*acos(0);
	
	decompProf(a,5);
	decomp_tab(a,n2,t);
	
	for(i=1;i<=n2;i++)
	printf("%d %.20f\n",convergenteProf(i,t));
	
	return 0;
}

