#include <stdio.h>
#include <stdlib.h>
/*void  parr(int *a, int n){
	if(!n) // массив пуст 
	return;
	printf("%d", *a);
	parr(a+1, n-1);
}
*/


struct Tree{
	int n;
	struct Tree* l;
	struct Tree* r;
};

struct Tree* createNode(int n, struct Tree* l, struct Tree* r){
	struct Tree* t = calloc(sizeof(struct Tree), 1);
	t->n = n;
	t->r = r;
	t->l = l;
	return t;
}


struct Tree* createLeaf(int n){
	return createNode(n, NULL, NULL);
}


int main(){
//	int arr[]={1,2,3,4,5,6,7};
//	parr(arr, sizeof(arr)/sizeof(int));
	struct Tree* root = createNode(4, createNode(2, createLeaf(3)), createLeaf(5));
	printf("%d", root->l->n);
	return 0;
}
