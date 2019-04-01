#include<stdio.h> 
#include<stdlib.h>
#include<string.h>


typedef struct MusicalComposition{
	int year;
	struct MusicalComposition* next;
}MusicalComposition;


MusicalComposition* createMusicalComposition(int year){
	MusicalComposition* Node = malloc(sizeof(MusicalComposition));
	Node->year = year;
	Node->next = NULL;
	return Node;
}


MusicalComposition* createMusicalCompositionList(int* array_years, int n){
	MusicalComposition* head = createMusicalComposition(array_years[0]);
	MusicalComposition* tmp = createMusicalComposition(array_years[1]);
	head->next = tmp;
	for (int i=2; i<n; i++){
		tmp->next = createMusicalComposition(array_years[i]);
    	tmp = tmp->next;
  	}
	return head;
}

void print_reversed(MusicalComposition *head){
    if (head) {
        print_reversed(head->next);
        printf("%d\n", head->year);
	}
}


int main(){
    int length;
    scanf("%d", &length);
    int* years = (int*)malloc(sizeof(int)*length);
    for (int i=0;i<length;i++){
    	scanf("%d", &years[i]);
    }
    MusicalComposition* head = createMusicalCompositionList(years, length);
    printf("\n");
    print_reversed(head);
    free(years);
    return 0;
}
