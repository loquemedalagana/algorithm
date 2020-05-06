#if 01
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
#define SIZE 20
#define INF (int)1e9
typedef pair<int, int> pii;
char MAP[SIZE + 10][SIZE + 10];
int check[SIZE + 10][SIZE + 10][4], N, M, NUM;
pii st, en;

int dr[] = { 0, 0, 1, -1 }; //동서남북순!
int dc[] = { 1, -1, 0, 0 };

struct Cross {
	pii p; //위치
	char shape;
	int EW, SN; //동서, 남북
	Cross(pii p, char shape, int EW, int SN) {
		this->p = p;
		this->shape = shape;
		this->EW = EW;
		this->SN = SN;
	}
	Cross() {}
};

Cross cross[10];

struct Info {
	pii p; int dir, time;
	Info(pii p, int dir, int time) {
		this->p = p;
		this->dir = dir;
		this->time = time;
	}
	Info() {}
};

struct cmp {
	bool operator () (const Info &a, const Info &b) {
		return a.time > b.time;
	}
};

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < N && c < M;
}

void init() {
	memset(MAP, NULL, sizeof(MAP));
	//	memset(check, -1, sizeof(check));
	NUM = 0;
}

void print() {
#if 01
	for (int d = 0; d < 4; d++) {
		printf("dir %d\n", d);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (check[i][j][d] == INF) cout << "x ";
				else cout << check[i][j][d] << " ";
			}
			cout << '\n';
		}
	}

#endif
#if 0
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (check[i][j] == INF) cout << "x ";
			else cout << check[i][j] << " ";
		}
		cout << '\n';
	}
#endif
}

//갈 수 있는 경우 0리턴, 못 가는 경우 기다려야 하는 시간 리턴
/*
켜져 있는 시간의 주기 (동서 + 남북) 합 -> 등차수열???
*/

int calc(int idx, int time, int dir) {
	char shape = cross[idx].shape;
	int ret = 100, ew = cross[idx].EW, sn = cross[idx].SN;

	int mod = time % (ew + sn);
	if (mod == 0) mod = (ew + sn); //실수ㅠㅠ
	ret = time / (ew + sn);

	if (dir < 2) {
		int fst = (shape == '-') ? 1 : sn + 1;
		int lst = fst + ew - 1;
		//printf("time %d -  %d ~ %d\n", time, fst, lst);
		if (mod >= fst && mod <= lst) {
			return 0;
		}
		else {
			//다음 가능한 시간 중 가장 빠른 시간
			for (int i = fst; ; i += (sn + ew)) {
				if (i >= time) {
					return i;
				}
			}
		}
	}
	else {
		int fst = (shape == '|') ? 1 : ew + 1;
		int lst = fst + sn - 1;
	//	printf("time %d |  %d ~ %d\n", time, fst, lst);
		if (mod >= fst && mod <= lst) {
			return 0;
		}
		else {
			//다음 가능한 시간 중 가장 빠른 시간
			for (int i = fst; ; i += (sn + ew)) {
				if (i >= time) {
					return i;
				}
			}
		}
	}

	//	return ret;
}

void solve() {
	priority_queue<Info, vector<Info>, cmp> q;
#if 01
	for (int d = 0; d < 4; d++) {
		int nR = st.first + dr[d], nC = st.second + dc[d];
		if (inRange(nR, nC) && MAP[nR][nC] != '.') {
			check[st.first][st.second][d] = 0;
			q.push(Info(st, d, 0));
		}
	}
#endif
	//check[st.first][st.second] = 0;
	
	//q.push(Info(st, -1, 0));

	while (!q.empty()) {
		int r = q.top().p.first, c = q.top().p.second, dir = q.top().dir, time = q.top().time; q.pop();
		if (pii(r, c) == en) {
		//	print();
			cout << time << '\n';
			return;
		}

		for (int d = 0; d < 4; d++) {
			int nR = r + dr[d], nC = c + dc[d];
			if (!inRange(nR, nC) || MAP[nR][nC] == '.') continue;
			if (dir == -1) dir = d;

			if (MAP[nR][nC] == '#' || pii(nR, nC) == en) {
				if (check[nR][nC][d] > time + 1) {
					check[nR][nC][d] = time + 1;
					q.push(Info(pii(nR, nC), d, time + 1));
				}
			}

			else if (MAP[nR][nC] >= '0' && MAP[nR][nC] <= '9') {
				//켜져 있으면 지나가고, 꺼져 있으면 기다린다.
				int wait = calc(MAP[nR][nC] - '0', time + 1, dir);
		//		printf("num %d, shape %c, dir %d -> %d, time %d-> %d\n", MAP[nR][nC] - '0', cross[MAP[nR][nC] - '0'].shape, dir, d, time, wait);
				if (wait == 0) {
					if (check[nR][nC][d] > time + 1) {
						check[nR][nC][d] = time + 1;
						q.push(Info(pii(nR, nC), d, time + 1));
					}

				}
				else {
					if (check[nR][nC][d] > wait) {
						//	printf("num %d, shape %c, dir %d -> %d, time %d-> %d\n", MAP[nR][nC] - '0', cross[MAP[nR][nC] - '0'].shape, dir, d, time, wait);
						check[nR][nC][d] = wait;
						q.push(Info(pii(nR, nC), d, wait));
					}
				}
			}
		}
	}

	//	print();

	cout << "impossible\n";
}

int main() {
//	freopen("1400.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0);

	while (true) {
		cin >> N >> M;
		if (!N && !M) return 0;
		init();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
			//	check[i][j] = INF;
				fill(check[i][j], check[i][j] + 4, INF);
				cin >> MAP[i][j];
				if (MAP[i][j] >= '0' && MAP[i][j] <= '9') { //교차로 인덱싱
					NUM++;
					//좌표 저장
					cross[MAP[i][j] - '0'].p = pii(i, j);
				}
				else if (MAP[i][j] == 'A') {
					st = pii(i, j);
				}
				else if (MAP[i][j] == 'B') {
					en = pii(i, j);
				}
			}
		}

		//교차로가 있는 경우 교차로 정보 입력
		// - 동서방향 켜짐, | 남북방향 켜짐 (초기에)
		for (int i = 0; i < NUM; i++) {
			int idx; cin >> idx;
			cin >> cross[idx].shape >> cross[idx].EW >> cross[idx].SN;
		}

		solve();
	}

	return 0;
}
#endif