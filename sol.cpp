#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int NMAX = 305;

int n;
int a, m;
pair<int, int> p[NMAX*NMAX];

int main() {
    scanf("%d", &n);
    m = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a);
            m = max(m, a);
            p[a] = make_pair(i, j);
        }
    }

    int ans = 0;
    for (int i = 1; i < m; ++i) {
        ans += abs(p[i + 1].first - p[i].first) + abs(p[i + 1].second - p[i].second);
    }
    printf("%d\n", ans);

    return 0;
}
