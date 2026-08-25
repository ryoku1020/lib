#pragma once
#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

class enumerate_sequence{
    int n,m;
    class iterator{
        std::vector<int> value;
        int m;
        bool finished;
    public:
        using iterator_category=std::input_iterator_tag;
        using value_type=std::vector<int>;
        using difference_type=std::ptrdiff_t;
        using pointer=std::vector<int>*;
        using reference=std::vector<int>&;
        iterator(int n,int m,bool finished):value(n),m(m),finished(finished){}
        reference operator*(){return value;}
        pointer operator->(){return &value;}
        iterator& operator++(){
            for(int i=(int)value.size()-1;i>=0;i--){
                if(++value[i]<m)return *this;
                value[i]=0;
            }
            finished=true;
            return *this;
        }
        bool operator==(const iterator&rhs)const{
            return finished==rhs.finished&&(finished||value==rhs.value);
        }
        bool operator!=(const iterator&rhs)const{return !(*this==rhs);}
    };
public:
    enumerate_sequence(int n,int m):n(n),m(m){
        assert(n>=0);
        assert(n==0||m>0);
    }
    iterator begin()const{return {n,m,false};}
    iterator end()const{return {n,m,true};}
};

inline enumerate_sequence enumeratesequence(int n,int m){
    return {n,m};
}

inline enumerate_sequence enumeratesequece(int n,int m){
    return {n,m};
}
