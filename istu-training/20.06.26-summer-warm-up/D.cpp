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

class Fenwik {
public:
  int t[1 << 20];
  int n;

  void init (int nn)
  {
    n = nn;
    _(t, 0);
    forn(i, n) {
      inc(i, 1);
    }
  }

  int sum2 (int r)
  {
    int result = 0;
    for (; r >= 0; r = (r & (r+1)) - 1)
      result += t[r];
    return result;
  }

  void inc (int i, int delta)
  {
    for (; i < n; i = (i | (i+1)))
      t[i] += delta;
  }

  int sum(int r)
  {
    return sum2(n - 1) - sum2(r);
  }
} fenwik;

const int NMAX = 45;

struct R {
  lint h, g;
  int id;
  R(lint a, lint b, int id): h(a), g(b), id(id) { }
};

int n;
lint k;
lint h[NMAX], g[NMAX];
int m[1 << 20];

vector<R> a, b, c;

void debug(const vector<R> &a) {
  dbg("--------\n");
  for (auto it : a) {
    dbg(" (%lld, %lld, %d)", it.h, it.g, it.id);
  }
  dbg("\n--------\n");
}

int bit(int n, int k) {
  return (n >> k) & 1;
}

void read() {
  scanf("%d %lld", &n, &k);
  forn(i, n) {
    scanf("%lld %lld", &h[i], &g[i]);
  }
}

void solve() {
  a.reserve(1 << 20);
  b.reserve(1 << 20);

  int n1, n2;
  n1 = n >> 1;
  n2 = n - n1;
  forn(msk, 1 << n1) {
    lint last_h = 0;
    lint gold = 0;
    bool good = true;

    forn(i, n1) {
      if (bit(msk, i)) {
        good = good && last_h <= h[i];
        gold += g[i];
        last_h = h[i];
      }
    }
    if (good) {
      a.pb(R(last_h, gold, -1));
    }
  }

  

  forn(msk, 1 << n2) {
    lint first_h = 0;
    lint last_h = 0;
    lint gold = 0;
    bool good = true;

    forn(i, n2) {
      if (bit(msk, i)) {
        int id = n1 + i;
        good = good && last_h <= h[id];
        gold += g[id];
        last_h = h[id];
        if (first_h == 0) {
          first_h = h[id];
        }
      }
    }
    if (good) {
      b.pb(R(first_h, gold, msk));
    }
  }

  fenwik.init(b.size());
  sort(all(a), [&](const R &a, const R &b) {
    return a.h < b.h;
  });
  sort(all(b), [&](const R &a, const R &b) {
    return a.h < b.h;
  });
  c = b;
  sort(all(c), [&](const R &a, const R &b) {
    return a.g < b.g;
  });
  for (int i = 0; i < (int)c.size(); ++i) {
    m[c[i].id] = i;
  }

  debug(a);
  debug(b);
  debug(c);
  dbg("m: ");
  forn(i, sz(c)) {
    dbg(" %d", m[i]);
  }
  dbg("\n");

  lint ans = 0;
  int id = 1;
  forn(i, sz(a)) {
    while (id < sz(b) && b[id].h < a[i].h) {
      dbg("decrement %d, a[i].h = %lld\n", b[id].id, a[i].h);
      fenwik.inc(m[b[id].id], -1);
      id++;
    }

    int lft;
    lft = lower_bound(all(c), R(-1, k - a[i].g, -1), [&](const R &a, const R &b) {
      return a.g < b.g;
    }) - c.begin();
    dbgx(lft);
    dbgx(fenwik.sum(lft - 1));
    ans += fenwik.sum(lft - 1);
  }

  printf("%lld\n", ans);
}

int main() {
	prepare("");

  read();
  solve();

  return 0;
}
