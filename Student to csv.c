#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LENGTH 40

FILE *fileOutput;

struct Student 
{
  char nim[10];
  int tahun_masuk;
  char prodi[MAX_LENGTH];
  char nama[MAX_LENGTH];
  float ipk;
};

//Dibuat oleh mang adi, proudly on nvim
/*buat sebuah program yang menerima input data dari user, 
 * pakai dynamic array. data termasuk nama, NIM, etc necessary 
 * (mungkin bisa kayak prodi atau tahun masuk dh). data yang diinput harus di-display ulang setelah selesai input. 
 * data yang dibuat harus bisa menggunakan fitur "search" or "find" data dari sebuah NIM. 
 * buat sebuah program untuk menghitung: 
 * mean, 
 * highest value, 
 * varians, dan 
 * standar deviasi dari beberapa data GPA student*/

// HitungStat mengambil parameter yaitu array of struct student, contohnya disini Mahasiswa, 
// integer contohnya disini adalah ada "n Mahasiswa"
// dan 3 pointer to float ini, sudah ada namanya
void HitungStat(struct Student Mahasiswa[], int n, float* mean, float* varians, float* sd){
      
  float TotalNilai = 0.0;
  float jumlah_kuadrat_selisih = 0.0;

  //mencari total nilai
  for (int i = 0; i < n; i++)
  {
    TotalNilai += Mahasiswa[i].ipk;
  }
  // menghitung mean;
  *mean = TotalNilai / n;

  //mencari nilai sum squared >>> (xi - x(mean))^2
  for (int i = 0; i < n; i++)
  {
    jumlah_kuadrat_selisih += pow(Mahasiswa[i].ipk - *mean, 2);
  }

  //varians = sum_squared / jumlah data
  *varians = jumlah_kuadrat_selisih / n;
  //standar_deviasi
  *sd = sqrt(*varians);
}


int main()
{ 
  int jumlahSiswa;
  char garbage[1];
  //init
  printf("Halo! selamat datang di database siswa!\n silahkan masukkan jumlah siswa yang mau diinput:  ");
  scanf("%i", &jumlahSiswa);
  struct Student Mahasiswa[jumlahSiswa];
  gets(garbage);
  //input data siswa
  for(int i = 0; i < jumlahSiswa; i=i+1)
  {

    printf("\nData Mahasiswa ke: %i\n\n", i+1);
    printf("Nama: ");
    gets(Mahasiswa[i].nama);
    //gets(garbage);

    printf("\nMasukkan NIM: ");;
    gets(Mahasiswa[i].nim);
    //gets(garbage);

    printf("\nMasukkan Prodi: ");
    gets(Mahasiswa[i].prodi);
    //gets(garbage);

    printf("\nMasukkan Tahun Masuk: ");
    scanf("%i", &Mahasiswa[i].tahun_masuk);
    //gets(garbage);

    printf("\nMasukkan IPK: ");
    scanf("%f", &Mahasiswa[i].ipk);
    gets(garbage);
    //garbage adalah garbage collector, untuk buffer agar clear;
  }

  //mengeprint di terminal
  for(int i = 0; i < jumlahSiswa; i=i+1)
  {
    printf("\nMahasiswa ke: %i\n", i+1);
    printf("Nama:           %s\n", Mahasiswa[i].nama);
    printf("NIM:            %s\n", Mahasiswa[i].nim);
    printf("Prodi:          %s\n", Mahasiswa[i].prodi);
    printf("Tahun Masuk:    %i\n", Mahasiswa[i].tahun_masuk);
    printf("IPK:            %.2f\n", Mahasiswa[i].ipk);
  }
  
//Perhitungannn
  float mean, varians, standar_deviasi;
  float IPK_terkecil = Mahasiswa[0].ipk;
  float IPK_terbesar = Mahasiswa[0].ipk;

  for (int i = 0; i<jumlahSiswa; i++)
  {
    if (Mahasiswa[i].ipk < IPK_terkecil)
    {
      IPK_terkecil = Mahasiswa[i].ipk;
    } 
    
    if (Mahasiswa[i].ipk > IPK_terbesar)
    {
      IPK_terbesar = Mahasiswa[i].ipk;
    }
  }

  //hitung stat (struct, int, float*, float* float*)
  HitungStat(Mahasiswa, jumlahSiswa, &mean, &varians, &standar_deviasi);
  
  printf("\nvarians:        %f\n", varians);
  printf("nilai terkecil:   %f\n", IPK_terkecil);
  printf("nilai terbesar:   %f\n", IPK_terbesar);
  printf("mean:             %f\n", mean);
  printf("standar deviasi:  %.2f\n", standar_deviasi);
  

  //pencarian siswa
  char nama_dicari[MAX_LENGTH];
  char ch;
  int ketemu;
  //ask user untuk mau cari lagi?
  printf("\nmau cari siswa?(y/n): ");
  scanf("%c", &ch);

  //main loop untuk mencari siswa
  while (ch == 'y' || ch == 'Y'){
    gets(garbage);
    printf("\nmasukkan nama: ");
    gets(nama_dicari);

    //jika user mengulang, dibawah akan mengeset ketemu menjadi 0 agar bisa.
    ketemu = 0;
    //looping semua siswa; dan compare dengan strcmp
    for(int i = 0; i<jumlahSiswa; i++){
      if (strcmp(Mahasiswa[i].nama, nama_dicari) == 0){
          printf("ketemu! \n");
          printf("Nama:         %s\n", Mahasiswa[i].nama);
          printf("Nim:          %s\n", Mahasiswa[i].nim);
          printf("Prodi:        %s\n", Mahasiswa[i].prodi);
          printf("Tahun Masuk:  %i\n", Mahasiswa[i].tahun_masuk);
          printf("IPK:          %.2f\n", Mahasiswa[i].ipk);
          ketemu = 1; //siswa ditemukan
          break; //keluar dari loop
    } 
  }
  if (!ketemu)
  {
  printf("ga ketemu icibos, gaada orang namanya \"%s\"", nama_dicari);
  } //prompt untuk mengulang
  
  printf("\nmau cari lagi?(y/n): ");
  scanf(" %c", &ch);
  //gets(garbage);
}

  
    // ngambil path document
  char* AlamatDocument = getenv("USERPROFILE");  // mengambil nama user
    
    if (AlamatDocument != NULL) {
        // mengappend
      char filePath[1024];
      snprintf(filePath, sizeof(filePath), "%s\\Documents\\Data Siswa.csv", AlamatDocument);
      
        // buka file, kalo gaada buat auto
      fileOutput = fopen(filePath, "w");
  }  
  
  //meng outputkan text ke file tujuan yaini csv
  fprintf(fileOutput, "No.;Nama Mahasiswa;NIM;Prodi;Tahun Masuk;IPK\n");
  
  for (int i = 0; i<jumlahSiswa; i++)
  { //file print ke file tujuan, dan mengeprint nama,nim dsb.
    fprintf(fileOutput, "%i;", i + 1);
    fprintf(fileOutput, "%s;", Mahasiswa[i].nama);
    fprintf(fileOutput, "%s;", Mahasiswa[i].nim);
    fprintf(fileOutput, "%s;", Mahasiswa[i].prodi);
    fprintf(fileOutput, "%i;", Mahasiswa[i].tahun_masuk);
    fprintf(fileOutput, "%.2f\n", Mahasiswa[i].ipk);

  }
    //mengoutputkan hasil fungsi HitungStat ke file tujuan
  fprintf(fileOutput, "\nvarians:       %.2f\n", varians);
  fprintf(fileOutput, "nilai terkecil:  %.2f\n", IPK_terkecil);
  fprintf(fileOutput, "nilai terbesar:  %.2f\n", IPK_terbesar);
  fprintf(fileOutput, "mean:            %.2f\n", mean);
  fprintf(fileOutput, "standar deviasi: %.2f\n", standar_deviasi);


  printf("\nFile siswa berada di folder Document anda!\nDocuments\\Data Siswa.csv");
  //close file, agar tidak terbentur dengan process lain
  fclose(fileOutput);

  return 0;

}

