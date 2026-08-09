#pragma once
template<class T>
struct RangeSet{
    T covered;
    using P=pair<T,T>;
    using It=set<P>::iterator;
    set<P>st;
    RangeSet():covered(0){}
    //[l,r) を insert
    void insert(T l,T r){
        assert(l<=r);
        if(l==r)return;
        erase(l,r);
        {
            auto it=st.lower_bound({l,-inf<T>});
            if(it!=st.begin()&&prev(it)->second==l){
                l=prev(it)->first;
                erase(prev(it)->first,prev(it)->second);
            }
        }
        {
            auto it=st.lower_bound({r,-inf<T>});
            if(it!=st.end()&&it->first==r){
                r=it->second;
                erase(it->first,it->second);
            }
        }
        st.insert({l,r});covered+=r-l;
    }
    //[l,r) に含まれる区間を削除
    //はみ出るやつは残しておく
    void erase(T l,T r){
        assert(l<=r);
        if(l==r)return;
        rep(_,1){
            auto it=st.upper_bound({l,-inf<T>});
            if(it==st.begin())break;
            it=prev(it);
            if(it->second<=l)break;
            covered-=min<T>(r,it->second)-l;
            T tif=it->first,tis=it->second;
            st.erase(it);
            if(tif!=l)st.insert({tif,l});
            if(tis>r)st.insert({r,tis});
        }
        while(1){
            auto it=st.lower_bound({l,-inf<T>});
            if(it==st.end()||it->first>=r)break;
            if(it->second>=r){
                covered-=r-it->first;
                T tis=it->second;st.erase(it);
                if(tis!=r)st.insert({r,tis});
                break;
            }
            covered-=it->second-it->first;
            st.erase(it);
        }
    }
    //x を含む区間
    It find(T x){
        auto it=st.upper_bound({x,inf<T>});
        if(it==st.begin())return st.end();
        if(prev(it)->second<=x)return st.end();
        return prev(it);
    }
    //x が含まれるか
    bool contains(T x){
        return find(x)!=st.end();
    }
    //[l,r) が全て含まれるか
    bool contains(T l,T r){
        assert(l<=r);
        if(l==r)return true;
        auto it=find(l);
        return it!=st.end()&&r<=it->second;
    }
    //x を含む区間、なければ x より後の最初の区間
    It lower_bound(T x){
        auto it=st.lower_bound({x,-inf<T>});
        if(it!=st.begin()&&prev(it)->second>x)return prev(it);
        return it;
    }
    //[l,r) と交わる部分を列挙
    vc<P>enumerate(T l,T r){
        assert(l<=r);
        vc<P>res;
        for(auto it=lower_bound(l);it!=st.end()&&it->first<r;it++){
            T a=max(l,it->first),b=min(r,it->second);
            if(a<b)res.pb({a,b});
        }
        return res;
    }
    void clear(){
        st.clear();covered=0;
    }
    void debug(){
        dbg("==========="s);
        for(auto&[l,r]:st){
            dbg(l,r);
        }
        dbg("==========="s);
    }
}; 

// 区間ごとに monoid の値を持つ range set
template<class T,class Info>
struct RangeSetInfo{
    using value_type=typename Info::value_type;
    struct Node{
        T l,r;
        value_type val;
    };
    struct Cmp{
        bool operator()(const Node&a,const Node&b)const{
            return a.l<b.l;
        }
    };
    using It=typename set<Node,Cmp>::iterator;
    using CIt=typename set<Node,Cmp>::const_iterator;
    set<Node,Cmp>st;

    It lower_bound(T x){
        auto it=st.lower_bound({x,x,Info::e()});
        if(it!=st.begin()&&prev(it)->r>x)return prev(it);
        return it;
    }

    CIt lower_bound(T x)const{
        auto it=st.lower_bound({x,x,Info::e()});
        if(it!=st.begin()&&prev(it)->r>x)return prev(it);
        return it;
    }

    void add(vector<Node>&v,T l,T r,const value_type&val){
        if(l<r&&val!=Info::e())v.pb({l,r,val});
    }

    //[l,r) に info を作用させる
    void apply(T l,T r,const value_type&info){
        assert(l<=r);
        if(l==r||info==Info::e())return;
        vector<Node>v;
        auto it=lower_bound(l);
        T cur=l;
        while(it!=st.end()&&it->l<r){
            Node x=*it;
            it=st.erase(it);
            if(cur<x.l)add(v,cur,min(r,x.l),Info::op(Info::e(),info));
            T a=max(l,x.l),b=min(r,x.r);
            add(v,x.l,a,x.val);
            add(v,a,b,Info::op(x.val,info));
            add(v,b,x.r,x.val);
            cur=max(cur,b);
        }
        if(cur<r)add(v,cur,r,Info::op(Info::e(),info));
        for(auto&x:v)st.insert(x);
    }

    //[l,r) の情報を極大な区間の集合として返す
    vector<tuple<T,T,value_type>> get(T l,T r)const{
        assert(l<=r);
        vector<tuple<T,T,value_type>>res;
        if(l==r)return res;
        auto add=[&](T a,T b,const value_type&val){
            if(a==b)return;
            if(!res.empty()&&std::get<2>(res.back())==val)std::get<1>(res.back())=b;
            else res.emplace_back(a,b,val);
        };
        T cur=l;
        for(auto it=lower_bound(l);it!=st.end()&&it->l<r;it++){
            if(cur<it->l)add(cur,min(r,it->l),Info::e());
            T a=max(cur,it->l),b=min(r,it->r);
            add(a,b,it->val);
            cur=max(cur,b);
        }
        add(cur,r,Info::e());
        return res;
    }

    void clear(){st.clear();}
};
