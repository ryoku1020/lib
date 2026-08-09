#pragma once
template<class T,int depth>
struct BinaryTrie{
    struct Node{
        Node*l,*r;
        T size;
        Node():l(nullptr),r(nullptr),size(0){}
    };
    T all_size;
    T offset;
    Node*root;
    BinaryTrie(){
        root=new Node();
        all_size=0;
        offset=0;
    }
    T count(T val){
        assert(val>=0);
        assert(val<(T(1)<<depth));
        val^=offset;
        auto dfs=[&](auto&dfs,Node*now,T l,T r,int target)->T{
            if(r-l==1){
                return now->size;
            }
            T mid=(l+r)>>1;
            if((val<mid)){
                if(now->l==0)return 0;
                return dfs(dfs,now->l,l,mid,target-1);
            }else{
                if(now->r==0)return 0;
                return dfs(dfs,now->r,mid,r,target-1);
            }
        };
        return dfs(dfs,root,0,T(1)<<depth,depth-1);
    }
    T lessthan(T val){
        if(val<=0)return 0;
        if(val>=T(1)<<depth)return all_size;
        auto dfs=[&](auto&dfs,Node*now,T l,T r,int target)->T{
            if(now==0)return 0;
            if(r-l==1)return 0;
            T mid=(l+r)>>1;
            if(!(val>>target&1)){
                if(!(offset>>target&1))return dfs(dfs,now->l,l,mid,target-1);
                else return dfs(dfs,now->r,mid,r,target-1);
            }else{
                if(!(offset>>target&1)){
                    return (now->l?now->l->size:0)+dfs(dfs,now->r,mid,r,target-1);
                }else{
                    return (now->r?now->r->size:0)+dfs(dfs,now->l,l,mid,target-1);
                }
            }
        };
        return dfs(dfs,root,0,T(1)<<depth,depth-1);
    }
    void insert(T val,int x=1){
        assert(val>=0);
        assert(val<(T(1)<<depth));
        assert(all_size+x>=0);
        val^=offset;
        auto dfs=[&](auto&dfs,Node*now,T l,T r,int target)->void{
            if(r-l==1){
                now->size+=x;
                return;
            }
            T mid=(l+r)>>1;
            if((val<mid)){
                if(now->l==0)now->l=new Node();
                dfs(dfs,now->l,l,mid,target-1);
            }else{
                if(now->r==0)now->r=new Node();
                dfs(dfs,now->r,mid,r,target-1);
            }
            now->size+=x;
        };
        dfs(dfs,root,0,T(1)<<depth,depth-1);
        all_size+=x;
    }
    void all_xor(T x){
        assert(0<=x&&x<(T(1)<<depth));
        offset^=x;
    }
    T find_min(){
        assert(all_size);
        auto dfs=[&](auto&dfs,Node*now,T l,T r,int target)->T{
            if(r-l==1){
                return l^offset;
            }
            T mid=(l+r)>>1;
            if(!(offset>>target&1)){
                if(now->l&&now->l->size)return dfs(dfs,now->l,l,mid,target-1);
                else return dfs(dfs,now->r,mid,r,target-1);
            }else{
                if(now->r&&now->r->size)return dfs(dfs,now->r,mid,r,target-1);
                else return dfs(dfs,now->l,l,mid,target-1);
            }
        };
        return dfs(dfs,root,0,T(1)<<depth,depth-1);
    }
};
