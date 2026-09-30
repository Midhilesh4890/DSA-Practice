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

void solve() {
    int n;
    cin >> n;
    vi bit(n + 1, 0), c(n + 1), freq(n, 0);

    rep(i, 1, n + 1) {
        int x;
        cin >> x;

        int sum = 0;
        for (int j = x; j > 0; j -= j & -j)
            sum += bit[j];

        c[i] = i - 1 - sum;
        freq[c[i]]++;

        for (int j = x; j <= n; j += j & -j)
            bit[j]++;
    }

    ll res = 1;
    int cur = 0, prev = 0;
    rep(i, 1, n + 1) {
        if (i > 1) cur += freq[i - 1];
        if (c[i] == 0) continue;
        res = res * (cur - prev) % MOD1;
        prev++;
    }

    ll d = 1;
    rep(i, 1, n)
        rep(j, 2, freq[i] + 1)
            d = d * j % MOD1;

    res = res * modpow(d, MOD1 - 2, MOD1) % MOD1;
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
