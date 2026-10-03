#pragma once

template<class acted,bool beats=false>
struct lazy_segtree{
    using info=typename acted::info;
    using tag=typename acted::tag;
    using value_type=typename acted::value_type;
    using lazy_type=typename acted::lazy_type;
    template<class T,class=void>
    struct has_commute{
        static constexpr bool value=false;
    };
    template<class T>
    struct has_commute<T,decltype((void)T::commute,void())>{
        static constexpr bool value=T::commute;
    };
    static constexpr bool commute=has_commute<tag>::value;
    int N;
    int n;
    int lg;
    vc<value_type>node;
    vc<lazy_type>lazy;
    vc<int>len;
    void build(int N_){
        assert(N_>=0);
        N=N_;
        lg=0;
        while((1<<lg)<N)lg++;
        n=1<<lg;
        node=vc<value_type>(n*2,info::id());
        lazy=vc<lazy_type>(n,tag::id());
        len=vc<int>(n*2);
        REP(i,n,n*2)len[i]=(i-n<N);
        DREP(i,n-1,1)len[i]=len[i*2]+len[i*2+1];
    }
    lazy_segtree(int N,value_type leaf=info::id()){
        build(N);
        REP(i,n,n*2)node[i]=(i-n<N?leaf:info::id());
        DREP(i,n-1,1)update(i);
    }
    lazy_segtree(int N,vc<value_type> A){
        build(N);
        A.resize(n,info::id());
        REP(i,n,n*2)node[i]=A[i-n];
        DREP(i,n-1,1)update(i);
    }
    template<class F>requires is_invocable_r_v<value_type,F&,int>
    lazy_segtree(int N,F f){
        build(N);
        REP(i,n,n*2){
            if(i-n<N)node[i]=f(i-n);
            else node[i]=info::id();
        }
        DREP(i,n-1,1)update(i);
    }
    void all_apply(int k,lazy_type x){
        assert(0<=k&&k<n*2);
        node[k]=acted::act(node[k],x,len[k]);
        if(k<n){
            lazy[k]=tag::op(lazy[k],x);
            if constexpr(beats){
                if(node[k].fail())push(k),update(k);
            }
        }
    }
    void push(int k){
        assert(0<k&&k<n);
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=tag::id();
    }
    void update(int i){
        assert(0<i&&i<n);
        node[i]=acted::act(info::op(node[i*2],node[i*2+1]),lazy[i],len[i]);
    }
    void set(int i,value_type x){
        assert(0<=i&&i<N);
        i+=n;
        for(int j=lg;j;j--)push(i>>j);
        node[i]=x;
        for(int j=1;j<=lg;j++)update(i>>j);
    }
    value_type prod(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        if(l==r)return info::id();
        if constexpr(commute){
            auto dfs=[&](auto&dfs,int k,int sl,int sr,lazy_type x)->value_type{
                if(sr<=l||r<=sl)return info::id();
                if(l<=sl&&sr<=r)return acted::act(node[k],x,len[k]);
                x=tag::op(lazy[k],x);
                int mid=(sl+sr)>>1;
                return info::op(dfs(dfs,k*2,sl,mid,x),dfs(dfs,k*2+1,mid,sr,x));
            };
            return dfs(dfs,1,0,n,tag::id());
        }
        l+=n,r+=n;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        value_type sml=info::id(),smr=info::id();
        while(l<r){
            if(l&1)sml=info::op(sml,node[l++]);
            if(r&1)smr=info::op(node[--r],smr);
            l/=2,r/=2;
        }
        return info::op(sml,smr);
    }
    void apply(int l,int r,lazy_type x){
        assert(0<=l&&l<=r&&r<=N);
        if(l==r)return;
        l+=n,r+=n;
        if constexpr(!commute){
            for(int i=lg;i;i--){
                if(((l>>i)<<i)!=l)push(l>>i);
                if(((r>>i)<<i)!=r)push((r-1)>>i);
            }
        }
        int l2=l,r2=r;
        while(l2<r2){
            if(l2&1)all_apply(l2++,x);
            if(r2&1)all_apply(--r2,x);
            l2/=2,r2/=2;
        }
        for(int i=1;i<=lg;i++){
            if(((l>>i)<<i)!=l)update(l>>i);
            if(((r>>i)<<i)!=r)update((r-1)>>i);
        }
    }
    void applyat(int i,lazy_type x){
        assert(0<=i&&i<N);
        i+=n;
        if constexpr(!commute)for(int j=lg;j;j--)push(i>>j);
        all_apply(i,x);
        for(int j=1;j<=lg;j++)update(i>>j);
    }
    value_type all_prod(){
        return node[1];
    }
    template<class F>
    int max_right(int L,F f){
        assert(0<=L&&L<=N);
        if(L<N)for(int i=lg;i;i--)push((n+L)>>i);
        int l=n+L,w=1;
        value_type ansL=info::id();
        for(;L+w<=N;l>>=1,w<<=1)if(l&1){
            if(!f(info::op(ansL,node[l])))break;
            ansL=info::op(ansL,node[l++]);
            L+=w;
        }
        while(w>1){
            if(0<l&&l<n)push(l);
            l<<=1,w>>=1;
            if(L+w<=N&&f(info::op(ansL,node[l]))){
                ansL=info::op(ansL,node[l++]);
                L+=w;
            }
        }
        return L;
    }
    template<class F>
    int min_left(int R,F f){
        assert(0<=R&&R<=N);
        if(R>0)for(int i=lg;i;i--)push((n+R-1)>>i);
        int r=n+R,w=1;
        value_type ansR=info::id();
        for(;R-w>=0;r>>=1,w<<=1)if(r&1){
            if(!f(info::op(node[r-1],ansR)))break;
            ansR=info::op(node[--r],ansR);
            R-=w;
        }
        while(w>1){
            if(0<r-1&&r-1<n)push(r-1);
            r<<=1,w>>=1;
            if(R-w>=0&&f(info::op(node[r-1],ansR))){
                ansR=info::op(node[r-1],ansR);
                R-=w;
                r--;
            }
        }
        return R;
    }
};