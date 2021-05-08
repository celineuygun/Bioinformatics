#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
#include "database.h"

int main(int argc,char* argv[]){
    char *data = malloc(sizeof(char) * 100);
    char *filename = malloc(sizeof(char) * 50);  
    if(!data || !filename) exit(1);
    char fileloc[] = "../data/"; 
    printf("Okunacak dosya ismini uzantisiz girin: ");
    scanf(" %[^\n]%*c", filename);
    while(strstr(filename, ".")){
        printf("Dosya ismi uzantisiz girilmelidir: ");
        scanf(" %[^\n]%*c", filename);
    }
    strcpy(data, fileloc);
    strcat(data, filename);
    strcat(data, ".txt");
 
    printf("Okunacak dosyanin adresi: %s\n", data);
    Dtbase *dbt = read_person_file(data);
    printf("Veri tabani okundu, hatali veri sayisi: %d\n",dbt->corrupted);
    
    char dna_seq[SIZE], gen_seq[SIZE/5];
    int k; 
    printf("DNA benzerligini bulmak icin bir DNA dizisi giriniz\n");
    scanf("%s", dna_seq);
    printf("En cok benzer kac tane veri istiyorsunuz?\n");
    scanf("%d", &k);
    int *ids = malloc(sizeof(int) * k);  
    ids = find_similar_first(dna_seq, dbt, k);
    printf("Toplamda bulunan benzer birey sayisi: %d\n", k);
    for(int i = 0, j; i < k; ++i){
        find_binary(dbt, 0, dbt->size - 1, ids[i], dna_seq);
    }
	
    // TODO: Kullanicidan bir gen dizisi isteyin.
    // printf("Geni bulmak icin bir gen dizisini giriniz: ");
    // scanf("%s", gen_seq);
    // // bu gen dizisine sahip bireyleri arayip, idlerini geri dondurun.
    // ids = realloc(ids, sizeof(int) * 100);
    // ids = find_gene_persons(gen_seq, dbt->size, *dbt);
    // printf("Bulunan birey sayisi %lu\n", sizeof(ids)); 
	return 0;
}