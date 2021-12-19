#include "./testlib.h"
#include <iostream>
#include <cstdio>

using namespace std;

void print_table(int n) {
    int c = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d%c", c++, j + 1 == n ? '\n' : ' ');
        }
    }
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    if (n == -1) {
        print_table(300);
        return 0;
    }

    int c = 0;
    auto values = rnd.perm(n*n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d%c", values[c++] + 1, j + 1 == n ? '\n' : ' ');
        }
    }
    
    return 0;
}
