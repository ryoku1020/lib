#pragma once
vc<int>sf_array(vc<int>s,bool first=true){
    assert(s.size()<=numeric_limits<int>::max());
    if(s.empty())return {};
    auto smin=min(s);for(auto&x:s)x-=smin;
    enum Type{
        S,
        L,
        LMS
    };
    auto convert=[&](Type x){
        if(x==Type::L)return x;
        return Type::S;
    };
    if(first==0&&max(s)+1==s.size()){
        vc<int>ans(s.size());
        rep(i,s.size()){
            ans[s[i]]=i;
        }
        return ans;
    }
    if(first){
        for(auto&x:s)x++;
        s.pb(0);
    }
    const int MAX=max(s)+1; 
    vc<Type>type(s.size());
    type.back()=Type::S;
    drep(i,(int)s.size()-1){
        if(s[i]<s[i+1])type[i]=Type::S;
        if(s[i]>s[i+1])type[i]=Type::L;
        if(s[i]==s[i+1])type[i]=type[i+1];
    }
    rep(i,(int)s.size()-1){
        if(type[i]==Type::L&&type[i+1]==Type::S){
            type[i+1]=Type::LMS;
        }
    }
    vc<int>cnt(MAX),start(MAX);
    for(auto&x:s)cnt[x]++;
    REP(i,1,MAX){
        start[i]=start[i-1]+cnt[i-1];
    }
    vc<int>l(MAX),r(MAX);
    rep(i,MAX){
        if(i)l[i]=r[i-1]+1;
        r[i]=l[i]+cnt[i]-1;
    }
    vc<int>ans(s.size(),-1);
    auto push_front=[&](int x){
        ans[l[s[x]]++]=x;
    }; 
    auto push_back=[&](int x){ 
        ans[r[s[x]]--]=x;
    };
    auto induced_sorting=[&](){
        rep(i,ans.size()){
            auto&x=ans[i];
            if(x!=-1&&x&&type[x-1]==Type::L){
                push_front(x-1);
            }
        }
        drep(i,s.size()){
            auto&x=ans[i];
            if(x!=-1&&x&&convert(type[x-1])==Type::S){
                push_back(x-1);
            }
        }   
    };
    
    rep(i,s.size()){
        if(type[i]==Type::LMS){
            push_back(i);
        }
    }
    rep(i,MAX){
        r[i]=l[i]+cnt[i]-1;
    }
    induced_sorting();
    vc<int>LMS_ord;
    vc<int>pus;
    auto same=[&](int l,int r){
        if(s[l]!=s[r])return 0;
        for(int i=1;;i++){
            if(s[l+i]!=s[r+i])return 0;
            if(type[l+i]==Type::LMS&&type[r+i]==Type::LMS){
                return 1;
            }
            if(type[l+i]==Type::LMS)return 0;
            if(type[r+i]==Type::LMS)return 0;
        }
    };
    vc<int>inv(s.size());
    int pre=-1;
    int sz=0;
    rep(i,ans.size())if(type[ans[i]]==Type::LMS){
        LMS_ord.pb(ans[i]);
        ++sz;
        inv[ans[i]]=sz-1;
        if(pus.size()){
            pus.pb(pus.back()+(!same(pre,ans[i])));
        }else pus.pb(0);
        pre=ans[i];
    }
    vc<int>nw;
    vc<int>lms_pos;
    rep(i,s.size()){
        if(type[i]==Type::LMS){
            nw.pb(pus[inv[i]]);
            lms_pos.pb(i);
        }
    }
    
    auto res=sf_array(nw,false);
    rep(i,MAX){
        if(i)l[i]=r[i-1]+1;
        r[i]=l[i]+cnt[i]-1;
    }
    reverse(all(res));
    ans=vc<int>(s.size(),-1);
    for(auto&x:res){
        push_back(lms_pos[x]);
    }
    rep(i,MAX){
        if(i)l[i]=r[i-1]+1;
        r[i]=l[i]+cnt[i]-1;
    }
    induced_sorting();
    if(first)ans.erase(ans.begin());
    return ans;
}

vc<int>sf_array(string s){
    assert(s.size()<=numeric_limits<int>::max());
    if(s.empty())return {};
    char c=CHAR_MAX;
    for(auto&x:s)chmin(c,x);
    vc<int>S(s.size());
    rep(i,s.size())S[i]=s[i]-c;
    return sf_array(S);
}
vc<int>lcp_array(vc<int>s){
    assert(s.size()<=numeric_limits<int>::max());
    if(s.empty())return {};
    auto sf=sf_array(s);
    sf.insert(sf.begin(),s.size());
    vc<int>rank(s.size()+1);
    rep(i,sf.size()){
        rank[sf[i]]=i;
    }
    vc<int>LCP(s.size());
    int h=0;
    rep(i,s.size()){
        int j=sf[rank[i]-1];
        if(h)--h;
        for(;j+h<s.size()&&i+h<s.size();h++){
            if(s[j+h]!=s[i+h])break;
        }
        LCP[rank[i]-1]=h;
    }
    LCP.erase(LCP.begin());
    return LCP;
}
vc<int>lcp_array(string s){
    assert(s.size()<=numeric_limits<int>::max());
    if(s.empty())return {};
    char c=CHAR_MAX;
    for(auto&x:s)chmin(c,x);
    vc<int>S(s.size());
    rep(i,s.size())S[i]=s[i]-c;
    return lcp_array(S);
}
