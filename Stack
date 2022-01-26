#include <iostream>
#include <stdexcept>
#include <vector>
//#include <algorithm>
using namespace std;
template <typename Tip>
    class Stek{
        struct Cvor{
            Tip elem;
            Cvor* sljed;
            Cvor (const Tip &element=0, Cvor* sljedeci=0) : elem(element),sljed(sljedeci){}
        };
        int brojelem;
        Cvor* Vrh;
        Cvor* Pocetak;
    
        public: 
        
        Stek(){
            Vrh=0;brojelem=0;Pocetak=0;
        }
        ~Stek(){
            Cvor* Pomocni(Vrh);
            while(Vrh!=0){
                Pomocni=Vrh->sljed;
                delete Vrh;
                Vrh=Pomocni;
            }
            delete Vrh;
            
        }
        Stek(const Stek<Tip> &S){
            Cvor* pomocni(S.Vrh);
            Cvor* pomocni2(0);
            brojelem=0;
            while(pomocni!=0){
                Cvor* Novi(new Cvor(pomocni->elem,pomocni->sljed));
                if(brojelem==0){
                    Vrh=Novi;
                    pomocni2=Vrh;
                }else{
                pomocni2->sljed=Novi;
                pomocni2=Novi;
                }
                brojelem++;
                pomocni=pomocni->sljed;
            }
            
    }
        Stek<Tip> &operator =(Stek<Tip> S){
        if(Vrh==S.Vrh) return *this;
          Cvor* Pomocni(Vrh);
            while(Vrh!=0){
                Pomocni=Vrh->sljed;
                delete Vrh;
                Vrh=Pomocni;
            }
            delete Vrh;
             Cvor* pomocni(S.Vrh);
            Cvor* pomocni2(0);
            brojelem=0;
            while(pomocni!=0){
                Cvor* Novi(new Cvor(pomocni->elem,pomocni->sljed));
                if(brojelem==0){
                    Vrh=Novi;
                    pomocni2=Vrh;
                }else{
                pomocni2->sljed=Novi;
                pomocni2=Novi;
                }
                brojelem++;
                pomocni=pomocni->sljed;
            }
        return *this;
    }
        void brisi(){
        Cvor* Pomocni(Vrh);
            while(Vrh!=0){
                Pomocni=Vrh->sljed;
                delete Vrh;
                Vrh=Pomocni;
            }
            delete Vrh;
            Pocetak=0;
            Vrh=0;
            brojelem=0;
    }
        void stavi(const Tip& el){
        brojelem++;
        Cvor* Pomocni(new Cvor(el,Vrh));
        if(Pocetak==0){
            Pocetak=Pomocni;
            Vrh=Pomocni;
            Pocetak->sljed=0;
        }else{
            Vrh=Pomocni;
    }}
        Tip skini(){
        if(brojelem==0) throw std::range_error("Prazan");
        Tip zad(Vrh->elem);
        brojelem--;
        Cvor* Pomocni(Vrh);
        Vrh=Vrh->sljed;
        delete Pomocni;
        return zad;
    }
        Tip& vrh(){
        if(brojelem==0) throw std::range_error("Prazan");
        return Vrh->elem;
    }
        int brojElemenata()const{
         return brojelem;
     }
    };
    

void pretraga(Stek<vector<int>> &s,int trazeni){
    if(s.brojElemenata() == 0){
        cout<<"Nema elementa";
        return;
    }
    auto trenvect(s.vrh());
    int poc(0),kr(trenvect.size());
    if(trenvect.size()==0){}else{
    if(trenvect[0] == trazeni){
            cout<< "0" <<" "<< s.brojElemenata() -1;
            return;
        }
    while(poc<kr){
        int sred((poc+kr)/2);
        
        if(sred<0 || sred>trenvect.size()) break;
        
        if(trenvect[sred] == trazeni){
            cout<< sred <<" "<< s.brojElemenata() -1;
            return;
        }else if(trenvect[sred] < trazeni) poc = sred+1;
        else kr=sred-1;
    }}
    auto a(s.skini());
    pretraga(s,trazeni);
    s.stavi(a);
    
    
}

void PrvojeraPoc(){
    Stek<vector<int>> s;
    vector<int> a;
    vector<int> b;
    a.push_back(1);
    a.push_back(2);
    b.push_back(3);
    s.stavi(a);
    s.stavi(b);
    pretraga(s,3);
    cout<<endl;
}
void ProvjeraNaKraju(){
    Stek<vector<int>> s;
    vector<int> a;
    vector<int> b;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    b.push_back(4);
    s.stavi(a);
    s.stavi(b);
    pretraga(s,3);
    cout<<endl;
}
void ProvjeraStekaBezElem(){
    Stek<vector<int>> s;
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    vector<int> f;
    pretraga(s,2);
    cout<<endl;
}
int main(){
    PrvojeraPoc();
    ProvjeraNaKraju();
     ProvjeraStekaBezElem();

    return 0;
}
