#include <stdio.h>
int main() {
    while (1) {
        //Gives a possibiliy to close the programm.
        char is_procces_done = "-";
        printf("Do you want to make a transaction? (y/n) ");
        scanf_s("%c", &is_procces_done);
        //Checks if input is valid
        switch (is_procces_done) {
        case 'n':
            break;
        case 'y':
            printf("main");
            continue;
        }
        printf("Error! %c is not a valid input. \n", is_procces_done);
    }
    return 0;
}