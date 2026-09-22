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
    int n, k;
    cin >> n >> k;
    vi a(n), spf(n + 1);
    for (int &x : a) cin >> x;

    for (int p = 2; p <= n; p++) {
        if (spf[p] != 0) continue;
        for (int x = p; x <= n; x += p) {
            if (spf[x] == 0) spf[x] = p;
        }
    }

    vll dp(n + 1, 0);
    for (int x = k + 1; x <= n; x++) {
        dp[x] = INF;
        int rem = x;
        while (rem > 1) {
            int p = spf[rem];
            dp[x] = min(dp[x], 1 + p * dp[x / p]);
            while (rem % p == 0) rem /= p;
        }
    }

    ll res = 0;
    for (int x : a) res += dp[x];
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
