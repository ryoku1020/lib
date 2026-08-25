#define IGNORE
#include <cassert>
#include "../../template.hpp"
#include "../../math/mat.hpp"

int main(){
    matrix<int>a(vvc<int>{{1,2},{3,4}});
    assert((a*2)[0][0]==2&&(a*2)[1][1]==8);
    assert((2*a)[0][1]==4&&(2*a)[1][0]==6);
    a*=3;
    assert(a[0][0]==3&&a[1][1]==12);
}
