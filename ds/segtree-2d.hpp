#pragma once
#include"../template.hpp"
template<class Info>
struct segtree2d{
    using value_type=Info::value_type;
    ll H,W;
    struct Node{
        Node*l,*r,*nxt_root;
        value_type sum;
        Node():l(0),r(0),nxt_root(0),sum(Info::e()){}
        value_type get_sum(Node*x){
            if(x==0)return Info::e();
            return x->sum;
        }
        //[U,D)
        value_type inner_sum(ll W,ll U,ll D){
            if(nxt_root==0)return Info::e();
            value_type res=Info::e();
            auto dfs=[&](auto&dfs,ll su,ll sd,Node*now)->void{
                if(su>=D||sd<=U)return;
                if(U<=su&&sd<=D){
                    res=Info::op(now->sum,res);
                    return;
                }
                ll mid=midpoint(su,sd);
                if(now->l)dfs(dfs,su,mid,now->l);
                if(now->r)dfs(dfs,mid,sd,now->r);
            };
            dfs(dfs,0,W,nxt_root);
            return res;
        }
    };
    Node*root;
    segtree2d(ll H,ll W):H(H),W(W){
        root=new Node();
    }
    void set(ll i,ll j,value_type v){
        auto dfs=[&](auto&dfs,ll L,ll R,Node*now)->void{
            auto dfs2=[&](auto&dfs2,ll D,ll U,Node*now)->value_type{
                if(U-D==1){
                    now->sum=Info::op(now->sum,v);
                    return now->sum;
                }
                ll mid=midpoint(D,U);
                if(j<mid){
                    if(now->l==0)now->l=new Node();
                    return now->sum=Info::op(dfs2(dfs2,D,mid,now->l),now->get_sum(now->r));
                }else{
                    if(now->r==0)now->r=new Node();
                    return now->sum=Info::op(dfs2(dfs2,mid,U,now->r),now->get_sum(now->l));
                }
            };
            if(now->nxt_root==0)now->nxt_root=new Node();
            dfs2(dfs2,0,W,now->nxt_root);
            if(R-L==1)return;
            ll mid=midpoint(L,R);
            if(i<mid){
                if(now->l==0)now->l=new Node();
                return dfs(dfs,L,mid,now->l);
            }else{
                if(now->r==0)now->r=new Node();
                return dfs(dfs,mid,R,now->r);
            }
        };
        dfs(dfs,0,H,root);
    }
    //[L,R) [D,U)
    value_type prod(ll L,ll R,ll D,ll U){
        value_type res=Info::e();
        auto dfs=[&](auto&dfs,ll sl,ll sr,Node*now){
            if(sl>=R||sr<=L)return;
            if(L<=sl&&sr<=R){
                res=Info::op(now->inner_sum(W,D,U),res);
                return;
            }
            ll mid=midpoint(sl,sr);
            if(now->l)dfs(dfs,sl,mid,now->l);
            if(now->r)dfs(dfs,mid,sr,now->r);
        };
        dfs(dfs,0,H,root);
        return res;
    }
};