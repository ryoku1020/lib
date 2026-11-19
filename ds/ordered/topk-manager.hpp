#pragma once
namespace ryoku{
template<class T,int minisgood,class Add,class Del>
struct topkmanager{
    multiset<T>tk,td;
    ll k;
    Add add;
    Del del;
    topkmanager(ll k,Add add,Del del):k(k),add(add),del(del){}
    auto worst(){
        if constexpr(minisgood)return prev(tk.end());
        else return tk.begin();
    }
    auto best(){
        if constexpr(minisgood)return td.begin();
        else return prev(td.end());
    }
    void balance(){
        while((ll)tk.size()>k){
            auto it=worst();
            T x=*it;
            tk.erase(it);
            td.insert(x);
            del(x);
        }
        while((ll)tk.size()<k&&!td.empty()){
            auto it=best();
            T x=*it;
            td.erase(it);
            tk.insert(x);
            add(x);
        }
        if(tk.empty()||td.empty())return;
        auto i=worst(),j=best();
        if(minisgood?*j<*i:*i<*j){
            T x=*i,y=*j;
            tk.erase(i);
            td.erase(j);
            tk.insert(y);
            td.insert(x);
            del(x);
            add(y);
        }
    }
    void insert(T x){
        td.insert(x);
        balance();
    }
    void erase(T x){
        auto it=tk.find(x);
        if(it!=tk.end()){
            tk.erase(it);
            del(x);
        }else{
            it=td.find(x);
            assert(it!=td.end());
            td.erase(it);
        }
        balance();
    }
    ll size()const{
        return tk.size();
    }
};
}
