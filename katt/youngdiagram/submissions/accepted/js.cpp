#include <vector>
#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int n;
 
int go2(vector<int>& q, int len) {
	if(len == 0) return -10000;
	for(vector<int>::iterator it = q.begin(); it != q.end(); ++it){
		if(*it <= 0) return -10000;
	}
	int ans = 0;
	int last[q[0]];
	for (int i = 0; i < q[0]; i++) {
		last[i] = 1;
		ans++;
	}
	for (int i = 1; i < len; i++) {
		int lastLen = q[i - 1];
		int thisLen = q[i];
		if (thisLen > lastLen) {
			return -10000;
		}
		int sum = 0;
		for (int j = lastLen - 1; j >= 0; j--) {
			sum += last[j];
			if (j < thisLen) {
				ans += sum;
			}
			last[j] = sum;
		}
	}
	return ans;
}
 
 
int at;
 
vector<vector<int> > generate(vector<vector<int> >& seqs) {
	//printf("begin generate\n");
	vector<vector<int> > best;
	int bestNum = 0;
	for (vector<vector<int> >::iterator it = seqs.begin(); it != seqs.end(); ++it){
		//printf("begin sequence \n");
		vector<int> nums = *it;
		int len = nums.size();
		for(int a1 = 0; a1<len; a1++){
			if(a1 && nums[a1] == nums[a1-1]) continue;
			for(int a2 = a1; a2<len; a2++){
				if(a2 && nums[a2] == nums[a2-1]) continue;
				for(int b1 = a2; b1<len; b1++){
					if(b1 && nums[b1] == nums[b1-1]) continue;
					if(b1 != a1 && nums[a1] < 9) continue;
					for(int b2 = b1; b2<len; b2++){
						if(b2 && nums[b2] == nums[b2-1]) continue;
						for(int b3 = b2; b3<len; b3++){
							if(b3 && nums[b3] == nums[b3-1]) continue;
							//printf("length: %d adds: %d %d %d %d %d\n", len, a1, a2, b1, b2, b3);
							nums[a1]--;
							nums[a2]--;
							nums[b1]++;
							nums[b2]++;
							nums.push_back(1);
							int res = go2(nums, len+1);
							if(res > bestNum){
								best.clear();
								bestNum = res;
							}
							if(res == bestNum && find(best.begin(), best.end(), nums) == best.end()) best.push_back(nums); 
							nums.pop_back();
							nums[b3]++;
							res = go2(nums, len);
							//printf("result: %d\n", res);
							if(res > bestNum){
								best.clear();
								bestNum = res;
							}
							if(res == bestNum && find(best.begin(), best.end(), nums) == best.end()) best.push_back(nums);
							for(int b4 = b3; b4<len-1 && a1 < 3 && at > 50; b4++){
								//if(a1 == 0 && a2 == 1 && b1 == 4 && b2 == 5 && b3 == 6){
								//printf("OK! last %d\n", nums[len-1]);
								//}
								int s = nums[len-1];
								if(s != 1) break;
								nums[b4]++;
								nums.pop_back();
								int res = go2(nums, len-1);
								if(res > bestNum){
									best.clear();
									bestNum = res;
								}
								if(res == bestNum && find(best.begin(), best.end(), nums) == best.end()) best.push_back(nums);
								nums.push_back(1);
								nums[b4]--;
							}
							nums[a1]++;
							nums[a2]++;
							nums[b1]--;
							nums[b2]--;
							nums[b3]--;
							//printf("done\n");
						}
					}
				}
			}
		}
		nums.push_back(1);
		int res = go2(nums, len+1);
		if(res > bestNum){
			best.clear();
			bestNum = res;
		}
		if(res == bestNum && find(best.begin(), best.end(), nums) == best.end()) best.push_back(nums);
		//printf("end sequence\n");
	}
	//printf("end generate: \n");
	return best;
}
 
int main() {
	scanf("%d", &n);
	//n = 100;
	vector<vector<int> > seqs;
	vector<int> first;
	first.push_back(1);
	seqs.push_back(first);
	for (int i = 2; i <= n; i++) {
		at = i;
		seqs = generate(seqs);
		/*printf("%d\n", go2(seqs[0], seqs[0].size()));
		for(int j = 0; j<seqs.size(); j++){
			for (vector<int>::iterator it = seqs[j].begin(); it != seqs[j].end(); ++it) {
				printf("%d ", *it);
			}
			printf("\n");
		}*/
	}
	printf("%d\n", go2(seqs[0], seqs[0].size()));
 
	for (vector<int>::iterator it = seqs[0].begin(); it != seqs[0].end(); ++it) {
		printf("%d ", *it);
	}
	printf("\n");
}
 
