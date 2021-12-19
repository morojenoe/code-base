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

const int NMAX = 55;

int n;
string in, out;
int a[NMAX][NMAX];

void read() {
  cin >> n >> in >> out;
}

void solve() {
  forn(i, n) {
    forn(j, n) {
      if (i == j || (out[i] == 'Y' && in[j] == 'Y' && (i - j == 1 || i - j == -1))) {
        a[i][j] = 1;
      } else {
        a[i][j] = 0;
      }
    }
  }

  // dbg("------------\n");
  // forn(i, n) {
  //   forn(j, n) {
  //     dbg("%c", a[i][j] ? 'Y' : 'N');
  //   }
  //   dbg("\n");
  // }
  // dbg("------------\n");

  forn(k, n) {
    forn(i, n) {
      forn(j, n) {
        a[i][j] = a[i][j] | (a[i][k] & a[k][j]);
      }
    }
  }

  forn(i, n) {
    forn(j, n) {
      printf("%c", a[i][j] ? 'Y' : 'N');
    }
    printf("\n");
  }
}

int main() {
	prepare("");

  int t;
  scanf("%d", &t);
  forn(i, t) {
    printf("Case #%d:\n", i + 1);
    read();
    solve();
  }

  return 0;
}
