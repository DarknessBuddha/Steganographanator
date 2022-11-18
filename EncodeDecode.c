#include "EncodeDecode.h"

char* decodeImage(Image image){
    int maxLength = image.height * image.width / 3;
    char messageBank[maxLength];
    char* message;
    int msgIndex = 0;

    for (int i = 0; i < image.height; ++i){
        for (int j = 0; j < image.width; j += 3){
            bool binary[9];
            for (int k = 0; k < 3; k++){
                binary[k * 3] = image.pixels[i][j + k].red % 10;
                binary[k * 3 + 1] = image.pixels[i][j + k].green % 10;
                binary[k * 3 + 2] = image.pixels[i][j + k].blue % 10;
            }
            char ascii = binaryToAscii(binary);
            if (ascii == 0){
                i = image.height;
                break;
            }
            messageBank[msgIndex++] = (char)ascii;
        }
    }
    messageBank[msgIndex] = '\0';
    message = malloc(sizeof(char) * strlen(messageBank) + 1);
    strncpy(message, messageBank, strlen(messageBank));
    return message;
}

Image makeEncodedImage(Image image, char* message){
    Image encodedImage = allocateImage(image.height, image.width);
    int i = 0, j = 0;
    int msgIndex = 0;

    while (msgIndex < strlen(message)){
        bool* binary = charToBinary(message[msgIndex]);
        for (int k = 0; k < 3; ++k) {
            encodedImage.pixels[i][j].red = image.pixels[i][j].red / 10 * 10 + binary[k*3];
            encodedImage.pixels[i][j].green = image.pixels[i][j].green / 10 * 10 + binary[k*3 + 1];
            encodedImage.pixels[i][j].blue = image.pixels[i][j].blue / 10 * 10 + binary[k*3 + 2];
            j = (j + 1) % image.width;
            i = i + (j + 1) / image.width;
        }
        free(binary);
        msgIndex++;
    }
    
    for (; i < image.height; i++){
        for (; j < image.width; j++){
            encodedImage.pixels[i][j].red = image.pixels[i][j].red / 10 * 10;
            encodedImage.pixels[i][j].green = image.pixels[i][j].green / 10 * 10;
            encodedImage.pixels[i][j].blue = image.pixels[i][j].blue / 10 * 10;
        }
        j = 0;
    }

    return encodedImage;
}

bool* charToBinary(char letter){
    int len = 9;
    bool* binary = (bool*) calloc(len, sizeof(bool));
    int i = len - 1;
    while (letter > 0){
        binary[i] = letter % 2;
        letter /= 2;
        i--;
    }
    return binary;
}

char binaryToAscii(const bool* binary){
    char ascii = 0;
    for (int i = 8; i >= 1; --i) {
        ascii += (binary[i] << 8 - i);
    }
    return ascii;
}