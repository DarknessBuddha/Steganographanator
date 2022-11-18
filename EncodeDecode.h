#ifndef PA2_ENCODE_DECODE_H
#define PA2_ENCODE_DECODE_H
#include "ppm.h"
#include "string.h"
#include <stdlib.h>
#include <stdbool.h>
char* decodeImage(Image image);

Image makeEncodedImage(Image image, char* message);

bool* charToBinary(char letter);

char binaryToAscii(const bool* binary);
#endif //PA2_ENCODE_DECODE_H
