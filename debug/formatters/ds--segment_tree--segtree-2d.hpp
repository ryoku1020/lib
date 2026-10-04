#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class Info>
struct formatter<segtree_2d<Info>>{
    static void print(ostream&os,const segtree_2d<Info>&seg){
        os<<"segtree_2d "<<seg.H<<" x "<<seg.W<<" (use prod() to inspect a rectangle)";
    }
};
}
