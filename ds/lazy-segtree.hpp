#pragma once
template<class Info,class Tag,bool beats=false>
struct LazySegtree{
    using value_type=typename Info::value_type;
    using lazy_type=typename Tag::lazy_type;
    template<class T,class=void>
    struct has_commute{
        static constexpr bool value=false;
    };
    template<class T>
    struct has_commute<T,decltype((void)T::commute,void())>{
        static constexpr bool value=T::commute;
    };
    static constexpr bool commute=has_commute<Tag>::value;
    int N;
    int n;
    int lg;
    vc<value_type>node;
    vc<lazy_type>lazy;
    void build(int N_){
        assert(N_>=0);
        N=N_;
        lg=0;
        while((1<<lg)<N)lg++;
        n=1<<lg;
        node=vc<value_type>(n*2,Info::e());
        lazy=vc<lazy_type>(n,Tag::id());
    }
    LazySegtree(int N,value_type leaf=Info::e()){
        build(N);
        REP(i,n,n*2)node[i]=leaf;
        DREP(i,n-1,1)update(i);
    }
    LazySegtree(int N,vc<value_type> A){
        build(N);
        A.resize(n,Info::e());
        REP(i,n,n*2)node[i]=A[i-n];
        DREP(i,n-1,1)update(i);
    }
    template<class F>
    LazySegtree(int N,F f){
        build(N);
        REP(i,n,n*2){
            if(i-n<N)node[i]=f(i-n);
            else node[i]=Info::e();
        }
        DREP(i,n-1,1)update(i);
    }
    void all_apply(int k,lazy_type x){
        assert(0<=k&&k<n*2);
        node[k]=Tag::Apply(node[k],x);
        if(k<n){
            lazy[k]=Tag::Merge(lazy[k],x);
            if constexpr(beats){
                if(node[k].fail())push(k),update(k);
            }
        }
    }
    void push(int k){
        assert(0<=k&&k<n*2);
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=Tag::id();
    }
    void update(int i){
        assert(0<=i&&i<n*2);
        node[i]=Tag::Apply(Info::op(node[i*2],node[i*2+1]),lazy[i]);
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
        if constexpr(commute){
            auto dfs=[&](auto&dfs,int k,int sl,int sr,lazy_type x)->value_type{
                if(sr<=l||r<=sl)return Info::e();
                if(l<=sl&&sr<=r)return Tag::Apply(node[k],x);
                x=Tag::Merge(lazy[k],x);
                int mid=(sl+sr)>>1;
                return Info::op(dfs(dfs,k*2,sl,mid,x),dfs(dfs,k*2+1,mid,sr,x));
            };
            return dfs(dfs,1,0,n,Tag::id());
        }
        l+=n,r+=n;
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
    void apply(int l,int r,lazy_type x){
        assert(0<=l&&l<=r&&r<=N);
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
    void apply(int i,lazy_type x){
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
        value_type ansL=Info::e();
        for(;L+w<=N;l>>=1,w<<=1)if(l&1){
            if(!f(Info::op(ansL,node[l])))break;
            ansL=Info::op(ansL,node[l++]);
            L+=w;
        }
        while(w>1){
            if(0<l&&l<n)push(l);
            l<<=1,w>>=1;
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
        if(R>0)for(int i=lg;i;i--)push((n+R-1)>>i);
        int r=n+R,w=1;
        value_type ansR=Info::e();
        for(;R-w>=0;r>>=1,w<<=1)if(r&1){
            if(!f(Info::op(node[r-1],ansR)))break;
            ansR=Info::op(node[--r],ansR);
            R-=w;
        }
        while(w>1){
            if(0<r-1&&r-1<n)push(r-1);
            r<<=1,w>>=1;
            if(R-w>=0&&f(Info::op(node[r-1],ansR))){
                ansR=Info::op(node[r-1],ansR);
                R-=w;
                r--;
            }
        }
        return R;
    }
};
