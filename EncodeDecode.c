#include "EncodeDecode.h"

char* decodeImage(Image image){
    int maxLength = image.height * image.width / 9;
    char messageBank[maxLength];
    char* message;
    int msgIndex = 0;

    for (int i = 0; i < image.height; ++i){
        for (int j = 0; j < image.width; j += 3){
            Binary binary = makeBinary(9);
            for (int k = 0; k < 3; k++){
                binary.data[k * 3] = image.pixels[i][j + k].red % 10;
                binary.data[k * 3 + 1] = image.pixels[i][j + k].green % 10;
                binary.data[k * 3 + 2] = image.pixels[i][j + k].blue % 10;
            }
            char ascii = binaryToAscii(binary);
            free(binary.data);
            if (ascii == 0){
                i = image.height;
                break;
            }
            messageBank[msgIndex++] = ascii;
        }
    }
    messageBank[msgIndex] = '\0';
    message = (char*) malloc(sizeof(char) * strlen(messageBank) + 1);
    strncpy(message, messageBank, strlen(messageBank));
    return message;
}

Image makeEncodedImage(Image image, char* message){
    Image encodedImage = makeImage(image.height, image.width);
    int i = 0, j = 0;
    int msgIndex = 0;

    while (msgIndex < strlen(message) && i < image.height){
        Binary binary = asciiToBinary(message[msgIndex]);
        for (int k = 0; k < 3; ++k) {
            encodedImage.pixels[i][j].red = image.pixels[i][j].red / 10 * 10 + binary.data[k * 3];
            encodedImage.pixels[i][j].green = image.pixels[i][j].green / 10 * 10 + binary.data[k * 3 + 1];
            encodedImage.pixels[i][j].blue = image.pixels[i][j].blue / 10 * 10 + binary.data[k * 3 + 2];
            i += (j + 1) / image.width;
            j = (j + 1) % image.width;
        }
        free(binary.data);
        msgIndex++;
    }
    
    for (; i < image.height; i++, j = 0){
        for (; j < image.width; j++){
            encodedImage.pixels[i][j].red = image.pixels[i][j].red / 10 * 10;
            encodedImage.pixels[i][j].green = image.pixels[i][j].green / 10 * 10;
            encodedImage.pixels[i][j].blue = image.pixels[i][j].blue / 10 * 10;
        }
    }

    return encodedImage;
}

Binary makeBinary(int length){
    Binary binary;
    binary.length = length;
    binary.data = (bool*) calloc(length, sizeof(bool));
    return binary;
}

Binary asciiToBinary(char ascii){
    Binary binary = makeBinary(9);
    int i = binary.length - 1;
    while (ascii > 0 && i >= 0){
        binary.data[i] = ascii % 2;
        ascii /= 2;
        i--;
    }
    return binary;
}

char binaryToAscii(Binary binary){
    char ascii = 0;
    for (int i = binary.length-1; i >= binary.length-8; --i) {
        ascii += (binary.data[i] << (8 - i));
    }
    return ascii;
}


char* getUserInput(Header header){
    int maxLength = header.height * header.width / 9;
    char userChoice;
    char *userMessage = (char*) malloc (maxLength * sizeof(char) + 1);
    
    printf("Would you like to use the provided input message (Cats <3) or create a unique input message? y/n\n");
    scanf("%c%*c", &userChoice);
    userChoice = tolower(userChoice);    
    assert(userChoice == 'y' || userChoice == 'n');

    if (userChoice == 'y'){
        strcpy(userMessage, "Cats <3");
    }else{
        printf("Provide a user message (max length of %d): \n", maxLength);
        fgets(userMessage, maxLength, stdin);
        printf("Thank you for the message! :^)\n");
    }

    return userMessage;
}