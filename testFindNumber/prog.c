#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<string.h>
#include <ctype.h>


#define STRLEN 100
#define STRBLOCK 10



int findNumbers(char* strs){
// 	printf("enter into func\n");
	char newStr[STRBLOCK] = "";
	int k = 0;
	while(1){
		if (isdigit(strs[k])){
  //   			printf("is digit works k = %d\n", k);
			newStr[k] = strs[k];
    // 			 printf("strs[k] = %c\n", strs[k]);
      //			printf("newStr[k] = %c\n", newStr[k]);
			k+=1;
		}
		else{
     	//		printf("break works!\n");
	  		break;
		}
	}
 //	puts(newStr);
  //	printf("%d\n", atoi(newStr));
	return (atoi(newStr));
}


int main(){
	char* c = 0;
	char buf[STRLEN];
	char** strs = NULL;
	int i = 0;
	FILE* ptrFile = fopen("hhh.txt", "r");
	while(strcmp(c = fgets(buf,STRLEN,ptrFile) , "\n")){
//    		puts(c);
		*strchr(buf,'\n')='\0';
		if(!(i%STRBLOCK))strs = realloc(strs,(i+STRBLOCK)*sizeof(char*));
		strs[i]=malloc(STRLEN * sizeof(char));
		strcpy(strs[i],buf);
		i++;
	}
	for(int j = 0; j < i; j++){
		printf("%s\n", strs[j]);
		printf("%d\n", findNumbers(strs[j]));
	}
 	 return 0; 
}
