#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int kadane (int a[] ,int len);
int circular_com(int a[] ,int len);
 int main (void){
 	int i=0,len;
 	int a[100000];
 	while(scanf("%d ",&a[i])!=EOF){
 		i++;
	 }
	 len=i;
  	printf("%d",circular_com(a,len));
	
	return 0;
 }

int kadane (int a[] ,int len ){
	
  int kadamax, max;
  kadamax=max=a[0];	
  
  for(int i = 1 ;i<len ;i++){
  	
  	max=((max+a[i])>a[i]) ? max+a[i] : a[i];
  	
    kadamax=(max>kadamax) ? max : kadamax;
    
  
  }
	return kadamax;
	
}
int circular_com(int a[] ,int len){
	
	int b[len],mini,nocir,total=0;
	
	for(int i=0;i<len;i++){
	
		b[i]=a[i]*-1;	
	    total+=a[i];
	}
    mini=kadane(b,len);	
	nocir=kadane(a,len);
	return ((total+mini)>nocir) ? (total+mini) : nocir;	
	
}

