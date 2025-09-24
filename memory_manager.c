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
    memset(mem.stored_chars, 0, 16);

    // store bytes in the .bin file
    fwrite(mem.stored_ints, sizeof(int), 16, memory);
    fwrite(mem.stored_chars, sizeof(char), 16, memory);

    fclose(memory);

    free(mem.stored_ints);
    free(mem.stored_chars);
    mem.stored_ints = NULL;
    mem.stored_chars = NULL;
}


char define_task() {
    char choosed_task;    
    int flag = 1;

    while (flag == 1) {
        printf("flag: %d\n", flag);
        printf("Define the task type you want to do --\nw: Write\nr: Read.\n");
        scanf("%1s", &choosed_task);

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
        scanf("%1s",  &choosed_type);

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



int read_binary() { // READ FOR DEBBUGING
    FILE *binary = fopen("memory.bin", "rb");

    if (!binary) {
        fclose(binary);
        perror("Cannot open the file");
        return 1;
    }

    unsigned char byte = 0;
    int bytes_count = 0;
    while(fread(&byte, 1, 1, binary) == 1) {
        printf("%d\n", byte);
        bytes_count++;
    }
    printf("total bytes count: %d", bytes_count);

    fclose(binary);
    return 0;
}


int main() {

    FILE *memory = fopen("memory.bin", "r");

    if (!memory) {
        startup_memory();
    }
    else {
        char task = define_task();
        char type = define_datatype();

        // debugging
        printf("task in main: %c\n", task);
        printf("type in main: %c\n", type);
        read_binary();
    }
    return 0;
}
