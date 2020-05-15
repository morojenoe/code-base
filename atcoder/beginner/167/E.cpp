#define _CRT_SECURE_NO_DEPRECATE
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
    //freopen ("output.txt", "w", stdout);
#else
    if (s.length() != 0)
    {
        freopen ((s + ".in").c_str(), "r", stdin);
        freopen ((s + ".out").c_str(), "w", stdout);
    }
#endif
}

const int MOD = 998244353;
const int NMAX = 2000050;

int n, m, k;
int cnt[NMAX];
int f[NMAX];
int revf[NMAX];

int add(lint a, lint b) {
  return (a + b) % MOD;
}

int mul(lint a, lint b) {
  return (a * b) % MOD;
}

int bpow(int n, int k) {
  int res = 1;
  for (; k > 0; k >>= 1) {
    if (k & 1) {
      res = mul(res, n);
    }
    n = mul(n, n);
  }
  return res;
}

int cnk(int n, int k) {
  return mul(mul(f[n], revf[k]), revf[n - k]);
}


void read() {
  scanf("%d %d %d", &n, &m, &k);
}

void solve() {
  f[0] = 1;
  revf[0] = 1;
  forab(i, 1, NMAX - 1) {
    f[i] = mul(f[i - 1], i);
    revf[i] = bpow(f[i], MOD - 2);
  }

  cnt[0] = mul(m, bpow(m - 1, n - 1));

  forab(i, 1, n - 1) {
    cnt[i] = mul(m, bpow(m - 1, n - 1 - i));
    cnt[i] = mul(cnt[i], cnk(n - 1, i));
  }

  int ans = 0;
  forab(i, 0, k) {
    ans = add(ans, cnt[i]);
  }
  printf("%d\n", ans);
}

int main() {
  prepare("");

  read();
  solve();

  // forn(i, 10) {
  //   forn(j, i + 1) {
  //     dbg("%d ", cnk(i, j));
  //   }
  //   dbg("\n");
  // }
  return 0;
}