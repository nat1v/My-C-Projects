#include "stdio.h"
#include "stdbool.h"
float pi = 3.1415;

void ShowMenu(){
	printf("pilih bangun.\n\n1.persegi.\n2.persegi panjang.\n3.Jajar Genjang.\n4.Segitiga.\n5.Belah Ketupat.\n6.Layang2.\n7.Trapesium.\n8.Lingkaran.\n\n");
}

int GetChoice() 
{
    int chose;
    ShowMenu();
    while (true) {																	// cara baru mengecek
        printf("pilih : ");
        if (scanf("%i", &chose) == 1 && chose >= 1 && chose <= 8) {	
            break; // input yang valid
        } else {
            printf("Input salah. Silakan coba lagi.\n");
            while (getchar() != '\n'); // clear invalid input
        }
    }
    return chose;
}

void GetOperand(int* op1, int* op2){
	printf("\ninput nomor yang pertama?\n");
	scanf("%i", op1);
	printf("\ninput nomor yang kedua ?\n");
	scanf("%i", op2);
}
void GetOperandTrapesium(float* op1, float* op2, float* op3){
	printf("\ninput nomor yang pertama ?\n");
	scanf("%f", op1);
	printf("\ninput nomor yang kedua ?\n");
	scanf("%f", op2);
	printf("\ninput nomor yang ketiga  ?\n");
	scanf("%f", op3);
}
void GetOperandPersegi(int* op1){
	printf("\ninput panjang sisi ?\n");
	scanf("%i", op1);
}

void GetOperandLingkaran(float* op1){
	printf("\ninput nomor jari jari  ?\n");
	scanf("%f", op1);
}

void GetOperandKoma(float* op1, float* op2){
	printf("\ninput nomor yang pertama ?\n");
	scanf("%f", op1);
	printf("\ninput nomor yang kedua ?\n");
	scanf("%f", op2);
}

void DoCalculation(int TipeBangun){
	
	int a, b, c;
	float d, e, f;
	
//	if (TipeBangun < 1 || TipeBangun > 8){					// cara lama mengecek
//		printf("salah\n");
//		return;	
//	}
	if (TipeBangun == 1){										// persegi
		GetOperandPersegi(&a);
		printf("%i\n", a*a);
	}
	if (TipeBangun == 2){										//persegi panjang
	   	GetOperand(&a, &b);
	   	printf("%i x %i = %i\n", a, b, a*b);            
	}
	if (TipeBangun == 3){											//jajar genjang
		GetOperandKoma(&d, &e);
		printf("%.2f x %.2f = %.2f\n", d, e, d*e);
	}
	if (TipeBangun == 4){											// segitiga
		GetOperandKoma(&d, &e);
		printf("1/2 x %.1f x %.1f = %.2f\n",d, e, 0.5 * d * e);
	}
	if (TipeBangun == 5){											// belah ketupat
		GetOperandKoma(&d, &e);
		printf("1/2 x %.1f x %.1f = %.2f\n",d, e, 0.5 * d * e);
	}
	if (TipeBangun == 6){											//layang layang
		GetOperandKoma(&d, &e);
		printf("1/2 x %.1f x %.1f = %.2f\n",d, e, 0.5 * d * e);
	}
	if (TipeBangun == 7){											// trapesium
		GetOperandTrapesium(&d, &e, &f);
		printf("(%f + %f)/2 x %f = %f\n",d ,e, f, 0.5 * (d+e) * f);
	}
	if (TipeBangun == 8){											// lingkaran
		GetOperandLingkaran(&d);
		printf("%.4f x %.1f x %.1f = %.3f\n",pi ,d, d, pi * d * d);
	
	}
}

bool Continue(){
	char ch;
		printf("continue? (y/n)\n");
		scanf(" %c", &ch);
	if (ch == 'y')
		return true;
	else
		return false;
}

int main(){
	
	do{
	DoCalculation(GetChoice());
		}while (Continue());
		
			return 0;
}

