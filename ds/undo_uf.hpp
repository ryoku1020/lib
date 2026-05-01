#pragma once
#include "../template.hpp"
struct UndoableUnionFind {
    std::vector<int>par;
    std::stack<std::pair<int, int>>history;
    UndoableUnionFind(int n) {
        assert(n>=0);
        par.resize(n, -1);
    }
    int root(int x) {
        assert(0<=x&&x<(int)par.size());
        if (par[x] < 0)return x;
        else return root(par[x]);
    }
    bool same(int x, int y) {
        assert(0<=x&&x<(int)par.size());
        assert(0<=y&&y<(int)par.size());
        return root(x) == root(y);
    }
    bool merge(int x, int y) {
        assert(0<=x&&x<(int)par.size());
        assert(0<=y&&y<(int)par.size());
        x = root(x), y = root(y);
        history.push({ x,par[x] });
        history.push({ y,par[y] });
        if (x == y)return false;
        else if (par[x] > par[y])std::swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    void save() {
        while (history.size())history.pop();
    }
    void undo() {
        assert(history.size()>=2);
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
        assert(0<=x&&x<(int)par.size());
        return -par[root(x)];
    }
};
