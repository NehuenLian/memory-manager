#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char define_task() {
    char choosed_task;    
    int flag = 1;

    while (flag == 1) { // sentinel loop
        printf("flag: %d\n", flag);
        printf("Define the task type you want to do --\nw: Write\nr: Read.\n");
        scanf("%1s", &choosed_task);

        if (choosed_task == 'w' || choosed_task == 'r') {
            printf("Choosed task: %c", choosed_task);
            flag = 0;
        }
        else {
            printf("The task choosed doesn't exist.\n");
            flag = 1; // flag set to 1 again so the loop stills running
        }
    }
    return choosed_task;
}

char define_datatype() {
    char choosed_type = 0;
    int flag = 1;

    while (flag == 1) { // sentinel loop
        printf("flag: %d\n", flag);
        printf("Define datatype you want to access --\ni: int\nc: char\n");
        scanf("%1s",  &choosed_type);

        if (choosed_type == 'i' || choosed_type == 'c') {
            printf("Choosed type: %c", choosed_type);
            flag = 0;
        }
        else {
            printf("The type choosed doesn't exist.\n");
            flag = 1; // flag set to 1 again so the loop stills running
        }
    }
    return choosed_type;
}

int main() {

// == Program start ==
    // struct that will represent all memory structure
    typedef struct Memory {
        int store_ints;
        char store_chars;
    } Mem;

    // define 2 arrays (16 bytes each)
    enum size {SIZE=16}; // 16 bytes
    int *arr_int = malloc(SIZE);
    char *arr_char = malloc(SIZE);
    // initialize both arrays with 0 in all indexes
    for (int i = 0; i < sizeof(arr_int); i++) {
        arr_int[i] = 0;
    }
    for (int i = 0; i < sizeof(arr_char); i++) {
         arr_char[i] = 0;
    }

    Mem mem = {*arr_int, *arr_char}; // store the dinamic arrays in the struct.
    // memset(arr_int, 0, 16);
    // memset(arr_char, 0, 16);
// =========================

    char task = define_task();
    printf("task in main: %c\n", task);

    char type = define_datatype();
    printf("type in main: %c\n", type);

    return 0;
}
