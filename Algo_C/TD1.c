#include <stdlib.h>
#include <stdio.h>
#include <time.h>


float terme_produit(int i, int j, int n, float **A, float **B){
	
	float res=0;
	int k;
	for(k=0;k<n;k++){
		res+=A[i][k]*B[k][j];
	}
	return res;
} 

float **nouvmat(int n){
	
	float **m= calloc(n, sizeof(*m));
	float *t= calloc(n*n,sizeof(*t));
	
	int i;
	for(i=0;i<n;i++){
		m[i]= t+i*n;
	}	
	return m;
	
}

float ** produit_mat(int n,float **A, float **B){
	
	float res=0;
	int i,j;
	float **m = nouvmat(n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			m[i][j]=terme_produit(i,j,n,A,B);
		}
	}
	return m;
	
}

float ** initiale(int n){
	
	float **m=nouvmat(n);
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			m[i][j]= rand()%201-100;
		}
	}
	return m;
}


void affmat(int n, float **A){
	int i,j;
	for(i=0;printf("\n"),i<n;i++){
		for(j=0;j<n;j++){
			printf("%8.0f ", A[i][j]);
		}	
	
	}
}

void affmatansi(int n, float A[n][n]){
	int i,j;
	for(i=0;printf("\n"),i<n;i++){
		for(j=0;j<n;j++){
			printf("%8.0f ", A[i][j]);
		}	
	
	}
}

float det3kr(float **A){
	
	return	 A[0][0]*A[1][1]*A[2][2]
			+A[0][1]*A[1][2]*A[2][0]
			+A[0][2]*A[1][0]*A[2][1]
			-A[0][0]*A[1][2]*A[2][1]
			-A[0][1]*A[1][0]*A[2][2]
			-A[0][2]*A[1][1]*A[2][0];
}


float det3ansi(float A[3][3]){
	
	return	A[0][0]*A[1][1]*A[2][2]
			+A[0][1]*A[1][2]*A[2][0]
			+A[0][2]*A[1][0]*A[2][1]
			-A[0][0]*A[1][2]*A[2][1]
			-A[0][1]*A[1][0]*A[2][2]
			-A[0][2]*A[1][1]*A[2][0];
}




int main()
{
	srand(time(NULL));
	{		
		int n=5;
		float **A;
		float **B;
		float **C;
		A=initiale(n);
		B=initiale(n);
		C=produit_mat(n,A,B);
		affmat(n,A);
		affmat(n,B);
		affmat(n,C);
		}
		{
		float t[9]={1,2,3,4,5,6,7,8,9};		// tableau de pointeur
		float *A[3]={t,t+3,t+6};
		float det1=det3kr(A);
	//	float det2=det3ansi(....);
		affmat(3,A);
		printf("det= %f",det1);
		}
		float A[3][3]={{1,2,3},{4,5,6},{7,8,9}};	// tableau de tableau
		affmatansi(3,A);
		printf("det= %f",det3ansi(A));
		
		
	return 0;

}
