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

    vll a(n);
    for (ll &x : a) cin >> x;

    ll res = (a.back() > 0);
    rep(i, 0, n - 1) {
        ll bits = a[i] - 2 * a[i + 1];
        if (bits < 0) {
            cout << -1 << '\n';
            return;
        }
        res = max(res, bits);
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
