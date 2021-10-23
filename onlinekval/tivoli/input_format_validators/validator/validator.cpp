#include "validator.h"

void run() {
	int N = Int(1, 15);
	Endl();
	set<pair<int, int>> points;
	points.emplace(0, 0);
	auto point = [&]() -> pair<int, int> {
		const int M = 1'000'000 - 1;
		int x = Int(-M, M);
		Space();
		int y = Int(-M, M);
		return {x, y};
	};
	for (int i = 0; i < N; i++) {
		points.insert(point());
		Space();
		points.insert(point());
		Endl();
	}
	assert((int)points.size() == 2*N+1);
}
