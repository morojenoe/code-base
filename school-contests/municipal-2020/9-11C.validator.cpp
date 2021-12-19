#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int NMAX = 500000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, NMAX, "n");
    inf.readSpace();
    int k = inf.readInt(1, NMAX, "k");
    ensuref(k < n, "k should be less than n");
    inf.readEoln();
    char token[50];
    sprintf(token, "[1-9][0-9]{%d,%d}", n - 1, n - 1);
    inf.readToken(token, "number");
    inf.readEoln();
    inf.readEof();
}
