#include "validator.h"

void run() {
	int n = Int(1, int(3e5));
	Space();
	int m = Int(1, Arg("maxm"));
	Space();
	int k = Int(1, m);
	Endl();
	vector<pair<int,int>> towers;
	for (int i = 0; i < m; i++)
	{
		int a = Int(0, n-1);
		Space();
		int b = Int(0, n-1);
		Endl();
		towers.push_back({a,b});
	}
	AssertUnique(towers);
}
