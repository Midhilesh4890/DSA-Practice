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

const int MAXN = 300000;

vector<vi> limit(MAXN + 1);
vll power(MAXN + 1, 1);

void precompute() {
    vi rad(MAXN + 1, 1);
    for (int p = 2; p <= MAXN; p++) {
        if (rad[p] != 1) {
            continue;
        }
        for (int x = p; x <= MAXN; x += p) {
            rad[x] *= p;
        }
    }

    for (int y = 2; y <= MAXN; y++) {
        for (int x = rad[y]; x < y; x += rad[y]) {
            limit[x].push_back(y);
        }
    }

    for (int i = 1; i <= MAXN; i++) {
        power[i] = power[i - 1] * 2 % MOD1;
    }
}

int getf(int x, int y) {
    while (x < y) {
        int i = upper_bound(limit[x].begin(), limit[x].end(), y) - limit[x].begin();
        if (i == 0) {
            break;
        }
        y = limit[x][i - 1] - 1;
        x--;
    }
    return x;
}

ll range(int x, int l, int right, const vi& cnt, const vi& pref) {
    if (l > right) {
        return 0;
    }
    ll ways = power[pref[right] - pref[x]] - power[pref[l - 1] - pref[x]];
    ways = (ways + MOD1) % MOD1;
    return (power[cnt[x]] - 1) * ways % MOD1;
}

void solve() {
    int n;
    cin >> n;

    vi a(n), cnt(n + 1), pref(n + 1);
    for (auto &x : a) cin >> x;
    for (auto x : a) cnt[x]++;
    for (int x = 1; x <= n; x++) {
        pref[x] = pref[x - 1] + cnt[x];
    }

    ll res = 0;
    for (int x = 1; x <= n; x++) {
        if (cnt[x] == 0) {
            continue;
        }
        res = (res + x * (power[cnt[x]] - 1)) % MOD1;

        int l = x + 1;
        int value = x;
        for (int y : limit[x]) {
            if (y > n || value == 1) {
                break;
            }
            res = (res + value * range(x, l, y - 1, cnt, pref)) % MOD1;
            value = getf(x - 1, y - 1);
            l = y;
        }
        res = (res + value * range(x, l, n, cnt, pref)) % MOD1;
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
