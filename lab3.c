#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


void list_dir(const char *dirPath){
    DIR *dir = opendir(dirPath); 
	     что- то объ€вил chto-to obyavil
    if(dir) {
        struct  dirent *de = readdir(dir); 
        while (de) {    
			скеливаю им€    skleivayu imya        
            FILE* tempFile = fopen(strcat(str));
            if (tempFile){
            	fscanf( )
            	записали в массив строк zapisali v massive strok
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
