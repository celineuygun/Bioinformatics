#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
#include "database.h"


int main(int argc, char* argv[]){
  /*if(argc != 2){
    printf("Programi kullanmak icin dosya ismi ile calistirin.\n");
    exit(1);
    }
  while(!strstr(argv[1], ".txt")){
    printf("Dosya ismi .txt uzantili girilmelidir: ");
    exit(1);
    }*/
  argv[1] = "database.txt";
  char dna_seq[SIZE], gen_seq[SIZE];
  int i=0, k=0,respond=0;
  int *ids = calloc(10,sizeof(int)*100);  
  char *data = calloc(10,sizeof(char) * 100); 
  if(!data || !ids) exit(1);

  char fileloc[] = "../data/"; 

  strcpy(data, fileloc);
  strcat(data, argv[1]);
  printf("Okunacak dosyanin adresi: %s\n", data);
  Dtbase *dbt = read_person_file(data);
  printf("\nVeri tabani okundu:\nHatasiz veri sayisi: %d\nHatali veri sayisi: %d\n", dbt->size, dbt->corrupted);
  
  while(1){ 
    printf("\n\nHosgeldiniz. Lutfen yapmak istediginiz islemi secin:\n");
    printf(" 1:  Listeyi bastirmak\n");
    printf(" 2:  DNA benzerligini bulmak\n");
    printf(" 3:  Ayni gene sahip kisileri bulmak\n");
    printf(" 4:  Cikis\n>> ");
    scanf("%d",&respond);
    switch (respond){
      case 1:
      print_database(dbt);
      break;

      case 2:
      printf("DNA benzerligini bulmak icin bir DNA dizisi giriniz.\n>> ");
      scanf("%s", dna_seq);
      printf("En cok benzer kac tane veri istiyorsunuz?\n>> ");
      scanf("%d", &k);
      ids = realloc(ids, sizeof(int) * k);
      ids = find_similar_first(dna_seq, dbt, k);
      printf("Toplamda bulunan benzer birey sayisi: %d\n", k);
      i=0;
      while(i != k){
      find_binary(dbt,0,dbt->size-1,ids[i],dna_seq);
      i++;
      }
      break;

      case 3:
      printf("\n Ayni gene sahip olan insanlari bulmak icin bir gen dizisi giriniz.\n>> ");
      scanf("%s", gen_seq);
      int length=strlen(gen_seq);
      ids = realloc(ids, sizeof(int) * 100);
      ids = find_gene_persons(gen_seq,length , *dbt);
      printf("\nAyni gene sahip insanlarin ID listesini gormek istiyorsaniz 1'e, istemiyorsaniz 0'a basiniz.\n>> ");
      int x=0;
      scanf("%d",&x);
      if(x==1){
        i=0;
        while(1){
          if(ids[i]==ids[i+1]) break;
          printf("ID[%5d  ]: %5d \n",i+1,ids[i]);
          i++;
        }
        while(1){
          int y=0;
          printf("\nAyrintili DNA bilgisini gormek istediginiz kisi varsa lutfen ID listesindeki sira numarasini giriniz. Yoksa 0'a basarak cikis yapabilirsiniz.\n>> ");
          scanf("%d",&y);
          if(y==0) break;
          if(y>i){
          printf("Liste boyutundan daha buyuk sira numarasi girisi saptandi. Menuye geri donuluyor \n");
          break;
          }
          find_binary(dbt, 0, dbt->size - 1, ids[y-1], gen_seq);
        }
      }
      break;

      case 4:
      printf("Gule Gule..\n");
      exit(0);

      default:
      break;
    }
  }

  free(ids);
  free(data);
  return 0;
}
