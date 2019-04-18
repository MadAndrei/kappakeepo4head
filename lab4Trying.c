#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node{
	int num;
	struct Node* next;
}Node;


void push(Node** head, int n){
	Node* tmp = malloc(sizeof(Node));
	tmp->next = *head;
	tmp->num = n;
	*head = tmp;
}


int pop(Node** head){
	Node* out;
	int num;
	if(*head == NULL){
		printf("error");
		exit(-1);
	}
	else{
		out = *head;
    	*head = (*head)->next;
    	num = out->num;
    	free(out);
    	return num;
	}
}


int size(const Node* head){
	int count = 0;
	while(head){
		count+=1;
		head=head->next;
	}
	return count;
}


int top(const Node* head){
	if(head != NULL){
		return head->num;
	}
	else{
		printf("error");
		exit(-1);
	}
}



int main(){
	Node* head = NULL;
	char str[4] = "";
	int k;
	while(1){
		scanf("%s", str);
		if(strstr(str, "push")){
			scanf(" %d\n", &k);
			push(&head, k);
			printf("ok\n");
		}
		if(strstr(str, "pop")){
			printf("%d\n", pop(&head));
		}
		if(strstr(str, "top")){
			printf("%d\n", top(head));
		}
		if(strstr(str, "size")){
			printf("%d\n", size(head));
		}
		if(strstr(str, "exit")){
			printf("bye");
			return 0;
		}
	}
	return 0;
}

/*int main(){
	Node* head = NULL;
	for(int i=0; i<5; i++){
		push(&head, i);
	}
	printf("size = %d\n", size(head));
	while (head){
        printf("%d ", top(head));
        printf("%d ", pop(&head));
    }
}
*/
