#include"base.hpp"
template<class mint>
fps<mint>all_prod(vc<fps<mint>>v){
    assert(mint::get_mod());
    using fps=fps<mint>;
    if(v.empty())return {1};
    auto cmp=[&](auto&a,auto&b){return a.size()>b.size();};
    priority_queue<fps,vc<fps>,decltype(cmp)>pq(cmp);
    for(auto&p:v)pq.push(std::move(p));
    while(pq.size()>=2){
        auto p1=std::move(pq.top());pq.pop();
        auto p2=std::move(pq.top());pq.pop();
        pq.push(std::move(p1*p2));
    }
    return pq.top();
}
