#pragma once
#include"tree/base.hpp"
int give(char c){
    return c-'a';
}
const int sigma=26;
struct SuffixAutomaton{
    struct Node{
        int len;
        int link;
        array<int,sigma>nxt;
        Node():len(0),link(-1){
            nxt.fill(-1);
        }
    };
    vc<Node>nodes;
    pii get_segment(int nv){
        auto&target=nodes[nv];
        pii res;res.second=target.len;
        if(target.link>=0){
            res.first=nodes[target.link].len+1;
        }else{
            res.first=0;
        }
        return res;
    }
    int front=0;
    vc<int>prefix;
    vc<int>Esize;
    Tree<Unweighted>g;
    int nw(){
        nodes.push_back(Node());
        return front++;
    }
    SuffixAutomaton():g(1){
        prefix.pb(nw());
    }
    SuffixAutomaton(string s):g(1){
        prefix.pb(nw());
        for(auto&x:s){
            add(give(x));
        }
        auto res=TopoSort();
        reverse(all(res));
        Esize.assign(nodes.size(),0);
        rep(i,prefix.size()){
            Esize[prefix[i]]++;
        }
        for(auto&x:res){
            if(nodes[x].link>=0){
                Esize[nodes[x].link]+=Esize[x];
            }
        }
        g=Tree(nodes.size());
        rep(i,nodes.size()){
            if(nodes[i].link>=0){
                g.add_edge(i,nodes[i].link);
            }
        }
    }
    void add(int c){
        int p=prefix.back();
        prefix.push_back(nw());
        while(p!=-1&&nodes[p].nxt[c]==-1){
            nodes[p].nxt[c]=prefix.back();
            p=nodes[p].link;
        }
        nodes[prefix.back()].len=nodes[prefix[prefix.size()-2]].len+1;
        if(p==-1){
            nodes[prefix.back()].link=0;
        }else{
            int q=nodes[p].nxt[c];
            if(nodes[q].len==nodes[p].len+1){
                nodes[prefix.back()].link=q;
            }else{
                int clone=nw();
                nodes[clone]=nodes[q];
                nodes[prefix.back()].link=clone;
                nodes[q].link=clone;
                nodes[clone].len=nodes[p].len+1;
                while(p!=-1&&nodes[p].nxt[c]==q){
                    nodes[p].nxt[c]=clone;
                    p=nodes[p].link;
                }
            }
        }
    }
    ll NumberSubstring(){
        ll res=0;
        rep(i,nodes.size()){
            res+=nodes[i].len;
            if(nodes[i].link!=-1){
                res-=nodes[nodes[i].link].len;
            }
        }
        return res;
    }

    int InSubstring(string s){
        int now=0;
        rep(i,s.size()){
            if(nodes[now].nxt[give(s[i])]==-1)return 0;
            now=nodes[now].nxt[give(s[i])];
        }
        return Esize[now];
    }
    vc<int>TopoSort(){
        int n=nodes.size();
        vc<int>in_deg(n);
        rep(i,n)rep(j,sigma){
            if(nodes[i].nxt[j]>=0){
                in_deg[nodes[i].nxt[j]]++;
            }
        }
        queue<int>que;que.push(0);
        vc<int>res;
        while(que.size()){
            auto p=que.front();que.pop();
            res.pb(p);
            rep(j,sigma){
                if(nodes[p].nxt[j]>=0){
                    if(--in_deg[nodes[p].nxt[j]]==0)que.push(nodes[p].nxt[j]);
                }
            }
        }
        return res;
    }
    //'a',~,'z' を仮定してる
    //空文字は含まない
    string KthSubstring(ll k){
        k++;
        vc<ll>dp(nodes.size(),1);
        vc<int>ord=TopoSort();
        drep(i,ord.size()){
            rep(j,sigma){
                if(nodes[ord[i]].nxt[j]>=0)dp[ord[i]]+=dp[nodes[ord[i]].nxt[j]];
            }
        }
        int now=0;
        string res;
        while(1){
            if((--k)==0)break;
            rep(j,26){
                int target=nodes[now].nxt[j];if(target<0)continue;
                if(k<=dp[target]){
                    res+=j+'a';
                    now=target;
                    break;
                }else{
                    k-=dp[target];
                }
            }
        }
        return res;
    }
    string LCSusbstring(string t){
        int now=0,len=0,nb=0,nl=0;
        rep(i,t.size()){
            char x=t[i];
            while(now&&nodes[now].nxt[give(x)]<0)now=nodes[now].link,len=nodes[now].len;
            if(nodes[now].nxt[give(x)]<0){
                continue;
            }else{
                now=nodes[now].nxt[give(x)];
                len++;
                if(chmax(nl,len)){
                    nb=i-len+1;
                }
            }
        }
        return t.substr(nb,nl);
    }
};