#pragma once

namespace debug{

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

template<class T>
struct tree_formatter:raw_formatter<T>{};

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

template<class T>
void print_index_values(ostream&os,const vector<T>&values){
    print_index_values(os,values.size(),[&](size_t i)->const T&{return values[i];});
}

inline void print_table_row(ostream&os,const vector<string>&row,const vector<size_t>&width){
    for(size_t i=0;i<row.size();i++){
        if(i)os<<" | ";
        print_right(os,row[i],width[i]);
    }
}

}

template<class Info>
struct formatter<assign_segtree<Info>>{
    static void print(ostream&os,const assign_segtree<Info>&seg){
        auto copy=seg;
        os<<"assign_segtree [n="<<copy.N<<", assignments="<<copy.ptr<<"]\n\n";
        internal::print_index_values(os,copy.N,[&](size_t i){return copy.prod(i,i+1);});
    }
};

template<class X>
struct formatter<dual_segtree<X>>{
    static void print(ostream&os,const dual_segtree<X>&seg){
        auto copy=seg;
        os<<"dual_segtree [n="<<copy.n<<"]\n\n";
        internal::print_index_values(os,copy.n,[&](size_t i){return copy.get(i);});
    }
};

template<class Info,class Size,bool Persistent>
struct formatter<dynamic_segtree<Info,Size,Persistent>>{
    static void print(ostream&os,const dynamic_segtree<Info,Size,Persistent>&seg){
        os<<"dynamic_segtree size="<<seg.N<<" persistent="<<(Persistent?"true":"false")
          <<" (use debug::version(seg, root) to inspect a root)";
    }
};

template<class Info,class Size,bool Persistent>
struct formatter<version_view<dynamic_segtree<Info,Size,Persistent>,typename dynamic_segtree<Info,Size,Persistent>::node*>>{
    using seg_type=dynamic_segtree<Info,Size,Persistent>;
    using node=typename seg_type::node;
    static void print(ostream&os,const version_view<seg_type,node*>&view){
        os<<"dynamic_segtree root size="<<view.value.N<<"\nreachable nodes";
        size_t shown=0;
        bool truncated=false;
        auto dfs=[&](auto&dfs,node*now,Size l,Size r)->void{
            if(!now)return;
            if(shown>=config.max_tree_nodes){truncated=true;return;}
            shown++;
            os<<"\n  ["<<l<<','<<r<<") = ";internal::print_value(os,now->val,0);
            if(r-l>1){Size mid=(l+r)>>1;dfs(dfs,now->l,l,mid);dfs(dfs,now->r,mid,r);}
        };
        dfs(dfs,view.root,0,view.value.N);
        if(truncated)os<<"\n  …";
    }
};

template<class Info,class Tag,class Size>
struct formatter<dynamic_lazy_segtree<Info,Tag,Size>>{
    static void print(ostream&os,const dynamic_lazy_segtree<Info,Tag,Size>&seg){
        os<<"dynamic_lazy_segtree size="<<seg.N<<" allocated_nodes="<<seg.ptr-1<<" root="<<seg.root;
        if(seg.root){
            os<<"\nroot value=";internal::print_value(os,seg.pool[seg.root].val,0);
            os<<" lazy=";internal::print_value(os,seg.pool[seg.root].lazy,0);
        }
    }
};

template<class Info>
struct formatter<segtree_2d<Info>>{
    static void print(ostream&os,const segtree_2d<Info>&seg){
        os<<"segtree_2d "<<seg.H<<" x "<<seg.W<<" (use prod() to inspect a rectangle)";
    }
};

template<class T>
struct formatter<raw_view<T>>{
    static void print(ostream&os,const raw_view<T>&view){internal::raw_formatter<T>::print(os,view.value);}
};
template<class T>
struct formatter<tree_view<T>>{
    static void print(ostream&os,const tree_view<T>&view){internal::tree_formatter<T>::print(os,view.value);}
};

template<class T>
struct formatter<::edge<T>>{
    static void print(ostream&os,const ::edge<T>&e){
        os<<e.from<<" -> "<<e.to<<" (id="<<e.id;
        if constexpr(!is_same_v<T,unweighted>){os<<", cost=";debug::print_value(os,e.cost);}
        os<<')';
    }
};

template<class Info>
struct formatter<segtree<Info>>{
    static void print(ostream&os,const segtree<Info>&seg){
        os<<"segtree [n="<<seg.N<<"]\n\n";
        internal::print_index_values(os,seg.N,[&](size_t i)->const auto&{return seg.node[seg.n+i];});
    }
};

namespace internal{
template<class Info>
struct raw_formatter<segtree<Info>>{
    static void print(ostream&os,const segtree<Info>&seg){
        os<<"segtree raw n="<<seg.N<<" size="<<seg.n<<"\nnode = ";
        print_value(os,seg.node,0);
    }
};
template<class Info>
struct tree_formatter<segtree<Info>>{
    static void print(ostream&os,const segtree<Info>&seg){
        os<<"segtree [n="<<seg.N<<"]\n";
        size_t shown=0;
        bool truncated=false;
        auto dfs=[&](auto&dfs,int k,int l,int r,string prefix,bool last,bool root)->void{
            if(l>=seg.N)return;
            if(shown>=config.max_tree_nodes){truncated=true;return;}
            shown++;
            os<<'\n'<<prefix;
            if(!root)os<<(last?"└─ ":"├─ ");
            os<<'['<<l<<','<<min(r,seg.N)<<") = ";
            print_value(os,seg.node[k],0);
            if(k<seg.n&&min(r,seg.N)-l>1){
                int m=(l+r)/2;
                string child_prefix=prefix+(root?"":last?"   ":"│  ");
                bool has_right=m<seg.N;
                dfs(dfs,k*2,l,m,child_prefix,!has_right,false);
                if(has_right)dfs(dfs,k*2+1,m,r,child_prefix,true,false);
            }
        };
        if(seg.N)dfs(dfs,1,0,seg.n,"",true,true);
        if(truncated)os<<"\n…";
    }
};
}

template<class Info,class Tag,bool Beats>
struct formatter<lazy_segtree<Info,Tag,Beats>>{
    static void print(ostream&os,const lazy_segtree<Info,Tag,Beats>&seg){
        auto copy=seg;
        os<<"lazy_segtree [n="<<seg.N<<"]\n\n";
        internal::print_index_values(os,copy.N,[&](size_t i){return copy.prod(i,i+1);});
    }
};

namespace internal{
template<class Info,class Tag,bool Beats>
struct raw_formatter<lazy_segtree<Info,Tag,Beats>>{
    static void print(ostream&os,const lazy_segtree<Info,Tag,Beats>&seg){
        os<<"lazy_segtree raw n="<<seg.N<<" size="<<seg.n<<"\nnode = ";
        print_value(os,seg.node,0);
        os<<"\nlazy = ";print_value(os,seg.lazy,0);
    }
};
template<class Info,class Tag,bool Beats>
struct tree_formatter<lazy_segtree<Info,Tag,Beats>>{
    static void print(ostream&os,const lazy_segtree<Info,Tag,Beats>&seg){
        os<<"lazy_segtree [n="<<seg.N<<"]\n";
        size_t shown=0;
        bool truncated=false;
        using lazy_type=typename lazy_segtree<Info,Tag,Beats>::lazy_type;
        auto dfs=[&](auto&dfs,int k,int l,int r,lazy_type inherited,string prefix,bool last,bool root)->void{
            if(l>=seg.N)return;
            if(shown>=config.max_tree_nodes){truncated=true;return;}
            shown++;
            os<<'\n'<<prefix;
            if(!root)os<<(last?"└─ ":"├─ ");
            os<<'['<<l<<','<<min(r,seg.N)<<") value=";
            print_value(os,Tag::apply(seg.node[k],inherited),0);
            if(k<seg.n){os<<"  lazy=";print_value(os,seg.lazy[k],0);}
            if(k<seg.n&&min(r,seg.N)-l>1){
                int m=(l+r)/2;
                string child_prefix=prefix+(root?"":last?"   ":"│  ");
                bool has_right=m<seg.N;
                auto child_lazy=Tag::merge(seg.lazy[k],inherited);
                dfs(dfs,k*2,l,m,child_lazy,child_prefix,!has_right,false);
                if(has_right)dfs(dfs,k*2+1,m,r,child_lazy,child_prefix,true,false);
            }
        };
        if(seg.N)dfs(dfs,1,0,seg.n,Tag::id(),"",true,true);
        if(truncated)os<<"\n…";
    }
};
}

template<class T>
struct formatter<binary_indexed_tree<T>>{
    static void print(ostream&os,const binary_indexed_tree<T>&bit){
        vector<T>values;
        for(int i=0;i<bit.n;i++)values.push_back(bit.sum(i,i+1));
        os<<"fenwick_tree n="<<bit.n<<"\nvalues = ";
        internal::print_value(os,values,0);
        os<<"\nbit    = ";internal::print_value(os,bit.data,0);
    }
};

template<>
struct formatter<bit_vector>{
    static void print(ostream&os,const bit_vector&bv){
        os<<"bit_vector [n="<<bv.n<<"]\n\n";
        internal::print_bits(os,bv.n,[&](size_t i){return bv.rank1(i,i+1);});
    }
};

template<class T,int D>
struct formatter<wm_base<T,D>>{
    static void print(ostream&os,const wm_base<T,D>&wm){
        os<<"wavelet_matrix n="<<wm.n<<" levels="<<D<<"\nvalues = ";
        internal::print_value(os,wm.gi,0);
        for(int level=D-1;level>=0;level--){
            os<<"\nlevel "<<level<<" mid="<<wm.mid[level]<<" : ";
            size_t n=min<size_t>(wm.n,config.max_sequence_elements);
            for(size_t i=0;i<n;i++)os<<(wm.bv[level].rank1(i,i+1)?'1':'0');
            if(n<(size_t)wm.n)os<<"…";
        }
    }
};

template<class T,auto Op,int Extra>
struct formatter<base_disjoint_set_union<T,Op,Extra>>{
    static void print(ostream&os,const base_disjoint_set_union<T,Op,Extra>&uf){
        auto copy=uf;
        map<int,vector<int>>groups;
        for(int i=0;i<(int)copy.par.size();i++)groups[copy.root(i)].push_back(i);
        os<<"dsu [n="<<copy.par.size()<<", components="<<groups.size()<<"]\n";
        size_t shown=0;
        for(auto&[root,vertices]:groups){
            if(shown==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<shown++<<' ';
            internal::print_sequence(os,vertices,0,'{','}');
            if constexpr(Extra){os<<" data=";internal::print_value(os,copy.data[root],0);}
        }
    }
};

template<>
struct formatter<undoable_union_find>{
    static void print(ostream&os,const undoable_union_find&uf){
        auto copy=uf;
        map<int,vector<int>>groups;
        for(int i=0;i<(int)copy.par.size();i++)groups[copy.root(i)].push_back(i);
        os<<"undoable_dsu [n="<<copy.par.size()<<", components="<<groups.size()
          <<", history="<<copy.history.size()<<"]\n";
        size_t id=0;
        for(auto&[_,vertices]:groups){
            if(id==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<id++<<' ';internal::print_sequence(os,vertices,0,'{','}');
        }
    }
};

template<class X>
struct formatter<potentialized_union_find<X>>{
    static void print(ostream&os,const potentialized_union_find<X>&uf){
        auto copy=uf;
        map<int,vector<pair<int,typename X::value_type>>>groups;
        for(int i=0;i<(int)copy.par.size();i++)groups[copy.root(i)].push_back({i,copy.w[i]});
        os<<"potentialized_dsu [n="<<copy.par.size()<<", components="<<groups.size()<<"]";
        size_t id=0;
        for(auto&[root,vertices]:groups){
            if(id==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<id++<<" root="<<root<<' ';internal::print_value(os,vertices,0);
        }
    }
};

template<bool Directed,class T>
struct formatter<static_graph<Directed,T>>{
    static void print(ostream&os,const static_graph<Directed,T>&g){
        os<<(Directed?"directed":"undirected")<<" graph [n="<<g.size()<<", m="<<g.edge_size()<<"]\n";
        auto vertices=internal::shown_indices(g.size(),config.max_graph_vertices);
        size_t shown_edges=0;
        for(auto u:vertices){
            if(u==numeric_limits<size_t>::max()){os<<"\n…";continue;}
            os<<'\n'<<u<<(Directed?" ->":" --");
            bool first=true;
            for(const auto&e:g[u]){
                if(shown_edges>=config.max_graph_edges){os<<(first?" ":", ")<<"…";break;}
                os<<(first?" ":", ")<<e.to;first=false;shown_edges++;
                if constexpr(!is_same_v<T,unweighted>){os<<'(';internal::print_value(os,e.cost,0);os<<')';}
            }
        }
    }
};

template<class T>
struct formatter<::tree<T>>{
    static void print(ostream&os,const ::tree<T>&tr){
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

template<class G>
struct formatter<lowlink<G>>{
    static void print(ostream&os,const lowlink<G>&ll){
        os<<"lowlink n="<<ll.n<<"\n  v      ord low parent_edge";
        size_t n=min<size_t>(ll.n,config.max_graph_vertices);
        for(size_t v=0;v<n;v++)os<<"\n  "<<setw(6)<<v<<setw(5)<<ll.ord[v]<<setw(4)<<ll.low[v]<<setw(12)<<ll.parid[v];
        vector<int>bridges;
        auto copy=ll;
        for(int id=0;id<copy.g.edge_size();id++)if(copy.isbridge(id))bridges.push_back(id);
        os<<"\nbridges = ";internal::print_value(os,bridges,0);
    }
};

template<class G>
struct formatter<bcc_view<lowlink<G>>>{
    static void print(ostream&os,const bcc_view<lowlink<G>>&view){
        auto copy=view.value;
        auto edge_components=copy.twoedge_component();
        auto vertex_components=copy.twovertex_component();
        os<<"lowlink components\nvertex -> 2-edge-component = ";
        internal::print_value(os,edge_components.toid,0);
        os<<"\nblocks (edge ids) = ";internal::print_value(os,vertex_components.egs,0);
        os<<"\nblock-cut tree = ";internal::print_value(os,vertex_components.comp,0);
    }
};

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

template<class Cap,class Cost>
struct formatter<min_cost_flow<Cap,Cost>>{
    static void print(ostream&os,const min_cost_flow<Cap,Cost>&network){
        os<<"min_cost_flow [n="<<network.n<<", m="<<network.edges.size()<<"]\n\n";
        vector<vector<string>>rows{{"id","from -> to","flow / cap","cost"}};
        auto indices=internal::shown_indices(network.edges.size(),config.max_graph_edges);
        for(auto i:indices){
            if(i==numeric_limits<size_t>::max()){rows.push_back({"…","…","…","…"});continue;}
            const auto&e=network.edges[i];
            string flow_value=i<network.flow.size()?internal::value_string(network.flow[i]):"not-run";
            rows.push_back({to_string(e.id),to_string(e.from)+" -> "+to_string(e.to),
                            flow_value+" / "+internal::value_string(e.cap),internal::value_string(e.cost)});
        }
        vector<size_t>width(4);
        for(const auto&row:rows)for(size_t i=0;i<row.size();i++)width[i]=max(width[i],internal::visible_width(row[i]));
        internal::print_table_row(os,rows[0],width);
        os<<'\n'<<string(width[0],'-')<<"-+-"<<string(width[1],'-')<<"-+-"
          <<string(width[2],'-')<<"-+-"<<string(width[3],'-');
        for(size_t i=1;i<rows.size();i++){os<<'\n';internal::print_table_row(os,rows[i],width);}
    }
};

template<class T,int B>
struct formatter<persistent_array<T,B>>{
    static void print(ostream&os,const persistent_array<T,B>&array){
        os<<"persistent_array n="<<array.n_<<" branching="<<B<<" span="<<array.b_
          <<" (use debug::version(array, root) to inspect a version)";
    }
};

template<class T,int B>
struct formatter<version_view<persistent_array<T,B>,typename persistent_array<T,B>::Node*>>{
    using array_type=persistent_array<T,B>;
    using view_type=version_view<array_type,typename array_type::Node*>;
    static void print(ostream&os,const view_type&view){
        os<<"persistent_array [n="<<view.value.n_<<"]\n\n";
        internal::print_index_values(os,view.value.n_,[&](size_t i){return view.value.get(i,view.root);});
    }
};

template<class Info,class Tag>
struct formatter<persistent_lazy_segtree<Info,Tag>>{
    static void print(ostream&os,const persistent_lazy_segtree<Info,Tag>&seg){
        os<<"persistent_lazy_segtree n="<<seg.N<<" allocated_nodes="<<seg.ptr-1
          <<" (use debug::version(seg, root) to inspect a version)";
    }
};

template<class Info,class Tag>
struct formatter<version_view<persistent_lazy_segtree<Info,Tag>,int>>{
    using seg_type=persistent_lazy_segtree<Info,Tag>;
    static void print(ostream&os,const version_view<seg_type,int>&view){
        os<<"persistent_lazy_segtree [n="<<view.value.N<<", root="<<view.root<<"]\n\n";
        internal::print_index_values(os,view.value.N,[&](size_t i){return view.value.prod(i,i+1,view.root);});
    }
};

template<int B>
struct formatter<persistent_union_find<B>>{
    static void print(ostream&os,const persistent_union_find<B>&uf){
        os<<"persistent_dsu n="<<uf.par.n_<<" branching="<<B
          <<" (use debug::version(uf, root) to inspect a version)";
    }
};

template<int B>
struct formatter<version_view<persistent_union_find<B>,typename persistent_union_find<B>::node>>{
    using uf_type=persistent_union_find<B>;
    static void print(ostream&os,const version_view<uf_type,typename uf_type::node>&view){
        auto&uf=view.value;
        map<int,vector<int>>groups;
        for(int i=0;i<uf.par.n_;i++)groups[uf.root(i,view.root)].push_back(i);
        os<<"persistent_dsu [n="<<uf.par.n_<<", components="<<groups.size()<<"]\n";
        size_t id=0;
        for(auto&[_,vertices]:groups){
            if(id==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<id++<<' ';internal::print_sequence(os,vertices,0,'{','}');
        }
    }
};

}
