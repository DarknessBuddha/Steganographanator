/************************* 
 *Ivan Lin and Lucia Wang
 *CPSC 2310 F22 Section 4:30 and 2:00
 *lucia2@clemson.edu and ilin@clemson.edu
 *************************/ 

#ifndef PA2_ENCODE_DECODE_H
#define PA2_ENCODE_DECODE_H

#include "ppm.h"
#include "string.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

//Struct that holds a binary representation of 0s and 1s
typedef struct Binary{
    int length;
    bool* data;
}Binary;

/* Parameters: image - an image created that is a 2d array of pixels 
 * Return: output - a pointer to a string
 *                  of chars that represent the encoded message
 * This function takes the last bit from each RGB
 * block in each pixel and translates it into message
 */ 
char* decodeImage(Image image);

/* Parameters: image - an image created that is a 2d array of pixels 
               message - a pointer to a string of chars
                         that is the message to be encoded into the image
 * Return: output - an Image struct that
 *                  represents the new image with the encoded message
 * This function encodes a message passed in into
 * the image by changing the RGB pixel values of the image
 */ 
Image makeEncodedImage(Image image, char* message);

/* Parameters: length - an int value representing the
 *                      number of bits to represent a binary (9 in this case)
 * Return: Binary - a Binary struct of length passed in
 * This function creates space of length passed in for a binary representation
 */ 
Binary makeBinary(int length);

/* Parameters: ascii - a char passed in to be translated to binary
 * Return: output - a Binary representation of the char passed in
 * This function translates a character in ascii to binary
 */ 
Binary asciiToBinary(char ascii);

/* Parameters: binary - a binary representation to be translated to a char 
 * Return:        output - a char that corresponds to a letter in ascii 
 * This function takes in a string
 * of 0s and 1s and translates it into a letter in ascii
 */ 
short binaryToAscii(Binary binary);

/* Parameters: header - a header struct that holds the image height and width
 * Return: output - a pointer to a string of
 *         chars that represents a message to be encoded
 * This function prompts the user to enter a
 * message in or to use a default message to encode into an image
 */ 
char* getUserInput(Header header);
#endif //PA2_ENCODE_DECODE_H

/*
 * Parameters: None
 * Return: None
 * This function flushes the input buffer by reading it and discarding it
 */
void flushInput();