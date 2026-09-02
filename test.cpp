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
 
int n, m; 
int timer = 0, total; 
 
vi start, low, depth; 
vi edgeu, edgev, stk; 
vi visited, odd; 
 
vector<vpii> graph; 
vector<vi> tree; 
 
void make_block(int last) { 
    ++total; 
 
    vi nodes; 
    bool flag = false; 
 
    while (true) { 
        int id = stk.back(); 
        stk.pop_back(); 
 
        int u = edgeu[id]; 
        int v = edgev[id]; 
 
        if ((depth[u] & 1) == (depth[v] & 1)) flag = true; 
 
        if (visited[u] != total) { 
            visited[u] = total; 
            nodes.pb(u); 
        } 
 
        if (visited[v] != total) { 
            visited[v] = total; 
            nodes.pb(v); 
        } 
 
        if (id == last) break; 
    } 
 
    odd[total] = flag; 
 
    for (int v : nodes) { 
        tree[total].pb(v); 
        tree[v].pb(total); 
    } 
} 
 
void dfs(int u, int pe) { 
    start[u] = low[u] = ++timer; 
 
    for (auto [v, id] : graph[u]) { 
        if (id == pe) continue; 
 
        if (!start[v]) { 
            depth[v] = depth[u] + 1; 
            stk.pb(id); 
 
            dfs(v, id); 
 
            low[u] = min(low[u], low[v]); 
 
            if (low[v] >= start[u]) { 
                make_block(id); 
            } 
        } else if (start[v] < start[u]) { 
            stk.pb(id); 
            low[u] = min(low[u], start[v]); 
        } 
    } 
} 
 
void solve() { 
    cin >> n >> m; 
 
    graph.resize(n + 1); 
 
    edgeu.resize(m); 
    edgev.resize(m); 
 
    rep(i, 0, m) { 
        int u, v; 
        cin >> u >> v; 
 
        edgeu[i] = u; 
        edgev[i] = v; 
 
        graph[u].eb(v, i); 
        graph[v].eb(u, i); 
    } 
 
    start.assign(n + 1, 0); 
    low.assign(n + 1, 0); 
    depth.assign(n + 1, 0); 
 
    total = n; 
 
    tree.resize(n + m + 5); 
    visited.assign(n + 1, 0); 
    odd.assign(n + m + 5, 0); 
 
    rep(i, 1, n + 1) { 
        if (!start[i]) dfs(i, -1); 
    } 
 
    int height = 1; 
    while ((1 << height) <= total) ++height; 
 
    vector<vi> up(height, vi(total + 1)); 
    vi level(total + 1); 
    vi root(total + 1); 
    vi prefix(total + 1); 
 
    rep(s, 1, total + 1) { 
        if (root[s]) continue; 
 
        root[s] = s; 
        prefix[s] = odd[s]; 
 
        vi st = {s}; 
 
        while (!st.empty()) { 
            int u = st.back(); 
            st.pop_back(); 
 
            for (int v : tree[u]) { 
                if (v == up[0][u]) continue; 
 
                up[0][v] = u; 
                level[v] = level[u] + 1; 
                root[v] = s; 
                prefix[v] = prefix[u] + odd[v]; 
 
                st.pb(v); 
            } 
        } 
    } 
 
    rep(j, 1, height) { 
        rep(i, 1, total + 1) { 
            up[j][i] = up[j - 1][up[j - 1][i]]; 
        } 
    } 
 
    auto lca = [&](int u, int v) { 
        if (level[u] < level[v]) swap(u, v); 
 
        int d = level[u] - level[v]; 
 
        rep(j, 0, height) { 
            if ((d >> j) & 1) u = up[j][u]; 
        } 
 
        if (u == v) return u; 
 
        rrep(j, height - 1, 0) { 
            if (up[j][u] != up[j][v]) { 
                u = up[j][u]; 
                v = up[j][v]; 
            } 
        } 
 
        return up[0][u]; 
    }; 
 
    int q; 
    cin >> q; 
 
    while (q--) { 
        int u, v; 
        cin >> u >> v; 
 
        if (u == v || root[u] != root[v]) { 
            cout << "No\n"; 
            continue; 
        } 
 
        int p = lca(u, v); 
 
        int cnt = prefix[u] + prefix[v] - 2 * prefix[p] + odd[p]; 
 
        if (cnt || ((depth[u] ^ depth[v]) & 1)) { 
            cout << "Yes\n"; 
        } else { 
            cout << "No\n"; 
        } 
    } 
} 
 
int main() { 
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
 
    solve(); 
 
    return 0; 
}