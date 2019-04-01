#include <stdio.h>
#include <stdlib.h>


int foo(int i, int j, int* arr, int m, int n){
	if((i == m-1) && (j == n-1)){
		//printf("!!!!!!hooray!!!!!!!\n");
		return 1;
	}
	if (*(arr+i*m+j)==0){
		*(arr+i*m+j) = 1;
		if(i+1 < m){
			if(foo(i+1, j, arr, m, n)){
				//printf("hooray from %d %d\n",i+1,j);
				return 1;
			}
		}
		if(i-1 >= 0){
			if(foo( i-1,  j,  arr,  m,  n)){
				//printf("hooray from %d %d\n",i-1,j);
				return 1;
			}
		}
		if(j+1 < n){
			if(foo( i,  j+1,  arr,  m,  n)){
				//printf("hooray from %d %d\n",i,j+1);
				return 1;
			}
		}
		if(j-1 >= 0){
			if (foo( i,  j-1,  arr,  m,  n)){
				//printf("hooray from %d %d\n",i,j-1);
				return 1;
			}
		}
	}
	//printf("cant reach end from %d %d\n",i,j);
	return 0;
}


int main(){
	int *arr = NULL;
	int strNum, stlbNum;
	scanf("%d%d", &strNum, &stlbNum);
	arr = (int*)malloc(strNum*stlbNum*sizeof(int));
	for (int i=0; i<strNum; i++){
		for (int j=0; j<stlbNum; j++){
			scanf("%d", (arr+i*stlbNum+j));
		}
	}
	printf("\n");
	for (int i=0; i<strNum; i++){
		for (int j=0; j<stlbNum; j++){
			printf("%d ", *(arr+i*stlbNum+j));
		}
		printf("\n");
	}
	
	if (foo(0, 0, arr, strNum, stlbNum)){
		printf("jhbjh");
	}
	else
	{
		printf("not jhbjh");
	}
	
	printf("\n");
	for (int i=0; i<strNum; i++){
		for (int j=0; j<stlbNum; j++){
			printf("%d ", *(arr+i*stlbNum+j));
		}
		printf("\n");
	}
}
