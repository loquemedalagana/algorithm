#include <stdio.h>
#define MAXN (int)1e5
int dp[MAXN + 10], MXN;
int main() {
	int N; scanf("%d", &N); 
	dp[1] = 1; 
	for (int i = 2; ; i++) {
		dp[i] = dp[i - 1] * i;
		if (dp[i] > N) {
			MXN = i;
			break;
		}
	}
	int loop = MXN-1;	int cnt = 0;
	while (N) {
		N -= dp[loop];
		cnt++;
		if (N < 0) {
			N += dp[loop--];
			cnt--;
		}
		else if (N == 0) break;
	}
	printf("%d\n", cnt);
	return 0;
}