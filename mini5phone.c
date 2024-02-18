#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mini5phone.h"

struct PHONE_NODE *phonebook_head = NULL;
int isEmptyCSV = 1;

int loadCSV(char *filename) {
    FILE *p = fopen(filename, "rt");
    char buffer[1000];
    int i, j;
    struct PHONE_NODE *current_node, *previous_node;

    if (p == NULL) {
        isEmptyCSV = 1;
        return 1;
    }

    fgets(buffer, 999, p);
    isEmptyCSV = 0;

    previous_node = NULL;
    fgets(buffer, 999, p);
    while (!feof(p)) {
        current_node = (struct PHONE_NODE *) malloc(sizeof(struct PHONE_NODE));

        for (j = 0, i = 0; i < 999 && buffer[i] != '\0' && buffer[i] != ','; i++, j++)
            current_node->name[j] = buffer[i];

        current_node->name[j] = '\0';
        i++;

        for (j = 0; i < 999 && buffer[i] != '\0' && buffer[i] != ','; i++, j++)
            current_node->birthdate[j] = buffer[i];

        current_node->birthdate[j] = '\0';
        i++;

        for (j = 0; i < 999 && buffer[i] != '\0' && buffer[i] != '\n'; i++, j++)
            current_node->phone[j] = buffer[i];

        current_node->phone[j] = '\0';

        current_node->next = NULL;
        if (previous_node == NULL)
            phonebook_head = current_node;
        else
            previous_node->next = current_node;

        previous_node = current_node;
        fgets(buffer, 999, p);
    }

    fclose(p);

    return 0;
}

int saveCSV(char *filename) {
    FILE *p = fopen(filename, "wt");
    struct PHONE_NODE *current_node;

    if (p == NULL) return 1;

    fprintf(p, "name,birthdate,phone\n");

    for (current_node = phonebook_head; current_node != NULL; current_node = current_node->next)
        fprintf(p, "%s,%s,%s\n", current_node->name, current_node->birthdate, current_node->phone);

    fclose(p);

    return 0;
}

int addRecord(char name[], char birth[], char phone[]) {
    struct PHONE_NODE *new_node, *current_node;

    new_node = (struct PHONE_NODE *) malloc(sizeof(struct PHONE_NODE));
    if (new_node == NULL) return 1;

    strcpy(new_node->name, name);
    strcpy(new_node->birthdate, birth);
    strcpy(new_node->phone, phone);
    new_node->next = NULL;

    if (phonebook_head == NULL) {
        phonebook_head = new_node;
    } else {
        for (current_node = phonebook_head; current_node->next != NULL; current_node = current_node->next);
        current_node->next = new_node;
    }

    isEmptyCSV = 0;

    return 0;
}

int deleteRecord(char name[]) {
    struct PHONE_NODE *current_node, *previous_node;

    for (previous_node = NULL, current_node = phonebook_head; current_node != NULL; previous_node = current_node, current_node = current_node->next) {
        if (strcmp(current_node->name, name) == 0) {
            if (previous_node == NULL)
                phonebook_head = current_node->next;

            else
                previous_node->next = current_node->next;

            free(current_node);
            return 0;
        }
    }

    return 1;
}

int clearRecords() {
    struct PHONE_NODE *current_node, *next_node;

    for (current_node = phonebook_head; current_node != NULL; current_node = next_node) {
        next_node = current_node->next;
        free(current_node);
    }

    phonebook_head = NULL;
    isEmptyCSV = 1;

    return 0;
}

struct PHONE_NODE *findRecord(char name[]) {
    struct PHONE_NODE *current_node;

    for (current_node = phonebook_head; current_node != NULL; current_node = current_node->next) {
        if (strcmp(current_node->name, name) == 0) return current_node;
    }

    return NULL;
}


void printHeading() {
    printf("---- NAME ---- ---- BIRTH DATE ---- ---- PHONE ----\n");
}

void printContent(char *name, char *birth, char *phone) {
    printf("%-14s %-20s %-10s\n", name, birth, phone);
}

int listRecords() {
    struct PHONE_NODE *current_node;

    if (phonebook_head == NULL || isEmptyCSV) return 1;

    printHeading();

    for (current_node = phonebook_head; current_node != NULL; current_node = current_node->next)
        printContent(current_node->name, current_node->birthdate, current_node->phone);

    return 0;
}


