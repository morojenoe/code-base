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

const int NMAX = 105;
const int SMAX = 1000005;

struct TTicket {
  int i, j, c;
};

int n, k, S;
lint P;
ld w[NMAX][3];
ld d[NMAX][NMAX][NMAX];
ld dp[SMAX];
ld ticket[NMAX];
TTicket t[NMAX];

void read() {
  scanf("%d %d %d %lld", &n, &k, &S, &P);
  forn(i, n) {
    forn(j, 3) {
      double temp;
      scanf("%lf", &temp);
      w[i][j] = temp;
    }
    sort(w[i], w[i] + 3, greater<ld>());
  }
  forn(i, k) {
    scanf("%d %d %d", &t[i].i, &t[i].j, &t[i].c);
  }
}

void upd(int i, int j, int k, ld val) {
  if (d[i][j][k] < val) {
    d[i][j][k] = val;
  }
}

void solve() {
  forn(i, NMAX) forn(j, NMAX) forn(k, NMAX) d[i][j][k] = 0.0;
  d[0][0][0] = P;
  forn(i, n) {
    forn(j, n) {
      forn(k, n) {
        ld t = d[i][j][k];
        upd(i + 1, j, k, t*w[i][0]);
        upd(i + 1, j + 1, k, t*(w[i][0] + w[i][1]));
        upd(i + 1, j, k + 1, t);
      }
    }
  }
  forn(i, k) {
    ticket[i] = d[n][t[i].i][t[i].j];
    dbgx(ticket[i]);
  }

  dp[0] = 0.0;
  forn(i, S + 1) {
    forn(j, k) {
      if (i >= t[j].c) {
        dp[i] = max(dp[i], dp[i - t[j].c] + ticket[j]);
      }
    }
  }
  printf("%.15f\n", (double)dp[S]);
}

int main() {
#ifdef MY_DEBUG
  freopen("input.txt", "r", stdin);
#endif
    read();
    solve();

    return 0;
}
