#pragma once
template<class T>
struct SternBrocotTree{
    struct STFrac{
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
        static STFrac root(){
            return {0,1,1,0};
        }
        pair<T,T>ToFrac(){
            return {p+r,q+s};
        }
    };
    static vc<pair<char,T>>EncodePath(T a,T b){
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
    static STFrac DecodePath(vc<pair<char,T>>c){
        STFrac f=STFrac::root();
        for(auto&[type,w]:c){
            assert(type=='L'||type=='R');
            assert(w>=0);
            f.move(type,w);
        }
        return f;
    }
    static STFrac Lca(T p1,T q1,T p2,T q2){
        assert(p1>0&&q1>0&&p2>0&&q2>0);
        auto path1=EncodePath(p1,q1);
        auto path2=EncodePath(p2,q2);
        STFrac f=STFrac::root();
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
    static optional<STFrac> Ancestor(T p,T q,T d){
        assert(p>0&&q>0);
        assert(d>=0);
        auto path=EncodePath(p,q);
        STFrac f=STFrac::root();
        rep(i,path.size()){
            auto&[type,w]=path[i];
            T nw=min(w,d);
            d-=nw;
            f.move(type,nw);
            if(d==0)return f;
        }
        return nullopt;
    }
    static pair<pair<T,T>,pair<T,T>> Range(T p,T q){
        assert(p>0&&q>0);
        auto f=DecodePath(EncodePath(p,q));
        return {{f.p,f.q},{f.r,f.s}};
    }
};
