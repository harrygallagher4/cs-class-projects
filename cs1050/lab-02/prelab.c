#include <stdio.h>

// I actually wrote this function, please don't think I cheated
void get(int* param, char prompt[]) {
    do {
        if(*param < 0)
            printf("Please enter a non-negative number!\n");

        printf(prompt);
        scanf("%d", param);
    } while(*param < 0);
}

int main(void) {

    int first, second;

    get(&first, "Enter the first number: ");
    get(&second, "Enter the second number: ");

    printf("ADDITION\n");
    printf("The sum of %d and %d is %d\n", first, second, first + second);

    printf("MULTIPLICATION\n");
    printf("The product of %d and %d is %d\n", first, second, first * second);

    return 0;
}
