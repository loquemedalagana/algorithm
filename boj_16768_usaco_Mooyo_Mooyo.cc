#if 01
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <functional>
using namespace std;
#define SIZE 100
typedef pair<int, int> pii;
const int M = 10;
int N, K; int check[SIZE + 10][M];
vector<string> MAP;
vector<pii> cluster[SIZE*M + 10]; //저장할 좌표

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < N && c < M;
}

void print() {
	for (int i = 0; i < N; i++) {
		cout << MAP[i] << '\n';
	}
#if 0
	printf("visited\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << check[i][j] << " ";
		}
		cout << '\n';
	}
#endif
}

void dfs(int r, int c, int cnt, char type) {
	check[r][c] = cnt;
	cluster[cnt].push_back(pii(r, c));

	for (int d = 0; d < 4; d++) {
		int nR = r + dr[d], nC = c + dc[d];
		if (inRange(nR, nC) && MAP[nR][nC] != '0' && !check[nR][nC]) {
			if(MAP[nR][nC]==type) dfs(nR, nC, cnt, type);
		}
	}
}

pair<vector<int>, int> find() { //0 => not found, 1>= 클러스터의 갯수
	int cnt = 0;
	memset(check, 0, sizeof(check));
	vector<int> willdelete;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == '0' || check[i][j]) continue;
			dfs(i, j, ++cnt, MAP[i][j]);
		}
	}

	if(cnt==0) return pair<vector<int>, int>(willdelete, cnt);

	for (int i = 1; i <= cnt; i++) {
		if (cluster[i].size() >= K) {
			willdelete.push_back(i);
		}
	}
	return pair<vector<int>, int>(willdelete, cnt);
}

void clear(int landcnt, vector<int> &willdelete) { //willdelete는 지워질 클러스터
	
	for (int idx : willdelete) {
		for (auto &p : cluster[idx]) {
			MAP[p.first][p.second] = '0';
		}
	}

	vector<string> temp(N);
	for (int i = 0; i < N; i++) {
		temp[i] = "0000000000";
	}

	//fall
	/*개인적으로 여기 떨어트리는게 어려웠다ㅠㅠ*/
	for (int j = 0; j < M; j++) {
		string tmp = "";
		for (int i = N-1; i >= 0; i--) {
			if (MAP[i][j] != '0') {
				tmp += MAP[i][j];
			}
		}

		if (tmp.length() >= 1) {
			int idx = N - 1;
			for (char c : tmp) {
				temp[idx--][j] = c;
			}
		}
	}

#if 0
	printf("after fall\n");
	for (int i = 0; i < N; i++) {
		cout << temp[i] << '\n';
	}
	cout << '\n';
#endif
	MAP = temp;
	//init
	for (int i = 1; i <= landcnt; i++) {
		cluster[i].clear();
	}
}

void solve() {
//	print();
	while (true) {
		pair<vector<int>, int> willdelete = find();
		if (willdelete.first.empty()) break;
		else {
			clear(willdelete.second, willdelete.first);
		//	print();
		}
	}

#if 0
	pair<vector<int>, int> willdelete = find();
	if (willdelete.first.empty()) return;
	else {
		clear(willdelete.second, willdelete.first);
		print();
	}
#endif
	print();
}

int main() {
	//freopen("16768.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> N >> K; MAP.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> MAP[i];
	}
	solve();

	return 0;
}
#endif