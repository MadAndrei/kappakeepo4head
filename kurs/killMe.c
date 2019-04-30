#include <stdio.h>
 

int openBMP(char* path);
int saveBMP(char* path);


#pragma pack(push, 2)


struct BmpHeader {
    unsigned char b1, b2; 
    unsigned long size; 
    unsigned short notUse1; 
    unsigned short notUse2; 
    unsigned long massPos; 
 
    unsigned long headerLength; 
    unsigned long width; 
    unsigned long height; 
    unsigned short colorPlaneNumber; 
    unsigned short bitPixel; 
    unsigned long compressMethod; 
    unsigned long massLength; 
    unsigned long massWidth; 
    unsigned long massHeight; 
    unsigned long colorNumber; 
    unsigned long generalColorNumber; 
 
} bmpHeader;


#pragma pack(pop)
 
 
unsigned char** img;


int main(void)
{
 
    if (readBMP("E:\\1.bmp") == 0) {
        printf("bad path");
        return 0;
    }
 
    if (saveBMP("E:\\_1.bmp") == 0) {
        printf("bad path");
        return 0;
    }
    return 0;
}
 
int readBMP(char* path) {
    FILE* file;
    int i, j;
    unsigned char** img = NULL;
    file = fopen(path,"rb");
    if(file == NULL) return 0;
    fread(&bmpHeader, sizeof(bmpHeader), 1, file);
    if (bmpHeader.b1 != 'B' || bmpHeader.b2 != 'M' || bmpHeader.bitPixel != 24) {
        printf("corrupted file");
        return 0;
    }
    img = (unsigned char**)calloc(bmpHeader.width, sizeof(*img));
    for(i = 0; i < bmpHeader.width; ++i)
        img[i] = (unsigned char*)calloc(bmpHeader.height, sizeof(*img[i]));
    for (i = 0; i < bmpHeader.width; i++) {
        for (j = 0; j < bmpHeader.height; j++) {
            fread(&img[i][j], sizeof(img[i][j]), 1, file);
        }
    }
 
    fclose(file);
    return 1;
}
 
int saveBMP(char* path) {
    FILE* file;
    int i, j;
    file = fopen(path,"wb");
    if(file == NULL) return 0;
    fwrite(&bmpHeader, sizeof(bmpHeader), 1, file);
    for (i = 0; i < bmpHeader.width; i++) {
        for (j = 0; j < bmpHeader.height; j++) {
            fwrite(&img[i][j], sizeof(img[i][j]), 1, file);
        }
    }
    fclose(file);
    return 1;
}


