#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
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


int isNumeric(char* str){
	int i = 0;
	if(str[0] == '-'){
		i++;
	}
	for(i; i<strlen(str); i++){
		if(!(isdigit(str[i]))){
			return 0;
		}
	}	
	return 1;
}


void printHelp(){
	printf("Info\n");
    printf("--copy(-c) - Do copy of highlighted area which define by -S and -E\n");
    printf("--reflect(-r) - Reflecting marked area which define by -S and -E, axis of symmetry define by -M\n");
    printf("--draw_circle(-d) - Drawing circle which define by radius -R, starting coords -S, colour of board and colour inside circle -C, -K\n");
    printf("--start(-S) - Define the coordinates of the upper left point\n");
    printf("--end(-E) - Define the coordinates of the lower right point\n");
    printf("--color(-C) - Define colour: red, green, blue, white, black, orange, purple, brown, yellow\n");
    printf("--reflmod(-M) - Define  axis of symmetry (horizontal and vertical)\n");
    printf("--width(-W) - Define width of cirle\n");
    printf("--radius(-R) - Define radius of circle\n");
    printf("--fill(-F) - Define whether to fill the area\n");
    printf("--newcoord(-N) - Define the coordinates of the upper left point of the copy area\n");
    printf("--info(-i) - Print info about BMP file\n");	
}

#pragma pack (pop)

int main(int argc, char **argv){
	char name[100] = "./";
	strcat(name, argv[1]);
	PictureBmp* tmp = readBmp(name);
	char bordColour[13] = "";
	char fillColour[13] = "";
	int mod;
	uint8_t isFilled;
	uint32_t centrX, centrY, radius, centr2X, centr2Y, centr3X, centr3Y;
	uint32_t radiusFilled = 0;
	Colour anotherColour;
	 Colour anotherColour_;
	
	int opt = 0;
	int longIndex = 0;
	int flag = 0;
	char *optstring = "drcN:M:E:M:f:K:R:S:C:W:hi";
	
	
	struct option longOpts[] = {
        {"reflect", no_argument, &flag, 'r'},
        {"copy", no_argument, &flag, 'c'},
        {"draw_circle", no_argument, &flag, 'd'},
        {"help", required_argument, &flag, 'h'},
        {"start", required_argument, NULL, 'S'}, 
        {"end", required_argument, NULL, 'E'},
        {"color", required_argument, NULL, 'C'},
        {"width", required_argument, NULL, 'W'},
        {"radius", required_argument, NULL, 'R'},
        {"info", required_argument, &flag, 'i'},
    	{"fill", required_argument, NULL, 'F'},
    	{"color2", required_argument, NULL, 'K'},
    	{"reflmod", required_argument, NULL, 'M'},
    	{"newcoord", required_argument, NULL, 'N'},
        {NULL, 0, NULL, 0}
    };
	

	opt = getopt_long(argc, argv, optstring , longOpts, &longIndex);
	
	
	
	    while( opt != -1 ){
        switch( opt ){
            case 'E':
                
                if(!isNumeric(optarg))
                {
                    printf("%s - NOT a REQUIRED NUMBER\n", optarg);
                    return 0;
                }
                
                if(!isNumeric(argv[optind]))
                {
                    printf("%s - NOT a REQUIRED NUMBE\n", argv[optind]);
                    return 0;
                }

                centr2X = (uint32_t)atoi(optarg);
                centr2Y = (uint32_t)atoi(argv[optind]);
 
                break;
                
                
            case 'N':
                
                if(!isNumeric(optarg))
                {
                    printf("%s - NOT a REQUIRED NUMBER\n", optarg);
                    return 0;
                }
                
                if(!isNumeric(argv[optind]))
                {
                    printf("%s - NOT a REQUIRED NUMBE\n", argv[optind]);
                    return 0;
                }

                centr3X = (uint32_t)atoi(optarg);
                centr3Y = (uint32_t)atoi(argv[optind]);
 
                break;
            
            case 'S':

                if(!isNumeric(optarg)){
                    printf("%s - NOT a REQUIRED NUMBER\n", optarg);
                    return 0;
                }
                if(!isNumeric(argv[optind])){
                    printf("%s - NOT a REQUIRED NUMBER\n", argv[optind]);
                    return 0;
                }
              
                centrX = (uint32_t)atoi(optarg);
                centrY = (uint32_t)atoi(argv[optind]);

                break;

            case 'R':
                
                if(!isNumeric(optarg)){
                    printf("%s - NOT a REQUIRED NUMBER\n", optarg);
                    return 0;
                }
               
                radius = (uint32_t)atoi(optarg);
                
                break;
            
            case 'W':
                
                if(!isNumeric(optarg)){
                    printf("%s - UDu HAXYN\n", optarg);
                    return 0;
                }
                
                radiusFilled = (uint32_t)atoi(optarg);
                
                break;

            case 'C':
                
                anotherColour = createColour(optarg);
                
                break;
                
                
            case 'M':
                
                if(!(strcmp("vertical", optarg))){
                	isFilled = 1;
				}
				else{
					if(!(strcmp("horizontal", optarg))){
						isFilled = 0;
					}
					else{
						printf("%s - Bbl BBEJlU XUNHI0\n", optarg);
                    	return 0;
					}
				}
                
                break;


			case 'K':
            
                anotherColour_ = createColour(optarg);
                
                break;
                  
           case 'h':
                printHelp();
                break;
                
            case 'i':
                flag = 'i';
                break;

			case 'F':
			
                if(!(strcmp("yes", optarg))){
                	isFilled = 1;
				}
				else{
					if(!(strcmp("no", optarg))){
						isFilled = 0;
					}
					else{
						printf("%s - Bbl BBEJlU XUNHI0\n", optarg);
                    	return 0;
					}
				}
                break;

            case 'r':
                flag = 'r';
                break;
            
            case 'c':
                flag = 'c';
                break;
            
            case 'd':
                flag = 'd';
                break;
        }
           
        opt = getopt_long(argc, argv, optstring , longOpts, &longIndex);
        
    }
	
	
	
	
 switch(flag){
        case'r':

            if(centrX < 0 || 
               centrY < 0 || 
               centr2X > tmp->header.width_px || 
               centr2Y > (tmp->header.height_px - 1) ||
               centrX >= centr2X || 
               centrY >= centr2Y )
               {
                   printf("Bbl DayHrrrrr\n");
                   break;
               }
            else
            {
                reflectBmp(tmp, centrX, centrY, centr2X+1, centr2Y+1, isFilled);
            }
            
        break;

        case'c':

            if(centrX < 0 || 
               centrY < 0 || 
               centr2X > tmp->header.width_px || 
               centr2Y > (tmp->header.height_px - 1) ||
               centrX > centr2X || 
               centrY > centr2Y ||
			   centr2Y > centr3Y||
			   centr2X > centr2X)
               {
                   printf("Bbl ne prowli proverku na c\n");
                   break;
               }
            else
            {
                copyBmp(tmp, centrX, centrY, centr2X+1, centr2Y+1, centr3X, centr3Y);
            }
           
        break;

        case'd':

            if(centrX < 0 || 
               centrY < 0 || 
               centrX + radius > tmp->header.width_px || 
               centrY + radius > (tmp->header.height_px - 1 ) ||
               centrX - radius < 0 ||
               centrY - radius < 0 ||
               radius <= 0 ||
               radiusFilled > radius ||
               radiusFilled < 0)
               {
                   printf("Bbl DAyH))))))00))\n");
                   break;
               }
            else
            {
                drawCircle(tmp, centrX, centrY, radius, anotherColour, anotherColour_, radiusFilled, isFilled);
            }
            
        break;

        case 'i':
        	
        	BMPPrintInfo(tmp);
          	
        break;
    }
	
	writeBmp(argv[argc-1], tmp);
	system("pause");
}
