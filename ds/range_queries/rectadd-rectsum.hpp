#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class T>
struct rectadd_rectsum{
    struct inner_rectadd_pointsum{
        vc<tuple<ll,ll,ll,ll,array<T,4>>>ws;
        //[l,r) x [d,u)
        void add_rect(ll l,ll r,ll d,ll u,array<T,4>w){
            ws.pb({l,r,d,u,w});
        }
        vc<pll>qs;
        void add_query(ll x,ll y){
            qs.pb({x,y});
        }
        vc<array<T,4>>work()const{
            vc<array<T,4>>res(qs.size());
            if(ws.empty()||qs.empty())return res;
            struct point{
                ll x,y;
                int idx;
            };
            vc<point>ps;
            ps.reserve(qs.size());
            rep(i,qs.size()){
                auto [x,y]=qs[i];
                ps.pb({x,y,int(i)});
            }
            sort(all(ps),[](const point&a,const point&b){
                return a.x<b.x;
            });
            vc<ll>xs;
            xs.reserve(qs.size());
            for(auto&p:ps){
                if(xs.empty()||xs.back()!=p.x)xs.pb(p.x);
                p.x=xs.size()-1;
            }
            struct event{
                ll y;
                int l,r;
                array<T,4>w;
            };
            vc<event>es;
            es.reserve(ws.size()*2);
            for(auto[l,r,d,u,w]:ws){
                if(l>=r||d>=u)continue;
                int L=lower_bound(all(xs),l)-xs.begin();
                int R=lower_bound(all(xs),r)-xs.begin();
                if(L==R)continue;
                es.pb({d,L,R,w});
                es.pb({u,L,R,{-w[0],-w[1],-w[2],-w[3]}});
            }
            sort(all(es),[](const event&a,const event&b){
                return a.y<b.y;
            });
            sort(all(ps),[](const point&a,const point&b){
                return a.y<b.y;
            });
            vc<array<T,4>>bit(xs.size()+1);
            auto add=[&](int I,const array<T,4>&f){
                for(int i=I+1;i<=int(xs.size());i+=(i&-i)){
                    rep(j,4)bit[i][j]+=f[j];
                }
            };
            auto sm=[&](int R){
                array<T,4>res{};
                for(int i=R;i>0;i-=(i&-i)){
                    rep(j,4)res[j]+=bit[i][j];
                }
                return res;
            };
            int j=0;
            for(auto[x,y,idx]:ps){
                while(j<(int)es.size()&&es[j].y<=y){
                    auto[a,l,r,w]=es[j++];
                    add(l,w);add(r,{-w[0],-w[1],-w[2],-w[3]});
                }
                res[idx]=sm(x+1);
            }
            return res;
        }
    };
    vc<tuple<ll,ll,T>>ws;
    //[l,r) \times [d,u)
    void add_w(ll l,ll r,ll d,ll u,T w){
        ws.pb({l,d,w});
        ws.pb({r,u,w});
        ws.pb({l,u,-w});
        ws.pb({r,d,-w});
    }
    vc<array<ll,4>>qs;
    ll idx=0;
    //[l,r) [d,u)
    void add_query(ll l,ll r,ll d,ll u){
        qs.pb({r,u,idx,1});
        qs.pb({l,d,idx,1});
        qs.pb({r,d,idx,-1});
        qs.pb({l,u,idx,-1});
        idx+=1;
    }
    vc<T>work(){
        vc<T>res(idx);
        inner_rectadd_pointsum rps;
        for(auto&[r,u,w]:ws){
            rps.add_rect(r,inf<ll>,u,inf<ll>,{w,-w*u,-w*r,w*u*r});
        }
        rep(i,qs.size()){
            rps.add_query(qs[i][0],qs[i][1]);
        }
        auto XY=rps.work();
        rep(i,qs.size()){
            ll idx=qs[i][2],coef=qs[i][3];
            res[idx]+=XY[i][0]*coef*qs[i][0]*qs[i][1];
            res[idx]+=XY[i][1]*coef*qs[i][0];
            res[idx]+=XY[i][2]*coef*qs[i][1];
            res[idx]+=XY[i][3]*coef;
        }
        return res;
    }
};
}
