#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sumBetweenEvenOdd.h"
#include "indexFirstEven.h"
#include "indexLastOdd.h"

int sumBetweenEvenOdd (int *array, int n){
	int i;
	int sumBetween=0;
	if (indexFirstEven(array, n) == -1)
		return sumBetween;
	for (i=indexFirstEven(array, n); i<indexLastOdd(array, n); i++){
		sumBetween=sumBetween+abs(array[i]);
}
return sumBetween;
}
