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
#include <random>
#include <chrono>
 
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

int a[NMAX];
int CNT = 0;
int n;
map<pair<int, int>, bool> mem;

bool is_less(int i, int j) {
  if (mem.find(mp(i, j)) != mem.end()) {
    return mem[mp(i, j)];
  }
  if (mem.find(mp(j, i)) != mem.end()) {
    return !mem[mp(j, i)];
  }
  if (i >= n) {
    return mem[mp(i, j)] = false;
  }
  if (j >= n) {
    return mem[mp(i, j)] = true;
  }
  ++CNT;
  return mem[mp(i, j)] = a[i] < a[j];
  printf("? %d %d\n", i, j);
  fflush(stdout);
  char buf[10];
  scanf("%s", buf);
  return mem[mp(i, j)] = buf[0] == '<';
}

struct p {
  int r[2];
  p() {}
  p(int t) { r[0] = r[1] = t; }
  p(int a, int b) { r[0] = a; r[1] = b; }
};

p go(int L, int R) {
  dbg("L, R = %d %d\n", L, R);
  if (L == R) {
    return p(L);
  }
  int M = (L + R) / 2;
  auto r1 = go(L, M);
  auto r2 = go(M + 1, R);
  p res;
  int i = 0, j = 0;
  forn(s, 2) {
    if (is_less(r1.r[i], r2.r[j])) {
      res.r[s] = r1.r[i++];
    } else {
      res.r[s] = r2.r[j++];
    }
  }
  if (res.r[0] == res.r[1]) {
    res.r[1] = j == 0? r2.r[0] : r1.r[0];
  }
  return res;
}

void read() {
  scanf("%d", &n);
}


void solve() {
  vector<int> a;
  forn(i, n) {
    a.pb(i);
  }
  nth_element(a.begin(), a.begin() + 1, a.end(), is_less);
  printf("%d\n", a[1]);
  // int m = n;
  // while (m & (m - 1)) ++m;
  // auto ans = go(0, m - 1);
  // printf("! %d\n", ans.r[1]);
  // fflush(stdout);
  // for (auto it = mem.begin(); it != mem.end(); ) {
  //   if (it->first.first >= n || it->first.second >= n) {
  //     it = mem.erase(it);
  //   } else {
  //     ++it;
  //   }
  // }
  dbg("%d %d %d\n", (int)sz(mem), n, CNT);
  if (CNT > n + 20) {
    dbgx("JOPA");
    exit(0);
  }
}

void gen() {
  mem.clear();
  CNT = 0;
  n = 100;
  forn(i, n) {
    a[i] = i;
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(a, a + n, std::default_random_engine(seed));
}

int main() {

  // read();
  // solve();

  while (1) {
    // read();
    gen();
    solve();
  }

  return 0;
}
