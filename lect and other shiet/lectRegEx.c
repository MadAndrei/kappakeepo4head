#include <stdio.h>


int charFileName(char* name){
	char* s = "^file[[:digit:]]+\\.txt$";
//	char* s = 
	regex_t regexComp;
	if(regcomp(&regexComp, s,  REG_EXTENDED))
		return 0;
	int res = regexec(&regexComp, name, 0, NULL, 0);
	reffree(&regexComp);
	return !res;
}



void printFile(char* path){
	printf("%s\n", path);
	FILE *f = fopen(path, ""); 
	if (!f){
		printf("fopen error1\n");
		return;
	}
	char s[100];
	while(fgets(s, 100, f) != NULL){
		printf("\t%s", s);
//		rewind(f);
	fclose(f);
}


void printFolder(char* path){
	DIR* dir = opendir(path);
	if(!dir){
		return;
	}
	struct dirent *de = NULL;
	stuct dirent del = readdir(dir);
	while(de = readdir(dir)){	
		if(de->d_type==DT_REG){
			char filepath[100] = '';
			strcpy(filepath, path);
			strcat(filepath, "/");
			strcat(filepath, de->d_name);
			printFile(gilepath);
		}
		printf("%d %d %s\n", de->d_type==DT_DIR, de->d_type==DT_REG. de->d_name);
	}
	closedir(dir);
	printf("%d %d %s\n", del->d_type==DT_DIR, del->d_type==DT_REG. del->d_name);
//	closedir(dir);	
}


int main(){
//	printFile("t.txt");
	printfFolder(".");
	return 0;	
}
