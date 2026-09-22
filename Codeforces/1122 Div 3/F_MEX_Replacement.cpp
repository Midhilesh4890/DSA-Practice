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

bool check(ll target, const vpll &a, ll total) {
    ll req = 1, rem = 0, prev = target;
    for (int i = sz(a) - 1; i >= 0; i--) {
        ll x = a[i].fi, y = a[i].se;
        ll diff = prev - x - 1;
        while (diff > 0) {
            req *= 2;
            if (req > total) return false;
            diff--;
        }
        if (x == 0) return req <= y + rem;
        if (y < req) req += req - y;
        else rem += y - req;
        if (req > total) return false;
        prev = x;
    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    vpll a(n);
    ll total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i].fi >> a[i].se;
        total += a[i].se;
    }
    sort(all(a));
    if (a[0].fi != 0) a.insert(a.begin(), {0, 0});

    ll res = a.back().fi;
    ll h = res + 1;
    for (ll cnt = total; cnt > 0; cnt /= 2) h++;
    while (res + 1 < h) {
        ll m = res + (h - res) / 2;
        if (check(m, a, total)) res = m;
        else h = m;
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
