
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ORDERS 50

struct order {
    char name[50];
    char surname[50];
    bool is_urgent;
    char urgent_choice;
    // 1 - photo printing, 2 - film development, 3 - both
    int type_of_order;
    char time_of_order[16];
};

int user_order_creation(struct order orders[], int order_amount,
    const char* order_time)
{
    printf("Please fill form:\n");

    printf("Name: ");
    if (scanf_s("%49s", orders[order_amount].name,
        (unsigned)sizeof orders[order_amount].name) != 1) {
        return 0;
    }

    printf("Surname: ");
    if (scanf_s("%49s", orders[order_amount].surname,
        (unsigned)sizeof orders[order_amount].surname) != 1) {
        return 0;
    }

    printf("Is the order urgent? (y/n): ");
    if (scanf_s(" %c", &orders[order_amount].urgent_choice, 1) != 1) {
        return 0;
    }

    orders[order_amount].is_urgent =
        (orders[order_amount].urgent_choice == 'y' ||
            orders[order_amount].urgent_choice == 'Y');

    printf("Type of order (1-3): ");
    if (scanf_s("%d", &orders[order_amount].type_of_order) != 1 ||
        orders[order_amount].type_of_order < 1 ||
        orders[order_amount].type_of_order > 3) {
        printf("Invalid order type.\n");
        return 0;
    }

    snprintf(orders[order_amount].time_of_order,
        sizeof orders[order_amount].time_of_order,
        "%s", order_time);

    printf("Order created for: %s %s\n\n",
        orders[order_amount].name,
        orders[order_amount].surname);

    return 1;
}

void user_menu(struct order orders[], int* order_amount,
    const char* order_time)
{
    char choice;

    while (1) {
        printf("Available user options:\n"
            "1. Create new order\n"
            "2. View order status\n"
            "Q - Quit\n"
            "Please select option: ");

        if (scanf_s(" %c", &choice, 1) != 1) {
            return;
        }

        switch (choice) {
        case '1':
            if (*order_amount >= MAX_ORDERS) {
                printf("Maximum number of orders reached.\n");
                break;
            }

            if (user_order_creation(orders, *order_amount,
                order_time)) {
                (*order_amount)++;
            }
            break;

        case '2':
            printf("Total orders: %d\n", *order_amount);
            for (int i = 0; i < *order_amount; i++) {
                printf("%d. %s %s | Urgent: %s | Type: %d\n",
                    i + 1,
                    orders[i].name,
                    orders[i].surname,
                    orders[i].is_urgent ? "Yes" : "No",
                    orders[i].type_of_order);
            }
            break;

        case 'q':
        case 'Q':
            return;

        default:
            printf("Invalid input: %c\n", choice);
            break;
        }
    }
}

int main(void)
{
    struct order orders[MAX_ORDERS] = { 0 };

    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char buffer[16] = "unknown";

    if (t != NULL) {
        strftime(buffer, sizeof buffer, "%m%Y", t);
    }

    char type_of_pov;
    int order_amount = 0;

    while (1) {
        printf("Who is using the program? "
            "(u-user, a-admin, p-photographer, q-quit): ");

        if (scanf_s(" %c", &type_of_pov, 1) != 1) {
            return 1;
        }

        switch (type_of_pov) {
        case 'u':
            user_menu(orders, &order_amount, buffer);
            break;

        case 'a':
            printf("Admin view\n");
            break;

        case 'p':
            printf("Photographer view\n");
            break;

        case 'q':
        case 'Q':
            return 0;

        default:
            printf("Invalid input: %c\n", type_of_pov);
            break;
        }
    }
}
