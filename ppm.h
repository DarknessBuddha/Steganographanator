#ifndef PA2_PPM_H
#define PA2_PPM_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Header{
    char type[3];
    int height;
    int width;
    int maxColor;
}Header;

typedef struct Pixel{
    unsigned char red, green, blue;
}Pixel;

typedef struct Image{
    int height, width;
    Pixel** pixels;
}Image;

// headers
Header makeHeader(FILE* file);
void handleSpacesAndComments(FILE* file);
void discardComments(FILE* file);
void writeHeader(Header header, FILE* file);

// images
Image makeImage(Header header, FILE* file);
void freeImage(Image image);
void writeImage(Image image, FILE* file);

#endif //PA2_PPM_H
