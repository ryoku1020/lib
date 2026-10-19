#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>
#include <limits>
#include <numeric>

namespace ryoku {

// Inclusive bounds. Every result is lexicographically sorted.
// order: 0=arbitrary, 1=nondecreasing, 2=strictly increasing,
//       -1=nonincreasing, -2=strictly decreasing.
// sum_lo <= sum(a) <= sum_hi; by default there is no sum constraint.
// min_n <= size(a) <= max_n. The bound vectors have length max_n.
// All integer arithmetic for sums and endpoints is done in long long.
inline vvc<int> enumerate(const vc<int>& lo, const vc<int>& hi,
                          int min_n, int max_n, int order = 0,
                          long long sum_lo = std::numeric_limits<long long>::min(),
                          long long sum_hi = std::numeric_limits<long long>::max()) {
    if (min_n < 0 || max_n < min_n || (int)lo.size() != max_n ||
        (int)hi.size() != max_n || order < -2 || order > 2 || sum_lo > sum_hi)
        throw std::invalid_argument("enumerate: invalid arguments");
    vvc<int> res;
    vc<int> a;
    // Suffix bounds are safe even when some interval is empty.
    vc<long long> suf_lo(max_n + 1), suf_hi(max_n + 1);
    for (int i = max_n - 1; i >= 0; --i) {
        // Suffix sums fit in long long for practical enumerated lengths.
        suf_lo[i] = suf_lo[i + 1] + (long long)lo[i];
        suf_hi[i] = suf_hi[i + 1] + (long long)hi[i];
    }
    auto dfs = [&](auto&& self, int i, long long sum) -> void {
        if (i >= min_n && sum_lo <= sum && sum <= sum_hi) res.push_back(a);
        if (i == max_n) return;
        long long l = lo[i], r = hi[i];
        if (i) {
            if (order == 1) l = std::max(l, (long long)a.back());
            if (order == 2) l = std::max(l, (long long)a.back() + 1);
            if (order == -1) r = std::min(r, (long long)a.back());
            if (order == -2) r = std::min(r, (long long)a.back() - 1);
        }
        if (l > r) return;
        // Even the smallest value of this position cannot fit the upper sum bound.
        // For variable length, stopping at any later length is allowed.
        for (long long x = l; x <= r; ++x) {
            long long next_sum = sum + x;
            if (min_n == max_n) {
                if (next_sum + suf_lo[i + 1] > sum_hi ||
                    next_sum + suf_hi[i + 1] < sum_lo) continue;
            }
            a.push_back((int)x);
            self(self, i + 1, next_sum);
            a.pop_back();
        }
    };
    dfs(dfs, 0, 0);
    return res;
}

inline vvc<int> enumerate(const vc<int>& lo, const vc<int>& hi,
                          int order = 0,
                          long long sum_lo = std::numeric_limits<long long>::min(),
                          long long sum_hi = std::numeric_limits<long long>::max()) {
    return enumerate(lo, hi, (int)lo.size(), (int)lo.size(), order, sum_lo, sum_hi);
}

inline vvc<int> enumerate_vec(const vc<int>& lo, const vc<int>& hi) {
    return enumerate(lo, hi);
}
inline vvc<int> enumerate_vec(const vc<int>& hi) {
    return enumerate(vc<int>(hi.size(), 0), hi);
}
inline vvc<int> enumerate_vec(int n, int l, int r) {
    if (n < 0 || l > r) return {};
    return enumerate(vc<int>(n, l), vc<int>(n, r));
}
inline vvc<int> enumerate_vec(int n, int m) {
    if (m < 0) return {};
    return enumerate_vec(n, 0, m);
}
inline vvc<int> enumerate_nondecreasing(const vc<int>& lo, const vc<int>& hi) {
    return enumerate(lo, hi, 1);
}
inline vvc<int> enumerate_nondecreasing(const vc<int>& hi) {
    return enumerate(vc<int>(hi.size(), 0), hi, 1);
}
inline vvc<int> enumerate_nondecreasing(int n, int l, int r) {
    if (n < 0 || l > r) return {};
    return enumerate(vc<int>(n, l), vc<int>(n, r), 1);
}
inline vvc<int> enumerate_nondecreasing(int n, int m) {
    if (m < 0) return {};
    return enumerate_nondecreasing(n, 0, m);
}
inline vvc<int> enumerate_increasing(const vc<int>& lo, const vc<int>& hi) {
    return enumerate(lo, hi, 2);
}
inline vvc<int> enumerate_increasing(const vc<int>& hi) {
    return enumerate(vc<int>(hi.size(), 0), hi, 2);
}
inline vvc<int> enumerate_increasing(int n, int l, int r) {
    if (n < 0 || l > r) return {};
    return enumerate(vc<int>(n, l), vc<int>(n, r), 2);
}
inline vvc<int> enumerate_increasing(int n, int m) {
    if (m < 0) return {};
    return enumerate_increasing(n, 0, m);
}
inline vvc<int> enumerate_nonincreasing(const vc<int>& lo, const vc<int>& hi) {
    return enumerate(lo, hi, -1);
}
inline vvc<int> enumerate_nonincreasing(int n, int l, int r) {
    if (n < 0 || l > r) return {};
    return enumerate(vc<int>(n, l), vc<int>(n, r), -1);
}
inline vvc<int> enumerate_nonincreasing(int n, int m) {
    if (m < 0) return {};
    return enumerate_nonincreasing(n, 0, m);
}
inline vvc<int> enumerate_decreasing(const vc<int>& lo, const vc<int>& hi) {
    return enumerate(lo, hi, -2);
}
inline vvc<int> enumerate_decreasing(int n, int l, int r) {
    if (n < 0 || l > r) return {};
    return enumerate(vc<int>(n, l), vc<int>(n, r), -2);
}
inline vvc<int> enumerate_decreasing(int n, int m) {
    if (m < 0) return {};
    return enumerate_decreasing(n, 0, m);
}

// Exact sum and upper-bounded sum, with optional coordinate bounds / ordering.
inline vvc<int> enumerate_sum(const vc<int>& lo, const vc<int>& hi, long long s, int order = 0) {
    return enumerate(lo, hi, order, s, s);
}
inline vvc<int> enumerate_sum_le(const vc<int>& lo, const vc<int>& hi, long long s, int order = 0) {
    return enumerate(lo, hi, order, std::numeric_limits<long long>::min(), s);
}
inline vvc<int> enumerate_sum(int n, int m, int s) {
    if (n < 0 || m < 0 || s < 0) return {};
    return enumerate_sum(vc<int>(n, 0), vc<int>(n, m), s);
}
inline vvc<int> enumerate_sum_le(int n, int m, int s) {
    if (n < 0 || m < 0 || s < 0) return {};
    return enumerate_sum_le(vc<int>(n, 0), vc<int>(n, m), s);
}
inline vvc<int> enumerate_partition(int n, int m, int s) {
    if (n < 0 || m < 0 || s < 0) return {};
    return enumerate_sum(vc<int>(n, 0), vc<int>(n, m), s, 1);
}
inline vvc<int> enumerate_partition_le(int n, int m, int s) {
    if (n < 0 || m < 0 || s < 0) return {};
    return enumerate_sum_le(vc<int>(n, 0), vc<int>(n, m), s, 1);
}
inline vvc<int> enumerate_sum_ge(const vc<int>& lo, const vc<int>& hi, long long s, int order = 0) {
    return enumerate(lo, hi, order, s);
}
inline vvc<int> enumerate_sum_range(const vc<int>& lo, const vc<int>& hi,
                                    long long l, long long r, int order = 0) {
    return enumerate(lo, hi, order, l, r);
}

// All lengths 0..N (or L..R). For coordinate bounds, use the main enumerate().
inline vvc<int> enumerate_dynamic(int n, int l, int r, int order = 0) {
    if (n < 0 || l > r) return {};
    return enumerate(vc<int>(n, l), vc<int>(n, r), 0, n, order);
}
inline vvc<int> enumerate_dynamic(int n, int m) {
    if (m < 0) return {};
    return enumerate_dynamic(n, 0, m);
}
inline vvc<int> enumerate_dynamic(int min_n, int max_n, int l, int r, int order) {
    if (min_n < 0 || max_n < min_n || l > r) return {};
    return enumerate(vc<int>(max_n, l), vc<int>(max_n, r), min_n, max_n, order);
}
inline vvc<int> enumerate_dynamic(const vc<int>& lo, const vc<int>& hi, int min_n = 0, int order = 0) {
    return enumerate(lo, hi, min_n, (int)lo.size(), order);
}
inline vvc<int> enumerate_dynamic_sum(const vc<int>& lo, const vc<int>& hi,
                                      int min_n, long long sum_lo, long long sum_hi, int order = 0) {
    return enumerate(lo, hi, min_n, (int)lo.size(), order, sum_lo, sum_hi);
}

// Exactly k strictly positive entries, with 0 <= a[i] <= m.
inline vvc<int> enumerate_support(int n, int m, int k) {
    if (n < 0 || m < 0 || k < 0 || k > n) return {};
    vvc<int> res;
    vc<int> a(n);
    auto dfs = [&](auto&& self, int i, int used) -> void {
        if (used > k || used + n - i < k) return;
        if (i == n) { if (used == k) res.push_back(a); return; }
        for (long long x = 0; x <= m; ++x) {
            a[i] = (int)x;
            self(self, i + 1, used + (x != 0));
        }
    };
    dfs(dfs, 0, 0);
    return res;
}
inline vvc<int> enumerate_permutations(vc<int> a) {
    vvc<int> res;
    std::sort(a.begin(), a.end());
    do { res.push_back(a); } while (std::next_permutation(a.begin(), a.end()));
    return res;
}
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
