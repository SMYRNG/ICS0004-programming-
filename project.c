#include <stdio.h>

int main(void) {
    while (1) {
        char is_procces_done = '-';

        printf("Do you want to make a transaction? (y/n) ");
        if (scanf_s(" %c", &is_procces_done, 1) != 1) {
            return 1;
        }

        switch (is_procces_done) {
        case 'n':
            return 0;
        case 'y':
            printf("main\n");
            break;
        default:
            printf("Error! %c is not a valid input.\n", is_procces_done);
            break;
        }
    }
}
