#include <stdio.h>

static void user_menu(void)
{
    char choice;

    while (1) {
        printf("Avaliable user options: \n" 
            "1. Create new order\n"
            "2. View order (dummy)\n"
            "Q - Quit\n"
            "Please select option: ");

        if (scanf_s(" %c", &choice, 1) != 1) {
            return;
        }

        while (getchar() != '\n');

        switch (choice) {
        case '1':
            printf("Creating order and going back\n");
            break;

        case 'q':
        case 'Q':
            return;

        default:
            printf("Error! %c is not a valid input.\n", choice);
            break;
        }
    }
}

int main(void)
{
    char type_of_pov;

    while (1) {
        printf(
            "Who is using the program? "
            "(u-user, a-admin, p-photographer, q-quit): "
        );

        if (scanf_s(" %c", &type_of_pov, 1) != 1) {
            return 1;
        }

        while (getchar() != '\n');

        switch (type_of_pov) {
        case 'u':
            user_menu();
            break;

        case 'a':
            printf("admin pov\n");
            break;

        case 'p':
            printf("photographer pov\n");
            break;
        
        case 'Q':
        case 'q':
            return 0;

        default:
            printf("Error! %c is not a valid input.\n", type_of_pov);
            break;
        }
    }
}