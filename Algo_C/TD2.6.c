

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#if 1
typedef int element;
#define format_element "%d"
#else
typedef double element;
#define format_element "%lf"
#endif
void tri_a_bulle(element *tab, int taille)
{ int i,j;
  for(i=0;i<taille;i++)
  for(j=0;j<taille-1;j++)
  if(tab[j]>tab[j+1])
  { element x=tab[j]; tab[j]=tab[j+1]; tab[j+1]=x; }
}
void tri_a_bulle2(element *tab, int taille)
{ int j,encore;
  do
  { encore=0;
    for(j=0;j<taille-1;j++)
    if(tab[j]>tab[j+1])
    { element x=tab[j]; tab[j]=tab[j+1]; tab[j+1]=x; encore=1; }
  } while(encore);
}
void tri_a_bulle3(element *tab, int taille)
{ int j,nt;
  for(;taille>1;taille=nt)
  { nt=0;
    for(j=0;j<taille-1;j++)
    if(tab[j]>tab[j+1])
    { element x=tab[j]; tab[j]=tab[nt=j+1]; tab[j+1]=x; }
  }
}
void tri_selection(element *tab, int taille)
{ int i,j;
  for(i=0;i<taille;i++)
  { element x=tab[i];
    for(j=i+1;j<taille;j++) if(tab[j]<x)
    { tab[i]=tab[j]; tab[j]=x; x=tab[i]; }
  }
}
void tri_insertion(element *t, int taille)
{ int i, j;
  for(i=1;i<taille;i++)
  { element x=t[i];
    for(j=i-1;j>=0 && t[j]>x;j--) t[j+1]=t[j];
    t[j+1]=x;
  }
}
void afft(element t[], int n)
{ while(n--) printf(" "format_element,*t++);
  printf("\n");
}

int croissant(element t[], int n){
	while(n--) printf(" "format_element,*t++);
	return 1;
}

typedef void (*tri)(element*,int);
void test(element t[],int n,tri f,const char *nom)
{ element *u=malloc(n*sizeof(*u));
  int i;
  for(i=n;i--;) u[i]=t[i];
  int a=clock();
  f(u,n);
  a=clock()-a;
  printf("%s trie %s %d nombres en un temps %d/%ds\n",nom,croissant(u,n) && somme(t,n)==somme(u,n)?"bien":"mal",n,a,CLOCKS_PER_SEC);
  free(u);
}

int somme(int t[], int n)
{
	int s=0;
	
	while(n--){
	s+=t[n];
	}
	return s;
}

#define testri(t,n,tri) test(t,n,tri,#tri)
void taleat(element t[], int n)
{ int i;
  for(i=n;i--;) t[i]=i*i%(2*n+1);
}

int choix_pivot(int d, int f){
	
	return f-d;
}

/* Trier un tableau avec 3 parties: " <= pivot", " => pivot", "non trié" 
   O(n²) tableau trié
   O(log n) tableau aléatoire */
   
int partition1(element *tab, int debut, int fin, int indice_pivot){
	
	element tmp;
	int i, j;
	tmp = tab[fin];
	tab[indice_pivot]=tmp;
	tab[fin]=tab[indice_pivot];
	j=debut;
	
	for(i=debut;i<fin-1;i++){
		if(tab[i]<tab[fin])
		{
			tmp=tab[j];
			tab[j]=tab[i];
			tab[i]=tmp;
			j++;
		}
		
		tmp=tab[j];
		tab[j]=tab[fin];
		tab[fin]=tmp;
	}
	
	return j;
}

int partition1Prof(element *tab, int debut, int fin, int indice_pivot){
	element pivot=tab[indice_pivot]=tab[indice_pivot], x;
	tab[indice_pivot]=tab[fin];
	int i, j=debut;
	for(i=debut;i<fin;i++) if(tab[i]<pivot){
		x=tab[i]; tab[j]=tab[i]; tab[i]=x; j++;
	}
	tab[fin]=tab[j];
	tab[j]=pivot;
	return j;
	}


int partition2Prof(element *tab, int debut, int fin, int indice_pivot){
	element pivot=tab[indice_pivot]=tab[indice_pivot], x;
	tab[indice_pivot]=tab[fin];
	int i=debut, j=fin-1;
	while(i<j)
	{	
		while(i<j && tab[i]>pivot) i++;
		while(i<j && tab[j]<pivot) j--;
		x=tab[j]; tab[j]=tab[i]; tab[i]=x;
		i++; j--;
	}
	if(i==j && tab[i]<pivot) i++;
	tab[fin]=tab[i];
	tab[i]=pivot;
	return i;
	}

int partition3Prof(element *tab, int debut, int fin, int indice_pivot){
	element pivot=tab[indice_pivot], x;
	tab[indice_pivot]=tab[fin];
	int i=debut-1, j=fin;
	tab[fin]==pivot;
	while(1)
	{	
		while(tab[--j]<pivot) ; /*instruction répété est le ";"*/
		if(i==j) break;
		tab[j]=tab[i]; 
		tab[i]=pivot;
		while(tab[++i]>pivot) ;
		if(i==j) break;
		tab[i]=tab[j];
		tab[j]=pivot;

	}
	if(tab[i]<pivot) i++;
	return j;
	}

/* Trier un tableau avec 3 parties: " <= pivot", " => pivot", "non trié" 
   O(n) tableau trié
   O(log n) tableau n'importe quel tableau*/
   
int partition2(double *tab, int debut, int fin, int indice_pivot){
	double tmp, pivot;
	int indice_PG, indice_PP;
	tmp=tab[fin];
	tab[fin]=tab[indice_pivot];
	tab[indice_pivot]=tmp;
	
	pivot=tab[indice_pivot];
	indice_PP=fin-1;
	indice_PG=debut;
	while(indice_PG <= pivot){
	while(indice_PG<indice_PP && tab[indice_PG] < pivot )
			indice_PG++;
		}
	
	while(indice_PG<indice_PP && tab[indice_PP] > pivot)
		indice_PP--;
		if(indice_PP!=indice_PG)
		{	tmp=tab[indice_PP];
			tab[indice_PP]=tab[indice_PG];
			tab[indice_PG]=tmp;
		}
		if(tab[fin]<tab[indice_PG]){
			tmp = tab[fin];
			tab[fin]=tab[indice_PG];
			tab[indice_PG]=tmp;
		}
		return indice_PG;
}

#define partition partition1
void tri_rapide(element *tab, int debut, int fin)
{
	if(fin>debut)
	{
		int j=partition(tab,debut,fin,0?(debut+fin)/2:debut+rand()%(fin-debut+1));
		tri_rapide(tab,debut,j-1);
		tri_rapide(tab,j+1,fin);
	}	
}

void tri_rap(element t[], int n) { tri_rapide(t,0,n-1); }
//
//void tri_rapide1(element t[], int n) { partition=partition1; tri_rapide(t,0,n-1); }
//void tri_rapide2(element t[], int n) { partition=partition2; tri_rapide(t,0,n-1); }
//void tri_rapide3(element t[], int n) { partition=partition3; tri_rapide(t,0,n-1); }


void fusion1(element t[/*n*/], element u[/*m*/], element v[/*n+m*/], int n, int m)
{
	int i=0, j=0;
	while(i<n && j<m)
	if(t[i]<u[j]) v[i+j]=t[i], i++;
	else 		  v[i+j]=u[j], j++;
	while(i<n)    v[i+j]=t[i], i++;
	while(j<m)    v[i+j]=u[j], j++;
}

void fusion2(element t[/*n*/], element u[/*m*/], element v[/*n+m*/], int n, int m)
{
	int i=0, j=0, k=0;
	while(i<n && j<m)
	v[k++]=t[i]<u[j]? t[i++] :u[j++];
	while(i<n) v[k++]=t[i++];
	while(j<m) v[k++]=u[j++];
}



void tri_fusion(element t[/*n*/], int n)
{
	int m= n/2, p=n-m;
	
	if(!m) return;
	tri_fusion(t,m);
	tri_fusion(t+m,p);
	element u[m];
	
	int i;
	for(i=0;i<m;i++) u[i]=t[i];
	fusion2(u,t+m,t,m,p);
	
}

int main()
{ element t[]={21, 2, -1, 7, 4, 18, 3, 9, 23, 0, 1, 14, -5}, n=13;
  afft(t,n);
  tri_insertion(t,n);
  afft(t,n);
  for(n=1;n<=1000000;n*=10)
  { element *t=malloc(n*sizeof(*t));
    taleat(t,n);
    if(n>10000) continue;
    testri(t,n,tri_a_bulle);
    testri(t,n,tri_a_bulle2);
    testri(t,n,tri_a_bulle3);
    testri(t,n,tri_selection);
    testri(t,n,tri_insertion);
   	testri(t,n,tri_rap);
   	testri(t,n,tri_fusion);
    free(t);
    
  }
  return 0;
}
