#pragma once
#include "../template.hpp"
template<class T>
struct DoublePriorityQueue{
    struct RemovalPriorityQueue1{
        smpq<T> q,rq;
        void push(T x){q.push(x);}
        void remove(T x){rq.push(x);}
        void pop(){
            modify();
            assert(!q.empty());
            q.pop();
        }
        T top(){modify();assert(!q.empty());return q.top();}
        void modify(){
            while(q.size()&&rq.size()&&q.top()==rq.top()){
                rq.pop(),q.pop();
            }
        }
        int size(){
            return q.size()-rq.size();
        }
    };
    struct RemovalPriorityQueue2{
        bipq<T> q,rq;
        void push(T x){q.push(x);}
        void remove(T x){rq.push(x);}
        void pop(){
            modify();
            assert(!q.empty());
            q.pop();
        }
        T top(){modify();assert(!q.empty());return q.top();}
        void modify(){
            while(q.size()&&rq.size()&&q.top()==rq.top()){
                rq.pop(),q.pop();
            }
        }
    };
    RemovalPriorityQueue1 left;
    RemovalPriorityQueue2 right;
    void push(T x){
        left.push(x);
        right.push(x);
    }
    T front(){
        assert(size());
        return left.top();
    }
    T back(){
        assert(size());
        return right.top();
    }
    T pop_front(){
        assert(size());
        auto res=left.top();left.pop();right.remove(res);
        return res;
    }
    T pop_back(){
        assert(size());
        auto res=right.top();right.pop();left.remove(res);
        return res;
    }
    int size(){
        return left.size();
    }
};
