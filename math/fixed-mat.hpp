
template<class T,int N,int M>
struct fixed_matrix{
    static constexpr int n=N,m=M;
    array<array<T,M>,N>a{};
    fixed_matrix()=default;
    fixed_matrix(initializer_list<initializer_list<T>>il){
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
    fixed_matrix&operator+=(const fixed_matrix&mt2){
        rep(i,N)rep(j,M)a[i][j]+=mt2[i][j];
        return *this;
    }
    fixed_matrix&operator-=(const fixed_matrix&mt2){
        rep(i,N)rep(j,M)a[i][j]-=mt2[i][j];
        return *this;
    }
    template<int K>
    fixed_matrix<T,N,K>operator*(const fixed_matrix<T,M,K>&mt2)const{
        fixed_matrix<T,N,K>res;
        if constexpr(MATMAT::is_mint<T>::value){
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
    fixed_matrix&operator*=(const fixed_matrix<T,M,M>&mt2){
        return *this=*this*mt2;
    }
    fixed_matrix<T,M,N>trans()const{
        fixed_matrix<T,M,N>res;
        rep(i,N)rep(j,M)res[j][i]=a[i][j];
        return res;
    }
    fixed_matrix operator-()const{
        fixed_matrix res=*this;
        for(auto&row:res.a)for(auto&v:row)v=-v;
        return res;
    }
    fixed_matrix operator+()const{return *this;}
    friend fixed_matrix operator+(fixed_matrix lhs,const fixed_matrix&rhs){return lhs+=rhs;}
    friend fixed_matrix operator-(fixed_matrix lhs,const fixed_matrix&rhs){return lhs-=rhs;}
    static fixed_matrix unit(){
        static_assert(N==M,"unit requires square");
        fixed_matrix res;
        rep(i,N)res[i][i]=1;
        return res;
    }
    fixed_matrix pow(ll k)const{
        static_assert(N==M,"pow requires square");
        fixed_matrix res=unit(),mul=*this;
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
    optional<fixed_matrix>inverse()const{
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
