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

    vi a(n);
    int cnt = 0;
    for (int &x : a) {
        cin >> x;
        cnt += (x == 0);
    }

    if (cnt < 2) {
        cout << -1 << '\n';
    } else {
        cout << a.front() + a.back() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
