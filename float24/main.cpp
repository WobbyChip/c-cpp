#include <stdio.h>
#include <stdlib.h>
#include "float24.h"


void binaryTo24Float(const long binary) {
    unsigned char buffer[3];
    buffer[0] = static_cast<unsigned char>((binary >> 16) & 0xFF);
    buffer[1] = static_cast<unsigned char>((binary >> 8) & 0xFF);
    buffer[2] = static_cast<unsigned char>(binary & 0xFF);

    float24_s var = float24_s(0);
    memcpy(var.data.buffer+0, buffer+2, 1);
    memcpy(var.data.buffer+1, buffer+1, 1);
    memcpy(var.data.buffer+2, buffer+0, 1);

    printf ("%f\n", float(var));

    for (int i = 2; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            printf("%d", (var.data.buffer[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}


void float24ToBinary(float input)
{
    float24_s var = float24_s(input);
    printf ("%f\n", float(var));

    for (int i = 2; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            printf("%d", (var.data.buffer[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    printf("Enter a binary value (b001110011001001011110010).\n");
    printf("Enter a 24bit float value (0.012297).\n");

    while (1) {
        char input[25];
        printf("\nInput: ");
        scanf("%s", input);

        if (input[0] == 'b') {
            binaryTo24Float(strtol(input+1, NULL, 2));
        } else {
            float24ToBinary(atof(input));
        }
    }

    return EXIT_SUCCESS;
}

