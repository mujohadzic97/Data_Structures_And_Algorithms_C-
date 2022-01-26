#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <ctime>

using namespace std;
template <typename Tip1, typename Tip2>
class Mapa{
    
    public:
    Mapa(){}
    virtual ~Mapa(){}
    virtual Tip2 operator [](Tip1 x) const = 0;
    virtual Tip2& operator [](Tip1 x) = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi()= 0;
    virtual void obrisi(const Tip1 &VrKljuca)=0;
};
template <typename Tip1, typename Tip2>
class AVLStabloMapa: public Mapa<Tip1,Tip2>{
    struct Cvor {
        Tip1 klj;
        Tip2 vri;
        int balans;
        Cvor* lije;
        Cvor* des;
        Cvor* rod;
        Cvor(Tip1 kljuc,int bal = 0 ,Cvor* lijevi=0, Cvor* desno=0,Cvor * roditelj = nullptr):klj(kljuc),balans(bal),lije(lijevi),des(desno),rod(roditelj){}
    };
    Cvor* korijen;
    int brElem;
    public : 
    Cvor* Post(Cvor* korij){
        if(korij == nullptr) return korij;
        Cvor* Novi = new Cvor(korij->klj,korij->lije,korij->des,korij->rod);
        if(korij!=nullptr){
             
             Novi -> vri = korij -> vri;
             Novi->lije = Post(korij->lije);
             Novi->des = Post(korij->des);
             
            
            
        }
            return Novi; 
    }   
    
    AVLStabloMapa(const AVLStabloMapa<Tip1,Tip2> &m){
        brElem = m.brElem;

        korijen = Post(m.korijen);
        
    }
    AVLStabloMapa &operator = (AVLStabloMapa<Tip1,Tip2> m){
        if(m.korijen == korijen) return *this;
        obrisi();
        brElem = m.brElem;
        korijen = Post(m.korijen);
        return * this;
    }
    AVLStabloMapa(){
        brElem = 0;
        korijen = nullptr;
        
    }
    ~AVLStabloMapa(){
        obrisi();
    }
    Tip2 operator [](Tip1 x) const {
       Cvor* Pro;
        Pro = korijen;

        while(Pro != nullptr and Pro->klj!=x){
            if(Pro->klj==x) break;
            if(x<Pro->klj){
                
                Pro = Pro->lije;
            }else{
                
                Pro = Pro->des;
            }
        }
        if(Pro!=nullptr) return Pro->vri;
        else
            return Tip2();
        
    }

    void desnaRotacija(Cvor* OkoKojeg){
        Cvor* Prethodni = OkoKojeg->rod;
        OkoKojeg->rod = Prethodni->rod;
        Prethodni->rod = OkoKojeg;
        OkoKojeg->des = Prethodni;
        Prethodni->lije = OkoKojeg->des;
    }
    void lijevaRotacija(Cvor* OkoKojeg){
        Cvor* Prethodni = OkoKojeg->rod;
        OkoKojeg->rod = Prethodni->rod;
        Prethodni->rod = OkoKojeg;
        OkoKojeg->lije = Prethodni;
        Prethodni->des = OkoKojeg->lije;
    }

    void Balans(Cvor* dodani){
        //Cvor* Roditelj = dodani->rod;
        Cvor* prolaz = dodani;
        int skrenuolijevo=0,skrenuodesno=0;
        while(prolaz->balans != -2 || prolaz->balans!=2){
            Cvor* Pom = prolaz->rod;
            if(Pom->lije == prolaz) skrenuolijevo++;
            else skrenuodesno++;
            prolaz = prolaz->rod;
        }
        if(prolaz->balans == 2){
            if(skrenuolijevo==2){
                desnaRotacija(prolaz->lije);
            }
        }else if(prolaz->balans == -2){
            if(skrenuodesno == 2)
                lijevaRotacija(prolaz->des);
        }
        
        
    }
    
    
    void azurirajBalnas(Cvor * tekuci,Cvor* dodani){
        if(tekuci->vri == Tip2()) return;
        if(tekuci->rod == nullptr) return;
        Cvor* Roditelj(tekuci->rod);
        
        if(Roditelj->des == tekuci){
          Roditelj->balans = Roditelj->balans-1;  
        } 
        else{
             Roditelj->balans++;   
        }
        //if(Roditelj->balans>=2 || Roditelj->balans<=-2) Balans(dodani);
        azurirajBalnas(Roditelj,dodani);
    }
    
    
    Tip2& operator [](Tip1 z){
        Cvor* Pro;
        Pro = korijen;
        Cvor* prije;
        while(Pro != nullptr && Pro->klj!=z){
            if(Pro->klj==z) break;
            if(z<Pro->klj){
                prije = Pro;
                Pro = Pro->lije;
            }else{
                prije = Pro;
                Pro = Pro->des;
            }
        }
        
        if(Pro!=nullptr) return Pro->vri;
        
        if(Pro == nullptr && korijen == nullptr){
            brElem++;
            Cvor* Prvi = new Cvor(z);
            korijen = Prvi;
            korijen ->vri = Tip2();
            Prvi->rod = nullptr;
            azurirajBalnas(Prvi,Prvi);
            return korijen->vri;
        }else if(z<prije->klj){
            //Pro skreno lijevo
            
            Cvor* Novi = new Cvor(z);
            Novi->vri = Tip2();
            prije->lije= Novi;
            Novi->rod = prije;
            brElem++;
            azurirajBalnas(Novi,Novi);
            return Novi->vri;
            
            
        }else{
            //Pro skrenuo Desno
            Cvor* Novi = new Cvor(z);
            Novi->rod =prije;
            prije->des = Novi;
            Novi->vri = Tip2();
            brElem++;
            azurirajBalnas(Novi,Novi);
            return Novi->vri;
        }
      
    }
    int brojElemenata() const{return brElem;}
    void Postorder(Cvor* korij){
        if(korij!=nullptr){
             Postorder(korij->des);
             Postorder(korij->lije);
             obrisi(korij->klj);             
        }

    }    
    void obrisi(){
        Postorder(korijen);
        korijen = nullptr;
        brElem = 0;
    }
    void obrisi(const Tip1 &k){
        Cvor* Pro;
        Pro = korijen;
        Cvor* m;
        Cvor* pm;
        Cvor* tmp;
        Cvor* prije = nullptr;
    
        while(Pro != nullptr and Pro->klj!=k){
            prije = Pro;
            if(k<Pro->klj){
                Pro = Pro->lije;
            }else{
                Pro = Pro->des;
            }
        }if(Pro==nullptr) {
            return;
        }
        if(Pro->lije == nullptr){
            m = Pro -> des;
        }else{
            if(Pro->des == nullptr){
                m = Pro->lije;
            }else{
                pm = Pro;
                m = Pro->lije;
                tmp = m->des;
                while (tmp!=nullptr) {
                    pm = m;
                    m = tmp;
                    tmp = m->des;
                }
                if(pm!=Pro){
                    pm->des = m->lije;
                    m->lije = Pro->lije;
                }
                m->des = Pro->des;
            }
        }
        if(prije == nullptr){
            korijen = m;
        }
        else{
            if(Pro == prije->lije){
                prije->lije = m;
            }
            else{
                prije->des = m;
            }
        }
        
        delete Pro;
        brElem--;
    }
     

};


int main() {
    AVLStabloMapa<std::string,std::string> m;
    m["Sarajevo"] = "BiH";
    m["Zagreb"] = "Hrvatska";
    cout << m.brojElemenata() << " " << m["Zagreb"] << " '"; // 2 Hrvatska

    // Test praznih elemenata
    cout << m["Beograd"] <<"' '"; // ''
    cout << m["zagreb"] << "' "; // ''
    m.obrisi("Zagreb");

// Potpuno korektna AVLStabloMapa nece kreirati objekte "Beograd" i "zagreb"
// jer oni nemaju vrijednosti pa ce se ispod ispisati 1
// Ali to zahtijeva implementaciju "Pristupnika" pa cemo priznavati
// rjesenje koje ispise broj 3
cout << m.brojElemenata(); // 3 ili 1

// Test brisanja
cout << " '" << m["Zagreb"] << "' " ; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Sarajevo"] << "' "; // ''
    return 0;
}
