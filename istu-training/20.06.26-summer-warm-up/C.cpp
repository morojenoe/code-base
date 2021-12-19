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

const int NMAX = 2005;
const int SMAX = 105;

string s;
string w[NMAX];
int n;
int d[SMAX];

void read() {
  cin >> s >> n;
  forn(i, n) {
    cin >> w[i];
  }
}

bool search(string t) {
  forn(i, n) {
    if (w[i] == t) {
      return true;
    }
  }
  return false;
}

void rec(int n) {
  assert(d[n] != -1);
  dbgx(n);
  if (d[n] == -100) {
    cout << s.substr(0, n + 1);
    return;
  }

  rec(d[n]);
  cout << " " << s.substr(d[n] + 1, n - d[n]);
}

void solve() {
  int L = s.length();
  _(d, -1);
  string sub;
  for (int i = 0; i < L; ++i) {
    sub = s.substr(0, i + 1);
    if (search(sub)) {
      d[i] = -100;
      dbgx(i);
    }
  }

  

  for (int i = 1; i < L; ++i) {
    for (int j = i; j > 0; --j) {
      if (d[i - j] != -1 && d[i] == -1) {
        sub = s.substr(i - j + 1, j);
        if (search(sub)) {
          d[i] = i - j;
        }
      }
    }
  }

  dbg("dp: ");
  forn(i, s.length()) {
    dbg(" %d", d[i]);
  }
  dbg("\n");

  dbgx("OK");
  rec(s.length() - 1);
  cout << "\n";
}

int main() {
	prepare("");
    read();
    solve();

    return 0;
}
