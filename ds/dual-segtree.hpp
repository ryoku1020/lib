#pragma  once
template<class X>
struct DualSegtree{
    using value_type=X::value_type;
    vc<value_type>lazy;
    vc<value_type>node;
    int n;
    int lg;
    DualSegtree(int N){
        assert(N>=0);
        lg=0;while((1<<lg)<N)lg++;
        n=1<<lg;
        lazy=vc<value_type>(n,X::e());
        node=vc<value_type>(n*2,X::e());
    }
    DualSegtree(int N,const vc<value_type>&v){
        assert(N>=0);
        lg=0;while((1<<lg)<N)lg++;
        n=1<<lg;
        lazy=vc<value_type>(n,X::e());
        node=vc<value_type>(n*2,X::e());
        build(v);
    }
    void build(const vc<value_type>&v){
        assert((int)v.size()<=n);
        rep(i,n)node[i+n]=v[i];
    }
    void set(int p,value_type x,bool is_first=false){
        assert(0<=p&&p<n);
        if(is_first==0){
            p+=n;
            for(int i=lg;i;i--)push(p>>i);
            node[p]=x;
        }else node[p+n]=x;
    }
    void all_apply(int k,value_type x){
        assert(0<=k&&k<n*2);
        node[k]=X::op(node[k],x);
        if(k<n)lazy[k]=X::op(lazy[k],x);
    }
    void push(int k){
        assert(0<k&&k<n);
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=X::e();
    }
    void apply(int l,int r,value_type x){
        assert(0<=l&&l<=r&&r<=n);
        l+=n,r+=n;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        while(l<r){
            if(l&1)all_apply(l++,x);
            if(r&1)all_apply(--r,x);
            l/=2,r/=2;
        }
    }
    value_type get(int p){
        assert(0<=p&&p<n);
        p+=n;
        for(int i=lg;i;i--)push(p>>i);
        return node[p];
    }
};
