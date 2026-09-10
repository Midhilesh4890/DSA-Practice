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
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;
    s = " " + s;

    vi pref0(n + 1), prefd(n + 1);
    for (int i = 1; i <= n; ++i) {
        pref0[i] = pref0[i - 1] + (s[i] == '0');
        prefd[i] = prefd[i - 1];
        if (i > 1) {
            prefd[i] += (s[i] != s[i - 1]);
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        const int len = r - l + 1;
        const int zeros = pref0[r] - pref0[l - 1];
        const int ones = len - zeros;

        const int d = prefd[r] - prefd[l] + (s[l] != s[r]);
        const int m = d / 2;

        int p = 1;
        p = max(p, m);
        p = max(p, (zeros + 1) / 2);
        p = max(p, (ones + 1) / 2);
        p = max(p, (len - m + 2) / 3);

        cout << 4 * p - len << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
