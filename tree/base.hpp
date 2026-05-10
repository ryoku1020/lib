#pragma once
#include"../template.hpp"
#include"../graph/base.hpp" 
struct Tree{
    using Graph=static_graph<0>;
    using edge=Graph::edge;
    mutable Graph g;
    mutable bool built_hld=false;
    int n;
    mutable vc<int>in,out,head,size_,par,depth,ord;
    Tree(int n):n(n),g(n,n-1){}
    void add_edge(int a,int b){
        assert(0<=a&&a<n&&0<=b&&b<n);
        g.add_edge(a,b);
    }
    bool is_to_par(auto&e)const{
        return par[e.from]==e.to;
    }
    int size()const{
        return n;
    }
    auto operator[](int u)const{
        return g[u];
    }
    auto operator[](int u){
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
        vc<int>st;
        st.reserve(n);
        st.push_back(root);
        while(!st.empty()){
            int u=st.back();
            st.pop_back();
            ord.push_back(u);
            auto s=g[u];
            rep(i,s.size()){
                int v=s[i].to;
                if(v==par[u])continue;
                par[v]=u;
                depth[v]=depth[u]+1;
                st.push_back(v);
            }
        }
        drep(i,ord.size()){
            int u=ord[i];
            auto s=g[u];
            int heavy=-1,par_id=-1;
            rep(j,s.size()){
                int v=s[j].to;
                if(v==par[u]){
                    par_id=j;
                    continue;
                }
                size_[u]+=size_[v];
                if(heavy==-1||size_[s[heavy].to]<size_[v])heavy=j;
            }
            if(heavy!=-1&&heavy!=0){
                swap(s[heavy],s[0]);
                if(par_id==0)par_id=heavy;
                else if(par_id==heavy)par_id=0;
            }
            if(par_id!=-1&&par_id+1!=s.size()){
                swap(s[par_id],s[s.size()-1]);
            }
        }
        ord.clear();
        fill(all(size_),0);
        int T=0;
        st.push_back(root);
        while(!st.empty()){
            int u=st.back();
            if(size_[u]==0){
                in[u]=T++;
                ord.push_back(u);
            }
            auto s=g[u];
            if(size_[u]==s.size()){
                out[u]=T;
                st.pop_back();
                continue;
            }
            auto&e=s[size_[u]++];
            if(e.to==par[u])continue;
            head[e.to]=(size_[u]==1?head[u]:e.to);
            st.push_back(e.to);
        }
        size_.clear();
        size_.shrink_to_fit();
    }
    auto heavy_edge(int u)const{
        build();
        auto s=g[u];
        int sz=s.size(),ce=(par[u]==-1?sz:sz-1);
        if(ce<=0)return span<const Graph::edge>{s.l,s.l};
        return span<const Graph::edge>{s.l,s.l+1};
    }
    auto light_edges(int u)const{
        build();
        auto s=g[u];
        int sz=s.size(),ce=(par[u]==-1?sz:sz-1);
        if(ce<=1)return span<const Graph::edge>{s.l,s.l};
        return span<const Graph::edge>{s.l+1,s.l+ce};
    }
    int lca(int a,int b)const{
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
        build();
        return depth[a]+depth[b]-2*depth[lca(a,b)];
    }
    int jumpup(int a,int k)const{
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
        build();
        int L=lca(s,t);
        int D=depth[s]+depth[t]-2*depth[L];
        if(depth[s]-depth[L]>=k){
            return jumpup(s,k);
        }else{
            return jumpup(t,D-k);
        }
    }   
    vc<pair<int,int>>Query(int s,int t)const{
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
        if(d[s]>d[t]){
            rs.push_back({I[s],I[t]});
        }else{
            rt.push_back({I[s],I[t]});
        }
        rs.reserve(rs.size()+rt.size());
        for(auto it=rt.rbegin();it!=rt.rend();++it)rs.push_back(*it);
        return rs;
    }
    pair<int,int>get_diameter()const{
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
