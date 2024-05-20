#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

const int maxcoord = int(3e5) + 10;

signed main()
{
    fast();

	int n, m, k;
	cin >> n >> m >> k;

	vvi x(maxcoord);
	vvi y(maxcoord);

	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		x[a].push_back(i);
		y[b].push_back(i);
	}

	UF uf(m);
	auto join = [&](vvi& axis)
	{
		rep(i, maxcoord)
		{
			repp(j, 1, sz(axis[i]))
			{
				uf.join(axis[i][0], axis[i][j]);
			}
		}
	};
	join(x);
	join(y);

	vi compsizes;
	vi vis(m);
	rep(i, m)
	{
		int u = uf.find(i);
		if (vis[u]) continue;
		vis[u] = 1;
		compsizes.push_back(uf.size(u));
	}
	sort(all(compsizes));
	reverse(all(compsizes));
	int ans = 0;
	rep(i, min(k, sz(compsizes)))
	{
		ans += compsizes[i];
	}
	cout << ans;

    return 0;
}