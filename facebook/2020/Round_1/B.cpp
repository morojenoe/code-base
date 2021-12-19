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

void print(lint *a, int N, char arr_name) {
#ifdef MY_DEBUG
  dbg("----------------\n");
  dbg("%c:", arr_name);
  forn(i, N) {
    dbg(" %lld", a[i]);
  }
  dbg("\n");
#endif
}

const int PMAX = 1000005;
const int QMAX = PMAX;

int N, M, K, S;
lint P[PMAX], Q[QMAX];
lint AP, BP, CP, DP;
lint AQ, BQ, CQ, DQ;

void read() {
  scanf("%d %d %d %d", &N, &M, &K, &S);
  forn(i, K) {
    scanf("%lld", &P[i]);
  }
  scanf("%lld %lld %lld %lld", &AP, &BP, &CP, &DP);
  forab(i, K, N - 1) {
    P[i] = ((AP*P[i - 2]) % DP + (BP*P[i - 1]) % DP + CP) % DP + 1;
  }

  forn(i, K) {
    scanf("%lld", &Q[i]);
  }
  scanf("%lld %lld %lld %lld", &AQ, &BQ, &CQ, &DQ);
  forab(i, K, M - 1) {
    Q[i] = ((AQ*Q[i - 2]) % DQ + (BQ*Q[i - 1]) % DQ + CQ) % DQ + 1;
  }
}

bool check_get(int i, int j, lint T, int mid) {
  lint time1 = P[i] - Q[j] + Q[mid] - Q[j];
  lint time2 = Q[mid] - P[i] + Q[mid] - Q[j];
  return time1 <= T || time2 <= T;
}

int get_max(int i, int j, lint T) {
  int L = j, R = M;
  while (R - L > 1) {
    int mid = (L + R) >> 1;
    if (check_get(i, j, T, mid)) {
      L = mid;
    } else {
      R = mid;
    }
  }
  return L + 1;
}

bool check(lint T) {
  int j = 0;
  forn(i, N) {
    if (j == M) {
      return true;
    }
    if (P[i] < Q[j]) {
      while (j < M && Q[j] - P[i] <= T) {
        ++j;
      }
    } else {
      if (P[i] - Q[j] > T) {
        return false;
      }
      j = get_max(i, j, T);
    }
  }
  return j == M;
}

void solve() {
  // print(P, N, 'P');
  // print(Q, M, 'Q');
  sort(P, P + N);
  sort(Q, Q + M);
  lint L = 0, R = LINF;
  while (R - L > 1) {
    lint M = (L + R) >> 1;
    if (check(M)) {
      R = M;
    } else {
      L = M;
    }
  }
  printf("%lld\n", R);
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
