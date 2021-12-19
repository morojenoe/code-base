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

struct vec {
  int x, y;
};

const int NMAX = 15;

int n;
vec a[NMAX];
int p[15];

void read() {
  scanf("%d", &n);
  a[0].x = a[0].y = a[n + 1].x = a[n + 1].y = 0;
  forn(i, n) {
    scanf("%d %d", &a[i + 1].x, &a[i + 1].y);
  }
}

bool can(vec a, vec b) {
  return a.x == b.x || a.y == b.y;
}

int sign(int a) {
  if (a < 0) {
    return -1;
  }
  if (a > 0) {
    return 1;
  }
  return 0;
}

pii dir(vec a, vec b) {
  pii r = mp(b.x - a.x, b.y - a.y);
  r.first = sign(r.first);
  r.second = sign(r.second);
  return r;
}

bool check() {
  dbg("pos:");
  forn(i, n + 2) {
    dbg(" %d", p[i]);
  }
  dbg("\n");
  forn(i, n + 1) {
    bool good = can(a[p[i]], a[p[i + 1]]);
    if (i) {
      good = good && dir(a[p[i]], a[p[i + 1]]) != dir(a[p[i - 1]], a[p[i]]);
    }
    if (!good) {
      dbg("bad\n-------------\n");
      return false;
    }
  }
  dbg("good\n-------------\n");
  return true;
}

void solve() {
  p[0] = 0;
  p[n + 1] = 0;
  forn(i, n) {
    p[i + 1] = i + 1;
  }

  int ans = 0;
  do {
    if (check()) {
      ans++;
    }
  } while (next_permutation(p + 1, p + n + 1));
  printf("%d\n", ans);
}

int main() {
	prepare("");
    read();
    solve();

    return 0;
}
