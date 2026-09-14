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

const int N = 100000;
ll fact[N + 1];

void solve() {
    int n;
    cin >> n;
    vll a(n);
    for (ll &x : a) cin >> x;

    int l = n / 2;
    int r = (n - 1) / 2;
    int cnt = 0;
    ll m = a.back();

    for (int k = 1; k <= 2; k++) {
        ll d = a[k];
        vll b;
        b.reserve(n);
        b.pb(m);

        rep(i, 0, l) b.pb(1LL * i * d);
        for (int i = 1; i <= r; i++) b.pb(m - 1LL * i * d);

        sort(all(b));
        if (b == a) cnt++;
    }

    ll res = fact[l] * fact[r - 1] % MOD2;
    res = res * cnt % MOD2;
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD2;
    }

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
