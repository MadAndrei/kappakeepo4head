#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd (int *array, int n){
	int i;
	int sumBetween=0;
	if (indexFirstEven(array, n) == -1)
		return sumBetween;
	for (i=indexFirstEven(array, n); i<indexLastOdd(array, n); i++){
		sumBetween=sumBetween+abs(array[i]);
}
return sumBetween;
}