#pragma once
#include "../../template.hpp"

template<class Key,class Val,int K,Val sentinel,bool is_max>
struct extreme_k{
    static_assert(K>0);
    struct T{
        Val val;
        Key key;
        T&operator+=(Val v){val+=v;return *this;}
        T&operator-=(Val v){val-=v;return *this;}
        T operator+(Val v)const{return {val+v,key};}
        T operator-(Val v)const{return {val-v,key};}
        friend T operator+(Val v,const T&a){return a+v;}
    };
    array<T,K>d;
    extreme_k(){d.fill({sentinel,Key{}});}
    static bool better(Val a,Val b){
        if constexpr(is_max)return a>b;
        else return a<b;
    }
    static bool valid(Val a){
        if constexpr(is_max)return a>sentinel;
        else return a<sentinel;
    }
    T&operator[](int i){return d[i];}
    const T&operator[](int i)const{return d[i];}
    bool has(Key key,Val val)const{
        rep(i,K)if(valid(d[i].val)&&d[i].key==key&&d[i].val==val)return true;
        return false;
    }
    int add_element(Key key,Val val){
        if constexpr(K==2){
            if(valid(d[0].val)&&d[0].key==key){
                if(!better(val,d[0].val))return 0;
                d[0].val=val;
                return 1;
            }
            if(valid(d[1].val)&&d[1].key==key){
                if(!better(val,d[1].val))return 0;
                if(better(val,d[0].val)){
                    d[1]=d[0];
                    d[0]={val,key};
                }else d[1]={val,key};
                return 1;
            }
            if(!better(val,d[1].val))return 0;
            if(better(val,d[0].val)){
                d[1]=d[0];
                d[0]={val,key};
            }else d[1]={val,key};
            return 1;
        }else{
            int old=-1;
            rep(i,K)if(valid(d[i].val)&&d[i].key==key){
                old=i;
                break;
            }
            if(old!=-1){
                if(!better(val,d[old].val))return 0;
                REP(i,old,K-1)d[i]=d[i+1];
                d[K-1]={sentinel,Key{}};
            }
            if(!better(val,d[K-1].val))return 0;
            int pos=0;
            while(pos<K&&!better(val,d[pos].val))pos++;
            DREP(i,K-1,pos+1)d[i]=d[i-1];
            d[pos]={val,key};
            return 1;
        }
    }
    extreme_k&merge_data(const extreme_k&x){
        if constexpr(K==2){
            add_element(x.d[0].key,x.d[0].val);
            add_element(x.d[1].key,x.d[1].val);
        }else rep(i,K)add_element(x.d[i].key,x.d[i].val);
        return *this;
    }
    extreme_k&operator+=(Val v){
        rep(i,K)if(valid(d[i].val))d[i].val+=v;
        return *this;
    }
    extreme_k&operator-=(Val v){
        rep(i,K)if(valid(d[i].val))d[i].val-=v;
        return *this;
    }
    extreme_k operator+(Val v)const{return extreme_k(*this)+=v;}
    extreme_k operator-(Val v)const{return extreme_k(*this)-=v;}
    friend extreme_k operator+(Val v,const extreme_k&a){return a+v;}
};
template<class Key,class Val,int K,Val NEG_INF=neg_inf<Val>>
using max_k=extreme_k<Key,Val,K,NEG_INF,true>;
template<class Key,class Val,int K,Val INF=inf<Val>>
using min_k=extreme_k<Key,Val,K,INF,false>;
template<class T>
struct merge_info{
    using value_type=T;
    static value_type op(const value_type&a,const value_type&b){
        value_type res=a;
        return res.merge_data(b);
    }
    static value_type id(){return {};}
    static value_type e(){return id();}
};
template<class Key,class Val,int K,Val NEG_INF=neg_inf<Val>>
using maxk_info=merge_info<max_k<Key,Val,K,NEG_INF>>;
template<class Key,class Val,int K,Val INF=inf<Val>>
using mink_info=merge_info<min_k<Key,Val,K,INF>>;
