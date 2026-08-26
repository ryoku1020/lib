#pragma once
ull splitmix64(ull x){
    x+=0x9e3779b97f4a7c15ULL;
    x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;
    x=(x^(x>>27))*0x94d049bb133111ebULL;
    return x^(x>>31);
}
ull hashmap_hash(ull x){
    static const ull seed=[]{
        ull x=chrono::steady_clock::now().time_since_epoch().count();
        x^=(ull)(uintptr_t)&x;
        return splitmix64(x);
    }();
    return splitmix64(x+seed);
}
template<class Key,class Val,auto tohash=hashmap_hash>
struct hashmap{
    struct Node{
        Key k;
        Val v;
    };
    hashmap():data(cap),used(cap){}
    int cap=8;
    vc<Node>data;
    vc<uint8_t>used;
    int usedcnt=0;
    const double alpha=0.5;
    void recap(int new_cap=-1){
        if(new_cap==-1)new_cap=cap*2;
        vc<Node>ndata(new_cap);
        vc<uint8_t>nused(new_cap);
        rep(i,cap){
            if(!used[i])continue;
            int pt=tohash(data[i].k)&(new_cap-1);
            while(nused[pt]){
                pt=(pt+1)&(new_cap-1);
            }
            nused[pt]=1;
            ndata[pt]=data[i];
        }
        data=move(ndata),used=move(nused);
        cap=new_cap;
    }

    Val&operator[](const Key&k){
        if(usedcnt>cap*alpha){
            recap();
        }
        int pt=tohash(k)&(cap-1);
        while(used[pt]){
            if(data[pt].k==k){
                return data[pt].v;
            }
            pt=(pt+1)&(cap-1);
        }
        used[pt]=1;
        ++usedcnt;
        data[pt].k=k;
        return data[pt].v;
    }
    int erase(const Key&k){
        int pt=tohash(k)&(cap-1);
        while(used[pt]){
            if(data[pt].k==k)break;
            pt=(pt+1)&(cap-1);
        }
        if(!used[pt])return 0;
        int hole=pt,mask=cap-1;
        for(int nxt=(hole+1)&mask;used[nxt];nxt=(nxt+1)&mask){
            int home=tohash(data[nxt].k)&mask;
            if(((hole-home)&mask)<((nxt-home)&mask)){
                data[hole]=move(data[nxt]);
                hole=nxt;
            }
        }
        used[hole]=0;
        --usedcnt;
        return 1;
    }
    int count(const Key&k){
        int pt=tohash(k)&(cap-1);
        while(used[pt]){
            if(data[pt].k==k){
                return 1;
            }
            pt=(pt+1)&(cap-1);
        }
        return 0;
    }
    int size(){return usedcnt;}
    int empty(){return size()==0;}
    void clear(){*this=hashmap();}
    void reserve(int S){
        int new_cap=cap;
        while(new_cap*alpha<S){
            new_cap*=2;
        }
        if(new_cap!=cap)recap(new_cap);
    }
    struct iterator{
        hashmap*m;
        int i;
        iterator(hashmap*mp,int i):m(mp),i(i){
            while(i<mp->cap&&!mp->used[i])++i;
        }
        iterator&operator++(){
            do ++i;while(i<m->cap&&!m->used[i]);
            return *this;
        }
        Node&operator*()const{return m->data[i];}
        Node*operator->()const{return &m->data[i];}
        bool operator==(const iterator&r)const{return i==r.i;}
        bool operator!=(const iterator&r)const{return i!=r.i;}
    };
    iterator begin(){return {this,0};}
    iterator end(){return {this,cap};}
};
