#include <stdio.h>


struct Orang{
    char nama[11];
    int IndexOrtu;
  };

void kasiTab(struct Orang People[], int OrtuIndex)
{
    for (int i = 0; i < OrtuIndex; i++)
    {
        printf("%i. ", i+1);
        int Tab = 0; 
        int IndexSekarang = People[i].IndexOrtu;

        while (IndexSekarang != -1)
        {
            Tab++;
            IndexSekarang = People[IndexSekarang].IndexOrtu;
        } 
          
        
    for (int i = 0; i<Tab; i++)
    {
        printf("\t");
    }

        printf("%s\n", People[i].nama);
    } 
}

int main(){
  
  int a;
  printf("mau berapa people?: ");
  scanf("%i", &a);

  struct Orang *People;
  People = (struct Orang*) malloc(a * sizeof(struct Orang));

  int lastGeneration = -1;

  char garbage[1];

  for (int i = 0; i<a; i++)
  {
        gets(garbage);
        printf("index array ke: %i \n", i+1);
        printf("Nama: ");

        gets(People[i].nama);
    
        while (1) {
            printf("Anak ke berapa? (-1 jika tidak punya): ");
            scanf("%i", &People[i].IndexOrtu);

            if (People[i].IndexOrtu >= -1 && People[i].IndexOrtu < i) {
                break; // masih di dalam range input
            } else {
                printf("Mohon maaf bosq, Index Ortu hanya boleh diisi nilai dari -1 sampai %i (yang sudah dimasukkan sebelumnya).\n", i - 1);
                printf("Coba lagi.\n");
            }
        }
        printf("\n");
  }
  
  
  printf("Pohon Keluarga: \n");
  kasiTab(People, a);

  return 0;
}
