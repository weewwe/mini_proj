#ifndef _BASE_H_
#define _BASE_H_

#include "record.h"

// function prototypes
void print_records(Record[]);
void print_ids(Record[]);
void print_names(Record[]);
int add_a_record(Record[], int);
int add_file(Record[], int);
int add_stdin(Record[], int);

#endif
