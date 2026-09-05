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
    vi cnt;
    int ones = 0;
    ll res = 0;
    rep(i, 0, n) {
        int x;
        cin >> x;
        if (x == 1) {
            ++ones;
        } else if (ones > 0) {
            cnt.pb(ones);
            res += ones;
        }
    }

    string s;
    cin >> s;
    int l = 0, d = 0, m = sz(cnt);
    cout << res;
    for (char ch : s) {
        if (l < m) {
            if (ch == '1') {
                res -= m - l;
                ++d;
                while (l < m && cnt[l] <= d) ++l;
            } else {
                res -= cnt[m - 1] - d;
                --m;
            }
        }
        cout << ' ' << res;
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
