#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <openssl/sha.h>

#define BITS 8  
#define VERSION "1.0.0"
#define MAX_INPUT_SIZE 4096
#define MAX_KEY_LENGTH 256

unsigned int generateRandom(unsigned int *seed) {
    *seed = (1664525 * (*seed) + 1013904223) % 4294967296;
    return *seed;
}

void hashKey(const char *keyStr, unsigned char *hash) {
    if (keyStr == NULL || strlen(keyStr) == 0) {
        fprintf(stderr, "Error: Key cannot be empty.\n");
        exit(1);
    }
    SHA256((unsigned char *)keyStr, strlen(keyStr), hash);
}

void encryptDecrypt(const char *input, char *output, unsigned char *keyHash) {
    size_t length = strlen(input);
    for (size_t i = 0; i < length; i++) {
        output[i] = input[i] ^ keyHash[i % SHA256_DIGEST_LENGTH];
    }
    output[length] = '\0';
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[--len] = '\0';
    }
}

void printHelp() {
    printf("Bit Flip Cipher (v%s)\n", VERSION);
    printf("\n");
    printf("Usage: bflip -k <key> [text]\n");
    printf("\n");
    printf("Description: This tool encrypts text using a key-derived SHA-256 hash with XOR bit flipping. As a symmetric cipher, decryption can be performed by reapplying this tool with the same key.\n");
    printf("\n");
    printf("Examples:\n");
    printf("  bflip -k secretkey 'hello world'\n");
    printf("  bflip -k 'multi-word secretkey' 'hello world'\n");
    printf("  printf 'hello world' | bflip -k secretkey\n");
    printf("\n");
    printf("Options:\n");
    printf("  -k <key>      Specify the encryption/decryption key (string).\n");
    printf("  -h, --help    Display this help menu.\n");
    printf("  -v, --version Display the version information.\n");
    printf("\n");
    printf("Credits:\n");
    printf("  This tool was created by noinoiexists.\n  Source: https://github.com/noinoiexists/Bit-Flip-Cipher\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Bit Flip Cipher (v%s)\nTry 'bflip --help' for more information.\nOr visit https://github.com/noinoiexists/Bit-Flip-Cipher\n", VERSION);
        return 1;
    }
    
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printHelp();
        return 0;
    }
    
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("Bit Flip Cipher\nVersion: %s\n(https://github.com/noinoiexists/Bit-Flip-Cipher)\n", VERSION);
        return 0;
    }
    
    if (argc < 3 || strcmp(argv[1], "-k") != 0) {
        fprintf(stderr, "Usage: bflip -k <key> [text]\nTry 'bflip --help' for more information\n");
        return 1;
    }
    
    if (strlen(argv[2]) > MAX_KEY_LENGTH) {
        fprintf(stderr, "Error: Key is too long. Maximum allowed length is %d characters.\n", MAX_KEY_LENGTH);
        return 1;
    }
    
    unsigned char keyHash[SHA256_DIGEST_LENGTH];
    hashKey(argv[2], keyHash);
    
    char input[MAX_INPUT_SIZE];
    if (argc == 4) {  
        if (strlen(argv[3]) >= MAX_INPUT_SIZE) {
            fprintf(stderr, "Error: Input text is too large. Maximum allowed size is %d characters.\n", MAX_INPUT_SIZE - 1);
            return 1;
        }
        strncpy(input, argv[3], sizeof(input) - 1);
        input[sizeof(input) - 1] = '\0';
    } else {  
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Error: No input provided.\n");
            return 1;
        }
        trimNewline(input);
    }
    
    char output[MAX_INPUT_SIZE];
    encryptDecrypt(input, output, keyHash);
    
    printf("%s\n", output);
    return 0;
}
