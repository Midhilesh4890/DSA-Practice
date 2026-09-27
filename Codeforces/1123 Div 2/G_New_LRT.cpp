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
    int n, m;
    cin >> n >> m;

    vi c(m + 1);
    rep(i, 1, m + 1) cin >> c[i];

    vi steps;
    rep(x, 1, min(n, m) + 1) {
        if ((m & x) == x) {
            steps.pb(x);
        }
    }

    vll ways(n + 1, 0);
    vll cost(n + 1, 0);
    ways[0] = 1;

    rep(i, 1, n + 1) {
        rep(j, 0, sz(steps)) {
            int x = steps[j];
            if (x > i) break;

            ways[i] += ways[i - x];
            ways[i] %= MOD2;

            cost[i] += cost[i - x];
            cost[i] %= MOD2;

            cost[i] += ways[i - x] * c[x] % MOD2;
            cost[i] %= MOD2;
        }
    }

    cout << cost[n] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
