#include <stdio.h> // ����� ����� ���� �������� �� ����������
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED "\033[0;31m"
#define NONE "\033[0m"

char** input(char **text, int *sentence);
char** deleteSameSentences(char** text, int *sentence);
char** bombDefusing(char** text, int *sentence); // �� ������ ������������ ������ � �������� ��� 
char** findStudents(char** text, int* sentence);
char** deleteDoubleEnemy(char** text, int* sentence);
void output(char ***text, int *sentence);
void menu(char*** text, int* sentence);


int main (void) {
  char** text = (char**)malloc(sizeof(char*));
  int sentence = 0;
  printf("������� ���-������ (�����)");
  text = input(text, &sentence);
  text = deleteSameSentences(text, &sentence);
  menu(&text, &sentence);
}

char** input(char** text, int* sentence){ // �������� 
	int slen = 70;
	char ch;
 	int symb = 0;

	while (ch != '\n'){
		text[*sentence] = (char*)malloc(slen * sizeof(char));
		while (ch != '.' && ch != '\n'){
			ch = getchar();
			if (ch == '\n'){
				break;
			}
			if (symb >= slen - 1){
				slen += 70;
				text[*sentence] = (char*)realloc(text[*sentence], slen * sizeof(char));
			}
			text[*sentence][symb++] = ch;
		}
		if (ch == '\n'){
			break;
		}
		ch = '\0';
		text[*sentence][symb] = ch;
		*sentence += 1;
		text = (char**)realloc(text, (*sentence + 1) * sizeof(char*));
		symb = 0;
		slen = 70;
	}
	return text;
}


char** deleteSameSentences(char** text, int *sentence){ // ��������(��� �� �������)
  int firstToCheck, secondToCheck, k;
  int checker = 0;
  for (firstToCheck=0; firstToCheck<*sentence-1; firstToCheck++){
    for (secondToCheck=firstToCheck+1; secondToCheck<*sentence; secondToCheck++){
      if (strlen(text[firstToCheck]) == strlen(text[secondToCheck])){
        checker = 0;
        for (k=0; k<strlen(text[firstToCheck]); k++){
          if (tolower(text[firstToCheck][k]) != tolower(text[secondToCheck][k])){
            checker = -1;
            break;
          }
        }
        if (checker == 0){
          free(text[secondToCheck]);
          for (int i=secondToCheck; i<*sentence; i++){
            text[i]=text[i+1];
          }
          text[*sentence - 1] = NULL;
          secondToCheck-=1;
          *sentence-=1;
        }
      }
    }
  }
  return text;
}


char** bombDefusing(char** text, int *sentence){ // �� ������ ������������ ������ � �������� ��� 
  int firstToCheck, k;
  for (firstToCheck=0; firstToCheck<*sentence; firstToCheck++){
    for (k=0; k<strlen(text[firstToCheck]); k++){
      printf("%c\n",text[firstToCheck][k] );
      if ((text[firstToCheck][k] == 'b') && (text[firstToCheck][k+1] == 'o') && (text[firstToCheck][k+2] == 'm') && (text[firstToCheck][k+3] == 'b')){
        text[firstToCheck][k] = 'd';
        text[firstToCheck][k+1] = 'e';
        text[firstToCheck][k+2] = 'f';
        text[firstToCheck][k+3] = 'u';
        printf("��� �� vol if\n");
      }
    }
  }
  return text;
}

char** findStudents(char** text, int* sentence){ // ����� ������
  int firstToCheck, k, i;
  int counter = 0;
  for (firstToCheck=0; firstToCheck<*sentence; firstToCheck++){
    for (k=0; k<strlen(text[firstToCheck]); k++){
      if ((text[firstToCheck][k] == 's') && (text[firstToCheck][k+1] == 't') && (text[firstToCheck][k+2] == 'u') && (text[firstToCheck][k+3] == 'd') && (text[firstToCheck][k+4] == 'e') && (text[firstToCheck][k+5] == 'n') && (text[firstToCheck][k+6] == 't') && ((text[firstToCheck][k+7] == ' ') || (text[firstToCheck][k+7] == '.') || (text[firstToCheck][k+7] == ','))) {
        counter += 1;
      }
    }
    printf("%d\n", counter);
    for (i=0; i<strlen(text[firstToCheck]); i++){
      if ((text[firstToCheck][k] == 's') && (text[firstToCheck][k+1] == 't') && (text[firstToCheck][k+2] == 'u') && (text[firstToCheck][k+3] == 'd') && (text[firstToCheck][k+4] == 'e') && (text[firstToCheck][k+5] == 'n') && (text[firstToCheck][k+6] == 't') && ((text[firstToCheck][k+7] == ' ') || (text[firstToCheck][k+7] == '\n'))){
        printf("%s%c%s", RED, text[firstToCheck][i], NONE);
        printf("%s%c%s", RED, text[firstToCheck][i+1], NONE);
        printf("%s%c%s", RED, text[firstToCheck][i+2], NONE);
        printf("%s%c%s", RED, text[firstToCheck][i+3], NONE);
        printf("%s%c%s", RED, text[firstToCheck][i+4], NONE);
        printf("%s%c%s", RED, text[firstToCheck][i+5], NONE);
        printf("%s%c%s", RED, text[firstToCheck][i+6], NONE);
        i+=6;
      }
      else{
        printf("%c", text[firstToCheck][i]);
      }
    }
    counter = 0;
  }
}

char** deleteDoubleEnemy(char** text, int* sentence){ // ���� ����� � �������, �� � �����, �����, ������
  int firstToCheck, k, i;
  int counter = 0;
  for (firstToCheck=0; firstToCheck<*sentence; firstToCheck++){
    for (k=0; k<strlen(text[firstToCheck]); k++){
      if ((text[firstToCheck][k] == 'e') && (text[firstToCheck][k+1] == 'n') && (text[firstToCheck][k+2] == 'e') && (text[firstToCheck][k+3] == 'm') && (text[firstToCheck][k+4] == 'y') && ((text[firstToCheck][k+5] == ' ') || (text[firstToCheck][k+5] == '.') || (text[firstToCheck][k+5] == ','))) {
        counter += 1;
      }
    }
    if (counter > 1){
      free(text[firstToCheck]);
        for (i=firstToCheck; i<*sentence; i++){
          text[i]=text[i+1];
        }
        text[*sentence - 1] = NULL;
        firstToCheck-=1;
        *sentence-=1;
    }
  }
  return text;
}

void output(char ***text, int *sentence){
	for (int i = 0; i < *sentence; i++){
/*		if ((*text)[i] != NULL){
			printf("%s", (*text)[i]);
		}
	}
	if (*sentence == 0){
		printf("����������� ��� ");
	}
	printf("\n");
  */
  printf("%s", (*text)[i]);}
}

void menu(char*** text, int* sentence){
  printf("������� ��-����))00))");
  int firstSymb;
  char secondSymb;
  scanf("%d", &firstSymb);
  if (firstSymb == 1){
    bombDefusing(text, sentence);
    output(text, sentence);
  }
 // secondSymb=getchar();
  //if (secondSymb != '\n'){
    //firstSymb = -1;
  //}
  //else{
    /*switch(firstSymb){
      case'1':
        bombDefusing(text, sentence);
        output(text, sentence);
        break;
      case'2':
        findStudents(text, sentence);
        break;
      case'3':
        deleteDoubleEnemy(text, sentence);
        output(text, sentence);
        break;
      case'4':
        output(text, sentence);
    }*/
  //}
}