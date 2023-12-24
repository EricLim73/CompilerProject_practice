/* date = September 3rd 2023 5:24 pm */

#ifndef VALUE_H
#define VALUE_H

typedef double Value;

typedef struct
{
    int    count;
    int    capacity;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif //VALUE_H
