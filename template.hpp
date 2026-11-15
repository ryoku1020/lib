//https://github.com/ryoku1020/lib
#pragma once
#ifdef TEMPLATE
#else
#define TEMPLATE
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
namespace ryoku{}
using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using i128=__int128;
using u128=unsigned __int128;
template<class T>using vc=vector<T>;
template<class T>using vvc=vc<vc<T>>;
template<class T>using vvvc=vvc<vc<T>>;
template<class T>using smpq=priority_queue<T,vector<T>,greater<T>>;
template<class T>using bipq=priority_queue<T>;
using vi=vc<int>;
using vvi=vvc<int>;
using vl=vc<ll>;
using vvl=vvc<ll>;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define REP(i,j,n) for(ll i=(j);i<(ll)(n);i++)
#define DREP(i,n,m) for(ll i=ll(n);i>=ll(m);i--)
#define drep(i,n) for(ll i=(ll(n)-1);i>=0;i--)
#define rall(x) x.rbegin(),x.rend()
#define mp(...) make_pair(__VA_ARGS__)
#define pb push_back
#define fi first
#define se second
#define is insert
#define bg begin()
#define ed end()
#define all(x) x.begin(),x.end()
#define ref(x,v) for(auto&x:v)
istream& operator>>(istream&is,i128&x){
    string s;if(!(is>>s))return is;
    u128 y=0;
    int i=0,neg=0;
    if(s[0]=='-'||s[0]=='+')neg=s[0]=='-',i=1;
    for(;i<(int)s.size();i++)y=y*10+s[i]-'0';
    x=neg?(y?-(i128)(y-1)-1:0):(i128)y;
    return is;
}
ostream& operator<<(ostream&os,i128 x){
    if(x==0)return os<<0;
    if(x<0)os<<"-";
    u128 y=x<0?-(u128)x:(u128)x;
    string s;
    while(y)s.pb('0'+y%10),y/=10;
    reverse(all(s));
    return os<<s;
}

void scan(int&a){cin>>a;}
void scan(ll&a){cin>>a;}
void scan(i128&a){cin>>a;}
void scan(string&a){cin>>a;}
void scan(char&a){cin>>a;}
void scan(uint&a){cin>>a;}
void scan(ull&a){cin>>a;}
void scan(bool&a){cin>>a;}
void scan(ld&a){ cin>>a;}
template<class A,class B>
void scan(pair<A,B>&p){
    scan(p.first);
    scan(p.second);
}
template<class C>void scan(C&a){for(auto&x:a)scan(x);}
void read(){}
template<class Head,class... Tail>void read(Head&head,Tail&... tail){scan(head); read(tail...);}
#define INT(...) int __VA_ARGS__; read(__VA_ARGS__);
#define LL(...) ll __VA_ARGS__; read(__VA_ARGS__);
#define ULL(...) ull __VA_ARGS__; read(__VA_ARGS__);
#define STR(...) string __VA_ARGS__; read(__VA_ARGS__);
#define VC(type,name,...) vector<type> name(__VA_ARGS__); read(name);
#define VVC(type,name,size,...) vector<vector<type>> name(size,vector<type>(__VA_ARGS__)); read(name);
template<class T>void print(T a){cout<<a;}
template<class T>void print(vector<T>a){for(int i=0;i<(int)a.size();i++){if(i)cout<<" ";print(a[i]);}}
void PRT(){cout<<endl; return;}
template<class T>void PRT(T a){print(a); cout<<endl; return;}
template<class Head,class... Tail>void PRT(Head head,Tail... tail){print(head); cout<<" "; PRT(tail...); return;}
template<class T,class F>int chmin(T&x,F y){return x>y?(x=y,1):0;}
template<class T,class F>int chmax(T&x,F y){return x<y?(x=y,1):0;}
template<typename T>T floor(T a,T b){return a/b-(a%b&&((a<0)!=(b<0)));}
template<typename T>T ceil(T a,T b){return a/b+(a%b&&((a<0)==(b<0)));}
template<typename T>T bmod(T x,T y){return x-y*floor(x,y);}
template<typename T>
pair<T,T>divmod(T x,T y){
    T q=floor(x,y);
    return{q,x-q*y};
}
void YesNo(bool b){cout<<(b?"Yes":"No")<<endl;}void YESNO(bool b){cout<<(b?"YES":"NO")<<endl;}
void AliceBob(bool b){cout<<(b?"Alice":"Bob")<<endl;}
void Yes(){cout<<"Yes"<<endl;}void YES(){cout<<"YES"<<endl;}
void No(){cout<<"No"<<endl;}void NO(){cout<<"NO"<<endl;}
#ifdef LOCAL
#define LOJ(a, b) (a)
#else
#define LOJ(a, b) (b)
#endif
vc<int>stovi(const string&s,const string&S){
    vc<int>v(s.size());
    rep(i,s.size()){
        auto t=S.find(s[i]);
        assert(t!=string::npos);
        v[i]=t;
    }
    return v;
}
template<class T=ll>
T isqrt(T x){
    T F=sqrtl(x);
    if(F*F>x)F--;
    return F;
}
template<class C>C sorted(C a){
    sort(all(a));
    return a;
}
template<class C>C reved(C a){
    reverse(all(a));
    return a;
}
template<class T>
pair<vc<int>,vc<T>>compress(const vc<T>&a){
    vc<T>xs=a;
    sort(all(xs));
    xs.erase(unique(all(xs)),xs.end());
    vc<int>b(a.size());
    rep(i,a.size())b[i]=lb(xs,a[i])-xs.begin();
    return{b,xs};
}
template<class T>
auto make_vec(int n,T x){
    return vc<T>(n,x);
}
template<class... Args>
auto make_vec(int n,Args...args){
    return vc(n,make_vec(args...));
}
template<class T>T tri(T x){return x*(x-1)/2;}
//[l,r)
template<class T>T tri(T l,T r){return (r-l)*(l+r-1)/2;}
//n を先頭に持ってくる
template<class C>
C rot(C v,int n){
    rotate(v.begin(),v.begin()+n,v.end());
    return v;
}
template<class C>
C concat(C a,const C&b){
    a.insert(a.end(),b.begin(),b.end());
    return a;
}
template<class Container>
auto rle(const Container&cv){
    using T=typename Container::value_type;
    vc<pair<T,int>>res;
    for(const auto&x:cv){
        if(res.empty()||res.back().fi!=x)res.pb({x,1});
        else res.back().se++;
    }
    return res;
}
template<class T>
vc<T>iota(int n){
    vc<T>v(n);rep(i,n)v[i]=i;
    return v;
}
template<class T,int minfirst,class C>
vc<int>argsort(const C&a){
    auto idx=iota<int>(a.size());
    sort(all(idx),[&](int i,int j){
        return (minfirst?make_pair(a[i],i)<make_pair(a[j],j):make_pair(a[i],i)>make_pair(a[j],j));
    });
    return idx;
}
template<class C>
auto trans(const C&a){
    using T=typename C::value_type::value_type;
    assert(a.size()&&a[0].size());
    rep(i,a.size())assert(a[i].size()==a[0].size());
    vvc<T>b(a[0].size(),vc<T>(a.size()));
    rep(i,a.size())rep(j,a[0].size())b[j][i]=a[i][j];
    return b;
}
vc<string>trans(const vc<string>&a){
    assert(a.size()&&a[0].size());
    rep(i,a.size())assert(a[i].size()==a[0].size());
    vc<string>b(a[0].size(),string(a.size(),0));
    rep(i,a.size())rep(j,a[0].size())b[j][i]=a[i][j];
    return b;
}
template<class C>ll sz(const C&a){return (int)a.size();}
template<class C,class T>auto lb(const C&a,const T&x){return lower_bound(all(a),x);}
template<class C,class T>auto ub(const C&a,const T&x){return upper_bound(all(a),x);}
template<class T>int popcount(T n){return __builtin_popcountll(n);}
template<class T=void,class L=ll,class C>L sum(const C&a){return accumulate(all(a),L(0));}
template<class T>
struct subset_view{
    T s;
    struct iterator{
        T s,x;
        bool done;
        T operator*()const{return x;}
        iterator&operator++(){
            if(x==0)done=true;
            else x=(x-1)&s;
            return*this;
        }
        bool operator!=(const iterator&r)const{return done!=r.done;}
    };
    iterator begin()const{return{s,s,false};}
    iterator end()const{return{s,0,true};}
};
template<class T>
subset_view<T>subset(T s){return{s};}
template<class C>auto max(const C&a){return *max_element(all(a));}
template<class C>auto min(const C&a){return *min_element(all(a));}
template<class C>ll argmin(const C&a){return min_element(all(a))-a.begin();}
template<class C>ll argmax(const C&a){return max_element(all(a))-a.begin();}
template<class L=ll,class C>
vc<L>presum(const C&a){
    vc<L>ret(a.size()+1);
    rep(i,a.size())ret[i+1]=ret[i]+a[i];
    return ret;
}
template<class T,class F>
vc<T>&operator+=(vc<T>&a,F b){
    for(auto&v:a)v+=b;
    return a;
}
template<class T,class F>
vc<T>&operator-=(vc<T>&a,F b){
    for(auto&v:a)v-=b;
    return a;
}
template<class T,class F>
vc<T>&operator*=(vc<T>&a,F b){
    for(auto&v:a)v*=b;
    return a;
}
template<class T,size_t N,class F>
array<T,N>&operator+=(array<T,N>&a,F b){
    for(auto&v:a)v+=b;
    return a;
}
template<class T,size_t N,class F>
array<T,N>&operator-=(array<T,N>&a,F b){
    for(auto&v:a)v-=b;
    return a;
}
template<class T,size_t N,class F>
array<T,N>&operator*=(array<T,N>&a,F b){
    for(auto&v:a)v*=b;
    return a;
}
template<class T=ll>
constexpr T pow(T a,T b){
    T res=1;
    while(b){
        if(b&1)res*=a;
        a*=a;
        b/=2;
    }
    return res;
}
template<class T>
struct temporary{
    T& x;T old;
    template<class U>temporary(T&x,U&&y):x(x),old(x){
        x=std::forward<U>(y);
    }
    ~temporary(){x=std::move(old);}
    temporary(const temporary&)=delete;
};
template<class T,class U>
temporary(T&,U&&)->temporary<T>;
#define CAT_(a,b) a##b
#define CAT(a,b) CAT_(a,b)
#define WITH(x,y) temporary CAT(_tmp_,__COUNTER__)(x,y)
constexpr ll ten(ll a){return pow<ll>(10,a);}
template<typename T>constexpr T inf=numeric_limits<T>::max()/2-1;
template<>constexpr pll inf<pll> ={inf<ll>,inf<ll>};
template<class T>constexpr T neg_inf=-inf<T>;
template<>constexpr pll neg_inf<pll> ={-inf<ll>,-inf<ll>};
template<class C>C UNIQUE(C&a){
    sort(all(a));
    a.erase(unique(all(a)),a.end());
    return a;
}

template<class T>
int tbit(T x){
    using U=make_unsigned_t<T>;
    U y=(U)x;
    if(!y)return -1;
    if(sizeof(U)>sizeof(ull)&&(u128)y>>64)return 127-__builtin_clzll((ull)((u128)y>>64));
    return 63-__builtin_clzll((ull)y);
}
template<class T>
int lbit(T x){
    using U=make_unsigned_t<T>;
    U y=(U)x;
    if(!y)return -1;
    if((ull)y)return __builtin_ctzll((ull)y);
    return 64+__builtin_ctzll((ull)((u128)y>>64));
}
template<class T>
int tbit(T x,int p){
    using U=make_unsigned_t<T>;
    constexpr int W=numeric_limits<U>::digits;
    U y=(U)x;
    if(p<0)return -1;
    if(p>=W-1)return tbit(y);
    return tbit(y&((U(1)<<(p+1))-1));
}
template<class T>
int lbit(T x,int p){
    using U=make_unsigned_t<T>;
    constexpr int W=numeric_limits<U>::digits;
    U y=(U)x;
    if(p<0)return lbit(y);
    if(p>=W)return -1;
    return lbit(y&(~U(0)<<p));
}
enum debug_color{
    BLACK=30,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE,
    BRIGHT_BLACK=90,BRIGHT_RED,BRIGHT_GREEN,BRIGHT_YELLOW,BRIGHT_BLUE,BRIGHT_MAGENTA,BRIGHT_CYAN,BRIGHT_WHITE
};
#ifdef LOCAL
static int dbging=1;
#include "debug/local.hpp"
#define mark(col) do{if(dbging!=0)::debug::internal::mark(col);}while(0)
#else
template<debug_color col,class... Ts>
void dbg(const Ts&...xs){}
#define dbg(...) ((void)0)
#define mark(...) ((void)0)
#endif
struct template_setup{
    template_setup(){
        #if defined(LOCAL)&&!defined(INTERACTIVE)
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        #endif
        cin.tie(0)->sync_with_stdio(0);
        #ifdef LOCAL
        cout<<fixed<<setprecision(6);
        #else
        cout<<fixed<<setprecision(20);
        #endif
    }
};
static struct template_setup template_setup;
#endif
