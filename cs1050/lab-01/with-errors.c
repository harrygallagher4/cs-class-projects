#include <stdio.h>

int main(void) {
    int i, Y; // i -> x, Y -> y
    printf("\n Enter the first number: ") // missing semicolon
    scanf("%d", x); // should be pointer?

    printf("\n Enter the second number: ");
    scanf("%d", &y); // should not be pointer?

    if(x > y) {
        Printf("\n is the largest number", x); // Printf -> printf, needs %d for format
    } Else { // should be lower case
        printf("\n %d is the largest number", y);
    }

    printf("\n");
    return 0;
}
