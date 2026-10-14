#include "../../template.hpp"
#include "../../math/fixed-mat.hpp"

struct unprintable{int value;};

int main(){
    int called=0;
    auto f=[&](){called++;return unprintable{};};
    dbg(f());
    auto fixed=[&](){called++;return ryoku::fixed_matrix<int,2,2>::unit();};
    auto matrix=[&](){called++;return ryoku::matrix<int>::unit(2);};
    dbg(fixed(),matrix());
    return called;
}
