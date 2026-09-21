#pragma once

#include <cctype>
#include <cstdlib>
#include <sstream>
#include <typeinfo>
#if defined(__unix__)||defined(__APPLE__)
#include <unistd.h>
#endif

namespace debug{

template<class T,class=void>
struct formatter{};

struct options{
    size_t max_sequence_elements=128;
    size_t max_tree_nodes=64;
    size_t max_graph_vertices=48;
    size_t max_graph_edges=96;
    size_t max_matrix_rows=16;
    size_t max_matrix_columns=16;
    size_t max_bit_count=256;
    size_t max_string=200;
    int max_depth=8;
    bool color=true;
};

inline options config;

template<class T>
struct full_view{const T&value;};

template<class T>
full_view<T>full(const T&value){return{value};}

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
    auto begin=s.find("T = ");
    auto l=begin==string_view::npos?begin:begin+4;
    auto r=l==string_view::npos?l:s.rfind(']');
#elif defined(__GNUC__)
    string_view s=__PRETTY_FUNCTION__;
    auto begin=s.find("with T = ");
    auto l=begin==string_view::npos?begin:begin+9;
    auto r=l==string_view::npos?l:s.find(';',l);
    if(l!=string_view::npos&&r==string_view::npos)r=s.rfind(']');
#elif defined(_MSC_VER)
    string_view s=__FUNCSIG__;
    auto begin=s.find("type_name<");
    auto l=begin==string_view::npos?begin:begin+10;
    auto r=l==string_view::npos?l:s.find(">(void)",l);
#else
    string_view s=typeid(T).name();
    auto l=size_t(0),r=s.size();
#endif
    if(l==string_view::npos||r==string_view::npos||l>r)return typeid(T).name();
    return string(s.substr(l,r-l));
}

inline void print_escaped_char(ostream&os,unsigned char c,char quote){
    if(c=='\\'||c==(unsigned char)quote)os<<'\\'<<c;
    else if(c=='\0')os<<"\\0";
    else if(c=='\n')os<<"\\n";
    else if(c=='\r')os<<"\\r";
    else if(c=='\t')os<<"\\t";
    else if(c=='\b')os<<"\\b";
    else if(c=='\f')os<<"\\f";
    else if(c=='\v')os<<"\\v";
    else if(isprint(c))os<<c;
    else os<<"\\x"<<hex<<setw(2)<<setfill('0')<<(int)c<<dec<<setfill(' ');
}

inline void print_escaped(ostream&os,string_view s){
    os<<'"';
    size_t n=min(s.size(),config.max_string);
    for(size_t i=0;i<n;i++){
        print_escaped_char(os,(unsigned char)s[i],'"');
    }
    if(n<s.size())os<<"…";
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

inline vector<size_t>shown_indices(size_t n,size_t limit){
    vector<size_t>result;
    if(limit==numeric_limits<size_t>::max()||n<=limit){
        result.resize(n);
        iota(result.begin(),result.end(),0);
        return result;
    }
    size_t head=(limit+1)/2,tail=limit/2;
    for(size_t i=0;i<head;i++)result.push_back(i);
    result.push_back(numeric_limits<size_t>::max());
    for(size_t i=n-tail;i<n;i++)result.push_back(i);
    return result;
}

inline size_t visible_width(string_view s){
    size_t width=0;
    for(unsigned char c:s)if((c&0xc0)!=0x80)width++;
    return width;
}

inline void print_right(ostream&os,string_view s,size_t width){
    auto length=visible_width(s);
    if(length<width)os<<string(width-length,' ');
    os<<s;
}

inline string shorten(string_view s,size_t limit){
    if(visible_width(s)<=limit)return string(s);
    if(!limit)return string();
    if(limit==1)return "…";
    size_t head=(limit-1)*2/3,tail=limit-1-head;
    size_t head_end=0,head_width=0;
    while(head_end<s.size()&&head_width<head){
        head_end++;
        while(head_end<s.size()&&((unsigned char)s[head_end]&0xc0)==0x80)head_end++;
        head_width++;
    }
    size_t tail_begin=s.size(),tail_width=0;
    while(tail_begin&&tail_width<tail){
        tail_begin--;
        if(((unsigned char)s[tail_begin]&0xc0)!=0x80)tail_width++;
    }
    return string(s.substr(0,head_end))+"…"+string(s.substr(tail_begin));
}

template<class T>
void print_sequence(ostream&os,const T&x,int depth,char open='[',char close=']'){
    if constexpr(requires{size(x);}){
        size_t n=size(x),i=0,printed=0;
        auto indices=shown_indices(n,config.max_sequence_elements);
        vector<string>items;
        for(const auto&v:x){
            while(printed<indices.size()&&indices[printed]==numeric_limits<size_t>::max()){
                items.push_back("…");
                printed++;
            }
            if(printed==indices.size())break;
            if(i==indices[printed]){
                items.push_back(value_string(v,depth+1));
                printed++;
            }
            i++;
        }
        size_t total=2;
        bool multiline=false;
        for(const auto&item:items){
            total+=visible_width(item)+2;
            multiline|=item.find('\n')!=string::npos;
        }
        bool wrap=multiline||total>120;
        os<<open;
        size_t column=1;
        for(size_t j=0;j<items.size();j++){
            size_t width=visible_width(items[j]);
            bool next_line=wrap&&(j==0||column+2+width>118||items[j].find('\n')!=string::npos);
            if(j)os<<',';
            if(next_line){os<<"\n  ";column=2;}
            else if(j){os<<' ';column+=2;}
            size_t begin=0;
            while(1){
                auto end=items[j].find('\n',begin);
                auto part=string_view(items[j]).substr(begin,end==string::npos?items[j].size()-begin:end-begin);
                os<<part;column+=visible_width(part);
                if(end==string::npos)break;
                os<<"\n  ";column=2;begin=end+1;
            }
        }
        if(wrap&&!items.empty())os<<'\n';
        os<<close;
    }else{
        os<<open;
        size_t i=0;
        for(const auto&v:x){
            if(i==config.max_sequence_elements){os<<", …";break;}
            if(i++)os<<", ";
            print_value(os,v,depth+1);
        }
        os<<close;
    }
}

template<class T>
void print_matrix(ostream&os,const T&x,int depth){
    size_t rows=x.size(),cols=rows?x[0].size():0;
    bool rectangular=all_of(x.begin(),x.end(),[&](const auto&row){return row.size()==cols;});
    if(!rectangular){
        print_sequence(os,x,depth);
        return;
    }
    auto row_index=shown_indices(rows,config.max_matrix_rows);
    auto col_index=shown_indices(cols,config.max_matrix_columns);
    vector<vector<string>>cell(row_index.size(),vector<string>(col_index.size()));
    vector<size_t>width(col_index.size(),1);
    bool multiline=false;
    for(size_t i=0;i<row_index.size();i++)for(size_t j=0;j<col_index.size();j++){
        if(row_index[i]==numeric_limits<size_t>::max()||col_index[j]==numeric_limits<size_t>::max()){
            cell[i][j]="…";
            continue;
        }
        cell[i][j]=value_string(x[row_index[i]][col_index[j]],depth+1);
        multiline|=cell[i][j].find('\n')!=string::npos;
        width[j]=max({width[j],visible_width(cell[i][j]),to_string(col_index[j]).size()});
    }
    if(multiline){print_sequence(os,x,depth);return;}
    size_t iw=max<size_t>(1,to_string(rows?rows-1:0).size());
    os<<'['<<rows<<" × "<<cols<<']';
    if(!rows||!cols)return;
    os<<'\n'<<string(iw+3,' ');
    for(size_t j=0;j<col_index.size();j++){
        if(col_index[j]==numeric_limits<size_t>::max()){os<<' ';print_right(os,"…",width[j]);}
        else os<<setw(width[j]+1)<<col_index[j];
    }
    for(size_t i=0;i<row_index.size();i++){
        if(row_index[i]==numeric_limits<size_t>::max()){
            os<<'\n'<<setw(iw)<<"⋮"<<" |";
            continue;
        }
        os<<'\n'<<setw(iw)<<row_index[i]<<" |";
        for(size_t j=0;j<col_index.size();j++){os<<' ';print_right(os,cell[i][j],width[j]);}
    }
}

template<class F>
void print_bits(ostream&os,size_t n,F bit){
    if(n<=64){
        os<<"index : ";for(size_t i=0;i<n;i++)os<<i%10;
        os<<"\nbit   : ";for(size_t i=0;i<n;i++)os<<(bit(i)?'1':'0');
        return;
    }
    size_t limit=max<size_t>(64,config.max_bit_count);
    size_t chunk_limit=limit==numeric_limits<size_t>::max()?limit:(limit+63)/64;
    auto chunks=shown_indices((n+63)/64,chunk_limit);
    for(size_t k=0;k<chunks.size();k++){
        if(k)os<<'\n';
        if(chunks[k]==numeric_limits<size_t>::max()){os<<"     …";continue;}
        size_t l=chunks[k]*64,r=min(n,l+64);
        os<<setw(5)<<l<<": ";
        for(size_t i=l;i<r;i++)os<<(bit(i)?'1':'0');
    }
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
        os<<'\'';print_escaped_char(os,(unsigned char)x,'\'');os<<'\'';
    }else if constexpr(is_basic_string<U>::value||is_string_view<U>::value){
        print_escaped(os,string_view(x));
    }else if constexpr(is_same_v<U,const char*>||is_same_v<U,char*>){
        if(x)print_escaped(os,string_view(x));else os<<"nullptr";
    }else if constexpr(is_array_v<U>&&is_same_v<remove_extent_t<U>,char>){
        constexpr size_t N=extent_v<U>;
        size_t n=N&&x[N-1]=='\0'?N-1:N;
        print_escaped(os,string_view(x,n));
    }else if constexpr(is_bitset<U>::value){
        print_bits(os,x.size(),[&](size_t i){return x[i];});
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
        size_t n=size(x);
        auto indices=shown_indices(n,config.max_sequence_elements);
        vector<pair<string,string>>items;
        size_t current=0,next=0;
        for(const auto&[k,v]:x){
            while(next<indices.size()&&indices[next]==numeric_limits<size_t>::max()){
                items.push_back({"…",string()});next++;
            }
            if(next==indices.size())break;
            if(current==indices[next]){
                items.push_back({value_string(k,depth+1),value_string(v,depth+1)});next++;
            }
            current++;
        }
        bool compact=n<=8;
        size_t total=2;
        for(const auto&[k,v]:items){
            compact&=k.find('\n')==string::npos&&v.find('\n')==string::npos;
            total+=k.size()+v.size()+4;
        }
        compact&=total<=100;
        os<<'{';
        for(size_t i=0;i<items.size();i++){
            if(compact){
                if(i)os<<", ";
                os<<items[i].first<<": "<<items[i].second;
            }else{
                os<<"\n  ";
                if(items[i].first=="…"&&items[i].second.empty())os<<"…";
                else os<<items[i].first<<" => "<<items[i].second;
            }
        }
        if(!compact&&!items.empty())os<<'\n';
        os<<'}';
    }else if constexpr(set_like<U>){
        print_sequence(os,x,depth,'{','}');
    }else if constexpr(is_tuple_like<U>::value&&!range_like<U>){
        print_tuple(os,x,depth,make_index_sequence<tuple_size_v<U>>{});
    }else if constexpr(range_like<U>){
        print_sequence(os,x,depth);
    }else if constexpr(is_arithmetic_v<U>){
        constexpr U infinity=numeric_limits<U>::max()/2-1;
        if(x==infinity)os<<"∞";
        else if constexpr(is_signed_v<U>){if(x==-infinity)os<<"-∞";else os<<x;}
        else os<<x;
    }else if constexpr(streamable<U>){
        os<<x;
    }else{
        os<<"<unprintable "<<type_name<U>()<<'>';
    }
}

struct expression_parse_result{
    vector<string>names;
    bool valid=true;
};

inline expression_parse_result expression_names(string_view source){
    expression_parse_result result;
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
            result.names.emplace_back(source.substr(l,r-l));
            begin=i+1;
        }
    }
    result.valid=!quote&&!round&&!square&&!curly&&!angle;
    return result;
}

inline bool use_color(){
    if(!config.color||getenv("NO_COLOR"))return false;
#if defined(__unix__)||defined(__APPLE__)
    if(!isatty(fileno(stderr)))return false;
#endif
    const char*term=getenv("TERM");
    return term&&string_view(term)!="dumb";
}

inline string paint(string_view code,string_view text,bool color){
    return color?"\033["+string(code)+"m"+string(text)+"\033[0m":string(text);
}

inline void styled(ostream&os,string_view value,bool color){
    if(!color){os<<value;return;}
    size_t begin=0;
    while(begin<value.size()){
        auto unprintable=value.find("<unprintable ",begin);
        auto ellipsis=value.find("…",begin);
        auto next=min(unprintable,ellipsis);
        if(next==string_view::npos){os<<value.substr(begin);break;}
        os<<value.substr(begin,next-begin);
        if(next==unprintable){
            auto end=value.find('>',next);
            if(end==string_view::npos)end=value.size()-1;
            os<<paint("2",value.substr(next,end-next+1),true);
            begin=end+1;
        }else{
            os<<paint("2","…",true);
            begin=next+string_view("…").size();
        }
    }
}

inline string base_name(string_view path){
    auto pos=path.find_last_of("/\\");
    return string(path.substr(pos==string_view::npos?0:pos+1));
}

inline void print_lines(ostream&os,string_view prefix,string_view value,bool color){
    size_t begin=0;
    while(1){
        auto end=value.find('\n',begin);
        os<<prefix;
        styled(os,value.substr(begin,end==string_view::npos?value.size()-begin:end-begin),color);
        os<<'\n';
        if(end==string_view::npos)break;
        begin=end+1;
    }
}

template<class T>
struct is_full_view:false_type{};
template<class T>
struct is_full_view<full_view<T>>:true_type{};

struct rendered_value{
    string text;
    string suffix;
    bool structured=false;
};

template<class T>
rendered_value render(const T&x){
    using U=bare_t<T>;
    rendered_value result{value_string(x)};
    if constexpr(is_matrix<U>::value){
        result.structured=true;
        size_t columns=x.empty()?0:x[0].size();
        bool rectangular=all_of(x.begin(),x.end(),[&](const auto&row){return row.size()==columns;});
        if(rectangular){
            result.suffix=" ["+to_string(x.size())+" × "+to_string(columns)+"]";
            auto newline=result.text.find('\n');
            result.text=newline==string::npos?string():result.text.substr(newline+1);
        }
    }else if constexpr(range_like<U>&&!is_basic_string<U>::value&&!is_string_view<U>::value){
        result.structured=true;
        if constexpr(requires{size(x);})if(size(x)>config.max_sequence_elements){
            result.suffix=" [n="+to_string(size(x))+"]";
        }
    }else if constexpr(is_bitset<U>::value||is_full_view<U>::value){
        result.structured=true;
    }
    result.structured|=result.text.find('\n')!=string::npos;
    return result;
}

template<class... Ts>
void log(const char*file,int line,const char*function,string_view source,const Ts&...xs){
    auto parsed=expression_names(source);
    vector<rendered_value>values{render(xs)...};
    if(!parsed.valid||parsed.names.size()!=values.size()){
        parsed.names.clear();
        for(size_t i=0;i<values.size();i++)parsed.names.push_back("arg"+to_string(i));
    }
    string location=base_name(file)+":"+to_string(line)+" · "+function;
    bool compact=all_of(values.begin(),values.end(),[](const auto&value){return!value.structured;});
    size_t compact_width=visible_width(location)+3;
    for(size_t i=0;i<values.size();i++)compact_width+=visible_width(parsed.names[i])+visible_width(values[i].text)+5;
    compact&=compact_width<=140;
    bool color=use_color();
    if(compact){
        cerr<<paint("2","["+location+"]",color)<<' ';
        for(size_t i=0;i<values.size();i++){
            if(i)cerr<<"   ";
            cerr<<paint("36",parsed.names[i],color)<<" = ";
            styled(cerr,values[i].text,color);
        }
        cerr<<'\n';
        return;
    }
    vector<string>labels(values.size());
    size_t width=0;
    for(size_t i=0;i<values.size();i++){
        labels[i]=shorten(parsed.names[i]+values[i].suffix,48);
        width=max(width,visible_width(labels[i]));
    }
    cerr<<paint("2","┌─ "+string(function)+" · "+base_name(file)+":"+to_string(line),color)<<'\n';
    for(size_t i=0;i<values.size();i++){
        size_t label_width=visible_width(labels[i]);
        size_t padding=label_width<width?width-label_width:0;
        cerr<<"│ "<<paint("36",labels[i],color)<<string(padding,' ')<<" =";
        if(values[i].text.find('\n')==string::npos&&!values[i].text.empty()){
            cerr<<' ';styled(cerr,values[i].text,color);cerr<<'\n';
        }else{
            cerr<<'\n';
            if(!values[i].text.empty())print_lines(cerr,"│   ",values[i].text,color);
        }
    }
    cerr<<paint("2","└─",color)<<'\n';
}

}

template<class T>
struct formatter<full_view<T>>{
    static void print(ostream&os,const full_view<T>&view){
        auto saved=config;
        config.max_sequence_elements=numeric_limits<size_t>::max();
        config.max_tree_nodes=numeric_limits<size_t>::max();
        config.max_graph_vertices=numeric_limits<size_t>::max();
        config.max_graph_edges=numeric_limits<size_t>::max();
        config.max_matrix_rows=numeric_limits<size_t>::max();
        config.max_matrix_columns=numeric_limits<size_t>::max();
        config.max_bit_count=numeric_limits<size_t>::max();
        config.max_string=numeric_limits<size_t>::max();
        config.max_depth=numeric_limits<int>::max();
        internal::print_value(os,view.value,0);
        config=saved;
    }
};

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
