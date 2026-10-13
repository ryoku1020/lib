#pragma once
#include"../../template.hpp"
#include"../sequence/BIT.hpp"
namespace ryoku{
template<class T>
struct rectadd_pointsum{
    vc<tuple<ll,ll,ll,ll,T>>ws;
    //[l,r) x [d,u)
    void add_rect(ll l,ll r,ll d,ll u,T w){
        ws.pb({l,r,d,u,w});
    }
    vc<pll>qs;
    void add_query(ll x,ll y){
        qs.pb({x,y});
    }
    vc<T>work()const{
        vc<T>res(qs.size());
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
            T w;
        };
        vc<event>es;
        es.reserve(ws.size()*2);
        for(auto[l,r,d,u,w]:ws){
            if(l>=r||d>=u)continue;
            int L=lower_bound(all(xs),l)-xs.begin();
            int R=lower_bound(all(xs),r)-xs.begin();
            if(L==R)continue;
            es.pb({d,L,R,w});
            es.pb({u,L,R,-w});
        }
        sort(all(es),[](const event&a,const event&b){
            return a.y<b.y;
        });
        sort(all(ps),[](const point&a,const point&b){
            return a.y<b.y;
        });
        binary_indexed_tree<T>bit(xs.size()+1);
        int j=0;
        for(auto[x,y,idx]:ps){
            while(j<(int)es.size()&&es[j].y<=y){
                auto[a,l,r,w]=es[j++];
                bit.range_add(l,r,w);
            }
            res[idx]=bit.get(x);
        }
        return res;
    }
};
}
