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
    int n, q;
    cin >> n >> q;

    vi a(n), queries(q);
    rep(i, 0, n) cin >> a[i];

    int l = 0;
    rep(i, 0, q) {
        cin >> queries[i];
        l = max(l, queries[i]);
    }

    vi res;
    while (true) {
        int mn = *min_element(all(a));
        int mx = *max_element(all(a));
        res.pb(mx - mn);

        if (mx == 0 || sz(res) > l) break;

        vi b;
        b.reserve(n * (n - 1) / 2);
        rep(i, 0, n) {
            rep(j, i + 1, n) {
                b.pb(a[i] ^ a[j]);
            }
        }

        nth_element(b.begin(), b.begin() + n, b.end());
        b.resize(n);
        a = b;
    }

    rep(i, 0, q) {
        int x = queries[i];
        if (x < sz(res)) {
            cout << res[x] << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
