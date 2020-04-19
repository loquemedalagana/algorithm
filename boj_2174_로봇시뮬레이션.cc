#if 01
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 100
#define W 0
#define E 1
#define S 2
#define NN 3
int R, C, N, M, MAP[SIZE+10][SIZE+10];
int res[SIZE + 10]; //시뮬레이션 결과 저장

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

struct Info {
	pii p; int dir;
	Info(pii p, int dir) {
		this->p = p;
		this->dir = dir;
	}
	Info() {}
};

Info robot[SIZE + 10];

bool inRange(int r, int c) {
	return r >= 1 && c >= 1 && r <= R && c <= C;
}

void print(int idx) {
	printf("robot %d\n", idx);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			printf("%2d", MAP[i][j]);
		}
		printf("\n");
	}
}

int turn(int dir) {
	switch (dir) {
	case E:
		return NN;
	case W:
		return S;
	case NN:
		return W;
	case S:
		return E;
	}
}


#if 01
int mov(int idx, char ord, int loop) { //로봇숫자, 명령, 이동횟수
	 //성공 return 0, 실패 : 벽 -1, 다른 로봇과 부딛힘 => 부딛힌 로봇의 숫자	
	if (ord == 'F') {
		for (int i = 0; i < loop; i++) {
			int &r = robot[idx].p.first, &c = robot[idx].p.second; int dir = robot[idx].dir;
			MAP[r][c] = 0;
			r += dr[dir], c += dc[dir];
			if (!inRange(r, c)) return -1;
			else {
				if (MAP[r][c]) return MAP[r][c];
				else MAP[r][c] = idx;
			}
		}
	}
	else {
		loop %= 4;
		if (loop == 0) return 0;
		while (loop--) {
			robot[idx].dir = turn(robot[idx].dir);
			if (ord == 'R') robot[idx].dir ^= 1;
		}
	}

	return 0;
}
#endif

void solve() {
	//명령 입력
	bool ok = true;
	for (int i = 0; i < M; i++) {
		int rbnum, loop; char ord; cin >> rbnum; cin >> ord; cin >> loop;
		res[rbnum] = mov(rbnum, ord, loop);
		if (res[rbnum] == -1) {
			ok = false;
			printf("Robot %d crashes into the wall\n", rbnum);
			goto EXIT;
			//return 0;
		}
		else if (res[rbnum] >= 1) {
			ok = false;
			printf("Robot %d crashes into robot %d\n", rbnum, res[rbnum]);
			goto EXIT;
		//	return 0;
		}
	}

EXIT:
	if (ok) printf("OK\n");
}

int main() {
//	freopen("2174.txt", "r", stdin); 
	cin.tie(0); ios::sync_with_stdio(0);
//	int T; cin >> T;
//	while (T--) {
		memset(MAP, 0, sizeof(MAP));
		cin >> R >> C >> N >> M;

		for (int i = 1; i <= N; i++) {
			cin >> robot[i].p.first >> robot[i].p.second;
			char ord; cin >> ord;
			switch (ord) {
			case 'W':
				robot[i].dir = W;
				break;
			case 'E':
				robot[i].dir = E;
				break;
			case 'S':
				robot[i].dir = S;
				break;
			case 'N':
				robot[i].dir = NN;
				break;
			}
			MAP[robot[i].p.first][robot[i].p.second] = i; //현재 로봇위치 기록
		}

		solve();
//	}

	return 0;
}
#endif
