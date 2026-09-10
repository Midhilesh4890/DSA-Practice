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

void solve() {
    int n, m;
    cin >> n >> m;

    vpii edges(m);
    vector<vpii> g(n);
    for (int i = 0; i < m; ++i) {
        auto &[u, v] = edges[i];
        cin >> u >> v;
        u--;
        v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    int rem = m - n + 1;
    if (rem < 3) {
        cout << "NO\n";
        return;
    }

    vi parent(n, -1), parent_edge(n, -1), order;
    vector<bool> tree(m, false);
    parent[0] = 0;
    order.push_back(0);

    for (int i = 0; i < n; ++i) {
        int vertex = order[i];
        for (auto [neighbor, id_] : g[vertex]) {
            if (parent[neighbor] != -1) continue;
            parent[neighbor] = vertex;
            parent_edge[neighbor] = id_;
            tree[id_] = true;
            order.push_back(neighbor);
        }
    }

    vi edge_mask(m), vertex_mask(n);
    int idx = 0;
    for (int i = 0; i < m; ++i) {
        if (tree[i]) continue;
        int bit = 1 << idx++;
        edge_mask[i] = bit;
        auto [u, v] = edges[i];
        vertex_mask[u] ^= bit;
        vertex_mask[v] ^= bit;
    }

    for (int i = n - 1; i > 0; --i) {
        int vertex = order[i];
        edge_mask[parent_edge[vertex]] = vertex_mask[vertex];
        vertex_mask[parent[vertex]] ^= vertex_mask[vertex];
    }

    vi visited(n), reach;
    reach.reserve(n);
    for (int sub = 1; sub < (1 << rem); sub++) {
        reach.clear();
        reach.push_back(0);
        visited[0] = sub;

        for (int i = 0; i < (int)reach.size(); ++i) {
            int vertex = reach[i];
            for (auto [neighbor, id_] : g[vertex]) {
                if (visited[neighbor] == sub) continue;
                if (__builtin_parity((unsigned)(edge_mask[id_] & sub))) continue;
                visited[neighbor] = sub;
                reach.push_back(neighbor);
            }
        }

        if ((int)reach.size() == n) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
