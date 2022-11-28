/************************* 
 *Ivan Lin and Lucia Wang
 *CPSC 2310 F22 Section 4:30 and 2:00
 *lucia2@clemson.edu and ilin@clemson.edu
 *************************/ 

#include <stdio.h>
#include <assert.h>
#include "ppm.h"
#include "EncodeDecode.h"

int main(int argc, char**argv) {
    //Makes sure 3 arguments were passed in and opens a file to be read and a file to write to
    assert(argc == 3);
    FILE* inFile = fopen(argv[1], "rb");
    FILE* outFile = fopen(argv[2], "wb");

    //Makes sure the files were opened
    assert(inFile);
    assert(outFile);

    //Creates a header and image by calling the respective functions
    Header header = getHeader(inFile);
    Image image = getImage(header, inFile);
    writeHeader(header, outFile);

    //Gets a message from the user and prints it
    char* message = getUserInput(header);
    printf("%s", message);


    //Encodes the message into the image and writes it to the outfile
    Image encodedImage = makeEncodedImage(image, message);
    writeImage(image, outFile);

    //Gets the message from the image and prints it
    message = decodeImage(encodedImage);
    printf("%s\n", message);

    // free memory
    free(message);
    freeImage(image);
    freeImage(encodedImage);

    //Closes the files
    fclose(inFile);
    fclose(outFile);
    return 0;
}
