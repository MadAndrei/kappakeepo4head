#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define vtof(v) ( *((float*)v) )
#define SIZE 4

int cmp(const void* a, const void* b){
	float res;
	res = (vtof(a) - vtof(b));
	if((res <  0.0001) && (res >= 0)){
		return 0;
	}
	if(res < 0){
		return -1;
	}
	if(res > 0){
		return 1;
	}
}


int universalMax(void* arr, int n, int (*cmp)(const void* a, const void* b)){
	
	return 0;
}


int main(){
	int* arrInt = NULL;
	char* arrChar = NULL;
	float* arrFloat = NULL;
	int sizeEl;
	scanf("%d", &sizeEl);
	if(sizeEl == 1){
		arrChar = (char*)malloc(SIZE*sizeof(char));
		scanf("%s", arrChar);
		for(int i=0; i<SIZE; i++){
			printf("%f ", (float)(arrChar[i]));
		}
	}
	if(sizeEl == 4){
		arrInt = (int*)malloc(20*sizeof(int));
		for(int i=0; i<SIZE; i++){
			scanf("%d", &arrInt[i]);
		}
//		for(int i=0; i<SIZE; i++){
//			printf("%d", arrInt[i]);
//		}
	}
	if(sizeEl == 8){
		arrFloat = (float*)malloc(20*sizeof(float));
		for(int i=0; i<SIZE; i++){
			scanf("%f", &arrFloat[i]);
		}
//		for(int i=0; i<SIZE; i++){
//			printf("%f", arrFloat[i]);
//		}
	}
//	int l = cmp(&arrFloat[0], &arrFloat[1]);
int l = cmp(&arrInt[0], &arrInt[1]);
	printf("%d", l);
}
