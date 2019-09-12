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

void tri_insertion(element *t, int taille)
{ int i, j;
  for(i=1;i<taille;i++)
  { element x=t[i];
    for(j=i-1;j>=0 && t[j]>x;j--) t[j+1]=t[j];
    t[j+1]=x;
  }
}

/* fonction qui trie par insertion une sous-suite d’un sous tableau des éléments
séparés par un gap*/

void insertion_gap(element *t, int taille, int gap)
{
  
  int i,j,k;
  for(k=0;k<gap;++k){
  	
  for(i=k;i<taille;i+=gap)
  { 
  	element x=t[i];
    for(j=i-gap;j>=0 && t[j]>x;j-=gap) t[j+gap]=t[j];
    t[j]=x;
  }
}
}
/*
On effectue le tri shell 
avec un gap = n*2/3, gap=(3^n-1)/2, sqrt(n) et autres */
void tri_shell(element *t,int taille)
{
	int h,r;	
	for(h=taille;h>=1;--h){
		
		r=h;
		while(r%3==0) r/=3;
		while(r%2==0) r/=2;
		if(r==1) insertion_gap(t,taille,h);
		
	}
}

void afft(element t[], int n)
{ while(n--) printf(" "format_element,*t++);
  printf("\n");
}

int somme(int t[], int n)
{
	int s=0;
	
	while(n--){
	s+=t[n];
	}
	return s;
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


#define testri(t,n,tri) test(t,n,tri,#tri)
void taleat(element t[], int n)
{ int i;
  for(i=n;i--;) t[i]=i*i%(2*n+1);
}


int main()
{ element t[]={21, 2, -1, 7, 4, 18, 3, 9, 23, 0, 1, 14, -5}, n=13;
  afft(t,n);
  for(n=1;n<=10000000;n*=10)
  { 
  	element *t=malloc(n*sizeof(*t));
    taleat(t,n);
    testri(t,n,tri_insertion);
    testri(t,n,tri_shell);
//    afft(t,n);
    free(t);
    
  }
  return 0;
}
