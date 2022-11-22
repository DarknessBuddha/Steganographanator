#include "ppm.h"
// headers
Header getHeader(FILE* file){
    Header header;

    fscanf(file, "%2s ", header.type);
    handleSpacesAndComments(file);

    fscanf(file, "%d", &header.width);
    handleSpacesAndComments(file);

    fscanf(file, "%d", &header.height);
    handleSpacesAndComments(file);

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
    while ((buffer = (fgetc(file))) != EOF && buffer != '\n');
}

void writeHeader(Header header, FILE* file){
    fprintf(file, "%s %d %d %d\n",
            header.type, header.width,
            header.height, header.maxColor
    );
}

Image makeImage(int height, int width){
    Image image;
    image.height = height;
    image.width = width;
    image.pixels = (Pixel**) malloc(sizeof(Pixel*) * height);
    for(int i = 0; i < height; i++){
        image.pixels[i] = (Pixel*) malloc(sizeof(Pixel) * width);
    }
    return image;
}


Image getImage(Header header, FILE* file){
    Image image;
    image = makeImage(header.height, header.width);

    for(int i = 0; i < header.height; i++){
        fread(image.pixels[i], sizeof(Pixel), image.width, file);
    }
    return image;
}

void freeImage(Image image){
    for (int i = 0; i < image.height; ++i)
        free(image.pixels[i]);
    free(image.pixels);
}

void writeImage(Image image, FILE* file){
    for (int i = 0; i < image.height; ++i)
        fwrite(image.pixels[i], sizeof(Pixel), image.width, file);
}