#pragma once
#include"../template.hpp"
struct UndoUnionFind {
    std::vector<int>par;
    std::stack<std::pair<int, int>>history;
    UndoUnionFind(int n) {
        par.resize(n, -1);
    }
    int root(int x) {
        if (par[x] < 0)return x;
        else return root(par[x]);
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    bool merge(int x, int y) {
        x = root(x), y = root(y);
        history.push({ x,par[x] });
        history.push({ y,par[y] });
        if (x == y) return false;
        if (par[x] > par[y])std::swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    void save() {
        while (history.size())history.pop();
    }
    void undo() {
        for(int jj=0;jj<2;jj++){
            par[history.top().first] = history.top().second;
            history.pop();
        }
        return;
    }
    void rollback() {
        while (history.size())undo();
    }
    int size(int x){
        return -par[root(x)];
    }
};