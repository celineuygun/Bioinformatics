#include"database.h"
#ifndef SEQUENCE_H_
#define SEQUENCE_H_

int find_distance(char* seq1, char*seq2);
int* find_similar_first(char* seq1, Dtbase* dbt, int k);
int find_gene_classic(char* seq, int size, char dnasequence[SIZE]);
int find_gene_rabinkarp(char* seq, int size, char dnasequence[SIZE], int prime);
int *find_gene_persons(char* seq, int size, Dtbase dbt);
double finger_print(char* seq, int prime, int size);
#endif /* SEQUENCE_H_ */
