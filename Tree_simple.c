#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Orang {
    char nama[11];
    int IndexOrtu;
};

bool isValidParent(struct Orang People[], int currentIndex, int parentIndex) {
    while (parentIndex != -1) {
        if (parentIndex == currentIndex) {
            return false;
        }
        parentIndex = People[parentIndex].IndexOrtu;
    }
    return true;
}

int getMaxAvailableGeneration(struct Orang People[], int currentIndex) {
    bool foundNewRoot = false;
    int lastRootIndex = -1;
    int maxAllowedIndex = -1;
    
    // Search backwards to find the most recent root
    for (int i = currentIndex - 1; i >= 0; i--) {
        if (People[i].IndexOrtu == -1) {
            foundNewRoot = true;
            lastRootIndex = i;
            break;
        }
    }
    
    if (foundNewRoot) {
        // Find the highest index that's connected to this root or its children
        for (int i = lastRootIndex + 1; i < currentIndex; i++) {
            if (People[i].IndexOrtu >= -1 && People[i].IndexOrtu <= maxAllowedIndex + 1) {
                maxAllowedIndex = i;
            }
        }
        return maxAllowedIndex + 1;
    }
    
    // If no new root was found, allow connections to any previous index
    return currentIndex - 1;
}

void kasiTab(struct Orang People[], int OrtuIndex) {
    for (int i = 0; i < OrtuIndex; i++) {
        printf("%i. ", i + 1);
        int Tab = 0;
        int IndexSekarang = People[i].IndexOrtu;

        while (IndexSekarang != -1) {
            Tab++;
            IndexSekarang = People[IndexSekarang].IndexOrtu;
        }

        for (int j = 0; j < Tab; j++) {
            printf("\t");
        }

        printf("%s\n", People[i].nama);
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
            int maxGen = getMaxAvailableGeneration(People, i);
            printf("Anak ke berapa? (-1 jika tidak punya): ");
            scanf("%i", &People[i].IndexOrtu);

            if (People[i].IndexOrtu >= -1 && People[i].IndexOrtu <= maxGen) {
                if (isValidParent(People, i, People[i].IndexOrtu)) {
                    break;
                } else {
                    printf("Mohon maaf bosq, Index Ortu tidak boleh membuat siklus di pohon keluarga.\n");
                    printf("Coba lagi.\n");
                }
            } else {
                printf("Mohon maaf bosq, Index Ortu hanya boleh diisi nilai dari -1 sampai %i.\n", maxGen);
                printf("Coba lagi.\n");
            }
        }
        printf("\n");
    }

    printf("Pohon Keluarga: \n");
    kasiTab(People, a);

    free(People);
    return 0;
}
