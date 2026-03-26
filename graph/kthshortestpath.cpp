#pragma once
#include"base.cpp"
template<class T>
struct leftist_heap{
    leftist_heap*l,*r;
    int s;
    T val;
    int edge; 
    leftist_heap():l(nullptr),r(nullptr),s(0),edge(-1){}
    static leftist_heap*new_node(){
        return new leftist_heap();
    }
    static leftist_heap*meld(leftist_heap*a,leftist_heap*b){
        if(a==nullptr)return b;
        if(b==nullptr)return a;
        if(a->val>b->val)swap(a,b);
        auto na=new leftist_heap(*a);
        na->r=meld(na->r,b); 
        if(na->l==nullptr||(na->l->s<na->r->s))swap(na->l,na->r);
        na->s=(na->r==nullptr?0:na->r->s)+1;
        return na;
    }
    static leftist_heap*push(leftist_heap*a,T x,int f){
        leftist_heap*b=new leftist_heap();
        b->val=x;
        b->s=1;
        b->edge=f;
        return meld(a,b);
    }
};
template<class T,class G>
vc<T> kthshortestpath(G g,int s,int t,int k){
    auto INF=numeric_limits<T>::max();
    using Heap=leftist_heap<T>;
    int n=g.size();
    vc<int>used(g.edge_size());
    vc<T>md(n,INF);
    vc<int>pid(n,-1);
    md[t]=0;smpq<pair<T,int>>que;que.push({0,t});
    while(que.size()){
        auto [d,v]=que.top();que.pop();
        if(md[v]!=d)continue;
        if(pid[v]!=-1)used[pid[v]]=1;
        for(auto&e:g.inv(v)){
            if(chmin(md[e.to],md[e.from]+e.cost)){
                que.push({md[e.to],e.to});
                pid[e.to]=e.id;
            }
        }
    }
    vc<int>seen(n);
    vc<Heap*>heap(n+1);
    auto dfs=[&](auto&dfs,int u)->void{
        seen[u]=1;
        for(auto&e:g[u]){
            if(!used[e.id]){
                if(md[e.to]!=INF)heap[u]=Heap::push(heap[u],md[e.to]+e.cost-md[e.from],e.to);
            }
        }
        for(auto&e:g.inv(u)){
            if(seen[e.to])continue;
            if(used[e.id]){
                heap[e.to]=heap[u];
                dfs(dfs,e.to);
            }
        }
    };
    dfs(dfs,t);
    heap[n]=Heap::new_node();
    heap[n]->edge=s;
    auto comp=[](const pair<T,Heap*>&a,const pair<T,Heap*>&b){
        return a.first>b.first;
    };
    priority_queue<pair<T,Heap*>,vc<pair<T,Heap*>>,decltype(comp)>que2(comp);
    if(md[s]!=INF)que2.push({md[s],heap[n]});
    vc<T>len;
    while(que2.size()){
        auto [d,hp]=que2.top();que2.pop();
        len.pb(d);
        k--;
        if(k==0)break;
        if(hp->l)que2.push({d+hp->l->val-hp->val,hp->l});
        if(hp->r)que2.push({d+hp->r->val-hp->val,hp->r});
        if(heap[hp->edge])que2.push({d+heap[hp->edge]->val,heap[hp->edge]});
    }
    while(k)len.pb(-1),--k;
    return len;
}
