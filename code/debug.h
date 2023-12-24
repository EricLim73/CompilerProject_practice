/* date = September 3rd 2023 4:56 pm */

#ifndef DEBUG_H
#define DEBUG_H

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

internal int 
simpleInstruction(const char* name, int offset);
internal int 
constantInstruction(const char* name, Chunk* chunk, int offset);
internal int 
constantInstruction_long(const char* name, Chunk* chunk, int offset);


#endif //DEBUG_H
