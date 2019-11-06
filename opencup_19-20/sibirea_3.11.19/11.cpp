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

const int NMAX = 300005;  

int n;
vector<int> g[NMAX];
map<int, map<int, int>> e;
lint d[NMAX];
lint ans[NMAX];

void dfs(int v, int p) {
  d[v] = 0;
  forn(i, sz(g[v])) {
    int u = g[v][i];
    if (u == p) continue;
    dfs(u, v);
    if (d[u] > 0) {
      d[v] += min(d[u], (lint)e[u][v]);
    } else {
      d[v] += e[u][v];
    }
  }
}

void dfs2(int v, int p, lint up) {
  dbg("v = %d p = %d up = %lld ans = %lld\n", v, p, up, d[v] + up);
  ans[v] = d[v] + up;
  forn(i, sz(g[v])) {
    int u = g[v][i];
    if (u == p) continue;
    lint new_up = d[v] + up;
    if (d[u] > 0) {
      new_up -= min(d[u], (lint)e[u][v]);
    } else {
      new_up -= e[u][v];
    }
    if (new_up == 0) {
      new_up = e[v][u];
    }
    new_up = min(new_up, (lint)e[v][u]);
    dfs2(u, v, new_up);
  }
}

void read() {
  scanf("%d", &n);
  forn(i, n - 1) {
    int a, b, ab, ba;
    scanf("%d %d %d %d", &a, &b, &ab, &ba);
    a--; b--;
    g[a].pb(b);
    g[b].pb(a);
    e[a][b] = ab;
    e[b][a] = ba;
  }
}

void solve() {
  dfs(0, -1);
  forn(i, n) {
    dbgx(d[i]);
  }
  dfs2(0, -1, 0);
  forn(i, n) {
    printf("%lld\n", ans[i]);
  }
}

int main() {
#ifdef MY_DEBUG
  freopen("input.txt", "r", stdin);
#endif
    read();
    solve();

    return 0;
}
