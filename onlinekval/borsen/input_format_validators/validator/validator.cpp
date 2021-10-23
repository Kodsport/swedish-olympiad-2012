#include "validator.h"

typedef long long ll;

void run() {
	int maxn = Arg("maxn");
    int N = Int(1, maxn); Endl();
    Float(0, 100, 10); Endl();
    for (int i = 0; i < N; i++) {
        Float(1, 1000, 10, false); Endl();
    }
    Eof();
}
