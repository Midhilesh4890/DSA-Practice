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

    vll a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    vector<vi> adj(n);
    rep(i, 0, n - 1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vi parent(n, -1), order;
    order.reserve(n);
    parent[0] = 0;
    order.pb(0);

    rep(i, 0, n) {
        int u = order[i];
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            order.pb(v);
        }
    }

    vll diff(n);
    ll res = 0;

    rrep(i, n - 1, 0) {
        int u = order[i];
        ll sum = 0;
        ll g = b[u];

        for (int v : adj[u]) {
            if (parent[v] != u) continue;
            sum += a[v];
            g = gcd(g, diff[v]);
        }

        g = gcd(g, sum);
        res += b[u] - g + a[u] % g;
        diff[u] = (g < b[u] ? g : 0);
    }

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
