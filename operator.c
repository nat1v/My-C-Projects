#include "stdio.h"
#include "stdbool.h"


void ShowMenu() 
{
	printf("choose operator:\n1.Addition.\n2.Subtraction.\n3.Multiplication\n4.Division.\n");
}

void Operand(int* Number1, int* Number2){
	printf("\ninput nomor yang pertama?\n");
	scanf("%i", Number1);
	printf("\ninput nomor yang kedua ?\n");
	scanf("%i", Number2);
}

int GetChoice(){
	 int chose;
    ShowMenu();
    while (true) {																	// cara baru mengecek
        printf("\npilih : ");
        if (scanf("%i", &chose) == 1 && chose >= 1 && chose <= 4) {	
            break; // input yang valid
        } else {
            printf("Input salah. Silakan coba lagi.\n");
            while (getchar() != '\n'); // clear invalid input
        }
}
}

void DoCalculation (int TypeOp){
	
	int a,b;
	
	if (TypeOp == 1){
		Operand(&a, &b);
		printf("%i + %i = %i\n", a, b, a+b);
	}
	if (TypeOp == 2){
		Operand(&a, &b);
		printf("%i - %i = %i\n",a, b, a - b);
	}
	if (TypeOp == 3){
		Operand(&a, &b);
		printf("%i x %i= %i\n",a ,b ,a*b);
	}
	if (TypeOp == 4){
		Operand(&a, &b);
		printf("%i / %i = %i remainders = %i\n",a ,b, a/b, a%b);
	}
	
}

bool Continue(){
	char ch;
	printf("lanjut?(y): ");
	scanf(" %c", &ch);
	if (ch == 'y' || ch == 'Y')
		return true;
	else
		return false;
}

int main(){
	do
	{
	DoCalculation(GetChoice());
	} while (Continue());
	
	return 0;
	
}