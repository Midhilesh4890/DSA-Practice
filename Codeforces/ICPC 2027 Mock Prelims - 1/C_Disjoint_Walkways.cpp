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
    ll n;
    int q;
    cin >> n >> q;

    while (q--) {
        ll s, t;
        cin >> s >> t;

        if (s == t) {
            cout << 0 << '\n';
            continue;
        }
        if ((s & t) == 0) {
            cout << s + t << '\n';
            continue;
        }

        ll a = 1, b = 1, c = 1;
        while ((s & a) != 0) a <<= 1;
        while ((t & b) != 0) b <<= 1;

        if (a > n || b > n) {
            cout << -1 << '\n';
            continue;
        }

        while (((s | t) & c) != 0) c <<= 1;

        ll res = INF;
        if (c <= n) res = s + t + 2 * c;
        if (a != b) res = min(res, s + t + 2 * (a + b));

        cout << res << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
