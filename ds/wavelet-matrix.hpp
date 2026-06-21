#include"bit-vector.hpp"
template<class T,int D>
struct WMbase{
    using U=make_unsigned_t<T>;
    int n;
    array<BitVector,D>bv;
    array<int,D>mid;
    vc<T>gi;
    void build(vc<T>a){
        gi=a,n=a.size();
        vc<int>send(n);
        drep(bit,D){
            rep(i,n)send[i]=a[i]>>bit&1;
            bv[bit]=BitVector(send);
            vc<T>l,r;
            rep(i,n){
                if(a[i]>>bit&1)r.pb(a[i]);
                else l.pb(a[i]);
            }
            mid[bit]=l.size();
            l.insert(l.end(),all(r));
            a=move(l);
        }
    }
    template<class F>
    void build_info(F f){
        auto a=gi;
        vc<int>idx(n);
        rep(i,n)idx[i]=i;
        f(a,idx,D);
        drep(bit,D){
            vc<T>l,r;
            vc<int>li,ri;
            rep(i,n){
                if(a[i]>>bit&1)r.pb(a[i]),ri.pb(idx[i]);
                else l.pb(a[i]),li.pb(idx[i]);
            }
            l.insert(l.end(),all(r));
            li.insert(li.end(),all(ri));
            a=move(l);
            idx=move(li);
            f(a,idx,bit);
        }
    }
    template<class L>
    static array<vc<L>,D+1>& lower_pref(){
        static array<vc<L>,D+1>pref;
        return pref;
    }
    template<class L>
    void buildlowersum(const vc<L>&W){
        auto&pref=lower_pref<L>();
        build_info([&](const vc<T>&a,const vc<int>&idx,int bit){
            pref[bit]=vc<L>(n+1);
            rep(i,n)pref[bit][i+1]=pref[bit][i]+W[idx[i]];
        });
    }
    struct Node{
        int bit,l,r;
        int size()const{return r-l;}
    };
    struct Child{
        bool has;
        Node zero,one;
    };
    Child child(Node x)const{
        if(x.bit==-1)return {false,{},{}};
        int a0=bv[x.bit].rank0(x.l);
        int b0=bv[x.bit].rank0(x.r);
        int a1=x.l-a0,b1=x.r-b0;
        return {true,{x.bit-1,a0,b0},{x.bit-1,mid[x.bit]+a1,mid[x.bit]+b1}};
    }
    template<class F>
    void walk(int l,int r,F&&f)const{
        auto dfs=[&](auto&dfs,Node x)->void{
            Child ch=child(x);
            auto go=[&](Node y){dfs(dfs,y);};
            f(x,ch,go);
        };
        dfs(dfs,{D-1,l,r});
    }
    T KthSmallest(int l,int r,int k)const{
        T ans=0;
        walk(l,r,[&](auto node,auto child,auto go){
            if(!child.has)return;
            if(child.zero.size()<=k){
                k-=child.zero.size();
                ans+=T(1)<<node.bit;
                go(child.one);
            }else{
                go(child.zero);
            }
        });
        return ans;
    }
    ll CountLess(int l,int r,T k)const{
        ll ans=0;
        walk(l,r,[&](Node x,Child ch,auto go){
            if(!ch.has)return;
            if(k>>x.bit&1)ans+=ch.zero.size(),go(ch.one);
            else go(ch.zero);
        });
        return ans;
    }
    //[l,r) [d,u)
    ll Count(int l,int r,T d,T u)const{
        return CountLess(l,r,u)-CountLess(l,r,d);
    }
    template<class L>
    L LowerSum(int l,int r,T u)const{
        auto&pref=lower_pref<L>();
        L ans=0;
        walk(l,r,[&](auto x,auto ch,auto go){
            if(!ch.has)return;
            if(u>>x.bit&1){
                ans+=pref[x.bit][ch.zero.r]-pref[x.bit][ch.zero.l];
                go(ch.one);
            }else{
                go(ch.zero);
            }
        });
        return ans;
    }
    template<class L>
    L LowerSum(int l,int r,T d,T u)const{
        return LowerSum<L>(l,r,u)-LowerSum<L>(l,r,d);
    }
};