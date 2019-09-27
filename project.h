#ifndef PROJECT_H

#include <stdio.h>
#include <stdlib.h>

struct data //list implementation
{
    struct data * prev;
    int cylinder;
    struct data * next;
};

int size,start;

void sort(struct data*);
void add(struct data**, int value);
struct data* insert(struct data **, int val);
void delete(struct data **,struct data *);
struct data* copy(struct data *head);

int FCFS(struct data*);
int SSTF(struct data*);
//int SCAN(struct data*);
//int CSCAN(struct data*);
int LOOK(struct data*);
int CLOOK(struct data*);

#endif
