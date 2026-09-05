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
    vi b(n), diff(n + 1, 0);
    bool flag = false;
    rep(i, 0, n) {
        cin >> b[i];
        if (b[i] != -1) flag = true;
        if (b[i] > 0) {
            int l = max(0, i - b[i] + 1);
            int r = min(n - 1, i + b[i] - 1);
            ++diff[l];
            --diff[r + 1];
        }
    }

    vi id(n, -1);
    int cnt = 0, m = 0;
    rep(i, 0, n) {
        cnt += diff[i];
        if (cnt == 0) id[i] = m++;
    }

    vi cur(m, 0), req(m, 0);
    rep(i, 0, n) {
        if (b[i] == -1) continue;
        int l = i - b[i], r = i + b[i];
        int x = (l >= 0 ? id[l] : -1);
        int y = (r < n ? id[r] : -1);
        if (x == -1 && y == -1) {
            cout << 0 << '\n';
            return;
        }
        if (x == -1) cur[y] = 1;
        else if (y == -1 || x == y) cur[x] = 1;
        else req[y] = 1;
    }

    ll dp0 = 1, dp1 = 0;
    rep(i, 0, m) {
        ll total = (dp0 + dp1) % MOD2;
        ll next = cur[i] ? 0 : (req[i] ? dp1 : total);
        dp1 = total;
        dp0 = next;
    }

    ll res = (dp0 + dp1) % MOD2;
    if (!flag) res = (res + MOD2 - 1) % MOD2;
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
