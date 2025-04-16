#include <iostream>
#include <string>
using namespace std;

// Kelas abstrak induk
class Hewan {
protected:
    string nama;
    int umur;
    double berat;

public:
    // Konstruktor kosong
    Hewan() {
    }

    // Konstruktor berisi
    Hewan(string nm, int umr, double brt) {
        nama = nm;
        umur = umr;
        berat = brt;
    }

    // Getter
    string getNama() {
        return nama;
    }

    int getUmur() {
        return umur;
    }

    double getBerat() {
        return berat;
    }

    // Setter
    void setNama(string nm) {
        nama = nm;
    }

    void setUmur(int umr) {
        umur = umr;
    }

    void setBerat(double brt) {
        berat = brt;
    }

    // Metode abstrak - harus diimplementasikan oleh kelas turunan
    virtual void bersuara() = 0;
    
};

// Kelas turunan pertama
class Anjing : public Hewan {
private:
    string ras;

public:
    // Konstruktor kosong
    Anjing() : Hewan(){
    }

    // Konstruktor berisi
    Anjing(string nm, int umr, double brt, string r) : Hewan(nm, umr, brt) {
        ras = r;
    }

    // Getter dan setter untuk atribut spesifik kelas
    string getRas() {
        return ras;
    }

    void setRas(string r) {
        ras = r;
    }

    // Implementasi metode abstrak
    void bersuara(){
        cout << "ANJAYYYYY" << endl;
    }
/*
    void tampilkanInfo() override {
        cout << "Informasi Anjing:" << endl;
        cout << "Nama: " << nama << endl;
        cout << "Umur: " << umur << " tahun" << endl;
        cout << "Berat: " << berat << " kg" << endl;
        cout << "Ras: " << ras << endl;
    }*/
};

// Kelas turunan kedua
class Burung : public Hewan {
private:
    bool bisaTerbang;
    string spesies;

public:
    // Konstruktor kosong
    Burung() : Hewan() {
        bisaTerbang = false;
        spesies = "";
    }

    // Konstruktor berisi
    Burung(string nm, int umr, double brt, bool bt, string s) : Hewan(nm, umr, brt) {
        bisaTerbang = bt;
        spesies = s;
    }

    // Getter dan setter untuk atribut spesifik kelas
    bool getBisaTerbang() {
        return bisaTerbang;
    }

    string getSpesies() {
        return spesies;
    }

    void setBisaTerbang(bool bt) {
        bisaTerbang = bt;
    }

    void setSpesies(string s) {
        spesies = s;
    }

    // Implementasi metode abstrak
    void bersuara() {
        cout << "ANJIRRRR" << endl;
    }

};

int main() {

    // Menggunakan konstruktor berisi
    Anjing anjing1("Jio", 3, 15.5, "Golden Retriever");
    Burung burung1("Tweety", 2, 0.3, true, "Kenari");
    
    cout << "Informasi anjing:" <<endl;
    cout << "Nama: " << anjing1.getNama() << endl;
    cout << "Umur: " << anjing1.getUmur() << " tahun" << endl;
    cout << "Berat: " << anjing1.getBerat() << " kg" << endl;
    cout << "Ras: " << anjing1.getRas() << endl << "Bersuara: ";
    anjing1.bersuara();
 
    cout << "Informasi burung:" <<endl;
    cout << "Nama: " << burung1.getNama() << endl;
    cout << "Umur: " << burung1.getUmur() << " tahun" << endl;
    cout << "Berat: " << burung1.getBerat() << " kg" << endl;
    cout << "Bisa Terbang?" << (burung1.getBisaTerbang() ? "ya" : "sg bro") << endl;
    cout << "Spesies: " << burung1.getSpesies() << endl << "Bersuara: ";
    burung1.bersuara();
 

    
    // Menggunakan konstruktor kosong
    Anjing anjing2;
    Burung burung2;
    
    
    // Menggunakan setter
    anjing2.setNama("fookymay");
    anjing2.setUmur(5);
    anjing2.setBerat(10.6);
    anjing2.setRas("Bali");
    
    burung2.setNama("Coco");
    burung2.setUmur(3);
    burung2.setBerat(0.2);
    burung2.setBisaTerbang(true);
    burung2.setSpesies("Kakatua");
    
    // Menggunakan getter
    cout << "\n\nInformasi Anjing (Setter edition): " << endl;
    cout << "Nama: " << anjing2.getNama() << endl;
    cout << "Umur: " << anjing2.getUmur() << " tahun" << endl;
    cout << "Berat: " << anjing2.getBerat() << " kg" << endl;
    cout << "Ras: " << anjing2.getRas() << "\nBersuara seperti: ";
    anjing2.bersuara();
    cout << endl;
    
    cout << "Informasi Burung (menggunakan getter):" << endl;
    cout << "Nama: " << burung2.getNama() << endl;
    cout << "Umur: " << burung2.getUmur() << " tahun" << endl;
    cout << "Berat: " << burung2.getBerat() << " kg" << endl;
    cout << "Spesies: " << burung2.getSpesies() << endl;
    cout << "Bisa terbang: " << (burung2.getBisaTerbang() ? "Ya" : "Tidak") << "\nbersuara kayak: ";
    burung2.bersuara();
    
    return 0;
}
