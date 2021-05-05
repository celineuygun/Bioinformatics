// #include<stdio.h>
// #include"sequence.h"
// #include"database.h"

// int main(int argc,char* argv[]){
//      char* filename;    
    
//      char dna_seq[SIZE],gen_seq[SIZE/5];
//      int k;
//      int* ids ;  
//     //TODO: Komut satirindan verilecek dosya adini aliniz ve 
//     // filename değişkeninde saklayiniz.
 
//     // printf("Okunacak Dosya: %s\n",filename);
//     //TODO: Dosyayi acin ve bir Dtbase degiskeninde saklayin.
//     // Dtbase *dbt = read_person_file(filename);
//     // printf("Veri tabani okundu, hatali veri sayisi: %d\n",dbt->corrupted);
    
//     //TODO: Kullanici dan bir DNA dizisi ve k sayisi isteyin.
//     // bu diziye benzer k tane birey idsini arayip, geri dondurun.
//     // print("DNA benzerligini bulmak icin bir DNA dizisi giriniz\n");
//     // scanf("%s",dna_seq);
//     // printf("En cok benzer kac tane veri istiyorsunuz?\n");
//     // scanf("%d",k);
//     // ids = malloc(sizeof(int)*k);
//     // ids = find_similar_first(dna_seq,&dbt,k);
//     // printf("Toplamda bulunan benzer birey sayisi: %d",k);
	
//     // TODO: Kullanicidan bir gen dizisi isteyin.
//     // print("Geni bulmak icin bir gen dizisini giriniz\n");
//     // scanf("%s",gen_seq);
//     // bu gen dizisine sahip bireyleri arayip, idlerini geri dondurun.
//     // ids = find_gene_persons(gen_seq,dbt->size,&dbt);
//     // printf("Bulunan birey sayisi %d\n",sizeof(ids)); 
// 	return 0;
// }
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"database.h"
#include"sequence.h"
#include<assert.h>

int main(){
   char* filename="testDb";
   //TODO: Dosya okuma fonksiyonunu cagirip
   // Dogru sayida eleman okuyup okumadigini test ediniz.
   // ekrana basarak kontrol yapiniz.
   Dtbase *dbt = read_person_file(filename);
   print_database(dbt);
   print_double_helix(dbt->db[0]);


   // TODO: assertion kullanarak yazdiginiz fonksiyonlari
   // test ediniz.
   assert(find_distance("merhaba","merhaba") == 0);
   assert(find_distance("merhaba","vertaba") == 2);
   assert(find_distance("merhaba","gaba") == 4);
   printf("Uzaklik testlerini gecti\n");

   // TODO: find_similarity icin test durumu:
   printf("Benzerlik icin verilen dizi ATG\n");
   find_similar_first("ATG",dbt,2);
   int* ids = find_similar_first("ATG",dbt,2);
   assert(ids[0] == 3);
   assert(ids[1] == 6);
   printf("Benzerlik testini gecti\n");
   // TODO: Arama testleri
   assert(find_gene_rabinkarp("GGCA",4,"ACGTACCGTGGGCAACGAAT",101)==1);
   assert(find_gene_rabinkarp("GCCA",4,"ACGTACCGTGGGCAACGAAT",101)==0);
   assert(find_gene_classic("GGCA",4,"ACGTACCGTGGGCAACGAAT")==1);
   assert(find_gene_classic("GCCA",4,"ACGTACCGTGGGCAACGAAT")==0);
   printf("Arama testlerini gecti\n");
   return 0;
}
