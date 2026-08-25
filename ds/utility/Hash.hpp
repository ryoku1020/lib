#pragma once
template<typename T,size_t N>
struct hash_type{
    array<T,N>v;
    hash_type(long long x=0){for(size_t i=0;i<N;++i)v[i]=T(x);}
    hash_type(T x){for(size_t i=0;i<N;++i)v[i]=x;}
    T& operator[](size_t i){assert(i<N);return v[i];}
    const T& operator[](size_t i)const{assert(i<N);return v[i];}
    hash_type operator-()const{hash_type res;for(size_t i=0;i<N;++i)res.v[i]=-v[i];return res;}
    hash_type& operator+=(const hash_type&b){for(size_t i=0;i<N;++i)v[i]+=b.v[i];return*this;}
    hash_type& operator-=(const hash_type&b){for(size_t i=0;i<N;++i)v[i]-=b.v[i];return*this;}
    hash_type& operator*=(const hash_type&b){for(size_t i=0;i<N;++i)v[i]*=b.v[i];return*this;}
    hash_type& operator/=(const hash_type&b){for(size_t i=0;i<N;++i)v[i]/=b.v[i];return*this;}
    hash_type& operator+=(const T&b){for(size_t i=0;i<N;++i)v[i]+=b;return*this;}
    hash_type& operator-=(const T&b){for(size_t i=0;i<N;++i)v[i]-=b;return*this;}
    hash_type& operator*=(const T&b){for(size_t i=0;i<N;++i)v[i]*=b;return*this;}
    hash_type& operator/=(const T&b){for(size_t i=0;i<N;++i)v[i]/=b;return*this;}
    hash_type operator+(const hash_type&b)const{return hash_type(*this)+=b;}
    hash_type operator-(const hash_type&b)const{return hash_type(*this)-=b;}
    hash_type operator*(const hash_type&b)const{return hash_type(*this)*=b;}
    hash_type operator/(const hash_type&b)const{return hash_type(*this)/=b;}
    hash_type operator+(const T&b)const{return hash_type(*this)+=b;}
    hash_type operator-(const T&b)const{return hash_type(*this)-=b;}
    hash_type operator*(const T&b)const{return hash_type(*this)*=b;}
    hash_type operator/(const T&b)const{return hash_type(*this)/=b;}
    friend hash_type operator+(const T&a,const hash_type&b){return hash_type(a)+=b;}
    friend hash_type operator-(const T&a,const hash_type&b){return hash_type(a)-=b;}
    friend hash_type operator*(const T&a,const hash_type&b){return hash_type(a)*=b;}
    friend hash_type operator/(const T&a,const hash_type&b){return hash_type(a)/=b;}
    bool operator==(const hash_type&b)const{return v==b.v;}
    bool operator!=(const hash_type&b)const{return v!=b.v;}
    bool operator<(const hash_type&b)const{return v<b.v;}
    bool operator<=(const hash_type&b)const{return v<=b.v;}
    bool operator>(const hash_type&b)const{return v>b.v;}
    bool operator>=(const hash_type&b)const{return v>=b.v;}
    static const hash_type& get_base(){
        static const hash_type b=[](){
            mt19937_64 en(chrono::steady_clock::now().time_since_epoch().count());
            uniform_int_distribution<long long>d(2,2e10);
            auto isp=[](long long n){
                if(n<2)return false;
                for(long long i=2;i*i<=n;++i)if(n%i==0)return false;
                return true;
            };
            hash_type res;
            for(size_t i=0;i<N;++i){
                long long p;
                do{p=d(en);}while(!isp(p));
                res.v[i]=T(p);
            }
            return res;
        }();
        return b;
    }
    static hash_type get_rand(){
        static mt19937_64 en(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<long long>d(0,llabs(numeric_limits<long long>::max()));
        hash_type res;
        for(size_t i=0;i<N;++i)res.v[i]=T(d(en));
        return res;
    }
};
