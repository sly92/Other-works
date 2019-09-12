#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include <math.h>

void decomp_2(int nb, int *dec, int digits){
	
	int i;
	for(i=digits-1;i>=0;i--){		
		dec[i]=nb&1; //operation bit a bit &1 = %2==0 
		nb>>=1;	// decalle d'1 bit vers la droite
	}
}

void afft(int t[], int n)
{ while(n--) printf("%d",*t++);
  printf("\n");
}

void motProf(int i,  const char* a, int digits){
	
	int dec[digits];
	decomp_2(i,dec,digits);
	while(digits--) if(dec[digits]) putchar(a[digits]);	
}

void enumere(const char* alphabet){

	int digits=strlen(alphabet), n=1<<digits, i;
	for(i=0;i<n;i++) motProf(i,alphabet,digits), printf("\n");	
}

void decomp_22(int nb, int *dec, int digits){
	
	int i;
	for(i=digits-1;i>=0;i--){		
		dec[i]=nb%2; 
		nb/=2;
	}
}


void motProf2(int i,  const char* a, int digits){
	
	//int dec[digits];
	//decomp_2(i,dec,digits);
	while(digits--) if(i>>digits&1) putchar(a[digits]);	
}

void enumere2(const char* alphabet){

	int digits=strlen(alphabet), n=pow(2,digits), i;
	for(i=0;i<n;i++) motProf2(i,alphabet,digits), printf("\n");	
}


void main(){
	
	int t[8];
	int digits=8;
	int nb=5;
	
	decomp_2(nb,t,digits);
	afft(t,8);

	enumere("ACGTEB");
	enumere2("ACGTEB");	
}
