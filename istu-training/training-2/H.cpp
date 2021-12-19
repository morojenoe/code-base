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

const int NMAX = 200005;

int n, m;
char s[NMAX];
char q[NMAX][2];

char nxt[256];

void read() {
  scanf("%d %d", &n, &m);
  scanf(" %s", s);
  forn(i, m) {
    scanf(" %c %c", &q[i][0], &q[i][1]);
  }
}

void make() {
  string t;
  forn(i, n) {
    t += nxt[s[i]];
  }
  dbg("%s\n", t.c_str());
}

void solve() {
  for (char c = 'a'; c <= 'z'; ++c) {
    nxt[c] = c;
  }
  forn(i, m) {
    int c1, c2;
    c1 = q[i][0];
    c2 = q[i][1];

    char t1, t2;
    for (char t = 'a'; t <= 'z'; ++t) {
      if (nxt[t] == c1) {
        t1 = t;
      }
      if (nxt[t] == c2) {
        t2 = t;
      }
    }
    swap(nxt[t1], nxt[t2]);
    // make();
  }
  forn(i, n) {
    s[i] = nxt[s[i]];
  }
  printf("%s\n", s);
}


int main() {
	prepare("");
    read();
    solve();

    return 0;
}
