#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PHONE 15
#define FILENAME "phonebook.txt"


void addContact() {
    char name[MAX_NAME], phone[MAX_PHONE];
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Phone: ");
    scanf(" %s", phone);
    fprintf(file, "%s -> %s\n", name, phone);
    fclose(file);
    printf("Contact saved successfully!\n");
}


void displayContacts() {
    char name[MAX_NAME], phone[MAX_PHONE];
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No contacts found.\n");
        return;
    }
    printf("\nContacts:\n");
    while (fscanf(file, " %[^,],%s", name, phone) != EOF) {
        printf("Name: %s \nPhone: %s\n", name, phone);
    }
    fclose(file);
}


void searchContact() {
    char name[MAX_NAME], phone[MAX_PHONE], search[MAX_NAME];
    int found = 0;
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No contacts found.\n");
        return;
    }
    printf("Enter name to search: ");
    scanf(" %[^\n]", search);
    while (fscanf(file, " %[^,],%s", name, phone) != EOF) {
        if (strcmp(name, search) == 0) {
            printf("Found! \nName: %s \nPhone: %s\n", name, phone);
            found = 1;
            break;
        }
    }
    if (!found) printf("Contact not found.\n");
    fclose(file);
}


void deleteContact() {
    char name[MAX_NAME], phone[MAX_PHONE], search[MAX_NAME];
    int found = 0;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter name to delete: ");
    scanf(" %[^\n]", search);
    while (fscanf(file, " %[^,],%s", name, phone) != EOF) {
        if (strcmp(name, search) == 0) {
            found = 1;
            continue;
        }
        fprintf(temp, "%s,%s\n", name, phone);
    }
    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    if (found) printf("Contact deleted successfully!\n");
    else printf("Contact not found.\n");
}


int main() {
    int choice;
    while (1) {
        printf("\nPhone Book\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
