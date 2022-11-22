#ifndef PA2_ENCODE_DECODE_H
#define PA2_ENCODE_DECODE_H

#include "ppm.h"
#include "string.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

typedef struct Binary{
    int length;
    bool* data;
}Binary;

char* decodeImage(Image image);

Image makeEncodedImage(Image image, char* message);

Binary makeBinary(int length);

Binary asciiToBinary(char ascii);

char binaryToAscii(Binary binary);

char* getUserInput(Header header);
#endif //PA2_ENCODE_DECODE_H
