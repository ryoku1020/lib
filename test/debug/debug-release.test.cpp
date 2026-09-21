#include "../../template.hpp"

struct unprintable{int value;};

int main(){
    int called=0;
    auto f=[&](){called++;return unprintable{};};
    dbg(f());
    return called;
}
