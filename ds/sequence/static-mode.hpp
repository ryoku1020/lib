#pragma once
template<class T>
struct static_range_mode{
    vc<T>a;
    int n;
    int B;
    int block_cnt;
    vc<vc<int>>idx;
    vvc<pair<int,T>>mode;
    vc<int>inv;
    vc<int>Query_cnt;
    compresser<T>cp;
    bool built=false;
    static_range_mode()=default;
    static_range_mode(int n):n(n){assert(n>=0);a.resize(n);}
    void set(int i,T x){assert(!built);assert(0<=i&&i<n);a[i]=x;}
    void precalc(){
        if(built)return;
        built=true;
        assert(n>0);
        B=sqrt(n);
        rep(i,n)cp.push(a[i]);cp.build();rep(i,n)a[i]=cp.find(a[i]);
        idx.resize(n);
        inv.resize(n);
        rep(i,n){
            idx[a[i]].push_back(i);
            inv[i]=idx[a[i]].size()-1;
        }
        block_cnt=(n+B-1)/B;
        mode.resize(block_cnt+1,vc<pair<int,T>>(block_cnt+1));
        Query_cnt.resize(n);
        vc<int>cnt(n);
        rep(l,block_cnt+1){
            rep(i,n)cnt[i]=0;
            int front=l*B;
            pair<int,T>now_mode{0,0};
            REP(r,l,block_cnt+1){
                int lm=min<int>(n,r*B);
                while(front<lm){
                    cnt[a[front]]++;
                    chmax(now_mode,make_pair(int(cnt[a[front]]),T(a[front])));
                    ++front;
                }
                mode[l][r]=now_mode;
            }
        }
        dbg(mode);
    }
    //[l,r) l==r > ng!!!!!!
    pair<int,T>query(int l,int r){
        assert(0<=l&&l<r&&r<=n);
        precalc();
        if(l/B==r/B){
            pair<int,T>now_mode{0,0};
            REP(i,l,r){
                Query_cnt[a[i]]++;
                chmax(now_mode,make_pair(int(Query_cnt[a[i]]),T(a[i])));
            }
            REP(i,l,r)Query_cnt[a[i]]--;
            now_mode.second=cp.x[now_mode.second];
            return now_mode;
        }
        
        pair<int,T>now_mode=mode[l/B+1][r/B];
        REP(i,l,(l/B+1)*B){
            auto&target=a[i];
            ll nxt=inv[i]+now_mode.first;
            if(idx[target].size()>nxt&&idx[target][nxt]<r){
                while(idx[target].size()>nxt+1&&idx[target][nxt+1]<r)++nxt;
                now_mode={nxt-inv[i]+1,target};
            }
        }
        REP(i,r/B*B,r){
            auto&target=a[i];
            ll nxt=inv[i]-now_mode.first;
            if(nxt>=0&&idx[target][nxt]>=l){
                while(nxt-1>=0&&idx[target][nxt-1]>=l)--nxt;
                now_mode={inv[i]-nxt+1,target};
            }
        } 
        now_mode.second=cp.x[now_mode.second];
        return now_mode;
    }
};
