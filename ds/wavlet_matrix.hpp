#pragma once
#include"../template.hpp"
#include"bit_vector.hpp"
template<class T,int depth>
struct wavlet_matrix{
    int n;
    vc<T>val;
    vc<int>start;
    vc<bit_vector>bv;
    wavlet_matrix(int n=0):val(n),n(n),start(depth){}
    void set(int i,T x){
        val[i]=x;
    }

    void build(){
        bv.resize(depth);
        drep(i,depth){
            vc<int>w(n);rep(j,n)w[j]=val[j]>>i&1;
            bv[i]=bit_vector(w);
            vc<int>l,r;
            rep(j,n){
                ((val[j]>>i&1)?r:l).push_back(val[j]);
            }
            start[i]=l.size();
            val=move(l);
            for(auto&x:r)val.pb(x);
        }
    }
    T kth_smallest(int l,int r,T k){
        T now=0;
        drep(i,depth){
            auto&target=bv[i];
            int l0=target.rank0(l);
            int r0=target.rank0(r);
            int al=start[i];
            int l1=l-l0;
            int r1=r-r0;
            if(r0-l0>k){
                l=l0,r=r0;
            }else{
                now|=T(1)<<i;
                k-=(r0-l0);
                l=al+l1;
                r=al+r1;
            }
        }
        return now;
    }
    //# of i \in[l,r) and val[i]<=k
    int count_lower(int l,int r,T k){
        int ans=0;
        drep(i,depth){
            auto&target=bv[i];
            int l0=target.rank0(l);
            int r0=target.rank0(r);
            int al=start[i];
            int l1=l-l0;
            int r1=r-r0;
            if(k>>i&1){
                ans+=r0-l0;
                l=al+l1;
                r=al+r1;
            }else{
                l=l0,r=r0;
            }
        }
        return ans+r-l;
    }
    int count(int l,int r,T x){
        return count_lower(l,r,x)-count_lower(l,r,x-1);
    }
};