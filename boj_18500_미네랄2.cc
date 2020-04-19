#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define SIZE 100
typedef pair<int, int> pii;
char MAP[SIZE + 10][SIZE + 10];
int N, M, ord[SIZE+10], K;
int check[SIZE + 10][SIZE + 10];
vector<pii> cluster[SIZE*SIZE + 10];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << MAP[i][j];
		}
		cout << '\n';
	}
}

void print2() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << check[i][j] << " ";
		}
		cout << '\n';
	}
}

bool inRange(int r, int c) {
	return !check[r][c] && MAP[r][c] == 'x' && r >= 1 && c >= 1 && r <= N && c <= M;
}

void dfs(int r, int c, int cnt) {
	check[r][c] = cnt;
	cluster[cnt].push_back(make_pair(r, c));
	for (int d = 0; d < 4; d++) {
		int nR = r + dr[d], nC = c + dc[d];
		if (inRange(nR, nC)) dfs(nR, nC, cnt);
	}
}

bool cmp(const pii &a, const pii &b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

void fall(vector<pii> &clu, int num) {
	//max값과 n+1 혹은 다른 클러스터값과의 거리 계산
	int MX = (*max_element(clu.begin(), clu.end())).first;
	if (MX == N) return;

	int diff = N + 10;

	//차이 계산하기
	for (pii p : clu) {
		//	if (p.first < MX) continue;
		if (check[p.first+1][p.second] == num) continue;
		int i;
		for (i = p.first + 1; i <= N; i++) {
			if (check[i][p.second] != num && check[i][p.second]) {
				break;
			}
		}
	//	printf("cur %d, other cluster %d ", p.first, i);
		diff = min(diff, i - p.first - 1);
	//	printf("diff %d\n", i - p.first - 1);
	}

	if (diff == 0) return;

	for (pii &p : clu) {
		MAP[p.first][p.second] = '.';
	}

	for (pii p : clu) {
		MAP[p.first + diff][p.second] = 'x';
	}

}

void solve() {
//	print();
	for (int k = 0; k < K; k++) {
		//던지기
		int sr = ord[k]; int sc = (k % 2) ? (M + 1) : 0;
		if (sc == 0) {
			for (int j = sc + 1; j <= M; j++) {
				if (MAP[sr][j] == 'x') {
					MAP[sr][j] = '.';
					break;
				}
			}

		}
		else if (sc == M + 1) {
			for (int j = M; j >= 1; j--) {
				if (MAP[sr][j] == 'x') {
					MAP[sr][j] = '.';
					break;
				}
			}
		}

		//클러스터
		//find
		memset(check, 0, sizeof(check));
		int clustercnt = 0;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (check[i][j] || MAP[i][j] == '.') continue;
				dfs(i, j, ++clustercnt);
			}
		}

	//	print2();
	
		//fall
		for (int i = 1; i <= clustercnt; i++) {
			if (!cluster[i].empty()) {
			//	cout << cluster[i].size() << " ";
				fall(cluster[i], i);
				cluster[i].clear();
			}
		}
		
	//	print();
		
	}
	print();
}

int main() {
//	freopen("18500.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
		}
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> ord[i];
		ord[i] = (N + 1) - ord[i];
	}

	solve();

	return 0;
}