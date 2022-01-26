//NA 2017/2018: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <stdexcept>



class ChebyshevApproximation{
        std::vector<double> koef;
        int stepen;
        int m;
        double minimum;
        double maximum;
        public:
    template <typename FunTip>
        ChebyshevApproximation(FunTip f, double xmin, double xmax, int n){
            if(xmin>=xmax || n<1) throw std::domain_error("Bad parameters");
            stepen = n;
            minimum =xmin;
            maximum = xmax;
            m=n;
            double mi =4/(xmax-xmin);
            std::vector<double> c(m+1);
            c[m] = 0;
            c[m-1]=mi*m*c[m];
            c[m-2] = mi*(m-1)*c[m-1];
            for(int k(m-3);k>=0;k--)
                c[k] = c[k+2] + mi*(k+1)*c[k+1];
            koef = c;
        }
        void set_m(int m){
            if(m<=1 || m>stepen) throw std::domain_error("Bad order");
            this->m = m;
        }
        void trunc(double eps){
            bool valja = false;
            for(int i(0);i<koef.size();i++){
                if(koef[i]>eps){
                    valja = true;
                    break;
                }
            }
            if(eps<0 || valja == false) throw std::domain_error("Bad tolerance");
        }
        double operator()(double x) const{
            if(x<=minimum || x>=maximum) throw std::domain_error("Bad argument");
        }
        double derivative(double x) const{
            if(x<=minimum || x>=maximum) throw std::domain_error("Bad argument");
        }
        ChebyshevApproximation derivative() const;
        ChebyshevApproximation antiderivative() const;
        double integrate(double a, double b) const{
            if(a<=minimum || a>=maximum ||b<=minimum || b>=maximum ) throw std::domain_error("Bad interval");
        }
        double integrate() const;
};
template <typename FunTip>
 std::pair<double, bool> RombergIntegration(FunTip f, double a, double b, double eps = 1e-8, int nmax = 1000000, int nmin = 50){
     if(nmin>=nmax || nmin<0 || nmax<0 || eps<0) throw std::domain_error("Bad parameter");
     int n=2;
     double h=(b-a)/n;
     double s = (f(a)+f(b))/2;
     double Iold = s;
     std::vector<double> I(nmax);
     for(int i(0);i<(nmax);i++){
         for(int j(1);j<=n/2;j++){
             s+=f(a+(2*j-1)*h);
         }
         I[i] = h*s;
         double p= 4;
         for(int k(i-1);k>=0;k--){
             I[k] = (p*I[k+1]-I[k])/(p-1);
             p=4*p;
         }
         if(std::fabs(I[0]-Iold)<=eps)
            return std::make_pair(I[0],true);
        Iold = I[0];
        h=h/2;
        n=n*2;
        if(n>=nmax) break;
     }
 return std::make_pair(I[0],false);    
}
template <typename FunTip>
 std::pair<double, bool> TanhSinhIntegration(FunTip f, double a, double b, double eps = 1e-8, int nmax = 1000000, int nmin = 20, double range = 3.5){
     if(nmin>=nmax || nmin<0 || nmax<0 || eps<0 || range<=0) throw std::domain_error("Bad parameter");
     double PI = 4*atan(1);
     auto smjena = [PI,f,a,b](double x){
         return ((b-a)*PI*std::cosh(x)*f((((b+a)/2) + ((b-a)*std::tanh(PI*std::sinh(x)/2))/2))/(4*std::cosh(PI/2*std::sinh(x))*std::cosh(PI/2*std::sinh(x))));
     };
     a=-range;
     b=range;
     int N=2;
     double h =(b-a)/2;
     double s = 0;
     double temp = (smjena(a)+smjena(b))/2;
     if(std::isfinite(temp)) s= temp;
     double Iold=s;
     double I=Iold;
     //Nakon smjene smijemo iskoristiti simpsonovo pravilo za racunanje integrala
     while(N<nmax){
         for(int i(1);i<=N;i++){
             temp = smjena(a + (2*i-1) * h);
             if(std::isfinite(temp)) s+= temp;
         }
         I=h*s;
         if(N>=nmin && fabs(I-Iold)<=eps) return std::make_pair(I,true);
     
         Iold = I;
         h=h/2;
         N=N*2;
     }
    return std::make_pair(I,false);     
}

template<typename FunTip>
std::pair<double,bool> AdaptivAux(FunTip f,double a,double b,double eps,double f1,double f2,double f3, int R){
    double c=(a+b)/2;
    double I1 = (b-a)*(f1+4*f3+f2)/6;
    double f4 = f((a+c)/2);
    double f5 = f((c+b)/2);
    double I2 = (b-a)*(f1+4*f4+2*f3+4*f5+f2)/12;
    if(!std::isfinite(I1)) I1=0;
    if(!std::isfinite(I2)) I2=0;
    if(R<=0) return std::make_pair(I2,0);
    if(fabs(I1-I2)<=eps && !(I1==0 && I2 == 0)) return std::make_pair(I2,1);
    
    auto tmp1 = AdaptivAux(f,a,c,eps,f1,f3,f4,R-1);
    auto tmp2 = AdaptivAux(f,c,b,eps,f3,f2,f5,R-1);
    return std::make_pair(tmp1.first + tmp2.first,tmp2.second);
    
    
    
    
    
}
template <typename FunTip>
 std::pair<double, bool> AdaptiveIntegration(FunTip f, double a, double b, double eps = 1e-10, int maxdepth = 30, int nmin = 1){
    if(nmin<0 || maxdepth<0 || eps<0) throw std::domain_error("Bad parameter");
    double s=0;
    bool valjal = true;
    double h=(b-a)/nmin;
    for(int i(0);i<nmin;i++){
        auto par(AdaptivAux(f,a,a+h,eps,f(a),f(a+h),f((a+h)/2),maxdepth));
        s = s + par.first;
        if(!par.second) valjal = false;
        a = a+h;
    }
     return std::make_pair(s,valjal);
 }

int main ()
{
    //Robergova integracija na funkciji sin(x)
    const double PIPI1 = 4 * std::atan(1);
    auto sinf1 = [](double x) { return std::sin(x); };
    auto rig = RombergIntegration(sinf1, 0, PIPI1);
    std::cout << rig.first << " " << rig.second;
    //Test za TanhSinhIntegration na funkciju sin(x)

    auto sinf = [](double x) { return std::sin(x); };
    auto rez = TanhSinhIntegration(sinf, 0, PIPI1);
    std::cout << rez.first << " " << rez.second;
    //Test za adaptivnu integraciju gdje imamo nesvojstveni integral
    auto aig =  AdaptiveIntegration([](double x) { return 1 / std::sqrt(x); }, 0, 1, 1e-6, 40);
    std::cout << aig.first << " " << aig.second<<std::endl;
    try
    {
        //Test na pogrešene parametre kod ThanSinhIntegracije
        auto rez = TanhSinhIntegration([](double x) {
            return log(fabs(x - 1));
        }, 0, 1, 1e-10, -100);
    }
    catch (std::domain_error e)
    {
        std::cout  << e.what() << std::endl;
    } 
	return 0;
}
