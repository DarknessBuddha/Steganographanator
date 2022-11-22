#include <stdio.h>
#include <assert.h>
#include "ppm.h"
#include "EncodeDecode.h"

int main(int argc, char**argv) {
    assert(argc == 3);
    FILE* inFile = fopen(argv[1], "rb");
    FILE* outFile = fopen(argv[2], "wb");

    assert(inFile);
    assert(outFile);

    Header header = getHeader(inFile);
    Image image = getImage(header, inFile);
    writeHeader(header, outFile);

    char* message = getUserInput(header);
    printf("%s", message);

    return 0;

    Image encodedImage = makeEncodedImage(image, message);
    writeImage(image, outFile);

    message = decodeImage(encodedImage);
    printf("%s\n", message);

    // free memory
    free(message);
    freeImage(image);
    freeImage(encodedImage);

    fclose(inFile);
    fclose(outFile);
    return 0;
}
