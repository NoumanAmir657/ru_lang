#include <stdlib.h>

#include "../headers/chunk.h"
#include "../headers/memory.h"
#include "../headers/vm.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;

    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;


    // CHALLENGE CODE
    if (chunk->lineCapacity < chunk->lineCount + 2) {
        int oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->lineCapacity);
    }

    if (chunk->lineCount == 0) {
        chunk->lines[chunk->lineCount] = line;
        chunk->lines[chunk->lineCount + 1] = 1;

        chunk->lineCount += 2;
        chunk->count++;
        return;
    }

    if (chunk->lines[chunk->lineCount - 2] == line) {
        chunk->lines[chunk->lineCount - 1]++;
        chunk->count++;
    }
    else {
        chunk->lines[chunk->lineCount] = line;
        chunk->lines[chunk->lineCount + 1] = 1;
        chunk->lineCount += 2;
        chunk->count++;
    }
    //
}

int addConstant(Chunk* chunk, Value value) {
    push(value);
    writeValueArray(&chunk->constants, value);
    pop();
    return chunk->constants.count - 1;
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}