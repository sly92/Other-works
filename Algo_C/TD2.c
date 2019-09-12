//laurent.pierre@u-paris10.fr
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

void insertion_gap(element *tab, int taille, int gap)
{
	element tmp;
	int i,j,k;
	for(k=0;k<gap;++k)
	{
		
		for(i=k;i<taille;i=i+gap)
		  { 
		  	tmp=tab[i];
		    for(j=i-gap;j>=0 && tab[j]>tmp;j=j-gap) 
		    {
		    	tab[j+gap]=tab[j];
		    	tab[j]=tmp;
			}
		  }
	}
}

void tri_shell1(element *tab,int taille)
{
	int h,r;
	for(h=taille;h>=1;--h)
	{
		r=h;
		while(r%3==0)	r=r/3;
		while(r%2==0)	r=r/2;
		if(r==1)	insertion_gap(tab,taille,h);
	}
}

void tri_shell2(element *tab,int taille)
{
	int h;
	for(h=taille;h>=1;--h)
	{
		h=h*2/3;
		insertion_gap(tab,taille,h);
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

//Tri Quadratique
//exercice 6
//Q1
int choix_pivot(int d, int f)
{
 return (f+d)/2;
}

//Q2
int partition(element tab[], int debut, int fin, int indice_pivot)
{
	element pivot=tab[indice_pivot],x;
	tab[indice_pivot]=tab[fin];
	int i, j=debut;
	for (i=debut;i<fin;i++) if (tab[i]<pivot)
	{
		x=tab[j]; 
		tab[j]=tab[i];
		tab[i]=x;
		j++;
	}
	tab[fin]=tab[j];
	tab[j]=pivot;
	return j;
}

//Q3
int partition_2(element t[], int debut, int fin, int indice_pivot)
{
	element pivot=t[indice_pivot],x;
	t[indice_pivot]=t[fin];
	int i=debut, j=fin-1;
	while (i<j)
	{
		while (i<j && t[i]>pivot) i++;
		while (i<j && t[j]<pivot) j--;
		x=t[j]; t[j]=t[i]; t[i]=x;
		i++;j--;
	}
	if (i==j && t[i]<pivot) i++;
	t[fin]=t[i];
	t[i]=pivot;
	return i;
}

//Exercice 7
void tri_rapide1(element t[], int debut, int fin)
{
	if (fin>debut)
	{
		int j=partition(t, debut, fin, 1?(debut+fin)/2:debut+rand()%(fin-debut+1));
		tri_rapide1(t, debut, j-1);
		tri_rapide1(t,j+1, fin);
	}
}

void tri_rapide(element t[], int n)
{
	tri_rapide1(t,0,n-1);
}

//Exercice 8 
//Tri Fusion
void fusion(element t[/*N*/], element u[/*M*/], element w[/*N+M*/], int N, int M)
{
	int i,j;
	i=j=0;
	while (i<N && j<M)
	{
		if (t[i]<u[j])
		{
			w[i+j]=t[i];
			i++;
		}
		else // t[i]>=u[j]
		{
			w[i+j]=u[j];
			j++;
		}
	} 
	for (; j<M; j++) w[N+j]=u[j];
	for (; i<N;i++) w[M+i]=t[i];
}

void fusion2(element t[/*N*/], element u[/*M*/], element w[/*N+M*/], int N, int M)
{
	int i=0,j=0;
	while (i<N && j<M)
	{
		if(t[i]<u[j]) w[i+j]=t[i],i++;
		else w[i+j]=u[j],j++;
	}
	while(i<N) w[i+j]=t[i],i++;
	while(j<M) w[i+j]=u[j],j++;
}

void fusion3(element t[/*N*/], element u[/*M*/], element w[/*N+M*/], int N, int M)
{
	int i=0,j=0,k=0;
	while(i<N&&j<M) w[k++]=t[i]<u[j]? t[i++]:u[j++];
	while(i<N) w[k++]=t[i];
	while(j<M) w[k++]=u[j];
}

void tri_fusion(element t[/*N*/], int n)
{
	int i,m=n/2,p=n-m;
	if (!m) return;
	tri_fusion(t, m);
	tri_fusion(t+m, p);
	element u[m];
	for (i=0;i<m;i++) u[i]=t[i];
	fusion(u, t+m, t, m,p);
}

//DIVERS
void afft(element t[], int n)
{ while(n--) printf(" "format_element,*t++);
  printf("\n");
}

typedef void (*tri)(element*,int);
void test(element t[],int n,tri f,const char *nom)
{ element *u=malloc(n*sizeof(*u));
  int i;
  for(i=n;i--;) u[i]=t[i];
  int a=clock();
  f(u,n);
  a=clock()-a;
  printf("%s trie %d nombres en un temps %d\n",nom,n,a);
  free(u);
}
#define testri(t,n,tri) test(t,n,tri,#tri)
void taleat(element t[], int n)
{ int i;
  for(i=n;i--;) t[i]=i*i%(2*n+1);
}



int main()
{
	element t[]={21, 2, -1, 7, 4, 18, 3, 9, 23, 0, 1, 14, -5}, n=13;
  	afft(t,n);
  	tri_fusion(t,n);
  	afft(t,n);
	for(n=1;n<=1000000;n*=10)
  	{ 
		element *t=malloc(n*sizeof(*t));
   		taleat(t,n);
    	testri(t,n,tri_fusion);
		testri(t,n,tri_rapide);
		testri(t,n,tri_shell1);
		testri(t,n,tri_shell2);
	//	testri(t,n,tri_insertion);
    	free(t);
	}
  	return 0;
}

