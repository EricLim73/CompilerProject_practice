#include "chunk.h"

void 
initChunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lineCapacity = 0;
    chunk->lineOffset = 0;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}


void 
writeConstant(Chunk* chunk, Value value, int line)
{
    if (chunk->capacity < chunk->count + 2)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, 
                                 chunk->code, 
                                 oldCapacity, 
                                 chunk->capacity);
    }
    
    chunk->code[chunk->count] = OP_CONSTANT_LONG;
    chunk->count+=1;
    uint8_t operand_idx = (uint8_t)addConstant(chunk, value);
    chunk->code[chunk->count] = operand_idx;
    
    if (chunk->lineCapacity < chunk->lineOffset + 2)
    {
        int oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
        chunk->lines = GROW_ARRAY(int, 
                                  chunk->lines, 
                                  oldCapacity, 
                                  chunk->lineCapacity);
        memset(chunk->lines, 0, sizeof(int) * chunk->lineCapacity);
    }
    
    if (chunk->lines[chunk->lineOffset+1] != line &&
        chunk->count != 0)
    {
        chunk->lineOffset+=2;
    }
    
    chunk->lines[chunk->lineOffset] += 1;
    chunk->lines[chunk->lineOffset+1] = line;
    
    chunk->count+=1;
}


void 
writeChunk(Chunk* chunk, uint8_t byte, int line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, 
                                 chunk->code, 
                                 oldCapacity, 
                                 chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    
    if (chunk->lineCapacity < chunk->lineOffset + 2)
    {
        int oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
        chunk->lines = GROW_ARRAY(int, 
                                  chunk->lines, 
                                  oldCapacity, 
                                  chunk->lineCapacity);
        memset(chunk->lines, 0, sizeof(int) * chunk->lineCapacity);
    }
    
    if (chunk->lines[chunk->lineOffset+1] != line &&
        chunk->count != 0)
    {
        chunk->lineOffset+=2;
    }
    
    chunk->lines[chunk->lineOffset] += 1;
    chunk->lines[chunk->lineOffset+1] = line;
    
    chunk->count++;
}

int getLineNumber(Chunk* chunk, int idx)
{
    int number = 0;
    int offset = chunk->lines[number];
    while(number <= chunk->lineOffset )
    {
        if (offset <= idx)
        {
            number+= 2;
            offset += chunk->lines[number];
        }
        if (offset > idx)
        {
            return chunk->lines[number+1]; 
        }
    }
    return -1;
}

void 
freeChunk(Chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(uint8_t, chunk->lines, chunk->capacity);
    
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int 
addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;  // return index of the added value
}