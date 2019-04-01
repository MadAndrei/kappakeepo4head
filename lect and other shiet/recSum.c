#include <stdio.h>
#include <stdlib.h>

void recSum(int arr[100], int counter, int sum){
	if (counter != 100){
		sum+=arr[counter];
		counter++;
		recSum(arr, counter, sum);
	}
	printf("%d\n", sum);
	exit(1);
}


int main(){
	int counter = 0;
	int sum = 0;
	int arr[100];
	int elem;
	for (int i = 0; i < 100; i++){
		scanf("%d", &elem);
		arr[i] = elem;
	}	
	recSum(arr, counter, sum);
    return 0;
}
