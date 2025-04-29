#include "iostream"
using namespace std;

class peripheral{
  protected:
    string nama; // Encapsulation: data is hidden and only accessible via methods
    
  public:
    void setNama(string nm){ // Encapsulation: setter
        nama = nm;
    }

    string getNama(){ return nama; } // Encapsulation: getter

    peripheral(){
        // Default constructor
    }
    
    peripheral(string nm){ // Constructor with parameter
        nama = nm;
    }

    virtual void MerekTerkenal (){ // Polymorphism: virtual method to be overridden
        cout << "";
    }

};

class Keyboard : public peripheral{ // Inheritance: Keyboard inherits from Peripheral
private:
    int jumlah_Key; // Encapsulation
    string suara;   // Encapsulation
public:

    Keyboard(string nm, int jml, string sr) : peripheral(nm){ // Inheritance: constructor of base called
        jumlah_Key = jml;
        suara = sr;
    }
    
    Keyboard() : peripheral(){ // Default constructor calling base class constructor
    }
    
    void jumlahK(int k){ // Encapsulation: setter
        jumlah_Key = k;
    }
    int getJumlahK(){ return jumlah_Key; } // Encapsulation: getter
    
    void setSuara(string sr){ suara = sr; } // Encapsulation: setter
    string getSuara(){ return suara; }      // Encapsulation: getter
    
    void MerekTerkenal(){ // Polymorphism: overriding base class method
        cout << "merek terkenal adalah maxfit /n";
    }
  
};

class mouse : public peripheral{ // Inheritance: mouse inherits from peripheral
private:
    int DPI;           // Encapsulation
    int jmlh_tombol;   // Encapsulation
public:
    mouse(string nm, int dp, int k) : peripheral(nm) // Inheritance: constructor of base called
    {
        DPI = dp;
        jmlh_tombol = k;
    }
    
    mouse() : peripheral(){ }

    void setjumlahK(int k){ // Encapsulation: setter
        jmlh_tombol = k;
    }
    
    int getJumlahK(){ return jmlh_tombol; } // Encapsulation: getter
    
    void setDPI(int b){ DPI = b; }  // Encapsulation: setter
    
    int getDPI(){ return DPI; }     // Encapsulation: getter
    
    void MerekTerkenal(){ // Polymorphism: overriding virtual function
        cout << "merek terkenal adalah razer ";
    }
  
};

int main(){
    
    mouse mouse1;
    mouse1.setNama("se"); // Abstraction: we don't care how it's stored, just how to use it
    mouse1.setjumlahK(2); // Abstraction
    mouse1.setDPI(2000);  // Abstraction
    
    cout << mouse1.getNama() << mouse1.getJumlahK() << mouse1.getDPI() << endl;
    mouse1.MerekTerkenal(); // Polymorphism: dynamic behavior depending on object type
    
    Keyboard kibod("logitek", 56, "kletak");
    cout << kibod.getNama() << kibod.getJumlahK() << kibod.getSuara() << endl;
    kibod.MerekTerkenal(); // Polymorphism: calls Keyboard's override

}
