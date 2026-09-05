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

void solve() {
    int n;
    cin >> n;
    vi b(n), diff(n + 1, 0);
    rep(i, 0, n) {
        cin >> b[i];
        if (b[i] > 0) {
            int l = max(0, i - b[i] + 1);
            int r = min(n - 1, i + b[i] - 1);
            ++diff[l];
            --diff[r + 1];
        }
    }

    string res(n, '0');
    vi dist(n, n);
    int cnt = 0;
    bool flag = false;
    rep(i, 0, n) {
        cnt += diff[i];
        if (cnt == 0) {
            res[i] = '1';
            dist[i] = 0;
            flag = true;
        }
    }

    if (!flag) {
        cout << -1 << '\n';
        return;
    }

    rep(i, 1, n) dist[i] = min(dist[i], dist[i - 1] + 1);
    rrep(i, n - 2, 0) dist[i] = min(dist[i], dist[i + 1] + 1);

    rep(i, 0, n) {
        if (b[i] != -1 && b[i] != dist[i]) {
            cout << -1 << '\n';
            return;
        }
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
