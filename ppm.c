#include "ppm.h"
// headers
Header makeHeader(FILE* file){
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

Image makeImage(Header header, FILE* file){
    Image image;
    image.height = header.height;
    image.width = header.width;
    image.pixels = (Pixel**) malloc(sizeof(Pixel*) * header.height);

    for(int i = 0; i < header.height; i++){
        image.pixels[i] = (Pixel*) malloc(sizeof(Pixel) * image.width);
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
    for (int i = 0; i < image.height; ++i){
        fwrite(image.pixels[i], sizeof(Pixel), image.width, file);
    }
}