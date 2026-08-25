#ifdef TEMPLATE
#else
#define TEMPLATE
# pragma GCC optimize("O3")
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <cassert>
#include <functional>
#include <iterator>
#include <utility>
#include <complex>
#include <bitset>
#include <chrono>
#include <random>
#include <limits>
#include <optional>
#include <variant>
#include <any>

#include <array>
#include <bit>
#include <compare>
#include <concepts>
#include <numbers>
#include <ranges>
#include <span>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <version>
using namespace std;
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
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define REP(i,j,n) for(ll i=(j);i<(ll)(n);i++)
#define DREP(i,n,m) for(ll i=(n);i>=(m);i--)
#define drep(i,n) for(ll i=((n)-1);i>=0;i--)
#define rall(x) x.rbegin(),x.rend()
#define mp(...) make_pair(__VA_ARGS__)
#define pb push_back
#define fi first
#define se second
#define is insert
#define bg begin()
#define ed end()
#define all(x) x.begin(),x.end()
void scan(int&a) { cin >> a; }
void scan(ll&a) { cin >> a; }
void scan(string&a) { cin >> a; }
void scan(char&a) { cin >> a; }
void scan(uint&a) { cin >> a; }
void scan(ull&a) { cin >> a; }
void scan(bool&a) { cin >> a; }
void scan(ld&a){ cin>> a;}
template<class T> void scan(vector<T>&a) { for(auto&x:a) scan(x); }
void read() {}
template<class Head, class... Tail> void read(Head&head, Tail&... tail) { scan(head); read(tail...); }
#define INT(...) int __VA_ARGS__; read(__VA_ARGS__);
#define LL(...) ll __VA_ARGS__; read(__VA_ARGS__);
#define ULL(...) ull __VA_ARGS__; read(__VA_ARGS__);
#define STR(...) string __VA_ARGS__; read(__VA_ARGS__);
#define VC(type, name, ...) vector<type> name(__VA_ARGS__); read(name);
#define VVC(type, name, size, ...) vector<vector<type>> name(size, vector<type>(__VA_ARGS__)); read(name);
template<class T>void print(T a) { cout << a; }
template<class T> void print(vector<T>a) { for(int i=0;i<(int)a.size();i++){if(i)cout<<" ";print(a[i]);}cout<<endl;}
void PRT() { cout <<endl; return ; }
template<class T> void PRT(T a) { print(a); cout <<endl; return; }
template<class Head, class... Tail> void PRT(Head head, Tail ... tail) { print(head); cout << " "; PRT(tail...); return; }
template<class T,class F>
bool chmin(T &x, F y){
    if(x>y){
        x=y;
        return true;
    }
    return false;
}
template<class T, class F>
bool chmax(T &x, F y){
    if(x<y){
        x=y;
        return true;
    }
    return false;
}
template <typename T>
T floor(T a, T b) {
  return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
  return floor(x + y - 1, y);
}
template <typename T>
T bmod(T x, T y) {
  return x - y * floor(x, y);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
  T q = floor(x, y);
  return {q, x - q * y};
}
void YesNo(bool b){
    cout<<(b?"Yes":"No")<<endl;
}
void YESNO(bool b){
    cout<<(b?"YES":"NO")<<endl;
}
void AliceBob(bool b){
    cout<<(b?"Alice":"Bob")<<endl;
}
void TakahashiAoki(bool b){
    cout<<(b?"Takahashi":"Aoki")<<endl;
}
void Yes(){
    cout<<"Yes"<<endl;
}
void No(){
    cout<<"No"<<endl;
}
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
    while((F+1)*(F+1)<=x)F++;
    while(F*F>x)F--;
    return F;
}
template<class T>
vvc<T>trans(const vvc<T>&a){
    assert(a.size()&&a[0].size());
    vvc<T>b(a[0].size(),vc<T>(a.size()));
    rep(i,a.size())rep(j,a[0].size()){
        b[j][i]=a[i][j];
    }
    return b;
}
template<class T>
vc<string>trans(const vc<string>&a){
    assert(a.size()&&a[0].size());
    vc<string>b(a[0].size(),string(a.size(),0));
    rep(i,a.size())rep(j,a[0].size()){
        b[j][i]=a[i][j];
    }
    return b;
}
template<class T>
int popcount(T n){
    return __builtin_popcountll(n);
}
template<class T,class L=ll>
L sum(vc<T>&a){
    return accumulate(all(a),L(0));
}
template<class T>
vc<T>subset(T S){
    vc<T>ans;
    for(T x=S;x>0;x=(x-1)&S)ans.pb(x);
    ans.pb(0);
    return ans;
}
template<class T>
T max(vc<T>&a){
    return *max_element(all(a));
}
template<class T>
T min(vc<T>&a){
    return *min_element(all(a));
}
#ifndef COMPRESSER_STRUCT
#define COMPRESSER_STRUCT
template<class T>
struct compresser{
    vc<T>x;
    compresser(int n=0){x.reserve(n);}
    compresser(const vc<T>&xs){
        x=xs;
    }
    void push(T p){built=false;x.pb(p);}
    bool built=false;
    void build(){
        if(!chmax(built,1))return;
        sort(all(x));
        x.erase(unique(all(x)),x.end());
    }
    int find(T v){
        build();
        auto itr=lower_bound(all(x),v)-x.begin();
        if(itr==x.size()||x[itr]!=v)return -1;
        return itr;
    }
    int find_next(T v){
        build();
        return lower_bound(all(x),v)-x.begin();
    }
    int size(){
        build();
        return x.size();
    }
    T operator[](int i)const{
        assert(0<=i&&i<x.size());
        return x[i];
    }
};
#endif
template<class T,class L=ll>
vc<L> presum(vc<T> &a){
    vc<L> ret(a.size()+1);
    rep(i,a.size())ret[i+1]=ret[i]+a[i];
    return ret;
}
template<class T, class F>
vc<T> &operator+=(vc<T> &a,F b){
    for (auto&v:a)v += b;
    return a;
}
template<class T, class F>
vc<T> &operator-=(vc<T>&a,F b){
    for (auto&v:a)v-=b;
    return a;
}
template<class T, class F>
vc<T> &operator*=(vc<T>&a,F b){
    for (auto&v:a)v*=b;
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
constexpr ll ten(ll a){
    return pow<ll>(10,a);
}
template<typename T>constexpr T inf=numeric_limits<T>::max()/2-1;
template<class T>
int tbit(T x){
    using U=make_unsigned_t<T>;
    U y=(U)x;
    return y?(int)bit_width(y)-1:-1;
}
template<class T>
int lbit(T x){
    using U=make_unsigned_t<T>;
    U y=(U)x;
    return y?(int)countr_zero(y):-1;
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
istream& operator>>(istream&is,i128&x){
    string s;is>>s;
    x=0;
    int i=0,neg=0;
    if(s[0]=='-')neg=1,i=1;
    for(;i<(int)s.size();i++)x=x*10+s[i]-'0';
    if(neg)x=-x;
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
#ifdef LOCAL
#include "debug/debug.hpp"
#else
#define dbg(...) ((void)0)
#endif

struct template_setup{
    template_setup(){
        #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        
        #endif
        cin.tie(0)->sync_with_stdio(0);
        #ifdef LOCAL
        cout<<fixed<<setprecision(6);
        dbg("==============="s);
        #else
        cout<<fixed<<setprecision(20);
        #endif
    }
};
inline template_setup template_setup;

#endif
