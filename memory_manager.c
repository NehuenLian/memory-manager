#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void startup_memory() {

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
    mem.stored_chars = malloc(SIZE);

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
        printf("Current_byte: %d. (%d).\n", current_byte, i);
        volatile_memory[i] = current_byte;
        i++;
    }
    fclose(file);
    return volatile_memory;
}


int read_binary() { // READ FOR DEBBUGING
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
    printf("total bytes count: %d\n", bytes_count);

    fclose(file);
    return 0;
}


char define_task() {
    char choosed_task;    
    int flag = 1;

    while (flag == 1) {
        printf("flag: %d\n", flag);
        printf("Define the task type you want to do --\nw: Write\nr: Read.\n");
        scanf(" %c", &choosed_task);

        if (choosed_task == 'w' || choosed_task == 'r') {
            printf("Choosed task: %c", choosed_task);
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
        printf("flag: %d\n", flag);
        printf("Define datatype you want to access --\ni: int\nc: char\n");
        scanf(" %c",  &choosed_type);

        if (choosed_type == 'i' || choosed_type == 'c') {
            printf("Choosed type: %c", choosed_type);
            flag = 0;
        }
        else {
            printf("The type choosed doesn't exist.\n");
            flag = 1; // flag set to 1 again so the sentinel loop stills running
        }
    }
    return choosed_type;
}


void read_char(unsigned char *memory) {
    int index = 0;

    printf("Select the memory index you want to read:\n");
    scanf("%d", &index);
    if (index <= 79) {
        printf("Index selected: %d", memory[index]);
    }
    else {
        printf("Error: out of index");
    }
}


int main() {

    FILE *file = fopen("memory.bin", "r");

    if (!file) {
        startup_memory();
    }
    else {
        char task = define_task();
        char type = define_datatype();
        printf("%c, %c", task, type); // 

        unsigned char *memory = load_into_memory();
        read_char(memory);
    }
    fclose(file);
    return 0;
}
