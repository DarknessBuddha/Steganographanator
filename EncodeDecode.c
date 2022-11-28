/************************* 
 *Ivan Lin and Lucia Wang
 *CPSC 2310 F22 Section 4:30 and 2:00
 *lucia2@clemson.edu and ilin@clemson.edu
 *************************/ 

#include "EncodeDecode.h"

char* decodeImage(Image image){
    //Finds the char limit and initializes a placeholder for the message
    int maxLength = image.height * image.width / 9;
    char messageBank[maxLength];
    char* message;
    int msgIndex = 0;

    //Traverses the image and parses the last bit from every pixel in each RGB channel;
    for (int i = 0; i < image.height; ++i){
        for (int j = 0; j < image.width; j += 3){
            //Initializes a 9 bits that will hold a binary number
            Binary binary = makeBinary(9);
            //Populates the binary with either a 1 or a 0
            for (int k = 0; k < 3; k++){
                binary.data[k * 3] = image.pixels[i][j + k].red % 10;
                binary.data[k * 3 + 1] = image.pixels[i][j + k].green % 10;
                binary.data[k * 3 + 2] = image.pixels[i][j + k].blue % 10;
            }

            //Sets a char equal to the binary translated to ascii and frees the data pointer
            char ascii = binaryToAscii(binary);
            free(binary.data);

            //If something failed (ie, caused ascii to become 0) breaks out
            if (ascii == 0){
                i = image.height;
                break;
            }
            //Adds the char ascii to the message placeholder
            messageBank[msgIndex++] = ascii;
        }
    }
    //Appends the null character to the end of the message
    messageBank[msgIndex] = '\0';
    //Dynamically allocates room for a message and copies the message from the image to it and returns it
    message = (char*) malloc(sizeof(char) * strlen(messageBank) + 1);
    strncpy(message, messageBank, strlen(messageBank));
    return message;
}

Image makeEncodedImage(Image image, char* message){
    //Initializes counter variables and makes an image
    Image encodedImage = makeImage(image.height, image.width);
    int i = 0, j = 0;
    int msgIndex = 0;

    //Encodes a message into the image while there is room in image and there are still letters to encode
    while (msgIndex < strlen(message) && i < image.height){
        //Assigns a binary value from a char translated to binary
        Binary binary = asciiToBinary(message[msgIndex]);
        //Creates a pixel with RGB values modified with the pixels from the original with a bit
        for (int k = 0; k < 3; ++k) {
            encodedImage.pixels[i][j].red = 
            image.pixels[i][j].red / 10 * 10 + binary.data[k * 3];
            encodedImage.pixels[i][j].green = 
            image.pixels[i][j].green / 10 * 10 + binary.data[k * 3 + 1];
            encodedImage.pixels[i][j].blue = 
            image.pixels[i][j].blue / 10 * 10 + binary.data[k * 3 + 2];
            
            //Increments i and j
            i += (j + 1) / image.width;
            j = (j + 1) % image.width;
        }
        //Frees the data pointer and increments the index
        free(binary.data);
        msgIndex++;
    }
    

    for (; i < image.height; i++, j = 0){
    //Sets the pixels of the encoded image to the allocated places on the image
        for (; j < image.width; j++){
            encodedImage.pixels[i][j].red = 
            image.pixels[i][j].red / 10 * 10;
            encodedImage.pixels[i][j].green = 
            image.pixels[i][j].green / 10 * 10;
            encodedImage.pixels[i][j].blue = 
            image.pixels[i][j].blue / 10 * 10;
        }
    }

    return encodedImage;
}

Binary makeBinary(int length){
    //Declares a Binary struct of boolean values with length passed in 
    Binary binary;
    binary.length = length;
    binary.data = (bool*) calloc(length, sizeof(bool));
    return binary;
}

Binary asciiToBinary(char ascii){
    //Translates an ascii character in to a binary by splitting it with 2k + 1 or 2k
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
    //Translates a binary to a character in ascii using the bitwise operation left shift
    char ascii = 0;
    for (int i = binary.length-1; i >= binary.length-8; --i) {
        ascii += (binary.data[i] << (8 - i));
    }
    return ascii;
}

char* getUserInput(Header header){
    //Calculates the character limit and allocates memory for the user's message
    int maxLength = header.height * header.width / 9;
    char userChoice;
    char *userMessage = (char*) malloc (maxLength * sizeof(char) + 1);
    
    //Prompts the user to either use the default message or to input a message and takes in the user's choice
    printf("Would you like to use the provided input message (Cats <3)");
    printf("or create a unique input message? y/n\n");
    scanf("%c%*c", &userChoice);
    userChoice = tolower(userChoice);    
    //Error checks to make sure the user put something valid
    assert(userChoice == 'y' || userChoice == 'n');

    //If y was input, sets the userMessage to the default message
    if (userChoice == 'y'){
        strcpy(userMessage, "Cats <3");
    //Otherwise, takes in a message from the user and thanks them
    }else{
        printf("Provide a user message (max length of %d): \n", maxLength);
        fgets(userMessage, maxLength, stdin);
        printf("Thank you for the message! :^)\n");
    }

    return userMessage;
}