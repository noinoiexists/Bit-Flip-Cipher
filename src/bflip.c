#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS 8  
#define VERSION "1.0.0"

unsigned int generateRandom(unsigned int *seed) {
    *seed = (1664525 * (*seed) + 1013904223) % 4294967296;
    return *seed;
}

void stringToBinary(const char *input, char binary[][BITS + 1], size_t length) {
    for (size_t i = 0; i < length; i++) {
        unsigned char c = input[i];
        for (int j = BITS - 1; j >= 0; j--) {
            binary[i][j] = (c & 1) + '0';
            c >>= 1;
        }
        binary[i][BITS] = '\0';  
    }
}

void binaryToString(const char binary[][BITS + 1], char *output, size_t length) {
    for (size_t i = 0; i < length; i++) {
        unsigned char c = 0;
        for (int j = 0; j < BITS; j++) {
            c = (c << 1) | (binary[i][j] - '0');
        }
        output[i] = c;
    }
    output[length] = '\0';
}

void flipBits(char binary[][BITS + 1], size_t length, unsigned int key) {
    unsigned int seed = key;
    for (size_t i = 0; i < length; i++) {
        unsigned int pos = (generateRandom(&seed) % 4) + 1;
        pos = BITS - pos;  
        binary[i][pos] = (binary[i][pos] == '0') ? '1' : '0';
    }
}

void encryptDecrypt(const char *input, char *output, unsigned int key) {
    size_t length = strlen(input);
    char binary[length][BITS + 1];
    
    stringToBinary(input, binary, length);
    flipBits(binary, length, key);
    binaryToString(binary, output, length);
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void printHelp() {
    printf("Bit Flip Cipher (v%s)\n",VERSION);
    printf("\n");
    printf("Usage: blip -k <key> [text]\n");
    printf("Description: This tool encrypts text using an integer key by flipping pseudo-random bits in the binary representation of the text.\n");
    printf("Examples:\n");
    printf("  bflip -k 12345 'hello world'\n");
    printf("  printf 'hello world' | bflip -k 12345\n");
    printf("\n");
    printf("Options:\n");
    printf("  -k <key>      Specify the encryption/decryption key (integer).\n");
    printf("  -h, --help    Display this help menu.\n");
    printf("  -v, --version Display the version information.\n");
    printf("\n");
    printf("Credits:\n");
    printf("  This tool was created by noinoiexists.\n  Github: https://github.com/noinoiexists/\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Bit Flip Cipher (v%s)\n",VERSION);
        fprintf(stderr, "Try 'bflip --help' for more information.\n");
        return 1;
    }
    
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printHelp();
        return 0;
    }
    
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("Bit Flip Cipher\nVersion: %s\n", VERSION);
        return 0;
    }
    
    if (argc < 3 || strcmp(argv[1], "-k") != 0) {
        fprintf(stderr, "Usage: bflip -k <key> [text]\n");
        return 1;
    }
    
    unsigned int key = atoi(argv[2]);
    char input[4096];
    
    if (argc == 4) {  
        strncpy(input, argv[3], sizeof(input) - 1);
        input[sizeof(input) - 1] = '\0';
    } else {  
        size_t length = fread(input, 1, sizeof(input) - 1, stdin);
        if (length == 0) {
            fprintf(stderr, "Error: No input provided.\n");
            return 1;
        }
        input[length] = '\0';
        trimNewline(input);
    }
    
    char output[4096];
    encryptDecrypt(input, output, key);
    
    printf("%s", output);
    return 0;
}
