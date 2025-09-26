#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------
// Memory management
int startup_memory() {

    FILE *memory = fopen("memory.bin", "wb");

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
    fwrite(mem.stored_ints, sizeof(int), 16, memory);
    fwrite(mem.stored_chars, sizeof(char), 16, memory);

    fclose(memory);

    free(mem.stored_ints);
    free(mem.stored_chars);
    mem.stored_ints = NULL;
    mem.stored_chars = NULL;
}


unsigned char* load_into_memory() {
    FILE *file = fopen("memory.bin", "rb");
    static unsigned char volatile_memory[80];

    if (!file) {
        perror("Cannot open the file");
        return NULL;
    }

    unsigned char current_byte = 0;
    int i = 0;

    while (fread(&current_byte, 1, 1, file) == 1) {
        volatile_memory[i] = current_byte;
        i++;
    }
    fclose(file);
    return volatile_memory;
}


int* divide_int_memory(unsigned char *full_memory) {

    int *int_data = malloc(64);
    if (!int_data) return NULL;
    memcpy(int_data, &full_memory[0], sizeof(int) * 16);
    
    return int_data;
}

unsigned char* divide_char_memory(unsigned char *full_memory) {
    unsigned char *char_data = malloc(16);
    if (!char_data) return NULL;
    memcpy(char_data, &full_memory[64], sizeof(char) * 16);

    return char_data;
}
// ---------------------------------------


// ---------------------------------------
// Debugging
int read_binary() {
    FILE *file = fopen("memory.bin", "rb");

    if (!file) {
        perror("Cannot open the file");
        return 1;
    }

    unsigned char byte = 0;
    int bytes_count = 0;
    while(fread(&byte, 1, 1, file) == 1) {
        printf("%d\n", byte);
        bytes_count++;
    }
    printf("Total bytes count: %d\n", bytes_count);

    fclose(file);
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

    printf("Select index you want to read for int:\n"); // int data available only from 0 to 63
    scanf("%d", &index);

    if (index <= 15) {
        printf("Your data: %d.\n", int_bytes[index]);
    }
    else printf("Out of index.\n");

}

void read_char(unsigned char *char_bytes) {
    int index = 0;
    printf("Select index you want to read for char:\n"); // char data available only from 0 to 15
    scanf("%d", &index);

    if (index <= 15) {
        printf("Your data: %d.\n", char_bytes[index]);
    }
    else printf("Out of index.\n");
}
// ---------------------------------------


int main() {

    FILE *file = fopen("memory.bin", "r");

    if (!file) {
        startup_memory();
    }

    char task = define_task();
    char type = define_datatype();
    unsigned char *full_memory = load_into_memory();

    int *int_bytes = divide_int_memory(full_memory);
    unsigned char *char_bytes = divide_char_memory(full_memory);

    if (task == 'r' && type == 'i') {
        read_int(int_bytes);
    }
    if (task == 'r' && type == 'c') {
        read_char(char_bytes);
    }

    fclose(file);
    return 0;
}
