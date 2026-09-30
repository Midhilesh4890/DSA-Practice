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
    vi p(n + 1), q(n + 1);
    rep(i, 1, n + 1) cin >> p[i];
    rep(i, 1, n + 1) cin >> q[i];

    vi id(n + 1, -1), pos(n + 1), len(n + 1);
    vector<vi> cnt(n + 1);

    rep(i, 1, n + 1) {
        if (id[i] != -1) continue;

        vi cycle;
        int u = i;
        while (id[u] == -1) {
            id[u] = i;
            pos[u] = sz(cycle);
            cycle.pb(u);
            u = p[u];
        }

        int l = sz(cycle);
        for (int v : cycle) len[v] = l;
        if (cnt[l].empty()) cnt[l].resize(l, 0);
    }

    rep(i, 1, n + 1) {
        if (id[i] != id[q[i]]) continue;
        int l = len[i];
        int dist = (pos[q[i]] - pos[i] + l) % l;
        cnt[l][dist]++;
    }

    vi h(k + 1, 0);
    rep(l, 1, n + 1) {
        if (cnt[l].empty()) continue;
        rep(dist, 0, l) {
            if (cnt[l][dist] == 0) continue;
            int s = dist;
            if (dist == 0) s = l;
            for (int j = s; j <= k; j += l)
                h[j] += cnt[l][dist];
        }
    }

    cout << *max_element(h.begin() + 1, h.end()) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
