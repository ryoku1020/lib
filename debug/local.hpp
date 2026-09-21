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

}

template<class Info>
struct formatter<assign_segtree<Info>>{
    static void print(ostream&os,const assign_segtree<Info>&seg){
        auto copy=seg;
        os<<"assign_segtree size="<<copy.N<<" assignments="<<copy.ptr<<"\nvalues = [";
        size_t n=min<size_t>(copy.N,config.max_elements);
        for(size_t i=0;i<n;i++){
            if(i)os<<", ";
            internal::print_value(os,copy.prod(i,i+1),0);
        }
        if(n<(size_t)copy.N)os<<", …";
        os<<']';
    }
};

template<class X>
struct formatter<dual_segtree<X>>{
    static void print(ostream&os,const dual_segtree<X>&seg){
        auto copy=seg;
        os<<"dual_segtree size="<<copy.n<<"\nvalues = [";
        size_t n=min<size_t>(copy.n,config.max_elements);
        for(size_t i=0;i<n;i++){
            if(i)os<<", ";
            internal::print_value(os,copy.get(i),0);
        }
        if(n<(size_t)copy.n)os<<", …";
        os<<']';
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
        auto dfs=[&](auto&dfs,node*now,Size l,Size r)->void{
            if(!now||shown++==config.max_elements)return;
            os<<"\n  ["<<l<<','<<r<<") = ";internal::print_value(os,now->val,0);
            if(r-l>1){Size mid=(l+r)>>1;dfs(dfs,now->l,l,mid);dfs(dfs,now->r,mid,r);}
        };
        dfs(dfs,view.root,0,view.value.N);
        if(shown>config.max_elements)os<<"\n  …";
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
        os<<"segtree n="<<seg.N<<" size="<<seg.n<<"\nleaves ";
        vector<typename segtree<Info>::value_type>leaves;
        for(int i=0;i<seg.N;i++)leaves.push_back(seg.node[seg.n+i]);
        internal::print_value(os,leaves,0);
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
        os<<"segtree tree n="<<seg.N<<" size="<<seg.n;
        size_t shown=0;
        auto dfs=[&](auto&dfs,int k,int l,int r,string prefix,bool last)->void{
            if(shown++>=config.max_elements)return;
            os<<'\n'<<prefix<<(last?"└─ ":"├─ ")<<"node "<<k<<" ["<<l<<','<<r<<") = ";
            print_value(os,seg.node[k],0);
            if(k<seg.n){
                int m=(l+r)/2;
                dfs(dfs,k*2,l,m,prefix+(last?"   ":"│  "),false);
                dfs(dfs,k*2+1,m,r,prefix+(last?"   ":"│  "),true);
            }
        };
        if(seg.n)dfs(dfs,1,0,seg.n,"",true);
        if(shown>config.max_elements)os<<"\n…";
    }
};
}

template<class Info,class Tag,bool Beats>
struct formatter<lazy_segtree<Info,Tag,Beats>>{
    static void print(ostream&os,const lazy_segtree<Info,Tag,Beats>&seg){
        os<<"lazy_segtree n="<<seg.N<<" size="<<seg.n<<"\nleaves ";
        auto copy=seg;
        vector<typename lazy_segtree<Info,Tag,Beats>::value_type>leaves;
        for(int i=0;i<copy.N;i++)leaves.push_back(copy.prod(i,i+1));
        internal::print_value(os,leaves,0);
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
        os<<"lazy_segtree tree n="<<seg.N<<" size="<<seg.n;
        size_t n=min<size_t>(seg.n,config.max_elements);
        for(size_t k=1;k<n;k++){
            os<<"\n  node "<<k<<" value=";print_value(os,seg.node[k],0);
            os<<" lazy=";print_value(os,seg.lazy[k],0);
        }
        if(n<(size_t)seg.n)os<<"\n  …";
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
        os<<"bit_vector n="<<bv.n<<"\nindex: ";
        size_t n=min<size_t>(bv.n,config.max_elements);
        for(size_t i=0;i<n;i++)os<<i%10;
        if(n<(size_t)bv.n)os<<"…";
        os<<"\nbit  : ";
        for(size_t i=0;i<n;i++)os<<(bv.rank1(i,i+1)?'1':'0');
        if(n<(size_t)bv.n)os<<"…";
    }
};

template<class T,int D>
struct formatter<wm_base<T,D>>{
    static void print(ostream&os,const wm_base<T,D>&wm){
        os<<"wavelet_matrix n="<<wm.n<<" levels="<<D<<"\nvalues = ";
        internal::print_value(os,wm.gi,0);
        for(int level=D-1;level>=0;level--){
            os<<"\nlevel "<<level<<" mid="<<wm.mid[level]<<" : ";
            size_t n=min<size_t>(wm.n,config.max_elements);
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
        os<<"dsu n="<<copy.par.size()<<" components="<<groups.size();
        size_t shown=0;
        for(auto&[root,vertices]:groups){
            if(shown++==config.max_elements){os<<"\n…";break;}
            os<<"\n  ";internal::print_value(os,vertices,0);
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
        os<<"undoable_dsu n="<<copy.par.size()<<" history="<<copy.history.size();
        for(auto&[_,vertices]:groups){os<<"\n  ";internal::print_value(os,vertices,0);}
    }
};

template<class X>
struct formatter<potentialized_union_find<X>>{
    static void print(ostream&os,const potentialized_union_find<X>&uf){
        auto copy=uf;
        map<int,vector<pair<int,typename X::value_type>>>groups;
        for(int i=0;i<(int)copy.par.size();i++)groups[copy.root(i)].push_back({i,copy.w[i]});
        os<<"potentialized_dsu n="<<copy.par.size();
        for(auto&[root,vertices]:groups){
            os<<"\n  root "<<root<<" : ";internal::print_value(os,vertices,0);
        }
    }
};

template<bool Directed,class T>
struct formatter<static_graph<Directed,T>>{
    static void print(ostream&os,const static_graph<Directed,T>&g){
        os<<(Directed?"directed":"undirected")<<" graph n="<<g.size()<<" m="<<g.edge_size();
        size_t vertices=min<size_t>(g.size(),config.max_elements);
        for(size_t u=0;u<vertices;u++){
            os<<"\n  "<<u<<" :";
            size_t shown=0;
            for(const auto&e:g[u]){
                if(shown++==config.max_elements){os<<" …";break;}
                os<<' '<<e.to;
                if constexpr(!is_same_v<T,unweighted>){os<<'(';internal::print_value(os,e.cost,0);os<<')';}
            }
        }
        if(vertices<(size_t)g.size())os<<"\n  …";
    }
};

template<class T>
struct formatter<::tree<T>>{
    static void print(ostream&os,const ::tree<T>&tr){
        auto copy=tr;
        copy.build();
        os<<"tree / HLD n="<<copy.n;
        os<<"\n  v      parent depth head in out size component";
        size_t n=min<size_t>(copy.n,config.max_elements);
        for(size_t v=0;v<n;v++){
            os<<"\n  "<<setw(6)<<v<<setw(7)<<copy.par[v]<<setw(6)<<copy.depth[v]
              <<setw(5)<<copy.head[v]<<setw(3)<<copy.in[v]<<setw(4)<<copy.out[v]
              <<setw(5)<<copy.size_[v]<<setw(10)<<copy.cp[v];
        }
        if(n<(size_t)copy.n)os<<"\n  …";
    }
};

template<class G>
struct formatter<lowlink<G>>{
    static void print(ostream&os,const lowlink<G>&ll){
        os<<"lowlink n="<<ll.n<<"\n  v      ord low parent_edge";
        size_t n=min<size_t>(ll.n,config.max_elements);
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
        os<<"flow n="<<network.n<<" m="<<network.edges.size();
        size_t n=min(network.edges.size(),config.max_elements);
        for(size_t i=0;i<n;i++){
            const auto&e=network.edges[i];
            os<<"\n  #"<<e.id<<' '<<e.from<<" -> "<<e.to<<"  flow=";
            if(i<network._flow.size())internal::print_value(os,network._flow[i],0);else os<<"not-run";
            os<<" / cap=";internal::print_value(os,e.cost,0);
        }
        if(n<network.edges.size())os<<"\n  …";
    }
};

template<class Cap,class Cost>
struct formatter<min_cost_flow<Cap,Cost>>{
    static void print(ostream&os,const min_cost_flow<Cap,Cost>&network){
        os<<"min_cost_flow n="<<network.n<<" m="<<network.edges.size();
        size_t n=min(network.edges.size(),config.max_elements);
        for(size_t i=0;i<n;i++){
            const auto&e=network.edges[i];
            os<<"\n  #"<<e.id<<' '<<e.from<<" -> "<<e.to<<"  flow=";
            if(i<network.flow.size())internal::print_value(os,network.flow[i],0);else os<<"not-run";
            os<<" / cap=";internal::print_value(os,e.cap,0);
            os<<" cost=";internal::print_value(os,e.cost,0);
        }
        if(n<network.edges.size())os<<"\n  …";
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
        os<<"persistent_array version n="<<view.value.n_<<"\nvalues = [";
        size_t n=min<size_t>(view.value.n_,config.max_elements);
        for(size_t i=0;i<n;i++){
            if(i)os<<", ";
            internal::print_value(os,view.value.get(i,view.root),0);
        }
        if(n<(size_t)view.value.n_)os<<", …";
        os<<']';
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
        os<<"persistent_lazy_segtree root="<<view.root<<" n="<<view.value.N<<"\nleaves = [";
        size_t n=min<size_t>(view.value.N,config.max_elements);
        for(size_t i=0;i<n;i++){
            if(i)os<<", ";
            internal::print_value(os,view.value.prod(i,i+1,view.root),0);
        }
        if(n<(size_t)view.value.N)os<<", …";
        os<<']';
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
        os<<"persistent_dsu n="<<uf.par.n_<<" components="<<groups.size();
        for(auto&[_,vertices]:groups){os<<"\n  ";internal::print_value(os,vertices,0);}
    }
};

}
