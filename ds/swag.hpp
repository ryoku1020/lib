#pragma once
template<class X>
struct SlidingWindowAggregation{
    using value_type=X::value_type;
    vc<value_type>left,right;
    vc<value_type>left_data,right_data;
    SlidingWindowAggregation(){
        left_data.push_back(X::e());
        right_data.push_back(X::e());
    }
    void push_front(value_type v){
        left.push_back(v);
        left_data.push_back(X::op(v,left_data.back()));
    }
    void push_back(value_type v){
        right.push_back(v);
        right_data.push_back(X::op(right_data.back(),v));
    }
    vc<value_type>nl,nr;
    void balance(){
        if(right.empty()){
            int ms=(left.size()+1)/2;
            nl.reserve(ms);
            nr.reserve(left.size()-ms);
            rep(i,ms)nr.push_back(left[i]);
            REP(i,ms,left.size())nl.push_back(left[i]);
            reverse(all(nr));
            left=move(nl);
            right=move(nr);
        }else if(left.empty()){
            int ms=(right.size()+1)/2;
            nl.reserve(ms);
            nr.reserve(right.size()-ms);
            rep(i,ms)nl.push_back(right[i]);
            REP(i,ms,right.size())nr.push_back(right[i]);
            reverse(all(nl)); 
            left=move(nl);
            right=move(nr);
        }
        
        left_data={X::e()};
        left_data.reserve(left.size()+1);
        for(auto&v:left)left_data.push_back(X::op(v,left_data.back()));
        right_data={X::e()};
        right_data.reserve(right.size()+1);
        for(auto&v:right)right_data.push_back(X::op(right_data.back(),v));
    }
    value_type get_all(){
        return X::op(left_data.back(),right_data.back());
    }
    void pop_front(){
        assert(left.size()+right.size()>0);
        if(left.empty())balance();
        left.pop_back();
        left_data.pop_back();
    }
    void pop_back(){
        assert(left.size()+right.size()>0);
        if(right.empty())balance();
        right.pop_back();
        right_data.pop_back();
    }
};
template<class X>
struct OneWaySlidingWindowAggregation{
    using value_type=X::value_type;
    vc<value_type>s1,s2;
    vc<value_type>S1,S2;
    void push_back(value_type x){
        s2.push_back(x);
        if(S2.size())S2.push_back(X::op(S2.back(),x));
        else S2.push_back(x);
    }
    void push_front(value_type x){
        s1.push_back(x);
        if(S1.size())S1.push_back(X::op(x,S1.back()));
        else S1.push_back(x);
    }
    void modify(){
        assert(s1.empty());
        while(s2.size()){
            auto p=s2.back();s2.pop_back();S2.pop_back();
            s1.push_back(p);
            if(S1.size())S1.push_back(X::op(p,S1.back()));
            else S1.push_back(p);
        }
    }
    void pop_front(){
        assert(s1.size()+s2.size()>0);
        if(s1.empty()){
            modify();        
        }
        s1.pop_back();S1.pop_back();
    }
    value_type get_all(){
        if(s1.empty()){
            modify();
        }
        value_type t1,t2;
        if(S1.empty())t1=X::e();
        else t1=S1.back();
        if(S2.empty())t2=X::e();
        else t2=S2.back();
        return X::op(t1,t2);
    }
};
