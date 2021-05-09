#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include"database.h"
#include"sequence.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/*
 * Verilen iki char dizisinin benzerligini bulur.
 * Bu islemi Levenshtein uzakligi kullanarak yapar.
 */
int find_distance(char* seq1,char* seq2){
   int distance, replace, insert, delete;
   int lenSeq1 = strlen(seq1), lenSeq2 = strlen(seq2);
   int** matrix = malloc((lenSeq1+1)*sizeof(int *));
   for(int i = 0; i <= lenSeq1; ++i) matrix[i] = malloc((lenSeq2+1)*sizeof(int));
   for(int i = 0; i <= lenSeq1; ++i) matrix[i][0] = i;
   for(int j = 0; j <= lenSeq2; ++j) matrix[0][j] = j;

   for(int i = 1; i <= lenSeq1; ++i){
      for(int j = 1; j <= lenSeq2; ++j){
         if(seq1[i-1]!=seq2[j-1]){
            if(i == j && i == 1){
               matrix[i][j] = 1;
               continue;
            }
            replace = matrix[i-1][j-1];
            delete = matrix[i-1][j];
            insert = matrix[i][j-1];
            replace = MIN(replace, insert);
            replace = MIN(replace, delete);
            matrix[i][j] = replace + 1;
         }else{
            matrix[i][j] = matrix[i-1][j-1];
         }
      }
   }
   distance = matrix[lenSeq1][lenSeq2];
   for(int i = 0; i <= lenSeq1; ++i)free(matrix[i]);
   free(matrix);
   return distance;
}

/*
 * Parametre olarak verilen karakter dizisine
 * veri tabanı içerisinde benzeyen ilk k
 * kişi idsini geri döndürür.
 * Bu idler bir dizide saklanır.
 * En benzer idler, uzakligi en dusuk olanlardir.
 */
int* find_similar_first(char* seq1, Dtbase* dbt,int k){
  int* similar_ids = calloc(k, sizeof(int));
  /*
   int min, index = 0;

   for(int j = 0; j < k; j++){
      min = find_distance(seq1,dbt->db[j].sequence);
      for(int i = j+1; i < dbt->size; ++i){
         if(min >= find_distance(seq1, dbt->db[i].sequence)){
            int flag = 0;
            for(int p = 0; p < j; ++p){
               if(dbt->db[i].id == similar_ids[p]){flag = 1; break;}
            }
            if(flag == 1) continue;
            min = find_distance(seq1, dbt->db[i].sequence);
            index = i;
         } 
      }
      similar_ids[j] = dbt->db[index].id;
   }
   */
   
   int j, count = 0;
   Hash* hashtable[SIZE];
   for (int p=0; p<SIZE; p++){
      hashtable[p] = calloc(1, sizeof(Hash));
      hashtable[p]->id = -1;
      hashtable[p]->next = NULL;
   } 

   for(int i = 0; i<dbt->size; i++){
      int hashIndex = find_distance(seq1,dbt->db[i].sequence);
      Hash* hash_node = hashtable[hashIndex];
      Hash* cur;
      
      if(hash_node->id == -1) hash_node->id = dbt->db[i].id;
      else{
         for(cur = hash_node; cur->next != NULL; cur = cur->next);
         Hash* next = calloc(1, sizeof(Hash));
         next->next = NULL;
         next->id = dbt->db[i].id;
         cur->next = next;
      } 
   }

   for(j = 0; j<SIZE; j++){
      for(Hash* curr = hashtable[j]; curr != NULL; curr = curr->next){
         similar_ids[count] = curr->id;
         count++;
      }
      if(count == k) break;
   }

   if(count<k){
      similar_ids = realloc(similar_ids, sizeof(int)*count);
   } 

   return similar_ids;
}

/*
 * Parametre olarak verilen dizi icin
 * Rabin parmakizini hesaplar.
 * seq  : parmakizi hesaplanacaj deger
 * prime: kullanilacak asal sayi
 * size : seq dizisinin boyutu
 * Ornek: dizi  = abr prime=101 ise
 *        sonuc = 97*101^2 + 98*101^1 + 114*101^0 = 999509
 *
 */
double finger_print(char* seq,int prime,int size){
    int i;
    double sum = 0;
    for(i=0;i<size;i++){
       sum += seq[i]*pow(prime,(size-i-1));
    }
    return sum;
  }

/*
 * Verilen bir gen dizisini DNA dizisi içerisinde arar.
 * Klasik string arama algoritmasini kullanir.
 * seq         : aranacak dizi
 * size        : seq dizisinin boyutu
 * dnaseqeunce : seq geninin aranacagi DNA dizisi
 * Gen bulunursa fonksiyon found=1 dondurur, bulunamazsa found=0.
 * Ornek : seq = ACG size = 3 dnaSequence = TTGACGT found=1
 *         seq = ACG size = 3 dnaSequence = TTGAGGT found=0
 */
int find_gene_classic(char* seq,int size, char dnasequence[SIZE]){
	int found=0;
   for(int i = 0; i<SIZE; i++){
      if(dnasequence[i]==seq[0]){
         found=1;
         for(int j = 1; j<size; j++){
            if(dnasequence[i+j]!=seq[j]){
               found=0;
               break;
            }
         }
         if(found==1) break;
      }
   }
	// varsa found=1 olarak dondur.
	return found;
}

/*
 * Verilen bir gen dizisini DNA dizisi içerisinde arar.
 * Rabin-Karp string arama algoritmasini kullanir.
 * seq         : aranacak dizi
 * size        : seq dizisinin boyutu
 * dnaseqeunce : seq geninin aranacagi DNA dizisi
 * Gen bulunursa fonksiyon found=1 dondurur, bulunamazsa found=0.
 * Ornek : seq = ACG size = 3 dnaSequence = TTGACGT found=1
 *         seq = ACG size = 3 dnaSequence = TTGAGGT found=0
 */
int find_gene_rabinkarp(char* seq,int size, char dnasequence[SIZE],int prime){
   int found=0;
   double hashseq=0.0;
   double hashdna=0.0;
   int i=0,j=0;
   hashseq=finger_print(seq,prime,size);
   for(i=0;i<SIZE-size;i++){
     hashdna=finger_print(&dnasequence[i],prime,size);
      if(hashseq==hashdna){
         for(j=0;j<size;j++){
            if(dnasequence[i+j]!=seq[j]){
               break;
            }
         }
       found=1;
      }
   }
    return found;
}

/*
 * Parametre olarak verilen gen dizisini bir veri tabani
 * icinde arar, diziye sahip bireylerin idsini geri döndürür.
 */
int *find_gene_persons(char* seq,int size,Dtbase dbt){
   int *ids=malloc(sizeof(int)*dbt.size);
   int i=0,say=0,find=0,count=0,j=0;
   for(i=0;i<dbt.size;i++){
       find=find_gene_rabinkarp(seq,size,dbt.db[i].sequence,101);
      if(find==1){
         say=i;
          count++;
           while(j<count){
       ids[j]=dbt.db[say].id;
                   j++;
                   }
                }
           }
    printf("Toplamda bulunan birey sayisi: %d\n",count);
    return ids;
}
