#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "indexLastOdd.h"

int indexLastOdd (int *array, int n){
	int odd = -1;
	int i;
	for (i=0; i<n; i++){
		if (array[i] % 2 != 0)
			odd=i;
}
	return odd;
} 
