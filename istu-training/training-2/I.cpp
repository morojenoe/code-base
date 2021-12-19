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

bool operator<(const vec &a, const vec &b) {
  if (a.x == b.x) {
    return a.y < b.y;
  }
  return a.x < b.x;
}

const int NMAX = 3005;

int n;
vec a[NMAX];
set<vec> s;

void read() {
  scanf("%d", &n);
  forn(i, n) {
    scanf("%d %d", &a[i].x, &a[i].y);
  }
}

void solve() {
  forn(i, n) {
    s.insert(a[i]);
  }
  int ans = 0;
  forn(i, n) {
    forab(j, i + 1, n - 1) {
      vec m;
      m.x = a[i].x + a[j].x;
      m.y = a[i].y + a[j].y;
      if (m.x % 2 == 0 && m.y % 2 == 0) {
        m.x /= 2;
        m.y /= 2;
        if (s.find(m) != s.end()) {
          ans++;
        }
      }
    }
  }
  printf("%d\n", ans);
}

int main() {
	prepare("");
    read();
    solve();

    return 0;
}
