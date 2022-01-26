#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int DajMax(const std::vector<int> &a){
    if(a.size()==0) return 0;
    int max=a[0];
    for(int i(1);i<a.size();i++)
        if(max<a[i]) max = a[i];
    return max;
}


void DajCiftre(std::vector<int> &a, int i){
    std::vector<int> izl(a.size()),cifre(10,0);
    for(int j=0; j<a.size();j++)
        cifre[(a[j]/i)%10]++;
    for(int j=1; j<10;j++)
        cifre[j]+=cifre[j-1];
    for(int j=a.size()-1;j>=0;j--){
        izl[cifre[(a[j]/i)%10]-1] = a[j];
        cifre[(a[j]/i)%10]--;
    }
    a = izl;
}
bool JelList(std::vector<int> a,int i){
    return (i>=a.size()/2 && i<a.size());
}

void radixSort(vector<int> &a){
    int max = DajMax(a);
    for(int i(1);max/i>0;i*=10)
        DajCiftre(a,i);
}
int Roditelj(int i){
    return (i-1)/2;
}
int DesnoDijete(int i){
    return 2*i+2;
}
int LjevoDijete(int i){
    return 2*i+1;
}
void Popravi(std::vector<int> &a, int i){
    while(!JelList(a,i)){
        int veci =LjevoDijete(i);
        int dd =DesnoDijete(i);
        if(dd<a.size() && a[dd]>a[veci]){
            veci = dd;
        }
        if(a[i]>a[veci]) return;
        swap(a[i],a[veci]);

        i=veci;
    }
}
void stvoriGomilu(std::vector<int > &a){
    for(int i(a.size()/2);i>=0;i--){
        Popravi(a,i);
    }
}


void izbaciPrvi(vector<int> &a ,int &velicina){
    
    swap(a[0],a[a.size()-1]);
    if(a.size() != 0) 
        Popravi(a,0);
    
}
void PopraviG(std::vector<int> &a,int i){

    
    while (i!=0 && a[i]>a[Roditelj(i)]){
        int tmp(a[i]);
        a[i] = a[Roditelj(i)];
        a[Roditelj(i)] = tmp;
        i = Roditelj(i);
    }
}
void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina){
    a.resize(a.size()+1);
    a[a.size()-1] = umetnuti;
    PopraviG(a,a.size()-1);
}


void Izmjenjaj(std::vector<int> &a,int velicina, int i){
    int najveci = i, desno(DesnoDijete(i)),ljevo(LjevoDijete(i));
      if(ljevo < velicina && a[ljevo] > a[najveci])
        najveci = ljevo;
    if(desno < velicina && a[desno] > a[najveci])
        najveci = desno;
    if(najveci != i){
        swap (a[i],a[najveci]);
        Izmjenjaj(a,velicina,najveci);
    }
}

void gomilaSort(std::vector<int> &a){
    for(int i(a.size()/2 - 1);i>=0;i--)
         Izmjenjaj(a,a.size(),i);
    for(int i=a.size()-1;i>=0;i--){
        swap(a[0],a[i]);
        Izmjenjaj(a,i,0);
    }
}



int main() {

  
    return 0;
}
