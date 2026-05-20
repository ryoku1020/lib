#pragma once
#include"bit-vector.hpp"
template<class T,int depth>
struct WaveletMatrix{
    int n;
    vc<T>val;
    vc<int>start;
    vc<BitVector>bv;
    WaveletMatrix(int n=0):val(n),n(n),start(depth){
        assert(n>=0);
    }
    void set(int i,T x){
        assert(0<=i&&i<n);
        val[i]=x;
    }

    void build(){
        bv.resize(depth);
        drep(i,depth){
            vc<int>w(n);rep(j,n)w[j]=val[j]>>i&1;
            bv[i]=BitVector(w);
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
        assert(0<=l&&l<=r&&r<=n);
        assert(0<=k&&k<r-l);
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
        assert(0<=l&&l<=r&&r<=n);
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
        assert(0<=l&&l<=r&&r<=n);
        return count_lower(l,r,x)-count_lower(l,r,x-1);
    }
};
