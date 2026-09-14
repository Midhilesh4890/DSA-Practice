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

#define fi ptr
#define se second

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define rrep(i, a, b) for (int i = (a); i >= (b); i--)

void solve() {
    int n;
    cin >> n;

    vi diff(n + 1, 0);
    vi req(n + 1, 0);

    for (int k = 1; k <= n; ++k) {
        int a;
        cin >> a;

        ll l = 1LL * k * a;
        ll r = min(1LL * n, 1LL * k * (a + 1));

        if (l < n) {
            diff[(int)l]++;
            diff[(int)r]--;
        }

        rep(j, 0, a) {
            l = 1LL * k * j;
            r = min(1LL * n, 1LL * k * (j + 1));
            req[(int)r] = max(req[(int)r], (int)l + 1);
        }
    }

    vi dp(n + 1, 0);
    dp[0] = 1;

    int res = 1;
    int cnt = 0;
    int ptr = 0;

    rep(y, 0, n) {
        cnt += diff[y];

        if (cnt == 0) {
            dp[y + 1] = res;
            res = 2LL * res % MOD2;
        }

        while (ptr < req[y + 1]) {
            res -= dp[ptr];
            if (res < 0) res += MOD2;
            ptr++;
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
