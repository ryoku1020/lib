
#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ryoku {




// Enumerate all a in [0,m]^n, in lexicographic order.
inline vvc<int> enumerate_vec(int n, int m) {
    vvc<int> res;
    if (n < 0 || m < 0) return res;
    vc<int> a(n);
    auto dfs = [&](auto&& self, int i) -> void {
        if (i == n) {
            res.push_back(a);
            return;
        }
        for (int x = 0; x <= m; ++x) {
            a[i] = x;
            self(self, i + 1);
        }
    };
    dfs(dfs, 0);
    return res;
}

// Enumerate 0 <= a[0] <= ... <= a[n-1] <= m, in lexicographic order.
inline vvc<int> enumerate_nondecreasing(int n, int m) {
    vvc<int> res;
    if (n < 0 || m < 0) return res;
    vc<int> a(n);
    auto dfs = [&](auto&& self, int i, int lo) -> void {
        if (i == n) {
            res.push_back(a);
            return;
        }
        for (int x = lo; x <= m; ++x) {
            a[i] = x;
            self(self, i + 1, x);
        }
    };
    dfs(dfs, 0, 0);
    return res;
}

// All enumeration functions return lexicographically sorted vector<vector<int>>.
// Bounds are inclusive.

// a[i] in [lo[i],hi[i]]. Negative values are allowed.
inline vvc<int> enumerate_vec(const vc<int>& lo, const vc<int>& hi) {
    vvc<int> res;
    if (lo.size() != hi.size()) throw std::invalid_argument("enumerate_vec: size mismatch");
    int n = (int)lo.size();
    for (int i = 0; i < n; ++i) if (lo[i] > hi[i]) return res;
    vc<int> a(n);
    auto dfs = [&](auto&& self, int i) -> void {
        if (i == n) {
            res.push_back(a);
            return;
        }
        for (int x = lo[i]; ; ++x) {
            a[i] = x;
            self(self, i + 1);
            if (x == hi[i]) break;
        }
    };
    dfs(dfs, 0);
    return res;
}

// a[i] in [l,r].
inline vvc<int> enumerate_vec(int n, int l, int r) {
    if (n < 0 || l > r) return {};
    return enumerate_vec(vc<int>(n, l), vc<int>(n, r));
}

// 0 <= a[0] < ... < a[n-1] <= m.
inline vvc<int> enumerate_increasing(int n, int m) {
    vvc<int> res;
    if (n < 0 || m < 0) return res;
    vc<int> a(n);
    auto dfs = [&](auto&& self, int i, int lo) -> void {
        if (i == n) {
            res.push_back(a);
            return;
        }
        for (int x = lo; x <= m; ++x) {
            a[i] = x;
            self(self, i + 1, x + 1);
        }
    };
    dfs(dfs, 0, 0);
    return res;
}

namespace detail {
// Enumerate 0 <= a[i] <= m with sum == s or sum <= s.
// sorted=true additionally requires a[0] <= ... <= a[n-1].
inline vvc<int> enumerate_sum_impl(int n, int m, int s, bool sorted, bool exact) {
    vvc<int> res;
    if (n < 0 || m < 0 || s < 0) return res;
    vc<int> a(n);
    auto dfs = [&](auto&& self, int i, int lo, int rem) -> void {
        if (i == n) {
            if (!exact || rem == 0) res.push_back(a);
            return;
        }
        if (exact && (1LL * (n - i) * lo > rem ||
                      1LL * (n - i) * m < rem)) return;
        for (int x = lo; x <= m && x <= rem; ++x) {
            a[i] = x;
            self(self, i + 1, sorted ? x : 0, rem - x);
        }
    };
    dfs(dfs, 0, 0, s);
    return res;
}
} // namespace detail

// 0 <= a[i] <= m, sum a[i] == s.
inline vvc<int> enumerate_sum(int n, int m, int s) {
    return detail::enumerate_sum_impl(n, m, s, false, true);
}

// 0 <= a[i] <= m, sum a[i] <= s.
inline vvc<int> enumerate_sum_le(int n, int m, int s) {
    return detail::enumerate_sum_impl(n, m, s, false, false);
}

// Nondecreasing and sum a[i] == s.
inline vvc<int> enumerate_partition(int n, int m, int s) {
    return detail::enumerate_sum_impl(n, m, s, true, true);
}

// Nondecreasing and sum a[i] <= s.
inline vvc<int> enumerate_partition_le(int n, int m, int s) {
    return detail::enumerate_sum_impl(n, m, s, true, false);
}

// Exactly k entries are positive, with 0 <= a[i] <= m.
inline vvc<int> enumerate_support(int n, int m, int k) {
    vvc<int> res;
    if (n < 0 || m < 0 || k < 0 || k > n) return res;
    vc<int> a(n);
    auto dfs = [&](auto&& self, int i, int used) -> void {
        if (used > k || used + n - i < k) return;
        if (i == n) {
            if (used == k) res.push_back(a);
            return;
        }
        for (int x = 0; x <= m; ++x) {
            a[i] = x;
            self(self, i + 1, used + (x != 0));
        }
    };
    dfs(dfs, 0, 0);
    return res;
}

// Distinct permutations of a, in lexicographic order.
inline vvc<int> enumerate_permutations(vc<int> a) {
    vvc<int> res;
    std::sort(a.begin(), a.end());
    do {
        res.push_back(a);
    } while (std::next_permutation(a.begin(), a.end()));
    return res;
}

// k distinct indices chosen from {0,...,n-1}, in ascending order.
inline vvc<int> enumerate_combinations(int n, int k) {
    if (n < 0 || k < 0 || k > n) return {};
    if (k == 0) return {vc<int>{}};
    return enumerate_increasing(k, n - 1);
}

// Finite, terminating impartial games under normal play.
// Board must support operator<.
template<class Board>
struct impartial_game {
    using parts = std::vector<Board>;
    using options = std::vector<parts>;
    using observed_move = std::pair<parts, int>;

    struct observed_sum_move {
        int index;
        parts to;
        int grundy;
    };

private:
    std::function<options(const Board&)> next;
    std::map<Board, int> memo;
    std::set<Board> active;

public:
    impartial_game() = default;

    std::size_t cache_size() const {
        return memo.size();
    }

    // f(board) -> vector<Board>
    template<class F>
    void set_moves(F f) {
        next = [f](const Board& b) -> options {
            options res;
            for (const Board& to : f(b)) {
                res.push_back(parts{to});
            }
            return res;
        };
        clear();
    }

    // f(board) -> vector<vector<Board>>
    // Each inner vector is one move's independent components.
    template<class F>
    void set_splits(F f) {
        next = [f](const Board& b) -> options {
            return f(b);
        };
        clear();
    }

    void clear() {
        memo.clear();
        active.clear();
    }

    int get(const Board& b) {
        auto it = memo.find(b);
        if (it != memo.end()) return it->second;

        if (!next) {
            throw std::logic_error("set_moves or set_splits first");
        }
        if (!active.insert(b).second) {
            throw std::logic_error("cycle in game graph");
        }

        int result;
        try {
            options os = next(b);
            std::vector<char> seen(os.size() + 1, false);

            for (const parts& to : os) {
                int g = get_sum(to);
                if (g < (int)seen.size()) {
                    seen[g] = true;
                }
            }

            result = 0;
            while (seen[result]) ++result;
        } catch (...) {
            active.erase(b);
            throw;
        }

        active.erase(b);
        memo.emplace(b, result);
        return result;
    }

    int get_sum(const parts& boards) {
        int result = 0;
        for (const Board& b : boards) {
            result ^= get(b);
        }
        return result;
    }

    bool win(const Board& b) {
        return get(b) != 0;
    }

    bool lose(const Board& b) {
        return get(b) == 0;
    }

    vc<Board> win_states(const vc<Board>& boards) {
        vc<Board> res;
        for (const Board& b : boards) {
            if (win(b)) res.push_back(b);
        }
        std::sort(res.begin(), res.end());
        return res;
    }

    vc<Board> lose_states(const vc<Board>& boards) {
        vc<Board> res;
        for (const Board& b : boards) {
            if (lose(b)) res.push_back(b);
        }
        std::sort(res.begin(), res.end());
        return res;
    }

    bool win_sum(const parts& boards) {
        return get_sum(boards) != 0;
    }

    std::vector<observed_move> inspect(const Board& b) {
        if (!next) {
            throw std::logic_error("set_moves or set_splits first");
        }
        std::vector<observed_move> res;
        for (const parts& to : next(b)) {
            res.push_back({to, get_sum(to)});
        }
        return res;
    }

    std::vector<observed_sum_move> inspect_sum(const parts& boards) {
        int total = get_sum(boards);
        std::vector<observed_sum_move> res;

        for (int i = 0; i < (int)boards.size(); ++i) {
            int rest = total ^ get(boards[i]);
            for (const parts& to : next(boards[i])) {
                res.push_back({i, to, rest ^ get_sum(to)});
            }
        }
        return res;
    }

    // (false,{}) means no winning move.
    // (true,{}) means a valid move to the empty game.
    std::pair<bool, parts> best_move(const Board& b) {
        if (!win(b)) return {false, {}};

        for (const auto& p : inspect(b)) {
            if (p.second == 0) return {true, p.first};
        }
        throw std::logic_error("inconsistent winning position");
    }

    // (-1,{}) means no winning move.
    // Otherwise replace component index with returned parts.
    std::pair<int, parts> best_move_sum(const parts& boards) {
        int total = get_sum(boards);
        if (total == 0) return {-1, {}};

        for (int i = 0; i < (int)boards.size(); ++i) {
            int rest = total ^ get(boards[i]);
            for (const parts& to : next(boards[i])) {
                if ((rest ^ get_sum(to)) == 0) {
                    return {i, to};
                }
            }
        }
        throw std::logic_error("inconsistent winning sum");
    }

    template<class F>
    std::vector<int> sequence(int n, F make_board) {
        std::vector<int> res;
        res.reserve(n);
        for (int i = 0; i < n; ++i) {
            res.push_back(get(make_board(i)));
        }
        return res;
    }

    // Mainly for Board=int.
    std::vector<int> sequence(int n) {
        return sequence(n, [](int i) {
            return Board(i);
        });
    }

    template<class MakeBoard, class Predicted>
    int first_mismatch(int n, MakeBoard make_board,
                       Predicted predicted) {
        for (int i = 0; i < n; ++i) {
            Board b = make_board(i);
            if (get(b) != predicted(b)) return i;
        }
        return -1;
    }

    template<class Predicted>
    int first_mismatch(int n, Predicted predicted) {
        return first_mismatch(
            n,
            [](int i) { return Board(i); },
            predicted
        );
    }

    // Heuristic, not a proof of periodicity.
    // Returns (preperiod,period), or (-1,-1).
    static std::pair<int, int> guess_period(
        const std::vector<int>& a,
        int max_period,
        int min_repeats = 4
    ) {
        int n = (int)a.size();

        for (int p = 1; p <= max_period; ++p) {
            int start = 0;
            for (int i = 0; i + p < n; ++i) {
                if (a[i] != a[i + p]) {
                    start = i + 1;
                }
            }
            if (n - start >= 1LL * min_repeats * p) {
                return {start, p};
            }
        }
        return {-1, -1};
    }
};

} // namespace ryoku
