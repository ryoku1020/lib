#pragma once
template<class string>
vc<int>prefix_function(const string&s){
    vc<int>pi(s.size());
    REP(i,1,s.size()){
        int j=pi[i-1];
        while(j&&s[j]!=s[i])j=pi[j-1];
        if(s[j]==s[i])j++;
        pi[i]=j;
    }
    return pi;
}
template<class string>
int period(const string&s){
    auto f=prefix_function(s);
    if(s.size()%(s.size()-f.back())==0)return s.size()-f.back();
    return s.size();
}
template<class string,int ban='~'>
vc<int>find_pattern(const string&s,const string&pattern){
    assert(pattern.size());
    string t=pattern;t.push_back(ban);for(auto&x:s)t.push_back(x);
    vc<int>pi=prefix_function(t);
    vc<int>ans;
    REP(i,pattern.size()+1,t.size()){
        if(pi[i]==pattern.size()){
            ans.push_back(i-pattern.size()*2);
        }
    }
    return ans;
}
