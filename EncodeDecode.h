#ifndef PA2_ENCODE_DECODE_H
#define PA2_ENCODE_DECODE_H

#include "ppm.h"
#include "string.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Binary{
    int length;
    bool* data;
}Binary;

char* decodeImage(Image image);

Image makeEncodedImage(Image image, char* message);

Binary makeBinary(int length);

Binary asciiToBinary(char ascii);

char binaryToAscii(Binary binary);
#endif //PA2_ENCODE_DECODE_H
