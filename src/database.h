#include<stdio.h>

#ifndef SRC_DATABASE_H_
#define SRC_DATABASE_H_

#define SIZE 21
#define NSIZE 25
#define DBSIZE 50000

typedef struct PRS{
    char sequence[SIZE];
    char pair[SIZE];
    int id;
    char name[NSIZE];
} Person;

typedef struct DB{
    Person db[DBSIZE];
    int corrupted;
    int size;
} Dtbase;

Dtbase* read_person_file(char* filename);
void print_database(Dtbase* db);
void print_double_helix(Person db);
void find_binary(Dtbase* dbt, int l, int r, int n, char* dna_seq);

#endif /* SRC_DATABASE_H_ */