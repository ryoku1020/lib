#pragma once
/*
struct X{
    using value_type=pair<mint,mint>;
    static value_type op(value_type a,value_type b){
        return {a.first*b.first,b.first*a.second+b.second};
    }
    static value_type e(){
        return {1,0};
    }
};*/
template<typename Info>
struct Segtree{
    using value_type=typename Info::value_type;
    vc<value_type>node;
    int N;
    int n;
    int lg;
    void update(int i){
        assert(0<=i&&i<n);
        node[i]=Info::op(node[i*2],node[i*2+1]);
    }
    Segtree(int N_=0,value_type leaf=Info::e()){
        assert(N_>=0);
        N=N_;
        n=1;
        lg=0;
        while(n<N)n*=2,++lg;
        node.resize(n*2,Info::e());
        REP(i,n,n+N)node[i]=leaf;
        DREP(i,n-1,1)update(i);
    }
    template<class F>
    Segtree(int N_,F f){
        assert(N_>=0);
        N=N_;
        n=1;
        lg=0;
        while(n<N)n*=2,++lg;
        node.resize(n*2,Info::e());
        for(int i=n;i<n+N;i++){
            node[i]=f(i-n);
        }
        DREP(i,n-1,1)update(i);
    }
    void push_back(value_type val){
        if(n==N){
            vc<value_type>vs(n+1);rep(i,n)vs[i]=node[i+n];
            vs[n]=val;
            (*this)=Segtree(N+1,[&](auto i){
                if(i<n+1)return vs[i];
                return Info::e();
            });
        }else{
            node[N+n]=val;
            int i=N+n;
            while(i>>=1)update(i);N++;
        }
    }
    void set(int i,value_type val){
        assert(0<=i&&i<N);
        node[i+=n]=val;
        while(i>>=1)update(i);
    }
    void apply(int i,value_type val){
        assert(0<=i&&i<N);
        i+=n;
        node[i]=Info::op(node[i],val);
        while(i>>=1)update(i);
    }
    value_type prod(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        l+=n,r+=n;
        value_type sml=Info::e(),smr=Info::e();
        while(l<r){
            if(l&1)sml=Info::op(sml,node[l++]);
            if(r&1)smr=Info::op(node[--r],smr);
            l/=2,r/=2;
        }
        return Info::op(sml,smr);
    }
    value_type all_prod(){
        return node[1];
    }
    template<class F>
    int max_right(int L,F f){
        assert(0<=L&&L<=N);
        int l=n+L,w=1;
        value_type ansL=Info::e();
        for(;L+w<=N;l>>=1,w<<=1)if(l&1){
            if(!f(Info::op(ansL,node[l])))break;
            ansL=Info::op(ansL,node[l++]);
            L+=w;
        }
        while(l<<=1,w>>=1){
            if(L+w<=N&&f(Info::op(ansL,node[l]))){
                ansL=Info::op(ansL,node[l++]);
                L+=w;
            }
        }
        return L;
    }
    template<class F>
    int min_left(int R,F f){
        assert(0<=R&&R<=N);
        int r=n+R,w=1;
        value_type ansR=Info::e();
        for(;R-w>=0;r>>=1,w<<=1)if(r&1){
            if(!f(Info::op(node[r-1],ansR)))break;
            ansR=Info::op(node[--r],ansR);
            R-=w;
        }
        while(r<<=1,w>>=1){
            if(R-w>=0&&f(Info::op(node[r-1],ansR))){
                ansR=Info::op(node[r-1],ansR);
                R-=w;
                r--;
            }
        }
        return R;
    }
};
