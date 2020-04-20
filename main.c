#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "base.h"
#include "extras.h"
#include "record.h"

#define MAX_RECORDS 100

// function prototypes
int input_handler(char[], Record[], int);
void display_menu();

// main function
int main() {
    int entire_num = 0;
    Record records[MAX_RECORDS];
    memset(&records, 0, sizeof(records));
    for (int i = 0; i < MAX_RECORDS; i++) {
        records[i].id = 0;
        //strcpy(records[i].name, "\0");
    }
    char user_input[64] = "";
    while (strcmp(user_input, "99") != 0) {
        display_menu();
        printf("\nSelect a menu> ");
        scanf("%s", user_input);
        entire_num = input_handler(user_input, records, entire_num);
    }
    return 0;
}


// Function: input_handler()
// Input: record - array of Records; this may contain empty elements in the middle
// Output: none
// - Handles the user input and invokes functions that correspond to the user input
int input_handler(char input[], Record records[], int member_num) {
    // TODO: Modify this function as you need
    int flag = 0;
    if (!strcmp(input, "1")) {
        member_num = add_a_record(records, member_num);
        return member_num;
    }
    else if (!strcmp(input, "2")) {
        print_records(records);
        return member_num;
    }
    else if (!strcmp(input, "3")) {
        flag = defragment(records, member_num);
        if (flag == 1) printf("\ndefragment succeed.\n\n");
        else printf("No defragment.\n");
        return member_num;
    }
    else if (!strcmp(input, "4")) {
        sort(records, member_num);
        return member_num;
    }
    else if (!strcmp(input, "5")) {
        delete_record(records, member_num);
        return member_num;
    }
    else if (!strcmp(input, "6")) {
        find_record(records, member_num);
        return member_num;
    }
    else if (!strcmp(input, "7")) {
        fix_detail(records, member_num);
        return member_num;
    }
    else if (!strcmp(input, "99")) {
        printf("Terminating... bye!\n");
        return member_num;
    } // Quit - no operation (an empty statement with a semi-colon)
    else {
        printf("Unknown menu: %s \n\n", input);
        return member_num;
    }
}



// Function: display_menu()
// Input: none
// Output: none
// - Leave a brief information about the function
void display_menu() {

    // TODO: Modify this function as you need

    printf("******************************\n");
    printf(" Membership management system \n");
    printf("******************************\n");
    printf(" 1. Add a new member\n");
    printf(" 2. Print records\n");
    printf(" 3. Optimize (defragment) the records\n");
    printf(" 4. Sort records\n");
    printf(" 5. Delete record\n");
    printf(" 6. Find record\n");
    printf(" 7. Fix detail\n");
    printf(" 99. Quit\n");
}
