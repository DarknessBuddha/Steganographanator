/************************* 
 *Ivan Lin and Lucia Wang
 *CPSC 2310 F22 Section 4:30 and 2:00
 *lucia2@clemson.edu and ilin@clemson.edu
 *************************/ 

#include "ppm.h"
// headers
Header getHeader(FILE* file){
    Header header;

    // scan ppm type and skips spaces and comments
    fscanf(file, "%2s ", header.type);
    handleSpacesAndComments(file);

    //Gets the width and skips spaces and comments
    fscanf(file, "%d", &header.width);
    handleSpacesAndComments(file);

    //Gets the height and skips spaces and comments
    fscanf(file, "%d", &header.height);
    handleSpacesAndComments(file);

    //Gets the max color
    fscanf(file, "%d ", &header.maxColor);

    return header;
}

void handleSpacesAndComments(FILE* file){
    int buffer;
    do{
        // skip spaces
        while ((buffer = (fgetc(file))) != EOF && isspace(buffer));
        // check for comment
        if(buffer == '#') discardComments(file);
    } while (!isdigit(buffer));
    ungetc(buffer, file);
}

void discardComments(FILE* file){
    int buffer;
    //While not end of line or a new line character,
    //moves the file pointer ahead
    while ((buffer = (fgetc(file))) != EOF && buffer != '\n');
}

void writeHeader(Header header, FILE* file){
    //Prints out the header info to the outfile
    fprintf(file, "%s %d %d %d\n",
            header.type, header.width,
            header.height, header.maxColor
    );
}

Image makeImage(int height, int width){
    //Initializes variables to information passed in
    Image image;
    image.height = height;
    image.width = width;

    //Allocates space for pixel pointers
    image.pixels = (Pixel**) malloc(sizeof(Pixel*) * height);
    //Loops through and allocates space for width pixels
    for(int i = 0; i < height; i++){
        image.pixels[i] = (Pixel*) malloc(sizeof(Pixel) * width);
    }
    return image;
}

Image getImage(Header header, FILE* file){
    //Makes an image
    Image image;
    image = makeImage(header.height, header.width);

    //Creates an image using information from the file passed in
    for(int i = 0; i < header.height; i++){
        fread(image.pixels[i], sizeof(Pixel), image.width, file);
    }
    return image;
}

void freeImage(Image image){
    //Loops through and frees all memory malloced for the image
    for (int i = 0; i < image.height; ++i)
        free(image.pixels[i]);
    free(image.pixels);
}

void writeImage(Image image, FILE* file){
    //Writes the image passed in to the outfile
    for (int i = 0; i < image.height; ++i)
        fwrite(image.pixels[i], sizeof(Pixel), image.width, file);
}