#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
#include "database.h"
#include <time.h>

int main(int argc, char* argv[]){
  if(argc != 2){ // komut satirindan eksik veya yanlis girilme durumunda program sonlanir
    printf("Programi kullanmak icin dosya ismi ile calistirin.\n");
    exit(1);
  }
  while(!strstr(argv[1], ".txt")){
    printf("Dosya ismi .txt uzantili girilmelidir.\n");
    exit(1);
  }
  char dna_seq[SIZE], gen_seq[SIZE];
  int i = 0, k = 0, response = 0, *ids; 
  char fileloc[] = "../data/";

  char *data = calloc(strlen(fileloc) + strlen(argv[1]) + 1, sizeof(char));
  if(!data) exit(1);

  Dtbasecor *corr = calloc(1, sizeof(Dtbasecor));
  if(!corr) exit(1);
  corr->db = calloc(DBSIZE, sizeof(cPerson));
  if(!corr->db) exit(1);
  corr->size = 0;
  // arguman olarak verilen dosya ismi datalarin bulundugu lokasyon ile birlestirilir
  strcpy(data, fileloc); // data = "../data/"
  strcat(data, argv[1]); // data = "../data/argv[1]"
  Dtbase *dbt = read_person_file(data, corr); // dosyadaki veriler uygun struct'lara yerlestirilir

  printf("\n========= PROJE BILGILERI\n");
  printf("Konu: Bioinformatics\n");
  printf("Hazirlayanlar:\n");
  printf("Dilara Elif Narin\n");
  printf("Zeynep Selin Uygun\n");
  printf("Ece Yucer");
  
  while(1){ // switch case ile menu olusturduk.
    printf("\n\nYapmak istediginiz islemi seciniz.\n");
    printf(" 1:  Dosya bilgilerini gormek\n");
    printf(" 2:  Hatasiz verileri bastirmak\n");
    printf(" 3:  Hatali verileri bastirmak\n");
    printf(" 4:  DNA benzerligini bulmak\n");
    printf(" 5:  Ayni gene sahip kisileri bulmak\n");
    printf(" 0:  Cikis\n>> ");
    scanf("%d", &response);
    switch(response){
      case 1:
        printf("\n========= DOSYA BILGILERI\n");
        printf("Dosyanin adresi     : %s\n", data);
        printf("Toplam veri sayisi  : %d\nHatasiz veri sayisi : %d\nHatali veri sayisi  : %d\n", dbt->size + corr->size, dbt->size, dbt->corrupted);
        break;

      case 2:
        print_database(dbt);
        break;

      case 3:
        printf("\n========== HATALI VERILER\n");
        for(int i = 0; i < corr->size; ++i) printf("%3d) ID: %-5d ISIM: %s\n", i+1, corr->db[i].id, corr->db[i].name);
        printf("\nAyrintili DNA bilgisini gormek istediginiz kisinin sira numarasini giriniz.\n>> ");
        scanf("%d", &i);
        while(i < 1 || i > corr->size){ // sira numarasindan kucuk veye buyuk deger girme durumunda hata verir.
          printf("Lutfen gecerli bir secim yapiniz.\n>> ");
          scanf("%d", &i);
        }
        print_double_helix_corr(corr->db[i-1]);
        break;

      case 4:
        printf("\nDNA benzerligini bulmak icin bir DNA dizisi giriniz.\n>> ");
        scanf("%s", dna_seq);
        printf("\nEn cok benzer kac tane veri istiyorsunuz?\n>> ");
        scanf("%d", &k);
        ids = find_similar_first(dna_seq, dbt, k);
        for(int i = 0; i != k; ++i) find_binary(dbt, 0, dbt->size - 1, ids[i], dna_seq, 1); // parametre olarak verilen id'lere sahip
                                                                                            // girilen sayi kadar benzer kisi bilgisi
                                                                                            // ve DNA sarmalini bastirir
        free(ids);
        break;

      case 5:
        printf("\nAyni gene sahip olan insanlari bulmak icin bir gen dizisi giriniz.\n>> ");
        scanf("%s", gen_seq);
        int length = strlen(gen_seq);
        ids = find_gene_persons(gen_seq, length, *dbt);
        printf("\nAyni gene sahip insanlarin ID listesini gormek istiyorsaniz 1'e, istemiyorsaniz 0'a basiniz.\n>> ");
        int x = 0;
        scanf("%d", &x);
        if(x == 1){
          printf("\n");
          for(i = 0; ids[i] != ids[i+1]; ++i) printf("ID[%5d  ]: %5d \n", i+1, ids[i]); // idse atanan tum IDleri bastirmak icin for dongusu
          while(1){
            int y = 0;
            printf("\nAyrintili DNA bilgisini gormek istediginiz kisi varsa lutfen ID listesindeki sira numarasini giriniz. Yoksa 0'a basarak cikis yapabilirsiniz.\n>> ");
            scanf("%d", &y);
            if(y == 0) break;
            if(y > i){
              printf("\nListe boyutundan daha buyuk sira numarasi girisi saptandi. Menuye geri donuluyor\n");
              break;
            }
            find_binary(dbt, 0, dbt->size - 1, ids[y-1], gen_seq, 0); 
            // parametre olarak verilen id'lere sahip ayrintili kisi bilgisi ve DNA sarmalini bastirir.
          }
        }free(ids);
        break;

      case 0:
        printf("\nGule Gule..\n");
        exit(0);

      default:
        break;
    }
  }
  free(corr->db);
  free(corr);
  free(dbt);
  free(data);
  return 0;
}
