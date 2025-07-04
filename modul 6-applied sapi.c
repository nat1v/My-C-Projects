#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COWS 100
#define MAX_ID_LEN 20
#define MAX_STATUS_LEN 50

typedef struct {
    char id[MAX_ID_LEN];
    char jenis_kelamin; // 'J' atau 'B'
    int tahun_lahir;
    float berat_badan;
    char status[MAX_STATUS_LEN];
} Sapi;

Sapi sapi_list[MAX_COWS];
int count = 0;

// Deklarasi fungsi
void add_cow();
void see_all();
void seek_by_id();
void update_cow();
void seek_by_gender();
void count_gender();
void seek_by_weight();
void menyusui_cows();
void heaviest_cow();
void save_to_csv();
void load_from_csv();
void delete_cow();
void sort_cows();
void cows_by_birth_year();
float average_weight();

// Fungsi bantu untuk sorting
int compare_berat(const void *a, const void *b) {
    Sapi *sa = (Sapi*)a;
    Sapi *sb = (Sapi*)b;
    if (sa->berat_badan < sb->berat_badan) return 1;
    if (sa->berat_badan > sb->berat_badan) return -1;
    return 0;
}

int compare_tahun(const void *a, const void *b) {
    Sapi *sa = (Sapi*)a;
    Sapi *sb = (Sapi*)b;
    return sa->tahun_lahir - sb->tahun_lahir;
}

// Fungsi utama
int main() {
    load_from_csv();
    int choice;
    
    do {
        printf("\n=== Sistem Manajemen Data Sapi ===\n");
        printf("1. Tambah Data Sapi\n");
        printf("2. Lihat Semua Data\n");
        printf("3. Cari Sapi Berdasarkan ID\n");
        printf("4. Update Data Sapi\n");
        printf("5. Lihat Sapi Berdasarkan Jenis Kelamin\n");
        printf("6. Hitung Jumlah Sapi Jantan/Betina\n");
        printf("7. Cari Sapi dengan Berat Tertentu\n");
        printf("8. Tampilkan Sapi Menyusui\n");
        printf("9. Cari Sapi Terberat\n");
        printf("10. Simpan/Load Data CSV\n");
        printf("11. Hitung Rata-rata Berat\n");
        printf("12. Hapus Data Sapi (Group A)\n");
        printf("13. Urutkan Data Sapi (Group A)\n");
        printf("14. Tabel Sapi Berdasarkan Tahun Lahir (Group A)\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Bersihkan buffer input

        switch(choice) {
            case 1: add_cow(); break;
            case 2: see_all(); break;
            case 3: seek_by_id(); break;
            case 4: update_cow(); break;
            case 5: seek_by_gender(); break;
            case 6: count_gender(); break;
            case 7: seek_by_weight(); break;
            case 8: menyusui_cows(); break;
            case 9: heaviest_cow(); break;
            case 10: 
                printf("1. Simpan ke CSV\n2. Muat dari CSV\n");
                int sub;
                scanf("%d", &sub);
                if(sub == 1) save_to_csv();
                else if(sub == 2) load_from_csv();
                break;
            case 11: 
                printf("Rata-rata berat: %.2f kg\n", average_weight());
                break;
            case 12: delete_cow(); break;
            case 13: sort_cows(); break;
            case 14: cows_by_birth_year(); break;
            case 0: printf("Keluar dari program...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while(choice != 0);
    
    return 0;
}

// Implementasi fungsi tambah data sapi
void add_cow() {
    if(count >= MAX_COWS) {
        printf("Kapasitas penuh! Tidak bisa menambah data baru.\n");
        return;
    }
    
    Sapi *cow = &sapi_list[count];
    char input[256];
    
    printf("Masukkan ID: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%s", cow->id);
    
    // Validasi ID duplikat
    for(int i = 0; i < count; i++) {
        if(strcmp(sapi_list[i].id, cow->id) == 0) {
            printf("ID sudah terdaftar!\n");
            return;
        }
    }
    
    // Jenis kelamin
    do {
        printf("Jenis Kelamin (J/B): ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%c", &cow->jenis_kelamin);
    } while(cow->jenis_kelamin != 'J' && cow->jenis_kelamin != 'B');
    
    // Tahun lahir
    do {
        printf("Tahun Lahir (1900-2023): ");
        fgets(input, sizeof(input), stdin);
    } while(sscanf(input, "%d", &cow->tahun_lahir) != 1 || 
             cow->tahun_lahir < 1900 || cow->tahun_lahir > 2023);
    
    // Berat badan
    do {
        printf("Berat Badan (kg): ");
        fgets(input, sizeof(input), stdin);
    } while(sscanf(input, "%f", &cow->berat_badan) != 1 || cow->berat_badan <= 0);
    
    // Status
    printf("Status: ");
    fgets(cow->status, MAX_STATUS_LEN, stdin);
    cow->status[strcspn(cow->status, "\n")] = 0;
    
    count++;
    printf("Data berhasil ditambahkan!\n");
}

// Implementasi fungsi lihat semua data
void see_all() {
    if(count == 0) {
        printf("Belum ada data sapi.\n");
        return;
    }
    
    printf("+------------------+----+------------+-----------+---------------------+\n");
    printf("| ID               | JK | Tahun Lahir| Berat(kg) | Status              |\n");
    printf("+------------------+----+------------+-----------+---------------------+\n");
    
    for(int i = 0; i < count; i++) {
        Sapi *cow = &sapi_list[i];
        printf("| %-16s | %c  | %10d | %9.2f | %-19s |\n", 
               cow->id, cow->jenis_kelamin, cow->tahun_lahir, cow->berat_badan, cow->status);
    }
    
    printf("+------------------+----+------------+-----------+---------------------+\n");
}

// Implementasi fungsi cari berdasarkan ID
void seek_by_id() {
    char id[MAX_ID_LEN];
    printf("Masukkan ID yang dicari: ");
    scanf("%s", id);
    
    for(int i = 0; i < count; i++) {
        if(strcmp(sapi_list[i].id, id) == 0) {
            Sapi *cow = &sapi_list[i];
            printf("Data ditemukan:\n");
            printf("ID: %s\n", cow->id);
            printf("Jenis Kelamin: %c\n", cow->jenis_kelamin);
            printf("Tahun Lahir: %d\n", cow->tahun_lahir);
            printf("Berat Badan: %.2f kg\n", cow->berat_badan);
            printf("Status: %s\n", cow->status);
            return;
        }
    }
    printf("Data tidak ditemukan!\n");
}

// Implementasi fungsi update data
void update_cow() {
    char id[MAX_ID_LEN];
    printf("Masukkan ID yang ingin diupdate: ");
    scanf("%s", id);
    
    for(int i = 0; i < count; i++) {
        if(strcmp(sapi_list[i].id, id) == 0) {
            Sapi *cow = &sapi_list[i];
            int choice;
            
            printf("Pilih field yang ingin diupdate:\n");
            printf("1. Jenis Kelamin\n2. Tahun Lahir\n3. Berat Badan\n4. Status\n");
            scanf("%d", &choice);
            
            switch(choice) {
                case 1:
                    printf("Jenis Kelamin baru (J/B): ");
                    scanf(" %c", &cow->jenis_kelamin);
                    break;
                case 2:
                    printf("Tahun Lahir baru: ");
                    scanf("%d", &cow->tahun_lahir);
                    break;
                case 3:
                    printf("Berat Badan baru: ");
                    scanf("%f", &cow->berat_badan);
                    break;
                case 4:
                    printf("Status baru: ");
                    while(getchar() != '\n');
                    fgets(cow->status, MAX_STATUS_LEN, stdin);
                    cow->status[strcspn(cow->status, "\n")] = 0;
                    break;
                default:
                    printf("Pilihan tidak valid!\n");
            }
            printf("Data berhasil diupdate!\n");
            return;
        }
    }
    printf("ID tidak ditemukan!\n");
}

// Implementasi fungsi cari berdasarkan jenis kelamin
void seek_by_gender() {
    char gender;
    printf("Masukkan jenis kelamin (J/B): ");
    scanf(" %c", &gender);
    
    if(gender != 'J' && gender != 'B') {
        printf("Jenis kelamin harus J atau B!\n");
        return;
    }
    
    int total = 0;
    printf("+------------------+------------+-----------+---------------------+\n");
    printf("| ID               | Tahun Lahir| Berat(kg) | Status              |\n");
    printf("+------------------+------------+-----------+---------------------+\n");
    
    for(int i = 0; i < count; i++) {
        if(sapi_list[i].jenis_kelamin == gender) {
            Sapi *cow = &sapi_list[i];
            printf("| %-16s | %10d | %9.2f | %-19s |\n", 
                   cow->id, cow->tahun_lahir, cow->berat_badan, cow->status);
            total++;
        }
    }
    
    printf("+------------------+------------+-----------+---------------------+\n");
    printf("Total: %d ekor\n", total);
}

// Implementasi fungsi hitung jumlah jantan/betina
void count_gender() {
    int jantan = 0, betina = 0;
    
    for(int i = 0; i < count; i++) {
        if(sapi_list[i].jenis_kelamin == 'J') jantan++;
        else betina++;
    }
    
    printf("Jumlah sapi jantan: %d\n", jantan);
    printf("Jumlah sapi betina: %d\n", betina);
}

// Implementasi fungsi cari berdasarkan berat
void seek_by_weight() {
    float berat;
    printf("Masukkan batas berat (kg): ");
    scanf("%f", &berat);
    
    int total = 0;
    printf("+------------------+----+------------+-----------+---------------------+\n");
    printf("| ID               | JK | Tahun Lahir| Berat(kg) | Status              |\n");
    printf("+------------------+----+------------+-----------+---------------------+\n");
    
    for(int i = 0; i < count; i++) {
        if(sapi_list[i].berat_badan > berat) {
            Sapi *cow = &sapi_list[i];
            printf("| %-16s | %c  | %10d | %9.2f | %-19s |\n", 
                   cow->id, cow->jenis_kelamin, cow->tahun_lahir, cow->berat_badan, cow->status);
            total++;
        }
    }
    
    printf("+------------------+----+------------+-----------+---------------------+\n");
    if(total > 0) printf("Total sapi di atas %.2f kg: %d\n", berat, total);
    else printf("Tidak ada sapi di atas %.2f kg\n", berat);
}

// Implementasi fungsi tampilkan sapi menyusui
void menyusui_cows() {
    int total = 0;
    printf("+------------------+----+------------+-----------+\n");
    printf("| ID               | JK | Tahun Lahir| Berat(kg) |\n");
    printf("+------------------+----+------------+-----------+\n");
    
    for(int i = 0; i < count; i++) {
        if(strcmp(sapi_list[i].status, "menyusui") == 0) {
            Sapi *cow = &sapi_list[i];
            printf("| %-16s | %c  | %10d | %9.2f |\n", 
                   cow->id, cow->jenis_kelamin, cow->tahun_lahir, cow->berat_badan);
            total++;
        }
    }
    
    printf("+------------------+----+------------+-----------+\n");
    if(total > 0) printf("Total sapi menyusui: %d\n", total);
    else printf("Tidak ada sapi menyusui\n");
}

// Implementasi fungsi cari sapi terberat
void heaviest_cow() {
    if(count == 0) {
        printf("Belum ada data sapi.\n");
        return;
    }
    
    int max = 0;
    for(int i = 1; i < count; i++) {
        if(sapi_list[i].berat_badan > sapi_list[max].berat_badan)
            max = i;
    }
    
    Sapi *cow = &sapi_list[max];
    printf("Sapi terberat:\n");
    printf("ID: %s\n", cow->id);
    printf("Berat: %.2f kg\n", cow->berat_badan);
    printf("Status: %s\n", cow->status);
}

// Implementasi penyimpanan ke CSV
void save_to_csv() {
    FILE *fp = fopen("data_sapi.csv", "w");
    if(!fp) {
        printf("Gagal membuka file!\n");
        return;
    }
    
    fprintf(fp, "ID,Jenis Kelamin,Tahun Lahir,Berat Badan,Status\n");
    for(int i = 0; i < count; i++) {
        Sapi *cow = &sapi_list[i];
        fprintf(fp, "%s,%c,%d,%.2f,%s\n", cow->id, cow->jenis_kelamin, 
                cow->tahun_lahir, cow->berat_badan, cow->status);
    }
    
    fclose(fp);
    printf("Data berhasil disimpan ke file CSV!\n");
}

// Implementasi pembacaan dari CSV
void load_from_csv() {
    FILE *fp = fopen("data_sapi.csv", "r");
    if(!fp) {
        printf("File tidak ditemukan!\n");
        return;
    }
    
    char line[512];
    // Lewati header
    if(fgets(line, sizeof(line), fp)) {
        count = 0;
        
        while(fgets(line, sizeof(line), fp) && count < MAX_COWS) {
            Sapi *cow = &sapi_list[count];
            sscanf(line, "%[^,],%c,%d,%f,%[^\n]", cow->id, &cow->jenis_kelamin,
                   &cow->tahun_lahir, &cow->berat_badan, cow->status);
            count++;
        }
        
        printf("Data berhasil dimuat dari file CSV!\n");
    }
    
    fclose(fp);
}

// Implementasi hapus data
void delete_cow() {
    char id[MAX_ID_LEN];
    printf("Masukkan ID yang ingin dihapus: ");
    scanf("%s", id);
    
    for(int i = 0; i < count; i++) {
        if(strcmp(sapi_list[i].id, id) == 0) {
            // Geser data
            for(int j = i; j < count - 1; j++) {
                sapi_list[j] = sapi_list[j+1];
            }
            count--;
            printf("Data berhasil dihapus!\n");
            return;
        }
    }
    printf("ID tidak ditemukan!\n");
}

// Implementasi urutkan data
void sort_cows() {
    if(count == 0) {
        printf("Belum ada data untuk diurutkan.\n");
        return;
    }
    
    int choice;
    printf("Pilih kriteria pengurutan:\n");
    printf("1. Berat Badan (Descending)\n");
    printf("2. Tahun Lahir (Ascending)\n");
    scanf("%d", &choice);
    
    // Buat salinan untuk sorting
    Sapi temp_list[MAX_COWS];
    memcpy(temp_list, sapi_list, count * sizeof(Sapi));
    
    if(choice == 1) {
        qsort(temp_list, count, sizeof(Sapi), compare_berat);
        printf("Data diurutkan berdasarkan berat badan:\n");
    } else if(choice == 2) {
        qsort(temp_list, count, sizeof(Sapi), compare_tahun);
        printf("Data diurutkan berdasarkan tahun lahir:\n");
    } else {
        printf("Pilihan tidak valid!\n");
        return;
    }
    
    printf("+------------------+------------+-----------+\n");
    printf("| ID               | Tahun Lahir| Berat(kg) |\n");
    printf("+------------------+------------+-----------+\n");
    
    for(int i = 0; i < count; i++) {
        printf("| %-16s | %10d | %9.2f |\n", 
               temp_list[i].id, temp_list[i].tahun_lahir, temp_list[i].berat_badan);
    }
    
    printf("+------------------+------------+-----------+\n");
}

// Implementasi tabel tahun lahir
void cows_by_birth_year() {
    int year;
    printf("Masukkan tahun lahir: ");
    scanf("%d", &year);
    
    int total = 0;
    for(int i = 0; i < count; i++) {
        if(sapi_list[i].tahun_lahir == year) total++;
    }
    
    if(total == 0) {
        printf("Tidak ada sapi yang lahir di tahun %d\n", year);
        return;
    }
    
    printf("+------------------+----+-----------+\n");
    printf("| ID               | Jenis| Berat(kg)|\n");
    printf("+------------------+----+-----------+\n");
    
    for(int i = 0; i < count; i++) {
        if(sapi_list[i].tahun_lahir == year) {
            Sapi *cow = &sapi_list[i];
            printf("| %-16s | %c    | %9.2f |\n", cow->id, cow->jenis_kelamin, cow->berat_badan);
        }
    }
    
    printf("+------------------+----+-----------+\n");
    printf("Total sapi lahir tahun %d: %d\n", year, total);
}

// Implementasi rata-rata berat
float average_weight() {
    if(count == 0) return 0;
    
    float total = 0;
    for(int i = 0; i < count; i++) {
        total += sapi_list[i].berat_badan;
    }
    return total / count;
}
