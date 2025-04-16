#include "stdio.h"
#include "stdlib.h"

//#define DEBUG

int merge_sort(int a[], int size){
  
  int p, q, r;
  int i, j, k;

  for (int i = 0; i<size; i++){
      printf(" %i", a[i]);
  }
  
  


  return 0;
}





int main(){

  int a;
  printf("masukkan size array");
  scanf("%i", &a);
    
  int* a_Processed = malloc(sizeof(int) * a);
  for (int i = 0; i < a; i++){
      scanf("%i", &a_Processed[i]);
  }
  
  merge_sort(a_Processed, a);
  
  int midpoint = a/2;
  int p, q, r, i, j, k;
  for (int i = 0; i<a; i++){
      if(p/2 != 0){
        
      }
  }


  #ifdef DEBUG
  
  for (int i = 0; i < a; i++){
      printf(" %i", a_Processed[i]);
  }

  #endif /* ifdef DEBUG */
 

  return 0;
}
