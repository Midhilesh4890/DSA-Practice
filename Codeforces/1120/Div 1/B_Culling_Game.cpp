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

struct State {
    ll limit, s;
    int cnt;
};

struct Node {
    ll sum = 0;
    vector<State> st;
};

class SegmentTree {
    int n;
    vector<Node> tree;

    void pull(int v) {
        const Node &l = tree[v * 2];
        const Node &r = tree[v * 2 + 1];
        Node &cur = tree[v];
        cur.sum = l.sum + r.sum;
        cur.st.clear();

        int j = 0;
        for (const State &state : l.st) {
            while (j < sz(r.st) && r.st[j].limit <= state.s) ++j;
            if (j == sz(r.st)) {
                cur.st.pb({state.limit, state.s + r.sum, state.cnt});
            } else {
                cur.st.pb({state.limit, r.st[j].s,
                               state.cnt + r.st[j].cnt});
            }
        }

        ll need = l.st.empty() ? 0 : l.st.back().limit;
        for (const State &state : r.st) {
            ll limit = state.limit - l.sum;
            if (limit > need) cur.st.pb({limit, state.s, state.cnt});
        }
    }

    void build(int v, int l, int r, const vll &a) {
        if (l == r) {
            tree[v].sum = a[l];
            tree[v].st.pb({a[l], a[l], 1});
            return;
        }
        int mid = (l + r) / 2;
        build(v * 2, l, mid, a);
        build(v * 2 + 1, mid + 1, r, a);
        pull(v);
    }

    void remove(int v, int l, int r, int pos) {
        if (l == r) {
            tree[v].sum = 0;
            tree[v].st.clear();
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) remove(v * 2, l, mid, pos);
        else remove(v * 2 + 1, mid + 1, r, pos);
        pull(v);
    }

public:
    explicit SegmentTree(const vll &a) : n(sz(a)), tree(4 * n) {
        build(1, 0, n - 1, a);
    }

    void remove(int pos) {
        remove(1, 0, n - 1, pos);
    }

    int res() const {
        return tree[1].st.front().cnt - 1;
    }
};

void solve() {
    int n;
    cin >> n;
    vll a(n);
    for (ll &x : a) cin >> x;
    vi p(n);
    for (int &x : p) {
        cin >> x;
        x--;
    }

    SegmentTree seg(a);
    rep(i, 0, n) {
        cout << seg.res() << (i + 1 == n ? '\n' : ' ');
        if (i + 1 < n) seg.remove(p[i]);
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
