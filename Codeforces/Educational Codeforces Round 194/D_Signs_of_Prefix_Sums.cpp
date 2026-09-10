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

bool check(const string &s, int cost) {
    array<bool, 7> dp{};
    dp[3] = true;

    for (char c : s) {
        array<bool, 7> next{};

        for (int prev = -3; prev <= 3; ++prev) {
            if (!dp[prev + 3]) continue;

            for (int cur = -3; cur <= 3; ++cur) {
                if (c == '+' && cur <= 0) continue;
                if (c == '-' && cur >= 0) continue;
                if (c == '0' && cur != 0) continue;

                int d = abs(cur - prev);
                if (d >= 1 && d <= cost) {
                    next[cur + 3] = true;
                }
            }
        }

        dp = next;
    }

    for (bool flag : dp) {
        if (flag) return true;
    }
    return false;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;

    if (s[0] == '0' || s.find("00") != string::npos) {
        cout << -1 << '\n';
    } else if (check(s, 1)) {
        cout << 1 << '\n';
    } else if (check(s, 2)) {
        cout << 2 << '\n';
    } else {
        cout << 3 << '\n';
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
