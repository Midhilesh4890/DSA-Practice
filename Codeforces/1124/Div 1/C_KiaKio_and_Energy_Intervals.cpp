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

ull visited[1 << 18] = {};
ull nxt = 1;

bool check(int l, int r, int mask, const vi &a, const vi &pref) {
    if (l == r) return false;
    int mid = l + (r - l) / 2;

    ull curr = nxt++;
    int mx = 0, p = mid + 1;
    for (int i = mid; i >= l; i--) {
        mx = max(mx, a[i]);
        while (p <= r && a[p] <= mx) {
            visited[pref[p + 1] & mask] = curr;
            p++;
        }
        int req = (pref[i] & mask) ^ mask;
        if ((mx & mask) == mask && visited[req] == curr) return true;
    }

    curr = nxt++;
    mx = 0;
    p = mid;
    for (int i = mid + 1; i <= r; i++) {
        mx = max(mx, a[i]);
        while (p >= l && a[p] <= mx) {
            visited[pref[p] & mask] = curr;
            p--;
        }
        int req = (pref[i + 1] & mask) ^ mask;
        if ((mx & mask) == mask && visited[req] == curr) return true;
    }

    return check(l, mid, mask, a, pref)
        || check(mid + 1, r, mask, a, pref);
}

void solve() {
    int n;
    cin >> n;
    vi a(n);
    for (auto &x : a) cin >> x;

    vi pref(n + 1);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] ^ a[i];
        mx = max(mx, a[i]);
    }

    int res = 0;
    for (int bit = 17; bit >= 0; bit--) {
        int mask = res | (1 << bit);
        if (mask <= mx && check(0, n - 1, mask, a, pref)) {
            res = mask;
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
