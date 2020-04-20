#ifndef _EXTRAS_H_
#define _EXTRAS_H_

#include "record.h"

// function prototypes
int defragment(Record[], int);
void sort(Record[], int);
void delete_record(Record[], int);
void find_record(Record[], int);
void fix_detail(Record[], int);
void make_file(Record[], int);

#endif
