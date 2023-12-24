#include "common.c"
#include "memory.c"
#include "value.c"
#include "chunk.c"
#include "debug.c"

int main(int argc, const char* argv[])
{
    
    Chunk chunk;
    initChunk(&chunk);
    
    writeChunk(&chunk, OP_CONSTANT, 123);
    
    uint8_t constant = (uint8_t)addConstant(&chunk, 1.2);
    writeChunk(&chunk, constant, 123);
    
    writeChunk(&chunk, OP_RETURN, 123);
    writeConstant(&chunk, 1234.123, 13);
    
    
    
    disassembleChunk(&chunk, "test chunk");
    
    freeChunk(&chunk);
    
    return 0;
}