#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T>
struct formatter<::ryoku::tree<T>>{
    static void print(ostream&os,const ::ryoku::tree<T>&tr){
        auto copy=tr;
        copy.build();
        os<<"tree / HLD [n="<<copy.n<<"]\n\n";
        vector<vector<string>>rows{{"v","par","dep","head","in","out","size","comp"}};
        auto vertices=internal::shown_indices(copy.n,config.max_tree_nodes);
        for(auto v:vertices){
            if(v==numeric_limits<size_t>::max()){rows.push_back({"⋮","⋮","⋮","⋮","⋮","⋮","⋮","⋮"});continue;}
            rows.push_back({to_string(v),to_string(copy.par[v]),to_string(copy.depth[v]),to_string(copy.head[v]),
                            to_string(copy.in[v]),to_string(copy.out[v]),to_string(copy.size_[v]),to_string(copy.cp[v])});
        }
        vector<size_t>width(8);
        for(const auto&row:rows)for(size_t i=0;i<row.size();i++)width[i]=max(width[i],internal::visible_width(row[i]));
        internal::print_table_row(os,rows[0],width);
        os<<'\n'<<string(width[0],'-');
        for(size_t i=1;i<width.size();i++)os<<"-+-"<<string(width[i],'-');
        for(size_t i=1;i<rows.size();i++){os<<'\n';internal::print_table_row(os,rows[i],width);}
    }
};
}
