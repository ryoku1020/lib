#pragma once
#include"../../ds/union_find/uf.hpp"
#include"../base.hpp"
#include"../bipartite-match.hpp"
vc<int>bipatite_edge_coloring(vc<pii>edge,int L,int R){
    //D regular graph part
    vc<int>d1(L),d2(R);
    for(auto&[x,y]:edge)d1[x]++,d2[y]++;
    int D=max(max(d1),max(d2));
    if(D==0)return{};
    auto build=[&](int N,vc<int>d1){
        disjoint_set_union dsu(N);
        smpq<pii>que;rep(i,N)que.push({d1[i],i});
        while(que.size()>1){
            auto p=que.top();que.pop();
            auto q=que.top();que.pop();
            if(p.fi+q.fi>D)break;
            que.push({p.fi+q.fi,p.se});
            dsu.merge(p.se,q.se);
        }
        return dsu;
    };
    auto dsuL=build(L,d1);
    auto dsuR=build(R,d2);
    int ML=0,MR=0;rep(i,L)ML+=dsuL.root(i)==i;rep(i,R)MR+=dsuR.root(i)==i;
    int N=max(ML,MR);
    d1.assign(N,0),d2.assign(N,0);
    static_graph<0>g(2*N);
    vc<int>vaal(L,-1),vaar(R,-1);
    int iil=0,iir=0;
    for(auto&[x,y]:edge){
        x=dsuL.root(x),y=dsuR.root(y);
        if(vaal[x]==-1)vaal[x]=iil++;
        if(vaar[y]==-1)vaar[y]=iir++;
        x=vaal[x],y=vaar[y];
        g.add_edge(x,y+N);
        d1[x]++,d2[y]++;
    }
    queue<pii>qL,qR;
    rep(i,N)if(d1[i]<D)qL.push({d1[i],i});
    rep(i,N)if(d2[i]<D)qR.push({d2[i],i});
    while(qL.size()&&qR.size()){
        auto li=qL.front();qL.pop();
        auto ri=qR.front();qR.pop();
        g.add_edge(li.se,ri.se+N);
        li.fi=++d1[li.se];
        ri.fi=++d2[ri.se];
        if(li.fi<D)qL.push(li);
        if(ri.fi<D)qR.push(ri);
    }
    //---------------------------
    int M=D*N;
    vc<int>ord(M);iota(all(ord),0);
    vc<int>waier(N*2,-1);
    vc<array<int,2>>twin(M);
    vc<int>side(M,-1);
    vc<int>first_match(M);
    auto divide_segment=[&](int L,int R){
        rep(z,2)REP(i,L,R){
            int eey=ord[i];
            int lvc=g.get_edge(eey).from;if(z)lvc=g.get_edge(eey).to;
            if(waier[lvc]==-1){
                waier[lvc]=eey;
            }else{
                twin[eey][z]=waier[lvc];
                twin[waier[lvc]][z]=eey;
                waier[lvc]=-1;
            }
        }
        REP(i,L,R){
            int eey=ord[i];if(side[eey]!=-1)continue;
            int z=0;
            side[eey]=z;
            while(1){
                eey=twin[eey][z];z^=1;
                if(eey==ord[i])break;
                side[eey]=z;
            }
        }
        partition(ord.begin()+L,ord.begin()+R,[&](int eid){
            return side[eid]==0;
        });
        REP(i,L,R)side[ord[i]]=-1;
    };
    auto dfs=[&](auto&dfs,int L,int R,int D)->void{
        if(D==1)return;
        if(D%2==0){ 
            divide_segment(L,R);
            dfs(dfs,L,L+R>>1,D/2);
            dfs(dfs,L+R>>1,R,D/2);
        }else{
            using EdgeSeg=pair<int,int>;
            vc<EdgeSeg>abb;
            bipartite_matching bm(N,N);
            REP(i,L,R)bm.add_edge(g.get_edge(ord[i]).from,g.get_edge(ord[i]).to-N,g.get_edge(ord[i]).id);
            auto res=bm.work();
            for(auto&e:res)first_match[e.id]=1;
            partition(ord.begin()+L,ord.begin()+R,[&](int eid){
                return first_match[eid]==1;
            });
            divide_segment(L+N,R);
            int LRM=(L+N+R)>>1;
            abb={{L,L+N},{L+N,LRM},{LRM,R}};
            vc<EdgeSeg>T;
            while(1){   
                auto W=[&](pii x){return x.se-x.fi==N;};
                if(W(abb[0])&&W(abb[1])&&W(abb[2]))break;
                 if((abb[1].se-abb[1].fi)/N%2==0){
                    T.pb(abb[2]);
                    int M=abb[1].se+abb[1].fi>>1;
                    divide_segment(abb[1].fi,abb[1].se);
                    abb[2]={M,abb[1].se};
                    abb[1]={abb[1].fi,M};
                }else{
                    divide_segment(abb[0].fi,abb[1].se);
                    int W=(abb[1].se-abb[0].fi)>>1;
                    int W2=(abb[2].se-abb[2].fi);
                    rotate(ord.begin()+abb[0].fi,ord.begin()+abb[0].fi+W*2,ord.begin()+abb[2].se);
                    abb[0]={L,L+W2};
                    abb[1]={L+W2,L+W2+W};
                    abb[2]={L+W2+W,L+W2+W*2};
                }
            }
            while(T.size()){
                auto TLR=T.back();T.pop_back();
                int next=1<<tbit((TLR.se-TLR.fi)/N);
                if(next<(TLR.se-TLR.fi)/N)next*=2;
                int make=(next-(TLR.se-TLR.fi)/N)*N;
                int L=TLR.fi-make;
                int R=TLR.se;
                dfs(dfs,L,R,(R-L)/N);
            }
        }
    };
    dfs(dfs,0,D*N,D);
    vc<int>ans(edge.size());
    rep(i,M)if(ord[i]<edge.size())ans[ord[i]]=i/N;
    return ans;
}