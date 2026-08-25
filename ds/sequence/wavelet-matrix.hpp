#pragma once
#include"bit-vector.hpp"
template<class T,int D>
struct wm_base{
    using U=make_unsigned_t<T>;
    int n;
    array<bit_vector,D>bv;
    array<int,D>mid;
    vc<T>gi;
    void build(vc<T>a){
        gi=a,n=a.size();
        vc<int>send(n);
        drep(bit,D){
            rep(i,n)send[i]=a[i]>>bit&1;
            bv[bit]=bit_vector(send);
            vc<T>l,r;
            rep(i,n){
                if(a[i]>>bit&1)r.pb(a[i]);
                else l.pb(a[i]);
            }
            mid[bit]=l.size();
            l.insert(l.end(),all(r));
            a=move(l);
        }
    }
    template<class F>
    void build_info(F f){
        auto a=gi;
        vc<int>idx(n);
        rep(i,n)idx[i]=i;
        f(a,idx,D);
        drep(bit,D){
            vc<T>l,r;
            vc<int>li,ri;
            rep(i,n){
                if(a[i]>>bit&1)r.pb(a[i]),ri.pb(idx[i]);
                else l.pb(a[i]),li.pb(idx[i]);
            }
            l.insert(l.end(),all(r));
            li.insert(li.end(),all(ri));
            a=move(l);
            idx=move(li);
            f(a,idx,bit);
        }
    }
    template<class L>
    static array<vc<L>,D+1>& lower_pref(){
        static array<vc<L>,D+1>pref;
        return pref;
    }
    template<class L>
    void buildlowersum(const vc<L>&W){
        auto&pref=lower_pref<L>();
        build_info([&](const vc<T>&a,const vc<int>&idx,int bit){
            pref[bit]=vc<L>(n+1);
            rep(i,n)pref[bit][i+1]=pref[bit][i]+W[idx[i]];
        });
    }
    struct node{
        int bit,l,r;
        int size()const{return r-l;}
    };
    struct child_type{
        bool has;
        node zero,one;
    };
    child_type child(node x)const{
        if(x.bit==-1)return {false,{},{}};
        int a0=bv[x.bit].rank0(x.l);
        int b0=bv[x.bit].rank0(x.r);
        int a1=x.l-a0,b1=x.r-b0;
        return {true,{x.bit-1,a0,b0},{x.bit-1,mid[x.bit]+a1,mid[x.bit]+b1}};
    }
    T kth_smallest(int l,int r,int k)const{
        T ans=0;
        node x={D-1,l,r};
        while(x.bit!=-1){
            child_type ch=child(x);
            if(ch.zero.size()<=k){
                k-=ch.zero.size();
                ans+=T(1)<<x.bit;
                x=ch.one;
            }else x=ch.zero;
        }
        return ans;
    }
    ll count_less(int l,int r,T k)const{
        ll ans=0;
        node x={D-1,l,r};
        while(x.bit!=-1){
            child_type ch=child(x);
            if(k>>x.bit&1)ans+=ch.zero.size(),x=ch.one;
            else x=ch.zero;
        }
        return ans;
    }
    //[l,r) [d,u)
    ll count(int l,int r,T d,T u)const{
        return count_less(l,r,u)-count_less(l,r,d);
    }
    template<class L>
    L lower_sum(int l,int r,T u)const{
        auto&pref=lower_pref<L>();
        L ans=0;
        node x={D-1,l,r};
        while(x.bit!=-1){
            child_type ch=child(x);
            if(u>>x.bit&1){
                ans+=pref[x.bit][ch.zero.r]-pref[x.bit][ch.zero.l];
                x=ch.one;
            }else x=ch.zero;
        }
        return ans;
    }
    template<class L>
    L lower_sum(int l,int r,T d,T u)const{
        return lower_sum<L>(l,r,u)-lower_sum<L>(l,r,d);
    }
};
