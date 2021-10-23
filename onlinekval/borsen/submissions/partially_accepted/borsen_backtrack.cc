#include <cstdio>
#include <algorithm>

using namespace std;

double cost;
double as[14];
int n;

double bf(int at, double money, double stock) {
    if (at == n) return money;
    double res = bf(at + 1, money, stock);
    res = max(res, bf(at + 1, 0, (money - cost) / as[at]));
    res = max(res, bf(at + 1, stock * as[at] - cost, 0));
    return res;
}

int main(){
	scanf("%d%lf", &n, &cost);
    for (int i = 0; i < n; i++) scanf("%lf", as + i);
	printf("%lf\n", bf(0, 100, 0));
}
