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
    string s;
    cin >> n >> q >> s;

    ll z = 0, d = 0;
    rep(i, 0, n) z += (s[i] == '0');

    rep(i, 1, n) {
        if (s[i - 1] != s[i]) {
            d += ll(i) * (n - i);
        }
    }

    cout << (d + z * (n - z)) / 2;

    while (q--) {
        int i;
        cin >> i;
        i--;

        if (i > 0) {
            ll w = ll(i) * (n - i);
            if (s[i - 1] == s[i]) {
                d += w;
            } else {
                d -= w;
            }
        }

        if (i + 1 < n) {
            ll w = ll(i + 1) * (n - i - 1);
            if (s[i] == s[i + 1]) {
                d += w;
            } else {
                d -= w;
            }
        }

        if (s[i] == '0') {
            s[i] = '1';
            z--;
        } else {
            s[i] = '0';
            z++;
        }

        cout << ' ' << (d + z * (n - z)) / 2;
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
