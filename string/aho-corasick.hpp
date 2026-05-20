#pragma once
template<int sigma,auto give_order>
struct AhoCorasick{
    vc<array<int,sigma>>child;
    vc<int>suffix;
    vc<int>depth;
    vc<int>word;
    int root;
    int new_node(){
        int id=child.size();
        child.push_back({});
        rep(i,sigma)child.back()[i]=-1;
        suffix.push_back(-1);
        depth.push_back(0);
        return id;
    }
    AhoCorasick(){
        root=new_node();
    }
    template<class String>
    int add(String&s){
        int res=0;
        auto dfs=[&](auto&dfs,int now,int idx)->void{
            if(idx==s.size()){
                word.push_back(now);
                return;
            }
            int C=give_order(s[idx]);
            assert(0<=C&&C<sigma);
            if(child[now][C]==-1){
                ++res;
                int nxt=new_node();
                depth[nxt]=depth[now]+1;
                child[now][C]=nxt;
            }
            dfs(dfs,child[now][C],idx+1);
        };
        dfs(dfs,root,0);
        return res;
    }

    void build(){
        suffix[root]=root;
        queue<int>que;que.push(root);
        while(que.size()){
            auto now=que.front();que.pop();
            rep(c,sigma){
                if(child[now][c]!=-1){
                    int nxt=child[now][c];
                    int nxt_suffix=suffix[now];
                    while(nxt_suffix!=root&&child[nxt_suffix][c]==-1){
                        nxt_suffix=suffix[nxt_suffix];
                    }
                    
                    if(child[nxt_suffix][c]!=-1&&now!=root)suffix[nxt]=child[nxt_suffix][c];
                    else suffix[nxt]=nxt_suffix;
                    que.push(nxt);
                }
            }
        }
    }
    int size(){
        return child.size();
    }
    vc<int>suffix_order(){
        vc<int>in_deg(size());
        for(auto&x:suffix){
            in_deg[x]++;
        }
        queue<int>que;rep(i,size()){
            if(in_deg[i]==0)que.push(i);
        }
        vc<int>res;
        while(que.size()){
            auto p=que.front();que.pop();
            res.pb(p);in_deg[suffix[p]]--;
            if(in_deg[suffix[p]]==0)que.push(suffix[p]);
        }
        res.pb(0);
        reverse(all(res));
        return res;
    }
    vvc<int>suffix_inv(){
        vvc<int>res(size());
        REP(i,1,size())res[suffix[i]].pb(i);
        return res;
    }
};