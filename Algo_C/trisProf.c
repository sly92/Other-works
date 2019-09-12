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

typedef void (*tri)(element*,int);
void test(element t[],int n,tri f,const char *nom)
{ element *u=malloc(n*sizeof(*u));
  int i;
  for(i=n;i--;) u[i]=t[i];
  int a=clock();
  f(u,n);
  a=clock()-a;
  printf("%s trie %d nombres en un temps %d\n",nom,a);
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
  tri_insertion(t,n);
  afft(t,n);
  for(n=1;n<=10000;n*=10)
  { element *t=malloc(n*sizeof(*t));
    taleat(t,n);
    testri(t,n,tri_a_bulle);
    testri(t,n,tri_a_bulle2);
    testri(t,n,tri_a_bulle3);
    testri(t,n,tri_selection);
    testri(t,n,tri_insertion);
    free(t);
  }
  return 0;
}
