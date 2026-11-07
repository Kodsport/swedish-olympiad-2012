#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m,k;
    cin >> n >> m >> k;
    using p3 = array<int,3>;

    vector<p3> towers;

    rep(i, m)
    {
        int x,y;
        cin >> x >> y;
        p3 p = {x,y,i};
        towers.push_back(p);
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
        if (!unions.contains(parent))
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

    cout << ans << '\n';

    return 0;
}
