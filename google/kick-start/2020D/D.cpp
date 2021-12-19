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

int rb[1<<16];
void gen_rb() {
  for (int i = 0; i < (1 << 16); ++i) {
    fornd(j, 16) {
      if ((i >> j) & 1) {
        rb[i] = j;
        break;
      }
    }
  }
}

int get_rb(int n) {
  if ((n >> 16) > 0) {
    return rb[n >> 16] + 16;
  }
  return rb[n];
}

class SparseTable {
public:
  int a[NMAX][20];
  int n;

  void build(int *b, int n) {
    this->n = n;
    forn(i, n) {
      a[i][0] = b[i];
    }
    for (int j = 1; j < 20; ++j) {
      for (int i = 0; i < n; ++i) {
        int k = i + (1 << (j - 1));
        if (k >= n) {
          k = -1;
        } else {
          k = a[i + (1 << (j - 1))][j - 1];
        }
        a[i][j] = max(a[i][j - 1], k);
      }
    }
  }

  int get_max(int l, int r) {
    if (l > r) {
      return -1;
    }
    l--, r--;
    int len = r - l + 1;
    int t = get_rb(len);
    // dbg("l r t %d %d %d\n", l, r, t);
    return max(a[l][t], a[r - (1 << t) + 1][t]);
  }
};

class Tree {
public:
  int a[4*NMAX];
  int len;

  void build(int *b, int n) {
    len = 1;
    while (len < n) {
      len <<= 1;
    }

    for (int i = 0; i < len; ++i) {
      if (i < n) {
        a[len + i] = b[i];
      } else {
        a[len + i] = -1;
      }
    }

    for (int i = len - 1; i > 0; --i) {
      a[i] = max(a[i*2], a[i*2 + 1]);
    }
  }

  int get_max(int v, int i, int j, int l, int r) {
    if (i <= l && r <= j) {
      return a[v];
    }
    if (i > r || l > j) {
      return -1;
    }
    int m = (l + r) >> 1;
    return max(get_max(v*2, i, j, l, m), get_max(v*2 + 1, i, j, m + 1, r));
  }

  int get_max(int l, int r) {
    if (l > r) {
      return -1;
    }
    return get_max(1, l, r, 1, len);
  }
};

// void gen() {
//   n = rand() % 10;
//   q = 10;
//   forn(i, n - 1) {
//     bool ok = true;
//     do {
//       d[i] = rand() % 50;
//       forn(j, i) {
//         if (d[j] == d[i]) {
//           ok = false;
//         }
//       }
//     } while (!ok);
//   }
// }

int n, q;
int d[NMAX];
SparseTable tree;

void read() {
  scanf("%d %d", &n, &q);
  forn(i, n - 1) {
    scanf("%d", &d[i]);
  }
}

int check(int m, int s) {
  int max_left = tree.get_max(m, s - 1);

  int L = s, R = n + 1;
  while (R - L > 1) {
    int mid = (R + L) >> 1;
    if (tree.get_max(s, mid - 1) < max_left) {
      L = mid;
    } else {
      R = mid;
    }
  }

  return s - m + L - s;
}

int check_right(int s, int m) {
  int max_right = tree.get_max(s, m - 1);

  int L = 0, R = s;
  while (R - L > 1) {
    int mid = (R + L) >> 1;
    if (tree.get_max(mid, s - 1) < max_right) {
      R = mid;
    } else {
      L = mid;
    }
  }

  return m - s + s - R;
}

void solve(int s, int k) {
  if (k == 1) {
    printf(" %d", s);
    return;
  }

  int L = 0, R = s;
  while (R - L > 1) {
    int m = (L + R) >> 1;
    if (check(m, s) + 1 <= k) {
      R = m;
    } else {
      L = m;
    }
  }
  // dbgx(R);
  if (check(R, s) + 1 == k) {
    // dbg("\n------------\nL works %d\n\n\n", R);
    printf(" %d", R);
    return;
  }

  L = s, R = n + 1;
  while (R - L > 1) {
    int m = (L + R) >> 1;
    if (check_right(s, m) + 1 <= k) {
      L = m;
    } else {
      R = m;
    }
  }

  if (check_right(s, L) + 1 == k) {
    // dbg("\n------------\nR works %d\n\n\n", L);
    printf(" %d", L);
    return;
  }

  assert(false && "something wrong");
}

void solve() {
  tree.build(d, n);
  forn(i, q) {
    int s, k;
    scanf("%d %d", &s, &k);
    solve(s, k);
  }
  printf("\n");
}

void test() {
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  tree.build(a, 10);
  dbg("\n");
  assert(tree.get_max(1, 10) == 10);
  assert(tree.get_max(6, 7) == 7);
  assert(tree.get_max(2, 8) == 8);
}

int main() {
  gen_rb();

  // test(); return 0;

	prepare("");
  
  int t;
  scanf("%d", &t);

  forn(i, t) {
    printf("Case #%d:", i + 1);
    read();
    solve();
  }

  return 0;
}
