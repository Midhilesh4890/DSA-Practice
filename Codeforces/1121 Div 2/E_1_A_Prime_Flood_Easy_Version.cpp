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

    vi a(n), cnt(n + 1), pref(n + 1);
    for (auto &x : a) cin >> x;
    for (auto x : a) cnt[x]++;

    vll power(n + 1, 1);
    rep(i, 1, n + 1) {
        power[i] = power[i - 1] * 2 % MOD1;
        pref[i] = pref[i - 1] + cnt[i];
    }

    vector<vi> factors(n + 1);
    rep(p, 2, n + 1) {
        if (!factors[p].empty()) continue;
        for (int x = p; x <= n; x += p) {
            factors[x].pb(p);
        }
    }

    vector<vi> dp(n + 1, vi(n + 1));
    ll res = 0;

    rep(r, 1, n + 1) {
        dp[r][r] = r;
        res = (res + (power[cnt[r]] - 1) * r) % MOD1;

        rep(l, 1, r) {
            int ans = 1;

            for (auto p : factors[l]) {
                ans = max(ans, dp[l - 1][r - (r % p == 0)]);
            }
            for (auto p : factors[r]) {
                ans = max(ans, dp[l - (l % p == 0)][r - 1]);
            }

            dp[l][r] = ans;

            int m = pref[r - 1] - pref[l];
            ll val = (power[cnt[l]] - 1) * (power[cnt[r]] - 1) % MOD1;
            val = val * power[m] % MOD1;
            res = (res + val * dp[l][r]) % MOD1;
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
