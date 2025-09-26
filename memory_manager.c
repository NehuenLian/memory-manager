#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------
// Memory management
int startup_memory() {

    FILE *memory_file = fopen("memory.bin", "wb");
    if (!memory_file) {
        perror("Cannot open the file");
        return 1;
    }

    enum size {SIZE=16}; // 16 bytes
    // struct that will represent all memory structure
    typedef struct Memory {
        int *stored_ints;
        char *stored_chars;
    } Mem;

    // define 2 memory type structures
    Mem mem;
    mem.stored_ints = malloc(SIZE * 4);
    if (!mem.stored_ints) {
        printf("Couldn't assign memory for ints.\n");
        return 1;
    }

    mem.stored_chars = malloc(SIZE);
    if (!mem.stored_chars) {
        printf("Couldn't assign memory for chars.\n");
        return 1;
    }

    memset(mem.stored_ints, 0, SIZE * 4); 
    memset(mem.stored_chars, 'A', 16);

    // store bytes in the .bin file
    fwrite(mem.stored_ints, sizeof(int), 16, memory_file);
    fwrite(mem.stored_chars, sizeof(char), 16, memory_file);

    fclose(memory_file);

    free(mem.stored_ints);
    free(mem.stored_chars);
    mem.stored_ints = NULL;
    mem.stored_chars = NULL;

    return 0;
}


unsigned char* load_into_memory() {
    FILE *memory_file = fopen("memory.bin", "rb");

    if (!memory_file) {
        perror("Cannot open the file");
        return NULL;
    }
    static unsigned char runtime_full_memory[80];

    unsigned char current_byte = 0;
    int i = 0;

    while (fread(&current_byte, 1, 1, memory_file) == 1) {
        runtime_full_memory[i] = current_byte;
        i++;
    }
    fclose(memory_file);
    return runtime_full_memory;
}


int* divide_int_memory(unsigned char *runtime_full_memory) {

    int *int_data = malloc(64);
    if (!int_data) return NULL;
    memcpy(int_data, &runtime_full_memory[0], sizeof(int) * 16);
    
    return int_data;
}

unsigned char* divide_char_memory(unsigned char *runtime_full_memory) {
    unsigned char *char_data = malloc(16);
    if (!char_data) return NULL;
    memcpy(char_data, &runtime_full_memory[64], 16);

    return char_data;
}

int update_memory(unsigned char *runtime_full_memory, int *int_bytes, unsigned char *char_bytes) {
    printf("Updating memory...\n");
    FILE *memory_file = fopen("memory.bin", "wb");
    if (!memory_file) {
        perror("Cannot open the file");
        return 1;
    }

    printf("int_bytes index 1: %d\n", int_bytes[1]); // muestra 40

    // runtime_full_memory size = 80 bytes.
    memcpy(runtime_full_memory, &int_bytes[0], sizeof(int) * 16);
    memcpy(runtime_full_memory + 64, &char_bytes[64], 16);

    fwrite(runtime_full_memory, sizeof(char), 80, memory_file);
    fclose(memory_file);

    return 0;
}
// ---------------------------------------


// ---------------------------------------
// Debugging
int read_binary() {
    FILE *memory_file = fopen("memory.bin", "rb");

    if (!memory_file) {
        perror("Cannot open the file");
        return 1;
    }

    unsigned char byte = 0;
    int bytes_count = 0;
    while(fread(&byte, 1, 1, memory_file) == 1) {
        printf("%d\n", byte);
        bytes_count++;
    }
    printf("Total bytes count: %d\n", bytes_count);

    fclose(memory_file);
    return 0;
}
// ---------------------------------------


// ---------------------------------------
// User interaction
char define_task() {
    char choosed_task;    
    int flag = 1;

    while (flag == 1) {
        printf("Define the task type you want to do --\nw: Write\nr: Read.\n");
        scanf(" %c", &choosed_task);

        if (choosed_task == 'w' || choosed_task == 'r') {
            flag = 0;
        }
        else {
            printf("The task choosed doesn't exist.\n");
            flag = 1; // flag set to 1 again so the sentinel loop stills running
        }
    }
    return choosed_task;
}

char define_datatype() {
    char choosed_type = 0;
    int flag = 1;

    while (flag == 1) {
        printf("Define datatype you want to access --\ni: int\nc: char\n");
        scanf(" %c",  &choosed_type);

        if (choosed_type == 'i' || choosed_type == 'c') {
            flag = 0;
        }
        else {
            printf("The task choosed doesn't exist.\n");
            flag = 1; // flag set to 1 again so the sentinel loop stills running
        }
    }
    return choosed_type;
}
// ---------------------------------------


// ---------------------------------------
// Reading data
void read_int(int *int_bytes) {
    int index = 0;

    printf("Select index you want to read for int:\n");
    scanf("%d", &index);

    if (index <= 15) {
        printf("Your data: %d.\n", int_bytes[index]);
    }
    else printf("Out of index.\n");
}

void read_char(unsigned char *char_bytes) {
    int index = 0;
    printf("Select index you want to read for char:\n");
    scanf("%d", &index);

    if (index <= 15) {
        printf("Your data: %d.\n", char_bytes[index]);
    }
    else printf("Out of index.\n");
}
// ---------------------------------------


// ---------------------------------------
// Modify data
void modify_int(int *int_bytes) {
    int index = 0;
    printf("Select index you want to modify for int:\n");
    scanf("%d", &index);

    if (index <= 15) {
        int new_value = 0;
        printf("Actual value: %d\n", int_bytes[index]);
        printf("Select new value:\n");
        scanf("%d", &new_value);
        int_bytes[index] = new_value;
    }
    else printf("Out of index.\n");
}

void modify_char(unsigned char *char_bytes) {
    int index = 0;
    printf("Select index you want to modify for char:\n");
    scanf("%d", &index);

    if (index <= 15) {
        int new_value = 0;
        printf("Actual value: %d\n", char_bytes[index]);
        printf("Select new value:\n");
        scanf("%d", &new_value);
        char_bytes[index] = new_value;
    }
    else printf("Out of index.\n");
}


int main() {

    FILE *memory_file = fopen("memory.bin", "r");

    if (!memory_file) {
        startup_memory();
    }
    fclose(memory_file);

    char task = define_task();
    char type = define_datatype();
    unsigned char *runtime_full_memory = load_into_memory();

    // separate full memory by type
    int *int_bytes = divide_int_memory(runtime_full_memory);
    unsigned char *char_bytes = divide_char_memory(runtime_full_memory);

    if (task == 'r' && type == 'i') {
        read_int(int_bytes);
    }
    else if (task == 'r' && type == 'c') {
        read_char(char_bytes);
    }
    else if (task == 'w' && type == 'i') {
        modify_int(int_bytes);
        update_memory(runtime_full_memory, int_bytes, char_bytes);
    }
    else if (task == 'w' && type == 'c') {
        modify_char(char_bytes);
        update_memory(runtime_full_memory, int_bytes, char_bytes);
    }

    free(int_bytes);
    free(char_bytes);
    return 0;
}
