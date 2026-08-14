#pragma once
#include"base.hpp"
template<class mint>
struct SubproductTree{
    int M;
    vc<mint>queries;
    vc<fps<mint>>T;
    bool built;
    SubproductTree(int n=0):built(false){
        assert(mint::get_mod());
        queries.reserve(n);
    }
    void add(mint x){
        queries.push_back(x);
    }
    void dfs(int node,int l,int r){
        if(r-l==1){
            T[node]=fps{mint(1),-queries[l]};
            return;
        }
        int m=(l+r)/2;
        dfs(2*node,l,m);
        dfs(2*node+1,m,r);
        T[node]=T[2*node]*T[2*node+1];
    }
    void build_tree(){
        M=queries.size();
        if(M==0)return;
        T.assign(4*M,fps<mint>{});
        dfs(1,0,M);
        built=true;
    }
    vc<mint>middle_product(const vc<mint>&A,const vc<mint>&B){
        int n=A.size();
        int m=B.size();
        if(m==0)return vc<mint>(n+1,mint(0));
        int S=1;while(S<n)S*=2;
        vc<mint>a=A;a.resize(S,mint(0));
        vc<mint>b(S,mint(0));
        rep(i,m)b[i]=B[m-1-i];
        
        atcoder::internal::butterfly(a);
        atcoder::internal::butterfly(b);
        for(int i=0;i<S;++i)a[i]*=b[i];
        atcoder::internal::butterfly_inv(a);
        mint invS=mint(1)/mint(S);
        vc<mint>res(n-m+1);
        rep(i,n-m+1)res[i]=a[i+m-1]*invS;
        return res;
    }

    void evaluate(int node,int l,int r,const vc<mint>&U,vc<mint>&res){
        if(r-l==1){
            res[l]=U[0];
            return;
        }
        int m=(l+r)/2;
        const fps<mint>&T_left=T[2*node];
        const fps<mint>&T_right=T[2*node+1];
        int n=U.size();
        int m_l=T_left.size();
        int m_r=T_right.size();
        int S=1;while(S<n)S*=2;
        vc<mint>u_ntt=U;u_ntt.resize(S,mint(0));
        atcoder::internal::butterfly(u_ntt);
        
        vc<mint>t_r_ntt(S,mint(0));
        rep(i,m_r)t_r_ntt[i]=T_right[m_r-1-i];
        atcoder::internal::butterfly(t_r_ntt);
        vc<mint>u_l(S);
        rep(i,S)u_l[i]=u_ntt[i]*t_r_ntt[i];
        atcoder::internal::butterfly_inv(u_l);
        vc<mint> t_l_ntt(S,mint(0));
        rep(i,m_l)t_l_ntt[i]=T_left[m_l-1-i];
        atcoder::internal::butterfly(t_l_ntt);
        vc<mint>u_r(S);
        rep(i,S)u_r[i]=u_ntt[i]*t_l_ntt[i];
        atcoder::internal::butterfly_inv(u_r);

        mint invS=1/mint(S);
        vc<mint>Ul(n-m_r+1);
        rep(i,n-m_r+1)Ul[i]=u_l[m_r-1+i]*invS;
        vc<mint>Ur(n-m_l+1);
        rep(i,n-m_l+1)Ur[i]=u_r[m_l-1+i]*invS;
        evaluate(2*node,l,m,Ul,res);
        evaluate(2*node+1,m,r,Ur,res);
    }
    vc<mint>calc(const fps<mint>&target){
        if(!built)build_tree();
        if(M==0)return {};
        int N=target.size();
        if(N==0)return vc<mint>(M,mint(0));
        fps<mint>V=T[1].inv(N);
        vc<mint>F(all(target));
        F.resize(N+M-1,mint(0));
        vc<mint>U=middle_product(F,V);
        vc<mint>res(M);
        evaluate(1,0,M,U,res);
        return res;
    }
};

template<class mint>
vc<mint>MultipointEvaluation(fps<mint>f,vc<mint>query){
    assert(mint::get_mod());
    SubproductTree<mint> st(query.size());
    for(auto&x:query)st.add(x);
    auto ans=st.calc(f);
    return ans;
}