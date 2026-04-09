#pragma once
#include"../template.hpp"
//n<=2^32
struct bit_vector{
    using u64=uint64_t;
    vc<u64>big_block;
    vc<u64>pattern;
    constexpr static inline int B=64;
    int n;
    bit_vector()=default;
    bit_vector(const vc<int>&v):n(v.size()){
        big_block.assign((n+B-1)/B+1,0);
        pattern.assign(big_block.size()+1,0);
        REP(i,1,big_block.size()){
            u64 val=0;
            uint shift=0;
            uint lim=min<uint>(v.size(),i*B);
            REP(l,(i-1)*B,lim){
                val+=(u64)v[l]<<(shift++);
            }
            big_block[i]=big_block[i-1]+__builtin_popcountll(val);
            pattern[i-1]=val;
        }
    }
    //[0,r)
    int rank1(int r){
        assert(0<=r&&r<=n);
        int res=big_block[r/B];
        res+=__builtin_popcountll(pattern[r/B]&((u64(1)<<(r%B))-1));
        return res;
    }
    int rank1(int l,int r){
        assert(l<=r);
        return rank1(r)-rank1(l);
    }
    int rank0(int r){
        return r-rank1(r);
    }
    int rank0(int l,int r){
        return r-l-rank1(l,r);
    }
};
template<class T,int depth>
struct wavlet_matrix{
    int n;
    vc<T>val;
    vc<int>start;
    vc<T>last;
    vc<bit_vector>bv;
    wavlet_matrix(int n=0):val(n),n(n),start(depth){}
    void set(int i,T x){
        val[i]=x;
    }

    void build(auto&F=[](int,vc<T>){}){
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
            F(i,val);
        }
        last=val;
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
    //[l,r) で val[i]<=k となる i についての sum を得る　
    template<class Info,class Y>
    Info::value_type sum(int l,int r,T k,Y&func){
        typename Info::value_type res=Info::e();
        drep(i,depth){
            auto&target=bv[i];
            int l0=target.rank0(l);
            int r0=target.rank0(r);
            int al=start[i];
            int l1=l-l0;
            int r1=r-r0;
            if(k>>i&1){
                res=Info::op(res,func(i,l0,r0));
                l=al+l1;
                r=al+r1;
            }else{
                l=l0,r=r0;
            }
        }
        res=Info::op(res,func(0,l,r));
        return res;
    }
};