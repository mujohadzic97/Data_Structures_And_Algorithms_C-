//NA 2017/2018: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string> 
using namespace std;

class AbstractInterpolator{
    protected : 
    vector<pair<double,double>> p;
    int Locate (double x) const;
    public: 
    
    AbstractInterpolator(const vector<pair<double, double>> &data){
        auto v(data);
        sort(v.begin(),v.end(),[](const pair<double,double> &x,const pair<double,double> &y){
            
            return x.first<y.first;
        });
    
        for(int i(1);i<v.size();i++){
            if(v[i].first==v[i-1].first) throw domain_error("Invalid data set");
        }
        p=v;
    }
    virtual double operator()(double x) const = 0;
};
int AbstractInterpolator::Locate(double x) const{
    int poc(0),kraj(p.size());
    int sred;
    while(poc<=kraj){
    sred=((poc+kraj)/2);
        if(sred==5){
        if(p[sred-1].first < x){
            return sred;
        }
        else if(p[sred-1].first > x) kraj=sred-1;
        
        else poc=sred+1;    
        }else if(sred==0){
            if( p[sred].first>=x){
                return sred;
            }
            else if( p[sred].first>x) kraj=sred-1;
        
            else poc=sred+1;
        
        }else{
            
        if(p[sred-1].first < x && p[sred].first>=x){
            return sred;
        }
        else if(p[sred-1].first > x && p[sred].first>x) kraj=sred-1;
        
        else poc=sred+1;
    }}
    if(sred>=5) return p.size();
    return 0;
}





class LinearInterpolator : public AbstractInterpolator{

    public: 
    LinearInterpolator(const std::vector<std::pair<double, double>> &data):AbstractInterpolator(data){}
    double operator()(double x) const override{
        int i(Locate(x));
        if(i==p.size()) i--;
        if(i==0)i++;
        return (((p[i].first-x)/(p[i].first-p[i-1].first))*p[i-1].second+((x-p[i-1].first)/(p[i].first-p[i-1].first))*p[i].second);
    }
};







class PolynomialInterpolator : public AbstractInterpolator{
    std::vector<std::vector<double>> v;
    public:
    PolynomialInterpolator(const std::vector<std::pair<double, double>> &data):AbstractInterpolator(data){
        v.resize(p.size());
        for(int i(0);i<data.size();i++){
            v[i].resize(data.size());
            v[i][0] = p[i].second;
        }
        for(int j=1;j<p.size();j++){
            for(int i(p.size());i>=j+1;i--){
                v[i-1][j]=((v[i-1][j-1]-v[i-2][j-1])/(p[i-1].first-p[i - j-1].first));
            }
        }
        
    }
    double operator()(double x) const override{
        double vr(0),pro;int j;
        for(int i(p.size()-1);i>=0;i--){
            pro=1;
            for(j=0;j<i;j++)
                pro*=(x-p[j].first);
            pro*=v[i][j];
            vr+=pro;
        }
        return vr;
    }
    void AddPoint(const std::pair<double, double> &pa){
        for(int i(0);i<p.size();i++)
            if(fabs(p[i].first-pa.first)<std::numeric_limits<double>::epsilon()) throw domain_error ("Invalid point");
        auto point(pa);
        p.push_back(point);
        v.resize(p.size());
        for(int i(0);i<p.size();i++)
            v[i].resize(p.size());
        
        v[p.size()-1][0]=point.second;
        for(int i(1);i<v.size();i++)
            v[p.size()-1][i]=((v[p.size()-1][i-1]-v[p.size()-2][i-1])/(p[p.size()-1].first-p[p.size()-1-i].first));
    }
    std::vector<double> GetCoefficients() const{
        std::vector<double> vv(p.size(),0);
        vv[p.size()-1] = -(p[0].first);
        for(int i(1);i<p.size();i++){
            for(int j=p.size()-i-1;j<p.size()-1;j++)
                vv[j]=vv[j]-p[i].first*vv[j+1];
            vv[p.size()-1]= vv[p.size()-1] - p[i].first; 
        }
        std::vector<double> koefs(p.size(),0);
        for(int i(0);i<p.size();i++){
            double vr = p.size();
            for(int j(p.size()-1);j>0;j--)
                vr = vr*p[i].first+j*vv[j];
            vr = p[i].second/vr;
            
            double br(1);
            for(int k(p.size()-1);k>=0;k--){
                koefs[k]=koefs[k]+br*vr;
                br=vv[k]+p[i].first*br;
            }
            
        }
        return koefs;
    }
};
class SplineInterpolator : public AbstractInterpolator{
    std::vector<double> r;
    std::vector<double> vs;
    std::vector<double> vq;
    public:
    SplineInterpolator(const std::vector<std::pair<double,double>>&data);
    double operator()(double x)const override{
        int i(Locate(x));
        if(i==0) i++;
        if(i==p.size())i--;
        double vr(x-p[i-1].first);
        
        
        
        return vr*(vq[i-1]+vr*(r[i-1]+vs[i-1]*vr))+p[i-1].second;
    }
};
SplineInterpolator::SplineInterpolator(const std::vector<std::pair<double,double>>&data):AbstractInterpolator(data){
    int n = data.size()-1;
    r.resize(n+1);
    vs.resize(n+1);
    vq.resize(n+1);
    std::vector<double> alfa(n+1);
    r[0]=0;
    r[n] = 0;
    for(int i(1);i<n;i++){
        alfa[i] = 2*(p[i+1].first - p[i-1].first);
        r[i]= 3*((p[i+1].second - p[i].second)/(p[i+1].first-p[i].first)-(p[i].second-p[i-1].second)/(p[i].first-p[i-1].first));
    }
    for(int i(1);i< n-1;i++){
        double tmp = (p[i+1].first-p[i].first)/alfa[i];
        alfa[i+1]=alfa[i+1]-tmp*(p[i+1].first-p[i].first);
        r[i+1]=r[i+1]-r[i]*tmp;
    }
    r[n-1]=r[n-1]/alfa[n-1];
    for(int i(n-2);i>0;i--)
            r[i]=(r[i]-(p[i+1].first-p[i].first)*r[i+1])/alfa[i];
        for(int i(0);i<n;i++){
            double mi(p[i+1].first-p[i].first);
            vs[i]=(r[i+1]-r[i])/(3*mi);
            vq[i]=(p[i+1].second-p[i].second)/mi - mi*(r[i+1]+2*r[i])/3;
        }
}
class BarycentricInterpolator : public AbstractInterpolator{
    std::vector<double> vec;
    public:
    BarycentricInterpolator(const std::vector<std::pair<double, double>> &data,int order);
    double operator()(double x) const override{
        double gornji(0),donji(0);
        for(int i(0);i<p.size();i++){
            if(i==p.size()) break;
            if(std::abs(x-p[i].first)<std::numeric_limits<double>::epsilon()){return p[i].second;}
            else{
            gornji=gornji+((vec[i])/(x-p[i].first))*p[i].second;
            donji=donji+((vec[i])/(x-p[i].first));
            }
        }
    
        return gornji/donji;
    }
    std::vector<double> GetWeights() const{
        return vec;
    }

};
BarycentricInterpolator::BarycentricInterpolator(const std::vector<std::pair<double, double>> &data,int order) : AbstractInterpolator(data){
        if(order<0 || order>AbstractInterpolator::p.size()) throw std::domain_error("Invalid order");
        int k,l;
        for(int i(1);i<=AbstractInterpolator::p.size();i++){
        if(i-order<=1) k=1;
        else k=i-order;
        if(AbstractInterpolator::p.size()-order>=i) l=i;
        else l=AbstractInterpolator::p.size()-order;
        double wi(0);
        for(;k<=l;k++){
            double proizvod(1);
            for(int j(k);j<=k+order;j++){
                if(j==i) continue;
                proizvod=proizvod*(1/(AbstractInterpolator::p[i-1].first-AbstractInterpolator::p[j-1].first));
            }
            wi=wi+std::pow(-1,k-1)*proizvod;
 
        }
        vec.push_back(wi);
        }
}


class PiecewisePolynomialInterpolator : public AbstractInterpolator{
  int red;
  public:
  PiecewisePolynomialInterpolator(const std::vector<std::pair<double, double>> &data, int order):AbstractInterpolator(data){
      if(order<1 || order>=p.size()) throw std::domain_error("Invalid order");
  }
  double operator()(double x) const override{
      
  }
};
template <typename FunTip>
 double Limit(FunTip f, double x0, double h = 0, double eps = 1e-8,double nmax = 20){
     if(eps<=0 || nmax < 3 || nmax > 30) throw std::domain_error("Invalid parameters");
     if(fabs(h-0)<std::numeric_limits<double>::epsilon())
        h=0.001*(max(fabs(x0),1.));
    auto yold(numeric_limits<double>::infinity());
    std::vector<double> y(nmax);
    for(int i(0);i<nmax;i++){
        y[i]=f(x0+h);
        int p=2;
        for(int k(i-1);k>=0;k--){
            y[k] = (p*y[k+1]-y[k])/(p-1);
            p*=2;
        }
        if(fabs(y[0]-yold)<eps)
            return y[0];
        yold = y[0];
        h/=2;
    }
    
    throw std::logic_error("Accuracy goal is not achieved");
 }
int main (){
    //testiranje Linearnog interpolatora 
    LinearInterpolator li({{0,8},{1,3},{2,7},{4,5},{7,10}});
    std::cout << li(0.5) <<" "<<li(0.6)<<" "<<li(1.5)<<" "<<li(10)<<endl;
    LinearInterpolator li1({{4,5},{2,7},{0,8},{7,10},{1,3}});
    std::cout << li(0.5) <<" "<<li(0.6)<<" "<<li(1.5)<<" "<<li(10)<<endl;
    try
    {
        //pogresne x koordinate
        LinearInterpolator li3({{3,3},{3,3},{1,1},{6,6},{2,2},{5,5}});
    
    }
    catch (std::domain_error e)
    {
    std::cout << e.what()<<endl;
    }
    //Polinomijalna iterpolacija test
    PolynomialInterpolator pi({{-2,-39},{0,3},{4,25},{6,30}});
    std::cout << pi(2.5) <<" "<<pi(3.5)<<" "<<pi(7.5)<<" "<<pi(-3.5)<<endl;
    //Dodavanje Tacaka i vracanje vektora koeficienata
    PolynomialInterpolator pi4({{-2,-39},{0,3},{4,25},{6,30}});
    pi4.AddPoint({1,6});
    pi4.AddPoint({3,36});
    pi4.AddPoint({-3,-30}); 
    std::vector<double> p1 = pi4.GetCoefficients();
    for(int i = 0; i < p1.size(); i++) std::cout << p1[i] << " ";
    //Unos iste x koordinate
    try
    {
        PolynomialInterpolator pi6({{-2,-39},{-2,3},{4,25},{6,30}});
        
    }
    catch (std::domain_error e)
    {
        std::cout <<e.what() <<endl;
    }
    //Test spline interpolacije
    const double PI1=std::atan(1)*4;
    
    std::vector<std::pair<double,double>> data2;
    
    for(double i=2*PI1; i>=0; i-=PI1/2)
        data2.push_back({i,std::sin(i)});
    
    SplineInterpolator si1(data2);
    for (int i=-PI1/4; i<=2*PI1/2; i++)
        std::cout<<si1(i)<<" "<<std::sin(i)<<std::endl;
    //Poogresno Unesene x koordinate
    try
    {
        SplineInterpolator pi6({{-5,-39},{-2,3},{4,25},{4,30}});
        
    }
    catch (std::domain_error e)
    {
        std::cout<< e.what() << endl;
    }  
        
    //Test Baricentricne interpolacije
    BarycentricInterpolator bi1({{4,25},{0,3},{6,30},{-2,-39}}, 0);
    std::cout << bi1(-2) << endl;
    std::cout << bi1(7.5) << endl;
    std::cout << bi1(3.5) << endl;
    std::cout << bi1(-3.5)<< endl;;

    
    
    //pogresne koordinate kod baricnetricne interpolaccije
    try
    {
        BarycentricInterpolator bi4({{2,-39},{2,3},{2,25},{2,30}},2);
        
    }
    catch (std::domain_error e)
    {
        std::cout <<e.what() << endl;
    }
    

    //Pogresno zadavanje reda interpolacije
    try
    {
        BarycentricInterpolator bi5({{-2,-39},{0,3},{4,25},{6,30}},-1);
        
    }
    catch (std::domain_error e)
    {
        std::cout<< e.what()<< endl;
    }
    //Pogresni parametri u Limesu
    try
    {
        std::cout<<Limit([](double x) {return std::pow(x,1./3);},0,0,0,5)<<std::endl;
        
    }
    catch (std::domain_error e)
    {
        std::cout <<e.what()<< endl;
    }
    //Test limesa
    std::cout<<Limit([](double x) {return (std::exp(x)-1)/x;},0)<<endl;
    
    
    //Test Limesa za negativan korak
std::cout << Limit([](double x) { return atan(1 / x); }, 0, -1);
	return 0;
}
