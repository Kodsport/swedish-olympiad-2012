#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>
#include <random>
#include <time.h>
#include <stack>
#include <chrono>
#include <unordered_map>
#include <iomanip>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb __debugbreak();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)


inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

class DisjointSet
{

    std::unordered_map<int, int> rank;


public:
    std::unordered_map<int, int> p;
    DisjointSet(int m)
    {
        for (int i = 0; i < m; i++)
        {
            p[i] = i;
        }
    }

    int P(int x) { return (x == p[x]) ? x : p[x] = P(p[x]); }

    void Union(int a, int b)
    {
        int x = P(a);
        int y = P(b);

        // if `x` and `y` are present in the same set
        if (x == y) {
            return;
        }

        // Always attach a smainter depth tree under the
        // root of the deeper tree.
        if (rank[x] > rank[y]) {
            p[y] = x;
        }
        else if (rank[x] < rank[y]) {
            p[x] = y;
        }
        else {
            p[x] = y;
            rank[y]++;
        }
    }
};

void dfs(map<int,set<int>>& neighbours, vector<int>& seen, int c, int color)
{
    if (seen[c] != -1)
    {
        return;
    }
    else
    {
        seen[c] = color;
    }

    repe(neighbour, neighbours[c])
    {
        dfs(neighbours, seen, neighbour, color);
    }
}

int main()
{
    fast();

    int n;
    int m;
    int k;
    read(n);
    read(m);
    read(k);

    vector<p3> towers;

    rep(i, m)
    {
        int x;
        int y;
        read(x);
        read(y);
        towers.push_back({ x,y,i });
    }



    map<int, set<int>> neighbours;
    vector<int> groups(m, -1);


    rep(i, m)
    {
        neighbours[i] = {};
    }

    sort(all(towers));

    int curr = -1;
    rep(i, towers.size())
    {
        p3 tower = towers[i];
        if (tower[0] == curr)
        {

            neighbours[tower[2]].insert(towers[i - 1][2]);
            neighbours[towers[i - 1][2]].insert(tower[2]);
        }
        else
        {
            curr = tower[0];
        }
    }

    sort(all(towers), [](auto& left, auto& right) {
        return left[1] < right[1];
        });

    curr = -1;
    rep(i, towers.size())
    {
        p3 tower = towers[i];
        if (tower[1] == curr)
        {

            neighbours[tower[2]].insert(towers[i - 1][2]);
            neighbours[towers[i - 1][2]].insert(tower[2]);
        }
        else
        {
            curr = tower[1];
        }
    }

    rep(i, m)
    {
        dfs(neighbours, groups, i, i);
    }

    map<int, int> unions;
    repe(p, groups)
    {
        int parent = p;
        if (!setcontains(unions, parent))
        {
            unions[parent] = 0;
        }
        unions[parent]++;
    }

    vector<int> unionSizes;
    repe(un, unions)
    {
        unionSizes.push_back(-un.second);
    }

    sort(all(unionSizes));

    int ans = 0;
    rep(i, min(k, (int)unionSizes.size()))
    {
        ans -= unionSizes[i];
    }

    write(ans);

    return 0;
}
