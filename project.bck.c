#include <stdio.h>
#include <stdbool.h>

void user_order_creation(void)
{
    char name[50];
    char surname[50];
    bool is_urgent = false;
    // Type of orders: 1 - photo printing, 2 - film development, 3 - both
    int type_of_order = 0;

    printf("Please fill form:\n");
    printf("Name: ");
    scanf_s("%s", name, sizeof(name));
    printf("Surname: ");
    scanf_s("%s", surname, sizeof(surname));
    printf("Is the order urgent? (y/n): ");
    char urgent_choice;
    scanf_s(" %c", &urgent_choice, 1);
    is_urgent = (urgent_choice == 'y' || urgent_choice == 'Y');
    printf("Type of order (1-3): ");
    scanf_s("%d", &type_of_order);
    printf("Order created for: %s %s\n\n", name, surname);
}

static void user_menu(void)
{
    char choice;

    while (1) {
        printf("Avaliable user options: \n" 
            "1. Create new order\n"
            "2. View order status\n"
            "Q - Quit\n"
            "Please select option: ");

        if (scanf_s(" %c", &choice, 1) != 1) {
            return;
        }

        while (getchar() != '\n');

        switch (choice) {
        case '1':
            user_order_creation();
            break;
        case '2':
            printf("Viewing order status and going back\n");
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