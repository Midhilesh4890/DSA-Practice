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
const int MOD = 998244353;
const int INV2 = (MOD + 1) / 2;

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

    ll sum = 0;
    int cnt[2] = {};
    ll first[2] = {}, second[2] = {};
    rep(i, 0, n) {
        ll x;
        cin >> x;
        sum += x;
        int p = x % 2;
        ++cnt[p];
        if (x >= first[p]) {
            second[p] = first[p];
            first[p] = x;
        } else {
            second[p] = max(second[p], x);
        }
    }

    ll ans = 0;
    rep(p, 0, 2) {
        if (cnt[p] >= 2) {
            ll diff = 2LL * min(cnt[p] - 1, cnt[p ^ 1]);
            ans = max(ans, first[p] + second[p] + diff);
        }
    }
    if (cnt[0] && cnt[1]) {
        ll diff = 2LL * min(cnt[0], cnt[1]) - 1;
        ans = max(ans, first[0] + first[1] + diff);
    }

    cout << (2 * sum - ans) / 2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
