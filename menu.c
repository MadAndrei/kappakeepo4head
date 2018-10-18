#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_OF_ELEMENTS 100

int main (){
	int array [NUMBER_OF_ELEMENTS];
	int i=0;
	int c=0;
	int which;
	scanf ("%d", &which);
	while(1){
		c=scanf("%d",array+i);
			if(c==-1){
	break;
}
	i++;
}
	if (which == 0){
		if (indexFirstEven(array, i) == -1)
			printf ("Данные некорректны\n");
		else
			printf ("%d\n", indexFirstEven(array, i));
	}
	if (which == 1){
		if (indexLastOdd(array, i) == -1)
			printf ("Данные некорректны\n");	
		else
			printf ("%d\n", indexLastOdd(array, i));
	}	
	if (which == 3){
		printf ("%d\n", sumBeforeEvenAfterOdd(array, i));
	}
	if (which == 2){
		printf ("%d\n", sumBetweenEvenOdd(array, i));
	}
	if (which !=0 && which != 1 && which != 2 && which != 3) 
		printf ("Данные некорректны\n");
}
