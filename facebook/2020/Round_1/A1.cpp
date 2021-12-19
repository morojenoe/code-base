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

const int NMAX = 1000005;
const int KMAX = NMAX;
const int MOD = INF + 7;

int N, K;
lint W;
lint L[NMAX], H[NMAX];
lint AL, BL, CL, DL;
lint AH, BH, CH, DH;
lint P[NMAX];

struct evt {
  int id, type;
  lint x;

  evt(int id, int type, lint x): id(id), type(type), x(x) { }
};

bool operator<(const evt &a, const evt &b) {
  if (a.x == b.x) {
    return a.type > b.type;
  }
  return a.x < b.x;
}

vector<evt> e;

void print(lint *a, char arr_name) {
#ifdef MY_DEBUG
  dbg("----------------\n");
  dbg("%c:", arr_name);
  forn(i, N) {
    dbg(" %lld", a[i]);
  }
  dbg("\n");
#endif
}

void print(set<pii> &s) {
#ifdef MY_DEBUG
  dbg("----------------\n");
  dbg("set:");
  for (auto a : s) {
    dbg(" (%d, %d)", a.first, a.second);
  }
  dbg("\n");
#endif
}


void read() {
  scanf("%d %d %lld", &N, &K, &W);
  forn(i, K) {
    scanf("%lld", &L[i]);
  }
  scanf("%lld %lld %lld %lld", &AL, &BL, &CL, &DL);
  forab(i, K, N - 1) {
    L[i] = ((AL*L[i - 2]) % DL + (BL*L[i - 1]) % DL + CL) % DL + 1;
  }

  forn(i, K) {
    scanf("%lld", &H[i]);
  }
  scanf("%lld %lld %lld %lld", &AH, &BH, &CH, &DH);
  forab(i, K, N - 1) {
    H[i] = ((AH*H[i - 2]) % DH + (BH*H[i - 1]) % DH + CH) % DH + 1;
  }
  // print(L, 'L');
  // print(H, 'H');
}

inline lint calc_p(lint last_ans, lint last_W, lint last_H) {
  return (last_ans + (2LL*last_W % MOD) + (2LL*last_H) % MOD) % MOD;
}

void solve() {
  forn(i, N - 1) {
    assert(L[i] < L[i + 1]);
  }
  e.clear();
  forn(i, N) {
    e.pb(evt(i, 1, L[i]));
    e.pb(evt(i, -1, L[i] + W));
  }
  sort(all(e));

  set<pii> s;

  forn(j, sz(e)) {
    int id = e[j].id;
    if (e[j].type == 1) {
      if (s.empty()) {
        P[id] = (id > 0 ? P[id - 1] : 0) + 2LL*W + 2LL*H[id];
        P[id] %= MOD;
      } else {
        int max_h = (*s.rbegin()).first;
        // dbgx(id);
        // print(s);
        // dbgx(max_h);
        // dbgx(L[id] - L[id - 1]);
        P[id] = P[id - 1] + 2LL*(L[id] - L[id - 1]);
        
        if (max_h < H[id]) {
          // dbgx(H[id] - max_h);
          P[id] += 2*(H[id] - max_h);
        }
        P[id] %= MOD;
      }

      s.insert(mp(H[id], id));
    } else {
      s.erase(mp(H[id], id));
    }
  }

  // print(P, 'P');
  lint ans = 1;
  forn(i, N) {
    ans = (ans * P[i]) % MOD;
  }
  printf("%lld\n", ans);
}

int main() {
	prepare("");

  int T;
  scanf("%d", &T);
  forn(i, T) {
    printf("Case #%d: ", i + 1);
    read();
    solve();
  }

  return 0;
}
