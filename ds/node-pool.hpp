#pragma once
template<class T,class ptr_t=int>
struct NodePool{
    vector<T>pool;
    vector<ptr_t>st;
    int idx,cap;
    NodePool(int s=4):idx(1),cap(s){assert(s>0);pool.resize(s);}
    inline T&operator[](ptr_t i){assert(0<=int(i)&&int(i)<idx);return pool[int(i)];}
    void grow(){
        cap*=2;
        pool.resize(cap);
    }
    ptr_t get_new(){
        if(!st.empty()){
            ptr_t res=st.back();
            st.pop_back();
            return res;
        }
        if(idx==cap)grow();
        return ptr_t(idx++);
    }
    template<typename...Args>
    ptr_t get_new(Args...args){
        ptr_t res=get_new();
        pool[int(res)]=T(args...);
        return res;
    }
    void del(ptr_t i){assert(0<int(i)&&int(i)<idx);st.push_back(i);}
    void clear(){idx=1;st.clear();}
};
