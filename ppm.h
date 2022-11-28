/************************* 
 *Ivan Lin and Lucia Wang
 *CPSC 2310 F22 Section 4:30 and 2:00
 *lucia2@clemson.edu and ilin@clemson.edu
 *************************/ 

#ifndef PA2_PPM_H
#define PA2_PPM_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//Struct that holds the type of image, width, height, and RGB value from the image header
typedef struct Header{
    char type[3];
    int height;
    int width;
    int maxColor;
}Header;

//Struct that holds the RGB value of a pixel on an image
typedef struct Pixel{
    unsigned char red, green, blue;
}Pixel;

//Struct that holds the height and width of an image and a double pointer to a 2d array of pixels
typedef struct Image{
    int height, width;
    Pixel** pixels;
}Image;

/* Parameters: file - a file pointer that was opened in main to be read from
 * Return:        output - Header struct that holds the type, height, width, and max color 
 * This function takes the information from the image header and stores it
 */ 
Header getHeader(FILE* file);

/*
 * Parameters: file - input file to be read from
 *
 * Return: None
 * This function reads and discards comments and spaces. 
 * Comments start with #.
 */
void handleSpacesAndComments(FILE* file);

/*
 * Parameters: file - input file to be read from
 *
 * Return: None
 * This function reads and discards comments.
 * Comments start with #.
 */
void discardComments(FILE* file);

/*
 * Parameters: header - pointer storing the location of header data
 *             file - output file to be written to
 * Return: None
 * This function writes magic number, width, height,
 * and maximum color value of ppm to the output file.
 */
void writeHeader(Header header, FILE* file);

/*
 * Parameters: header - pointer storing the location of header data
 *             file - output file to be written to
 * Return: Image struct that represents a 2d array of pixels
 * This function creates an image and stores pixel values from the file
 */
Image getImage(Header header, FILE* file);

/*
 * Parameters: height - int that represents height in pixels of image
 *             width - int that represents width in pixels of image
 * Return: Image struct that represents a 2d array of pixels
 * This function allocates space for an image of height x width
 */
Image makeImage(int height, int width);

/*
Parameters: image - 2d pixel array that represents an image
Return: void
This function loops through and frees all memory that was allocated for the image
*/
void freeImage(Image image);

/*
 * Parameters: image - Image struct of pixels passed in
 *             file - output file to be written to
 * Return: None
 * This function writes header info and the pixels of ppm to the output file
 */
void writeImage(Image image, FILE* file);

#endif //PA2_PPM_H
