#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "sequence.h"
#define BUFFER_SIZE 100

/*
 * Parametre olarak verilen dosyayi acar
 * ve icindeki verileri bir veri yapisinda saklar.
 */
Dtbase* read_person_file(char* filename){
   Dtbase* dbt = malloc(sizeof(Dtbase));
   if(!dbt) exit(1);
   char buffer[BUFFER_SIZE];
   int lenBuf = 0, idNo, j=0;
   char name[NSIZE], first[SIZE], second[SIZE];
   FILE *fp = fopen(filename, "r");
   if(!fp){printf("Dosya acilamadi. Dogru dosya ismini girdiginizden emin olun.\n"); exit(1);}
   while(fgets(buffer, BUFFER_SIZE, fp) != NULL){
      lenBuf = strlen(buffer);
      buffer[lenBuf - 1] = (buffer[lenBuf - 1] == '\n') ? '\0' : buffer[lenBuf - 1];                       
      sscanf(buffer, "%d %s %s %s", &idNo, name, first, second);
      for(int i = 0; first[i] != '\0' || second[i] != '\0'; ++i){
         if((first[i] == 'A' && second[i] == 'T') || (first[i] == 'T' && second[i] == 'A'));
         else if((first[i] == 'G' && second[i] == 'C') || (first[i] == 'C' && second[i] == 'G'));
         else{
            dbt->corrupted++;
            j--;
            break;
         }
         if(first[i+1]=='\0'|| second[i+1]=='\0'){
            dbt->db[j].id = idNo;
            strcpy(dbt->db[j].name, name);
            strcpy(dbt->db[j].sequence, first);
            strcpy(dbt->db[j].pair, second);
            dbt->size++;
         }
      }
      ++j;
   }
   fclose(fp);
   return dbt;
}

/*
 * Parametre olarak verilen veri yapisini
 * ekrana basar.
 */
void print_database(Dtbase* dbt){
   printf("\n=========== DATABASE INFO\nSIZE: %25d\nCORRUPTED: %20d\n", dbt->size, dbt->corrupted);
   for(int i = 0; i < dbt->size; ++i){
      printf("\n============= PERSON INFO\nID: %27d\nNAME: %25s\nSEQUENCE:  %20s\nPAIR:      %20s\n", 
                                                            dbt->db[i].id, dbt->db[i].name, dbt->db[i].sequence, dbt->db[i].pair);
   }
}

/*
 * Parametre olarak verilen kisinin
 * bilgilerini ve dna cift sarmal yapisini basar.
 */
void print_double_helix(Person db){
   printf("\n============= PERSON INFO\nID: %27d\nNAME: %25s\nDNA:\n\n", db.id, db.name);
   for(int j = 0; db.sequence[j] != '\0' || db.pair[j] != '\0'; ++j){
      if(j % 4 == 0){
         if((j/4)%2==0)printf("  %c%c", db.sequence[j], db.pair[j]);
         else printf("  %c%c", db.pair[j], db.sequence[j]);
      }else if(j % 4 == 1 || j % 4 == 3){
         if((j/4)%2==0)printf(" %c--%c", db.sequence[j], db.pair[j]);
         else printf(" %c--%c", db.pair[j], db.sequence[j]);
      }else{
         if((j/4)%2==0)printf("%c----%c", db.sequence[j], db.pair[j]);
         else printf("%c----%c", db.pair[j], db.sequence[j]);
      }
      printf("\n");
   }
   printf("\n");
}

void find_binary(Dtbase* dbt, int l, int r, int n, char* dna_seq){
   if(l <= r){
      int m = (l + r)/2;
      if(dbt->db[m].id == n){
         print_double_helix(dbt->db[m]); 
         printf("DISTANCE: %d\n", find_distance(dna_seq, dbt->db[m].sequence));
         return;
      }
      else if(dbt->db[m].id < n) find_binary(dbt, m + 1, r, n, dna_seq);
      else find_binary(dbt, l, m - 1, n, dna_seq);
   }
}