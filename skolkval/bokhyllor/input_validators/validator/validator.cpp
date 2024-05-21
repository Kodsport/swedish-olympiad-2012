#include "validator.h"

typedef long long ll;

const int maxb = 20;

void run() {
	int maxbsum = Arg("maxbsum");
	int maxw = Arg("maxw");
    int S = Int(0, maxb); Space();
    int M = Int(0, maxb); Space();
    int L = Int(0, maxb); Endl();
    assert(S + M + L <= maxbsum);
    int W = Int(1, maxw); Endl();
    Eof();
}
