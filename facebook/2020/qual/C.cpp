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
    freopen ("output.txt", "w", stdout);
#else
    if (s.length() != 0)
    {
        freopen ((s + ".in").c_str(), "r", stdin);
        freopen ((s + ".out").c_str(), "w", stdout);
    }
#endif
}

const int NMAX = 800005;

struct seg {
  lint L, R, id;
  seg(lint a, lint b, lint c): L(a), R(b), id(c) { }
};

int n;
int a[NMAX][2];
vector<seg> s;
map<lint, pair<lint, int>> d;
lint ans;

bool cmp(const seg &a, const seg &b) {
  return a.L < b.L;
}

void read() {
  scanf("%d", &n);
  forn(i, n) {
    scanf("%d %d", &a[i][0], &a[i][1]);
  }
}

void upd(lint p, pair<lint, int> val) {
  ans = max(ans, val.first);
  if (d[p] == val) {
    return;
  }
  if (val.first > d[p].first) {
    d[p] = val;
  }
  if (val.first == d[p].first) {
    if (d[p].second != val.second) {
      d[p].second = -1;
    }
  }
}

void solve() {
  ans = 0;
  s.clear();
  d.clear();
  forn(i, n) {
    s.pb(seg(a[i][0] - a[i][1], a[i][0], i));
    s.pb(seg(a[i][0], a[i][0] + a[i][1], i));
  }

  sort(all(s), cmp);

  forn(i, sz(s)) {
    seg cur = s[i];
    upd(cur.R, mp(cur.R - cur.L, cur.id));
    if (d[cur.L].second != cur.id) {
      upd(cur.R, mp(d[cur.L].first + cur.R - cur.L, cur.id));
    }
  }
  printf("%lld\n", ans);
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
