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

const int MAXH = 15;
const int MAXW = 200005;
const int MAXQ = 200005;
const int MAXK = 200005;
const int MAXL = 20;

int H, W, K, Q;
char f[MAXH][MAXW];
struct Query {
  int D, L, R, id, ans;
};
Query q[MAXQ];
int nxt[MAXW];
int go[MAXW][MAXL];

void read() {
  scanf("%d %d %d %d\n", &H, &W, &K, &Q);
  forn(i, H) {
    scanf("%s\n", f[i]);
  }
  forn(i, Q) {
    scanf("%d %d %d", &q[i].D, &q[i].L, &q[i].R);
    q[i].L--; q[i].R--; q[i].D--;
    q[i].id = i;
    q[i].ans = 0;
  }
}

vector<int> pos;
int calc_nxt(int row, int i) {
  auto it = lower_bound(all(pos), i);
  if (it == pos.end()) return -1;
  return *it;
  // if (i % 10000 == 0) {
  //   dbgx(i);
  // }
  // if (i >= W) {
  //   return -1;
  // }
  // if (nxt[i] != -1) {
  //   return nxt[i];
  // }
  // if (f[row][i] == 'X') {
  //   return nxt[i] = i;
  // } else {
  //   return nxt[i] = calc_nxt(row, i + 1);
  // }
}

int get(int L, int R) {
  int p = nxt[L];
  if (p == -1 || p > R) {
    return 0;
  }
  int i = 0;
  int res = 0;
  for (; i < MAXL && go[p][i] != -1 && go[p][i] <= R; ++i) {
    res += 1 << i;
    p = go[p][i];
  }
  for (; i >= 0; --i) {
    if (go[p][i] != -1 && go[p][i] <= R) {
      res += 1 << i;
      p = go[p][i];
    }
  }
  res++;
  
  return res;
}

void print_go(int row) {
  forn(i, W) {
    if (f[row][i] == 'X') {
      forn(j, MAXL) {
        dbg("%d ", go[i][j]);
      }
      dbg("\n");
    }
  }
}

void solve() {
  forn(row, H) {
    dbg("========================\n");
    dbgx(row);
    forn(i, W) {
      nxt[i] = -1;
    }
    dbgx("OK");
    pos.clear();
    forn(i, W) {
      if (f[row][i] == 'X') {
        pos.pb(i);
        dbgx(i);
      }
    }
    forn(i, W) {
      nxt[i] = calc_nxt(row, i);
      dbgx(nxt[i]);
    }
    
    forn(i, W) {
      forn(j, MAXL) {
        go[i][j] = -1;
      }
    }
    forn(i, W) {
      if (f[row][i] == 'X') {
        go[i][0] = calc_nxt(row, i + K);
      }
    }
    // print_go(row);
    for (int j = 1; j < MAXL; ++j) {
      forn(i, W) {
        if (f[row][i] != 'X') continue;
        int prv = go[i][j - 1];
        if (prv == -1) {
          go[i][j] = -1;
        } else {
          go[i][j] = go[prv][j - 1];
        }
      }
    }
    forn(i, Q) {
      if (row <= q[i].D) {
        q[i].ans += get(q[i].L, q[i].R);
      }
    }
  }

  // int acc = 0;
  // forn(i, Q) {
  //   acc += q[i].ans;
  // }
  // printf("%d\n", acc);
  forn(i, Q) {
    printf("%d\n", q[i].ans);
  }
}

void gen() {
  H = 12;
  W = 100000;
  K = 1;
  Q = 100000;
  forn(i, H) {
    forn(j, W) {
      f[i][j] = rand() & 1? '.' : '.';
    }
  }
  forn(i, Q) {
    // scanf("%d %d %d", &q[i].D, &q[i].L, &q[i].R);
    q[i].D = H;
    q[i].L = 1;
    q[i].R = W;
    q[i].L--; q[i].R--; q[i].D--;
    q[i].id = i;
    q[i].ans = 0;
  }
}

int main() {
#ifdef MY_DEBUG
  freopen("input.txt", "r", stdin);
#endif
  read();
  // gen();
  solve();

  dbgx(clock() / CLOCKS_PER_SEC);
  return 0;
}
