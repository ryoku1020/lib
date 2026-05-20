#pragma once
template<typename T,size_t N>
struct Hash{
    array<T,N>v;
    Hash(long long x=0){for(size_t i=0;i<N;++i)v[i]=T(x);}
    Hash(T x){for(size_t i=0;i<N;++i)v[i]=x;}
    T& operator[](size_t i){assert(i<N);return v[i];}
    const T& operator[](size_t i)const{assert(i<N);return v[i];}
    Hash operator-()const{Hash res;for(size_t i=0;i<N;++i)res.v[i]=-v[i];return res;}
    Hash& operator+=(const Hash&b){for(size_t i=0;i<N;++i)v[i]+=b.v[i];return*this;}
    Hash& operator-=(const Hash&b){for(size_t i=0;i<N;++i)v[i]-=b.v[i];return*this;}
    Hash& operator*=(const Hash&b){for(size_t i=0;i<N;++i)v[i]*=b.v[i];return*this;}
    Hash& operator/=(const Hash&b){for(size_t i=0;i<N;++i)v[i]/=b.v[i];return*this;}
    Hash& operator+=(const T&b){for(size_t i=0;i<N;++i)v[i]+=b;return*this;}
    Hash& operator-=(const T&b){for(size_t i=0;i<N;++i)v[i]-=b;return*this;}
    Hash& operator*=(const T&b){for(size_t i=0;i<N;++i)v[i]*=b;return*this;}
    Hash& operator/=(const T&b){for(size_t i=0;i<N;++i)v[i]/=b;return*this;}
    Hash operator+(const Hash&b)const{return Hash(*this)+=b;}
    Hash operator-(const Hash&b)const{return Hash(*this)-=b;}
    Hash operator*(const Hash&b)const{return Hash(*this)*=b;}
    Hash operator/(const Hash&b)const{return Hash(*this)/=b;}
    Hash operator+(const T&b)const{return Hash(*this)+=b;}
    Hash operator-(const T&b)const{return Hash(*this)-=b;}
    Hash operator*(const T&b)const{return Hash(*this)*=b;}
    Hash operator/(const T&b)const{return Hash(*this)/=b;}
    friend Hash operator+(const T&a,const Hash&b){return Hash(a)+=b;}
    friend Hash operator-(const T&a,const Hash&b){return Hash(a)-=b;}
    friend Hash operator*(const T&a,const Hash&b){return Hash(a)*=b;}
    friend Hash operator/(const T&a,const Hash&b){return Hash(a)/=b;}
    bool operator==(const Hash&b)const{return v==b.v;}
    bool operator!=(const Hash&b)const{return v!=b.v;}
    bool operator<(const Hash&b)const{return v<b.v;}
    bool operator<=(const Hash&b)const{return v<=b.v;}
    bool operator>(const Hash&b)const{return v>b.v;}
    bool operator>=(const Hash&b)const{return v>=b.v;}
    static const Hash& get_base(){
        static const Hash b=[](){
            mt19937_64 en(chrono::steady_clock::now().time_since_epoch().count());
            uniform_int_distribution<long long>d(2,2e10);
            auto isp=[](long long n){
                if(n<2)return false;
                for(long long i=2;i*i<=n;++i)if(n%i==0)return false;
                return true;
            };
            Hash res;
            for(size_t i=0;i<N;++i){
                long long p;
                do{p=d(en);}while(!isp(p));
                res.v[i]=T(p);
            }
            return res;
        }();
        return b;
    }
    static Hash get_rand(){
        static mt19937_64 en(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<long long>d(0,llabs(numeric_limits<long long>::max()));
        Hash res;
        for(size_t i=0;i<N;++i)res.v[i]=T(d(en));
        return res;
    }
};
