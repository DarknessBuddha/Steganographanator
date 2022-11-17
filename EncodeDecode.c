#include "EncodeDecode.h"

char* decodeImage(Image image){
    int wordLength = image.height * image.width / 3;
    char* message = (char*) malloc(sizeof(char) * wordLength);
    int messagePos = 0;

    for (int i = 0; i < image.height; ++i){
        for (int j = 0; j < image.width; j += 1){
            unsigned int binaryLetter[9];
            for (int k = 0; k < 3; k++){
                binaryLetter[k*3] = image.pixels[i][j+k].red % 10;
                binaryLetter[k*3 + 1] = image.pixels[i][j+k].green % 10;
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

Image makeEncodedImage(Image image, char* message){
    Image encodedImage = allocateImage(image.height, image.width);
    unsigned int encodedMessage[strlen(message) * 8];
    int i = 0, j = 0;
    int counter = 0;
    int flag = 0;
    int flag2 = 0;

    for (int l = 0; l < strlen(message); l++, counter = (counter+1) % 3, flag++){
        char letter = message[l];
        int binary = letter % 2;
        letter /= 2;

        if (flag % 9 == 0)
        {
            encodedImage.pixels[i][j].red = image.pixels[i][j].red / 10 * 10;
            continue;
        }
        if (counter == 0)
            encodedImage.pixels[i][j].red = image.pixels[i][j].red / 10 * 10 + binary;
        else if (counter == 1){
            encodedImage.pixels[i][j].green = image.pixels[i][j].green / 10 * 10 + binary;
        }else{
            encodedImage.pixels[i][j].blue = image.pixels[i][j].blue / 10 * 10 + binary;
        }
    }
    
    for (; i < image.height; i++){
        for (; i < image.width; j++){
            encodedImage.pixels[i][j].red = image.pixels[i][j].red / 10 * 10;
            encodedImage.pixels[i][j].green = image.pixels[i][j].green / 10 * 10;
            encodedImage.pixels[i][j].blue = image.pixels[i][j].blue / 10 * 10;
        }
    }

    return encodedImage;
}
