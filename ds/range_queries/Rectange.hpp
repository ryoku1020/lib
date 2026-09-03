#include"../sequence/wavelet-matrix.hpp"
#include"../sequence/BIT.hpp"
template<class T,int D>
struct dynamic_rectangle_sum{
    wm_base<ll,D>wm;
    array<bit<T>,D>f;
    array<vc<int>,D>inv;
    vc<array<ll,3>>ps;
    vc<ll>xs;
    vc<ll>ys;

    void add_point(ll x,ll y,T w){
        xs.pb(x);
        ys.pb(y);
        ps.pb({x,y,(ll)w});
    }

    void build(){
        sort(all(ys));
        ys.erase(unique(all(ys)),ys.end());
        for(auto&[X,Y,w]:ps)Y=lower_bound(all(ys),Y)-ys.begin();
        sort(all(ps));
        xs.resize(ps.size());
        vc<ll>send(ps.size());
        rep(i,ps.size()){
            xs[i]=ps[i][0];
            send[i]=ps[i][1];
        }
        wm.build(send);
        wm.build_info([&](const vc<ll>&a,const vc<int>&idx,int bit){
            if(bit==D)return;
            inv[bit].assign(a.size(),0);
            vc<T>now_w(a.size());
            rep(i,a.size()){
                inv[bit][idx[i]]=i;
                now_w[i]=ps[idx[i]][2];
            }
            f[bit]=now_w;
        });
    }

    void add(ll x,ll y,T w){
        y=lower_bound(all(ys),y)-ys.begin();
        int itr=lower_bound(all(ps),array<ll,3>{x,y,numeric_limits<ll>::min()})-ps.begin();
        rep(i,D)f[i].add(inv[i][itr],w);
    }

    T iquery(int l,int r,ll d)const{
        if(d<=0)return 0;
        T ans=0;
        wm.walk(l,r,[&](auto node,auto child,auto go){
            if(!child.has)return;
            if(d>>node.bit&1){
                ans+=f[node.bit].sum(child.zero.l,child.zero.r);
                go(child.one);
            }else{
                go(child.zero);
            }
        });
        return ans;
    }

    T query(ll l,ll r,ll d,ll u)const{
        int xl=lower_bound(all(xs),l)-xs.begin();
        int xr=lower_bound(all(xs),r)-xs.begin();
        ll yd=lower_bound(all(ys),d)-ys.begin();
        ll yu=lower_bound(all(ys),u)-ys.begin();
        return iquery(xl,xr,yu)-iquery(xl,xr,yd);
    }
};
template<class T,int D>
struct dynamic_rectangle_add{
    dynamic_rectangle_sum<T,D>rs;
    void add_rec(ll l,ll r,ll d,ll u,T w){
        rs.add_point(l,d,w);
        rs.add_point(l,u,-w);
        rs.add_point(r,d,-w);
        rs.add_point(r,u,w);
    }
    void add(ll l,ll r,ll d,ll u,T w){
        rs.add(l,d,w);
        rs.add(l,u,-w);
        rs.add(r,d,-w);
        rs.add(r,u,w);
    }
    T query(ll x,ll y){
        return rs.query(0,x+1,0,y+1);
    }
    void build(){
        rs.build();
    }
};
template<class T,int D>
struct rectangle_sum{
    wm_base<ll,D>wm;
    vc<array<ll,3>>ps;
    vc<ll>xs;
    vc<ll>ys;
    void add_point(ll x,ll y,T w){
        xs.pb(x);
        ys.pb(y);
        ps.pb({x,y,w});
    }
    void build(){
        sort(all(ys));ys.erase(unique(all(ys)),ys.end());
        for(auto&[X,Y,w]:ps)Y=lower_bound(all(ys),Y)-ys.begin();
        sort(all(ps));
        xs.resize(ps.size());
        vc<ll>send(ps.size());
        vc<T>W(ps.size());
        rep(i,ps.size()){
            xs[i]=ps[i][0];
            send[i]=ps[i][1];
            W[i]=ps[i][2];
        }
        wm.build(send);
        wm.buildlowersum(W);
    }
    T query(ll l,ll r,ll d,ll u)const{
        ll xl=lower_bound(all(xs),l)-xs.begin();
        ll xr=lower_bound(all(xs),r)-xs.begin();
        ll yd=lower_bound(all(ys),d)-ys.begin();
        ll yu=lower_bound(all(ys),u)-ys.begin();
        return wm.template lower_sum<T>(xl,xr,yd,yu);
    }
};
