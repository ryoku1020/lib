#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../template.hpp"
#include "../../geometry/base.hpp"
using namespace ryoku;

using P=Point<ll>;

int main(){
    INT(n);
    vc<P>p(n);
    rep(i,n)cin>>p[i];
    sort(all(p));
    rep(i,n)cout<<p[i].x<<" "<<p[i].y<<"\n";
}
