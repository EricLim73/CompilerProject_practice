/* date = September 3rd 2023 0:12 pm */

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

// NOTE(EricLim): Every insturction will be represented in bytcode and this struct stores the number value
// of said instruction aka bytecode. The number value is that one byte representation.
typedef enum
{
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN,
    Total_Op_Cnt
} OpCode;


// NOTE(EricLim): bytecode is a series of instruction. This struct will hold on to that 
// information. This packet of information is considered "dynamic".
// If making an areana allocator, it would speed things up.
typedef struct
{
    int        count;    // current count
    int        capacity; // whole size : space left = capacity - count
    uint8_t*   code;     // 1 byte
    
    int32_t    lineOffset;    // current count
    int        lineCapacity; // whole size : space left = capacity - count
    int*       lines;    // stores line number of that opcode for debuging reasons
    ValueArray constants;
} Chunk;


void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void freeChunk(Chunk* chunk);

// followed by opcode, chunk can save operand information
// inside itself. This function returns the idx for that data
// ,in this case being "constant", from ValueArray pool 
int addConstant(Chunk* chunk, Value value);

int getLineNumber(Chunk* chunk, int idx);







#endif //CHUNK_H
