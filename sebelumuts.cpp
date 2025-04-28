#include "iostream"
using namespace std;

class peripheral{
  protected:
    string nama;
    
  public:
    void setNama(string nm){
        nama = nm;
    }

    string getNama(){ return nama; }

    peripheral(){
        
    }
    
    peripheral(string nm){
        nama = nm;
    }

    virtual void MerekTerkenal (){
        cout << "";
    }

};

class Keyboard : public peripheral{
private:
    int jumlah_Key;
    string suara;
public:

    Keyboard(string nm, int jml, string sr) : peripheral(nm){
    jumlah_Key = jml;
    suara = sr;
    }
    
    Keyboard() : peripheral(){

    }
    
    void jumlahK(int k){
        jumlah_Key = k;
    }
    int getJumlahK(){ return jumlah_Key; }
    
    void setSuara(string sr){
        suara = sr;
    }
    string getSuara(){
        return suara;
    }
    
    void MerekTerkenal(){
        cout << "merek terkenal adalah maxfit /n";
    }
  
};

class mouse : public peripheral{
private:
    int DPI;
    int jmlh_tombol;
public:
    mouse(string nm, int dp, int k) : peripheral(nm)
    {
    DPI = dp;
    jmlh_tombol = k;
    }
    
    mouse() : peripheral(){
    }

    void setjumlahK(int k){
        jmlh_tombol = k;
    }
    
    int getJumlahK(){ return jmlh_tombol; }
    
    void setDPI(int b){
        DPI = b;
    }
    
    int getDPI(){ return DPI; }
    
    
    void MerekTerkenal(){
        cout << "merek terkenal adalah razer ";
    }
  
};

int main(){
    
    mouse mouse1;
    mouse1.setNama("se");
    mouse1.setjumlahK(2);
    mouse1.setDPI(2000);
    
    cout << mouse1.getNama() << mouse1.getJumlahK() << mouse1.getDPI() << endl;
    mouse1.MerekTerkenal();
    
    Keyboard kibod("logitek", 56, "kletak");
    cout << kibod.getNama() << kibod.getJumlahK() << kibod.getSuara() << endl;
    kibod.MerekTerkenal();

}
