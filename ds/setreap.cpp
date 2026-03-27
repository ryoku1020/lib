#pragma once
#include"../template.cpp"
template<class T>
struct setreap{
    struct Node{
        uint32_t lc,rc,pri;
        int size;
        T val;
    };
    vector<Node>pool;
    int pool_ptr;
    uint32_t root;
    static uint32_t get_rand(){
        static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
        uint32_t t=x^(x<<11);x=y;y=z;z=w;
        return w=(w^(w>>19))^(t^(t>>8));
    }
    setreap(int max_nodes=1500005){
        pool.resize(max_nodes);
        pool_ptr=1;
        root=0;
    }
    uint32_t update(uint32_t t){
        if(!t)return 0;
        pool[t].size=1;
        if(pool[t].lc)pool[t].size+=pool[pool[t].lc].size;
        if(pool[t].rc)pool[t].size+=pool[pool[t].rc].size;
        return t;
    }
    uint32_t new_node(T val){
        uint32_t res=pool_ptr++;
        pool[res].lc=pool[res].rc=0;
        pool[res].size=1;
        pool[res].pri=get_rand();
        pool[res].val=val;
        return res;
    }
    void build(vc<T>v){
        sort(all(v));
        v.erase(unique(all(v)),v.end());
        int n=v.size();
        if(n==0){
            root=0;
            return;
        }
        vc<uint32_t>pts(n);
        for(int i=0;i<n;i++)pts[i]=new_node(v[i]);
        vc<uint32_t>st;
        for(int i=0;i<n;i++){
            uint32_t last=0;
            while(!st.empty()&&pool[st.back()].pri<pool[pts[i]].pri){
                last=st.back();
                st.pop_back();
            }
            pool[pts[i]].lc=last;
            if(!st.empty())pool[st.back()].rc=pts[i];
            st.push_back(pts[i]);
        }
        root=st[0];
        auto dfs=[&](auto&self,uint32_t cur)->void{
            if(!cur)return;
            self(self,pool[cur].lc);
            self(self,pool[cur].rc);
            update(cur);
        };
        dfs(dfs,root);
    }
    uint32_t merge(uint32_t l,uint32_t r){
        if(!l)return r;
        if(!r)return l;
        if(pool[l].pri>pool[r].pri){
            pool[l].rc=merge(pool[l].rc,r);
            return update(l);
        }else{
            pool[r].lc=merge(l,pool[r].lc);
            return update(r);
        }
    }
    pair<uint32_t,uint32_t>split(uint32_t l,T k){
        if(!l)return {0,0};
        if(pool[l].val<k){
            auto res=split(pool[l].rc,k);
            pool[l].rc=res.first;
            return {update(l),res.second};
        }else{
            auto res=split(pool[l].lc,k);
            pool[l].lc=res.second;
            return {res.first,update(l)};
        }
    }
    void insert(T val){
        auto s1=split(root,val);
        auto s2=split(s1.second,val+1);
        if(!s2.first)s2.first=new_node(val);
        root=merge(s1.first,merge(s2.first,s2.second));
    }
    void erase(T val){
        auto s1=split(root,val);
        auto s2=split(s1.second,val+1);
        root=merge(s1.first,s2.second);
    }
    T next(T val){
        uint32_t now=root;
        T ans=-1;
        while(now){
            if(pool[now].val>=val){
                ans=pool[now].val;
                now=pool[now].lc;
            }else{
                now=pool[now].rc;
            }
        }
        return ans;
    }
    T prev(T val){
        uint32_t now=root;
        T ans=-1;
        while(now){
            if(pool[now].val<val){
                ans=pool[now].val;
                now=pool[now].rc;
            }else{
                now=pool[now].lc;
            }
        }
        return ans;
    }
    int size(){
        return root?pool[root].size:0;
    }
    int smaller(T val){
        uint32_t now=root;
        int count=0;
        while(now){
            if(pool[now].val<val){
                count+=1+(pool[now].lc?pool[pool[now].lc].size:0);
                now=pool[now].rc;
            }else{
                now=pool[now].lc;
            }
        }
        return count;
    }
    T kth(int k){
        if(k<0||k>=size())return -1;
        uint32_t now=root;
        while(now){
            int lsz=pool[now].lc?pool[pool[now].lc].size:0;
            if(k<lsz){
                now=pool[now].lc;
            }else if(k==lsz){
                return pool[now].val;
            }else{
                k-=lsz+1;
                now=pool[now].rc;
            }
        }
        return -1;
    }
};