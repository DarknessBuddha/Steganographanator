#include <stdio.h>
#include <assert.h>
#include "ppm.h"
#include "EncodeDecode.h"
int main(int argc, char**argv) {
    assert(argc == 3);
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = fopen(argv[2], "w");

    assert(inFile);
    assert(outFile);

    Header header = makeHeader(inFile);
    Image image = makeImage(header, inFile);
    writeHeader(header, outFile);



    fclose(inFile);
    fclose(outFile);
    return 0;
}
