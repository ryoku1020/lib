#pragma once
#include"../lib/template.hpp"
template<class T> 
struct node_pool{
    static constexpr int B=1024;
    vc<T*>block;
    int sz=0;
    node_pool(){}
    node_pool(const node_pool&)=delete;
    node_pool& operator=(const node_pool&)=delete;
    ~node_pool(){
        clear();
        for(auto p:block)allocator<T>{}.deallocate(p,B);
    }
    template<class...Args>
    T*alloc(Args&&...args){
        int b=sz/B;
        int p=sz%B;
        if(b==(int)block.size()){
            block.pb(allocator<T>{}.allocate(B));
        }
        T*res=block[b]+p;
        construct_at(res,forward<Args>(args)...);
        sz++;
        return res;
    }
    void clear(){
        rep(i,sz){
            destroy_at(block[i/B]+i%B);
        }
        sz=0;
    }
    int size()const{
        return sz;
    }
};