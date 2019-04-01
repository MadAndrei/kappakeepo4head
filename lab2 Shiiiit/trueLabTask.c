   
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// �������� ��������� MusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
}MusicalComposition;



// �������� ��������� MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author, int year){
    MusicalComposition *MuCon = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    MuCon->name =(char*)malloc((strlen(name)+1)*(sizeof(char)));
    MuCon->author =(char*)malloc((strlen(author)+1)*(sizeof(char)));
    strcpy(MuCon->name, name);
    strcpy(MuCon->author, author);
    MuCon->year = year;
    MuCon->prev = NULL;
    MuCon->next = NULL;         
    return MuCon;
}
// ������� ��� ������ �� ������� MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* MuCon;
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* tmp = head;
    for(int i = 1; i < n; i++){
        MuCon = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        MuCon->prev = tmp;
        tmp->next = MuCon;
        tmp = MuCon;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    while(head->next)
        head = head->next;
    MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    head->next = tmp;
    *(head->next) = *element;
    tmp->next = NULL;
    tmp->prev = head;
}

void removeEl(MusicalComposition** head, char* name_for_remove){
    MusicalComposition* tmp = (*head);
    while(tmp){
        if(!(strcmp(tmp->name, name_for_remove))){
            if(!(tmp->prev)){//������
                if(!(tmp->next)){//������������
                    free(*head);
                    *head = NULL;
                }
                else{
                    (*head)->next->prev = NULL;
                    (*head) = (*head)->next;
                    free(tmp);
                }
             }
            else{//�� ������
                 if(!(tmp->next)){//���������
                      tmp->prev->next = NULL;
                      free(tmp);
                  }
      
                 else{
                     tmp->prev->next = tmp->next;
                     tmp->next->prev = tmp->prev;
                     free(tmp);
                 }
            }
        } 
        tmp = tmp->next;
    }
}

int count(MusicalComposition* head){
    int i = 0;
    while(head){
        i++;
        head = head->next;
    }
    return i;
}

void print_names(MusicalComposition* head){
    while(head){
        printf("%s\n", head->name);
        head = head->next;
    }
}
    
    
int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(&head, name_for_remove); 
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}











/*void labTask(MusicalComposition* head, int length){
	MusicalComposition* tmp = head;
	MusicalComposition* temp = head;
	int k = 0;
	for(int i=length-1; i--; i>0){
		while(1){
			if(k == i){
				break;
			}
			temp = temp->next;
			k+=1;
		}
		k = 0;
		while(1){
			if(k == (i-1)){
				break;
			}
			tmp = tmp->next;
			k+=1;	
		}
		k = 0;
		temp->next = tmp;
	}
	tmp->next = NULL;
}
*/
