#pragma once
#include "../template.hpp"
template<class Value_type,Value_type inf>
struct Min{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return min(a,b);
    }
    static value_type e(){
        return inf;
    }
    static value_type leaf(){
        return inf;
    }
    static value_type get(auto a){
        return inf;
    }
};
template<class Value_type,Value_type neg_inf>
struct Max{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return max(a,b);
    }
    static value_type e(){
        return neg_inf;
    }
    static value_type leaf(){
        return neg_inf;
    }
    static value_type get2(auto a){
        return neg_inf;
    }
};
template<class Value_type>
struct Sum{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return a+b;
    }
    static value_type e(){
        return 0;
    }
    static value_type leaf(){
        return 0;
    }
    static value_type get2(auto a){
        return 0;
    }
};
template<class Value_type>
struct Prod{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return a*b;
    }
    static value_type e(){
        return 1;
    }
    static value_type leaf(){
        return 1;
    }
    static value_type get2(auto a){
        return 1;
    }
};
template<class... Infos>
struct Merger{
    using value_type=tuple<typename Infos::value_type...>;
    template<size_t... I>
    static value_type op_impl(value_type a,value_type b,index_sequence<I...>){
        return value_type{Infos::op(get<I>(a),get<I>(b))...};
    }
    static value_type op(value_type a,value_type b){
        return op_impl(a,b,index_sequence_for<Infos...>{});
    }
    static value_type e(){
        return value_type{Infos::e()...};
    }
    static value_type leaf(){
        return value_type{Infos::leaf()...};
    }
    static value_type get2(auto a){
        return value_type{Infos::get2(a)...};
    }
};
template<class Value_type>
struct Affine{
    using value_type=pair<Value_type,Value_type>;
    static value_type op(value_type a,value_type b){
        return {a.first*b.first,a.second*b.first+b.second};
    }
    static value_type e(){
        return {1,0};
    }
    static value_type leaf(){
        return e();
    }
    static value_type get2(auto a){
        return e();
    }
};
template<class Info>
struct Reversed{
    using value_type=Info::value_type;
    static value_type op(value_type a,value_type b){
        return Info::op(b,a);
    }
    static value_type e(){
        return Info::e();
    }
    static value_type leaf(){
        return Info::leaf();
    }
    static value_type get2(){
        return Info::get2();
    }
};


template<class Key,class Val,int K>
struct MaxK{
    struct T{
        Val val;
        Key key;
        T&operator+=(Val v){val+=v;return *this;}
        T&operator-=(Val v){val-=v;return *this;}
        T operator+(Val v)const{return {val+v,key};}
        T operator-(Val v)const{return {val-v,key};}
        friend T operator+(Val v,const T&a){return a+v;}
    };
    struct DATA{
        array<T,K> d;
        DATA(){d.fill({-inf<Val>,Key{}});}
        T&operator[](int i){return d[i];}
        const T&operator[](int i)const{return d[i];}
        void add_element(const T&a){
            if(a.val<=d[K-1].val)return;
            int pos=0;
            while(pos<K&&d[pos].val>=a.val){
                if(d[pos].key==a.key)return;
                pos++;
            }
            int end=K-1;
            REP(i,pos,K)if(d[i].key==a.key){end=i;break;}
            DREP(i,end,pos+1)d[i]=d[i-1];
            d[pos]=a;
        }
        DATA&merge_data(const DATA&x){
            rep(i,K)add_element(x.d[i]);
            return *this;
        }
        DATA&operator+=(Val v){
            rep(i,K)if(d[i].val>-inf<Val>)d[i].val+=v;
            return *this;
        }
        DATA&operator-=(Val v){
            rep(i,K)if(d[i].val>-inf<Val>)d[i].val-=v;
            return *this;
        }
        DATA operator+(Val v)const{return DATA(*this)+=v;}
        DATA operator-(Val v)const{return DATA(*this)-=v;}
        friend DATA operator+(Val v,const DATA&a){return a+v;}
        static DATA e(){return DATA();}
    };
    static DATA op(const DATA&a,const DATA&b){
        DATA res(a);
        return res.merge_data(b);
    }
    static DATA e(){return DATA();}
};
template<class Key,class Val>
struct MaxK<Key,Val,2>{
    struct T{
        Val val;
        Key key;
        T&operator+=(Val v){val+=v;return *this;}
        T&operator-=(Val v){val-=v;return *this;}
        T operator+(Val v)const{return {val+v,key};}
        T operator-(Val v)const{return {val-v,key};}
        friend T operator+(Val v,const T&a){return a+v;}
    };
    struct DATA{
        array<T,2> d;
        DATA(){d.fill({-inf<Val>,Key{}});}
        T&operator[](int i){return d[i];}
        const T&operator[](int i)const{return d[i];}
        void add_element(const T&a){
            if(a.val<=d[1].val)return;
            if(a.key==d[0].key){
                if(a.val>d[0].val)d[0].val=a.val;
                return;
            }
            if(a.val>d[0].val){
                d[1]=d[0];
                d[0]=a;
            }else{
                d[1]=a;
            }
        }
        DATA&merge_data(const DATA&x){
            add_element(x.d[0]);
            add_element(x.d[1]);
            return *this;
        }
        DATA&operator+=(Val v){
            if(d[0].val>-inf<Val>)d[0].val+=v;
            if(d[1].val>-inf<Val>)d[1].val+=v;
            return *this;
        }
        DATA&operator-=(Val v){
            if(d[0].val>-inf<Val>)d[0].val-=v;
            if(d[1].val>-inf<Val>)d[1].val-=v;
            return *this;
        }
        DATA operator+(Val v)const{return DATA(*this)+=v;}
        DATA operator-(Val v)const{return DATA(*this)-=v;}
        friend DATA operator+(Val v,const DATA&a){return a+v;}
        static DATA e(){return DATA();}
    };
    static DATA op(const DATA&a,const DATA&b){
        DATA res(a);
        return res.merge_data(b);
    }
    static DATA e(){return DATA();}
};