//NA 2017/2018: Zadaća 1, Zadatak 1
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>
class Vector{
    std::vector<double> vec;
    // std::numeric_limits<double>::epsilon() 
    public :
        explicit Vector(int n){
            if(n<=0) throw std::range_error("Bad dimension");
            vec.assign(n,0);
            
        }
        Vector(std::initializer_list<double> l){
            if(l.size()==0) throw std::range_error("Bad dimension");
            vec.resize(l.size());
            std::copy(l.begin(),l.end(),vec.begin());
        }
        int NElems() const{
            return vec.size();
        }
        double &operator[](int i){
            return vec[i];
        }
        double operator[](int i) const{
            
            return vec[i];
        }
        double &operator()(int i){
            if(i<=0 || i>vec.size()){throw std::range_error("Invalid index");}
            return vec[i-1];    
        }
        double operator()(int i) const{
            if(i<=0 || i>vec.size()){throw std::range_error("Invalid index");}
            return vec[i-1];    
        }
        double Norm() const{
            double kn(0);
            for(int i(0);i<vec.size();i++){
                kn+=vec[i]*vec[i];
            }
            
            return std::sqrt(kn);
            
        }
        friend double VectorNorm(const Vector &v){
               double kn(0);
            for(int i(0);i<v.NElems();i++){
                kn+=v[i]*v[i];
            }
            
            return std::sqrt(kn);
         
        }
        double GetEpsilon() const{
            double a(Norm());
            return (std::numeric_limits<double>::epsilon())*a;
        }
        void Print(char separator = '\n', double eps = -1) const{
            for(int i(0);i<vec.size();i++){
                
            if(eps<0){
                    if(std::fabs(vec[i])<GetEpsilon()){
                        std::cout << 0;
                        if(i==vec.size()-1) break;
                        else std::cout<< separator;
                }else{
                    std::cout << vec[i];
                    if(i==vec.size()-1) break;
                    else std::cout<< separator;
            }}else{
                if(std::fabs(vec[i])<eps){    
                  std::cout << 0;
                        if(i==vec.size()-1) break;
                        else std::cout<< separator;
                  
                }else{
                std::cout << vec[i];
                if(i==vec.size()-1) break;
                else std::cout<< separator;
            }
        }}}
        friend void PrintVector(const Vector &v, char separator = '\n',double eps = -1){
             for(int i(0);i<v.NElems();i++){
                
            if(eps<0){
                    if(std::fabs(v[i])<v.GetEpsilon()){
                        std::cout << 0;
                        if(i==v.NElems()-1) break;
                        else std::cout<< separator;
                }else{
                    std::cout << v[i];
                    if(i==v.NElems()-1) break;
                    else std::cout<< separator;
            }}else{
                if(std::fabs(v[i])<eps){    
                  std::cout << 0;
                        if(i==v.NElems()-1) break;
                        else std::cout<< separator;
                  
                }else{
                std::cout << v[i];
                if(i==v.NElems()-1) break;
                else std::cout<< separator;
            }
        }}}
        friend Vector operator +(const Vector &v1, const Vector &v2){
            if(v1.NElems()!=v2.NElems()) throw std::domain_error("Incompatible formats");
            Vector v3(v1.NElems());
            for(int i(0);i<v1.NElems();i++){
                v3[i]=v1[i]+v2[i];
            }
            return v3;
        }
        Vector &operator +=(const Vector &v){
            if(NElems()!=v.NElems()) throw std::domain_error("Incompatible formats");
            for(int i(0);i<NElems();i++){
                vec[i]+=v[i];
            }
            return *this;
        }
        friend Vector operator -(const Vector &v1, const Vector &v2){
             if(v1.NElems()!=v2.NElems()) throw std::domain_error("Incompatible formats");
            Vector v3(v1.NElems());
            for(int i(0);i<v1.NElems();i++){
                v3[i]=v1[i]-v2[i];
            }
            return v3;
        }
        Vector &operator -=(const Vector &v){
         if(NElems()!=v.NElems()) throw std::domain_error("Incompatible formats");
            for(int i(0);i<NElems();i++){
                vec[i]-=v[i];
            }
            return *this;
        }
        friend Vector operator *(double s, const Vector &v){
             Vector v3(v.NElems());
             for(int i(0);i<v.NElems();i++){
                v3[i]=v[i]*s;
            }
            return v3;
        }
        friend Vector operator *(const Vector &v, double s){
             Vector v3(v.NElems());
             for(int i(0);i<v.NElems();i++){
                v3[i]=v[i]*s;
            }
            return v3;
        }
        Vector &operator *=(double s){
             for(int i(0);i<NElems();i++){
                vec[i]*=s;
            }
            return *this;
        }
        friend double operator *(const Vector &v1, const Vector &v2){
            if(v1.NElems()!=v2.NElems()) throw std::domain_error("Incompatible formats");
            double sum(0);
            for(int i(0);i<v1.NElems();i++){
                sum+=v1[i]*v2[i];
            }
            return sum;
        }
        friend Vector operator /(const Vector &v, double s){
            if(s==0) throw std::domain_error("Division by zero");
            Vector v3(v.NElems());
            for(int i(0);i<v.NElems();i++){
                v3[i]=v[i]/s;
            }
            return v3;
        }
        Vector &operator /=(double s){
            if(s==0) throw std::domain_error("Division by zero");
            for(int i(0);i<NElems();i++){
                vec[i]/=s;
            }
            return *this;
        }
};

class Matrix{
    
        std::vector<std::vector<double>> mat;
    
    public:
        Matrix(int m, int n){
            if(n<=0 || m<=0) throw std::range_error("Bad dimension");
            mat.resize(m);
            for(int i(0);i<m;i++){
                mat[i].resize(n);
                for(int j(0);j<n;j++){
                    mat[i][j]=0;
                }
            }
            
        }
        Matrix(const Vector &v){
            mat.resize(v.NElems());
            for(int i(0);i<mat.size();i++){
                mat[i].resize(1);              
                mat[i][0]=v[i];
            }
        }
        Matrix(std::initializer_list<std::vector<double>> l){
            if(l.size()<=0) throw std::range_error("Bad dimension");
            int br(0);
            mat.resize(l.size());
            for(auto i(l.begin());i!=l.end();i++){
                if(i->size()<=0) throw std::range_error("Bad dimension");
                auto it2(*i);
                for(int j(0);j<it2.size();j++){
                    mat[br].resize(it2.size());
                    if(br==0){
                        mat[br][j]=it2[j];
                    }else{
                        if(i->size()!=(i-1)->size()) throw std::logic_error("Bad matrix");
                        mat[br][j]=it2[j];
                    }
                }
                br++;
            }
        }
        int NRows() const{return mat.size();}
        int NCols() const{return mat[0].size();}
        double *operator[](int i){
            double* p(&mat[i][0]);
            return p;
        }
        const double *operator[](int i) const{
            const double* p(&mat[i][0]);
            return p;
        }
        double &operator()(int i, int j){
            if(i<=0 || j<=0 || i>mat.size() || j>mat[0].size()) throw std::range_error("Invalid index");
            return mat[i-1][j-1];
            
        }
        double operator()(int i, int j) const{
            if(i<=0 || j<=0 || i>mat.size() || j>mat[0].size()) throw std::range_error("Invalid index");
            return mat[i-1][j-1];
            
        }
        double Norm() const{
            double sum(0);
            for(int i(0);i<mat.size();i++){
                for(int j(0);j<mat[i].size();j++){
                    sum+=mat[i][j]*mat[i][j];
                }
            }
            return std::sqrt(sum);
        }
        friend double MatrixNorm(const Matrix &m){
            double sum(0);
            for(int i(0);i<m.NRows();i++){
                for(int j(0);j<m.NCols();j++){
                    sum+=m(i+1,j+1) * m(i+1,j+1);
                }
            }
            return std::sqrt(sum);
        }
        double GetEpsilon() const{
            return (std::numeric_limits<double>::epsilon())*Norm();
        }
        void Print(int width = 10, double eps = -1) const{
            for(int i(0);i<mat.size();i++){
                for(int j(0);j<mat[i].size();j++){
                    if(eps<0){
                        if(std::fabs(mat[i][j])<GetEpsilon()){
                            std::cout<< std::setw(width) << 0;
                        }else{
                            std::cout<< std::setw(width)<<mat[i][j];
                        }
                    }else{
                        if(std::fabs(mat[i][j])<eps){    
                            std::cout<< std::setw(width)<< 0;
                        }else{
                            std::cout<< std::setw(width)<<mat[i][j];
                        }
                    }
                }
                std::cout <<std::endl;
            }
        }
        friend void PrintMatrix(const Matrix &m, int width = 10, double eps = -1){
                for(int i(1);i<=m.NRows();i++){
                    for(int j(1);j<=m.NCols();j++){
                    if(eps<0){
                        if(std::fabs(m(i,j))<m.GetEpsilon()){
                            std::cout<< std::setw(width) << 0;
                        }else{
                            std::cout<< std::setw(width)<<m(i,j);
                        }
                    }else{
                        if(std::fabs(m(i,j))<eps){    
                            std::cout<< std::setw(width)<< 0;
                        }else{
                            std::cout<< std::setw(width)<<m(i,j);
                        }
                    }
                }
                std::cout <<std::endl;
            }
        }
        friend Matrix operator +(const Matrix &m1, const Matrix &m2){
            if(m1.NCols()!=m2.NCols() || m1.NRows()!=m2.NRows()) throw std::domain_error("Incompatible formats");
            Matrix m3(m1.NRows(),m1.NCols());
            for(int i(1);i<=m1.NRows();i++){
                for(int j(1);j<=m1.NCols();j++){
                    m3(i,j)=m1(i,j)+m2(i,j);
                }
            }
            return m3;
        }
        Matrix &operator +=(const Matrix &m){
            if(mat[0].size()!=m.NCols() || mat.size()!=m.NRows()) throw std::domain_error("Incompatible formats");
            for(int i(1);i<=m.NRows();i++){
                for(int j(1);j<=m.NCols();j++){
                    mat[i-1][j-1]+=m(i,j);
                }
            }
            return *this;
        }
        friend Matrix operator -(const Matrix &m1, const Matrix &m2){
                if(m1.NCols()!=m2.NCols() || m1.NRows()!=m2.NRows()) throw std::domain_error("Incompatible formats");
            Matrix m3(m1.NRows(),m1.NCols());
            for(int i(1);i<=m1.NRows();i++){
                for(int j(1);j<=m1.NCols();j++){
                    m3(i,j)=m1(i,j)-m2(i,j);
                }
            }
            return m3;
        }
        Matrix &operator -=(const Matrix &m){
            if(mat[0].size()!=m.NCols() || mat.size()!=m.NRows()) throw std::domain_error("Incompatible formats");
            for(int i(1);i<=m.NRows();i++){
                for(int j(1);j<=m.NCols();j++){
                    mat[i-1][j-1]-=m(i,j);
                }
            }
            return *this;
        }
        friend Matrix operator *(double s, const Matrix &m){
            Matrix m3(m);
            for(int i(1);i<=m.NRows();i++){
                for(int j(1);j<=m.NCols();j++){
                    m3(i,j)*=s;
                }
            }
            return m3;
        }
        friend Matrix operator *(const Matrix &m, double s){
            Matrix m3(m);
            for(int i(1);i<=m.NRows();i++){
                for(int j(1);j<=m.NCols();j++){
                    m3(i,j)*=s;
                }
            }
            return m3;
        }
        Matrix &operator *=(double s){
             for(int i(0);i<NRows();i++){
                for(int j(0);j<NCols();j++){
                    mat[i][j]*=s;
                }
            }
            return *this;
        }
        friend Matrix operator *(const Matrix &m1, const Matrix &m2){
            if(m1.NCols()!=m2.NRows()) throw std::domain_error("Incompatible formats");
            Matrix m3(m1.NRows(),m2.NCols());
            for(int k(1);k<=m3.NRows();k++){
                for(int i(1);i<=m1.NCols();i++){
                    
                    double sum(0);
                    for(int j(1);j<=m2.NRows();j++){
                        sum+=m1(k,j) * m2(j,i);
                    }
                m3(k,i)=sum;
            }
            }
            return m3;
        }
        Matrix &operator *=(const Matrix &m){
            if(NCols()!=m.NRows()) throw std::domain_error("Incompatible formats");
            
            std::vector<std::vector<double>> mat1;
            mat1.resize(NRows());
            
            for(int k(1);k<=NRows();k++){
                
                mat1[k-1].resize(m.NCols());
                for(int i(1);i<=NCols();i++){
                    
                    double sum(0);
                    
                    for(int j(1);j<=m.NRows();j++){
                        sum+=mat[k-1][j-1] * m(j,i);
                    }
                mat1[k-1][i-1]=sum;
                }
            }
            mat=mat1;
            return *this;
        }
        friend Vector operator *(const Matrix &m, const Vector &v){
            if(m.NCols()!=v.NElems()) throw std::domain_error("Incompatible formats");

            Vector v1(m.NRows());
            for(int i(1);i<=m.NRows();i++){
                double sum(0);
                for(int j(1);j<=2;j++){
                    sum+=m(i,j)*v(j);
                }
                v1(i)=sum;
            }
            return v1;
        }
        friend Matrix Transpose(const Matrix &m){
            Matrix m3(m.NCols(),m.NRows());
            for(int i(1);i<=m.NRows();i++){
                for(int j(1);j<=m.NCols();j++){
                    m3(j,i)=m(i,j);
                }
            }
            return m3;
        }
        void Transpose(){
            if(NCols()==NRows()){
                for(int i(0);i<NRows();i++){
                    for(int j(i);j<NCols();j++){
                        if(i==j){}
                        else{
                            double tmp(mat[i][j]);
                            mat[i][j]=mat[j][i];
                            mat[j][i]=tmp;
                        }
                    }
                }
            }else{
                std::vector<std::vector<double>> mat1;
                mat1.resize(mat[0].size());
                for(int i(0);i<mat[0].size();i++){
                    mat1[i].resize(mat.size());
                    for(int j(0);j<mat.size();j++){
                        mat1[i][j]=mat[j][i];
                    }
                }
            
                mat=mat1;
            }
        }

    
};

int main (){

    try{
        Vector v1(0);
    }catch(std::range_error e){
        std::cout << e.what() << std::endl;
    }
      try{
        Vector v1{};
    }catch(std::range_error e){
        std::cout << e.what() << std::endl;
    }
    Vector v1(1);
    Vector v2(3);
    Vector v3{1,2,3};
    for(int i(0);i<v2.NElems();i++){
        v2[i]=i;
    }
    v1(1)=3;
    PrintVector(v1);
    std::cout <<"\n";
    PrintVector(v2);
    std::cout <<"\n";
    PrintVector(v3);
    std::cout <<"\n";
    try {
        v1=v1+v2;
    }
    catch (std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
    v3=v3+v2;
    v2+=v3;
    //Norm i GetEpsilon se ovdje testiraju
    v2.Print(' ',2);
    std::cout <<"\n";
    v3.Print(' ',0.25);
    std::cout <<"\n";
    v1=v1*5.2;
    v1.Print(' ');
    std::cout << std::endl;
    v1/=5.2;
    v1.Print(' ');
    std::cout << std::endl;
    try {
        v1-=v3;
    }
    catch (std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
    try {
        v1=v1-v2;
    }
    catch (std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
    double a(v3*v2);
    std::cout << "Proizvod vektora v1 i v2 iznosi: "<< a << std::endl;
    v3=v3-v2;
    v3.Print(' ',5);
    std::cout << std::endl;
    v3.Print(' ');
    v3=v3/(-1);
    std::cout << std::endl;
    v3.Print(' ');
    std::cout << std::endl;
    
    try{
        Matrix m(0,2);
    }catch(std::range_error e){
        std::cout << e.what() << std::endl;
    }
    try{
        Matrix m(-2,3);
    }catch(std::range_error e){
        std::cout << e.what() << std::endl;
    }
    try{
        Matrix m{{3,2,3},{2,3}};
    }catch(std::logic_error e){
        std::cout << e.what() << std::endl;
    }
    try{
        Matrix m{{3,2,3},{2,3,4},{}};
    }catch(std::range_error e){
        std::cout << e.what() << std::endl;
    }
    Matrix m1(3,2);
    Matrix m2(v3);
    Matrix m3{{3,2},{4,5}};
    m1.Print(2);
    std::cout << std::endl;
    m2.Print(2);
    std::cout << std::endl;
    m3.Print(2);
    std::cout << std::endl;
    for(int i(0);i<m1.NRows();i++){
        for(int j(0);j<m1.NCols();j++){
            m1[i][j]=i+j+1;
        }
    }
    m1.Print(2);
    m2(1,1)=3;
    std::cout << std::endl;
    
    Matrix m4(3,2);
    m4 = m1 * m3;
    m4.Print(3);
    std::cout << std::endl;
    
    m4=m4+m1;
    m1+=m4;
    m4.Print(3);
    std::cout << std::endl;
    m1.Print(3);
    std::cout << std::endl;
    
    try {
        m3+=m2;
    }
    catch (std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
    try {
        m2= m4+m3;
    }
    catch (std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
    m4*=0.3;
    //Ovdje se testiraju i norme
    std::cout << "Sta se desi kad stavimo da je eps 5." << std::endl;
    m4.Print(5,5);
    std::cout << std::endl;
    
    m4.Transpose();
    m4.Print(5);
    std::cout << std::endl;
    
    m4(1,1)=4;
    try{
        m4(5,1)=3;
    }catch(std::range_error e){
        std::cout << e.what() << std::endl;
    }
    m4(1,3)=9;
    
    m4.Print(5);
    std::cout << std::endl;
    
    m3*= m4;
    m3.Print(5);
    std::cout << std::endl;
    
     try {
        m2= m4-m1;
    }
    catch (std::domain_error e) {
        std::cout << e.what() << std::endl;
    }
    
    m2=m4-m3;
    PrintMatrix(m2);
    std::cout << std::endl;
    PrintMatrix(m4);
    std::cout << std::endl;
    PrintMatrix(m3);
    std::cout << std::endl;
    PrintMatrix(m1);
    std::cout << std::endl;
    
    Matrix  m5(Transpose(m1));
    
    PrintMatrix(m5,5);
    std::cout << std::endl;
    
    m5-=m4;
    PrintMatrix(m5,5);
    std::cout << std::endl;
    
    m5*=178;
    PrintMatrix(m5,10,3500);
    std::cout << std::endl;
    
    Matrix m9(v2);
        PrintMatrix(m9,3);
    std::cout << std::endl;
    
    m5=m5*v2;
    
    PrintMatrix(m5,5,3);
    std::cout << std::endl;
    
    	return 0;
}
