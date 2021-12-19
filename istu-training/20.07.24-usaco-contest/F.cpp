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

const int NMAX = 100005;

int n, m;
int mark[NMAX];
char buf[NMAX];
vector<int> g[NMAX];
int tin[NMAX], tout[NMAX], up[NMAX][20], val[NMAX][20];
int Time = 0;

void read() {
  scanf("%d %d\n", &n, &m);
  scanf("%s", buf); 
  forn(i, n) {
    mark[i] = buf[i] == 'H' ? 1 : 2;
  }
  forn(i, n - 1) {
    int a, b;
    scanf("%d %d", &a, &b);
    a--; b--;
    g[a].pb(b);
    g[b].pb(a);
  }
}

void dfs(int v, int p) {
  tin[v] = Time++;

  up[v][0] = p;
  val[v][0] = mark[v];
  for (int i = 1; i < 20; ++i) {
    up[v][i] = up[up[v][i - 1]][i - 1];
    val[v][i] = val[v][i - 1] | val[up[v][i - 1]][i - 1];
  }
  
  for (int u : g[v]) {
    if (u != p) {
      dfs(u, v);
    }
  }
  tout[v] = Time++;
}

bool under(int a, int b) {
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int query(int a, int b, int c) {
  if (a == b) {
    return mark[a] == c ? 1 : 0;
  }
  int res = 0;
  for (int i = 19; i >= 0; --i) {
    int jump = up[a][i];
    if (!under(jump, b)) {
      res |= val[a][i];
      a = jump;
    }
  }
  for (int i = 19; i >= 0; --i) {
    int jump = up[b][i];
    if (!under(jump, a)) {
      res |= val[b][i];
      b = jump;
    }
  }
  // dbg("a, b, res = %d %d %d\n", a, b, res);
  if (!under(a, b)) {
    res |= val[a][1];
  }
  if (!under(b, a)) {
    res |= val[b][1];
  }
  return (c & res) ? 1 : 0;
}

void solve() {
  dfs(0, 0);

  forn(i, m) {
    int a, b, t;
    char c;
    scanf("%d %d %c", &a, &b, &c);
    a--; b--;
    t = c == 'H' ? 1 : 2;
    printf("%d", query(a, b, t));
  }
  printf("\n");
}

int main() {
	prepare("");
    read();
    solve();

    return 0;
}
