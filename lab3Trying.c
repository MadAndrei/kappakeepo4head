#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<string.h>
#include <ctype.h>



int findNumbers(int i, strArr[][]){
	char newStr[100] = "";
	int j = 0;
	while(1){
		if (isdigit(strArr[i][j])){
			newStr[j] = strArr[i][j];
			j+=1;
		}
		else{
			break;
		}
	}
	return (atoi(newStr));
}


void list_dir(const char *dirPath){
    DIR *dir = opendir(dirPath); 
	//     что- то объ€вил chto-to obyavil
    if(dir) {
        struct  dirent *de = readdir(dir); 
        while (de) {
			char* str = malloc(strlen(dirPath) + strlen(de->d_name) + 1);
	        strcpy(str,dirPath);
			strcat(str, "/");
			strcat(str, de->d_name);
            FILE* tempFile = fopen(str, "r");
            if (tempFile){ // esli file otkrilysa 
            	fscanf(tempFile,"%s",  ); // zapisivaem v massive strok
            	fclose(tempFile);
			}
			else{
				if (!strchr(de->name, '.'))
					list_dir(str, strArr);
				}
			de = readdir(dir);
            
        }
    }
    closedir(dir);               
}


int main(){
	
	
	
}
