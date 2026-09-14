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
    int n;
    cin >> n;
    vi a(n + 1), b(n + 1), root(n + 1);
    rep(i, 1, n + 1) cin >> a[i];
    rep(i, 1, n + 1) cin >> b[i];

    int start = -1;
    rep(i, 1, n + 1) {
        if (a[i] > b[i]) {
            cout << -1 << '\n';
            return;
        }
        if (a[i] != b[i] && start == -1) start = i;
    }
    if (start == -1) {
        cout << "0 1\n\n";
        return;
    }

    rrep(i, n, 1) root[i] = (b[i] == i ? i : root[b[i]]);
    rep(i, 1, n + 1) {
        if (a[i] != b[i] && root[i] != root[start]) {
            cout << -1 << '\n';
            return;
        }
    }

    vi res;
    res.reserve(2 * n * n);
    int p = start;

    rep(target, 1, n + 1) {
        if (a[target] == b[target]) continue;

        if (p != target) {
            vi parent(n + 1, -1);
            queue<int> q;
            vector<bool> visited(n + 1, false);
            visited[p] = true;
            parent[p] = p;
            q.push(p);

            while (!q.empty() && parent[target] == -1) {
                int u = q.front();
                q.pop();
                rep(v, a[u], b[u] + 1) {
                    if (visited[v]) continue;
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }

            if (parent[target] == -1) {
                cout << -1 << '\n';
                return;
            }

            vi path;
            for (int v = target; v != p; v = parent[v]) path.pb(v);
            reverse(all(path));
            for (int v : path) {
                while (a[p] < v) {
                    a[p]++;
                    res.pb(1);
                }
                res.pb(2);
                p = v;
            }
        }

        while (a[p] < b[p]) {
            a[p]++;
            res.pb(1);
        }
    }

    cout << sz(res) << ' ' << start << '\n';
    for (int x : res) cout << x << ' ';
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
