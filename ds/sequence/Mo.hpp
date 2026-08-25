#pragma once
struct mo{
    int N,Q;
    int B;
    mo(int N,int Q):N(N),Q(Q){
        assert(N>=0&&Q>=0);
        B=max<int>(1,Q?N/sqrt(Q):1);
    }
    vc<array<int,3>>query;
    void push(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        query.push_back({l,r,(int)query.size()});
    }
    void sort(){
        if(query.empty())return;
        auto cost=[&](int a,int b,int c,int d){
            return abs(a-c)+abs(b-d);
        };
        std::sort(all(query),[&](auto a,auto b){
            if(a[0]/B!=b[0]/B)return a[0]<b[0];
            return (a[0]/B%2?a[1]<b[1]:a[1]>b[1]);
        });
        int c1=0;
        rep(i,query.size()-1)c1+=cost(query[i][0],query[i][1],query[i+1][0],query[i+1][1]);
        {
            auto n_query=query;
            std::sort(all(n_query),[&](auto a,auto b){
                if((a[0]+B/2)/B!=(b[0]+B/2)/B)return a[0]<b[0];
                return ((a[0]+B/2)/B%2?a[1]<b[1]:a[1]>b[1]);
            });
            int c2=0;
            rep(i,query.size()-1)c2+=cost(n_query[i][0],n_query[i][1],n_query[i+1][0],n_query[i+1][1]);
            if(chmin(c1,c2))query=move(n_query);
        }
        
        for(int iter=0;iter<3;++iter){
            auto cost=[&](int i,int j){
                return abs(query[i][0]-query[j][0])+abs(query[i][1]-query[j][1]);
            };
            for (int i=1;i<(int)query.size()-2;++i){
                int cur=cost(i-1,i)+cost(i+1,i+2);
                int next=cost(i-1,i+1)+cost(i,i+2);
                if(next<cur){
                    swap(query[i],query[i+1]);
                }
            }
        }
    }
    template<class A1,class A2,class A3,class A4,class A5>
    void run(A1 addleft,A2 addright,A3 eraseleft,A4 eraseright,A5 answer){
        sort();
        int nl=0,nr=-1;
        rep(i,query.size()){
            while(nr<query[i][1])addright(++nr);
            while(nl>query[i][0])addleft(--nl);
            while(nr>query[i][1])eraseright(nr--);
            while(nl<query[i][0])eraseleft(nl++);
            answer(query[i][2]);
        }
    }
};
