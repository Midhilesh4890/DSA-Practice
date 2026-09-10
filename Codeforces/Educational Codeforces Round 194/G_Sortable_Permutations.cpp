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

    const int MOD = MOD1;
    vector<int> spf(n + 1), mu(n + 1), primes;
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            mu[i] = -1;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (1LL * i * p > n) break;
            spf[i * p] = p;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }

    auto pow = [&](int a, int e) {
        int res = 1;
        while (e) {
            if (e & 1) res = 1LL * res * a % MOD;
            a = 1LL * a * a % MOD;
            e >>= 1;
        }
        return res;
    };

    vector<int> fact(n + 1), invfact(n + 1);
    vector<int> pow2(n + 1), pow3(n + 1);
    fact[0] = pow2[0] = pow3[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
        pow2[i] = 2LL * pow2[i - 1] % MOD;
        pow3[i] = 3LL * pow3[i - 1] % MOD;
    }
    invfact[n] = pow(fact[n], MOD - 2);
    for (int i = n; i >= 1; --i)
        invfact[i - 1] = 1LL * invfact[i] * i % MOD;

    auto perms = [&](int r) -> ll {
        return 1LL * fact[n] * invfact[n - r] % MOD;
    };

    auto inverse = [&](int a, int b) {
        ll x = 1, y = 0;
        int m = b;
        while (b) {
            int q = a / b;
            int next = a % b;
            a = b;
            b = next;
            ll coef = x - q * y;
            x = y;
            y = coef;
        }
        return (x % m + m) % m;
    };

    vector<int> edges(n + 1);
    for (int a = 3; a <= n / 3; a += 2) {
        for (int b = 3; b <= n / a; b += 2) {
            int d = a * b;
            if (!mu[d]) continue;
            ll first = 1LL * a * (b - inverse(a, b));
            edges[d] += (n - 1 - first) / d + 1;
        }
    }

    ll res = perms(n / 2);
    for (int d = 3; d <= n; d += 2) {
        if (!mu[d]) continue;
        int r = n / d;
        int cmn = n / (2 * d);
        int b = (n % d == 0 && (r & 1));
        ll f = perms(r) * pow2[edges[d]] % MOD;
        ll g = perms(cmn) * pow2[edges[d] + b] % MOD;
        g = g * pow3[r - cmn - b] % MOD;
        res = (res - mu[d] * (f - g)) % MOD;
    }
    if (res < 0) res += MOD;
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
