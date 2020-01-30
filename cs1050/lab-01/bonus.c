#include <stdio.h>

int main(void) {

    double distance = 0;
    double speed = 0;

    do {
        if(distance < 0)
            printf("Distance should be a positive number\n");

        printf("Enter the distance: ");
        scanf("%lf", &distance);
        distance /= 1600;
    } while(distance < 0);

    do {
        if(speed< 0)
            printf("Speed should be a positive number\n");

        printf("Enter the speed: ");
        scanf("%lf", &speed);
    } while(speed < 0);

    // intentionally making this an int
    int time = 3600 * (distance / speed);
    printf("Flight time of the plane is %d seconds\n", time);

    return 0;
}
