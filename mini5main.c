#include<stdio.h>
#include "mini5phone.h"
#include <string.h>

int menu() {
    int selection;
    char garbage[5];

    printf("Phonebook Menu: (1)Add, (2)Delete/Clear, (3)Find, (4)List, (5)Quit > ");
    scanf("%d", &selection);
    fgets(garbage, 4, stdin);

    return selection;
}

int main() {
    int choice, record;
    char name[50], birth[50], phone[50];
    char delete_clear_choice;
    char garbage[5];

    loadCSV("phonebook.csv");

    do {
        choice = menu();

        switch (choice) {
            case 1:
                printf("Name: ");
                fgets(name, 49, stdin);
                name[strlen(name) - 1] = '\0';
                printf("Birth: ");
                fgets(birth, 12, stdin);
                birth[strlen(birth) - 1] = '\0';
                printf("Phone: ");
                fgets(phone, 14, stdin);
                phone[strlen(phone) - 1] = '\0';

                record = addRecord(name, birth, phone);
                if (record != 0) printf("CSV if out of space\n");

                break;
            case 2:
                printf("(D)elete or (C)lear> ");
                scanf(" %c", &delete_clear_choice);
                fgets(garbage, 4, stdin);

                if (delete_clear_choice == 'D' || delete_clear_choice == 'd') {
                    printf("Name: ");
                    fgets(name, 49, stdin);
                    name[strlen(name) - 1] = '\0';

                    record = deleteRecord(name);
                    if (record != 0) printf("Sorry, not found\n");

                } else if (delete_clear_choice == 'C' || delete_clear_choice == 'c') {
                    printf("Are you sure (Y/N)> ");
                    scanf(" %c", &delete_clear_choice);
                    fgets(garbage, 4, stdin);

                    if (delete_clear_choice == 'Y' || delete_clear_choice == 'y') {
                        clearRecords();
                    }
                }
                break;

       

    case 3:
                printf("Find name: ");
                fgets(name, 49, stdin);
                name[strlen(name) - 1] = '\0';

                struct PHONE_NODE *node = findRecord(name);

                if (node == NULL) printf("Does not exist\n");
                else {
                    printHeading();
                    printContent(node->name, node->birthdate, node->phone);
                }
                break;

     case 4:
                record = listRecords();

                if (record != 0) printf("Phonebook.csv does not exist\n");
                break;

            case 5:
                break;

            default:
                printf("Invalid menu selection\n");
        }
    } while (choice != 5);

    saveCSV("phonebook.csv");

    printf("End of phonebook program\n");

    return 0;
}

