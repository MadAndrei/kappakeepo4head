#include <stdio.h>
#include <stdlib.h>


int foo(int i, int j, int* arr, int m, int n, int k){
	if (*(arr+i*n+j)==0){
		*(arr+i*n+j) = 8;
		if(i+1 < m){
			//k+=1;
			k+=foo(i+1, j, arr, m, n, k);
		}
		if(i-1 >= 0){
			//k+=1;
			k+=foo(i-1, j, arr, m, n, k);
		}
		if(j+1 < n){
			//k+=1;
			k+=foo(i, j+1, arr, m, n, k);
		}
		if(j-1 >= 0){
			//k+=1;
			k+=foo(i, j-1, arr, m, n, k);
		}
	}
	else{
		return 0;
	}
	return k+1;
}


int main(){
	int *arr = NULL;
	int strNum, stlbNum;
	int k = 0;
	scanf("%d%d", &strNum, &stlbNum);
	arr = (int*)malloc(strNum*stlbNum*sizeof(int));
	for (int i=0; i<strNum; i++){
		for (int j=0; j<stlbNum; j++){
			scanf("%d", (arr+i*stlbNum+j));
		}
	}
	/*for (int i=0; i<strNum; i++){
		for (int j=0; j<stlbNum; j++){
			if(*(arr+i*stlbNum+j) == 0){
				foo(i, j, arr, m, n, k);
			}
		}
	}
	*/
	printf("\n");
	int l = foo(0, 0, arr, strNum, stlbNum, k);
	printf("%d\n", l);
	printf("\n");
	for (int i=0; i<strNum; i++){
		for (int j=0; j<stlbNum; j++){
			printf("%d ", *(arr+i*stlbNum+j));
		}
	printf("\n");
	}
}
