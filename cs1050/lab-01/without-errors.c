#include <stdio.h>

int main(void) {
    int x, y; // i -> x, Y -> y
    printf("\n Enter the first number: "); // missing semicolon
    scanf("%d", &x); // should be reference?

    printf("\n Enter the second number: ");
    scanf("%d", &y); // should not be reference?

    if(x > y) {
        printf("\n %d is the largest number", x); // Printf -> printf
    } else { // should be lower case
        printf("\n %d is the largest number", y);
    }

    printf("\n");
    return 0;
}
