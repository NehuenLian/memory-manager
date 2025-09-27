#ifndef MANAGE_RUNTIME_MEMORY
#define MANAGE_RUNTIME_MEMORY

signed char* load_into_memory();
int* divide_int_memory(unsigned char *runtime_full_memory);
unsigned char* divide_char_memory(unsigned char *runtime_full_memory);
int update_memory(unsigned char *runtime_full_memory, int *int_bytes, unsigned char *char_bytes);

#endif