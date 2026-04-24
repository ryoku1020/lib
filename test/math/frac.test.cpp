#include <cassert>
#include "../../math/frac.hpp"

int main(){
    using F=Frac<ll>;
    F a(2,4),b(1,6);
    assert(a.a==1&&a.b==2);
    assert(a+b==F(2,3));
    assert(a-b==F(1,3));
    assert(a*b==F(1,12));
    assert(a/b==F(3));
    assert(F(-1,2)<F(0));

    using G=Frac<ll,false>;
    G c(2,4),d(1,6);
    assert(c.a==2&&c.b==4);
    c+=d;
    assert(c.a==16&&c.b==24);
    assert(c==G(2,3));
    c.reduce();
    assert(c.a==2&&c.b==3);
    G e(2,4);
    e*=G(2,3);
    assert(e.a==4&&e.b==12);
}
