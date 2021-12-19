#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> st;
int n, k;
const int NMAX = 500005;
char buf[NMAX];
string s;

int main() {
  scanf("%d %d\n%s", &n, &k, buf);
  s = buf;

  for (int i = 0; i < (int)s.length(); ++i) {
    int d = s[i] - '0';
    while (k > 0 && st.size() > 0 && st[(int)st.size() - 1] < d) {
      st.pop_back();
      k--;
    }
    st.push_back(d);
  }

  while (k > 0) {
    st.pop_back();
    k--;
  }

  for (int i = 0; i < (int)st.size(); ++i) {
    printf("%d", st[i]);
  }
  printf("\n");

  return 0;
}