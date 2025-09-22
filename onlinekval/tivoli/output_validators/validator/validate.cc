#include <vector>
#include <tuple>
#include <cstring>
#include <cmath>
#include <array>
#include "validate.h"

using namespace std;

struct Point {
	int x, y;
};

long double dist(Point a, Point b) {
	long double dx = a.x - b.x;
	long double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

bool equal(long double correct, long double tested) {
	return abs(correct - tested) <= 1e-5 * abs(correct) 
        || abs(correct - tested) <= 1e-5;
}

long double
read_solution(int n, vector<array<Point, 2>>& inp, istream &sol, feedback_function feedback) {
	long double givenDist;
	sol >> givenDist;
	if (!(givenDist > 0) || isinf(givenDist) || isnan(givenDist))
        feedback("Expected positive distance");
	vector<bool> seen(n);
	Point last = {0, 0};
	double way = 0;
	for (int i = 0; i < n; i++) {
		int where, which;
		sol >> where >> which;
		if (!sol) feedback("Unexpected EOF");
		if (where < 1 || where > n) feedback("oob location");
		if (which < 1 || which > 2) feedback("oob choice");
		if (seen[where - 1]) feedback("duplicate location");
		seen[where - 1] = true;
		Point p = inp[where - 1][which - 1];
		way += dist(last, p);
		last = p;
	}
	if (!sol) feedback("Unexpected EOF");
	string tmp;
	if (sol >> tmp) feedback("Trailing output");
	way += dist(last, Point{0, 0});
	if (!equal(way, givenDist)) feedback("Incorrectly printed distance");
	return way;
}

int main(int argc, char **argv) {
	init_io(argc, argv);

	int n;
	judge_in >> n;
	vector<array<Point, 2>> inp(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			judge_in >> inp[i][j].x >> inp[i][j].y;
		}
	}

	long double out = read_solution(n, inp, cin, wrong_answer);
	long double ans = read_solution(n, inp, judge_ans, judge_error);

	if (equal(ans, out)) {
		accept();
	}

	if (out < ans) {
		judge_error("gave better solution than judge");
	}
	else {
		wrong_answer("gave worse solution than judge");
	}
}
