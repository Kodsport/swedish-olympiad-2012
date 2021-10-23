#include <cstdio>
#include <algorithm>

using namespace std;

double cost;
double mxmoney[100000];
double as[100000];

int main(){
	int n;
	scanf("%d%lf", &n, &cost);
    mxmoney[0] = 100;
    scanf("%lf", as);
	for(int i = 1; i<n; i++){
		scanf("%lf", as+i);
        mxmoney[i] = mxmoney[i - 1];
        for (int j = 0; j < i; j++) {
            double nmoney = (mxmoney[j] - cost) / as[j] * as[i] - cost;
            mxmoney[i] = max(mxmoney[i], nmoney);
        }
	}
	printf("%.10lf\n", mxmoney[n - 1]);
}
