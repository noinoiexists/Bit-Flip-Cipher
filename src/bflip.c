#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BITS 8  
#define VERSION "1.1.0"
#define MAX_INPUT_SIZE 8192
#define MAX_KEY_LENGTH 256

void hashKey(const char *keyStr, unsigned char *hash) {
    if (keyStr == NULL || strlen(keyStr) == 0) {
        fprintf(stderr, "Error: Key cannot be empty.\n");
        exit(1);
    }
    SHA256((unsigned char *)keyStr, strlen(keyStr), hash);
}

void encryptDecrypt(const char *input, char *output, unsigned char *keyHash, size_t length) {
    for (size_t i = 0; i < length; i++) {
        output[i] = input[i] ^ keyHash[i % SHA256_DIGEST_LENGTH];
    }
}

char *base64Encode(const unsigned char *input, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    
    char *b64text = (char *)malloc(bufferPtr->length + 1);
    memcpy(b64text, bufferPtr->data, bufferPtr->length);
    b64text[bufferPtr->length] = '\0';
    
    BIO_free_all(bio);
    return b64text;
}

unsigned char *base64Decode(const char *input, int *length) {
    BIO *bio, *b64;
    int inputLength = strlen(input);
    unsigned char *buffer = (unsigned char *)malloc(inputLength);
    
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(input, inputLength);
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    
    *length = BIO_read(bio, buffer, inputLength);
    
    BIO_free_all(bio);
    return buffer;
}

void printHelp() {
    printf("Bit Flip Cipher (v%s)\n", VERSION);
    printf("\n");
    printf("Usage: bflip -k <key> [text] | bflip -d -k <key> [base64_text]\n");
    printf("\n");
    printf("Description: This tool encrypts text using a key-derived SHA-256 hash with XOR bit flipping. Output is Base64 encoded to ensure compatibility. Use -d to decrypt Base64-encoded input.\n");
    printf("\n");
    printf("Examples:\n");
    printf("  bflip -k secretkey 'hello world'\n");
    printf("  echo 'hello world' | bflip -k secretkey\n");
    printf("  bflip -d -k secretkey 'BASE64_ENCODED_TEXT'\n");
    printf("\n");
    printf("Options:\n");
    printf("  -k <key>      Specify the encryption/decryption key (string).\n");
    printf("  -d            Decrypt Base64 input.\n");
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
    
    int decryptMode = 0;
    int keyIndex = -1;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            decryptMode = 1;
        } else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            keyIndex = i;
        }
    }
    
    if (keyIndex == -1) {
        fprintf(stderr, "Usage: bflip -k <key> [text] | bflip -d -k <key> [base64_text]\nTry 'bflip --help' for more information\n");
        return 1;
    }
    
    unsigned char keyHash[SHA256_DIGEST_LENGTH];
    hashKey(argv[keyIndex + 1], keyHash);
    
    char input[MAX_INPUT_SIZE] = {0};
    char output[MAX_INPUT_SIZE] = {0};
    size_t inputLength = 0;
    
    if (keyIndex + 2 < argc) {
        strncpy(input, argv[keyIndex + 2], MAX_INPUT_SIZE - 1);
        inputLength = strlen(input);
    } else {
        int c;
        while ((c = getchar()) != EOF && inputLength < MAX_INPUT_SIZE - 1) {
            input[inputLength++] = c;
        }
        input[inputLength] = '\0';
    }
    
    if (decryptMode) {
        int decodedLength;
        unsigned char *decoded = base64Decode(input, &decodedLength);
        encryptDecrypt((char *)decoded, output, keyHash, decodedLength);
        free(decoded);
        fwrite(output, 1, decodedLength, stdout);
        putchar('\n');
    } else {
        encryptDecrypt(input, output, keyHash, inputLength);
        char *encoded = base64Encode((unsigned char *)output, inputLength);
        printf("%s\n", encoded);
        free(encoded);
    }
    
    return 0;
}
