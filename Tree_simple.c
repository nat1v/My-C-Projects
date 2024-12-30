#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Orang {
    char nama[11];
    int IndexOrtu;
};

bool isValidParent(struct Orang People[], int currentIndex, int parentIndex) {
    if (parentIndex == -1) {
        return true;
    }
    if (parentIndex == currentIndex) {
        return false;
    }
    return isValidParent(People, currentIndex, People[parentIndex].IndexOrtu);
}

void printFamilyTreeRecursive(struct Orang People[], int total, int currentIndex, int depth) {
    
    for (int i = 0; i < depth; i++) {
        
        printf("\t");
    }
    printf("%s\n", People[currentIndex].nama);

    for (int i = 0; i < total; i++) {
        if (People[i].IndexOrtu == currentIndex) {

            printFamilyTreeRecursive(People, total, i, depth + 1);
        }
    }
}

int main() {
    int a;
    printf("Mau berapa people?: ");
    scanf("%i", &a);
    
    struct Orang *People = (struct Orang *)malloc(a * sizeof(struct Orang));
    char garbage[1];

    for (int i = 0; i < a; i++) {
        gets(garbage);
        printf("Index array ke: %i \n", i + 1);
        printf("Nama: ");
        gets(People[i].nama);

        while (1) {
            printf("Anak ke berapa? (-1 jika tidak punya): ");
            scanf("%i", &People[i].IndexOrtu);

            if (People[i].IndexOrtu >= -1 && People[i].IndexOrtu < i) {
                if (isValidParent(People, i, People[i].IndexOrtu)) {
                    break;
                } else {
                    printf("Mohon maaf bosq, Index Ortu tidak boleh membuat siklus di pohon keluarga.\n");
                    printf("Coba lagi.\n");
                }
            } else {
                printf("Mohon maaf bosq, Index Ortu hanya boleh diisi nilai dari -1 sampai %i.\n", i - 1);
                printf("Coba lagi.\n");
            }
        }

        printf("\n");
    }

    printf("Pohon Keluarga: \n");
    for (int i = 0; i < a; i++) {
        
        if (People[i].IndexOrtu == -1) {
            
            printFamilyTreeRecursive(People, a, i, 0);
        }
     
    }

    free(People);
    return 0;
}
