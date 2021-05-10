#include<stdio.h>

#ifndef SRC_DATABASE_H_
#define SRC_DATABASE_H_

#define SIZE 21
#define NSIZE 25
#define DBSIZE 50000

typedef struct hash {
  int id;
  struct hash *next;
} Hash;

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


typedef struct PRSC{
    char sequence[SIZE];
    char pair[SIZE];
    int id;
    char name[NSIZE];
    int cor_ind[SIZE];
} cPerson;

typedef struct DBC{
    cPerson *db;
    int size;
} Dtbasecor;

Dtbase* read_person_file(char* filename, Dtbasecor* corr);
void print_database(Dtbase* db);
void print_double_helix(Person db);
void print_double_helix_corr(cPerson db);
void find_binary(Dtbase* dbt, int l, int r, int id, char* dna_seq, int dist);

#endif /* SRC_DATABASE_H_ */