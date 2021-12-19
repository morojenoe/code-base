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

template<typename RAIter, typename T>
vector<pair<T, size_t>> group(RAIter begin, RAIter end) {
  sort(begin, end);
  vector<pair<T, size_t>> result;
  while (begin < end) {
    T cur_value = *begin;
    size_t count = 0;
    while (begin < end && *begin == cur_value) {
      ++count;
      ++begin;
    }
    result.push_back(make_pair(cur_value, count));
  }
  return result;
}


const int NMAX = 100005;

int n, m;
int a[NMAX], b[NMAX], c[NMAX];;
set<pair<int, int>> s;

void read() {
  scanf("%d %d", &n, &m);
  forn(i, n) scanf("%d", &a[i]);
  forn(i, m) scanf("%d %d", &b[i], &c[i]);
}

template<class T>
void debug(const T &g) {
#ifdef MY_DEBUG

  dbg("-------------\n");
  for (auto v : g) {
    dbg("(%d, %d) ", v.first, v.second);
  }
  dbg("\n-------------\n");

#endif
}

void solve() {
  auto g = group<int*, int>(a + 0, a + n);
  s.insert(all(g));
  forn(i, m) {
    int cnt = b[i];
    int val = c[i];
    dbg("%d) %d %d", i, cnt, val);
    auto it = s.begin();
    int count = 0;
    while (cnt > 0 && it->first < val) {
      if (it->second <= cnt) {
        count += it->second;
        cnt -= it->second;
        it = s.erase(it);
      } else {
        count += cnt;
        auto cur_val = *it;
        cur_val.second -= cnt;
        s.erase(it);
        s.insert(cur_val);
        cnt = 0;
      }
    }
    debug(s);
    dbgx(val);
    dbgx(count);
    if (count > 0) {
      auto it = s.lower_bound(mp(val, -1));
      if (it != s.end() && it->first == val) {
        auto cur_val = *it;
        cur_val.second += count;
        s.erase(it);
        s.insert(cur_val);
      } else {
        s.insert(mp(val, count));
      }
    }
    debug(s);
  }

  lint sum = 0;
  for (auto v : s) {
    sum += v.first * 1LL * v.second;
  }
  printf("%lld\n", sum);
}

int main() {
	prepare("");

  read();
  solve();

  return 0;
}
