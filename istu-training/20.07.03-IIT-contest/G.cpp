#pragma comment(linker, "/STACK:128777216")

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
 
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <deque>
#include <stack>
 
#include <math.h>
#include <cmath>
#include <string>
#include <cstring>
#include <string.h>
 
#include <memory.h>
#include <cassert>
#include <time.h>
 
using namespace std;
 
#define forn(i,n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define forab(i,a,b) for (int i = (int)(a); i <= (int)(b); i++)
#define forabd(i, b, a) for (int i = (int)(b); i >= (int)(a); i--)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
 
#define _(a, val) memset (a, val, sizeof (a))
#define sz(a) (int)((a).size())
#define pb push_back
#define mp make_pair
#define all(v) (v).begin(), (v).end()
 
typedef long long lint;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vii;
 
const lint LINF = 1000000000000000000LL;
const int INF = 1000000000;
const long double eps = 1e-9;
const long double PI = 3.1415926535897932384626433832795l;
 
#ifdef MY_DEBUG
#define dbgx( x ) { cerr << #x << " = " << x << endl; }
#define dbg( ... ) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
#else
#define dbgx( x ) {  } 
#define dbg( ... ) {  } 
#endif
 
void prepare(string s)
{
#ifdef MY_DEBUG
    freopen ("input.txt", "r", stdin);
    // freopen ("output.txt", "w", stdout);
#else
    if (s.length() != 0)
    {
        freopen ((s + ".in").c_str(), "r", stdin);
        freopen ((s + ".out").c_str(), "w", stdout);
    }
#endif
}

class dsu {
public:
  struct data {
    int cnt, p;
  };
  vector<data> d;

  void init(int n) {
    d.resize(n);
    for (int i = 0; i < n; ++i) {
      d[i].p = i;
      d[i].cnt = 1;
    }
  }

  int get(int v) {
    return d[v].p == v ? v : (d[v].p = get(d[v].p));
  }

  int count(int v) {
    return d[get(v)].cnt;
  }

  bool merge(int v, int u) {
    v = get(v);
    u = get(u);
    if (v == u) return false;
    if (d[v].cnt < d[u].cnt) {
      swap(v, u);
    }
    d[u].p = v;
    d[v].cnt += d[u].cnt;
    return true;
  }
};


const int NMAX = 200005;

int n;

struct edge {
  int v, u, w, id;
  edge(int a, int b, int w, int id): v(a), u(b), w(w), id(id) { }
};

bool operator<(const edge &a, const edge &b) {
  return a.w < b.w;
}

vector<edge> e;
dsu d;
int info[NMAX];

void read() {
  scanf("%d", &n);
  forn(i, n - 1) {
    int a, b, w;
    scanf("%d %d %d", &a, &b, &w);
    e.pb(edge(a - 1, b - 1, w, i));
  }
}

int h[NMAX];
vector<edge> g[NMAX];
int used[NMAX];

void dfs_calc_h(int v) {
  dbg("calc_h v = %d\n", v);
  used[v] = 1;
  h[v] = d.count(v);
  dbgx(h[v]);
  for (auto e : g[v]) {
    int u = e.v == v ? e.u : e.v;
    if (!used[u]) {
      dfs_calc_h(u);
      h[v] += h[u];
    }
  }
  dbgx(h[v]);
}

void dfs(int v, int all) {
  dbg("dfs %d %d\n", v, all);
  used[v] = 1;
  for (auto e: g[v]) {
    int u = e.v == v ? e.u : e.v;
    if (!used[u]) {
      info[e.id] = 2*h[u] * (all - h[u]);
      dfs(u, all);
    }
    
  }
}

void debug_dsu() {
#ifdef MY_DEBUG
  dbg("dsu: ");
  forn(i, n) {
    dbg("%d %d\n", i, d.count(i));
  }
  dbg("--------------\n");
#endif
}

void debug_h() {
#ifdef MY_DEBUG
  dbg("----------------\n");
  dbg("h:");
  forn(i, n) {
    dbg(" %d", h[i]);
  }
  dbg("\n----------------\n");
#endif
}

void calc(const vector<edge> &e) {
  for (auto edge : e) {
    h[edge.v] = h[edge.u] = 0;
    g[edge.v].clear();
    g[edge.u].clear();
    used[edge.v] = used[edge.u] = 0;
  }
  for (auto edge : e) {
    g[edge.v].pb(edge);
    g[edge.u].pb(edge);
  }
  
  for (auto edge: e) {
    if (!used[edge.v]) {
      dfs_calc_h(edge.v);
    }
    debug_h();
  }

  for (auto edge : e) {
    used[edge.v] = used[edge.u] = 0;
  }

  for (auto edge : e) {
    if (!used[edge.v]) {
      dfs(edge.v, h[edge.v]);
    }
  }

  for (auto edge : e) {
    d.merge(edge.u, edge.v);
  }
  debug_dsu();
}

void debug_info() {
#ifdef MY_DEBUG
  dbg("----------------\n");
  dbg("info:");
  forn(i, n) {
    dbg("%d ", info[i]);
  }
  dbg("\n----------------\n");
#endif
}

void solve() {
  sort(all(e));
  d.init(n);
  _(info, 0);
  for (int i = 0; i < sz(e); ) {
    int cur_w = e[i].w;
    vector<edge> e2;
    while (i < sz(e) && cur_w == e[i].w) {
      e2.pb(e[i++]);
    }
    dbgx(sz(e2));
    calc(e2);
    debug_info();
  }

  int mx = *max_element(info, info + n);
  vector<int> ans;
  forn(i, n) {
    if (info[i] == mx) {
      ans.pb(i + 1);
    }
  }
  printf("%d %d\n", mx, sz(ans));
  forn(i, sz(ans)) {
    printf("%d%c", ans[i], i + 1 == sz(ans) ? '\n' : ' ');
  }
}

int main() {
	prepare("");
    read();
    solve();

    return 0;
}
