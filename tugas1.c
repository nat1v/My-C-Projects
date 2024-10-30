#include "stdio.h"
#include "math.h"

int main (){
	
	int NilaiTerbesar, IndexNilaiTerbesar = 0;                  //digunakan untuk mengcompare array
	int SkorSiswaTotal, A;										// Total dan Size Array		
	float RataRataSiswa;										// Array	
	
	
	printf(" Mau ukuran Array Berapa? = ");
	scanf("%i", &A);         								//menanyakan user mau array size berapa
	printf("\n");
	
	int SkorSiswa[A];	
	
	for(int i=0; i<A; i++)
	{
		printf(" Silakan Masukan Nilai Aray ke %i = ", i);
		scanf("%i", &SkorSiswa[i]); 					//input data ke array
	}
	
	printf("\n Ini adalah Arraynya:");
	
	for(int i=0; i<A; i++)
	{
		printf(" %i  ", SkorSiswa[i]); 					//read data dari array
	}
	printf("\n");
	
	for(int i=0; i<A; i++)
	{
		SkorSiswaTotal = SkorSiswaTotal + SkorSiswa[i];  //total sum array
	}
	
	RataRataSiswa = (float)SkorSiswaTotal / A;
	
	for(int i=0; i<A; i++)
	{
		if (SkorSiswa[i] >= NilaiTerbesar)
		{
			NilaiTerbesar = SkorSiswa[i]; 				 // compare dengan array
			IndexNilaiTerbesar = i;						// save index terbesar
		}
	}
	

	
	printf("\n Total skor = %i", SkorSiswaTotal);
	printf("\n Rata-Rata = %.2f", RataRataSiswa);
	printf("\n Nilai Terbesar = %i", NilaiTerbesar);
	printf("\n Index ke = %i", IndexNilaiTerbesar);
	
	return 0;
	
	
}