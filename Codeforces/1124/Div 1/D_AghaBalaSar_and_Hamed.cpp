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
    int n;
    cin >> n;

    vi p(n), nxt(n, -1), st;
    rep(i, 0, n) {
        cin >> p[i];
    }

    rep(i, 0, n) {
        while (!st.empty() && p[st.back()] < p[i]) {
            nxt[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }

    vll dp(n);
    vi last(n), freq(n);
    rrep(i, n - 1, 0) {
        int j = nxt[i];
        last[i] = i;
        if (j != -1) {
            last[i] = last[j];
            dp[i] = 2LL * (j - i) - 1 + dp[j] + last[i] - j;
        }
    }

    ll res = 1LL * n * (n - 1) / 2;
    int r = -1, cnt = 0;
    rep(i, 0, n) {
        if (i > 0 && nxt[i - 1] != -1) {
            int j = nxt[i - 1];
            if (freq[j]++ == 0) cnt++;
            r = max(r, j);
        }
        if (freq[i] > 0) cnt--;

        if (r <= i) {
            res += dp[i];
            continue;
        }

        int j = nxt[i], k = nxt[j];
        ll ans = 3LL * (r - i) - cnt;
        ans -= j - i - 1;
        ans -= 2 - (freq[j] > 0);
        if (k != -1 && k <= r) ans -= 1 - (freq[k] > 0);
        ans += dp[r] + 1LL * (j == r ? 1 : 2) * (last[r] - r);
        res += ans;
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
