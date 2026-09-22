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
    int n, m;
    ll k, x, y;
    cin >> n >> m >> k;
    cin >> x >> y;

    vll a(n), b(m), pre(n + 1);
    for (auto& c : a) cin >> c;
    for (auto& c : b) cin >> c;
    sort(all(a));
    sort(all(b));

    rep(i, 0, n) pre[i + 1] = pre[i] + a[i];

    ll total = x + y * k, notes = 0;
    int p = n, res = 0;
    rep(j, 0, m + 1) {
        if (j > 0) {
            notes += (b[j - 1] + k - 1) / k;
            total -= b[j - 1];
        }
        if (notes > y) break;
        while (p > 0 && pre[p] > total) p--;
        res = max(res, p + j);
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
