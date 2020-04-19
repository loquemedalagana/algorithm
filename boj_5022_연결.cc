#if 01
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;
#define SIZE 101
typedef pair<int, int> pii;
typedef set<pii>::iterator it;

int R, C; int MAP[SIZE][SIZE], check[SIZE][SIZE]; //check 1, 2

struct Info {
	pii st, en;
};

Info P[2];
set<pii> PATH1[2], PATH2[2];

struct Node {
	pii p; set<pii> path;
};

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r <= R && c <= C;
}

void print() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << check[i][j] << ' ';
		}
		cout << '\n';
	}
}

set<pii> bfs(int idx, int step) { //idx == 0 -> A, idx == 1 -> B , step 1 A->B, step 2 B->A
	memset(check, 0, sizeof(check));
	check[P[idx].st.first][P[idx].st.second] = true;
	set<pii> imp; set<pii> pthh; pthh.insert(P[idx].st);
	queue<Node> q; q.push({ P[idx].st, pthh });

	while (!q.empty()) {
		int r = q.front().p.first, c = q.front().p.second;
		set<pii> path = q.front().path; q.pop();
		if (pii(r, c) == P[idx].en) {
		//	printf("%c's size %d\n", idx ? 'B' : 'A', path.size() - 1);
			return path;
		}

		for (int d = 0; d < 4; d++) {
			int nR = r + dr[d], nC = c + dc[d];
			if (!inRange(nR, nC) || check[nR][nC]) continue;
			if (pii(nR, nC) == P[(idx ^ 1)].st || pii(nR, nC) == P[idx ^ 1].en) continue;
			if (step == 1) {
				if (PATH1[idx ^ 1].find(pii(nR, nC)) != PATH1[idx ^ 1].end()) continue;
			}
			else if (step == 2) {
				if (PATH2[idx ^ 1].find(pii(nR, nC)) != PATH2[idx ^ 1].end()) continue;
			}

			pair<it, bool> okis = path.insert(pii(nR, nC));
			check[nR][nC] = true;
			q.push({ pii(nR, nC), path });

			if (okis.second == true) {
				path.erase(okis.first); //다음 for문이 돌면서 더 좋은 경우가 생길 경우
			}

		}
	}

	return imp; //최단 경로를 못 찾은 경우
}


int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> R >> C;

	for (int i = 0; i < 2; i++) {
		cin >> P[i].st.first >> P[i].st.second >> P[i].en.first >> P[i].en.second;
	}

	//먼저 지나갈 때 1 다음일때 B
	//A -> B
	//1. A bfs -> 성공하면 set를 경로에 저장 
	//2. B bfs -> 중간에 A랑 만나면 -1

	bool pt1ok = true, pt2ok = true;

	int len1 = 0, len2 = 0;

	for (int i = 0; i < 2; i++) {
		PATH1[i] = bfs(i, 1);// printf("idx %d size %d\n", i, PATH1[i].size());
		if (PATH1[i].empty()) {
			pt1ok = false;
			len1 = -1;
			break;
		}
		len1 += (PATH1[i].size() - 1);
	}

	//B -> A
	memset(check, 0, sizeof(check));

	for (int i = 1; i >= 0; i--) {
		PATH2[i] = bfs(i, 2); //printf("idx %d size %d\n", i, PATH2[i].size());
		if (PATH2[i].empty()) {
			pt2ok = false;
			len2 = -1;
			break;
		}
		len2 += (PATH2[i].size() - 1);
	}

	//	printf("%d %d\n", len1, len2);

	if (pt1ok && pt2ok) {
		printf("%d\n", min(len1, len2));
	}
	else if (pt1ok && !pt2ok) {
		printf("%d\n", len1);
	}
	else if (!pt1ok && pt2ok) {
		printf("%d\n", len2);
	}
	else {
		printf("IMPOSSIBLE\n");
	}

	return 0;
}
#endif