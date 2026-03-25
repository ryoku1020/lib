#pragma once
#include"../template.cpp"
#include"../math/mod261.cpp"
template<int base_count>
struct Roll{
    using mint=mod261;
    static inline uniform_int_distribution<int>un;
    static inline mt19937 mt;
    static int get(){
        return un(mt);
    }
    int n;
    static inline array<ll,base_count>base;
    static inline array<vc<mint>,base_count>pw;
    static inline array<vc<mint>,base_count>inv;
    static inline bool done=false;
    array<vc<mint>,base_count>pref;
    Roll(string s){
        build(s);
    }
    Roll(vc<ll>v){
        build(v);
    }
    Roll(vc<int>v){
        build(v);
    }
    static void init(int MAXN){
        done=1;
        un=uniform_int_distribution<int>(1e9,2e9);
        mt.seed(random_device{}());
        done=1;
        rep(i,base_count){
            pw[i].resize(MAXN+1);
            inv[i].resize(MAXN+1);
            base[i]=get();
        }
        rep(i,base_count){
            inv[i][0]=pw[i][0]=1;
            mint in=mint(base[i]).inv();
            rep(j,MAXN){
                inv[i][j+1]=inv[i][j]*in;
                pw[i][j+1]=pw[i][j]*base[i];
            }
        }
    }
    void build(vc<int>v){

        vc<ll>V;rep(i,v.size())V.pb(v[i]);
        build(V);
    }
    void build(vc<ll>v){
        assert(done);
        rep(i,v.size())v[i]++;
        n=v.size();
        rep(i,base_count){
            pref[i].resize(n+1);
            rep(j,n){
                pref[i][j+1]=pref[i][j]+v[j]*pw[i][j];
            }
        }
    }
    //[l,r)
    array<ll,base_count>get(int l,int r){
        array<ll,base_count>res{};
        rep(i,base_count){
            res[i]=((pref[i][r]-pref[i][l])*inv[i][l]).val;
        }
        return res;
    }
    void build(string s){
        vc<ll>v(s.size());
        rep(i,s.size())v[i]=s[i];
        build(v);
    }
};