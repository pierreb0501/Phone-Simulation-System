#ifndef MINI5PHONE_H
#define MINI5PHONE_H

struct PHONE_NODE {
    char name[50];
    char birthdate[12];
    char phone[15];
    struct PHONE_NODE *next;
};

int loadCSV(char *filename);
int saveCSV(char *filename);
int addRecord(char name[], char birth[], char phone[]);
int deleteRecord(char name[]);
int clearRecords();
struct PHONE_NODE *findRecord(char name[]);
void printHeading();
void printContent(char *name, char *birth, char *phone);
int listRecords();

#endif // MINI5PHONE_H

