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
    vll a(n);
    for (auto &x : a) cin >> x;
    sort(all(a));

    vll inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i < n; i++) {
        inv[i] = MOD1 - (MOD1 / i) * inv[MOD1 % i] % MOD1;
    }

    ll trees = 1;
    for (int i = 1; i < n; i++) {
        trees = trees * i % MOD1;
    }

    ll sum = a[n - 1] % MOD1;
    ll res = 0;
    for (int i = n - 2; i >= 0; i--) {
        int m = n - 1 - i;
        ll cost = (sum - a[i] * m % MOD1 + MOD1) % MOD1;
        ll ways = trees * inv[m] % MOD1;
        res = (res + cost * ways) % MOD1;
        sum = (sum + a[i]) % MOD1;
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
