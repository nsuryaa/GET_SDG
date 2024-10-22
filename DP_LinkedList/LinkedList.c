#include "header.h"

// Create a linked list of students
void create(int n) {
    int i;
    struct student* k;

    first = (struct student*)malloc(sizeof(struct student));
    printf("\nEnter the first name of the student: ");
    scanf("%s", first->name);
    printf("\nEnter the roll number of the student: ");
    scanf("%s", first->roll);
    first->next = NULL;
    last = first;

    for (i = 1; i < n; i++) {
        k = (struct student*)malloc(sizeof(struct student));
        printf("\nEnter the first name of the student: ");
        scanf("%s", k->name);
        printf("\nEnter the roll number of the student: ");
        scanf("%s", k->roll);
        k->next = NULL;
        last->next = k;
        last = k;
    }
}

// Display the database of students
void display() {
    struct student* t = first;
    if (t == NULL) {
        printf("\nThe database is empty!\n");
        return;
    }
    while (t != NULL) {
        printf("\nThe roll number of the student: %s", t->roll);
        printf("\nFirst name of the student: %s", t->name);
        t = t->next;
    }
}

// Insert a student record after a specific roll number
void insertafter() {
    char r[10];
    int flag = 0;
    printf("\nEnter the roll number you want to insert after: ");
    scanf("%s", r);
    struct student* t = first;
    while (t != NULL) {
        if (strcasecmp(r, t->roll) == 0) {  // Use strcasecmp for case-insensitive comparison
            struct student* k = (struct student*)malloc(sizeof(struct student));
            printf("\nEnter the first name of the student: ");
            scanf("%s", k->name);
            printf("\nEnter the roll number of the student: ");
            scanf("%s", k->roll);
            k->next = t->next;
            t->next = k;
            flag = 1;
            break;
        }
        t = t->next;
    }
    if (flag == 0)
        printf("\nThe roll number not found!!!");
}

// Delete a student record by roll number
void del() {
    struct student *back, *k;
    char r[10];
    int flag = 0;

    printf("\nEnter the roll number you want to delete: ");
    scanf("%s", r);

    if (strcasecmp(r, first->roll) == 0) {
        k = first;
        first = first->next;
        free(k);
        flag = 1;
    } else {
        back = first;
        k = first->next;
        while (k != NULL) {
            if (strcasecmp(r, k->roll) == 0) {
                back->next = k->next;
                free(k);
                flag = 1;
                break;
            }
            back = k;
            k = k->next;
        }
    }

    if (flag == 0)
        printf("\nThe roll number not found!!!");
}

// Search for a student by roll number
void search() {
    char r[10];
    int flag = 0;
    printf("\nEnter the roll number you want to search: ");
    scanf("%s", r);
    struct student* t = first;
    while (t != NULL) {
        if (strcasecmp(r, t->roll) == 0) {
            printf("\nThe roll number is found in the list!!!\nThe name is %s", t->name);
            flag = 1;
            break;
        }
        t = t->next;
    }
    if (flag == 0)
        printf("\nThe roll number is not in the database!!");
}

int main() {
    int n, o = -1;

    while (o != 0) {
        printf("\n\nMENU\n");
        printf("\nEnter 1 for creating database");
        printf("\nEnter 2 for displaying database");
        printf("\nEnter 3 for inserting a record after another");
        printf("\nEnter 4 for deleting a record");
        printf("\nEnter 5 for searching a record");
        printf("\nEnter 0 for exit");
        printf("\nEnter your choice: ");
        scanf("%d", &o);

        switch (o) {
            case 1:
                printf("\nEnter the maximum size of the database: ");
                scanf("%d", &n);
                create(n);
                break;
            case 2:
                display();
                break;
            case 3:
                insertafter();
                break;
            case 4:
                del();
                break;
            case 5:
                search();
                break;
            case 0:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nYou have entered an invalid choice!!!");
        }
    }

    return 0;
}
