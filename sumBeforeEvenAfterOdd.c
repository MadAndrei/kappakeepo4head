#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sumBeforeEvenAfterOdd.h"
#include "indexFirstEven.h"
#include "indexLastOdd.h"

int sumBeforeEvenAfterOdd (int *array, int n){
	int i;
	int sumBeforeAfter = 0;
	for (i=0; i<indexFirstEven(array, n); i++){
		sumBeforeAfter = abs(array[i]) + sumBeforeAfter;
	}
	if (indexLastOdd(array, n) == -1)
		return sumBeforeAfter;	
	for (i=indexLastOdd(array, n); i<n; i++){
		sumBeforeAfter = abs(array[i]) + sumBeforeAfter;
	}
	return sumBeforeAfter;
}
