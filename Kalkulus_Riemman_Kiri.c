#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int pangkat;
int *tanda; //tanda minus atau plus
double *koefisien;

double integrate(double x_input){
  
  double hasil_fungsi = 0;
  
  for (int i = 0; i<=pangkat; i++){

    hasil_fungsi += tanda[i] * koefisien[i] * pow(x_input, i);

  }

  return hasil_fungsi;
}

double riemann_kiri(double a, double b, int n, double (*sebuah_fungsi)(double)){
  
  double delta_x = (b-a)/n;
  double sum = 0.0;
  double x_i = a;
  
  for (int i = 0; i<n; i++){

    sum += integrate(x_i);
    x_i += delta_x;

  }

  return sum * delta_x;
}



int main(){
  
  int poinInterval;
  double batas_bawah, batas_atas;
  char pilihan_Tanda;



  if (scanf("%lf", &batas_atas) != 1){
      printf("invalid input untuk batas atas.");
  }
  if (scanf("%lf", &batas_bawah) != 1){
      printf("invalid input untuk batas bawah");
  }
  if (scanf("%d", &poinInterval) != 1 || poinInterval <= 0){
      printf("imvalid, harus positif (x > 0)");
  }


  printf("derajat polinomial: ");
    scanf("%d", &pangkat);
    
    
    koefisien = (double*)malloc((pangkat + 1) * sizeof(double));
    tanda = (int*)malloc((pangkat + 1) * sizeof(int));
    
    if (koefisien == NULL || tanda == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    
    printf("Masukkan koefisien dan tanda dari derajat tertinggi ke terendah:\n");
    for (int i = pangkat; i >= 0; i--) {
        if (i == pangkat) {
            printf("koefisien dari x^%d: ", i);
            scanf("%lf", &koefisien[i]);
            
            
            if (pangkat > 0) {
                printf("tanda untuk berikutnya (+ or -): ");
                scanf(" %c", &pilihan_Tanda);
                tanda[i] = 1; 
            } else {
                tanda[i] = 1;
            }
        } else {
           
            tanda[i] = (pilihan_Tanda == '+') ? 1 : -1;
            
            printf("Coefficient of x^%d: ", i);
            scanf("%lf", &koefisien[i]);
            
         
            if (i > 0) {
                printf("Sign for next term (+ or -): ");
                scanf(" %c", &pilihan_Tanda);
            }
        }
    }

double result;
  result = riemann_kiri(batas_bawah, batas_atas, poinInterval, integrate);
  printf("are rieman kiri = %lf", result);

  return 0;
}
