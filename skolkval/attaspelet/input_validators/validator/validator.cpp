#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run()
{
	// Assume that they are solvable
	vector<int> seen(9);
	vector<int> nums = SpacedInts(9, 0, 8);
	for (int i = 0; i < 9; i++)
	{
		if (seen[nums[i]]) assert(0);
		seen[nums[i]]=1;
	}
	Eof();
}
