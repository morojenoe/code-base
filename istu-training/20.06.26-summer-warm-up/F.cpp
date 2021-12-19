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

class MySet {
public:
  set<pair<lint, int>> s;
  lint add;

  MySet(): add(0) {}

  void insert(lint k, int id) {
    s.insert(mp(k, id));
    dbg("inserting (%lld, %d)\n", k, id);
  }

  void erase(lint k, int id) {
    dbg("erasing (%lld, %d)\n", k, id);
    k -= add;
    auto it = s.lower_bound(mp(k, -1));
    if (it != s.end()) {
      dbg("found: (%lld, %d)\n", it->first, it->second);
    }
    if (it == s.end() || it->first != k || it->second != id) {
      assert(false && "cannot find what to erase");
    }
    s.erase(it);
  }

  void add_to_add(lint val) {
    add -= val;
  }

  bool search(lint k, int &r) {
    k -= add;
    auto it = s.lower_bound(mp(k, -1));
    if (it != s.end() && it->first == k) {
      r = it->second;
      return true;
    }
    return false;
  }

  void debug() {
    dbg("------------\n");
    dbg("set:");
    for (auto it: s) {
      dbg(" (%lld, %d)", it.first, it.second);
    }
    dbg("\n------------\n");
  }
};

const int NMAX = 100005;

int n;
int a[NMAX];
MySet s;
lint x;

void read() {
  scanf("%d", &n);
  forn(i, n) {
    scanf("%d", &a[i]);
  }
  scanf("%lld", &x);
}

void solve() {
  lint sum = 0;
  forn(i, n) {
    sum += a[i];
    s.insert(sum, i);
  }

  forn(i, n) {
    int r;
    if (s.search(x, r)) {
      printf("%d %d\n", i + 1, r + 1);
      return;
    }
    s.erase(a[i], i);
    s.add_to_add(a[i]);
  }
  printf("-1 -1\n");
}

int main() {
	prepare("");
    read();
    solve();

    return 0;
}
