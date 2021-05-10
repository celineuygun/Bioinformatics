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
// Dtbase* read_person_file(char* filename){
//   Dtbase* dbt = calloc(1, sizeof(Dtbase));
//    if(!dbt) exit(1);
//    char buffer[BUFFER_SIZE];
//    int lenBuf = 0, idNo, j = 0;
//    char name[NSIZE], first[SIZE], second[SIZE];
//    FILE *fp = fopen(filename, "r");
//    if(!fp){printf("Dosya acilamadi. Dogru dosya ismini girdiginizden emin olun.\n"); exit(1);}
//    while(fgets(buffer, BUFFER_SIZE, fp) != NULL){
//       lenBuf = strlen(buffer);
//       buffer[lenBuf - 1] = (buffer[lenBuf - 1] == '\n') ? '\0' : buffer[lenBuf - 1];                       
//       sscanf(buffer, "%d %s %s %s", &idNo, name, first, second);
//       for(int i = 0; first[i] != '\0' || second[i] != '\0'; ++i){
//          if((first[i] == 'A' && second[i] == 'T') || (first[i] == 'T' && second[i] == 'A'));
//          else if((first[i] == 'G' && second[i] == 'C') || (first[i] == 'C' && second[i] == 'G'));
//          else{
//             dbt->corrupted++;
//             j--;
//             break;
//          }
//          if(first[i+1] == '\0'|| second[i+1] == '\0'){
//             dbt->db[j].id = idNo;
//             strcpy(dbt->db[j].name, name);
//             strcpy(dbt->db[j].sequence, first);
//             strcpy(dbt->db[j].pair, second);
//             dbt->size++;
//          }
//       }
//       ++j;
//    }
//    fclose(fp);
//    return dbt;
// }

Dtbase* read_person_file(char* filename, Dtbasecor* corr){
   int *cor_ind = calloc(SIZE, sizeof(int));
   Dtbase* dbt = calloc(1, sizeof(Dtbase));
   if(!dbt) exit(1);
   char buffer[BUFFER_SIZE];
   int lenBuf = 0, idNo, j = 0;
   char name[NSIZE], first[SIZE], second[SIZE];
   FILE *fp = fopen(filename, "r");
   if(!fp){printf("Dosya acilamadi. Dogru dosya ismini girdiginizden emin olun.\n"); exit(1);}
   while(fgets(buffer, BUFFER_SIZE, fp) != NULL){
      int counter = 0;
      lenBuf = strlen(buffer);
      buffer[lenBuf - 1] = (buffer[lenBuf - 1] == '\n') ? '\0' : buffer[lenBuf - 1];                       
      sscanf(buffer, "%d %s %s %s", &idNo, name, first, second);
      for(int i = 0; first[i] != '\0' || second[i] != '\0'; ++i){
         if((first[i] == 'A' && second[i] == 'T') || (first[i] == 'T' && second[i] == 'A'));
         else if((first[i] == 'G' && second[i] == 'C') || (first[i] == 'C' && second[i] == 'G'));
         else{
            if(counter == 0) dbt->corrupted++;
            cor_ind[counter] = i;
            counter++;
            j--;
         }
         if(first[i+1] == '\0'|| second[i+1] == '\0'){
            if(counter == 0){
               dbt->db[j].id = idNo;
               strcpy(dbt->db[j].name, name);
               strcpy(dbt->db[j].sequence, first);
               strcpy(dbt->db[j].pair, second);
               dbt->size++;
               continue;
            }
            for(int i = counter; i < SIZE; ++i) cor_ind[i] = -1;
            for(int i = 0; i < SIZE; ++i) corr->db[corr->size].cor_ind[i] = cor_ind[i];
            corr->db[corr->size].id = idNo;
            strcpy(corr->db[corr->size].name, name);
            strcpy(corr->db[corr->size].sequence, first);
            strcpy(corr->db[corr->size].pair, second);
            corr->size++;
         }
      }
      ++j;
   }
   fclose(fp);
   free(cor_ind);
   return dbt;
}

/*
 * Parametre olarak verilen veri yapisinda
 * bulunan hatasiz verileri ekrana basar.
 */
void print_database(Dtbase* dbt){
   for(int i = 0; i < dbt->size; ++i){
      printf("\n============ KISI BILGISI\nID: %27d\nISIM: %25s\nSEQUENCE:  %20s\nPAIR:      %20s\n", 
                                                            dbt->db[i].id, dbt->db[i].name, dbt->db[i].sequence, dbt->db[i].pair);
   }
}

/*
 * Parametre olarak verilen kisinin
 * bilgilerini ve dna cift sarmal yapisini basar.
 */
void print_double_helix(Person db){
   printf("\n============ KISI BILGISI\nID: %27d\nISIM: %25s\nDNA:\n\n", db.id, db.name);
   for(int j = 0; db.sequence[j] != '\0' || db.pair[j] != '\0'; ++j){
      if(j % 4 == 0){
         if((j/4)%2 == 0)printf("  %c%c", db.sequence[j], db.pair[j]);
         else printf("  %c%c", db.pair[j], db.sequence[j]);
      }else if(j % 4 == 1 || j % 4 == 3){
         if((j/4)%2 == 0)printf(" %c--%c", db.sequence[j], db.pair[j]);
         else printf(" %c--%c", db.pair[j], db.sequence[j]);
      }else{
         if((j/4)%2 == 0)printf("%c----%c", db.sequence[j], db.pair[j]);
         else printf("%c----%c", db.pair[j], db.sequence[j]);
      }
      printf("\n");
   }
   printf("\n");
}

/*
 * Parametre olarak verilen kisinin
 * bilgilerini ve hatali dna cift sarmal yapisini basar.
 */
void print_double_helix_corr(cPerson db){
   int c;
   printf("\n============ KISI BILGISI\nID: %27d\nISIM: %25s\nDNA:\n\n", db.id, db.name);
   for(int j = 0; db.sequence[j] != '\0' || db.pair[j] != '\0'; ++j){
      if(j % 4 == 0){
         if((j/4)%2 == 0)printf("  %c%c", db.sequence[j], db.pair[j]);
         else printf("  %c%c", db.pair[j], db.sequence[j]);
      }else if(j % 4 == 1 || j % 4 == 3){
         if((j/4)%2 == 0)printf(" %c--%c", db.sequence[j], db.pair[j]);
         else printf(" %c--%c", db.pair[j], db.sequence[j]);
      }else{
         if((j/4)%2 == 0)printf("%c----%c", db.sequence[j], db.pair[j]);
         else printf("%c----%c", db.pair[j], db.sequence[j]);
      }
      for(c = 0; c < SIZE && db.cor_ind[c] != -1; ++c){
         if(db.cor_ind[c] == j) printf("  <- HATA");
      }
      printf("\n");
   }
   printf("\nESLESME HATASI SAYISI: %d\n", c);
}

/*
 * Parametre olarak verilen veri yapisinda
 * istenen id'ye sahip kisiyi binary search ile
 * bulur ve bilgilerini eger dist == 1 ise
 * dna_seq ile olan Levenshtein uzakligiyla yazdirir.
 */
void find_binary(Dtbase* dbt, int l, int r, int id, char* dna_seq, int dist){
   if(l <= r){
      int m = (l + r)/2;
      if(dbt->db[m].id == id){
         print_double_helix(dbt->db[m]); 
         if(dist) printf("UZAKLIK: %d\n", find_distance(dna_seq, dbt->db[m].sequence));
         return;
      }
      else if(dbt->db[m].id < id) find_binary(dbt, m + 1, r, id, dna_seq, dist);
      else find_binary(dbt, l, m - 1, id, dna_seq, dist);
   }
}
