#pragma  once
template<class Info,class Tag>
struct PersistentLazySegtree{
    using value_type=typename Info::value_type;
    using lazy_type=typename Tag::lazy_type;
    struct Node{
        value_type val;
        lazy_type lazy;
        int l,r;
        Node():val(Info::e()),lazy(Tag::id()),l(0),r(0){}
    };
    //N=Q=10^5 > about 1.5e7
    static const int MAX_NODE=1.5e7;
    static Node inline pool[MAX_NODE];
    int ptr=1;
    int N;
    int LOG;
    vc<value_type>db;
    int new_node(const Node&n){
        assert(ptr<MAX_NODE);
        pool[ptr]=n;
        return ptr++;
    }
    int common(int l1,int r1,int l2,int r2){
        return max(int(0),min(r1,r2)-max(l1,l2));
    }
    void eval(int x){
        if(pool[x].lazy==Tag::id())return;
        pool[x].l=new_node(pool[pool[x].l]);
        pool[x].r=new_node(pool[pool[x].r]);
        pool[pool[x].l].lazy=Tag::Merge(pool[pool[x].l].lazy,pool[x].lazy);
        pool[pool[x].r].lazy=Tag::Merge(pool[pool[x].r].lazy,pool[x].lazy);
        pool[pool[x].l].val=Tag::Apply(pool[pool[x].l].val,pool[x].lazy);
        pool[pool[x].r].val=Tag::Apply(pool[pool[x].r].val,pool[x].lazy);
        pool[x].lazy=Tag::id();
    }
    PersistentLazySegtree():ptr(1),N(0),LOG(0){}
    int build(int n){
        assert(n>=0);
        LOG=1;
        while((1<<LOG)<n)LOG++;
        N=1<<LOG;
        db.resize(LOG+1);
        db[0]=Info::leaf();
        rep(i,LOG)db[i+1]=Info::op(db[i],db[i]);
        int root=new_node({});
        pool[root].val=db.back();
        return root;
    }
    int set(int i,value_type val,int root){
        assert(0<=i&&i<N);
        assert(0<root&&root<ptr);
        auto dfs=[&](auto&dfs,int l,int r,int root,int depth)->int {
            if(r-l==1){
                int x=new_node(pool[root]);
                pool[x].val=val;
                return x;
            }
            int x=new_node(pool[root]);
            eval(x);
            int mid=(l+r)>>1;
            if(l<=i&&i<mid)pool[x].l=dfs(dfs,l,mid,pool[x].l,depth-1);
            else pool[x].r=dfs(dfs,mid,r,pool[x].r,depth-1);
            pool[x].val=Info::op(pool[pool[x].l].val,pool[pool[x].r].val);
            return x;
        };
        return dfs(dfs,0,N,root,LOG);
    }
    value_type prod(int l,int r,int root){
        assert(0<=l&&l<=r&&r<=N);
        assert(0<root&&root<ptr);
        auto dfs=[&](auto&dfs,int sl,int sr,int root,int depth,lazy_type x)->value_type{
            if(sr<=l)return Info::e();
            if(r<=sl)return Info::e();
            if(l<=sl&&sr<=r)return Tag::Apply(pool[root].val,x);
            int mid=(sl+sr)>>1;
            value_type res=Info::e();
            x=Tag::Merge(pool[root].lazy,x);
            if(pool[root].l)res=Info::op(res,dfs(dfs,sl,mid,pool[root].l,depth-1,x));
            else res=Info::op(res,Tag::Apply(Info::bylen(common(sl,mid,l,r),db),x));
            if(pool[root].r)res=Info::op(res,dfs(dfs,mid,sr,pool[root].r,depth-1,x));
            else res=Info::op(res,Tag::Apply(Info::bylen(common(mid,sr,l,r),db),x));
            return res;
        };
        return dfs(dfs,0,N,root,LOG,Tag::id());
    }
    int apply(int l,int r,lazy_type x,int root){
        assert(0<=l&&l<=r&&r<=N);
        assert(0<root&&root<ptr);
        auto dfs=[&](auto&dfs,int sl,int sr,int root,int depth)->int{
            int nr;
            if(sr<=l)return root;
            if(r<=sl)return root;
            nr=new_node(pool[root]);
            if(l<=sl&&sr<=r){
                pool[nr].lazy=Tag::Merge(pool[nr].lazy,x);
                pool[nr].val=Tag::Apply(pool[nr].val,x);
                return nr;
            }
            eval(nr);
            int mid=(sl+sr)>>1;
            pool[nr].l=dfs(dfs,sl,mid,pool[nr].l,depth-1);
            pool[nr].r=dfs(dfs,mid,sr,pool[nr].r,depth-1);
            pool[nr].val=Info::op(pool[pool[nr].l].val,pool[pool[nr].r].val);
            return nr;
        };
        return dfs(dfs,0,N,root,LOG);
    }
    int replace(int l,int r,int r1,int r2){
        assert(0<=l&&l<=r&&r<=N);
        assert(0<r1&&r1<ptr);
        assert(0<r2&&r2<ptr);
        auto dfs=[&](auto&dfs,int sl,int sr,int r1,int r2,int depth)->int{
            if(sr<=l)return r1;
            if(r<=sl)return r1;
            if(l<=sl&&sr<=r){
                int nroot=new_node(pool[r2]);
                return nroot;
            }
            int nroot=new_node(pool[r1]);
            eval(nroot);
            eval(r2);
            int mid=(sl+sr)>>1;
            pool[nroot].l=dfs(dfs,sl,mid,pool[nroot].l,pool[r2].l,depth-1);
            pool[nroot].r=dfs(dfs,mid,sr,pool[nroot].r,pool[r2].r,depth-1);
            pool[nroot].val=Info::op(pool[pool[nroot].l].val,pool[pool[nroot].r].val);
            return nroot;
        };
        return dfs(dfs,0,N,r1,r2,LOG);
    }
};
