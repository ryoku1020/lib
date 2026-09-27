template<class T,class Graph>
pair<pair<vc<int>,vc<typename Graph::edge>>,T>shortest_path(const Graph&g,int s,int t){
    auto md=dijkstra<T>(g,s);
    if(md[t]==inf<T>)return {{{},{}},inf<T>};
    return {restore_path(g,md,s,t),md[t]};
}