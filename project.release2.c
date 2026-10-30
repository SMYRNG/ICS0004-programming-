#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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

// Read a whole line, including empty input.
// Returns 1 for a line, 0 for end of input, or -1 for a long line.
int read_input(char input[], int size)
{
    int ch;
    int i = 0;

    if (fgets(input, size, stdin) == NULL) {
        return 0;
    }

    while (input[i] != '\0') {
        i++;
    }

    if (i > 0 && input[i - 1] == '\n') {
        input[i - 1] = '\0';
    }
    else if (!feof(stdin)) {
        // Remove any characters that did not fit in the input array.
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }

    return 1;
}

// Treat lines containing only spaces or tabs as empty.
int is_blank(const char input[])
{
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ' && input[i] != '\t' && input[i] != '\r') {
            return 0;
        }
    }
    return 1;
}

// Names use a single word, just like the original scanf_s("%s") input.
int valid_name(const char input[])
{
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\r') {
            return 0;
        }
    }
    return 1;
}

int user_order_creation(struct order orders[], int order_amount,
    const char order_time[])
{
    printf("Please fill form:\n");

    struct order new_order = { 0 };
    char input[128];
    int result;

    // NAME VALIDATION
    while (1) {
        printf("Name: ");
        result = read_input(input, sizeof input);
        if (result == 0) {
            return 0;
        }
        if (result == -1 || strlen(input) > 49) {
            printf("Invalid name. Maximum 49 characters.\n");
        }
        else if (is_blank(input)) {
            printf("Invalid name. Name cannot be empty.\n");
        }
        else if (!valid_name(input)) {
            printf("Invalid name. Enter a single word.\n");
        }
        else {
            snprintf(new_order.name, sizeof new_order.name, "%.49s", input);
            break;
        }
    }

    // SURNAME VALIDATION
    while (1) {
        printf("Surname: ");
        result = read_input(input, sizeof input);
        if (result == 0) {
            return 0;
        }
        if (result == -1 || strlen(input) > 49) {
            printf("Invalid surname. Maximum 49 characters.\n");
        }
        else if (is_blank(input)) {
            printf("Invalid surname. Surname cannot be empty.\n");
        }
        else if (!valid_name(input)) {
            printf("Invalid surname. Enter a single word.\n");
        }
        else {
            snprintf(new_order.surname, sizeof new_order.surname, "%.49s", input);
            break;
        }
    }

    // URGENCY VALIDATION
    while (1) {
        printf("Is the order urgent? (y/n): ");
        result = read_input(input, sizeof input);
        if (result == 0) {
            return 0;
        }
        if (result == 1 && input[1] == '\0' &&
            (input[0] == 'y' || input[0] == 'Y' ||
             input[0] == 'n' || input[0] == 'N')) {
            new_order.urgent_choice = input[0];
            new_order.is_urgent = (input[0] == 'y' || input[0] == 'Y');
            break;
        }
        printf("Invalid urgency. Enter y or n.\n");
    }

    // ORDER TYPE VALIDATION
    while (1) {
        printf("Type of order (1 - Photo printing, 2 - Film development, 3 - Both): ");
        result = read_input(input, sizeof input);
        if (result == 0) {
            return 0;
        }
        if (result == 1 && input[1] == '\0' &&
            (input[0] == '1' || input[0] == '2' || input[0] == '3')) {
            new_order.type_of_order = input[0] - '0';
            break;
        }
        printf("Invalid order type. Enter 1, 2, or 3.\n");
    }

    snprintf(new_order.time_of_order,
        sizeof new_order.time_of_order,
        "%s", order_time);

    // Store the new order only after all input has been validated.
    orders[order_amount] = new_order;

    printf("Order created for: %s %s\n\n",
        new_order.name,
        new_order.surname);

    return 1;
}

int user_menu(struct order orders[], int order_amount,
    const char order_time[])
{
    char choice;
    char input[128];
    int result;

    while (1) {
        printf("Available user options:\n"
            "1. Create new order\n"
            "2. View order status\n"
            "Q - Quit\n"
            "Please select option: ");

        result = read_input(input, sizeof input);
        if (result == 0) {
            return order_amount;
        }
        if (result == -1 || input[0] == '\0' || input[1] != '\0') {
            printf("Invalid menu input. Enter 1, 2, or Q.\n");
            continue;
        }
        choice = input[0];

        switch (choice) {
        case '1':
            if (order_amount >= MAX_ORDERS) {
                printf("Maximum number of orders reached.\n");
                break;
            }

            if (user_order_creation(orders, order_amount,
                order_time)) {
                order_amount++;
            }
            break;

        case '2':
            printf("Total orders: %d\n", order_amount);
            for (int i = 0; i < order_amount; i++) {
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
            return order_amount;

        default:
            printf("Invalid input: %c\n", choice);
            break;
        }
    }
}

void admin_menu(const struct order orders[], int order_amount)
{
    char choice;
    char input[128];
    int result;

    while (1) {
        printf("Available admin options:\n"
            "1. View all orders\n"
            "Q - Quit\n"
            "Please select option: ");

        result = read_input(input, sizeof input);
        if (result == 0) {
            return;
        }
        if (result == -1 || input[0] == '\0' || input[1] != '\0') {
            printf("Invalid menu input. Enter 1 or Q.\n");
            continue;
        }
        choice = input[0];

        switch (choice) {
        case '1':
            printf("Total orders: %d\n", order_amount);
            if (order_amount == 0) {
                printf("No orders have been created.\n");
            }

            for (int i = 0; i < order_amount; i++) {
                printf("%d. %s %s | Urgent: %s | Type: %s | Time: %s\n",
                    i + 1,
                    orders[i].name,
                    orders[i].surname,
                    orders[i].is_urgent ? "Yes" : "No",
                    orders[i].type_of_order == 1 ? "Photo printing" :
                    orders[i].type_of_order == 2 ? "Film development" : "Both",
                    orders[i].time_of_order);
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
    struct tm local_time;
    char buffer[16] = "unknown";

    if (localtime_s(&local_time, &now) == 0) {
        strftime(buffer, sizeof buffer, "%m%Y", &local_time);
    }

    char type_of_pov;
    char input[128];
    int result;
    int order_amount = 0;

    while (1) {
        printf("Who is using the program? "
            "(u-user, a-admin, p-photographer, q-quit): ");

        result = read_input(input, sizeof input);
        if (result == 0) {
            return 1;
        }
        if (result == -1 || input[0] == '\0' || input[1] != '\0') {
            printf("Invalid menu input. Enter u, a, p, or q.\n");
            continue;
        }
        type_of_pov = input[0];

        switch (type_of_pov) {
        case 'u':
            order_amount = user_menu(orders, order_amount, buffer);
            break;

        case 'a':
            admin_menu(orders, order_amount);
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
