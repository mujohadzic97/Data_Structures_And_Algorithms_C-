//NA 2017/2018: Zadaća 2, Zadatak 1
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
            return (std::numeric_limits<double>::epsilon())*a*10;
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
                else std::cout<< separator<<std::endl;
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
        void Chop(double eps = -1);
        bool EqualTo(const Vector &v, double eps = -1) const;
};

void Vector::Chop(double eps){
    if(eps < 0) eps = GetEpsilon();
    for(int i(0);i<NElems();i++)
        if(fabs(vec[i])<eps) vec[i] = 0; 
}
bool Vector::EqualTo(const Vector &v,double eps)const{
    if(eps<0) eps = GetEpsilon();
    if(v.NElems()!= NElems()) return false;
    for(int i(0);i<NElems();i++)
        if(std::fabs(vec[i]-v[i])>eps) return false;    
    
    return true;
}

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
            return (std::numeric_limits<double>::epsilon())*Norm()*10;
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

            Vector v1(v.NElems());
            for(int i(0);i<v.NElems();i++){
                double sum(0);
                for(int j(0);j<v.NElems();j++){
                    sum+=m[i][j]*v[j];
                }
                v1[i]=sum;
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
        
        void Chop(double eps = -1);
        bool EqualTo(const Matrix &m, double eps = -1) const;
        friend Matrix LeftDiv(Matrix m1, Matrix m2);
        friend Vector LeftDiv(Matrix m, Vector v);
        friend Matrix operator /(const Matrix &m, double s);
        Matrix &operator /=(double s);
        
        
        friend Matrix operator /(Matrix m1, Matrix m2);
        Matrix &operator /=(Matrix m);
        
        
        double Det() const;
        friend double Det(Matrix m);
        void Invert();
        friend Matrix Inverse(Matrix m);
        
        void ReduceToRREF();
        friend Matrix RREF(Matrix m);
        int Rank() const;
        friend int Rank(Matrix m);
};
void Matrix::Chop(double eps){
    if(eps < 0) eps= GetEpsilon();
    for(int i(0);i<mat.size();i++){
        for(int j(0);j<mat[i].size();j++){
            if(fabs(mat[i][j]) < eps) mat[i][j] = 0;
        }
    }
}
bool Matrix::EqualTo(const Matrix &m, double eps)const{
    if(mat.size()!=m.NRows() && mat[0].size()!=m.NCols()) return false;
    if(eps<0) eps=GetEpsilon();
    for(int i(0);i<mat.size();i++){
        for(int j(0);j<mat[i].size();j++){
            if(fabs(mat[i][j]-m[i][j])> eps) return false;
        }        
    }
    return true;
}
Matrix LeftDiv(Matrix m1, Matrix m2){
    if(m1.NCols()!= m1.NRows()) throw std::domain_error("Divisor matrix is not square");
    if(m2.NRows()!= m1.NRows()) throw std::domain_error("Incompatible formats");
    for(int k(0);k<m1.NRows();k++){
        int p = k;
        for(int i(k+1);i<m1.NRows();i++){
        
            if(fabs(m1[i][k]) > fabs(m1[p][k])) p = i;
        }
        if(fabs(m1[p][k]) < m1.GetEpsilon()){ throw std::domain_error("Divisor matrix is singular");
    }if(p!= k){
        for(int i(0);i<m1.NCols();i++){
            auto temp(m1[p][i]);
            m1[p][i]=m1[k][i];
            m1[k][i]=temp;
            
        }
        for(int i(0);i<m2.NCols();i++){
            auto tem1(m2[p][i]);
            m2[p][i]=m2[k][i];
            m2[k][i]=tem1;
        }
    }
    for(int i(k+1);i<m1.NRows();i++){
        double m = m1[i][k]/m1[k][k];
    
        for(int j(k+1);j<m1.NRows();j++){
            m1[i][j] = m1[i][j] - m* m1[k][j];
            
            
        }
        for(int j(0);j<m2.NCols();j++){
            m2[i][j] = m2[i][j] - m*m2[k][j];
        }
    }}
    Matrix x(m1.NRows(),m2.NCols());
    for(int k(0);k<m2.NCols();k++){
        for(int i(m1.NRows() - 1); i>=0;i--){
            double s=m2[i][k];
            for(int j(i+1);j<m1.NRows();j++)
                s = s - m1[i][j]*x[j][k];
            
            x[i][k] = s/m1[i][i];
        }
    }
    return x;
}
Vector LeftDiv(Matrix m, Vector v){
    if(m.NCols()!= m.NRows()) throw std::domain_error("Divisor matrix is not square");
    if(v.NElems()!= m.NCols()) throw std::domain_error("Incompatible formats");
    for(int k(0);k<m.NRows();k++){
        int p = k;
        for(int i(k+1);i<m.NRows();i++){
        
            if(fabs(m[i][k]) > fabs(m[p][k])) p = i;
        }
        if(fabs(m[p][k]) < m.GetEpsilon()){ throw std::domain_error("Divisor matrix is singular");
        }
        if(p!= k){
        for(int i(0);i<m.NCols();i++){
            auto temp(m[p][i]);
            m[p][i]=m[k][i];
            m[k][i]=temp;
            
        }
        auto temp(v[k]);
        v[k] = v[p];
        v[p] = temp;
    }
    for(int i(k+1);i<m.NRows();i++){
        double mi = m[i][k]/m[k][k];
        for(int j(k+1);j<m.NRows();j++){
            m[i][j] -= mi* m[k][j];
        }
        v[i]-= mi*v[k];

    }}
    for(int i(v.NElems()-1);i>=0;i--){
        double s=v[i];
        for(int j(i+1);j<v.NElems();j++)
            s-=m[i][j]*v[j];
            
        v[i] = s/m[i][i];
    }
    return v;
}
Matrix &Matrix::operator /=(double s){
    if(fabs(s)<GetEpsilon()) throw std::domain_error("Division by zero");
    for(int i(0);i<NRows();i++)
        for(int j(0);j<NCols();j++)
            mat[i][j]/=s;
    return *this;
}
Matrix operator /(const Matrix &m,double s){
    if(s<m.GetEpsilon()) throw std::domain_error("Division by zero");
    Matrix m1(m);
    m1/=s;
    return m1;
}

Matrix operator /(Matrix m1,Matrix m2){
    if(m2.NCols()!= m2.NRows()) throw std::domain_error("Divisor matrix is not square");
    if(m1.NCols()!= m2.NCols()) throw std::domain_error("Incompatible formats");
    for(int k(0);k<m1.NCols();k++){
        int p = k;
        for(int i(k+1);i<m1.NCols();i++){
        
            if(fabs(m2[k][i]) > fabs(m2[k][p])) p = i;
        }
        if(fabs(m2[k][p]) < m2.GetEpsilon()){ throw std::domain_error("Divisor matrix is singular");
    }if(p!= k){
        for(int i(0);i<m1.NCols();i++){
            auto temp(m1[i][p]);
            m1[i][p]=m1[i][k];
            m1[i][k]=temp;
            
        }
        for(int i(0);i<m2.NCols();i++){
            auto tem1(m2[i][p]);
            m2[i][p]=m2[i][k];
            m2[i][k]=tem1;
        }
    }
    
    for(int i(k+1);i<m1.NCols();i++){
        double m = m1[k][i]/m1[k][k];
    
        for(int j(k+1);j<m1.NCols();j++){
            m1[j][i] = m1[j][i] - m* m1[j][k];
            
            
        }
        for(int j(0);j<m2.NRows();j++){
            m2[j][i] = m2[j][i] - m*m2[j][k];
        }
    }}
    Matrix x(m1.NRows(),m2.NCols());
    for(int k(0);k<m2.NRows();k++){
        for(int i(m1.NCols() - 1); i>=0;i--){
            double s=m2[i][k];
            for(int j(i+1);j<m1.NCols();j++)
                s = s - m1[i][j]*x[j][k];
            
            x[i][k] = s/m1[i][i];
        }
    }
    return x;
}

Matrix &Matrix::operator /=(Matrix m){
if(m.NCols()!= m.NRows()) throw std::domain_error("Divisor matrix is not square");
    if(NCols()!= m.NCols()) throw std::domain_error("Incompatible formats");
    for(int k(0);k<NCols();k++){
        int p = k;
        for(int i(k+1);i<NCols();i++){
        
            if(fabs(m[k][i]) > fabs(m[k][p])) p = i;
        }
        if(fabs(m[k][p]) < m.GetEpsilon()){ throw std::domain_error("Divisor matrix is singular");
    }if(p!= k){
        for(int i(0);i<NCols();i++){
            auto temp(mat[i][p]);
            mat[i][p]=mat[i][k];
            mat[i][k]=temp;
            
        }
        for(int i(0);i<m.NCols();i++){
            auto tem1(m[i][p]);
            m[i][p]=m[i][k];
            m[i][k]=tem1;
        }
    }
    
    for(int i(k+1);i<NCols();i++){
        double mi = mat[k][i]/mat[k][k];
    
        for(int j(k+1);j<NCols();j++){
            mat[j][i] = mat[j][i] - mi* mat[j][k];
            
            
        }
        for(int j(0);j<m.NRows();j++){
            m[j][i] = m[j][i] - mi*m[j][k];
        }
    }}
    for(int k(0);k<m.NCols();k++){
        for(int i(NRows() - 1); i>=0;i--){
            double s=m[i][k];
            for(int j(i+1);j<NRows();j++)
                s = s - mat[i][j]*mat[j][k];
            
            mat[i][k] = s/mat[i][i];
        }
    }
    return *this;
}

double Matrix::Det()const{
    if(NRows()!=NCols()) throw std::domain_error("Matrix is not square");
    double d(1);
    Matrix mat1(*this);
    for(int k(0);k<NRows();k++){
        int p = k;
        for(int i(k+1);i<NRows();i++){
        
            if(fabs(mat1[i][k]) > fabs(mat1[p][k])) p = i;
        }
        if(fabs(mat1[p][k]) < GetEpsilon()){return 0;
        }
        if(p!= k){
        for(int i(0);i<NCols();i++){
            auto temp(mat1[p][i]);
            mat1[p][i]=mat1[k][i];
            mat1[k][i]=temp;
            
        }
        d=-d;
    }
    d = d * mat1[k][k];
    for(int i(k+1);i<NRows();i++){
        double mi = mat1[i][k]/mat1[k][k];
        for(int j(k+1);j<NRows();j++){
            mat1[i][j] -= mi* mat1[k][j];
        }
        

    }}
    return d;
    
}
double Det(Matrix m){
        if(m.NRows()!=m.NCols()) throw std::domain_error("Matrix is not square");
    double d(1);
    for(int k(0);k<m.NRows();k++){
        int p = k;
        for(int i(k+1);i<m.NRows();i++){
        
            if(fabs(m[i][k]) > fabs(m[p][k])) p = i;
        }
        if(fabs(m[p][k]) < m.GetEpsilon()){return 0;
        }
        if(p!= k){
        for(int i(0);i<m.NCols();i++){
            auto temp(m[p][i]);
            m[p][i]=m[k][i];
            m[k][i]=temp;
            
        }
        d=-d;
    }
    d = d * m[k][k];
    for(int i(k+1);i<m.NRows();i++){
        double mi = m[i][k]/m[k][k];
        for(int j(k+1);j<m.NRows();j++){
            m[i][j] -= mi* m[k][j];
        }
        

    }}
    return d;
}
void Matrix::Invert(){
    if(NRows()!= NCols()) throw std::domain_error("Matrix is not square");
    std::vector<int> w;
    for(int k(0);k<NCols();k++){
    int p = k;
        for(int i(k+1);i<NRows();i++){
        
            if(fabs(mat[i][k]) > fabs(mat[p][k])) p = i;
        }
        if(fabs(mat[p][k]) < GetEpsilon()){ throw std::domain_error("Matrix is singular");
        }
        if(p!= k){
            for(int i(0);i<NCols();i++){
            auto temp(mat[p][i]);
            mat[p][i]=mat[k][i];
            mat[k][i]=temp;
            }
        }
        w.push_back(p);
        double mi = mat[k][k];
        mat[k][k] = 1;
        for(int j(0);j<NRows();j++) mat[k][j]/=mi;
        for(int i(0);i<NRows();i++){
            if(i!=k){
                mi=mat[i][k];
                mat[i][k]=0;
                for(int j(0);j<NRows();j++)mat[i][j]-=mi*mat[k][j];
            }
        }
    }
    int p;
    for(int j(NRows()-1);j>=0;j--){
        p=w[j];
        if(p!=j){
            for(int i(0);i<NCols();i++){
            auto temp(mat[i][p]);
            mat[i][p]=mat[i][j];
            mat[i][j]=temp;
            }
        }
    }
    
}
Matrix Inverse(Matrix m){
    if(m.NRows()!= m.NCols()) throw std::domain_error("Matrix is not square");
        std::vector<int> w;
    for(int k(0);k<m.NCols();k++){
    int p = k;
        for(int i(k+1);i<m.NRows();i++){
        
            if(fabs(m[i][k]) > fabs(m[p][k])) p = i;
        }
        if(fabs(m[p][k]) < m.GetEpsilon()){ throw std::domain_error("Matrix is singular");
        }
        if(p!= k){
            for(int i(0);i<m.NCols();i++){
            auto temp(m[p][i]);
            m[p][i]=m[k][i];
            m[k][i]=temp;
            }
        }
        w.push_back(p);
        double mi = m[k][k];
        m[k][k] = 1;
        for(int j(0);j<m.NRows();j++) m[k][j]/=mi;
        for(int i(0);i<m.NRows();i++){
            if(i!=k){
                mi=m[i][k];
                m[i][k]=0;
                for(int j(0);j<m.NRows();j++)m[i][j]-=mi*m[k][j];
            }
        }
    }
    int p;
    for(int j(m.NRows()-1);j>=0;j--){
        p=w[j];
        if(p!=j){
            for(int i(0);i<m.NCols();i++){
            auto temp(m[i][p]);
            m[i][p]=m[i][j];
            m[i][j]=temp;
            }
        }
    }
    return m;
}


int main ()
{
    try
    {
        Matrix M1 {{1,1,1},{2,2,2},{3,3,3}}, M2 {{1,2,3},{1,2,3}};
        Matrix M=M1/M2;
    }
    catch (std::domain_error e){std::cout << e.what() << "\n";}
    try
    {
        Matrix M1 {{1,1},{2,2}}, M2 {{1}};
        Matrix M=M1/M2;
    }
    catch (std::domain_error e){std::cout  << e.what() << "\n";}

    try
    {
        Matrix M1 {{1,2},{2,2},{3,3}}, M2 {{1,2},{1,2}};
        Matrix M=M1/M2;
    }catch (std::domain_error e){std::cout << e.what() << "\n";}
    try
    {
        Matrix M1 {{1,1,1},{2,2,2}}, M2 {{1,2},{1,2}};
        Matrix M=LeftDiv(M1,M2);
    }
    catch (std::domain_error e){std::cout<< e.what() << "\n";}
    try
    {
        Matrix M1 {{1,1},{2,2}}, M2 {{1,2}};
        Matrix M=LeftDiv(M1,M2);
    }
    catch (std::domain_error e){std::cout << e.what() << "\n";}
    try
    {
        Matrix M1 {{1,1,1},{2,2,2},{3,3,3}}, M2 {{1,2},{1,2},{1,2}};
        Matrix M=LeftDiv(M1,M2);
    }
    catch (std::domain_error e){std::cout <<e.what();}
    try{
            Matrix M1 {{1,1,1},{2,2,2}};
            M1=M1/0;
        }
    catch (std::domain_error e) {std::cout<< e.what() << "\n";}
    try{
            Matrix M1 {{1,1,1},{2,2,2}};
            M1/=0;
        }        
    catch (std::domain_error e) {std::cout << e.what() << "\n";}
    Matrix A{{0,3,2},{4,6,1},{3,1,7}};
    Vector v{1,2,4};
    Vector rez=A*v;
    if(v.EqualTo(LeftDiv(A,rez))==true) std::cout << "Rezultat mnozenja matrice A sa vektorom v jednak je razlici matrice A sa tezultatom. Testirana funkcija LeftDiv" << std::endl;
    
    Matrix C{{0,3,2},{4,6,1},{3,1,7}}, jedinicna{{1,0,0},{0,1,0},{0,0,1}};
    std::cout << "Inverzna matrica mateice C: " << std::endl;
    C.Print(3);
    std::cout << "Je: " << std::endl;
    Inverse(C).Print(12);
    jedinicna.Invert();
    Inverse(C);
    std::cout << "Sada kad ponovo invertujemo matricu C dobijemo pocetnu matricu: " << std::endl;
    C.Print(3);
    std::cout << "Determinanta matrice C iznosi: "<< Det(C) << std::endl;
    try
    {
        Matrix M1 {{1,1,1},{2,2,2}}, M2 {{1,2},{1,2}};
        Matrix M=LeftDiv(M1,M2);
    }
    catch (std::domain_error e){std::cout << e.what() << "\n";}
    try
    {
        Matrix M1 {{1,1},{2,2}}, M2 {{1,2}};
        Matrix M=LeftDiv(M1,M2);
    }
    catch (std::domain_error e){std::cout << e.what() << "\n";}
    try
    {
        Matrix M1 {{1,1,1},{2,2,2},{3,3,3}}, M2 {{1,2},{1,2},{1,2}};
        Matrix M=LeftDiv(M1,M2);
    }
    catch (std::domain_error e){std::cout << e.what() <<"\n";}
    Matrix D{{0,3,2},{4,6,1},{3,1,7}};
    Matrix x{{4,1,5},{1,2,1},{8,7,9}};
    Matrix re=D*x;
    if(x.EqualTo(LeftDiv(A,re))== 1) std::cout << "Djeljenje matrica je sa LeftDiv je tacno." << std::endl;
    return 0;
}
