#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define SIZE 502

typedef char TYPE;

typedef struct Stack{
	TYPE arr[SIZE];
	size_t sizeStack;
}Stack;


void push(Stack* stack, const TYPE value){
    if (stack->sizeStack >= SIZE){
        exit(-1);
    }
    stack->arr[stack->sizeStack] = value;
    stack->sizeStack++;
}


TYPE pop(Stack* stack){
    if (stack->sizeStack == 0){
        exit(-1);
    }
    stack->sizeStack--;
    return stack->arr[stack->sizeStack];
}


TYPE top(const Stack* stack) {
    if (stack->sizeStack <= 0) {
        exit(-1);
    }
    return stack->arr[stack->sizeStack - 1];
}



void main(){
    Stack stack;
    stack.sizeStack = 0;
 //   push(&stack, 'g');
  //  printf("%c", top(&stack));
  
  
}
