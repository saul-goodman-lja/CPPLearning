#include <bits/stdc++.h>
#include <unistd.h>
#ifdef _LOCAL_
#define debug(args...) print("[line:", __LINE__, ":" #args "]", ##args)
#else
#define debug(...) void(0)
#endif
#define all(a) a.begin(), a.end()
using namespace std;using llong = long long;
#define to(container, a) [](auto &&A) { return container(all(A)); }(a)
struct range { struct Iterator { using iterator_category = std::random_access_iterator_tag; using value_type = llong; using difference_type = ptrdiff_t; using pointer = llong; using reference = llong &; llong val, d; Iterator(){}; Iterator(llong val, llong d) : val(val), d(d){}; value_type operator*() const { return val; } Iterator &operator++() { return val += d, *this; } difference_type operator-(const Iterator &other) const { return (val - other.val) / d; } bool operator==(const Iterator &other) const { return val == other.val; } }; Iterator Begin, End; range(llong n) : Begin(0, 1), End(max(n, llong{0}), 1){}; range(llong a, llong b, llong d = llong(1)) : Begin(a, d), End(b, d) { llong cnt = (b - a) / d + bool((b - a) % d); End.val = a + max(cnt, llong(0)) * d; }; Iterator begin() const { return Begin; } Iterator end() const { return End; }; operator vector<Iterator::value_type>(){return vector(begin(),end());}}; //
template <typename... Args>llong pow(llong x, auto b, auto MOD) { if (b < 0) x = pow(x, MOD - 2, MOD), b = -b; if (not x) return x; llong res = 1; for (; b; (x *= x) %= MOD, b >>= 1) if (b & 1) (res *= x) %= MOD; return res;} //
template <typename T> T sum(auto &&a, T res) { for (auto x : a) res += x; return res;}//
template <typename T> llong sum(T &&a) { return sum(forward<T>(a), 0ll); }    //
template <typename T> T reversed(T a) { ranges::reverse(a); return a;} //
template <typename T> T uniqued(T a) { ranges::sort(a); a.resize(unique(begin(a), end(a)) - begin(a)); return a;} //
template <typename... Args>auto sorted(auto a, Args &&...args) { sort(begin(a), end(a), args...); return a;} //
template <typename T> T transposed(T a) { if(a.empty()) return a; int m = a.size() , n = a[0].size(); T b(n); for(int j : range(n)){ b[j].resize(m); for(int i : range(m)) b[j][i] = a[i][j];} return b;} //
template <typename T>vector<T> &operator+=(vector<T> &a, const vector<T> &b) { a.insert(end(a), begin(b), end(b)); return a;};template <typename T>vector<T> operator+(vector<T> a, const vector<T> &b) { return a += b; }; //
template <typename T>vector<T> &operator*=(vector<T> &a, int k) { if (k <= 0) a.clear(); else { assert(a.size() * k < INT_MAX); int N = a.size() * k; a.reserve(N); while (a.size() * 2 <= N) a += a; a.insert(end(a), begin(a), begin(a) + (N - a.size())); } return a;};template <typename T>vector<T> operator*(vector<T> a, int k) { return a *= k; }; //
template <typename RET>auto make_vector(RET x) { return x; }template <typename T1, typename T2, typename... Args>auto make_vector(T1 m, T2 n, Args... arg) { return vector(m, make_vector(n, arg...)); }
/* print */ template <typename Tuple, typename F, size_t... N> void TupleCall(Tuple &t, F &&f, std::index_sequence<N...>) { (f(get<N>(t)), ...); }template <typename... Args>std::ostream &operator<<(std::ostream &out, const std::tuple<Args...> &t) { TupleCall(t, [&](auto &&a) { out << a << ' '; }, make_index_sequence<sizeof...(Args)>{}); return out;}template <typename T1, typename T2>std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &t) { return out << t.first << ' ' << t.second; }template <typename T>std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) { for (size_t i = 0, n = v.size(); i < n; ++i) out << v[i] << ' '; return out;}template <typename T, typename... Args>void print(const T &t, const Args &...args) { cout << t; if constexpr (sizeof...(args)) { cout << ' '; print(args...); } else { cout << endl; }} //
auto io = [](){return cin.tie(nullptr) -> sync_with_stdio(false);}();

template <typename T>auto upgrate_type() { return 0; };template <>auto upgrate_type<int32_t>() { return (int64_t){}; }template <>auto upgrate_type<int64_t>() { return (__int128_t){}; }template <>auto upgrate_type<uint16_t>() { return (int32_t){}; }template <>auto upgrate_type<uint32_t>() { return (int64_t){}; }template <>auto upgrate_type<uint64_t>() { return (__uint128_t){}; }//
template <typename T, T MOD> struct modint { //
 using TT = decltype(upgrate_type<T>()); T val; static T norm(T x) { return x < 0 ? x + MOD : x >= MOD ? x - MOD : x; } static constexpr T get_mod() { return MOD; } modint() : val(0) {} modint(bool m) : val(norm(m)) {} modint(int8_t m) : val(norm(m)) {} modint(uint8_t m) : val(norm(m)) {} modint(int16_t m) : val(norm(m)) {} modint(uint16_t m) : val(norm(m)) {} modint(int32_t m) : val(norm(m)) {} modint(uint32_t m) : val(norm(m)) {} modint(int64_t m) : val(norm(m % MOD)) {} modint(uint64_t m) : val(norm(m % MOD)) {} modint(__int128_t m) : val(norm(m % MOD)) {} modint(__uint128_t m) : val(norm(m % MOD)) {} explicit operator bool() { return bool(val); } explicit operator int8_t() { return val; } explicit operator uint8_t() { return val; } explicit operator int16_t() { return val; } explicit operator uint16_t() { return val; } explicit operator int32_t() { return val; } explicit operator uint32_t() { return val; } explicit operator int64_t() { return val; } explicit operator uint64_t() { return val; } explicit operator __int128_t() { return val; } explicit operator __uint128_t() { return val; } bool operator==(modint o) { return val == o.val; } bool operator<=(modint o) { return val <= o.val; } bool operator!=(modint o) { return val != o.val; } bool operator>=(modint o) { return val >= o.val; } bool operator<(modint o) { return val < o.val; } bool operator>(modint o) { return val > o.val; } modint operator-() const { return modint(norm(-val)); } modint operator~() const { return modint(norm(~val)); } modint inv() const { return pow(*this, MOD - 2); } modint &operator+=(modint o) { return val = norm(val + o.val), *this; } modint &operator-=(modint o) { return val = norm(val - o.val), *this; } modint &operator*=(modint o) { return val = T(TT(val) * o.val % MOD), *this; } modint &operator/=(modint o) { return *this *= o.inv(); } modint &operator&=(modint o) { return val &= o.val, *this; } modint &operator|=(modint o) { return val |= o.val, *this; } modint &operator^=(modint o) { return val ^= o.val, *this; }  modint operator+(modint o) const { return modint(*this) += o; } modint operator-(modint o) const { return modint(*this) -= o; } modint operator*(modint o) const { return modint(*this) *= o; } modint operator/(modint o) const { return modint(*this) /= o; } modint operator&(modint o) const { return modint(*this) &= o; } modint operator|(modint o) const { return modint(*this) |= o; } modint operator^(modint o) const { return modint(*this) ^= o; } friend modint operator+(auto a, modint b) { return modint(a) + b; } friend modint operator-(auto a, modint b) { return modint(a) - b; } friend modint operator*(auto a, modint b) { return modint(a) * b; } friend modint operator/(auto a, modint b) { return modint(a) / b; } friend modint operator&(auto a, modint b) { return modint(a) & b; } friend modint operator|(auto a, modint b) { return modint(a) | b; } friend modint operator^(auto a, modint b) { return modint(a) ^ b; } friend istream &operator>>(std::istream &is, modint &a) { long long v;return is >> v, a.val = norm(v % MOD), is; }  friend ostream &operator<<(std::ostream &os, modint a) { return os << a.val; } friend std::string tostring(modint a) { return std::to_string(a.val); } 
};//
template<typename T, T MOD> auto pow(modint<T,MOD> x, auto b) { assert(b >= 0); if (not x.val) return x; modint<T,MOD> res = 1; for (; b; x *= x, b >>= 1) if (b & 1) res *= x; return res; } template <size_t N, typename T>struct COMB{ T FF[N]{1}, FI[N]; COMB() { for (int i = 1; i < N; ++i) FF[i] = FF[i - 1] * i; FI[N - 1] = FF[N - 1].inv(); for (int i = N - 1; i >= 1; --i) FI[i - 1] = FI[i] * i; } T operator()(int n, int k) { if (not(0 <= k and k <= n)) return T{0}; return FF[n] * FI[k] * FI[n - k]; }};
// constexpr llong mod = 29ll << 57 | 1; using mint = modint<llong, mod>;
// constexpr int mod = 998244353; using mint = modint<int, mod>; 
constexpr int mod = 1e9+7; using mint = modint<int, mod>; 
COMB<2 << 10, mint> comb;
struct IntegerSplitting{
    vector<mint> r;
    template<typename INT>
    mint operator()(vector<INT>&& limits,int y){ 
        if(y == 0) return 1;
        if(limits.empty() or y < 0) return 0;
        r.assign(y+1,0); r[0] = 1; 
        for(int s = 0; int i : limits) 
            for(i+=1; int j : range(s = min(y , s + i),i-1,-1)) 
                r[j] -= r[j-i]; 
        mint res = 0; 
        for(int i : range(y+1)) 
            res += comb(limits.size() + i - 1 , i) * r[y-i];
        return res;
    }
}split; 
class Solution {
public: 
      int kInversePairs(int n, int k)  {
        return (int)split(to(vector,range(n)),k);
    }
};