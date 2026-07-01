#pragma once
template<class Info>
struct AssignSegtree{
    using value_type=Info::value_type;
    vc<value_type>node;
    vc<int>lazy;
    int N,lg;
    void build(int n){
        assert(n>=0);
        ptr=0;
        lg=1;while((1<<lg)<n)lg++;
        N=1<<lg;
        node=vc<value_type>(N*2);
        lazy=vc<int>(N,-1);
    }
    AssignSegtree(int n,value_type leaf=Info::e()){
        build(n);
        REP(i,N,N+n)node[i]=leaf;
        REP(i,N+n,N*2)node[i]=Info::e();
        DREP(i,N-1,1)update(i);
    }
    void update(int i){
        assert(0<i&&i<N);
        node[i]=Info::op(node[i*2],node[i*2+1]);
        lazy[i]=-1;
    }
    void reset(){
        REP(i,1,N)push(i);
        DREP(i,N-1,1)update(i);
        mul.clear();
        ptr=0;
    }
    void all_apply(int k,int x){
        assert(0<=k&&k<N*2);
        if(x>=0){
            node[k]=mul[x][lg-tbit(k)];
            if(k<N)lazy[k]=x;
        }
    }
    void push(int k){
        assert(0<k&&k<N);
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=-1;
    }
    int ptr;
    vc<vc<value_type>>mul;
    void assign(int l,int r,value_type x){
        assert(0<=l&&l<=r&&r<=N);
        vc<value_type>push_{x};
        rep(i,lg)push_.push_back(Info::op(push_.back(),push_.back()));
        mul.push_back(push_);
        l+=N,r+=N;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        int l0=l,r0=r;
        while(l0<r0){
            if(l0&1)all_apply(l0++,ptr);
            if(r0&1)all_apply(--r0,ptr);
            l0/=2,r0/=2;
        }
        for(int i=1;i<=lg;i++){
            if(((l>>i)<<i)!=l)update(l>>i);
            if(((r>>i)<<i)!=r)update((r-1)>>i);
        }
        ptr++;
        //if(mul.size()*lg>=N)reset();
    }
    value_type prod(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        l+=N,r+=N;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        value_type sml=Info::e(),smr=Info::e();
        while(l<r){
            if(l&1)sml=Info::op(sml,node[l++]);
            if(r&1)smr=Info::op(node[--r],smr);
            l/=2,r/=2;
        }
        return Info::op(sml,smr);
    }
    void set(int i,value_type x){
        assert(0<=i&&i<N);
        i+=N;
        for(int j=lg;j;j--)push(i>>j);
        node[i]=x;
        for(int j=1;j<=lg;j++)update(i>>j);
    }
};
