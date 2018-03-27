#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
    char inputFileName[21];
    FILE *fileIn;

    printf("%s", "Enter a file name: ");
    scanf(" %s", inputFileName);

    printf("\n%s%s\n", "entered: ", inputFileName);

    fileIn = fopen(inputFileName, "rb");
    if(fileIn == NULL)
    {
        printf("%s\n%s\n", "File does not exist.", "Terminating Program!");
        exit(1);
    }

    long binaryIn = 0;
    long dataSize = 32;
    char inputBinary[33];
    while(!feof(fileIn))
    {
        fread(&dataSize, sizeof(dataSize), 1, fileIn);
        printf("%s%u\n", "Read: ", dataSize);
    }

}