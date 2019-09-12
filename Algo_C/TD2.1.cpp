void tri_a_bulle(int *tab, int taille){
	
	int i;
	int tmp;
	
	for(i=1;i<taille-1;i++){
		if(t[i-1]>t[i])
		{
		tmp = t[i];
		t[i] = t[i+1];
		t[i+1]=tmp;
		}
	}
}

int main(){
	
	int t[12]={21,2,-1,7,4,18,3,9,23,0,1,14,-5};
	
	tri_a_bulle(t,13)
	return 0;
	
}
