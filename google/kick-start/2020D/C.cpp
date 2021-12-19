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

const int NMAX = 500005;

int n, a, b;
vector<int> g[NMAX];
lint A[NMAX], B[NMAX];
vector<int> depth;

void read() {
  scanf("%d %d %d", &n, &a, &b);
  forn(i, n) {
    g[i].clear();
  }
  forn(i, n - 1) {
    int p;
    scanf("%d", &p);
    g[p - 1].pb(i + 1);
  }
}

void dfs(int v) {
  depth.pb(v);
  for (auto u: g[v]) {
    dfs(u);
  }
  depth.pop_back();
  A[v]++;
  B[v]++;
  if (sz(depth) >= a) {
    int id = sz(depth) - a;
    A[depth[id]] += A[v];
  }
  if (sz(depth) >= b) {
    int id = sz(depth) - b;
    B[depth[id]] += B[v];
  }
  
}

void solve() {
  forn(i, n) {
    A[i] = B[i] = 0;
  }
  depth.clear();
  dfs(0);
// #ifdef MY_DEBUG
//   dbg("-----------------\n");
//   dbg("A:");
//   forn(i, n) {
//     dbg(" %lld", A[i]);
//   }
//   dbg("\nB:");
//   forn(i, n) {
//     dbg(" %lld", B[i]);
//   }
//   dbg("\n-----------------\n");
// #endif

  ld ans = 0;
  forn(i, n) {
    lint cnt = A[i]*B[i] + A[i]*(n - B[i]) + B[i]*(n - A[i]);
    ans += cnt / (ld)n / (ld)n;
  }
  printf("%.15f\n", (double)ans);
}

int main() {
	prepare("");

  int t;
  scanf("%d", &t);

  forn(i, t) {
    printf("Case #%d: ", i + 1);
    read();
    solve();
  }

  return 0;
}
