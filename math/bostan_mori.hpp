#pragma once
#include "../template.hpp"
#include "fps.hpp"
template<class mint>
mint BostanMori(FormalPowerSeries<mint>p,FormalPowerSeries<mint>q,long long n){
    if(p.empty()||q.empty())return 0;
    int d=q.size();
    if((int)p.size()>=d)p.resize(d-1);
    int ntt_size=1;
    while(ntt_size<2*d)ntt_size<<=1;
    int half=ntt_size>>1;
    std::vector<mint>bp(ntt_size),bq(ntt_size),np_full(ntt_size),nq_half(half),np_half(half);
    mint inv_n=mint(ntt_size).inv(),inv_half=mint(half).inv();
    while(n>0){
        std::fill(bp.begin(),bp.end(),0);
        std::fill(bq.begin(),bq.end(),0);
        for(int i=0;i<(int)p.size();i++)bp[i]=p[i];
        for(int i=0;i<(int)q.size();i++)bq[i]=q[i];
        atcoder::internal::butterfly(bp);
        atcoder::internal::butterfly(bq);
        for(int i=0;i<half;i++)nq_half[i]=bq[2*i]*bq[2*i+1];
        atcoder::internal::butterfly_inv(nq_half);
        if(n%2==0){
            for(int i=0;i<half;i++)np_half[i]=bp[2*i]*bq[2*i+1]+bp[2*i+1]*bq[2*i];
            atcoder::internal::butterfly_inv(np_half);
            p.resize(d);
            for(int i=0;i<d;i++)p[i]=np_half[i]*inv_n;
        }else{
            for(int i=0;i<half;i++){
                np_full[2*i]=bp[2*i]*bq[2*i+1];
                np_full[2*i+1]=bp[2*i+1]*bq[2*i];
            }
            atcoder::internal::butterfly_inv(np_full);
            p.resize(d);
            for(int i=0;i<d;i++)p[i]=np_full[2*i+1]*inv_n;
        }
        q.resize(d);
        for(int i=0;i<d;i++)q[i]=nq_half[i]*inv_half;
        n>>=1;
    }
    return p[0]/q[0];
}