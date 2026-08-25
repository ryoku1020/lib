#pragma once
struct Mo{
    int N,Q;
    int B;
    Mo(int N,int Q):N(N),Q(Q){
        assert(N>=0&&Q>=0);
        B=max<int>(1,Q?N/sqrt(Q):1);
    }
    vc<array<int,3>>Query;
    void push(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        Query.push_back({l,r,(int)Query.size()});
    }
    void Sort(){
        if(Query.empty())return;
        auto cost=[&](int a,int b,int c,int d){
            return abs(a-c)+abs(b-d);
        };
        sort(all(Query),[&](auto a,auto b){
            if(a[0]/B!=b[0]/B)return a[0]<b[0];
            return (a[0]/B%2?a[1]<b[1]:a[1]>b[1]);
        });
        int c1=0;
        rep(i,Query.size()-1)c1+=cost(Query[i][0],Query[i][1],Query[i+1][0],Query[i+1][1]);
        {
            auto nQuery=Query;
            sort(all(nQuery),[&](auto a,auto b){
                if((a[0]+B/2)/B!=(b[0]+B/2)/B)return a[0]<b[0];
                return ((a[0]+B/2)/B%2?a[1]<b[1]:a[1]>b[1]);
            });
            int c2=0;
            rep(i,Query.size()-1)c2+=cost(nQuery[i][0],nQuery[i][1],nQuery[i+1][0],nQuery[i+1][1]);
            if(chmin(c1,c2))Query=move(nQuery);
        }
        
        for(int iter=0;iter<3;++iter){
            auto cost=[&](int i,int j){
                return abs(Query[i][0]-Query[j][0])+abs(Query[i][1]-Query[j][1]);
            };
            for (int i=1;i<(int)Query.size()-2;++i){
                int cur=cost(i-1,i)+cost(i+1,i+2);
                int next=cost(i-1,i+1)+cost(i,i+2);
                if(next<cur){
                    swap(Query[i],Query[i+1]);
                }
            }
        }
    }
    template<class A1,class A2,class A3,class A4,class A5>
    void run(A1 addleft,A2 addright,A3 eraseleft,A4 eraseright,A5 answer){
        Sort();
        int nl=0,nr=-1;
        rep(i,Query.size()){
            while(nr<Query[i][1])addright(++nr);
            while(nl>Query[i][0])addleft(--nl);
            while(nr>Query[i][1])eraseright(nr--);
            while(nl<Query[i][0])eraseleft(nl++);
            answer(Query[i][2]);
        }
    }
};
