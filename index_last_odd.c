#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "index_last_odd.h"

int index_last_odd (int *array, int n){
	int odd = -1;
	int i;
	for (i=0; i<n; i++){
		if (array[i] % 2 != 0)
			odd=i;
}
	return odd;
} 
