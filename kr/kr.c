#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#define pow_(x)  ( (x)*(x) )

#pragma pack (push, 1)


typedef struct{              	// Total: 54 bytes
	uint16_t  type;             //00-02	// Magic identifier: 0x4d42
	uint32_t  size;             //02-06	// File size in bytes
	uint16_t  reserved1;        //06-08	// Not used
	uint16_t  reserved2;        //09-0a	// Not used	
	uint32_t  offset;           //0a-0e	// Offset to image data in bytes from beginning of file (54 bytes)
	uint32_t  dib_header_size;  //0e-12	// DIB Header size in bytes (40 bytes)
	int32_t   width_px;         //12-16	// Width of the image
	int32_t   height_px;        //16-1a	// Height of image
	uint16_t  num_planes;       //1a-1c	// Number of color planes
	uint16_t  bits_per_pixel;   //1c-1e	// Bits per pixel
	uint32_t  compression;      //1e-22	// Compression type
	uint32_t  image_size_bytes; //22-26	// Image size in bytes
	int32_t   x_resolution_ppm; //26-2a	// Pixels per meter
	int32_t   y_resolution_ppm; //2a-2e	// Pixels per meter
	uint32_t  num_colors;       //2e-32	// Number of colors  
	uint32_t  important_colors; //32-36	// Important colors 
} BMPHeader;


typedef struct{
	BMPHeader header;
	uint8_t value[];
}PictureBmp;



typedef struct{
	uint8_t b;
	uint8_t g;
	uint8_t r;
}Colour;



void BMPPrintInfo(PictureBmp* image) {
	BMPHeader* header = &image->header;
	printf("\ntype %u\n", header->type);
	printf("size %u\n", header->size);
	printf("reserved1 %u\n", header->reserved1);
	printf("reserved2 %u\n", header->reserved2);
	printf("offset %u\n", header->offset);
	printf("dib_header_size %u\n", header->dib_header_size);
	printf("width_px %u\n", header->width_px);
	printf("height_px %u\n", header->height_px);
	printf("num_planes %u\n", header->num_planes);
	printf("bits_per_pixel %u\n", header->bits_per_pixel);
	printf("compression %u\n", header->compression);
	printf("image_size_bytes %u\n", header->image_size_bytes);
	printf("x_resolution_ppm %u\n", header->x_resolution_ppm);
	printf("y_resolution_ppm %u\n", header->y_resolution_ppm);
	printf("num_colors %u\n", header->num_colors);
	printf("important_colors %u\n", header->important_colors);
	//printf("Dim %uX%u\n", header->width_px, header->height_px);
	//printf("BPP %hu\n", header->bits_per_pixel);
}

PictureBmp* readBmp(char* name){
	FILE* ptr = fopen(name, "rb");
	fseek(ptr, 0, SEEK_END); // going to the end of file
	long len = ftell(ptr); // lenght of file
	uint8_t* file = (uint8_t*)malloc(len);
	fseek(ptr, 0, SEEK_SET);
	fread(file, len, 1, ptr);
	fclose(ptr);
			// check if is it BMP
	
	
	
	return (PictureBmp*)file; // cast to pictires(in fact no)
}


void writeBmp(char* name, PictureBmp* data){
	FILE* ptr = fopen(name, "wb");
	fwrite(data, data->header.size, 1, ptr);
	fclose(ptr);	
}

Colour getPixel(PictureBmp* image, uint32_t x, uint32_t y){
	y = image->header.width_px-1-y;
	size_t ySet = y*(image->header.width_px*3+(image->header.width_px%4));
	size_t xSet = x*3;
	return *(Colour*)(image->value+ySet+xSet);
}


void setPixel(PictureBmp* image, uint32_t x, uint32_t y, Colour colour){
	y = image->header.width_px-1-y;
	size_t ySet = y*(image->header.width_px*3+(image->header.width_px%4));
	size_t xSet = x*3;
	*(Colour*)(image->value+ySet+xSet) = colour;
}


void drawCircle(PictureBmp* image, uint32_t x, uint32_t y, uint32_t r, Colour colourBord, Colour colourCircle, uint32_t width, uint8_t filled){
	for(int i = 0; i< image->header.width_px; i++){
		for(int j = 0; j < image->header.height_px; j++){
			if((pow_(i-x) + pow_(j-y)) < pow_(r)){
				if(pow_(i-x) + pow_(j-y) < pow_(r-width)){
					if(filled){
						setPixel(image, i, j, colourCircle);
					}
				}
				else{
					setPixel(image, i, j, colourBord);
				}
			}
		}
	}
}


void reflectBmp(PictureBmp* image, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t choice){
	Colour pixel1, pixel2;
	if(choice){
		for(int i = 0; i<(image->header.width_px); i++){
			for(int j = 0; j<image->header.height_px; j++){
				if((i>x1) && (j>y1) && (i<x1+(x2-x1)/2) && (j<y2)){
					pixel1 = getPixel(image, i, j);
					pixel2 = getPixel(image, x2-1-i+x1, j);
					setPixel(image, i, j, pixel2); 
					setPixel(image, x2-1-i+x1, j, pixel1);
				}
			}
		}
	}
	else{ // don't work, rewrite
		for(int i = 0; i<(image->header.width_px); i++){
			for(int j = 0; j<image->header.height_px; j++){
				if((i>x1) && (j>y1) && (i<x2) && (j<y1+(y2-y1)/2)){
					pixel1 = getPixel(image, i, j);
					pixel2 = getPixel(image, i, y2-1-j+y1);
					setPixel(image, i, j, pixel2);
					setPixel(image, i, y2-1-j+y1, pixel1);
				}
			}
		}
	} // until this
}


void copyBmp(PictureBmp* image, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x4, uint32_t y4){
	uint32_t x3, y3;
	Colour** ptr = (Colour**)malloc((x2-x1)*sizeof(Colour*));
	for(int i = 0; i<x2-x1; i++){
		ptr[i] = (Colour*)malloc((y2-y1)*sizeof(Colour));
	}
	for(int i = x1; i<x2; i++){
		for(int j = y1; j<y2; j++){
			ptr[i-x1][j-y1] = getPixel(image, i, j);
		}
	}
	for(int i = x4; i<x4+(x2-x1); i++){
		for(int j = y4; j<y4+(y2-y1); j++){
			setPixel(image, i, j, ptr[i-x4][j-y4]);
		}
	}
}


Colour createColour(char* str){
	if(!strcmp(str, "red")){
		Colour pixel = {0, 0, 255};
		return pixel;
	}
	if(!strcmp(str, "green")){
		Colour pixel = {0, 128, 0};
		return pixel;
	}
	if(!strcmp(str, "blue")){
		Colour pixel = {255, 0, 0};
		return pixel;
	}
	if(!strcmp(str, "brown")){
		Colour pixel = {0, 75, 150};
		return pixel;
	}
	if(!strcmp(str, "black")){
		Colour pixel = {0,0,0};
		return pixel;
	}
	if(!strcmp(str, "purple")){
		Colour pixel = {100, 0, 100};
		return pixel;
	}
	if(!strcmp(str, "yellow")){
		Colour pixel = {0, 255, 255};
		return pixel;
	}
	if(!strcmp(str, "orange")){
		Colour pixel = {40, 135, 255};
		return pixel;
	}
	if(!strcmp(str, "white")){
		Colour pixel = {255, 255, 255};
		return pixel;
	}
	Colour pixel = {255,255,255};
	return pixel;
}

#pragma pack (pop)

int main(){
	PictureBmp* tmp = readBmp("./new.bmp");
	BMPPrintInfo(tmp);
	char bordColour[13] = "";
	char fillColour[13] = "";
	int mod;
	uint8_t isFilled;
	uint32_t centrX, centrY, radius, centr2X, centr2Y, centr3X, centr3Y;
	uint32_t radiusFilled = 0;
	
	printf("vvedite 4to hotite delat' 1 - krug, 2 - reflect, 3 - copy:\n");
	
	scanf("%d", &mod);
	
	if(mod == 1){
		printf("Vvedite zapolnyat' li:\n"); //
						
		scanf("%" SCNu8, &isFilled);
		
		printf("Coord centra po x:\n");
		
		scanf("%" SCNd32, &centrX);
		
		printf("Coord centra po y:\n");
		
		scanf("%" SCNd32, &centrY);
		
		printf("Vvedite radius:\n");
		
		scanf("%" SCNd32, &radius);
		
		printf("Vvefite radius zapolneniya:\n");
			
		scanf("%" SCNd32, &radiusFilled);
		
		printf("Vvedite cvet granitsi:\n");
		
		scanf("%s", bordColour);
		if(isFilled){
			printf("Vvedite cvet zapolneniya:\n");
			
			scanf("%s", fillColour);
		}
		drawCircle(tmp, centrX, centrY, radius, createColour(bordColour), createColour(fillColour), radiusFilled, isFilled);
	}


	if(mod == 2){
		printf("Viberete vid simmetrii :\n");
						
		scanf("%s", bordColour);
		
		if(!strcmp(bordColour, "vertical")){
			isFilled = 1;
		}
		else{
			isFilled = 0;
		}
		
		printf("Coord pervoi to4ki po x:\n");
		
		scanf("%" SCNd32, &centrX);
		
		printf("Coord pervoi to4ki po y:\n");
		
		scanf("%" SCNd32, &centrY);
		
		printf("Coord vtoroi to4ki po x:\n");
		
		scanf("%" SCNd32, &centr2X);
		
		printf("Coord pervoi vtoroi po y:\n");
		
		scanf("%" SCNd32, &centr2Y);
		
		reflectBmp(tmp, centrX, centrY, centr2X+1, centr2Y+1,  isFilled);
	}
	
	
	if(mod == 3){
		
		printf("Coord pervoi to4ki po x:\n");
		
		scanf("%" SCNd32, &centrX);
		
		printf("Coord pervoi to4ki po y:\n");
		
		scanf("%" SCNd32, &centrY);
		
		printf("Coord vtoroi to4ki po x:\n");
		
		scanf("%" SCNd32, &centr2X);
		
		printf("Coord pervoi vtoroi po y:\n");
		
		scanf("%" SCNd32, &centr2Y);
		
		printf("Coord tretiei to4ki po x:\n");
		
		scanf("%" SCNd32, &centr3X);
		
		printf("Coord tretiei to4ki po y:\n");
		
		scanf("%" SCNd32, &centr3Y);
		
		copyBmp(tmp, centrX, centrY, centr2X+1, centr2Y+1, centr3X, centr3Y);
	}
	
	
	Colour tmpColour = {0,0,0};
	Colour tmpColour_ = {255, 0 , 0};
//	setPixel(tmp, 10, 6, tmpColour_);
//	drawCircle(tmp, centrX, centrY, radius, createColour(bordColour), createColour(fillColour), radiusFilled, isFilled);
//	drawCircle(tmp, 200, 200, 70, test1, test2, 20, isFilled);
//	drawCircle(tmp, 100, 100, 50, tmpColour, tmpColour_, 1, 0);
//	reflectBmp(tmp, centrX, centrY, centr2X+1, centr2Y+1,  isFilled); // +1 po koord vtorogo ugla
//	reflectBmp(tmp, 6, 7, 23, 22,  0); // +1 po koord vtorogo ugla
//	copyBmp(tmp, 6, 7, 13, 14, 20, 20); // +1 po koord vtoroi to4ki
	writeBmp("./12345.bmp", tmp);
}
