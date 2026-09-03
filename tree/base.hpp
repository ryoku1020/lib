#pragma once
#include"../graph/base.hpp" 
template<class T=unweighted>
struct tree{
    using Graph=static_graph<0,T>;
    using edge=typename Graph::edge;
    using cost_t=typename Graph::cost_t;
    mutable Graph g;
    mutable int built_hld=-1;
    int n;
    mutable vc<int>in,out,head,size_,par,depth,ord,cp,cp_root;
    tree(int n):n(n),g(n,n-1){}
    void add_edge(const edge&e){
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
    bool same(int a,int b)const{
        assert(0<=a&&a<n&&0<=b&&b<n);
        build();
        return cp[a]==cp[b];
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
    template<int disjoint=0>
    void build(int root=0)const{
        assert(0<=root&&root<n);
        if(built_hld!=-1){
            return;
        }
        built_hld=disjoint;
        in.resize(n);
        out.resize(n);
        head.resize(n);
        size_.assign(n,1);
        par.resize(n);
        depth.resize(n);
        ord.assign(n*(disjoint+1),-1);
        cp.assign(n,-1);
        cp_root.clear();
        int timer=0;
        auto dfs=[&](auto&dfs,int u,int v,int d,int c)->void{
            cp[u]=c;
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
                dfs(dfs,e.to,u,d,c);
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
        };
        auto visit=[&](int u){
            int c=cp_root.size();
            cp_root.pb(u);
            par[u]=-1;
            depth[u]=0;
            head[u]=u;
            dfs(dfs,u,-1,0,c);
        };
        visit(root);
        rep(u,n)if(cp[u]==-1)visit(u);
        {auto dfs=[&](auto&dfs,int u)->void{
            in[u]=timer;
            ord[timer++]=u;
            auto s=g[u];
            bool first=true;
            rep(i,s.size()){
                auto&e=s[i];
                if(e.to==par[u])continue;
                head[e.to]=first?head[u]:e.to;
                first=false;
                dfs(dfs,e.to);
            }
            if constexpr(disjoint)out[u]=timer++;
            else out[u]=timer;
        };
        for(auto u:cp_root)dfs(dfs,u);}
        rep(u,n){
            auto s=g[u];
            int ce=s.size()-(par[u]!=-1);
            if(ce>1)sort(s.begin()+1,s.begin()+ce,[&](const edge&a,const edge&b){return in[a.to]<in[b.to];});
        }
    }
    auto heavy_edge(int u)const{
        assert(0<=u&&u<n);
        build();
        auto s=g[u];
        int sz=s.size(),ce=(par[u]==-1?sz:sz-1);
        if(ce<=0)return span<const edge>{s.data(),s.data()};
        return span<const edge>{s.data(),s.data()+1};
    }
    auto light_edges(int u)const{
        assert(0<=u&&u<n);
        build();
        auto s=g[u];
        int sz=s.size(),ce=(par[u]==-1?sz:sz-1);
        if(ce<=1)return span<const edge>{s.data(),s.data()};
        return span<const edge>{s.data()+1,s.data()+ce};
    }
    int lca(int a,int b)const{
        assert(0<=a&&a<n&&0<=b&&b<n);
        build();
        auto&h=head;
        auto&d=depth;
        auto&p=par;
        if(cp[a]!=cp[b])return -1;
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
        int L=lca(a,b);
        if(L==-1)return -1;
        return depth[a]+depth[b]-2*depth[L];
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
        if(cp[s]!=cp[t]||k<0)return -1;
        int L=lca(s,t);
        int D=depth[s]+depth[t]-2*depth[L];
        if(D<k)return -1;
        if(depth[s]-depth[L]>=k){
            return jumpup(s,k);
        }else{
            return jumpup(t,D-k);
        }
    }   
    int to(int x,int y)const{
        assert(0<=x&&x<n&&0<=y&&y<n&&x!=y);
        build();
        if(cp[x]!=cp[y])return -1;
        if(in[y]<in[x]||out[x]<=in[y])return g[x].size()-1;
        auto s=g[x];
        int ce=s.size()-(par[x]!=-1);
        if(in[s[0].to]<=in[y]&&in[y]<out[s[0].to])return 0;
        int l=1,r=ce;
        while(l<r){
            int m=(l+r)/2;
            if(in[s[m].to]<=in[y])l=m+1;
            else r=m;
        }
        return l-1;
    }
    vc<pair<int,int>>query(int s,int t,bool edge=false)const{
        assert(0<=s&&s<n&&0<=t&&t<n);
        build();
        if(cp[s]!=cp[t])return {};
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
    pair<int,int>get_diameter(int v=0)const{
        assert(n>0);
        assert(0<=v&&v<n);
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
        int v1=find_farthest(v);
        int v2=find_farthest(v1);
        return {v1,v2};
    }
};
