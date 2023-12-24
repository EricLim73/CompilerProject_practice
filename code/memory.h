/* date = September 3rd 2023 0:40 pm */
#ifndef CLOX_MEMORY_H
#define CLOX_MEMORY_H

// NOTE(EricLim): number "15" is just some threshold, can tweak for extra performance 
#define GROW_CAPACITY(capacity)\
((capacity) < 15 ? 15 : (capacity) * 2)


#define GROW_ARRAY(type, pointer, oldCount, newCount)\
(type*)reallocate(pointer, \
sizeof(type) * (oldCount),\
sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount)\
reallocate(pointer, sizeof(type) * (oldCount), 0)


// NOTE(EricLim): 
// 1. oldSize = 0 & newSize = nonZero -> allocate new block
// 2. oldSize = nonZero & newSize = 0 -> free allocation
// 3. oldSize = nonZero & newSize = nonZero smaller than oldSize -> shrink existing allocation
// 4. oldSize = nonZero & newSize = nonZero bigger than oldSize -> Grow existing allocation 
// 1     -> free()
// 2,3,4 -> realloc
void* reallocate(void* pointer, size_t oldSize, size_t newSize);



#endif //MEMORY_H
