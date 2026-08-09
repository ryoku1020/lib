#pragma once
template<class Info,class sztype,bool is_persistent>
struct DynamicSegtree{
    using value_type=Info::value_type;
    struct Node{
        Node*l,*r;
        value_type val;
        Node():l(nullptr),r(nullptr),val(Info::e()){}
        Node(value_type x):l(nullptr),r(nullptr),val(x){}
    };
    int N,LOG;
    vc<value_type>db;
    DynamicSegtree(int n,value_type leaf=Info::e()){
        assert(n>=0);
        LOG=0;
        while((1<<LOG)<n)LOG++;
        N=1<<LOG;
        db.resize(LOG+1);
        db[0]=leaf;
        rep(i,LOG)db[i+1]=Info::op(db[i],db[i]);
    }
    Node*build(){return new Node(db[LOG]);}
    value_type get(Node*x,int depth){return x?x->val:db[depth];}
    sztype common(sztype l1,sztype r1,sztype l2,sztype r2){return max(sztype(0),min(r1,r2)-max(l1,l2));}
    Node*set(Node*now,sztype i,value_type x){
        assert(now);
        assert(0<=i&&i<N);
        auto dfs=[&](auto&dfs,sztype l,sztype r,int depth,Node*cur)->Node*{
            Node*next=is_persistent?new Node(*cur):cur;
            if(r-l==1){next->val=x;return next;}
            sztype mid=(l+r)>>1;
            if(i<mid){
                if(!next->l)next->l=new Node(db[depth-1]);
                next->l=dfs(dfs,l,mid,depth-1,next->l);
            }else{
                if(!next->r)next->r=new Node(db[depth-1]);
                next->r=dfs(dfs,mid,r,depth-1,next->r);
            }
            next->val=Info::op(get(next->l,depth-1),get(next->r,depth-1));
            return next;
        };
        return dfs(dfs,0,N,LOG,now);
    }
    value_type prod(Node*now,int L,int R){
        assert(0<=L&&L<=R&&R<=N);
        auto dfs=[&](auto&dfs,int l,int r,int depth,Node*cur)->value_type{
            if(L<=l&&r<=R)return get(cur,depth);
            if(R<=l||r<=L)return Info::e();
            int mid=(l+r)>>1;
            Node*lc=cur?cur->l:nullptr,*rc=cur?cur->r:nullptr;
            if(!is_persistent&&cur){
                if(!lc)lc=cur->l=new Node(db[depth-1]);
                if(!rc)rc=cur->r=new Node(db[depth-1]);
            }
            return Info::op(dfs(dfs,l,mid,depth-1,lc),dfs(dfs,mid,r,depth-1,rc));
        };
        return dfs(dfs,0,N,LOG,now);
    }
    template<class F>
    sztype max_right(Node*now,sztype L,F f){
        assert(0<=L&&L<=N);
        value_type ans=Info::e();
        auto dfs=[&](auto&dfs,sztype l,sztype r,int depth,Node*cur)->bool{
            if(r<=L)return true;
            if(L<=l&&f(Info::op(ans,get(cur,depth)))){
                ans=Info::op(ans,get(cur,depth));
                L=r;
                return true;
            }
            if(r-l==1){L=l;return false;}
            sztype mid=(l+r)>>1;
            Node*lc=cur?cur->l:nullptr,*rc=cur?cur->r:nullptr;
            return dfs(dfs,l,mid,depth-1,lc)&&dfs(dfs,mid,r,depth-1,rc);
        };
        dfs(dfs,0,N,LOG,now);
        return L;
    }
    template<class F>
    sztype min_left(Node*now,sztype R,F f){
        assert(0<=R&&R<=N);
        value_type ans=Info::e();
        auto dfs=[&](auto&dfs,sztype l,sztype r,int depth,Node*cur)->bool{
            if(R<=l)return true;
            if(r<=R&&f(Info::op(get(cur,depth),ans))){
                ans=Info::op(get(cur,depth),ans);
                R=l;
                return true;
            }
            if(r-l==1){R=r;return false;}
            sztype mid=(l+r)>>1;
            Node*lc=cur?cur->l:nullptr,*rc=cur?cur->r:nullptr;
            return dfs(dfs,mid,r,depth-1,rc)&&dfs(dfs,l,mid,depth-1,lc);
        };
        dfs(dfs,0,N,LOG,now);
        return R;
    }
};
