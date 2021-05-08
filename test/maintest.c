#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "sequence.h"
#include <assert.h>
 
int main(){
    char gen_seq[SIZE/5];
    char* filename="testDb";
    // Dosya okuma ve print fonksiyonlari testi
    Dtbase *dbt= read_person_file(filename);
    printf("Veri tabani okundu, hatali veri sayisi: %d\n",dbt->corrupted);
    print_database(dbt);
    print_double_helix(dbt->db[0]);

    // find_distance icin test durumu:
    assert(find_distance("merhaba","merhaba") == 0);
    assert(find_distance("merhaba","vertaba") == 2);
    assert(find_distance("merhaba","gaba") == 4);
    printf("Uzaklik testlerini gecti\n");
 
    // find_similarity icin test durumu:
    printf("Benzerlik icin verilen dizi ATG\n");
    find_similar_first("ATG",dbt,2);
    int* ids = find_similar_first("ATG",dbt,2);
    assert(ids[0] == 3);
    assert(ids[1] == 6);
    printf("Benzerlik testini gecti\n");

    // Arama testleri
    assert(find_gene_rabinkarp("GGCA",4,"ACGTACCGTGGGCAACGAAT",101)==1);
    assert(find_gene_rabinkarp("GCCA",4,"ACGTACCGTGGGCAACGAAT",101)==0);
    assert(find_gene_classic("GGCA",4,"ACGTACCGTGGGCAACGAAT")==1);
    assert(find_gene_classic("GCCA",4,"ACGTACCGTGGGCAACGAAT")==0);
    printf("Arama testlerini gecti\n");

    ids=find_gene_persons("TTA",3,*dbt);
    assert(ids[0] == 6);
    assert(ids[1] == 7);
    printf("Gen bulma testlerini gecti\n");

    return 0;
}