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
int find_distance(char* seq1, char* seq2){
   int distance, replace, insert, delete;
   int lenSeq1 = strlen(seq1), lenSeq2 = strlen(seq2); // stringlerin uzunlugu bulunur
   int** matrix = malloc((lenSeq1+1) * sizeof(int *)); // (lenSeq1+1)x(lenSeq2+1) matriks olusturulur ve yer acilir
   for(int i = 0; i <= lenSeq1; ++i) matrix[i] = malloc((lenSeq2+1) * sizeof(int));
   for(int i = 0; i <= lenSeq1; ++i) matrix[i][0] = i; // diger seq'in bos olmasi durumundaki uzakliklar matrikste depolanir
   for(int j = 0; j <= lenSeq2; ++j) matrix[0][j] = j;

   // matrix[0][0] = 0(her iki seq de bos, uzaklik = 0)
   for(int i = 1; i <= lenSeq1; ++i){ 
      for(int j = 1; j <= lenSeq2; ++j){
         if(seq1[i-1] != seq2[j-1]){ // ayni harf degillerse
            if(i == j && i == 1){ // tek harflilerse uzaklik 1 olur (replace, tek secenek)
               matrix[i][j] = 1;
               continue;
            } // tek harfli degillerse
            replace = matrix[i-1][j-1]; // harfi degistirdik olarak dusunup, iki seqte de o indexteki harfi yoksayariz
            delete = matrix[i-1][j]; //  bir seqteki harfi yok silmisiz olarak yoksayariz
            insert = matrix[i][j-1]; // bir seqe harf eklemis olarak dusunup ortak harfi yoksayariz
            // yoksayilan harfler disinda kalan seq'lerin distancelarini iclerinde bulundururlar
            replace = MIN(replace, insert);
            replace = MIN(replace, delete); // 3 islemden en kucuk distancei buluruz
            matrix[i][j] = replace + 1; // +1 ise 3 islemden herhangi birinin maliyetidir
         }else{ // eger ayni harf ise o harfe bakmamiza gerek kalmaz
            matrix[i][j] = matrix[i-1][j-1]; // o harfi yoksayariz, uzakliga bir etkisi yoktur
         }
      }
   }
   distance = matrix[lenSeq1][lenSeq2]; // matriksin en sag altinda kalan sayi aradigimiz uzakliktir
   for(int i = 0; i <= lenSeq1; ++i) free(matrix[i]);
   free(matrix); // kullandigimiz alani temizliyoruz
   return distance;
}

/*
 * Parametre olarak verilen karakter dizisine
 * veri tabanı içerisinde benzeyen ilk k
 * kişi idsini geri döndürür.
 * Bu idler bir dizide saklanır.
 * En benzer idler, uzakligi en dusuk olanlardir.
 */
int* find_similar_first(char* seq1, Dtbase* dbt, int k){
   int* similar_ids = calloc(k, sizeof(int));
   Hash **hashtable = calloc(SIZE, sizeof(Hash*));
   if(!similar_ids || !hashtable) exit(1);
   Hash *next, *curr, *hash_node;
   int count = 0;

   for(int p = 0; p < SIZE; p++){// hash table olusturulur
      hashtable[p] = calloc(1, sizeof(Hash));
      if(!hashtable[p]) exit(1);
      hashtable[p]->id = -1;
      hashtable[p]->next = NULL;
   } 
   for(int i = 0; i < dbt->size; i++){// dna sequence uzaklik degerlerine gore hash table icersine yerlestirilir
      int hashIndex = find_distance(seq1, dbt->db[i].sequence);
      hash_node = hashtable[hashIndex];
      if(hash_node->id == -1) hash_node->id = dbt->db[i].id;
      else{
         for(curr = hash_node; curr->next != NULL; curr = curr->next);
         next = calloc(1, sizeof(Hash));
	      if(!next) exit(1);
         next->next = NULL;
         next->id = dbt->db[i].id;
         curr->next = next;
      } 
   }
   for(int j = 0; j < SIZE && count != k; j++){
      hash_node = hashtable[j];
      if(hash_node->id == -1) continue;
      for(curr = hash_node; curr != NULL && count != k; curr = curr->next){
         similar_ids[count] = curr->id;
         count++;
      }
   }
   if(count < k) similar_ids = realloc(similar_ids, sizeof(int) * count);
   if(!similar_ids) exit(1);
   for (int p = 0; p < SIZE; p++){
      curr = hashtable[p];
      if(curr){
        while(curr->next != NULL){
           hash_node = curr;
           curr = curr->next;
           free(hash_node);
      }free(curr);
     }
   }
   free(hashtable);
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
double finger_print(char* seq, int prime, int size){
   double sum = 0;
   for(int i = 0; i < size; i++){
      sum += seq[i] * pow(prime, size - i - 1);
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
int find_gene_classic(char* seq, int size, char dnasequence[SIZE]){
	int found = 0;
   for(int i = 0; i < SIZE; i++){
      if(dnasequence[i] == seq[0]){ // parametre olarak girilen gen dizsinin ilk harfi ile kiyaslama yapilir
         found = 1;
         for(int j = 1; j < size; j++){
            if(dnasequence[i+j] != seq[j]){ // eger ilk harfi ayni ise size kadar ilerler ve harf harf karsilastirir.
               found = 0;
               break;
            }
         }
         if(found == 1) break;
      }
   }
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
int find_gene_rabinkarp(char* seq, int size, char dnasequence[SIZE], int prime){
   int found = 0;
   double hashseq = 0.0;
   double hashdna = 0.0;
   int i = 0, j = 0;
   hashseq = finger_print(seq, prime, size);//parametre olarak girilen gen dizisinin hash degeri
   for(i = 0; i < SIZE - size; i++){
     hashdna = finger_print(&dnasequence[i], prime, size);//parametre olarak girilen size'a gore dna seq icinde 
                                                          //olusturulan gen dizilerinin has degeri.
      if(hashseq == hashdna){
         for(j = 0; j < size; j++){
            if(dnasequence[i+j] != seq[j]){//hash degerinin esit olmasi durumunda harf harf karsilastirir.
               break;
            }
         }
       found = 1;
      }
   }
   return found;
}

/*
 * Parametre olarak verilen gen dizisini bir veri tabani
 * icinde arar, diziye sahip bireylerin idsini geri döndürür.
 */
int *find_gene_persons(char* seq, int size, Dtbase dbt){
   int *ids = calloc(dbt.size, sizeof(int));
   int i = 0, say = 0, find = 0, count = 0, j = 0;
   for(i = 0; i < dbt.size; i++){
    find = find_gene_rabinkarp(seq, size, dbt.db[i].sequence, 101);
      if(find == 1){
         say = i;//say degiskenine gen bulunan veriyi atiyoruz
         ids[j]=dbt.db[say].id;//ve ids arrayi icerisine yaziyoruz.
         j++;
         count++;
      }
   }
   printf("\nTOPLAMDA BULUNAN KISI SAYISI: %d\n",count);
   return ids;
}

