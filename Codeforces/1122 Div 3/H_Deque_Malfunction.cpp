#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;

const ll INF = (ll)4e18;
constexpr int inf = 1000000000;
const int MOD1 = 998244353;
const int MOD2 = 1000000007;
const int INV1 = (MOD1 + 1) / 2;
const int INV2 = (MOD2 + 1) / 2;

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) ((int)(v).size())

#define pb push_back
#define eb emplace_back

#define fi first
#define se second

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = (a); i >= (b); i--)

ll modpow(ll a, ll e, ll mod) {
    a = (a % mod + mod) % mod;
    ll res = 1 % mod;
    while (e > 0) {
        if (e & 1) res = res * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}

struct Fenwick {
    vi bit;

    Fenwick(int n) : bit(n + 1) {}

    void update(int i, int val) {
        for (; i < sz(bit); i += i & -i) {
            bit[i] = max(bit[i], val);
        }
    }

    int query(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) {
            res = max(res, bit[i]);
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vi b(m + 1), last(n + 2);
    rep(i, 1, m + 1) {
        cin >> b[i];
        last[b[i]] = i;
    }

    rep(i, 1, n + 1) {
        if (last[i] == 0) {
            cout << -1 << '\n';
            return;
        }
    }

    vi pref(n + 2, m + 1), suff(n + 2, m + 1);
    rep(i, 1, n + 1) pref[i] = min(pref[i - 1], last[i]);
    rrep(i, n, 1) suff[i] = min(suff[i + 1], last[i]);

    Fenwick left(n), right(n);
    int res = 0;

    rrep(i, m, 1) {
        int x = b[i];
        int l = 1 + left.query(x - 1);
        int r = 1 + right.query(n - x);

        if (i <= pref[n]) res = max(res, l + r - 1);
        if (i < pref[x - 1]) left.update(x, l);
        if (i < suff[x + 1]) right.update(n - x + 1, r);
    }

    cout << n - res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
