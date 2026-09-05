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
const int MOD = 998244353;
const int INV2 = (MOD + 1) / 2;

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) ((int)(v).size())

#define pb push_back
#define eb emplace_back

#define fi first
#define se second

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = (a); i >= (b); i--)

struct DSU {
    vi p, s;

    DSU(int n) : p(n), s(n, 1) {
        iota(all(p), 0);
    }

    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (s[u] < s[v]) swap(u, v);
        p[v] = u;
        s[u] += s[v];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    DSU d1(n), d2(n), d3(n);
    rep(i, 0, m) {
        int u, v, l;
        cin >> u >> v >> l;
        --u;
        --v;
        if (l == 1) d1.merge(u, v);
        else if (l == 2) d2.merge(u, v);
        else d3.merge(u, v);
    }

    vector<pair<pii, int>> a;
    a.reserve(n);
    rep(i, 0, n) {
        a.pb({{d2.find(i), d3.find(i)}, i});
    }
    sort(all(a));

    rep(i, 1, n) {
        if (a[i].fi == a[i - 1].fi) {
            d1.merge(a[i].se, a[i - 1].se);
        }
    }

    vi ans;
    int root = d1.find(0);
    rep(i, 0, n) {
        if (d1.find(i) == root) ans.pb(i + 1);
    }

    cout << sz(ans) << '\n';
    rep(i, 0, sz(ans)) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
