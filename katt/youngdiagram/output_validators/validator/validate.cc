#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long double ld;

#define repe(i, container) for (auto& i : container)

vector<vector<pii>> coverdp;
int version = 0;
int num_covered(int prev, int i, vi& placement)
{
    if (i >= placement.size()) return 1;
    if (coverdp[prev][i].second == version) return coverdp[prev][i].first;
    int ret = 1;


    rep(diff, 1, min(prev + 1, placement[i] + 1))
    {
        ret += num_covered(diff, i + 1, placement);
    }
    coverdp[prev][i].first = ret;
    coverdp[prev][i].second = version;
    return ret;
}

int main(int argc, char **argv) {
	init_io(argc, argv);

	int n;
	judge_in >> n;
	const int maxn=120;
    coverdp.resize(maxn+1, vector<pii>(maxn+1, { 0,-1 }));


	auto check = [&](istream& sol, feedback_function feedback){
		int ans;
		if(!(sol >> ans)) feedback("Expected more output");
		if (ans<=0)
		{
			return -1;
		}

		int s = 0;
		int last = 100000;
		vi diagram;
		while (s<n)
		{
			int v;
			sol >> v;
			if (v<=0) feedback("All numbers of diagram must be >= 0");
			if (v>last) feedback("Diagram non-decreasing");
			last = v;
			s += v;
			diagram.push_back(v);
		}
		if (s!=n) feedback("Diagram has wrong sum");
		
		string trailing;
		if(sol >> trailing) feedback("Trailing output");
		version++;
		int real_cover = num_covered(maxn, 0, diagram)-1;
		if (ans != real_cover) feedback("Did not count number of covered diagrams correctly");
		return real_cover;
	};

	int judge_sol = check(judge_ans, judge_error);
	int author_sol = check(author_out, wrong_answer);

	if(author_sol > judge_sol)
		judge_error("NO! Contestant found better solution than judge");

	if(author_sol < judge_sol)
		wrong_answer("Contestant did not find optimal diagram");

	accept();
}
