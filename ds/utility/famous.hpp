#pragma once
template<class T,class=void>
struct famous_has_commute{
    static constexpr bool value=false;
};
template<class T>
struct famous_has_commute<T,decltype((void)T::commute,void())>{
    static constexpr bool value=T::commute;
};
template<class Value_type,Value_type inf>
struct Min{
    using value_type=Value_type;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){
        return min(a,b);
    }
    static value_type e(){
        return inf;
    }
    static value_type get(auto a){
        return inf;
    }
};
template<class Value_type,Value_type neg_inf>
struct Max{
    using value_type=Value_type;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){
        return max(a,b);
    }
    static value_type e(){
        return neg_inf;
    }
};
template<class Value_type>
struct Sum{
    using value_type=Value_type;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){
        return a+b;
    }
    static value_type e(){
        return 0;
    }
};
template<class Value_type>
struct Prod{
    using value_type=Value_type;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){
        return a*b;
    }
    static value_type e(){
        return 1;
    }
};
template<class... Infos>
struct merger{
    using value_type=tuple<typename Infos::value_type...>;
    static constexpr bool commute=(famous_has_commute<Infos>::value&&...);
    template<size_t... I>
    static value_type op_impl(value_type a,value_type b,index_sequence<I...>){
        return value_type{Infos::op(get<I>(a),get<I>(b))...};
    }
    static value_type op(value_type a,value_type b){
        return op_impl(a,b,index_sequence_for<Infos...>{});
    }
    static value_type e(){
        return value_type{Infos::e()...};
    }
};
template<class Value_type>
struct affine{
    using value_type=pair<Value_type,Value_type>;
    static value_type op(value_type a,value_type b){
        return {a.first*b.first,a.second*b.first+b.second};
    }
    static value_type e(){
        return {1,0};
    }
};
template<class Value_type>
struct add_min{
    struct info{
        using value_type=Value_type;
        static constexpr bool commute=true;
        static value_type op(value_type a,value_type b){
            return min(a,b);
        }
        static value_type e(){
            return numeric_limits<Value_type>::max();
        }
    };
    struct tag{
        using lazy_type=Value_type;
        static constexpr bool commute=true;
        static lazy_type merge(lazy_type old_tag,lazy_type new_tag){
            return old_tag+new_tag;
        }
        static lazy_type id(){
            return 0;
        }
        static typename info::value_type apply(typename info::value_type node,lazy_type lz){
            return node+lz;
        }
    };
};
template<class Value_type>
struct add_max{
    struct info{
        using value_type=Value_type;
        static constexpr bool commute=true;
        static value_type op(value_type a,value_type b){
            return max(a,b);
        }
        static value_type e(){
            return numeric_limits<Value_type>::lowest();
        }
    };
    struct tag{
        using lazy_type=Value_type;
        static constexpr bool commute=true;
        static lazy_type merge(lazy_type old_tag,lazy_type new_tag){
            return old_tag+new_tag;
        }
        static lazy_type id(){
            return 0;
        }
        static typename info::value_type apply(typename info::value_type node,lazy_type lz){
            return node+lz;
        }
    };
};
template<class Value_type>
struct add_sum{
    struct info{
        using value_type=pair<Value_type,Value_type>;
        static constexpr bool commute=true;
        static value_type op(value_type a,value_type b){
            return {a.first+b.first,a.second+b.second};
        }
        static value_type e(){
            return {0,0};
        }
    };
    struct tag{
        using lazy_type=Value_type;
        static constexpr bool commute=true;
        static lazy_type merge(lazy_type old_tag,lazy_type new_tag){
            return old_tag+new_tag;
        }
        static lazy_type id(){
            return 0;
        }
        static typename info::value_type apply(typename info::value_type node,lazy_type lz){
            return {node.first+node.second*lz,node.second};
        }
    };
};
template<class Value_type>
struct assign_min{
    struct info{
        using value_type=Value_type;
        static constexpr bool commute=true;
        static value_type op(value_type a,value_type b){
            return min(a,b);
        }
        static value_type e(){
            return numeric_limits<Value_type>::max();
        }
    };
    struct tag{
        using lazy_type=pair<bool,Value_type>;
        static lazy_type merge(lazy_type old_tag,lazy_type new_tag){
            if(new_tag.first)return new_tag;
            return old_tag;
        }
        static lazy_type id(){
            return {false,0};
        }
        static typename info::value_type apply(typename info::value_type node,lazy_type lz){
            if(lz.first)return lz.second;
            return node;
        }
    };
};
template<class Value_type>
struct assign_max{
    struct info{
        using value_type=Value_type;
        static constexpr bool commute=true;
        static value_type op(value_type a,value_type b){
            return max(a,b);
        }
        static value_type e(){
            return numeric_limits<Value_type>::lowest();
        }
    };
    struct tag{
        using lazy_type=pair<bool,Value_type>;
        static lazy_type merge(lazy_type old_tag,lazy_type new_tag){
            if(new_tag.first)return new_tag;
            return old_tag;
        }
        static lazy_type id(){
            return {false,0};
        }
        static typename info::value_type apply(typename info::value_type node,lazy_type lz){
            if(lz.first)return lz.second;
            return node;
        }
    };
};
template<class Value_type>
struct assign_sum{
    struct info{
        using value_type=pair<Value_type,Value_type>;
        static constexpr bool commute=true;
        static value_type op(value_type a,value_type b){
            return {a.first+b.first,a.second+b.second};
        }
        static value_type e(){
            return {0,0};
        }
    };
    struct tag{
        using lazy_type=pair<bool,Value_type>;
        static lazy_type merge(lazy_type old_tag,lazy_type new_tag){
            if(new_tag.first)return new_tag;
            return old_tag;
        }
        static lazy_type id(){
            return {false,0};
        }
        static typename info::value_type apply(typename info::value_type node,lazy_type lz){
            if(lz.first)return {node.second*lz.second,node.second};
            return node;
        }
    };
};
template<class Value_type>
struct affine_sum{
    struct info{
        using value_type=pair<Value_type,Value_type>;
        static constexpr bool commute=true;
        static value_type op(value_type a,value_type b){
            return {a.first+b.first,a.second+b.second};
        }
        static value_type e(){
            return {0,0};
        }
    };
    struct tag{
        using lazy_type=pair<Value_type,Value_type>;
        static lazy_type merge(lazy_type old_tag,lazy_type new_tag){
            return {new_tag.first*old_tag.first,new_tag.first*old_tag.second+new_tag.second};
        }
        static lazy_type id(){
            return {1,0};
        }
        static typename info::value_type apply(typename info::value_type node,lazy_type lz){
            return {node.first*lz.first+node.second*lz.second,node.second};
        }
    };
};
template<class info>
struct reversed{
    using value_type=typename info::value_type;
    static constexpr bool commute=famous_has_commute<info>::value;
    static value_type op(value_type a,value_type b){
        return info::op(b,a);
    }
    static value_type e(){
        return info::e();
    }
};


template<class Key,class Val,int K,Val neg_inf>
struct max_k{
    using DATA=max_k<Key,Val,K,neg_inf>;
    struct T{
        Val val;
        Key key;
        T&operator+=(Val v){val+=v;return *this;}
        T&operator-=(Val v){val-=v;return *this;}
        T operator+(Val v)const{return {val+v,key};}
        T operator-(Val v)const{return {val-v,key};}
        friend T operator+(Val v,const T&a){return a+v;}
    };
    array<T,K> d;
    max_k(){d.fill({neg_inf,Key{}});}
    T&operator[](int i){return d[i];}
    const T&operator[](int i)const{return d[i];}
    bool has(Key key,Val val)const{
        rep(i,K)if(d[i].val>neg_inf&&d[i].key==key&&d[i].val==val)return true;
        return false;
    }
    int add_element(Key key,Val val){
        if(val<=d[K-1].val)return 0;
        int pos=0;
        while(pos<K&&d[pos].val>=val){
            if(d[pos].key==key)return 0;
            pos++;
        }
        int end=K-1;
        REP(i,pos,K)if(d[i].key==key){end=i;break;}
        DREP(i,end,pos+1)d[i]=d[i-1];
        d[pos]={val,key};
        return 1;
    }
    DATA&merge_data(const DATA&x){
        rep(i,K)add_element(x.d[i].key,x.d[i].val);
        return *this;
    }
    DATA&operator+=(Val v){
        rep(i,K)if(d[i].val>neg_inf)d[i].val+=v;
        return *this;
    }
    DATA&operator-=(Val v){
        rep(i,K)if(d[i].val>neg_inf)d[i].val-=v;
        return *this;
    }
    DATA operator+(Val v)const{return DATA(*this)+=v;}
    DATA operator-(Val v)const{return DATA(*this)-=v;}
    friend DATA operator+(Val v,const DATA&a){return a+v;}
};
template<class Key,class Val,Val neg_inf>
struct max_k<Key,Val,2,neg_inf>{
    using DATA=max_k<Key,Val,2,neg_inf>;
    struct T{
        Val val;
        Key key;
        T&operator+=(Val v){val+=v;return *this;}
        T&operator-=(Val v){val-=v;return *this;}
        T operator+(Val v)const{return {val+v,key};}
        T operator-(Val v)const{return {val-v,key};}
        friend T operator+(Val v,const T&a){return a+v;}
    };
    array<T,2> d;
    max_k(){d.fill({neg_inf,Key{}});}
    T&operator[](int i){return d[i];}
    const T&operator[](int i)const{return d[i];}
    bool has(Key key,Val val)const{
        return (d[0].val>neg_inf&&d[0].key==key&&d[0].val==val)||(d[1].val>neg_inf&&d[1].key==key&&d[1].val==val);
    }
    int add_element(Key key,Val val){
        if(val<=d[1].val)return 0;
        if(key==d[0].key){
            if(val>d[0].val){
                d[0].val=val;
                return 1;
            }
            return 0;
        }
        if(val>d[0].val){
            d[1]=d[0];
            d[0]={val,key};
        }else{
            d[1]={val,key};
        }
        return 1;
    }
    DATA&merge_data(const DATA&x){
        add_element(x.d[0].key,x.d[0].val);
        add_element(x.d[1].key,x.d[1].val);
        return *this;
    }
    DATA&operator+=(Val v){
        if(d[0].val>neg_inf)d[0].val+=v;
        if(d[1].val>neg_inf)d[1].val+=v;
        return *this;
    }
    DATA&operator-=(Val v){
        if(d[0].val>neg_inf)d[0].val-=v;
        if(d[1].val>neg_inf)d[1].val-=v;
        return *this;
    }
    DATA operator+(Val v)const{return DATA(*this)+=v;}
    DATA operator-(Val v)const{return DATA(*this)-=v;}
    friend DATA operator+(Val v,const DATA&a){return a+v;}
};
template<class Key,class Val,int K,Val neg_inf>
struct maxk_info{
    using value_type=max_k<Key,Val,K,neg_inf>;
    static value_type op(const value_type&a,const value_type&b){
        value_type res(a);
        return res.merge_data(b);
    }
    static value_type e(){return value_type();}
};
template<class Key,class Val,int K,Val inf>
struct min_k{
    using DATA=min_k<Key,Val,K,inf>;
    struct T{
        Val val;
        Key key;
        T&operator+=(Val v){val+=v;return *this;}
        T&operator-=(Val v){val-=v;return *this;}
        T operator+(Val v)const{return {val+v,key};}
        T operator-(Val v)const{return {val-v,key};}
        friend T operator+(Val v,const T&a){return a+v;}
    };
    array<T,K> d;
    min_k(){d.fill({inf,Key{}});}
    T&operator[](int i){return d[i];}
    const T&operator[](int i)const{return d[i];}
    bool has(Key key,Val val)const{
        rep(i,K)if(d[i].val<inf&&d[i].key==key&&d[i].val==val)return true;
        return false;
    }
    int add_element(Key key,Val val){
        if(val>=d[K-1].val)return 0;
        int pos=0;
        while(pos<K&&d[pos].val<=val){
            if(d[pos].key==key)return 0;
            pos++;
        }
        int end=K-1;
        REP(i,pos,K)if(d[i].key==key){end=i;break;}
        DREP(i,end,pos+1)d[i]=d[i-1];
        d[pos]={val,key};
        return 1;
    }
    DATA&merge_data(const DATA&x){
        rep(i,K)add_element(x.d[i].key,x.d[i].val);
        return *this;
    }
    DATA&operator+=(Val v){
        rep(i,K)if(d[i].val<inf)d[i].val+=v;
        return *this;
    }
    DATA&operator-=(Val v){
        rep(i,K)if(d[i].val<inf)d[i].val-=v;
        return *this;
    }
    DATA operator+(Val v)const{return DATA(*this)+=v;}
    DATA operator-(Val v)const{return DATA(*this)-=v;}
    friend DATA operator+(Val v,const DATA&a){return a+v;}
};
template<class Key,class Val,Val inf>
struct min_k<Key,Val,2,inf>{
    using DATA=min_k<Key,Val,2,inf>;
    struct T{
        Val val;
        Key key;
        T&operator+=(Val v){val+=v;return *this;}
        T&operator-=(Val v){val-=v;return *this;}
        T operator+(Val v)const{return {val+v,key};}
        T operator-(Val v)const{return {val-v,key};}
        friend T operator+(Val v,const T&a){return a+v;}
    };
    array<T,2> d;
    min_k(){d.fill({inf,Key{}});}
    T&operator[](int i){return d[i];}
    const T&operator[](int i)const{return d[i];}
    bool has(Key key,Val val)const{
        return (d[0].val<inf&&d[0].key==key&&d[0].val==val)||(d[1].val<inf&&d[1].key==key&&d[1].val==val);
    }
    int add_element(Key key,Val val){
        if(val>=d[1].val)return 0;
        if(key==d[0].key){
            if(val<d[0].val){
                d[0].val=val;
                return 1;
            }
            return 0;
        }
        if(val<d[0].val){
            d[1]=d[0];
            d[0]={val,key};
        }else{
            d[1]={val,key};
        }
        return 1;
    }
    DATA&merge_data(const DATA&x){
        add_element(x.d[0].key,x.d[0].val);
        add_element(x.d[1].key,x.d[1].val);
        return *this;
    }
    DATA&operator+=(Val v){
        if(d[0].val<inf)d[0].val+=v;
        if(d[1].val<inf)d[1].val+=v;
        return *this;
    }
    DATA&operator-=(Val v){
        if(d[0].val<inf)d[0].val-=v;
        if(d[1].val<inf)d[1].val-=v;
        return *this;
    }
    DATA operator+(Val v)const{return DATA(*this)+=v;}
    DATA operator-(Val v)const{return DATA(*this)-=v;}
    friend DATA operator+(Val v,const DATA&a){return a+v;}
};
template<class Key,class Val,int K,Val inf>
struct mink_info{
    using value_type=min_k<Key,Val,K,inf>;
    static value_type op(const value_type&a,const value_type&b){
        value_type res(a);
        return res.merge_data(b);
    }
    static value_type e(){return value_type();}
};
