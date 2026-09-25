#include <stdio.h>

int main(void) {
    while (1) {
    int cicle_switch = 1;
    char type_of_pov;
    printf("Who is using the programm? (u-user, a-admin, p-photographer, q-quit) ");
    if (scanf_s(" %c", &type_of_pov, 1) != 1) {
        return 1;
    }
    switch (type_of_pov) {
    case 'u':
        while (cicle_switch) {
            char is_procces_done = '-';
            printf("Do you want to make a transaction? (y/n) ");
            if (scanf_s(" %c", &is_procces_done, 1) != 1) {
                return 1;
            }
            switch (is_procces_done) {
            case 'n':
                cicle_switch = 0;
                break;
            case 'y':
                printf("main\n");
                break;
            default:
                printf("Error! %c is not a valid input.\n", is_procces_done);
                break;
            }
        }
        break;
    case 'a':
        printf("admin pov \n");
        break;
    case 'p':
        printf("photographer pov \n");
        break;
    case 'q':
        return 0;
    default:
        printf("Error! %c is not a valid input.\n", type_of_pov);
        break;
    }
    }
}
