#pragma once
namespace ryoku{
template<class key>
struct adjacent_manager{
    set<key>sts;
    using F=function<void(const key&,const key&)>;
    F add,del;
    adjacent_manager(F add,F del):add(add),del(del){}
    bool insert(const key&x){
        auto r=sts.lower_bound(x);
        if(r!=sts.end()&&*r==x)return false;
        auto l=r==sts.begin()?sts.end():prev(r);
        if(l!=sts.end()&&r!=sts.end())del(*l,*r);
        auto it=sts.insert(r,x);
        if(l!=sts.end())add(*l,*it);
        if(r!=sts.end())add(*it,*r);
        return true;
    }
    bool erase(const key&x){
        auto it=sts.find(x);
        if(it==sts.end())return false;
        auto l=it==sts.begin()?sts.end():prev(it);
        auto r=next(it);
        if(l!=sts.end())del(*l,*it);
        if(r!=sts.end())del(*it,*r);
        sts.erase(it);
        if(l!=sts.end()&&r!=sts.end())add(*l,*r);
        return true;
    }
};
}