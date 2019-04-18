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
	out = *head;
	*head = (*head)->next;
	num = out->num;
	free(out);
    return num;
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
	return head->num;
}


int isEmpty(Node* head){
	if(head == NULL){
		return 0;
	}
	else{
		return 1;
	}
}

int main(){
	Node* head = NULL;
	char str[4] = "";
	int k;
	while(1){
		scanf("%s", str);
		if(!strcmp(str, "push")){
			scanf(" %d", &k);
			push(&head, k);
			printf("ok\n");
		}
		else{
			if(!strcmp(str, "pop")){
				if(isEmpty(head)){
					printf("%d\n", pop(&head));
				}
				else{
					printf("error");
					return 0;
				}
			}
			else{
				if(!strcmp(str, "top")){
					if(isEmpty(head)){
					printf("%d\n", top(head));
					}
					else{
						printf("error");
						return 0;
					}
				}
				else{
					if(!strcmp(str, "size")){
						printf("%d\n", size(head));
					}
					else{
						if(!strcmp(str, "exit")){
							printf("bye\n");
//							printf("%d", isEmpty(head));
							return 0;
						}
						else{
							return 0;
						}
					}
				}
			}
		}
	}
	return 0;
}
