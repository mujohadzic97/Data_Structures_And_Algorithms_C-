#include <iostream>
template<typename E>
class RBStablo{
    struct Cvor{
        Cvor* l;
        Cvor* r;
        Cvor* par;
        E key;
        char boja;
        Cvor(E key,Cvor* l=0,Cvor* r=0,Cvor* par=0,char bo='R') :key(key),l(l),r(r),par(par),boja(bo){}
    };
    Cvor* korijen;
    Cvor* nill;
    public:
    RBStablo(){
        nill = new Cvor(0,0,0,0,'B');
        korijen = nill;
    }
    void dodaj(E key,RBStablo* T){
        Cvor* novi = new Cvor(key,T->nill,T->nill,T->nill,'B');
        RB_Insert(T,novi);
    }
    void Left_Rotate(RBStablo* T,Cvor* x){
       Cvor* y = x->r;
        x->r = y->l;
        if(y->l!=T->nill)
            y->l->par=x;
        y->par = x->par;
        if(x->par == T->nill)
            T->korijen = y;
        else if(x == x->par->l)
            x->par->l = y;
        else
            x->par->r=y;
        y->l = x;
        x->par = y;
    }
    void RB_Insert(RBStablo* T, Cvor* z){
        Cvor* y = T->nill;
        Cvor* x = T->korijen;
        while(x!=T->nill){
            y = x;
            if(z->key < x->key)
                x=x->l;
            else
                x=x->r;
        }
        z->par=y;
        if(y== T->nill){
            T->korijen = z;
        }
        else if(z->key < y->key)
            y->l = z;
        else 
            y->r = z;
        z->l = T->nill;
        z->r = T->nill;
        z->boja = 'R';
        if(z==korijen) {
            z->boja='B';
            z->par = T->nill;
        }
        if(z->par !=T->nill)
        RB_Insert_Fixup(T,z);
            
    }
    void Right_Rotate(RBStablo* T,Cvor* x){
        Cvor* y = x->l;
        x->l = y->r;
        if(y->r!=T->nill)
            y->r->par=x;
        y->par = x->par;
        if(x->par == T->nill)
            T->korijen = y;
        else if(x == x->par->l)
            x->par->l = y;
        else
            x->par->r=y;
        y->r = x;
        x->par = y;
    }
    void RB_Insert_Fixup(RBStablo* T,Cvor* z){
        while(z->par->boja =='R' && korijen!=z){
            if(z->par == z->par->par->l){
                Cvor* y= z->par->par->r;
                if(y->boja=='R'){
                    z->par->boja='B';
                    y->boja='B';
                    z->par->par->boja='R';
                    z=z->par->par;
                }else{
                    
                 if(z == z->par->r){
                    z=z->par;
                    Left_Rotate(T,z);
                }
                    z->par->boja ='B';
                    z->par->par->boja ='R';
                    Right_Rotate(T,z->par->par);
                }
            }else{ 
                Cvor* y= z->par->par->l;
                if(y->boja=='R'){
                    z->par->boja='B';
                    y->boja='B';
                    z->par->par->boja='R';
                    z=z->par->par;
                
                }else{
                    
                if(z == z->par->l){
                    z=z->par;
                    Right_Rotate(T,z);
                }
                    z->par->boja ='B';
                    z->par->par->boja ='R';
                    Left_Rotate(T,z->par->par);
                }
            }
        }
    
        T->korijen->boja = 'B';
        
    }
    void ispisi(){
        printRBSInorder(korijen);
    }
    void printRBSInorder(Cvor* prolaz){
        if(prolaz == nill){
            return;
        }
printRBSInorder(prolaz->l);
        std::cout << prolaz->key<< " "<<prolaz->boja<<" ";
        printRBSInorder(prolaz->r);
        
    }
    void RB_Transplant(RBStablo* T, Cvor* u, Cvor*v){
        if(u->par == T->nill)
            T->korijen = v;
        else if(u == u->par->l)
            u->par->l=v;
        else
            u->par->r = v;
        v->par=u->par;
    }
    void RB_Delete(RBStablo* T, Cvor* z){
        Cvor* y=z;
        Cvor* x;
        char yoc = y->boja;
        if(z->l == T->nill){
            x = z->r;
            RB_Transplant(T,z,z->r);
        }else if(z->r == T->nill){
            x = z->l;
            RB_Transplant(T,z,z->l);
        }else{
            y = TREE_MIN(z->r);
            yoc = y->boja;
            x = y->r;
            if(y->par==z){
                x->par = y;
            }else{
                RB_Transplant(T,y,y->r);
                y->r = z->r;
                y->r->par = y;
            }
            RB_Transplant(T,z,y);
            
            y->l = z->l;
            y->l->par = y;
            y->boja = z->boja;
        }
        if(yoc =='B')
            RB_Delete_Fixup(T,x);
    }
    void RB_Delete_Fixup(RBStablo* T,Cvor* x){
        while(x!=T->korijen && x->boja=='B'){
            Cvor* w;
            if(x==x->par->l){
                w = x->par->r;
                if(w->boja=='R'){
                    w->boja = 'C';
                    x->par->boja = 'R';
                    Left_Rotate(T,x->par);
                    w = x->par->r;
                }
                if(w->l->boja=='B' && w->r->boja=='B'){
                    w->boja='R';
                    x=x->par;
                }else{
                    
                    if(w->r->boja =='B'){
                        w->l->boja = 'B';
                        w->boja = 'R';
                        Right_Rotate(T,w);
                        w = x->par->r;
                    }
                    w->boja=x->par->boja;
                    x->par->boja = 'B';
                    w->r->boja = 'B';
                    Left_Rotate(T,x->par);
                    x=T->korijen;
                }
            }else{
                w = x->par->l;
                if(w->boja=='R'){
                    w->boja = 'C';
                    x->par->boja = 'R';
                    Left_Rotate(T,x->par);
                    w = x->par->r;
                }
                if(w->r->boja=='B' && w->l->boja=='B'){
                    w->boja='R';
                    x=x->par;
                }else{
                    
                    if(w->l->boja =='B'){
                        w->r->boja = 'B';
                        w->boja = 'R';
                        Right_Rotate(T,w);
                        w = x->par->l;
                    }
                    w->boja=x->par->boja;
                    x->par->boja = 'B';
                    w->l->boja = 'B';
                    Left_Rotate(T,x->par);
                    x=T->korijen;
                }
            }
        }
        x->boja ='B';
    }
    Cvor* TREE_MIN(Cvor* m){
        Cvor* prolaz =m;
        
        
        while(prolaz->l!=nill){
            prolaz=prolaz->l;
        }
        return prolaz;
    }
    void obrisi(E key, RBStablo* T){
        Cvor* brisem=korijen;
        while(key!=brisem->key){
            if(key>brisem->key){
                brisem = brisem->r;
            }else{
                brisem = brisem->l;
            }
        }
        RB_Delete(T,brisem);
    }
};

int main() {
    RBStablo<int> T =RBStablo<int>();
    /*T.dodaj(6,&T);
    T.dodaj(11,&T);
    T.dodaj(10,&T);
    T.dodaj(2,&T);
    T.dodaj(9,&T);
    T.dodaj(7,&T);
    T.dodaj(5,&T);
    T.dodaj(13,&T);
    T.dodaj(22,&T);
    T.dodaj(27,&T);
    T.dodaj(36,&T);
    T.dodaj(12,&T);
    T.dodaj(31,&T);
    T.ispisi();

    T.ispisi();*/
    int opcija;
    int broj;
    do {
        std::cout<<"\nIzaberite opciju"<<std::endl;
        std::cout<<"1.Umetanje cvora\n2.Inorder ispis cvorova\n3.Brisanje Cvora\n4.Izlaz"<<std::endl;
        std::cin>>opcija;  
        if(opcija==1) {
            std::cout<<"Upišite element koji želite dodati: ";
            std::cin>>broj;
            T.dodaj(broj, &T);
        }
        else if(opcija==2){
            T.ispisi();
        }else if(opcija==3){
            std::cout<<"Upišite element koji želite obrisati: ";
            std::cin>>broj;
            T.obrisi(broj,&T);
        }
    } while (opcija!=4);
    return 0;
}
