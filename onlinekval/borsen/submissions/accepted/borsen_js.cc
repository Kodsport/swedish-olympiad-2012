#include <cstdio>
#include <algorithm>

using namespace std;

double cost, as;

int main(){
	int n;
	scanf("%d%lf", &n, &cost);
	double money = 100, stock = 0;
	for(int i = 0; i<n; i++){
		scanf("%lf", &as);
		double nstock = max(stock, (money-cost)/as);
		double nmoney = max(money, stock*as - cost);
		money = nmoney;
		stock = nstock;
	}
	printf("%.10lf\n", money);
}
