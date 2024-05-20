#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define min(a, b) ((a)<(b)?(a):(b))

typedef pair<int, int> pii;

vector<pii> towers;
vector<vector<int>> xc(300000), yc(300000);
vector<int> skipx(300000), skipy(300000);
vector<int> components;
vector<bool> seen;

int comp;

void dfs(int at){
	seen[at] = true;
	comp++;
	int xx = towers[at].first;
	int yy = towers[at].second;
	for(int i = skipx[xx]; i < xc[xx].size(); i = skipx[xx]){
		skipx[xx] = i+1;
		if(xc[xx][i] != at){
			if(!seen[xc[xx][i]]){
				dfs(xc[xx][i]);
			}
		}
	}
	for(int i = skipy[yy]; i < yc[yy].size(); i = skipy[yy]){
		skipy[yy] = i+1;
		if(yc[yy][i] != at){
			if(!seen[yc[yy][i]]){
				dfs(yc[yy][i]);
			}
		}
	}
}

int main(){
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	seen.resize(m);
	for(int i = 0; i < m; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		towers.push_back(pii(x,y));
		xc[x].push_back(i);
		yc[y].push_back(i);
	}
	for(int i = 0; i < m; ++i){
		comp = 0;
		if(!seen[i]) dfs(i);
		components.push_back(comp);
	}
	sort(components.begin(), components.end());
	int ans = 0;
	for(int i = 0; i < min(components.size(), k); ++i){
		ans += components[components.size()-1-i];
	}
	printf("%d\n", ans);
}
