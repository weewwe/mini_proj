#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "base.h"

// Function: print_names()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// To print names
void print_names(Record records[]) {
    // TODO: Modify this function as you need
    int len = 100;
    int i = 0;
    while (i < len) {
        if (i >= len) break;
        if (records[i].id == 0 && records[i].name[0] == '\0') break;
        if (records[i].id != 0 && records[i].name[0] == '\0') printf("  no.%d : empty\n", i + 1);
        if (records[i].name[0] != '\0') printf("  no.%d : %s\n", i + 1, records[i].name);
        i++;
    }
    printf("\n");
}

// Function: print_ids()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// To print ids
void print_ids(Record records[]) {
    // TODO: Modify this function as you need
    int len = 100;
    int i = 0;
    while (i < len) {
        if (i >= len) break;
        if (records[i].id == 0 && records[i].name[0] == '\0') break;
        if (records[i].id == 0 && records[i].name[0] != '\0') printf("  no.%d : empty\n", i + 1);
        if (records[i].id != 0) printf("  no.%d : %d\n", i + 1, records[i].id);
        i++;
    }
    printf("\n");
}

// Function: print_records()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// To print whole data or part of data
void print_records(Record records[]) {
    // TODO: Modify this function as you need
    int len = 100;
    int i = 0;
    int ch = 0;
    printf("Choose the option(0 for all, 1 for ids, 2 for names): ");
    scanf("%d", &ch);
    printf("\n");
    if (ch == 0) {
        while (i < len) {
            if (i >= len) break;
            if (records[i].id == 0 && records[i].name[0] == '\0') break;
            if (records[i].id != 0 && records[i].name[0] == '\0') {
                printf(" no.%d : %d\t", i + 1, records[i].id);
                printf("  name : empty\n");
            }
            if (records[i].id == 0 && records[i].name[0] != '\0') {
                printf(" no.%d : empty\t", i + 1);
                printf("  name : %s\n", records[i].name);
            }
            if (records[i].id != 0 && records[i].name[0] != '\0') {
                printf(" no.%d : %d\t", i + 1, records[i].id);
                printf("  name : %s\n", records[i].name);
            }
            i++;
        }
        printf("\n");
    }
    else if (ch == 1) print_ids(records);
    else print_names(records);
}

// Function: add_stdin()
// Input: record - array of Records; this may contain empty elements in the middle
//        i - integer; entire number of member
// Output: i - integer; number of added member
// To add members until user enter -1
int add_stdin(Record records[], int i) {
    int stop = 0;
    while (1) {
        printf("Enter the id number(-1 for quit): ");
        scanf("%d", &records[i].id);
        if (records[i].id == -1) {
            records[i].id = 0;
            break;
        }
        //else if (records[i].id == records[i - 1].id) {
        //    printf("Error! Try again!\n");
        //    continue;
        //}
        printf("Enter the name: ");
        scanf("%s", records[i].name);
        i++;
    }
    return i;
}

// Function: add_file()
// Input: record - array of Records; this may contain empty elements in the middle
//        i - integer; entire number of member
// Output: i - integer; number of added member
// To add members as a file
int add_file(Record records[], int i) {
    int j = 0;
    char buffer[100];
    char* arr[100] = { NULL, };
    FILE* fp = fopen("data.txt", "r");

    while (!feof(fp)) {
        j = 0;
        fgets(buffer, sizeof(buffer), fp);
        if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
        char *ptr = strtok(buffer, " ");
        while (ptr != NULL) {
            arr[j] = ptr;
            ptr = strtok(NULL, " ");
            if (ptr == NULL) {
                char first = *arr[j];
                if (isdigit(first)) records[i].id = atoi(arr[j]);
                else strcpy(records[i].name, arr[j]);
                break;
            }
            if (j == 0) records[i].id = atoi(arr[j]);
            //if (j == 1) strcpy(records[i].name, arr[j]);
            j++;
        }
        i++;
    }
    fclose(fp);
    return i;
}

// Function: add_a_record()
// Input: record - array of Records; this may contain empty elements in the middle
//        entire - integer; entire number of members
// Output: entire - integer; number of added members
// To add a member as a add_stdin or members as a add_file, and save as a file named 
// "new.txt"
int add_a_record(Record records[], int entire) {
    // TODO: Modify this function as you need
    int ch = 0;
    printf("Choose how to add a record(1 for stdin, 2 for file): ");
    scanf("%d", &ch);
    printf("\n");
    if (ch == 1) entire = add_stdin(records, entire);
    else if (ch == 2) entire = add_file(records, entire);
    else printf("Wrong choice!\n");

    FILE* fp = fopen("new.txt", "w");
    for (int i = 0; i < entire; i++) {
        if (records[i].id != 0 && records[i].name[0] == '\0') {
            fprintf(fp, "%d", records[i].id);
            fputs("\tempty\n", fp);
        }
        if (records[i].id == 0 && records[i].name[0] != '\0') {
            fputs("empty\t", fp);
            fwrite(records[i].name, strlen(records[i].name), 1, fp);
            fputs("\n", fp);
        }
        if (records[i].id != 0 && records[i].name[0] != '\0') {
            fprintf(fp, "%d", records[i].id);
            fputs("\t", fp);
            fwrite(records[i].name, strlen(records[i].name), 1, fp);
            fputs("\n", fp);
        }
    }
    fclose(fp);
    return entire;
}
