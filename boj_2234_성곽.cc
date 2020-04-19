#if 01
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define SIZE 50
typedef pair<int, int> pii;
int MAP[SIZE + 10][SIZE + 10], N, M;
int check[SIZE + 10][SIZE + 10];
vector<pii> rooms[SIZE*SIZE + 10];

int dr[] = { 0, -1, 0, 1 };
int dc[] = { -1, 0, 1, 0 };

void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << check[i][j] << " ";
		}
		cout << '\n';
	}
}

void dfs(int r, int c, int cnt) {
	check[r][c] = cnt;
	rooms[cnt].push_back(pii(r, c));

	for (int d = 0; d < 4; d++) {
		int nR = r + dr[d], nC = c + dc[d];
		if (check[nR][nC]) continue;
		if (MAP[r][c] & (1 << d)) continue;
		dfs(nR, nC, cnt);
	}
}

bool ok(int r1, int r2) {
	for (auto &p : rooms[r1]) {
		int walls = MAP[p.first][p.second];
		
		for (int d = 0; d < 4; d++) {
			int nR = p.first + dr[d], nC = p.second + dc[d];
			if (walls & (1 << d)) { //벽이있는데
				if (check[nR][nC] == r2) { //이벽뜷으면 다른방일때
					return true; //가능
				}
			}
		}
	}

	return false;
}

void solve() {
	//1. 번호 매기기 (flood fill)
	int roomcnt = 0; //방의 갯수
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (check[i][j]) continue;
			dfs(i, j, ++roomcnt);
		}
	}

//	print(); 
	int ans2 = 0;
	for (int i = 1; i <= roomcnt; i++) {
		ans2 = max(ans2, (int)rooms[i].size());
	}

	//1, 2번 답 구하기
	cout << roomcnt << '\n';
	cout << ans2 << '\n';

	//3번 답 구하기

	//for (int i = 1; i <= roomcnt; i++) {
	//	printf("room %d's size %d\n", i, rooms[i].size());
	//}

	int ans3 = 0;

	for (int i = 1; i < roomcnt; i++) {
		for (int j = i + 1; j <= roomcnt; j++) {
			//두 방이 합치는거 가능한지 체크 후 가능하면 답에 포함
			if (ok(i, j)) {
				ans3 = max(ans3, (int)rooms[i].size() + (int)rooms[j].size());
			}
		}
	}

	cout << ans3 << '\n';
}

int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> M >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
		}
	}

	solve();

	return 0;
}
#endif