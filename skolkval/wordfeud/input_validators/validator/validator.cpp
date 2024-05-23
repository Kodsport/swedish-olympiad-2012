#include <bits/stdc++.h>
#include "validator.h"



using namespace std;

void run() {
	bool disallow_mul = Arg("disallow_mul", false);
	int n = Int(1, 10);
	Endl();

	vector<vector<int>> taken(10, vector<int>(10));
	for (int i = 0; i < n; i++)
	{
		int c = Int(1,10);
		Space();
		int r = Int(1,10);
		Space();
		char w1 = Char();
		char w2 = Char();
		Endl();
		assert(!taken[r-1][c-1]);
		taken[r-1][c-1]=1;
		string type = string(1,w1)+string(1,w2);
		assert(type=="DL"||type=="TL"||type=="DW"||type=="TW");
		if (disallow_mul)
		{
			assert(type!="DW"&&type!="TW");
		}
	}
	
	string word = Line();
	for (auto c : word)
	{
		assert(c>='0' && c<='8');
	}

	
	Eof();
}
