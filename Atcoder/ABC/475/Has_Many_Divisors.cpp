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

const vi primes = {2, 3, 5, 7, 11, 13, 17, 19,
                   23, 29, 31, 37, 41, 43, 47, 53};
ll n, res, ans;

void dfs(int pos, int last, ll val, ll divs, int skip) {
    if (divs > ans) {
        ans = divs;
        res = val;
    }
    if (pos == sz(primes)) return;
    if (pos == skip) {
        dfs(pos + 1, last, val, divs, skip);
        return;
    }

    ll p = primes[pos];
    rep(e, 1, last + 1) {
        if (val > n / p) break;
        val *= p;
        dfs(pos + 1, e, val, divs * (e + 1), skip);
    }
}

void solve() {
    ll d;
    cin >> n >> d;

    res = 1;
    ans = 1;
    dfs(0, 60, 1, 1, -1);
    if (res % d != 0) {
        cout << res << '\n';
        return;
    }

    res = 1;
    ans = 1;
    ll rem = d;
    rep(i, 0, sz(primes)) {
        ll p = primes[i];
        int exp = 0;
        while (rem % p == 0) {
            rem /= p;
            exp++;
        }

        ll pow = 1;
        rep(e, 0, exp) {
            dfs(0, 60, pow, e + 1, i);
            if (e + 1 < exp) pow *= p;
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
