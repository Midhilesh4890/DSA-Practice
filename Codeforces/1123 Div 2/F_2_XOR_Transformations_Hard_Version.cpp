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

struct Trie {
    struct Node {
        int child[2] = {0, 0};
        int cnt = 0;
    };

    vector<Node> tree;
    int bits;

    Trie(int n, int mx) {
        bits = 1;
        while ((1LL << bits) <= mx) bits++;
        tree.reserve(1 + n * bits);
        tree.eb();
    }

    void insert(int x) {
        int node = 0;
        rrep(bit, bits - 1, 0) {
            int digit = (x >> bit) & 1;
            if (tree[node].child[digit] == 0) {
                tree[node].child[digit] = sz(tree);
                tree.eb();
            }
            node = tree[node].child[digit];
            tree[node].cnt++;
        }
    }

    int kth(int x, int k) const {
        int node = 0, res = 0;
        rrep(bit, bits - 1, 0) {
            int digit = (x >> bit) & 1;
            int next = tree[node].child[digit];
            int cnt = 0;
            if (next != 0) cnt = tree[next].cnt;

            if (k <= cnt) {
                node = next;
            } else {
                k -= cnt;
                res |= (1 << bit);
                node = tree[node].child[digit ^ 1];
            }
        }
        return res;
    }
};

vi transformArray(const vi& a) {
    int n = sz(a);
    ll zeros = 0;
    int l = 0;
    while (l < n) {
        int r = l + 1;
        while (r < n && a[r] == a[l]) r++;
        ll cnt = r - l;
        zeros += cnt * (cnt - 1) / 2;
        l = r;
    }
    if (zeros >= n) return vi(n, 0);

    Trie trie(n, a.back());
    rep(i, 0, n) trie.insert(a[i]);

    using Entry = array<int, 3>;
    vector<Entry> entries;
    entries.reserve(n);
    rep(i, 0, n) {
        entries.pb({trie.kth(a[i], 2), i, 2});
    }

    priority_queue<Entry, vector<Entry>, greater<Entry>> heap(
        greater<Entry>(), move(entries));

    vi res;
    res.reserve(n);
    rep(step, 0, 2 * n) {
        Entry cur = heap.top();
        heap.pop();

        int value = cur[0], id = cur[1], rank = cur[2];
        if (step % 2 == 1) res.pb(value);

        if (rank < n && step + 1 < 2 * n) {
            rank++;
            heap.push({trie.kth(a[id], rank), id, rank});
        }
    }
    return res;
}

void solve() {
    int n, q;
    cin >> n >> q;

    vi a(n), queries(q);
    rep(i, 0, n) cin >> a[i];
    int limit = 0;
    rep(i, 0, q) {
        cin >> queries[i];
        limit = max(limit, queries[i]);
    }
    sort(all(a));

    vi res;
    res.pb(a.back() - a.front());
    while (sz(res) <= limit && a.back() != 0) {
        a = transformArray(a);
        res.pb(a.back() - a.front());
    }

    rep(i, 0, q) {
        int x = queries[i];
        if (x < sz(res)) {
            cout << res[x] << '\n';
        } else {
            cout << 0 << '\n';
        }
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
