#pragma once
template<class info>
struct segtree_2d{
    using value_type=info::value_type;
    ll H,W;
    struct node{
        node*l,*r,*nxt_root;
        value_type sum;
        node():l(0),r(0),nxt_root(0),sum(info::e()){}
        value_type get_sum(node*x){
            if(x==0)return info::e();
            return x->sum;
        }
        //[U,D)
        value_type inner_sum(ll W,ll U,ll D){
            if(nxt_root==0)return info::e();
            value_type res=info::e();
            auto dfs=[&](auto&dfs,ll su,ll sd,node*now)->void{
                if(su>=D||sd<=U)return;
                if(U<=su&&sd<=D){
                    res=info::op(now->sum,res);
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
    node*root;
    segtree_2d(ll H,ll W):H(H),W(W){
        assert(H>=0&&W>=0);
        root=new node();
    }
    void set(ll i,ll j,value_type v){
        assert(0<=i&&i<H);
        assert(0<=j&&j<W);
        auto dfs=[&](auto&dfs,ll L,ll R,node*now)->void{
            auto dfs2=[&](auto&dfs2,ll D,ll U,node*now)->value_type{
                if(U-D==1){
                    now->sum=info::op(now->sum,v);
                    return now->sum;
                }
                ll mid=midpoint(D,U);
                if(j<mid){
                    if(now->l==0)now->l=new node();
                    return now->sum=info::op(dfs2(dfs2,D,mid,now->l),now->get_sum(now->r));
                }else{
                    if(now->r==0)now->r=new node();
                    return now->sum=info::op(dfs2(dfs2,mid,U,now->r),now->get_sum(now->l));
                }
            };
            if(now->nxt_root==0)now->nxt_root=new node();
            dfs2(dfs2,0,W,now->nxt_root);
            if(R-L==1)return;
            ll mid=midpoint(L,R);
            if(i<mid){
                if(now->l==0)now->l=new node();
                return dfs(dfs,L,mid,now->l);
            }else{
                if(now->r==0)now->r=new node();
                return dfs(dfs,mid,R,now->r);
            }
        };
        dfs(dfs,0,H,root);
    }
    //[L,R) [D,U)
    value_type prod(ll L,ll R,ll D,ll U){
        assert(0<=L&&L<=R&&R<=H);
        assert(0<=D&&D<=U&&U<=W);
        value_type res=info::e();
        auto dfs=[&](auto&dfs,ll sl,ll sr,node*now){
            if(sl>=R||sr<=L)return;
            if(L<=sl&&sr<=R){
                res=info::op(now->inner_sum(W,D,U),res);
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
