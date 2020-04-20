#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "extras.h"
// Function: swap()
// Input: Record pointer
// Output: none
// To swap records[i] and record[j]
void swap(Record* x, Record* y) {
    Record temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// Function: make_file()
// Input: record - array of Records; this may contain empty elements in the middle
//        mem_num - integer; entire number of member
// Output: none
// To save records in "new.txt"
void make_file(Record records[], int mem_num) {
    FILE* fp = fopen("new.txt", "w");
    for (int i = 0; i < mem_num; i++) {
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
}

// Function: defragment()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: 1 if successful, otherwise 0
// To collect all odd members at back of the data
int defragment(Record records[], int mem_num) {
    int flag = 0;
    int i = 0;
    int cnt = 0;
    int temp;
    while (i < mem_num) {
        if (cnt == mem_num) break;
        if (records[i].id != 0 && records[i].name[0] != '\0') {
            i++;
            cnt++;
            continue;
        }
        if (records[i].id != 0 && records[i].name[0] == '\0') {
            temp = i;
            while (temp < mem_num - 1) {
                swap(&records[temp], &records[temp + 1]);
                flag = 1;
                temp++;
            }
            temp = 0;
            cnt++;
            continue;
        }
        if (records[i].id == 0 && records[i].name[0] != '\0') {
            temp = i;
            while (temp < mem_num - 1) {
                swap(&records[temp], &records[temp + 1]);
                flag = 1;
                temp++;
            }
            temp = 0;
            cnt++;
            continue;
        }
    }
    make_file(records, mem_num);
    return flag;   // TODO: return 1 if defragment succeed; return 0 otherwise
}

// Function: sort_id()
// Input: record - array of Records; this may contain empty elements in the middle
//        mem_num - integer; entire number of member
// Output: none
// To sort data by id
void sort_id(Record records[], int mem_num) {
    Record temp;
    for (int i = 0; i < mem_num - 1; i++) {
        for (int j = 0; j < mem_num - i - 1; j++) {
            if (records[j + 1].id < records[j].id) {
                temp = records[j + 1];
                records[j + 1] = records[j];
                records[j] = temp;
            }
        }
    }
}

// Function: sort_name()
// Input: record - array of Records; this may contain empty elements in the middle
//        mem_num - integer; entire number of member
// Output: none
// To sort data by name
void sort_name(Record records[], int mem_num) {
    Record temp;
    for (int i = 0; i < mem_num - 1; i++) {
        for (int j = 0; j < mem_num - i - 1; j++) {
            if (strcmp(records[j + 1].name, records[j].name) < 0) {
                temp = records[j + 1];
                records[j + 1] = records[j];
                records[j] = temp;
            }
        }
    }
}

// Function: sort()
// Input: record - array of Records; this may contain empty elements in the middle
//        mem_num - integer; entire number of member
// Output: none
// To sort data
void sort(Record records[], int mem_num) {
    int ch = 0;
    printf("Choose the option(0 for sorted by id, 1 for sorted by name): ");
    scanf("%d", &ch);
    printf("\n");
    if (ch == 0) sort_id(records, mem_num);
    else if (ch == 1) sort_name(records, mem_num);
    make_file(records, mem_num);
    return;
}

// Function: delete_record()
// Input: record - array of Records; this may contain empty elements in the middle
//        mem_num - integer; entire number of member
// Output: none
// To delete chosen member
void delete_record(Record records[], int mem_num) {
    int ch = 0;
    int i = 0;
    printf("Select member number you want to delete: ");
    scanf("%d", &ch);
    printf("\n");
    ch--;
    while (ch < mem_num - 1) {
        swap(&records[ch], &records[ch + 1]);
        ch++;
    }
    records[ch].id = 0;
    while (records[ch].name[i] != '\0') records[ch].name[i] = '\0';
    make_file(records, mem_num);
}

// Function: find_record()
// Input: record - array of Records; this may contain empty elements in the middle
//        mem_num - integer; entire number of member
// Output: none
// To find the member with id or name and print out
void find_record(Record records[], int mem_num) {
    int ch = 0;
    int id_num = 0;
    int i = 0;
    int flag = 0;
    char name[10];
    printf("Choose number how to find(0 for id, 1 for name): ");
    scanf("%d", &ch);
    printf("\n");

    if (ch == 0) {
        printf("Enter the id: ");
        scanf("%d", &id_num);
        printf("\n");

        for (i = 0; i < mem_num; i++) {
            if (id_num == records[i].id) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            if (records[i].id != 0 && records[i].name[0] != '\0')
                printf(" no.%d: %d  name: %s\n\n", i + 1, records[i].id, records[i].name);
            if (records[i].id != 0 && records[i].name[0] == '\0')
                printf(" no.%d: %d  name: empty\n\n", i + 1, records[i].id);
        }
    }

    else if (ch == 1) {
        printf("Enter the name: ");
        scanf("%s", name);
        printf("\n");

        for (i = 0; i < mem_num; i++) {
            if (strcmp(name, records[i].name) == 0) break;
            flag = 1;
        }
        if (flag == 1) {
            if (records[i].id != 0 && records[i].name[0] != '\0')
                printf(" no.%d: %d  name: %s\n\n", i + 1, records[i].id, records[i].name);
            if (records[i].id == 0 && records[i].name[0] == '\0')
                printf(" no.%d: empty  name: %s\n\n", i + 1, records[i].name);
        }
    }
}

// Function: fix_detail()
// Input: record - array of Records; this may contain empty elements in the middle
//        mem_num - integer; entire number of member
// Output: none
// To fix all missing parts of members
void fix_detail(Record records[], int mem_num) {
    for (int i = 0; i < mem_num; i++) {
        if (records[i].id == 0 && records[i].name[0] != '\0') {
            printf("\nCurrent empty record: \n");
            printf(" no.%d: empty  name: %s\n", i + 1, records[i].name);
            printf("Enter the id: ");
            scanf("%d", &records[i].id);
            printf("Fixed empty record: \n");
            printf(" no.%d: %d  name: %s\n", i + 1, records[i].id, records[i].name);
        }
        if (records[i].id != 0 && records[i].name[0] == '\0') {
            printf("\nCurrent empty record: \n");
            printf(" no.%d: %d  name: empty\n", i + 1, records[i].id);
            printf("Enter the name: ");
            scanf("%s", records[i].name);
            printf("Fixed empty record: \n");
            printf(" no.%d: %d  name: %s\n", i + 1, records[i].id, records[i].name);
        }
    }
    make_file(records, mem_num);
}
