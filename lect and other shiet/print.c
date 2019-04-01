#include <stdio.h>

int cmp(const void* a, const void* b){
	if(*(int*)a > *(int*)b){
		return 1;
	}
	if(*(int*)b > *(int*)a){
		return -1;
	}
	return 0;
}


void* arrMax(int* arr, int n, int size, int (*comp)(const void *a, const void *b)){
	void* max = arr;
	for(int i=0; i<n; i++){
		if(comp(max, arr+i*size)<0){
			max = arr+i*size;
		}
	}
	return max;
}


int main(){
	int arr[] = {10,8,2,3,4,5,6,7,9};
	printf("%d\n", (int*)arrMax(arr, sizeof(arr)/sizeof(int), sizeof(int), cmp) - arr);
	return 0;
}
