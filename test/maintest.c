#include"database.h"
#include"sequence.h"

#include<assert.h>
int main(){
   char* filename="testDb";
   //TODO: Dosya okuma fonksiyonunu cagirip
   // Dogru sayida eleman okuyup okumadigini test ediniz.
   // ekrana basarak kontrol yapiniz.
   // Dtbase *dbt = read_person_file(filename);
   // printf("Veri tabani: \n");
   // print_database(dbt);


   // TODO: assertion kullanarak yazdiginiz fonksiyonlari
   // test ediniz.
   // assert(find_distance("merhaba","merhaba") == 0);
   // assert(find_distance("merhaba","vertaba") == 2);
   // assert(find_distance("merhaba","gaba") == 4);
   // printf("Uzaklik testlerini gecti\n");

   // TODO: find_similarity icin test durumu:
   // printf("Benzerlik icin verilen dizi ATG\n");
   // int* ids = find_similar_first("ATG",dbt,2);
   // assert(ids[0] == 3);
   // assert(ids[1] == 6);
   // printf("Benzerlik testini gecti\n");

   // TODO: Arama testleri
   // assert(find_gene_rabinkarp("GGCA",4,"ACGTACCGTGGGCAACGAAT",101)==1);
   // assert(find_gene_rabinkarp("GCCA",4,"ACGTACCGTGGGCAACGAAT",101)==0);
   // assert(find_gene_classic("GGCA",4,"ACGTACCGTGGGCAACGAAT")==1);
   // assert(find_gene_classic("GCCA",4,"ACGTACCGTGGGCAACGAAT")==0);
   // printf("Arama testlerini gecti\n");
   return 0;
}
