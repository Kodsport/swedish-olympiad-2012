#include <cstdio>

int main() {
	int n;
	scanf("%d", &n);
	
	int count = 0;
	
	for(int i=1; i<=n; i++) {
		for(int j=i; j<=n; j++) {
			for(int k=j; k<=n; k++) {
				if(i*i + j*j - i*j == k*k   ||   i*i + k*k - i*k == j*j    ||    j*j + k*k - j*k == i*i) {
					count++;
				}
			}
		}
	}
	
	printf("%d\n", count);
	return 0;
}
