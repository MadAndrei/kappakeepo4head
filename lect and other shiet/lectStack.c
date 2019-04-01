#include <stdio.h>

typedef int type;
#define ST_SIZE 20
typedef struct ArrayStack{
	type arr[ST_SIZE];
	int sp;
}ArrayStack;

ArrayStack createArrStack(){
	ArrayStack stack = {{}}
}



void push(ArrayStack* stack, type val ){
	stack->arr[stack->sp+1] = val;
	stack->sp++;
}

type pop(ArrayStack* stack ){
	return stack->arr[(stack->sp)--];
}


type top(ArrayStack* stack ){
	return stack->arr[(stack->sp)];
}


type isEmpty(ArrayStack* stack ){
	return stack->sp == -1;
}



int main(){
	ArrayStack stack = createArrStack;
	for (int i = 0; i<10; i++){
		push(&stack, i);
	}
	while(!isEmpty(&satck))
}
