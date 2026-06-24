#pragma once
#include"../graph/base.hpp" 
template<class T=Unweighted>
struct Tree{
    using Graph=StaticGraph<0,T>;
    using Edge=typename Graph::Edge;
    using cost_t=typename Graph::cost_t;
    mutable Graph g;
    mutable bool built_hld=false;
    int n;
    mutable vc<int>in,out,head,size_,par,depth,ord;
    Tree(int n):n(n),g(n,n-1){}
    void add_edge(const Edge&e){
        g.add_edge(e);
    }
    void add_edge(int a,int b,cost_t cost=1,int id=-1){
        g.add_edge(a,b,cost,id);
    }
    bool is_to_par(auto&e)const{
        return par[e.from]==e.to;
    }
    int size()const{
        return n;
    }
    auto operator[](int u)const{
        assert(0<=u&&u<n);
        return g[u];
    }
    auto operator[](int u){
        assert(0<=u&&u<n);
        return g[u];
    }
    template<int substract>
    void input(){
        rep(i,n-1){
            INT(a,b);
            a-=substract;
            b-=substract;
            g.add_edge(a,b);
        }
    }
    void build(int root=0)const{
        assert(0<=root&&root<n);
        if(built_hld)return;
        built_hld=1;
        in.resize(n);
        out.resize(n);
        head.resize(n);
        size_.assign(n,1);
        par.resize(n);
        depth.resize(n);
        ord.clear();
        ord.reserve(n);
        par[root]=-1;
        depth[root]=0;
        head[root]=root;
        int timer=0;
        auto dfs=[&](auto&dfs,int u,int v,int d)->void{
            depth[u]=d++;
            auto s=g[u];
            int heavy=-1,par_id=-1;
            rep(i,s.size()){
                auto&e=s[i];
                if(e.to==v){
                    par_id=i;
                    continue;
                }
                par[e.to]=u;
                dfs(dfs,e.to,u,d);
                size_[u]+=size_[e.to];
                if(heavy==-1||size_[s[heavy].to]<size_[e.to])heavy=i;
            }
            if(heavy!=-1&&heavy!=0){
                swap(s[heavy],s[0]);
                if(par_id==0)par_id=heavy;
                else if(par_id==heavy)par_id=0;
            }
            if(par_id!=-1&&par_id+1!=s.size()){
                swap(s[par_id],s[s.size()-1]);
            }
        };dfs(dfs,root,-1,0);
        {auto dfs=[&](auto&dfs,int u)->void{
            in[u]=timer++;
            ord.push_back(u);
            auto s=g[u];
            bool first=true;
            for(auto&e:s)if(e.to!=par[u]){
                head[e.to]=first?head[u]:e.to;
                first=false;
                dfs(dfs,e.to);
            }
            out[u]=timer;
        };dfs(dfs,root);}
    }
    auto heavy_edge(int u)const{
        assert(0<=u&&u<n);
        build();
        auto s=g[u];
        int sz=s.size(),ce=(par[u]==-1?sz:sz-1);
        if(ce<=0)return typename Graph::template Span<const Edge>{s.l,s.l};
        return typename Graph::template Span<const Edge>{s.l,s.l+1};
    }
    auto light_edges(int u)const{
        assert(0<=u&&u<n);
        build();
        auto s=g[u];
        int sz=s.size(),ce=(par[u]==-1?sz:sz-1);
        if(ce<=1)return typename Graph::template Span<const Edge>{s.l,s.l};
        return typename Graph::template Span<const Edge>{s.l+1,s.l+ce};
    }
    int lca(int a,int b)const{
        assert(0<=a&&a<n&&0<=b&&b<n);
        build();
        auto&h=head;
        auto&d=depth;
        auto&p=par;
        while(1){
            if(h[a]==h[b]){
                if(d[a]<d[b])return a;
                return b;
            }
            if(d[h[a]]<d[h[b]])swap(a,b);
            a=p[h[a]];
        }
    }
    int dist(int a,int b)const{
        assert(0<=a&&a<n&&0<=b&&b<n);
        build();
        return depth[a]+depth[b]-2*depth[lca(a,b)];
    }
    int jumpup(int a,int k)const{
        assert(0<=a&&a<n);
        build();
        if(k<0||depth[a]<k)return -1;
        auto&I=in;
        auto&H=head;
        auto&P=par;
        auto&O=ord;
        while(k>0){ 
            int x=I[a]-I[H[a]];
            if(x>=k){
                return O[I[a]-k];
            }
            k-=x+1;
            a=P[H[a]];
        }
        return a;
    }
    int jump(int s,int t,int k)const{
        assert(0<=s&&s<n&&0<=t&&t<n);
        build();
        int L=lca(s,t);
        int D=depth[s]+depth[t]-2*depth[L];
        if(depth[s]-depth[L]>=k){
            return jumpup(s,k);
        }else{
            return jumpup(t,D-k);
        }
    }   
    vc<pair<int,int>>Query(int s,int t,bool edge=false)const{
        assert(0<=s&&s<n&&0<=t&&t<n);
        build();
        auto&h=head;
        auto&d=depth;
        auto&I=in;
        auto&P=par;
        vc<pair<int,int>>rs,rt;
        while(h[s]!=h[t]){
            if(d[h[s]]>d[h[t]]){
                rs.push_back({I[s],I[h[s]]});
                s=P[h[s]];
            }else{
                rt.push_back({I[h[t]],I[t]});
                t=P[h[t]];
            }
        }
        if(s!=t||!edge){
            if(d[s]>d[t]){
                rs.push_back({I[s],I[t]+edge});
            }else{
                rt.push_back({I[s]+edge,I[t]});
            }
        }
        rs.reserve(rs.size()+rt.size());
        for(auto it=rt.rbegin();it!=rt.rend();++it)rs.push_back(*it);
        return rs;
    }
    pair<int,int>get_diameter()const{
        assert(n>0);
        auto find_farthest=[&](int from)->int{
            vc<int>d(n),p(n,-2),st(1,from);
            p[from]=-1;
            int far=from;
            while(!st.empty()){
                int u=st.back();
                st.pop_back();
                if(d[far]<d[u])far=u;
                for(auto&e:g[u])if(e.to!=p[u]){
                    p[e.to]=u;
                    d[e.to]=d[u]+1;
                    st.push_back(e.to);
                }
            }
            return far;
        };
        int v1=find_farthest(0);
        int v2=find_farthest(v1);
        return {v1,v2};
    }
};
