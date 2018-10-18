#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "index_first_even.h"
int index_first_even(int* array,int n){
	int i=-1;
	for (i=0; i<n; i++){
		if (array[i] % 2 == 0)
			return i;
	}
	return -1;
}
