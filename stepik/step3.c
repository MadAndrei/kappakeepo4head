#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int count(char* str){
	char tmp[200] = "";
	int k = 0;
	int count = 0;
	int* arr = NULL;
	int kk = 0;
	char** newStr = (char**)malloc(200*sizeof(char*));
	while(1){
		if(str[kk] == ' '){
			kk++;
		}
		else{
			break;
		}
	}
	for(int i=kk; i< strlen(str); i++){
		if(((str[i-1] == ' ') && (str[i] != ' ') && (str[i] != '\n') && (str[i] != '\0')) || (i == 0)){
			while(str[i] != ' ' ){
				if((str[i] != '\n') && (str[i] != '\0')){
					tmp[k] = str[i];
					k++;
					i++;
				}
				else{
					break;
				}
			}
			k = 0;
			newStr[count] = (char*)malloc((k+2)*(sizeof(char)));
			strcpy(newStr[count], tmp);
			memset(tmp, 0, 200);
			count++;
		}
	}
	arr = (int*)calloc(count, sizeof(int));
	for(int j=0; j<count; j++){
		for(int y = 0; y<count-1; y++){
			if(!strcmp(newStr[j], newStr[y])){
				arr[j] = arr[j]+1;
			}
		}
	}
	int max = 0;
	for(int j=0; j<count; j++){
		if(arr[j]>=max){
			max = arr[j];
		}
	}
	return max;
}

int main(){
	int res;
	char str[201] = "";
	fgets(str, 201, stdin);
	res = count(str);
	printf("%d", res);
}
