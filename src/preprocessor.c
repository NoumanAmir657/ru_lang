#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/preprocessor.h"

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }
    buffer[bytesRead] = '\0';
    fclose(file);
    return buffer;
}

char* preprocess(const char* source) {
    char p[1024];
    for (int i = 0; i < 1024; ++i) {
        p[i] = '\0';
    }
    int cnt = 0;

    initScanner(source);
    Token current;

    for (;;) {
        current = scanToken();

        if (current.type == TOKEN_EOF) {break;}

        if (current.type == TOKEN_IMPORT) {
            current = scanToken();

            char s[32] = {'\0'};
            for (int i = 1; i < current.length - 1; ++i) {
                s[i - 1] = *(current.start + i);
            }
            char* newSource = readFile(s);

            int i = 0;
            while (newSource[i] != '\0') {
                p[cnt++] = newSource[i++];
            }
            p[cnt++] = '\n';

            free(newSource);
        }
    }

    int i = 0;
    while (source[i] != '\0') {
        p[cnt++] = source[i++];
    }
    p[cnt] = '\0';


    char *dp = (char*)malloc(1024);
    i = 0;
    while (p[i] != '\0'){
        dp[i] = p[i];
        i++;
    }
    dp[i] = '\0';

    return dp;
}