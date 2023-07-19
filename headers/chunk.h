#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// 1-byte opcodes
typedef enum {
    OP_CONSTANT,        // <opcode> <constant_index>
    
    OP_NIL,             // <opcode>
    OP_TRUE,            // <opcode>
    OP_FALSE,           // <opcode>
    
    OP_POP,             // <opcode>

    OP_GET_LOCAL,       // <opcode> <local_slot_in_locals>
    OP_SET_LOCAL,       // <opcode> <local_slot_in_locals>

    OP_GET_GLOBAL,      // <opcode> <variable_index_in_chunk_constant>
    OP_DEFINE_GLOBAL,   // <opcode> <variable_index_in_chunk_constant>
    OP_SET_GLOBAL,      // <opcode> <variable_index_in_chunk_constant>

    OP_GET_UPVALUE,     // <opcode> <index>
    OP_SET_UPVALUE,     // <opcode> <index>

    OP_GET_PROPERTY,    // <opcode> <index>
    OP_SET_PROPERTY,    // <opcode> <index>

    OP_GET_SUPER,       // <opcode> <method_name>

    OP_EQUAL,           // <opcode>
    OP_GREATER,         // <opcode>
    OP_LESS,            // <opcode>
    
    OP_ADD,             // <opcode>
    OP_SUBTRACT,        // <opcode>
    OP_MULTIPLY,        // <opcode>
    OP_DIVIDE,          // <opcode>
    
    OP_NOT,             // <opcdoe>
    OP_NEGATE,          // <opcode>
    
    OP_PRINT,           // <opcode>

    OP_JUMP,            // <opcode>
    OP_JUMP_IF_FALSE,   // <opcode> <offset>
    OP_LOOP,            // <opcode> <offset>

    OP_CALL,

    OP_INVOKE,          // <opcode> <method_name> <arg_count>
    OP_SUPER_INVOKE,
    
    OP_CLOSURE,         // <opcode> <constant_index>
    
    OP_CLOSE_UPVALUE,   // <opcode>

    OP_RETURN,          // <opcode>

    OP_CLASS,           // <opcode> <constant_index>
    OP_INHERIT,         // <opcode>
    OP_METHOD,          // <opcode> <constant_index>
} OpCode;

// contains code
typedef struct {
    int capacity;
    int count;
    uint8_t* code;
    ValueArray constants;
    int* lines;
    int lineCount;
    int lineCapacity;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

#endif
