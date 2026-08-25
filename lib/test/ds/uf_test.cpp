#include "../../../ds/union_find/uf.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

// Naive implementation for comparison
struct naive_dsu {
    std::vector<int> group;
    int n;
    naive_dsu(int n) : n(n) {
        group.resize(n);
        std::iota(group.begin(), group.end(), 0);
    }
    int leader(int x) {
        return group[x];
    }
    bool same(int x, int y) {
        return group[x] == group[y];
    }
    bool merge(int x, int y) {
        int gx = group[x];
        int gy = group[y];
        if (gx == gy) return false;
        for (int i = 0; i < n; ++i) {
            if (group[i] == gy) group[i] = gx;
        }
        return true;
    }
    int size(int x) {
        int gx = group[x];
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (group[i] == gx) cnt++;
        }
        return cnt;
    }
};

template<class T, auto op>
struct naive_extra_dsu {
    std::vector<int> group;
    std::vector<T> data;
    int n;
    naive_extra_dsu(int n, T e) : n(n), data(n, e) {
        group.resize(n);
        std::iota(group.begin(), group.end(), 0);
    }
    int leader(int x) {
        return group[x];
    }
    bool same(int x, int y) {
        return group[x] == group[y];
    }
    bool merge(int x, int y) {
        int gx = group[x];
        int gy = group[y];
        if (gx == gy) return false;
        T combined = op(data[gy], data[gx]);
        for (int i = 0; i < n; ++i) {
            if (group[i] == gy) group[i] = gx;
        }
        for (int i = 0; i < n; ++i) {
            if (group[i] == gx) data[i] = combined;
        }
        return true;
    }
    int size(int x) {
        int gx = group[x];
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (group[i] == gx) cnt++;
        }
        return cnt;
    }
    T& operator[](int i) {
        return data[i];
    }
};

int add_op(int a, int b) { return a + b; }

void random_test(int n, int q) {
    disjoint_set_union uf(n);
    naive_dsu naive(n);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist_n(0, n - 1);
    std::uniform_int_distribution<int> dist_op(0, 3);

    for (int i = 0; i < q; ++i) {
        int op = dist_op(rng);
        int x = dist_n(rng);
        int y = dist_n(rng);

        if (op == 0) { // merge
            assert(uf.merge(x, y) == naive.merge(x, y));
        } else if (op == 1) { // same
            assert(uf.same(x, y) == naive.same(x, y));
        } else if (op == 2) { // size
            assert(uf.size(x) == naive.size(x));
        } else { // leader consistency
            assert(uf.same(x, y) == (uf.leader(x) == uf.leader(y)));
        }
    }
}

void random_test_extra(int n, int q) {
    extra_disjoint_set_union<int, add_op> uf(n, 1);
    naive_extra_dsu<int, add_op> naive(n, 1);

    std::mt19937 rng(43);
    std::uniform_int_distribution<int> dist_n(0, n - 1);
    std::uniform_int_distribution<int> dist_op(0, 4);

    for (int i = 0; i < q; ++i) {
        int op = dist_op(rng);
        int x = dist_n(rng);
        int y = dist_n(rng);

        if (op == 0) { // merge
            assert(uf.merge(x, y) == naive.merge(x, y));
        } else if (op == 1) { // same
            assert(uf.same(x, y) == naive.same(x, y));
        } else if (op == 2) { // size
            assert(uf.size(x) == naive.size(x));
        } else if (op == 3) { // data access
            assert(uf[x] == naive[x]);
        } else { // leader consistency and data
            assert(uf.same(x, y) == (uf.leader(x) == uf.leader(y)));
            if (uf.same(x, y)) assert(uf[x] == uf[y]);
        }
    }
}

int main() {
    // n * q approx 2e8 for strong stress tests
    const int N1 = 2000;
    const int Q1 = 50000; // 2000 * 50000 = 1e8

    std::cout << "Running random tests for dsu (N=" << N1 << ", Q=" << Q1 << ")..." << std::endl;
    random_test(N1, Q1);
    std::cout << "dsu random tests passed!" << std::endl;

    const int N2 = 1000;
    const int Q2 = 100000; // 1000 * 100000 = 1e8
    std::cout << "Running random tests for extra_disjoint_set_union (N=" << N2 << ", Q=" << Q2 << ")..." << std::endl;
    random_test_extra(N2, Q2);
    std::cout << "extra_disjoint_set_union random tests passed!" << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
