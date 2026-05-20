#pragma once
template<class T,int B>
struct PersistentArray{
    struct Node{
        array<Node*,B>child;
        T*val;
        Node():val(0){child.fill(nullptr);}
        Node(T x){
            val=new T(x);
            child.fill(nullptr);
        }
    };
    int b_;
    int n_;
    Node*build(int n,T x){
        assert(n>=0);
        n_=n;
        Node*root=new Node();
        int b=1;
        while(b<n)b*=B;
        auto dfs=[&](auto&dfs,int l,int r,Node*now,int b)->void{
            if(b==1){
                now->val=new T(x);
                return;
            }
            rep(i,B){
                int nl=l+i*b/B;
                int nr=l+(i+1)*b/B;
                if(nl<r){
                    now->child[i]=new Node();
                    dfs(dfs,nl,min(nr,n),now->child[i],b/B);
                }
            }
            return;
        };
        b_=b;
        dfs(dfs,0,n,root,b);
        return root;
    }
    Node*change(int pos,T x,Node*root){
        assert(root);
        assert(0<=pos&&pos<n_);
        int b=b_;
        auto dfs=[&](auto&dfs,int l,int r,Node*now,int b)->Node*{
            if(b==1){
                return new Node(x);
            }
            int ni=(pos-l)/(b/B);
            Node*nw=new Node();
            nw->child=now->child;
            nw->child[ni]=dfs(dfs,l+ni*(b/B),min(r,l+(ni+1)*(b/B)),now->child[ni],b/B);
            return nw;
        };
        return dfs(dfs,0,n_,root,b);
    }
    T get(int pos,Node*root){
        assert(root);
        assert(0<=pos&&pos<n_);
        int b=b_;
        auto dfs=[&](auto&dfs,int l,int r,Node*now,int b)->T{
            if(r-l==1){
                return *now->val;
            }
            int ni=(pos-l)/(b/B);
            return dfs(dfs,l+ni*(b/B),l+(ni+1)*(b/B),now->child[ni],b/B);
        };
        return dfs(dfs,0,n_,root,b);
    }
};
