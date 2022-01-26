#include <iostream>
#include <stdexcept>
using namespace std;

template <typename Tip>
class JednostrukaLista{

        struct Cvor{
        Tip elem;
        Cvor* sljed;
        Cvor (const Tip &element=0, Cvor* sljedeci=0) : elem(element),sljed(sljedeci){}
        };
        Cvor* tekuci;
        Cvor* kr;
        Cvor* poc;
        int brojelem;
    public:
    JednostrukaLista (){
        tekuci=poc=kr=0;
        brojelem=0;
        }
    ~JednostrukaLista(){
            while(poc!=0){
            tekuci=poc;
            poc=poc->sljed;
            delete tekuci;
        }
    }
    JednostrukaLista (const JednostrukaLista<Tip>& jlist){
        Cvor* pomocni(jlist.poc);
        Cvor* pomocni2(0);
        while(pomocni!=nullptr){
            Cvor* pomocni1;
            pomocni1=new Cvor(pomocni->elem,nullptr);
            
            if(pomocni2==0){
                poc=pomocni1;
            }else{
                pomocni2->sljed=pomocni1;    
            }
            pomocni2=pomocni1;
            pomocni=pomocni->sljed;
            
        }
        kr=pomocni2;
        brojelem=jlist.brojElemenata();
        
    }
    JednostrukaLista<Tip>& operator =(JednostrukaLista<Tip> jlist){
           while(poc!=0){
            tekuci=poc;
            poc=poc->sljed;
            delete tekuci;
        }
        Cvor* pomocni(jlist.poc);
        Cvor* pomocni2(0);
        while(pomocni!=nullptr){
            Cvor* pomocni1;
            pomocni1=new Cvor(pomocni->elem,nullptr);
            
            if(pomocni2==0){
                poc=pomocni1;
            }else{
                pomocni2->sljed=pomocni1;    
            }
            pomocni2=pomocni1;
            pomocni=pomocni->sljed;
            
        }
        kr=pomocni2;
        brojelem=jlist.brojElemenata();
       return *this; 
    }
    Tip& trenutni() const {
        //if(poc==0) throw std::range_error("Nema trenutnog\n");
        return tekuci->elem;
    }
    int brojElemenata() const{
        return brojelem;
    }
    bool prethodni(){
        if(tekuci==poc)return false;
        Cvor* pomocni(poc);
        while(pomocni!=tekuci){
             if(pomocni->sljed==tekuci) break;
            pomocni=pomocni->sljed;
        }
        tekuci=pomocni;
        return true;
    }
    bool sljedeci(){
        if(tekuci==kr) return false;
        tekuci=tekuci->sljed;
        return true;
    }
    void pocetak(){
        tekuci=poc;
    }
    void kraj(){
        tekuci=kr;
    }
    void obrisi(){
         Cvor* pomocni(poc);
         brojelem--;
         
         if(tekuci==poc){
             poc=poc->sljed;
             delete tekuci;
             tekuci=poc;
         }else{
        
        while(pomocni->sljed!=tekuci){
             pomocni=pomocni->sljed;
        }
        pomocni->sljed=tekuci->sljed;
        delete tekuci;
        tekuci=pomocni->sljed;
        if(tekuci == 0 ) kr=tekuci=pomocni;
             
         }
        
    }
    void dodajIza(const Tip& el){
        brojelem++;
        Cvor* pomocni;
        pomocni=new Cvor(el,0);
        if(poc==0){
            kr=pomocni;
            tekuci=pomocni;
            poc=pomocni;
            pomocni->sljed=0;
        }else{
            
            pomocni->sljed=tekuci->sljed;
            tekuci->sljed=pomocni;
            if(kr==tekuci) kr=pomocni;
    }}
    Tip& operator [](int i){
            int br(0);
            Cvor* pomocni(poc);
            while(br<i){
                pomocni=pomocni->sljed;
                br++;
            }
            return pomocni->elem;
        }
    void dodajIspred (const Tip& el) {
            Cvor* pomocni;
            brojelem++;
            pomocni= new Cvor(el,0);
            if(poc==0){
                poc=tekuci=kr=pomocni;
                pomocni->sljed=0;
            }else if(tekuci==poc){
                
            pomocni->sljed=poc;
            poc=pomocni;
                }else{
            Cvor* pomocni1(poc);
        while(pomocni1->sljed!=tekuci)
             pomocni1=pomocni1->sljed;
        
        pomocni->sljed=pomocni1->sljed;
        pomocni1->sljed=pomocni;
    }}
    Tip& operator [](int i) const{
            int br(0);
            Cvor* pomocni(poc);
            while(br<i){
                pomocni=pomocni->sljed;
                br++;
            }
            return pomocni->elem;
        }
    void IzbaciSvakiNTi(int n){
        if(n<=0) throw "Halo konju";
        Cvor *prolaz(poc);
        int brojac(brojElemenata());
        if(brojElemenata()==1){
            obrisi();
            return;
        }if(n==1){
            for(int i(1);i<=brojac;i++){
                obrisi();
            }
            return;
        }
        int br(1);
        int obrisano(0);
        for(int i(1);i<=brojac;i++){
            if(br==n-1){
                Cvor* pom(prolaz);
                Cvor* brisem(prolaz->sljed);
                prolaz=prolaz->sljed;
                prolaz=prolaz->sljed;
                if(brisem==tekuci){
                    tekuci=pom;
                }
                delete brisem;
                pom->sljed=prolaz;
                br=1;
                i++;
                obrisano++;
            }else{
                prolaz=prolaz->sljed;
                br++;
                
            }
        }
        brojelem-=obrisano;
    }
};


int main() {
    JednostrukaLista<int> j;
    for(int i(1);i<=12;i++){
        j.dodajIspred(i);
    }
    j.pocetak();
    for(int i(0);i<j.brojElemenata();i++){
        std::cout << j.trenutni() << std::endl;
        j.sljedeci();
    }
    j.IzbaciSvakiNTi(9);
    std::cout << j.brojElemenata() << std::endl;
    j.pocetak();
    for(int i(0);i<j.brojElemenata();i++){
        std::cout << j.trenutni()<<" ";
        j.sljedeci();
    }
    return 0;
}
