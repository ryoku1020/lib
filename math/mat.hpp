#pragma  once

namespace MATMAT{
template <typename T, typename = void>
struct IsMint : std::false_type {};
template <typename T>
struct IsMint<T, std::void_t<decltype(T::get_mod())>> : std::true_type {};
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
        if constexpr(MATMAT::IsMint<T>::value){
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

template<class T,int N,int M>
struct FixedMatrix{
    static constexpr int n=N,m=M;
    array<array<T,M>,N>a{};
    FixedMatrix()=default;
    FixedMatrix(initializer_list<initializer_list<T>>il){
        int i=0;
        for(auto&row:il){
            int j=0;
            for(auto&v:row){assert(j<M);a[i][j++]=v;}
            i++;
            assert(i<=N);
        }
    }
    array<T,M>&operator[](int i){assert(0<=i&&i<N);return a[i];}
    const array<T,M>&operator[](int i)const{assert(0<=i&&i<N);return a[i];}
    FixedMatrix&operator+=(const FixedMatrix&mt2){
        rep(i,N)rep(j,M)a[i][j]+=mt2[i][j];
        return *this;
    }
    FixedMatrix&operator-=(const FixedMatrix&mt2){
        rep(i,N)rep(j,M)a[i][j]-=mt2[i][j];
        return *this;
    }
    template<int K>
    FixedMatrix<T,N,K>operator*(const FixedMatrix<T,M,K>&mt2)const{
        FixedMatrix<T,N,K>res;
        if constexpr(MATMAT::IsMint<T>::value){
            auto Mt2=mt2.trans();
            rep(i,N)rep(j,K){
                __int128 tmp{};
                rep(k,M)tmp+=(ll)a[i][k].val*Mt2[j][k].val;
                res[i][j]=tmp%T::get_mod();
            }
        }else{
            rep(i,N)rep(j,K)rep(k,M)res[i][j]+=a[i][k]*mt2[k][j];
        }
        return res;
    }
    FixedMatrix&operator*=(const FixedMatrix&mt2){
        static_assert(N==M,"operator*= requires square");
        return *this=*this*mt2;
    }
    FixedMatrix<T,M,N>trans()const{
        FixedMatrix<T,M,N>res;
        rep(i,N)rep(j,M)res[j][i]=a[i][j];
        return res;
    }
    FixedMatrix operator-()const{
        FixedMatrix res=*this;
        for(auto&row:res.a)for(auto&v:row)v=-v;
        return res;
    }
    FixedMatrix operator+()const{return *this;}
    friend FixedMatrix operator+(FixedMatrix lhs,const FixedMatrix&rhs){return lhs+=rhs;}
    friend FixedMatrix operator-(FixedMatrix lhs,const FixedMatrix&rhs){return lhs-=rhs;}
    static FixedMatrix unit(){
        static_assert(N==M,"unit requires square");
        FixedMatrix res;
        rep(i,N)res[i][i]=1;
        return res;
    }
    FixedMatrix pow(ll k)const{
        static_assert(N==M,"pow requires square");
        FixedMatrix res=unit(),mul=*this;
        while(k){
            if(k&1)res=res*mul;
            mul=mul*mul;
            k>>=1;
        }
        return res;
    }
    T det()const{
        static_assert(N==M,"det requires square");
        auto A=a;
        T res=1;
        rep(i,N){
            if(A[i][i]==0){
                REP(j,i+1,N){
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
            REP(j,i,N)A[i][j]*=IN;
            REP(j,i+1,N){
                T coef=A[j][i];
                REP(k,i,N){
                    A[j][k]-=A[i][k]*coef;
                }
            }
        }
        return res;
    }
    int rank()const{
        auto A=a;
        int hj=0;
        rep(i,N){
            int HI{-1},HJ{-1};
            REP(hj2,hj,M){
                REP(hi,i,N){
                    if(A[hi][hj2]!=0){
                        HI=hi,HJ=hj2;
                        break;
                    }
                }
                if(HI!=-1)break;
            }
            if(HJ==-1){
                return i;
            }
            if(i!=HI)swap(A[i],A[HI]);
            T IN=1/A[i][HJ];
            REP(j,HJ,M)A[i][j]*=IN;
            REP(hi,i+1,N){
                T coef=A[hi][HJ];
                REP(hj2,HJ,M){
                    A[hi][hj2]-=A[i][hj2]*coef;
                }
            }
            hj=HJ+1;
        }
        return N;
    }
    optional<FixedMatrix>inverse()const{
        static_assert(N==M,"inverse requires square");
        auto A=a;
        auto res=unit();
        int hj=0;
        rep(i,N){
            int HI{-1},HJ{-1};
            REP(hj2,hj,N){
                REP(hi,i,N){
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
            REP(j,0,N)A[i][j]*=IN,res[i][j]*=IN;
            REP(hi,i+1,N){
                T coef=A[hi][HJ];
                rep(hj2,N){
                    A[hi][hj2]-=A[i][hj2]*coef;
                    res[hi][hj2]-=res[i][hj2]*coef;
                }
            }
            hj=HJ+1;
        }
        drep(i,N){
            DREP(j,i-1,0){
                rep(k,N)res[j][k]-=res[i][k]*A[j][i];
            }
        }
        return res;
    }
};