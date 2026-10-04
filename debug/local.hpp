#pragma once
#include "debug.hpp"
namespace ryoku{}
namespace debug{
using namespace ryoku;
template<class T>
struct raw_view{const T&value;};
template<class T>
struct tree_view{const T&value;};
template<class T,class Root>
struct version_view{T&value;Root root;};
template<class T>
struct bcc_view{const T&value;};
template<class T>
raw_view<T>raw(const T&value){return{value};}
template<class T>
tree_view<T>tree(const T&value){return{value};}
template<class T,class Root>
version_view<T,Root>version(T&value,Root root){return{value,root};}
template<class T>
bcc_view<T>bcc(const T&value){return{value};}
namespace internal{
template<class T>
struct raw_formatter{
    static void print(ostream&os,const T&value){print_value(os,value,0);}
};
}
namespace internal{
template<class T>
struct tree_formatter:raw_formatter<T>{};
}
namespace internal{
template<class F>
void print_index_values(ostream&os,size_t n,F get){
    auto indices=shown_indices(n,config.max_sequence_elements);
    vector<string>index_text,value_text;
    vector<size_t>width;
    for(auto i:indices){
        if(i==numeric_limits<size_t>::max()){
            index_text.push_back("…");value_text.push_back("…");width.push_back(1);
        }else{
            index_text.push_back(to_string(i));value_text.push_back(value_string(get(i)));
            width.push_back(max(visible_width(index_text.back()),visible_width(value_text.back())));
        }
    }
    os<<"idx :";
    for(size_t i=0;i<indices.size();i++){os<<' ';print_right(os,index_text[i],width[i]);}
    os<<"\nval :";
    for(size_t i=0;i<indices.size();i++){os<<' ';print_right(os,value_text[i],width[i]);}
}
}
namespace internal{
template<class T>
void print_index_values(ostream&os,const vector<T>&values){
    print_index_values(os,values.size(),[&](size_t i)->const T&{return values[i];});
}
}
namespace internal{
inline void print_table_row(ostream&os,const vector<string>&row,const vector<size_t>&width){
    for(size_t i=0;i<row.size();i++){
        if(i)os<<" | ";
        print_right(os,row[i],width[i]);
    }
}
}
template<class T>
struct formatter<raw_view<T>>{
    static void print(ostream&os,const raw_view<T>&view){internal::raw_formatter<T>::print(os,view.value);}
};
template<class T>
struct formatter<tree_view<T>>{
    static void print(ostream&os,const tree_view<T>&view){internal::tree_formatter<T>::print(os,view.value);}
};
}
