#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd (int *array, int n){
	int i;
	int sumBeforeAfter = 0;
	for (i=0; i<index_first_even(array, n); i++){
		sumBeforeAfter = abs(array[i]) + sumBeforeAfter;
	}
	if (index_last_odd(array, n) == -1)
		return sumBeforeAfter;	
	for (i=index_last_odd(array, n); i<n; i++){
		sumBeforeAfter = abs(array[i]) + sumBeforeAfter;
	}
	return sumBeforeAfter;
}
