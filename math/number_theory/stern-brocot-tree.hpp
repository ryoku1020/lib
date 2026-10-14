#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class T>
struct stern_brocot_tree{
    struct st_frac{
        T p,q,r,s;
        void move(char type,T w){
            assert(type=='L'||type=='R');
            assert(w>=0);
            if(type=='L'){
                r+=p*w;
                s+=q*w;
            }else{
                p+=r*w;
                q+=s*w;
            }
        }
        static st_frac root(){
            return {0,1,1,0};
        }
        pair<T,T>to_frac(){
            return {p+r,q+s};
        }
    };
    static vc<pair<char,T>>encode_path(T a,T b){
        assert(a>0&&b>0);
        vc<T>front;
        while(b){
            front.push_back(a/b);
            a%=b;
            swap(a,b);
        }
        vc<pair<char,T>>res;
        rep(i,front.size()){
            if(i+1==front.size())front[i]--;
            if(front[i]){
                res.push_back({"RL"[i%2],front[i]});
            }
        }
        return res;
    }
    static st_frac decode_path(vc<pair<char,T>>c){
        st_frac f=st_frac::root();
        for(auto&[type,w]:c){
            assert(type=='L'||type=='R');
            assert(w>=0);
            f.move(type,w);
        }
        return f;
    }
    static st_frac lca(T p1,T q1,T p2,T q2){
        assert(p1>0&&q1>0&&p2>0&&q2>0);
        auto path1=encode_path(p1,q1);
        auto path2=encode_path(p2,q2);
        st_frac f=st_frac::root();
        rep(i,min(path1.size(),path2.size())){
            auto&[type,w]=path1[i];
            if(path1[i]==path2[i]){
                f.move(type,w);
            }else{
                T nw=0;
                if(path2[i].first==type){
                    nw=min(path2[i].second,w);
                }
                f.move(type,nw);
                return f;
            }
        }
        return f;
    }
    static optional<st_frac> ancestor(T p,T q,T d){
        assert(p>0&&q>0);
        assert(d>=0);
        auto path=encode_path(p,q);
        st_frac f=st_frac::root();
        rep(i,path.size()){
            auto&[type,w]=path[i];
            T nw=min(w,d);
            d-=nw;
            f.move(type,nw);
            if(d==0)return f;
        }
        return nullopt;
    }
    static pair<pair<T,T>,pair<T,T>> range(T p,T q){
        assert(p>0&&q>0);
        auto f=decode_path(encode_path(p,q));
        return {{f.p,f.q},{f.r,f.s}};
    }

    template<class F>
    static st_frac binary_search(T n,T m,F judge){
        assert(n>=1&&m>=1);
        st_frac f=st_frac::root();
        while(f.p<=n-f.r&&f.q<=m-f.s){
            bool go_right=judge(f.p+f.r,f.q+f.s);
            T lim=min(n,m);
            if(go_right){
                if(f.r)lim=min(lim,(n-f.p)/f.r);
                if(f.s)lim=min(lim,(m-f.q)/f.s);
            }else{
                if(f.p)lim=min(lim,(n-f.r)/f.p);
                if(f.q)lim=min(lim,(m-f.s)/f.q);
            }
            auto ok=[&](T x){
                auto nf=f;
                nf.move(go_right?'R':'L',x);
                if(go_right)return judge(nf.p,nf.q);
                return !judge(nf.r,nf.s);
            };
            T ac=1,wa=1;
            while(wa<lim){
                T nxt=wa+min(wa,lim-wa);
                if(!ok(nxt)){
                    wa=nxt;
                    break;
                }
                ac=wa=nxt;
            }
            while(wa-ac>1){
                T mid=ac+(wa-ac)/2;
                if(ok(mid))ac=mid;
                else wa=mid;
            }
            f.move(go_right?'R':'L',ac);
        }
        return f;
    }
};

}
