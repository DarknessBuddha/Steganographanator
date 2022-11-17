#include "EncodeDecode.h"

char* decodeImage(Image image){
    int wordLength = image.height * image.width / 3;
    char* message = (char*) malloc(sizeof(char) * wordLength);
    int messagePos = 0;

    for (int i = 0; i < image.height; ++i){
        for (int j = 0; j < image.width; j += 1){
            unsigned int binaryLetter[9];
            for (int k = 0; k < 3; k++){
                if (image.pixels[i][j+k].red > 255)
                    return message;
                binaryLetter[k*3] = image.pixels[i][j+k].red % 10;

                if (image.pixels[i][j+k].green > 255)
                    return message;
                binaryLetter[k*3 + 1] = image.pixels[i][j+k].green % 10;

                if (image.pixels[i][j+k].green > 255)
                    return message;
                binaryLetter[k*3 + 2] = image.pixels[i][j+k].blue % 10;
            }
            char letter = 0;
            for (int k = 8; k >= 1; --k){
                letter += (binaryLetter[k] << 8 - k);
            }
            message[messagePos++] = letter;
        }
    } 

    return message;
}
