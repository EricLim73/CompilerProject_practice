#include "debug.h"

void 
disassembleChunk(Chunk* chunk, const char* name)
{
    printf("== %s ==\n", name);
    
    for (int offset = 0; offset < chunk->count;)
    {
        // NOTE(EricLim): Doing this way bc each instruction might have
        // different size within chunk
        offset = disassembleInstruction(chunk, offset);
        
    }
}

int
disassembleInstruction(Chunk* chunk, int offset)
{
    printf("%04d ", offset);
    if (offset > 0 &&
        getLineNumber(chunk, offset) == getLineNumber(chunk, offset-1))
    {
        printf("   | ");
    }
    else
    {
        printf("%4d ", getLineNumber(chunk, offset));
    }
    
    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
        case OP_RETURN:
        {
            return simpleInstruction("OP_RETURN", offset);
        }
        case OP_CONSTANT: 
        {
            return constantInstruction("OP_CONSTANT", chunk, offset);
        }
        case OP_CONSTANT_LONG: 
        {
            return constantInstruction_long("OP_CONSTANT_LONG", chunk, offset);
        }
        default:
        {
            printf("Unkown opcode %d\n", instruction);
            return offset + 1;
        }
    }
}

internal int 
simpleInstruction(const char* name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

internal int 
constantInstruction(const char* name, Chunk* chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];  // bc oprand is positioned after opcode
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("\n");
    return offset + 2;  // bc oprand is positioned after opcode
}


internal int 
constantInstruction_long(const char* name, Chunk* chunk, int offset)
{
    uint8_t idx = chunk->code[offset + 1];  // bc oprand is positioned after opcode
    printf("%-16s %4d '", name, idx);
    printValue(chunk->constants.values[idx]);
    printf("\n");
    return offset + 2;  // bc oprand is positioned after opcode
}
