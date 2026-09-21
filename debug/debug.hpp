#pragma once

#include <cctype>
#include <cstdlib>
#include <sstream>
#if defined(__unix__)||defined(__APPLE__)
#include <unistd.h>
#endif

namespace debug{

template<class T,class=void>
struct formatter{};

struct options{
    size_t max_elements=64;
    size_t max_matrix_rows=20;
    size_t max_matrix_columns=20;
    size_t max_string=200;
    int max_depth=8;
    bool color=true;
};

inline options config;

namespace internal{

template<class T>
using bare_t=remove_cvref_t<T>;

template<class T>
concept has_formatter=requires(ostream&os,const bare_t<T>&x){
    formatter<bare_t<T>>::print(os,x);
};

template<class T>
concept streamable=requires(ostream&os,const bare_t<T>&x){
    os<<x;
};

template<class T>
concept range_like=requires(const bare_t<T>&x){
    begin(x);
    end(x);
};

template<class T>
concept map_like=range_like<T>&&requires{
    typename bare_t<T>::key_type;
    typename bare_t<T>::mapped_type;
};

template<class T>
concept set_like=range_like<T>&&requires{
    typename bare_t<T>::key_type;
}&&!map_like<T>;

template<class T>
struct is_optional:false_type{};
template<class T>
struct is_optional<optional<T>>:true_type{};

template<class T>
struct is_variant:false_type{};
template<class... Ts>
struct is_variant<variant<Ts...>>:true_type{};

template<class T>
struct is_bitset:false_type{};
template<size_t N>
struct is_bitset<bitset<N>>:true_type{};

template<class T,class=void>
struct is_tuple_like:false_type{};
template<class T>
struct is_tuple_like<T,void_t<decltype(tuple_size<T>::value)>>:true_type{};

template<class T>
struct is_basic_string:false_type{};
template<class C,class R,class A>
struct is_basic_string<basic_string<C,R,A>>:true_type{};

template<class T>
struct is_string_view:false_type{};
template<class C,class R>
struct is_string_view<basic_string_view<C,R>>:true_type{};

template<class T>
struct is_matrix:false_type{};
template<class T,class A,class B>
struct is_matrix<vector<vector<T,A>,B>>:true_type{};

template<class T>
string type_name(){
#if defined(__clang__)
    string_view s=__PRETTY_FUNCTION__;
    auto l=s.find("T = ")+4;
    auto r=s.rfind(']');
#elif defined(__GNUC__)
    string_view s=__PRETTY_FUNCTION__;
    auto l=s.find("with T = ")+9;
    auto r=s.find(';',l);
#else
    return "?";
#endif
    return string(s.substr(l,r-l));
}

inline void print_escaped(ostream&os,string_view s){
    os<<'"';
    size_t n=min(s.size(),config.max_string);
    for(size_t i=0;i<n;i++){
        unsigned char c=s[i];
        if(c=='\\'||c=='"')os<<'\\'<<c;
        else if(c=='\n')os<<"\\n";
        else if(c=='\r')os<<"\\r";
        else if(c=='\t')os<<"\\t";
        else if(isprint(c))os<<c;
        else os<<"\\x"<<hex<<setw(2)<<setfill('0')<<(int)c<<dec<<setfill(' ');
    }
    if(n<s.size())os<<"…("<<s.size()-n<<" more)";
    os<<'"';
}

template<class T>
void print_value(ostream&os,const T&x,int depth);

template<class T>
string value_string(const T&x,int depth=0){
    ostringstream os;
    print_value(os,x,depth);
    return os.str();
}

template<class T>
void print_sequence(ostream&os,const T&x,int depth,char open='[',char close=']'){
    os<<open;
    size_t i=0;
    for(const auto&v:x){
        if(i==config.max_elements){
            if(i)os<<", ";
            os<<"…";
            if constexpr(requires{size(x);})os<<'('<<size(x)-i<<" more)";
            break;
        }
        if(i++)os<<", ";
        print_value(os,v,depth+1);
    }
    os<<close;
}

template<class T>
void print_matrix(ostream&os,const T&x,int depth){
    size_t rows=x.size(),cols=rows?x[0].size():0;
    bool rectangular=all_of(x.begin(),x.end(),[&](const auto&row){return row.size()==cols;});
    if(!rectangular){
        print_sequence(os,x,depth);
        return;
    }
    size_t shown_rows=min(rows,config.max_matrix_rows);
    size_t shown_cols=min(cols,config.max_matrix_columns);
    vector<vector<string>> cell(shown_rows,vector<string>(shown_cols));
    vector<size_t> width(shown_cols,1);
    for(size_t i=0;i<shown_rows;i++)for(size_t j=0;j<shown_cols;j++){
        cell[i][j]=value_string(x[i][j],depth+1);
        width[j]=max(width[j],cell[i][j].size());
    }
    size_t iw=max<size_t>(1,to_string(rows?rows-1:0).size());
    os<<'['<<rows<<" x "<<cols<<']';
    if(!rows||!cols)return;
    os<<'\n'<<string(iw+3,' ');
    for(size_t j=0;j<shown_cols;j++)os<<setw(width[j]+1)<<j;
    if(shown_cols<cols)os<<"  …";
    for(size_t i=0;i<shown_rows;i++){
        os<<'\n'<<setw(iw)<<i<<" |";
        for(size_t j=0;j<shown_cols;j++)os<<' '<<setw(width[j])<<cell[i][j];
        if(shown_cols<cols)os<<"  …";
    }
    if(shown_rows<rows)os<<'\n'<<setw(iw)<<"…"<<" |";
}

template<class T,size_t... I>
void print_tuple(ostream&os,const T&x,int depth,index_sequence<I...>){
    os<<'(';
    size_t i=0;
    ((i++?os<<", ":os,print_value(os,get<I>(x),depth+1)),...);
    if constexpr(sizeof...(I)==1)os<<',';
    os<<')';
}

template<class T>
void print_value(ostream&os,const T&x,int depth){
    using U=bare_t<T>;
    if(depth>config.max_depth){
        os<<"<max-depth>";
    }else if constexpr(has_formatter<U>){
        formatter<U>::print(os,x);
    }else if constexpr(is_same_v<U,bool>){
        os<<(x?"true":"false");
    }else if constexpr(is_same_v<U,char>){
        os<<'\''<<x<<'\'';
    }else if constexpr(is_basic_string<U>::value||is_string_view<U>::value){
        print_escaped(os,string_view(x));
    }else if constexpr(is_same_v<U,const char*>||is_same_v<U,char*>){
        if(x)print_escaped(os,string_view(x));else os<<"nullptr";
    }else if constexpr(is_array_v<U>&&is_same_v<remove_extent_t<U>,char>){
        print_escaped(os,string_view(x));
    }else if constexpr(is_bitset<U>::value){
        os<<"index: ";
        for(size_t i=0;i<x.size();i++)os<<i%10;
        os<<"\nbit  : ";
        for(size_t i=0;i<x.size();i++)os<<(x[i]?'1':'0');
    }else if constexpr(is_optional<U>::value){
        if(x){os<<"some(";print_value(os,*x,depth+1);os<<')';}
        else os<<"none";
    }else if constexpr(is_variant<U>::value){
        os<<"variant["<<x.index()<<"](";
        visit([&](const auto&v){print_value(os,v,depth+1);},x);
        os<<')';
    }else if constexpr(is_matrix<U>::value){
        print_matrix(os,x,depth);
    }else if constexpr(map_like<U>){
        os<<'{';
        size_t i=0;
        for(const auto&[k,v]:x){
            if(i==config.max_elements){os<<"\n  …";break;}
            os<<(i++?"\n  ":"\n  ");
            print_value(os,k,depth+1);os<<" => ";print_value(os,v,depth+1);
        }
        if(i)os<<'\n';
        os<<'}';
    }else if constexpr(set_like<U>){
        print_sequence(os,x,depth,'{','}');
    }else if constexpr(is_tuple_like<U>::value&&!range_like<U>){
        print_tuple(os,x,depth,make_index_sequence<tuple_size_v<U>>{});
    }else if constexpr(range_like<U>){
        print_sequence(os,x,depth);
    }else if constexpr(streamable<U>){
        os<<x;
    }else{
        os<<"<unprintable "<<type_name<U>()<<'>';
    }
}

inline vector<string> expression_names(string_view source){
    vector<string> result;
    size_t begin=0;
    int round=0,square=0,curly=0,angle=0;
    char quote=0;
    bool escape=false;
    for(size_t i=0;i<=source.size();i++){
        char c=i<source.size()?source[i]:',';
        if(quote){
            if(escape)escape=false;
            else if(c=='\\')escape=true;
            else if(c==quote)quote=0;
            continue;
        }
        if(c=='\''||c=='"'){quote=c;continue;}
        if(c=='(')round++;else if(c==')')round--;
        else if(c=='[')square++;else if(c==']')square--;
        else if(c=='{')curly++;else if(c=='}')curly--;
        else if(c=='<'&&i+1<source.size()&&source[i+1]!='='&&source[i+1]!='<'){
            auto close=source.find('>',i+1);
            if(close!=string_view::npos)angle++;
        }
        else if(c=='>'&&angle&&!(i+1<source.size()&&source[i+1]=='='))angle--;
        if(c==','&&!round&&!square&&!curly&&!angle){
            size_t l=begin,r=i;
            while(l<r&&isspace((unsigned char)source[l]))l++;
            while(l<r&&isspace((unsigned char)source[r-1]))r--;
            result.emplace_back(source.substr(l,r-l));
            begin=i+1;
        }
    }
    return result;
}

inline bool use_color(){
    if(!config.color||getenv("NO_COLOR"))return false;
#if defined(__unix__)||defined(__APPLE__)
    if(!isatty(fileno(stdout)))return false;
#endif
    const char*term=getenv("TERM");
    return term&&string_view(term)!="dumb";
}

inline string paint(string_view code,string_view text,bool color){
    return color?"\033["+string(code)+"m"+string(text)+"\033[0m":string(text);
}

inline void print_lines(ostream&os,string_view prefix,string_view value){
    size_t begin=0;
    while(1){
        auto end=value.find('\n',begin);
        os<<prefix<<value.substr(begin,end==string_view::npos?value.size()-begin:end-begin)<<'\n';
        if(end==string_view::npos)break;
        begin=end+1;
    }
}

template<class... Ts>
void log(const char*file,int line,const char*function,string_view source,const Ts&...xs){
    auto names=expression_names(source);
    vector<string> values{value_string(xs)...};
    size_t width=0;
    for(const auto&name:names)width=max(width,name.size());
    bool color=use_color();
    cout<<paint("2","┌─ DBG "+string(function)+" · "+string(file)+":"+to_string(line),color)<<'\n';
    for(size_t i=0;i<values.size();i++){
        string name=i<names.size()?names[i]:"arg"+to_string(i);
        string lead="│ "+paint("36",name,color)+string(width-name.size(),' ')+" = ";
        auto newline=values[i].find('\n');
        cout<<lead<<values[i].substr(0,newline)<<'\n';
        if(newline!=string::npos)print_lines(cout,"│ "+string(width+3,' '),string_view(values[i]).substr(newline+1));
    }
    cout<<paint("2","└─",color)<<'\n';
}

}

template<class T>
void print_value(ostream&os,const T&x){
    internal::print_value(os,x,0);
}

template<class T>
string to_string(const T&x){
    return internal::value_string(x);
}

}

#define dbg(...) do{if(dbging!=0)::debug::internal::log(__FILE__,__LINE__,__func__,#__VA_ARGS__ __VA_OPT__(,) __VA_ARGS__);}while(0)
