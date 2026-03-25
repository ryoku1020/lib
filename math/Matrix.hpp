#pragma  once
#include"../template.hpp"
namespace MATMAT{
template <typename T, typename = void>
struct is_mint : std::false_type {};
template <typename T>
struct is_mint<T, std::void_t<decltype(T::get_mod())>> : std::true_type {};
};
template<class T>
struct Matrix{
    int n,m;
    vvc<T>a;
    Matrix()=default;
    Matrix(vvc<T>b):a(b),n(b.size()){
        if(b.size())m=b[0].size();
    }
    Matrix(int n,int m):n(n),m(m),a(n,vc<T>(m)){}
    vc<T>&operator[](int i){
        assert(0<=i&&i<n);
        return a[i];
    }
    const vc<T>&operator[](int i)const{
        assert(0<=i&&i<n);
        return a[i];
    }
    Matrix&operator+=(const Matrix&mt2){
        assert(mt2.n==n&&mt2.m==m);
        rep(i,n)rep(j,m)a[i][j]+=mt2[i][j];
        return *this;
    }
    Matrix&operator-=(const Matrix&mt2){
        assert(mt2.n==n&&mt2.m==m);
        rep(i,n)rep(j,m)a[i][j]-=mt2[i][j];
        return *this;
    }
    Matrix&operator*=(const Matrix&mt2){
        assert(m==mt2.n);
        vc<vc<T>>res(n,vc<T>(mt2.m));
        auto Mt2=mt2.trans();
        if constexpr(MATMAT::is_mint<T>::value){
            rep(i,n)rep(j,mt2.m){
                __int128 tmp{};
                rep(k,m){
                    tmp+=(ll)a[i][k].val*Mt2[j][k].val; 
                }
                res[i][j]=tmp%T::get_mod();
            }
        }else{
            rep(i,n)rep(j,mt2.m)rep(k,m){
                res[i][j]+=a[i][k]*Mt2[j][k];
            }
        }
        a=move(res);
        n=a.size();
        m=a[0].size();
        return *this;
    }
    Matrix trans()const{
        Matrix res(m,n);
        rep(i,n)rep(j,m)res[j][i]=a[i][j];
        return res;
    }
    Matrix operator-() const{
        vvc<T>b=a;
        for(auto&x:b)for(auto&e:x)e=-e;
        return Matrix(b);
    }
    Matrix operator+() const {
        return *this;
    }
    friend Matrix operator+(Matrix lhs, const Matrix& rhs){
        return lhs+=rhs;
    }
    friend Matrix operator-(Matrix lhs, const Matrix& rhs){
        return lhs-=rhs;
    }
    friend Matrix operator*(Matrix lhs, const Matrix& rhs){
        return lhs*=rhs;
    }
    static Matrix unit(int n){
        Matrix mt(n,n);
        rep(i,n)mt[i][i]=1;
        return mt;
    }
    Matrix pow(ll n){
        Matrix res=unit(this->n);
        Matrix mul=a;
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }
    T det()const{
        assert(n==m);
        auto A=a;
        T res=1;
        rep(i,n){
            if(A[i][i]==0){
                REP(j,i+1,n){
                    if(A[j][i]!=0){
                        swap(A[i],A[j]);
                        res=-res;
                        break;
                    }
                }
            }
            if(A[i][i]==0)return 0;
            res*=A[i][i];
            T IN=1/A[i][i];
            REP(j,i,n)A[i][j]*=IN;
            REP(j,i+1,n){
                T coef=A[j][i];
                REP(k,i,n){
                    A[j][k]-=A[i][k]*coef;
                }
            }
        } 
        return res;
    }
    int rank()const{
        Matrix a;
        if(n>m)a=Matrix(*this).trans();
        else a=Matrix(*this);
        int N=a.n,M=a.m;
        int hj=0;
        rep(i,N){
            int HI{-1},HJ{-1}; 
            REP(hj2,hj,M){
                REP(hi,i,N){
                    if(a[hi][hj2]!=0){
                        HI=hi,HJ=hj2;
                        break;    
                    }
                }
                if(HI!=-1)break;
            }
            if(HJ==-1){
                return i;
            }
            if(i!=HI)swap(a[i],a[HI]);
            T IN=1/a[i][HJ];
            REP(j,HJ,M)a[i][j]*=IN;
            REP(hi,i+1,N){
                T coef=a[hi][HJ];
                REP(hj2,HJ,M){
                    a[hi][hj2]-=a[i][hj2]*coef; 
                }
            }
            hj=HJ+1;
        }
        return N;
    }
    optional<Matrix> inverse()const{
        assert(n==m);
        auto A=a;
        auto res=unit(n);
        int hj=0;
        rep(i,n){
            int HI{-1},HJ{-1}; 
            REP(hj2,hj,n){
                REP(hi,i,n){
                    if(A[hi][hj2]!=0){
                        HI=hi,HJ=hj2;
                        break;    
                    }
                }
                if(HI!=-1)break;
            }
            if(HJ==-1){
                return nullopt;
            }
            if(i!=HI)swap(A[i],A[HI]),swap(res[i],res[HI]);
            T IN=1/A[i][HJ];
            REP(j,0,n)A[i][j]*=IN,res[i][j]*=IN;
            REP(hi,i+1,n){
                T coef=A[hi][HJ];
                rep(hj2,n){
                    A[hi][hj2]-=A[i][hj2]*coef; 
                    res[hi][hj2]-=res[i][hj2]*coef;
                }
            }
            hj=HJ+1;
        }
        drep(i,n){
            DREP(j,i-1,0){
                rep(k,n)res[j][k]-=res[i][k]*A[j][i];
            }
        }
        return res;
    }
}; 