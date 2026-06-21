#pragma once
#include "conv.hpp"
template<class mint>
struct FormalPowerSeries:vc<mint>{
    #define BF atcoder::internal::butterfly
    #define IBF atcoder::internal::butterfly_inv
    using vc<mint>::vc;
    using vc<mint>::operator[];
    using poly=FormalPowerSeries<mint>;
    FormalPowerSeries(initializer_list<mint> init):vc<mint>(init){}
    FormalPowerSeries(const vc<mint>& v):vc<mint>(v){}
    FormalPowerSeries(vc<mint>&& v):vc<mint>(std::move(v)){}
    poly& operator=(initializer_list<mint> init){vc<mint>::operator=(init);return *this;}
    poly& operator=(const vc<mint>& v){vc<mint>::operator=(v);return *this;}
    poly& operator=(vc<mint>&& v){vc<mint>::operator=(std::move(v));return *this;}
    poly& operator+=(const poly& g){
        int n=g.size();
        if(n>(int)this->size())this->resize(n);
        for(int i=0;i<n;i++)(*this)[i]+=g[i];
        return *this;
    }
    poly& operator-=(const poly& g){
        int n=g.size();
        if(n>(int)this->size())this->resize(n);
        for(int i=0;i<n;i++)(*this)[i]-=g[i];
        return *this;
    }
    poly& operator*=(const poly& g){
        if(this->empty()||g.empty()){this->clear();return *this;}
        auto res=atcoder::convolution<mint>(*this,g);
        *this=poly(res.begin(),res.end());
        return *this;
    }
    poly& operator+=(const mint& v){if(this->empty())this->resize(1);(*this)[0]+=v;return *this;}
    poly& operator-=(const mint& v){if(this->empty())this->resize(1);(*this)[0]-=v;return *this;}
    poly& operator*=(const mint& v){for(auto& x:*this)x*=v;return *this;}
    poly& operator/=(const mint& v){mint inv=v.inv();for(auto& x:*this)x*=inv;return *this;}
    poly& operator>>=(const ll&v){*this=poly(this->begin()+min<int>(this->size(),v),this->end());return *this;} 
    poly& operator<<=(const ll&v){poly np(v+this->size());rep(i,this->size())np[i+v]=(*this)[i];*this=np;return *this;}


    poly operator+(const poly& g)const{return poly(*this)+=g;}
    poly operator-(const poly& g)const{return poly(*this)-=g;}
    poly operator*(const poly& g)const{return poly(*this)*=g;}

    
    poly operator+(const mint& v)const{return poly(*this)+=v;}
    friend poly operator+(const mint& v,const poly& g){return poly(g)+=v;}
    poly operator-(const mint& v)const{return poly(*this)-=v;}
    friend poly operator-(const mint& v,const poly& g){return -g+=v;}
    poly operator*(const mint& v)const{return poly(*this)*=v;}
    friend poly operator*(const mint& v,const poly& g){return poly(g)*=v;}
    poly operator/(const mint& v)const{return poly(*this)/=v;}
    friend poly operator/(const mint& v,const poly& g){return poly(g)/=v;}

    poly operator>>(const ll&v)const{return poly(*this)>>=v;}
    poly operator<<(const ll&v)const{return poly(*this)<<=v;}

    poly operator-()const{
        poly res=*this;
        for(auto& x:res)x=-x;
        return res;
    }
    poly pre(int sz)const{
        return poly(this->begin(),this->begin()+min((int)this->size(),sz));
    }
    //[0,n)
    poly inv(int deg=-1)const{
        assert((*this).size()&&(*this)[0].val!=0);
        if(deg==-1)deg=this->size();
        poly res{(*this)[0].inv()};
        for(int len=1;len<deg;len*=2){
            int nxt=len*2;
            auto F=(*this).pre(len*2);
            auto res2=res;
            F.resize(nxt);
            res2.resize(nxt);
            BF(F);
            BF(res2);
            rep(i,res2.size())F[i]*=res2[i];
            IBF(F);mint inv=1/mint(nxt);rep(i,F.size())F[i]*=inv; 
            for(int i=0;i<len;++i)F[i]=0;REP(i,len,len*2)F[i]=-F[i];
            F.resize(nxt);
            BF(F);
            rep(i,res2.size())F[i]*=res2[i];
            IBF(F);rep(i,F.size())F[i]*=inv;
            res.resize(len*2);REP(i,len,len*2)res[i]=F[i];
        }
        res.resize(deg);
        return res;
    }
    poly diff()const{
        auto res=*this;
        rep(i,res.size())res[i]*=i;
        res.erase(res.begin());
        return res;
    }
    poly integral()const{
        static vc<mint>inv_table{0,1};
        while((int)inv_table.size()<=this->size()){
            int i=inv_table.size();
            inv_table.push_back(-inv_table[mint::get_mod()%i]*mint(mint::get_mod()/i));
        }
        poly res(this->size()+1);
        rep(i,this->size())res[i+1]=(*this)[i]*inv_table[i+1];
        return res;
    }
    poly log(int deg)const{
        if(deg==-1)deg=this->size();
        assert(this->size()&&(*this)[0]==1);
        return (this->diff().pre(deg)*this->inv(deg)).integral().pre(deg);
    }
    poly exp(int deg=-1)const{
        assert((*this).size()&&(*this)[0]==0); 
        if(deg==-1)deg=this->size();
        static vc<mint>inv_table{0,1};
        while((int)inv_table.size()<=max((int)this->size(),deg)*2){
            int i=inv_table.size();
            inv_table.push_back(-inv_table[mint::get_mod()%i]*mint(mint::get_mod()/i));
        }
        poly res{1},h{1};
        for(int len=1;len<deg;len*=2){
            int nxt=len*2;
            mint inv=1/mint(nxt);
            poly G=res;G.resize(nxt);BF(G);
            poly H=h;H.resize(nxt);BF(H);
            poly V=G;
            rep(i,nxt)V[i]*=H[i];
            IBF(V);rep(i,nxt)V[i]*=inv;
            for(int i=0;i<len;++i)V[i]=0;REP(i,len,nxt)V[i]=-V[i];
            BF(V);
            poly g_prime(nxt);
            rep(i,len-1)g_prime[i]=res[i+1]*(i+1);
            BF(g_prime);
            poly f_prime(nxt);
            rep(i,len)if(i+1<(int)this->size())f_prime[i]=(*this)[i+1]*(i+1);
            BF(f_prime);
            poly w_prime(nxt);
            rep(i,nxt)w_prime[i]=g_prime[i]*H[i]+f_prime[i]*V[i];
            IBF(w_prime);rep(i,nxt)w_prime[i]*=inv;
            for(int i=nxt-1;i>=len;--i){
                mint fi=(i<(int)this->size())?(*this)[i]:0;
                w_prime[i]=fi-w_prime[i-1]*inv_table[i];
            }
            for(int i=0;i<len;++i)w_prime[i]=0;
            BF(w_prime);
            rep(i,nxt)G[i]*=w_prime[i];
            IBF(G);rep(i,nxt)G[i]*=inv;
            res.resize(nxt);
            REP(i,len,nxt)res[i]=G[i];
            if(nxt<deg){
                rep(i,nxt)H[i]*=(V[i]-w_prime[i]);
                IBF(H);rep(i,nxt)H[i]*=inv;
                h.resize(nxt);
                REP(i,len,nxt)h[i]=H[i];
            }
        }
        res.resize(deg);
        return res;
    }
    poly pow(ll m,int deg=-1)const{
        if(deg==-1)deg=this->size();
        if(m==0){poly res(deg);res[0]=1;return res;}
        rep(i,this->size()){
            if(m*i>deg)return poly(deg);
            if((*this)[i].val){
                auto target=(*this)>>i;
                mint coef=mint((*this)[i]);
                mint inv=1/coef;
                rep(i,target.size())target[i]*=inv; 
                return ((m*target.log(deg)).exp(deg)*mint(coef).pow(m))<<(i*m);
            }
        }
        return poly(deg);
    }
    void extend(int n){
        if(this->size()<n)this->resize(n);
    }
    poly shrink(){
        auto res=(*this);
        while(res.size()&&res.back()==0)res.pop_back();
        return res;
    }
    pair<poly,poly>div(poly f)const{
        if(this->size()<f.size()){ 
            return {{},(*this)}; 
        }
        int qsize=this->size()-f.size()+1;
        auto rthis=*this;reverse(all(rthis));
        auto rf=f;reverse(all(rf));
        auto rq=(rthis.pre(qsize)*rf.inv(qsize)).pre(qsize);
        reverse(all(rq));
        return {rq,(*this-rq*f).shrink()};
    }
    poly div_only(poly f)const{
        if(this->size()<f.size()){ 
            return {{}}; 
        }
        int qsize=this->size()-f.size()+1;
        auto rthis=*this;reverse(all(rthis));
        auto rf=f;reverse(all(rf));
        auto rq=(rthis.pre(qsize)*rf.inv(qsize)).pre(qsize);
        reverse(all(rq));
        return rq;
    }
    optional<poly> sqrt(int deg=-1)const{
        if(deg==-1)deg=this->size();
        if((this)->size()==0)return poly(deg);
        if((*this)[0]==0){
            REP(i,1,this->size()){
                if((*this)[i].val){
                    if(i%2)return nullopt; 
                    if(deg-i/2<=0)break;
                    auto res=((*this)>>i).sqrt(deg-i/2);
                    if(!res.has_value())return nullopt;
                    auto ret=res.value();
                    ret<<=(i/2);
                    ret.resize(deg);
                    return ret;
                }
            }
            return poly(deg);
        }
        ll s=mod_sqrt((*this)[0].val,mint::get_mod());
        if(s==-1)return nullopt;
        poly res{s};
        mint inv=1/mint(2);
        for(int i=1;i<deg;i*=2){
            res=(res+(*this).pre(i<<1)*res.inv(i<<1))*inv;
        }
        return res.pre(deg);
    }
    //f(x) -> f(vx)
    poly substitute(mint v){
        mint coef=1;
        poly nxt(*this);rep(i,nxt.size()){
            nxt[i]*=coef;
            coef*=v;
        }
        return nxt;
    }
};
template<class mint>
FormalPowerSeries(vc<mint>)->FormalPowerSeries<mint>;
template<class mint>
using fps=FormalPowerSeries<mint>;
template<class mint>
FormalPowerSeries<mint>to_fps(vc<mint> v){
    FormalPowerSeries<mint>res(v.size());rep(i,v.size())res[i]=v[i];
    return res;
}
template<class mint>
FormalPowerSeries<mint>to_fps(FormalPowerSeries<mint> v){
    return v;
}
template<class mint>
vc<mint>to_vec(FormalPowerSeries<mint> v){
    vc<mint>res(v.size());rep(i,v.size())res[i]=v[i];
    return res;
}
template<class mint>
vc<mint>to_vec(vc<mint> v){
    return v;
}
template<class mint>
FormalPowerSeries<mint> all_prod(vc<FormalPowerSeries<mint>> v){
    assert(mint::get_mod());
    using poly=FormalPowerSeries<mint>;
    if(v.empty())return {1};
    auto cmp=[&](auto&a,auto&b){return a.size()>b.size();};
    priority_queue<poly,vc<poly>,decltype(cmp)>pq(cmp);
    for(auto&p:v)pq.push(std::move(p));
    while(pq.size()>=2){
        auto p1=std::move(pq.top());pq.pop();
        auto p2=std::move(pq.top());pq.pop();
        pq.push(std::move(p1*p2));
    }
    return pq.top();
}
template<class mint>
FormalPowerSeries<mint> all_prod(vc<vc<mint>> v){
    vc<FormalPowerSeries<mint>> ps;
    ps.reserve(v.size());
    for(auto&p:v)ps.push_back(std::move(p));
    return all_prod(ps);
}
template<class mint>
struct SubproductTree{
    using poly=FormalPowerSeries<mint>;
    int M;
    vc<mint> queries;
    vc<poly> T;
    bool built;
    SubproductTree(int n=0):built(false){
        assert(mint::get_mod());
        queries.reserve(n);
    }
    void add_query(mint x){
        queries.push_back(x);
    }
    void build_dfs(int node,int l,int r){
        if(r-l==1){
            T[node]=poly{mint(1),-queries[l]};
            return;
        }
        int m=(l+r)/2;
        build_dfs(2*node,l,m);
        build_dfs(2*node+1,m,r);
        T[node]=T[2*node]*T[2*node+1];
    }
    void build_tree(){
        M=queries.size();
        if(M==0)return;
        T.assign(4*M,poly{});
        build_dfs(1,0,M);
        built=true;
    }
    vc<mint> middle_product(const vc<mint>& A,const vc<mint>& B){
        int n=A.size();
        int m=B.size();
        if(m==0)return vc<mint>(n+1,mint(0));
        int S=1;while(S<n)S*=2;
        vc<mint> a=A;a.resize(S,mint(0));
        vc<mint> b(S,mint(0));
        for(int i=0;i<m;++i)b[i]=B[m-1-i];
        
        atcoder::internal::butterfly(a);
        atcoder::internal::butterfly(b);
        for(int i=0;i<S;++i)a[i]*=b[i];
        atcoder::internal::butterfly_inv(a);
        
        mint invS=mint(1)/mint(S);
        vc<mint> res(n-m+1);
        for(int i=0;i<n-m+1;++i)res[i]=a[i+m-1]*invS;
        return res;
    }

    void evaluate(int node,int l,int r,const vc<mint>& U,vc<mint>& res){
        if(r-l==1){
            res[l]=U[0];
            return;
        }
        int m=(l+r)/2;
        
        const poly& T_left=T[2*node];
        const poly& T_right=T[2*node+1];
        
        int n=U.size();
        int m_l=T_left.size();
        int m_r=T_right.size();
        
        int S=1;while(S<n)S*=2;
        
        vc<mint> u_ntt=U;u_ntt.resize(S,mint(0));
        atcoder::internal::butterfly(u_ntt);
        
        vc<mint> t_r_ntt(S,mint(0));
        for(int i=0;i<m_r;++i)t_r_ntt[i]=T_right[m_r-1-i];
        atcoder::internal::butterfly(t_r_ntt);
        
        vc<mint> u_l(S);
        for(int i=0;i<S;++i)u_l[i]=u_ntt[i]*t_r_ntt[i];
        atcoder::internal::butterfly_inv(u_l);
        
        vc<mint> t_l_ntt(S,mint(0));
        for(int i=0;i<m_l;++i)t_l_ntt[i]=T_left[m_l-1-i];
        atcoder::internal::butterfly(t_l_ntt);
        
        vc<mint> u_r(S);
        for(int i=0;i<S;++i)u_r[i]=u_ntt[i]*t_l_ntt[i];
        atcoder::internal::butterfly_inv(u_r);
        mint invS=mint(1)/mint(S);
        vc<mint> Ul(n-m_r+1);
        for(int i=0;i<n-m_r+1;++i)Ul[i]=u_l[m_r-1+i]*invS;
        vc<mint> Ur(n-m_l+1);
        for(int i=0;i<n-m_l+1;++i)Ur[i]=u_r[m_l-1+i]*invS;
        evaluate(2*node,l,m,Ul,res);
        evaluate(2*node+1,m,r,Ur,res);
    }
    vc<mint> calc(const poly& target){
        if(!built)build_tree();
        if(M==0)return {};
        int N=target.size();
        if(N==0)return vc<mint>(M,mint(0));
        poly V=T[1].inv(N);
        vc<mint> F(target.begin(),target.end());
        F.resize(N+M-1,mint(0));
        vc<mint> U=middle_product(F,V);
        vc<mint> res(M);
        evaluate(1,0,M,U,res);
        return res;
    }
};

template<class mint>
vc<mint> multipoint_evaluation(std::type_identity_t<FormalPowerSeries<mint>> f,vc<mint> query){
    assert(mint::get_mod());
    SubproductTree<mint> st(query.size());
    for(auto& x:query)st.add_query(x);
    auto ans=st.calc(f);
    return ans;
}
//f(a),f(ar),...,f(ar^{m-1})
template<class mint>
vc<mint>chirp_z(std::type_identity_t<FormalPowerSeries<mint>>f,mint a,mint r,int m){
    assert(mint::get_mod());
    if(m==0)return {};
    if(r==0){
        vc<mint>ans(m);
        mint coef=1;
        rep(i,f.size()){
            ans[0]+=f[i]*coef;
            coef*=a;
        }
        REP(i,1,m)ans[i]=f[0];
        return ans;
    }
    FormalPowerSeries<mint> A(f.size()),B(f.size()+m);
    vc<mint>ir(f.size()+m+1),rp(f.size()+m+1);
    mint tmp=1;mint IR=1;
    mint inv_r=1/r;
    rep(i,ir.size()){
        ir[i]=tmp;
        tmp*=IR;
        IR*=inv_r;
    }
    tmp=1;IR=1;
    rep(i,rp.size()){
        rp[i]=tmp;
        tmp*=IR;
        IR*=r;
    }
    mint AA=1;
    rep(i,f.size()){
        A[f.size()-i-1]=f[i]*ir[i]*AA;
        AA*=a;
    }
    rep(i,f.size()+m)B[i]=rp[i];
    auto res=A*B;
    vc<mint>ans(m);
    rep(i,m){
        ans[i]=res[i+f.size()-1]*ir[i];
    }
    return ans;
}

template<class mint>
FormalPowerSeries<mint>interporate(vc<mint>x,vc<mint>y){
    assert(mint::get_mod());
    assert(x.size()==y.size());
    int n=x.size();
    int sz=1;
    while(sz<n)sz*=2;
    vc<FormalPowerSeries<mint>>tree(sz*2,{1});
    rep(i,n)tree[sz+i]={-x[i],1};
    DREP(i,sz-1,1)tree[i]=tree[i*2]*tree[i*2+1];
    auto gdeval=multipoint_evaluation(tree[1].diff(),x);
    vc<mint>a(n);rep(i,n)a[i]=y[i]/gdeval[i];
    auto dfs=[&](auto&dfs,int l,int r,int idx)->FormalPowerSeries<mint>{
        if(r-l==1){
            if(l>=n)return {0};
            return{a[l]};
        }
        int mid=(l+r)>>1;
        auto L=dfs(dfs,l,mid,idx*2);
        auto R=dfs(dfs,mid,r,idx*2+1);
        return L*tree[idx*2+1]+R*tree[idx*2];
    };
    auto ans=dfs(dfs,0,sz,1);
    return ans;
}
//f(a)=y_0 f(ar)=y_1 .... 
template<class mint>
vc<mint>geo_interporate(mint a,mint r,vc<mint>y){
    assert(mint::get_mod());
    
    int n=y.size();
    if(n==0)return {};
    if(n==1)return {y[0]};
    if(r==0){
        mint c0=y[1];
        mint c1=(y[0]-y[1])/a;
        return {c0,c1};
    }
    //(x-a)(x-ar)...(x-ar^{n-1})
    auto get=[&](auto&get,int n)->FormalPowerSeries<mint>{
        if(n==0)return {1};
        auto down=get(get,n/2);
        auto res=down*down.substitute(1/r.pow(n/2))*r.pow(1ll*(n/2)*(n/2));
        if(n%2)res*={-a*r.pow(n-1),1};
        return res;
    };
    vc<mint>x(n);x[0]=a;REP(i,1,n)x[i]=x[i-1]*r;
    auto all_mul=get(get,n);
    auto gdeval=chirp_z(all_mul.diff(),a,r,n);
    FormalPowerSeries<mint>A(n);rep(i,n)A[i]=y[i]/gdeval[i];
    auto coef=chirp_z(-A,r.inv(),r.inv(),n);
    FormalPowerSeries<mint>C(n);rep(i,n)C[i]=coef[i];
    C=C.substitute(1/a);C/=a;
    return (C*all_mul).pre(n);
}
template<class mint>
FormalPowerSeries<mint>taylor_shift(FormalPowerSeries<mint>f,int c){
    assert(mint::get_mod());
    Binom<mint>bin;bin.build(f.size()+2);
    vc<mint>cp(f.size()+1);cp[0]=1;REP(i,1,f.size()+1)cp[i]=cp[i-1]*c;
    rep(i,f.size())f[i]*=bin.fact(i);
    FormalPowerSeries<mint>rc(f.size());rep(i,f.size())rc[i]=cp[f.size()-i-1]*bin.invfact(f.size()-i-1);
    auto ans=(f*rc);
    ans=FormalPowerSeries<mint>(ans.begin()+f.size()-1,ans.end());
    rep(i,f.size())ans[i]*=bin.invfact(i);
    return ans;
}
template<class F>
auto taylor_shift(F f,int c)->FormalPowerSeries<typename F::value_type>{
    using mint=typename F::value_type;
    return taylor_shift(FormalPowerSeries<mint>(std::move(f)),c);
}
