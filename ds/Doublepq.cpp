#pragma once
#include"../template.cpp"
template<class T>
struct Doublepq{
    struct removalpq1{
        smpq<T> q,rq;
        void push(T x){q.push(x);}
        void remove(T x){rq.push(x);}
        void pop(){
            modify();
            q.pop();
        }
        T top(){modify();return q.top();}
        void modify(){
            while(q.size()&&rq.size()&&q.top()==rq.top()){
                rq.pop(),q.pop();
            }
        }
        int size(){
            return q.size()-rq.size();
        }
    };
    struct removalpq2{
        bipq<T> q,rq;
        void push(T x){q.push(x);}
        void remove(T x){rq.push(x);}
        void pop(){
            modify();
            q.pop();
        }
        T top(){modify();return q.top();}
        void modify(){
            while(q.size()&&rq.size()&&q.top()==rq.top()){
                rq.pop(),q.pop();
            }
        }
    };
    removalpq1 left;
    removalpq2 right;
    void push(T x){
        left.push(x);
        right.push(x);
    }
    T front(){
        return left.top();
    }
    T back(){
        return right.top();
    }
    T pop_front(){
        auto res=left.top();left.pop();right.remove(res);
        return res;
    }
    T pop_back(){
        auto res=right.top();right.pop();left.remove(res);
        return res;
    }
    int size(){
        return left.size();
    }
};