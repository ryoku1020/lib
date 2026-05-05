#pragma once
# pragma GCC optimize("O3")
using namespace std;
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
using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using i128=__int128;
template<class T>using vc=vector<T>;
template<class T>using vvc=vc<vc<T>>;
template<class T>using vvvc=vvc<vc<T>>;
#define vec(d,T,n,...) vec_##d(T,n,__VA_ARGS__)
#define vec_1(T,n,a) vector<T> n(a)
#define vec_2(T,n,a,b) vector<vector<T>> n(a,vector<T>(b))
#define vec_3(T,n,a,b,c) vector<vector<vector<T>>> n(a,vector<vector<T>>(b,vector<T>(c)))
#define vec_4(T,n,a,b,c,d) vector<vector<vector<vector<T>>>> n(a,vector<vector<vector<T>>>(b,vector<vector<T>>(c,vector<T>(d))))
#define vec_5(T,n,a,b,c,d,e) vector<vector<vector<vector<vector<T>>>>> n(a,vector<vector<vector<vector<T>>>>(b,vector<vector<vector<T>>>(c,vector<vector<T>>(d,vector<T>(e)))))
#define vec_6(T,n,a,b,c,d,e,f) vector<vector<vector<vector<vector<vector<T>>>>>> n(a,vector<vector<vector<vector<vector<T>>>>>(b,vector<vector<vector<vector<T>>>>(c,vector<vector<vector<T>>>(d,vector<vector<T>>(e,vector<T>(f))))))
#define vec_7(T,n,a,b,c,d,e,f,g) vector<vector<vector<vector<vector<vector<vector<T>>>>>>> n(a,vector<vector<vector<vector<vector<vector<T>>>>>>(b,vector<vector<vector<vector<vector<T>>>>>(c,vector<vector<vector<vector<T>>>>(d,vector<vector<vector<T>>>(e,vector<vector<T>>(f,vector<T>(g)))))))
template<class T>using smpq=priority_queue<T,vector<T>,greater<T>>;
template<class T>using bipq=priority_queue<T>;
#define rep(i,n) for(ll i=0;i<(ll)(n);i++)
#define REP(i,j,n) for(ll i=(j);i<(ll)(n);i++)
#define DREP(i,n,m) for(ll i=(n);i>=(m);i--)
#define drep(i,n) for(ll i=((n)-1);i>=0;i--)
#define rall(x) x.rbegin(),x.rend()
#define mp make_pair
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
#define CHR(...) char __VA_ARGS__; read(__VA_ARGS__);
#define DBL(...) double __VA_ARGS__; read(__VA_ARGS__);
#define LD(...) ld __VA_ARGS__; read(__VA_ARGS__);
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
void Yes(){
    cout<<"Yes"<<endl;
}
void No(){
    cout<<"No"<<endl;
}
template<class T=ll>
T isqrt(T x){
    T F=sqrtl(x);
    while((F+1)*(F+1)<=x)F++;
    while(F*F>x)F--;
    return F;
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
vvc<int>readgraph(int n,int m,int off = -1){
    vvc<int> g(n);
    rep(i, m){
        int u,v;
        cin>>u>>v;
        u+=off,v+=off;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}
vvc<int> readtree(int n,int off=-1){
    return readgraph(n,n-1,off);
}
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
constexpr T POW(T a,T b){
    T res=1;
    while(b){
        if(b&1)res*=a;
        a*=a;
        b/=2;
    }
    return res;
}
constexpr ll ten(ll a){
    return POW<ll>(10,a);
}
template<typename T>constexpr T inf=numeric_limits<T>::max()/2-1;
int tbit(int32_t x){return x==0?-1:31-__builtin_clz((uint32_t)x);}
int lbit(int32_t x){return x==0?-1:__builtin_ctz((uint32_t)x);}
int tbit(uint32_t x){return x==0?-1:31-__builtin_clz(x);}
int lbit(uint32_t x){return x==0?-1:__builtin_ctz(x);}
int tbit(int64_t x){return x==0?-1:63-__builtin_clzll((uint64_t)x);}
int lbit(int64_t x){return x==0?-1:__builtin_ctzll((uint64_t)x);}
int tbit(uint64_t x){return x==0?-1:63-__builtin_clzll(x);}
int lbit(uint64_t x){return x==0?-1:__builtin_ctzll(x);}
int tbit(int32_t x,int p){return p<0?-1:tbit((int32_t)(x&(p>=31?~0u:(1u<<(p+1))-1)));}
int lbit(int32_t x,int p){return p>31?-1:lbit((int32_t)(x&(~0u<<p)));}
int tbit(uint32_t x,int p){return p<0?-1:tbit((uint32_t)(x&(p>=31?~0u:(1u<<(p+1))-1)));}
int lbit(uint32_t x,int p){return p>31?-1:lbit((uint32_t)(x&(~0u<<p)));}
int tbit(int64_t x,int p){return p<0?-1:tbit((int64_t)(x&(p>=63?~0ULL:(1ULL<<(p+1))-1)));}
int lbit(int64_t x,int p){return p>63?-1:lbit((int64_t)(x&(~0ULL<<p)));}
int tbit(uint64_t x,int p){return p<0?-1:tbit((uint64_t)(x&(p>=63?~0ULL:(1ULL<<(p+1))-1)));}
int lbit(uint64_t x,int p){return p>63?-1:lbit((uint64_t)(x&(~0ULL<<p)));}
std::istream& operator>>(std::istream& is, __int128& x) {
    std::streambuf* sb = is.rdbuf();

    int c = sb->sgetc();
    while (c <= ' ') c = sb->snextc();

    bool neg = false;
    if (c == '-') {
        neg = true;
        c = sb->snextc();
    }

    unsigned __int128 v = 0;

    while ((unsigned)(c - '0') < 10) {
        v = v * 10 + (c - '0');
        c = sb->snextc();
    }

    x = neg ? -(__int128)v : (__int128)v;
    return is;
}

std::ostream& operator<<(std::ostream& os, __int128 x) {
    std::streambuf* sb = os.rdbuf();

    if (x == 0) {
        sb->sputc('0');
        return os;
    }

    char buf[40];
    int pos = 39;

    bool neg = x < 0;
    unsigned __int128 v = neg ? -(unsigned __int128)x : (unsigned __int128)x;

    while (v) {
        buf[--pos] = char('0' + (v % 10));
        v /= 10;
    }

    if (neg) buf[--pos] = '-';

    sb->sputn(buf + pos, 39 - pos);
    return os;
}
#ifdef LOCAL

template<typename T, typename U> std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p);
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);
template<typename T> std::ostream& operator<<(std::ostream& os, const std::deque<T>& dq);
template<typename T> std::ostream& operator<<(std::ostream& os, const std::list<T>& lst);
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s);
template<typename T> std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& s);
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m);
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& m);
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> st);
template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q);
template<typename T, std::size_t N> std::ostream& operator<<(std::ostream& os, const std::array<T, N>& a);
template <typename T, typename Container, typename Compare>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T, Container, Compare> pq);

#define dbg(...) debug_func(0, #__VA_ARGS__, __VA_ARGS__)

template <typename T>
void debug_func(int i, T name) {
  cout << endl;
}

template <typename T1, typename T2, typename... T3>
void debug_func(int i, const T1 &name, const T2 &a, const T3 &...b) {
  for ( ; name[i] != ',' && name[i] != '\0'; i++ ) cout << name[i];
  cout << ":" << a << " ";
  debug_func(i + 1, name, b...);
}
// pair
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
// vector
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) os << ", ";
        os << v[i];
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::deque<T>& dq) {
    os << "[";
    for (size_t i = 0; i < dq.size(); ++i) {
        if (i > 0) os << ", ";
        os << dq[i];
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& lst) {
    os << "[";
    bool first = true;
    for (const auto& x : lst) {
        if (!first) os << ", ";
        os << x;
        first = false;
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) os << ", ";
        os << x;
        first = false;
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) os << ", ";
        os << x;
        first = false;
    }
    os << "}";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) os << ", ";
        os << kv;
        first = false;
    }
    os << "}";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) os << ", ";
        os << kv;
        first = false;
    }
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::stack<T> st) {
    os << "[";
    bool first = true;
    while (!st.empty()) {
        if (!first) os << ", ";
        os << st.top();
        st.pop();
        first = false;
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    os << "[";
    bool first = true;
    while (!q.empty()) {
        if (!first) os << ", ";
        os << q.front();
        q.pop();
        first = false;
    }
    os << "]";
    return os;
}

template<typename T, typename Container, typename Compare>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T, Container, Compare> pq) {
    os << "[";
    while (!pq.empty()) {
        os << pq.top() << (pq.size() > 1 ? ", " : "");
        pq.pop();
    }
    return os << "]";
}
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& a) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        if (i > 0) os << ", ";
        os << a[i];
    }
    os << "]";
    return os;
}
#else
#define dbg(...) 1111
#endif
