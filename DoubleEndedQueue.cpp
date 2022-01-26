#include <iostream>
#include<stdexcept>

template <typename Tip>
    class DvostraniRed{
        int brelem;
        struct Cvor{
          Tip el;
          Cvor * sljed;
          Cvor * pr;
          Cvor(Tip element=0, Cvor* sljedeci=0, Cvor* prethodni=0):el(element),sljed(sljedeci),pr(prethodni){}
        };
        
        Cvor* Poc;
        Cvor* Vrh;
        public:
        DvostraniRed(){
            brelem=0;
            Poc=Vrh=0;
        }
        DvostraniRed(const DvostraniRed<Tip> &r){
            brelem=r.brojElemenata();
            Cvor* PocNovog(r.Poc);
            if(brelem==0){
                Poc=0;
                Vrh=0;
            }else if(brelem==1){
                Cvor* Novi(new Cvor(PocNovog->el,0,0));
                Vrh=Poc=Novi;
            }else{
                Cvor* PrviNovi(new Cvor(PocNovog->el));
                Vrh=Poc=PrviNovi;
                PocNovog=PocNovog->pr;
                while(PocNovog!=0){
                    Cvor* Novi(new Cvor(PocNovog->el));
                    Cvor* Pom(Vrh);
                    Vrh=Novi;
                    Vrh->sljed=Pom;
                    Pom->pr=Vrh;
                    PocNovog=PocNovog->pr;    
                }
                
                
                   
            }
        }
        DvostraniRed<Tip> &operator =(DvostraniRed<Tip> &r){
            if(Vrh==r.Vrh) return *this;
                while(Vrh!=Poc){
                Cvor* Pom(Vrh);
                Vrh=Vrh->sljed;
                delete Pom;
            }
            delete Poc;
             brelem=r.brojElemenata();
            Cvor* PocNovog(r.Poc);
            if(brelem==0){
                Poc=0;
                Vrh=0;
            }else if(brelem==1){
                Cvor* Novi(new Cvor(PocNovog->el,0,0));
                Vrh=Poc=Novi;
            }else{
                 Cvor* PrviNovi(new Cvor(PocNovog->el));
                Vrh=Poc=PrviNovi;
                PocNovog=PocNovog->pr;
                while(PocNovog!=0){
                    Cvor* Novi(new Cvor(PocNovog->el));
                    Cvor* Pom(Vrh);
                    Vrh=Novi;
                    Vrh->sljed=Pom;
                    Pom->pr=Vrh;
                    PocNovog=PocNovog->pr;    
                }
                
            }
            return *this;
        }
        const DvostraniRed<Tip> operator =(DvostraniRed<Tip> &r)const{
            if(Vrh==r.Vrh) return *this;
                while(Vrh!=Poc){
                Cvor* Pom(Vrh);
                Vrh=Vrh->sljed;
                delete Pom;
            }
            delete Poc;
             brelem=r.brojElemenata();
            Cvor* PocNovog(r.Poc);
            if(brelem==0){
                Poc=0;
                Vrh=0;
            }else if(brelem==1){
                Cvor* Novi(new Cvor(PocNovog->el,0,0));
                Vrh=Poc=Novi;
            }else{
                Cvor* PrviNovi(new Cvor(PocNovog->el));
                Vrh=Poc=PrviNovi;
                PocNovog=PocNovog->pr;
                while(PocNovog!=0){
                    Cvor* Novi(new Cvor(PocNovog->el));
                    Cvor* Pom(Vrh);
                    Vrh=Novi;
                    Vrh->sljed=Pom;
                    Pom->pr=Vrh;
                    PocNovog=PocNovog->pr;    
                }
                
            }
            return *this;
        }
        ~DvostraniRed(){
            while(Vrh!=Poc){
                Cvor* Pom(Vrh);
                Vrh=Vrh->sljed;
                delete Pom;
            }
            delete Poc;
        }
        void brisi(){
            while(Vrh!=Poc){
                Cvor* Pom(Vrh);
                Vrh=Vrh->sljed;
                delete Pom;
                
            }
            delete Poc;
            Poc=Vrh=0;
            brelem=0;
        }
        void staviNaVrh(const Tip& el){
            Cvor* Novi(new Cvor(el));
            if(brelem==0){
                Poc=Vrh=Novi;
            }else if(brelem==1){
                Vrh=Novi;
                Vrh->sljed=Poc;
                Poc->pr=Vrh;
            }else{
                Cvor* Pom(Vrh);
                Vrh=Novi;
                Vrh->sljed=Pom;
                Pom->pr=Vrh;
            }
            brelem++;
        }
        Tip  skiniSaCela() {
            if(brelem==0) throw std::logic_error("Prazno");
            if(brelem==1){
                
                Tip a(Poc->el);
                delete Poc;
                Poc=Vrh=0;
                brelem--;
                return a;
            }else if(brelem==2){
                Tip a(Poc->el);
                delete Poc;
                Poc=Vrh;
                Vrh->sljed=0;
                Poc->sljed=0;
                brelem--;
                return a;
            
            
            }else{
                
                Tip a(Poc->el);
                Cvor* Pomocni(Poc->pr);
                delete Poc;
                Poc=Pomocni;
                Poc->sljed=0;
                brelem--;
                return a;
            }
        }
        Tip  skiniSaVrha() {
            if(brelem==0) throw std::logic_error("Prazno");
            if(brelem==1){
                
                Tip a(Vrh->el);
                delete Vrh;
                Poc=Vrh=0;
                brelem--;
                return a;
            }else{
                
                Tip a(Vrh->el);
                Cvor* Pomocni(Vrh->sljed);
                delete Vrh;
                Vrh=Pomocni;
                Vrh->pr=nullptr;
                brelem--;
                return a;
            }
        }
        Tip & vrh(){
            if(brelem==0) throw std::logic_error("Prazno");
            return Vrh->el;
        }
        int brojElemenata() const{
            return brelem;
        }
        Tip & celo(){
            if(brelem==0) throw std::logic_error("Prazno");
            return Poc->el;
        }
        void staviNaCelo(Tip el){
             Cvor* Novi(new Cvor(el));
            if(brelem==0){
                Poc=Vrh=Novi;
            }else if(brelem==1){
                Poc=Novi;
                Vrh->sljed=Poc;
                Poc->pr=Vrh;
            }else{
                Cvor* Pom(Poc);
                Poc=Novi;
                Pom->sljed=Poc;
                Poc->pr=Pom;
            }
            brelem++;
        
        }
    };



    void TestnaFStaviCelo(){
        DvostraniRed<int> r;
        r.staviNaCelo(3);
        std::cout << "U Dvostruki Red je stavljen element na Celo: "<< 3 << std::endl;
    }
    
    void TestnaFStaviVrh(){
        DvostraniRed<int> r;
        for(int i(0);i<4;i++){
        r.staviNaVrh(i);
        std::cout << "U Dvostruki Red je stavljen element na vrh: "<< i << std::endl;
        }
    }

    void TestnaFBrisi(){
        DvostraniRed<int> r;
        r.brisi();
        std::cout << "Dvostrani Red je resetovan!"<<  std::endl;
    }

    void TestnaFCelo(){
        DvostraniRed<int> r;
        try{
            int a(r.celo());
            std::cout << "Na celu Dvostranog Reda se nalazi element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        r.staviNaCelo(3);
        try{
            int a(r.celo());
            std::cout << "Na celu Reda se nalazi element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        
    }
    void TestnaFVrh(){
        DvostraniRed<int> r;
        try{
            int a(r.vrh());
            std::cout << "Na celu Dvostranog Reda se nalazi element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        r.staviNaCelo(3);
        try{
            int a(r.vrh());
            std::cout << "Na celu Reda se nalazi element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        
    }


    void TestnaFSkiniSaCela(){
        DvostraniRed<int> r;
        try{
            int a(r.skiniSaCela());
            std::cout << "Sa Cela Reda je uklonjen element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        r.staviNaCelo(5);
        try{
            int a(r.skiniSaCela());
            std::cout << "Sa Cela Reda je uklonjen element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        
    }  void TestnaFSkiniSaVrha(){
        DvostraniRed<int> r;
        try{
            int a(r.skiniSaVrha());
            std::cout << "Sa Cela Reda je uklonjen element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        r.staviNaCelo(5);
        try{
            int a(r.skiniSaVrha());
            std::cout << "Sa Cela Reda je uklonjen element: "<< a << std::endl;
        }catch(std::logic_error e){
            std::cout << e.what() << std::endl;
        }
        
    }


    void TestnaFBrojElem(){
        DvostraniRed<int> r;
        for(int i(1);i<13;i++){
            r.staviNaCelo(i);
        }
        std::cout << "Dvostrani red ima "<<r.brojElemenata() <<" elemenata."<< std::endl;
    }





int main() {
    TestnaFBrisi();
    TestnaFBrojElem();
    TestnaFCelo();
    TestnaFSkiniSaCela();
    TestnaFStaviCelo();
    TestnaFStaviVrh();
    TestnaFVrh();
    TestnaFSkiniSaVrha();
    
}
