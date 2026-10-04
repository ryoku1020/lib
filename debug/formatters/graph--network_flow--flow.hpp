#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class Cap>
struct formatter<flow<Cap>>{
    static void print(ostream&os,const flow<Cap>&network){
        os<<"flow [n="<<network.n<<", m="<<network.edges.size()<<"]\n\n";
        vector<vector<string>>rows{{"id","from -> to","flow / cap"}};
        auto indices=internal::shown_indices(network.edges.size(),config.max_graph_edges);
        for(auto i:indices){
            if(i==numeric_limits<size_t>::max()){rows.push_back({"…","…","…"});continue;}
            const auto&e=network.edges[i];
            string flow_value=i<network._flow.size()?internal::value_string(network._flow[i]):"not-run";
            rows.push_back({to_string(e.id),to_string(e.from)+" -> "+to_string(e.to),
                            flow_value+" / "+internal::value_string(e.cost)});
        }
        vector<size_t>width(3);
        for(const auto&row:rows)for(size_t i=0;i<row.size();i++)width[i]=max(width[i],internal::visible_width(row[i]));
        internal::print_table_row(os,rows[0],width);
        os<<'\n'<<string(width[0],'-')<<"-+-"<<string(width[1],'-')<<"-+-"<<string(width[2],'-');
        for(size_t i=1;i<rows.size();i++){os<<'\n';internal::print_table_row(os,rows[i],width);}
    }
};
}
