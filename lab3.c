#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


void list_dir(const char *dirPath){
    DIR *dir = opendir(dirPath); 
	     ���- �� ������� 
    if(dir) {
        struct  dirent *de = readdir(dir); 
        while (de) {    
			�������� ���            
            FILE* tempFile = fopen(strcat(str));
            if (tempFile){
            	fscanf( )
            	�������� � ������ �����
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
