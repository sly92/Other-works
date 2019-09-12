#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void tri_a_bulle(int *t, int taille){
	
	int i,j,tmp;
	
	for(i=0;i<taille;i++)		
		for(j=0;j<taille-1;j++)
			if(t[j]>t[j+1]){ tmp = t[j]; t[j]=t[j+1];  t[j+1]=tmp;}
}


void tri_a_bulle2(int *tab, int taille){
	int i,j,continuer;
	do
	{ 	continuer = 0;
		for(j=0;j<taille-1;j++)
		if(tab[j]>tab[j+1])
		{ int x= tab[j]; tab[j]=tab[j+1]; tab [j+1]=x; continuer=1;}
		}while(continuer);
}

void tri_a_bulle3(int *tab, int taille){
	int j,nt;
	for(;taille>1;taille=nt)
	{
		nt=0;
		for(j=0;j<taille-1;j++)
		if(tab[j]>tab[j+1])
		{ int x=tab[j]; tab[j]=tab[nt=j+1]; tab[j+1]=x;}
	}
}
//
//void tri_selection(int *tab, int taille){
//
//	int i, j, tmp;
//	int min=*tab;
//	int index;
//	
//	for(i=0;i<taille;i++){
//		
//		for(j=0;j<taille;j++){
//			
//			if(tab[j+i]<min) { min=tab[j+i]; index=j+i; }
//		}
//		 tmp=tab[i];
//		 tab[i]=min;
//		 tab[index]=tmp;
//		 
//	}	
//}

void tri_selection(int *t, int n){
	int i,j;
	for(i=0;i<n;i++){
		int x=t[i];
		for(j=i+1;j<n;j++) if(t[j]<x)
		{ t[i]=t[j]; t[j]=x; x=t[i];}
	}
}
	
void tri_insertion(int *t,int n){
	
	int i,j,x;
	
	for(i=1;i<n;i++){
		x = t[i];
		for(j=i-1;j>=0 && t[j]>x;j--){
			t[j+1]=t[j];
			t[j+1]=x;
		
		}
	}
}
	
//void tri_insertion(int *t, int n){
//	
//	int i,j,x;
//	
//	for(i=1;n-1;i++){
//		x=t[i];
//		while(j>0 && t[j-1]>x){
//			t[j]=t[j-1];
//			j--;
//		}
//		t[j]=x;
//	}	
//}

typedef void (*tri)(int*,int);

void test(int t[], int n, tri f)
{
	int *u = malloc(n*sizeof(*u)), i;
	for(i=n;i--;) u[i] = t[i];
	int a= clock();
	f(u,n);
	a=clock()-a;
	printf("durée du tri %d\n",a);
	free(u);
}

void taleat(int t[], int n)
{
	int i;
	for(i=n;i--;) t[i]=i*i%(2*n+1);
}



//int init_tableau(){
//	
//	int i, *t;
//	int n =50;
//	
//	while(n--){
//		t[n]= rand(n)+1;	
//	}
//	return t;
//}

void aff_tab(int t[],int n){
	
	while(n--) printf(" %d",*t++);
	printf("\n");
}

int main(){
	
	int t[]={21,2,-1,7,4,18,3,9,23,0,1,14,-5}, n=13;
	aff_tab(t,n);
	tri_insertion(t,n);
	aff_tab(t,n);
	
	for(n=1;n<=10000;n*=10)
	{
		int *t=malloc(n*sizeof(*t));
		taleat(t,n);
		test(t,n,tri_a_bulle);
		test(t,n,tri_a_bulle2);
		test(t,n,tri_a_bulle3);
		test(t,n,tri_selection);
		free(t);
	}
	return 0;
	
}
