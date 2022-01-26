#include <iostream>
#include <stdexcept>
using namespace std;

template <typename Tip>
    class Iterator;



template <typename Tip>
class Lista{
private:

void operator = (Lista &);
Lista (const Lista&);
public:
Lista(){}
virtual ~Lista(){}
virtual int brojElemenata() const = 0;
virtual Tip& trenutni() const = 0;
virtual bool prethodni() = 0;
virtual bool sljedeci() = 0;
virtual void pocetak() = 0;
virtual void kraj() = 0;
virtual void obrisi() = 0;
virtual void dodajIspred (const Tip& el) = 0;
virtual void dodajIza (const Tip& el) = 0;
virtual Tip& operator [](int i) = 0;
friend class Iterator<Tip>;
};
template <typename Tip>
class DvostrukaLista : public Lista<Tip>{
        template<class DvostrukaLista> friend class Iterator;
        struct Cvor{
            Tip elem;
            Cvor* sljed;
            Cvor* pr;
            Cvor (const Tip &element=0, Cvor* sljedeci=0,Cvor* prije=0) : elem(element),sljed(sljedeci),pr(prije){}
        };
        Cvor* tekuci;
        Cvor* kr;
        Cvor* poc;
        int brojelem;
    public:
    DvostrukaLista (){
        tekuci=poc=kr=0;
        brojelem=0;
        }
    ~DvostrukaLista(){
            while(poc!=0){
                Cvor* Pom(poc);
                poc=poc->sljed;
                delete Pom;
            }

    }
    DvostrukaLista (const DvostrukaLista<Tip>& dlist){
        Cvor* pom(dlist.poc);
        brojelem=dlist.brojElemenata();
        if(brojelem==0){
            poc=kr=tekuci=0;
        }else if(brojelem==1){
            Cvor* Novi(new Cvor(pom->elem));
            poc=kr=tekuci=Novi;
        }else{
            Cvor* NoviPrvi(new Cvor(pom->elem));
            poc=NoviPrvi;
            kr=NoviPrvi;
            pom=pom->sljed;
            while(pom!=0){
                Cvor* Novi(new Cvor(pom->elem));
                Cvor* Pom(kr);
                kr=Novi;
                Pom->sljed=kr;
                kr->pr=Pom;
                pom=pom->sljed;
            }
        }
        tekuci=poc;
    }
    DvostrukaLista<Tip>& operator =(DvostrukaLista<Tip> dlist){
            if(dlist.poc==poc) return *this;
            while(poc!=0){
            tekuci=poc;
            poc=poc->sljed;
            delete tekuci;
            }
          Cvor* pom(dlist.poc);
        brojelem=dlist.brojElemenata();
        if(brojelem==0){
            poc=kr=tekuci=0;
        }else if(brojelem==1){
            Cvor* Novi(new Cvor(pom->elem));
            poc=kr=tekuci=Novi;
        }else{
            Cvor* NoviPrvi(new Cvor(pom->elem));
            poc=NoviPrvi;
            kr=NoviPrvi;
            pom=pom->sljed;
            while(pom!=0){
                Cvor* Novi(new Cvor(pom->elem));
                Cvor* Pom(kr);
                kr=Novi;
                Pom->sljed=kr;
                kr->pr=Pom;
                pom=pom->sljed;
            }
        }
        tekuci=poc;
       return *this; 
    }
    
   
    Tip& trenutni() const {
        return tekuci->elem;
    }
    int brojElemenata() const{
        return brojelem;
    }
    bool prethodni(){
        if(tekuci==poc)return false;
        tekuci=tekuci->pr;
        return true;
    }
    bool sljedeci(){
        if(tekuci->sljed==0)return false;
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
        
          brojelem--;
          if(tekuci==poc){tekuci=tekuci->sljed;delete poc;poc=tekuci;}
          else if(tekuci==kr){
              tekuci=tekuci->pr;
              delete kr;
              kr=tekuci;
          }else{
              Cvor* Pom1(tekuci->sljed);
              Cvor* Pom2(tekuci->pr);
              Pom1->pr=Pom2;
              Pom2->sljed=Pom1;
              delete tekuci;
              tekuci=Pom1;
          }
          if(brojelem==0){poc=0;tekuci=0;kr=0;}
    }
    void dodajIza(const Tip& el){
        
        Cvor* pomocni;
        pomocni=new Cvor(el,0,0);
        if(brojelem==0){
            kr=pomocni;
            tekuci=pomocni;
            poc=pomocni;
        }else if(brojelem==1){
            kr=pomocni;
            poc->sljed=kr;
            pomocni->pr=poc;
            tekuci=poc;
        }else{
            Cvor* pom(tekuci->sljed);
            pomocni->sljed=tekuci->sljed;
            tekuci->sljed=pomocni;
            pomocni->pr=tekuci;
            if(tekuci==kr) kr=pomocni;
            else
            pom->pr=pomocni;
            
            
        }
        brojelem++;
    }
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
        Cvor* Novi(new Cvor(el));
        if(brojelem==0){
            poc=Novi;
            kr=Novi;
            tekuci=Novi;
        }else if(tekuci==poc){
            poc=Novi;
            poc->sljed=tekuci;
            tekuci->pr=poc;
            if(tekuci->sljed==0) kr=tekuci;
        }else{
            Cvor* Pom(tekuci->pr);
            tekuci->pr=Novi;
            Novi->sljed=tekuci;
            Pom->sljed=Novi;
            Novi->pr=Pom;
            if(tekuci->sljed==0) kr=tekuci;
        }
        brojelem++;    
    }
    const Tip& operator [](int i) const{
            int br(0);
            Cvor* pomocni(poc);
            while(br<i){
                pomocni=pomocni->sljed;
                br++;
            }
            return pomocni->elem;
        }
    
};

template <typename Tip>
    class Iterator{
        const DvostrukaLista<Tip>* li;
        typename DvostrukaLista<Tip>::Cvor* trenutniLista;
    public:
        Iterator(const DvostrukaLista<Tip> &dvlist):trenutniLista(dvlist.tekuci){}
        Iterator(const Lista<Tip> &lis):li((DvostrukaLista<Tip>*)&lis),trenutniLista(li->tekuci){}
        void Poc(){
            trenutniLista=li->poc;
        }
        bool Sljed(){
            if(trenutniLista->sljed==0)return false;
            trenutniLista=trenutniLista->sljed;
            return true;
        }
        Tip Tekuci(){
            return trenutniLista->elem;
        }
    };

template<typename Tip>
    Tip dajMaksimum(const Lista<Tip>& n){
        Iterator<Tip> i(n);
        i.Poc();
        Tip max(i.Tekuci());
      
        i.Sljed();
        while(i.Sljed()){
            if(i.Tekuci()>max) max=i.Tekuci();
    
        }
        
        return max;
    }


template <typename Tip>
    void TestnaFDodajIza(DvostrukaLista<Tip> &s, Tip el){
        s.dodajIza(el);
        std::cout << "U Dvostruku Listu je stavljen element: "<< el <<" iza tekuceg elementa."<< std::endl;
    }
template <typename Tip>
    void TestnaFDodajIspred(DvostrukaLista<Tip> &s, Tip el){
        s.dodajIspred(el);
        std::cout << "U Dvostruku Listu je stavljen element: "<< el <<" ispred tekuceg elementa."<< std::endl;
    }

template <typename Tip>
    void TestnaFObrisi(DvostrukaLista<Tip> &s){
        s.obrisi();
        std::cout << "U Dvostrukoj Listi je obrisan tekuci element!"<<  std::endl;
    }
template <typename Tip>
    void TestnaFTekuci(DvostrukaLista<Tip> &s){
        std::cout << "Tekuci element Dvostruke Liste je: "<< s.trenutni() << std::endl;
    }

template <typename Tip>
    void TestnaFSkini(DvostrukaLista<Tip> &s){
        std::cout << "Sa vrha DvostrukaListaa je uklonjen element: "<< s.skini() << std::endl;
    }

template <typename Tip>
    void TestnaFBrojElem(DvostrukaLista<Tip> &s){
        std::cout << "Dvostruka Lista ima "<< s.brojElemenata() <<" elemenata."<< std::endl;
    }
template <typename Tip>
    void TestnaFPred(DvostrukaLista<Tip> &s){
        if(s.prethodni())
        std::cout << "Postavili smo tekuci element na prethodni element Dvostruke Liste."<< std::endl;
        else std::cout << "Nema prethodnog elementa jer se nalazimo na pocetku Dvostruke Liste." << std::endl;
    }

template <typename Tip>
    void TestnaFSljed(DvostrukaLista<Tip> &s){
        if(s.sljedeci())
        std::cout << "Postavili smo tekuci element na sljedeci element Dvostruke Liste."<< std::endl;
        else std::cout << "Nema sljedeceg elementa jer se nalazimo na kraju Dvostruke Liste." << std::endl;
    }
template <typename Tip>
    void TestnaFPoc(DvostrukaLista<Tip> &s){
        std::cout << "Tekuci element Dvostruke Liste je postavljen na pocetak."<< std::endl;
         s.pocetak();
    }
template <typename Tip>
    void TestnaFKr(DvostrukaLista<Tip> &s){
        std::cout << "Tekuci element Dvostruke Liste je postavljen na kraj."<< std::endl;
        s.kraj();
    }

int main() {
    DvostrukaLista<int> dvlist;
    TestnaFDodajIza(dvlist,9);
    TestnaFPred(dvlist);
    TestnaFDodajIspred(dvlist,10);
    TestnaFTekuci(dvlist);
    TestnaFPred(dvlist);
    TestnaFTekuci(dvlist);
    TestnaFBrojElem(dvlist);
    TestnaFSljed(dvlist);
    for(int i(0);i<2;i++){
        TestnaFDodajIza(dvlist,i);
    }
    TestnaFTekuci(dvlist);
    TestnaFKr(dvlist);
    TestnaFTekuci(dvlist);
    TestnaFSljed(dvlist);
    TestnaFObrisi(dvlist);
    TestnaFTekuci(dvlist);
    TestnaFPoc(dvlist);
    TestnaFTekuci(dvlist);
    return 0;
}
