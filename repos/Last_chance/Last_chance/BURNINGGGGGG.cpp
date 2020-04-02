#define _CRT_SECURE_NO_WARNINGS
//5901 relocation (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define INF (int)1e9
#define MAXN (int)1e4
#define MAXK 5
int N, M, K, markets[MAXK + 1], isMarket[MAXN+10];
int check[MAXK + 1][MAXN + 10]; //2차원 배열 아이디어어!! (문제의 핵심)
vector<pii> graph[MAXN + 10];

void bfs(int st) {
	priority_queue < pii, vector<pii>, greater<pii> > pq;
	pq.push(pii(0, markets[st]));
	while (!pq.empty()) {
		int cur = pq.top().second, curdist = pq.top().first; pq.pop();

		if (check[st][cur] <= curdist) continue;

		check[st][cur] = curdist;
		for (auto &n : graph[cur]) {
			if (check[st][n.second] > curdist + n.first) {
				pq.push(pii(curdist + n.first, n.second));
			}
		}
	}
}

void dijkstra(int start) //from a market
{
	priority_queue <pii, vector<pii>, greater<pii> > pq;
	pq.push(pii(0, markets[start]));

	while (!pq.empty()) //standard heap dijkstra
	{
		int curdist = pq.top().first;
		int curnode = pq.top().second;
		pq.pop();

		if (check[start][curnode] <= curdist)
			continue;

		check[start][curnode] = curdist;

		for (int i = 0; i < graph[curnode].size(); i++)
		{
			int nextnode = graph[curnode][i].second;
			int nextdist = graph[curnode][i].first + curdist;

			if (nextdist < check[start][nextnode])
				pq.push(pii(nextdist, nextnode));
		}
	}
}

void solve() {
	for (int k = 0; k < K; k++) {
		fill(check[k] + 1, check[k] + 1 + N, INF); //init
	//	for (int i = 1; i <= N; i++) check[k][i] = INF;
		bfs(k);
	//	dijkstra(k);
	}
#if 0
	for (int k = 0; k < K; k++) {
		printf("market %d -> ", k);
		for (int i = 1; i <= N; i++) {
			printf("%d ", check[k][i]);
		}
		printf("\n");
	}
#endif 
	vector<int> ord(K); for (int i = 0; i < K; i++) ord[i] = i;
	int ans = INF;
	//순열로 답 계산

	do {
		int tempans = INF;
		for (int i = 1; i <= N; i++) {
			if (isMarket[i]) continue;
			tempans = min(tempans, check[ord[0]][i] + check[ord[K - 1]][i]);
		}
		for (int i = 1; i < K; i++) {
			tempans += check[ord[i-1]][markets[ord[i]]];
		}
		printf("tempans %d\n", tempans);
		ans = min(ans, tempans);
	} while (next_permutation(ord.begin(), ord.end()));

	cout << ans << '\n';
}

int main() {
	freopen("5901.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		cin >> markets[i]; isMarket[markets[i]] = true;
	}
	while (M--) {
		int from, to, cost; cin >> from >> to >> cost;
		graph[from].push_back(pii(cost, to));
		graph[to].push_back(pii(cost, from));
	}
	solve();
	return 0;
}
#endif

//bomberman (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 200
int R, C, N, check[SIZE+10][SIZE+10];
vector<string> MAP;
/*
1. 초기상태
2. 다음 1초 아무것도 안함
3. 모든 칸에 설치
4. 3초전에 설치한게 폭발
*/

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < R && c < C;
}

void printstate() {
	printf("state\n");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			printf("%d ", check[i][j]);
		}
		printf("\n");
	}
}

void print() {
	for (int i = 0; i < R; i++) cout << MAP[i] << '\n';
}

void install() {
	memset(check, 0, sizeof(check));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (MAP[i][j] == 'O') {
				check[i][j] = 3;
			}
			else {
				MAP[i][j] = 'O';
				check[i][j] = 1;
			}
		}
	}
}

void bomb() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (check[i][j] == 3) { //이부분 실수 주의
				MAP[i][j] = '.'; // check[i][j] = 0;
				for (int d = 0; d < 4; d++) {
					int nR = i + dr[d], nC = j + dc[d];
					if (!inRange(nR, nC)) continue;
					MAP[nR][nC] = '.'; //check[nR][nC] = 0;
				}
			}
		}
	}
}

void solve() {
	for (int time = 2; time <= N; time++) {
		if (time % 2 == 0) { //모든 칸에 폭탄 설치
			install();
		}
		else { //폭발
			bomb();
		}
	//	printstate();
	}
	print();
}

int main() {
	freopen("16918.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> R >> C >> N; MAP.resize(R);
	for (int i = 0; i < R; i++) cin >> MAP[i];
	if (N == 1) {
		print();
	}
	else if (N>=2) {
		solve();
	}
	return 0;
}
#endif

//2336 https://www.acmicpc.net/board/view/33864 반례 참고 - 클래스!!!! (완성은 했지만..)
#if 0
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class SegmentTree {
public:
	SegmentTree(int n) : n(n) {
		tree.resize(pow(2, ceil(log2(n)) + 1), n);
	}

	inline int min(int left, int right) {
		return min(left, right, 1, 1, n);
	}
	inline void modify(int index, int value) {
		modify(index, value, 1, 1, n);
	}

private:
	int min(int left, int right, int node, int start, int end) {
		if (start == end || left <= start && right >= end)
			return tree[node];

		int res = n;

		if (left <= (start + end) / 2) {
			int temp = min(left, right, node * 2, start, (start + end) / 2);
			if (temp < res)
				res = temp;
		}

		if (right >= (start + end) / 2 + 1) {
			int temp = min(left, right, node * 2 + 1, (start + end) / 2 + 1, end);
			if (temp < res)
				res = temp;
		}

		return res;
	}
	void modify(int index, int value, int node, int start, int end) {
		if (tree[node] > value)
			tree[node] = value;

		if (start == end)
			return;
		else if (index <= (start + end) / 2)
			modify(index, value, node * 2, start, (start + end) / 2);
		else
			modify(index, value, node * 2 + 1, (start + end) / 2 + 1, end);
	}

private:
	int n;
	vector<int> tree;
};

struct Student {
	int x, y, z;
};

const int MAX_N = 500001;
int n, t;
vector<Student> arr;

bool Cmp(const Student& st1, const Student& st2) { return st1.x < st2.x; }

int main() {
	freopen("2336.txt", "r", stdin);
	cin.tie(0);	ios::sync_with_stdio(0);

	cin >> n;
	arr.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> t;
		arr[t].x = i;
	}
	for (int i = 1; i <= n; i++) {
		cin >> t;
		arr[t].y = i;
	}
	for (int i = 1; i <= n; i++) {
		cin >> t;
		arr[t].z = i;
	}

	sort(arr.begin(), arr.end(), Cmp);

	SegmentTree segmentTree(n);
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (segmentTree.min(1, arr[i].y) >= arr[i].z)
			cnt++;
		segmentTree.modify(arr[i].y, arr[i].z);
	}
	cout << cnt << '\n';

	return 0;
}

#endif

//cheeze https://jm25.tistory.com/84
//망한 소스
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 1000
int R, C, N; pii st;
char MAP[SIZE + 10][SIZE + 10];
int check[SIZE + 10][SIZE + 10];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

struct Info {
	pii p; int num; bool isExist;
	Info(pii p, int num, bool isExist) {
		this->p = p;
		this->num = num;
		this->isExist = isExist;
	}
	Info() {}
};

vector<Info> cheeze;

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < R && c < C;
}

bool cmp1(const Info &a, const Info &b) {
	return a.num < b.num;
}

void print() {
	printf("state\n");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << check[i][j] << " ";
		}
		cout << '\n';
	}
}

void solve() {
	int time = 0, Eaten = 0, level = 1; //Eaten -> 이미 먹은 치즈 수, level 능력치
	sort(cheeze.begin(), cheeze.end(), cmp1);
	queue<pii> q; q.push(st);
	check[st.first][st.second] = 1;

	//for (auto &p : cheeze) {
	//	printf("pos(%d, %d), num %d\n", p.p.first, p.p.second, p.num);
	//}

	for (int i = 0; i < N; i++) {
		queue<pii> q; memset(check, 0, sizeof(check));
		check[st.first][st.second] = 1; q.push(st);

		while (!q.empty()) {
			int r = q.front().first, c = q.front().second; q.pop();

			if (MAP[r][c]-'0' == level) {
				st = cheeze[i].p; level++; time += check[r][c] - 1;
				//	print();
				break;
			}

			for (int d = 0; d < 4; d++) {
				int nR = r + dr[d], nC = c + dc[d];
				if (!inRange(nR, nC)) continue;
				if (!check[nR][nC] && MAP[nR][nC] != 'X') {
					check[nR][nC] = check[r][c] + 1;
					q.push(make_pair(nR, nC));
				}
			}
		}
	}

	cout << time << '\n';
}

int main() {
	freopen("5558.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> R >> C >> N;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'S') {
				st = make_pair(i, j);
			}
			else if (MAP[i][j] >= '0' && MAP[i][j] <= '9') {
				cheeze.push_back(Info(make_pair(i, j), MAP[i][j] - '0', true));
			}
		}
	}
	//	cout << cheeze.size() << '\n';
	solve();
	return 0;
}
#endif
//다시 (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 1000
int R, C, N; pii st;
char MAP[SIZE + 10][SIZE + 10];
int check[SIZE + 10][SIZE + 10];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

struct Info {
	pii p; int num; bool isExist;
	Info(pii p, int num, bool isExist) {
		this->p = p;
		this->num = num;
		this->isExist = isExist;
	}
	Info() {}
};

vector<Info> cheeze;

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < R && c < C;
}

bool cmp1(const Info &a, const Info &b) {
	return a.num < b.num;
}

void print() {
	printf("state\n");
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << check[i][j] << " ";
		}
		cout << '\n';
	}
}

void solve() {
	int time = 0, Eaten = 0, level = 1; //Eaten -> 이미 먹은 치즈 수, level 능력치
	sort(cheeze.begin(), cheeze.end(), cmp1);
	queue<pii> q; q.push(st);
	check[st.first][st.second] = 1;

	//for (auto &p : cheeze) {
	//	printf("pos(%d, %d), num %d\n", p.p.first, p.p.second, p.num);
	//}

	for (int i = 0; i < cheeze.size(); i++) {
		queue<pii> q; memset(check, 0, sizeof(check));
		check[st.first][st.second] = 1; q.push(st);

		while (!q.empty()) {
			int r = q.front().first, c = q.front().second; q.pop();

			if (pii(r, c) == cheeze[i].p) {
				st = cheeze[i].p; level++; time += check[r][c] - 1;
			//	print();
				break;
			}

			for (int d = 0; d < 4; d++) {
				int nR = r + dr[d], nC = c + dc[d];
				if (!inRange(nR, nC)) continue;
				if (!check[nR][nC] && MAP[nR][nC] != 'X') {
					check[nR][nC] = check[r][c] + 1;
					q.push(make_pair(nR, nC));
				}
			}
		}
	}

	cout << time << '\n';
}

int main() {
	freopen("5558.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> R >> C >> N;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 'S') {
				st = make_pair(i, j);
			}
			else if (MAP[i][j] >= '0' && MAP[i][j] <= '9') {
				cheeze.push_back(Info(make_pair(i, j), MAP[i][j] - '0', true));
			}
		}
	}
	//	cout << cheeze.size() << '\n';
	solve();
	return 0;
}
#endif

//1189 come back home (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
char MAP[7][7]; int N, M, K, ans, distt;
int check[7][7]; pii st, en;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

bool inRange(int r, int c) {
	return r >= 1 && c >= 1 && r <= N && c <= M;
}

void dfs(int r, int c, int dist) {
	if (dist == K && pii(r, c) == en) {
		ans++;
		return;
	}

	for (int d = 0; d < 4; d++) {
		int nR = r + dr[d], nC = c + dc[d];
		if (!check[nR][nC] && inRange(nR, nC) && MAP[nR][nC] != 'T') {
			check[nR][nC] = true;
			dfs(nR, nC, dist + 1);
			check[nR][nC] = false;
		}
	}

}

int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> N >> M >> K;
	st = pii(N, 1), en = pii(1, M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> MAP[i][j];
	//		cout << MAP[i][j];
		}
	}

	memset(check, 0, sizeof(check));
	check[st.first][st.second] = 1;
	dfs(st.first, st.second, 1);

	cout << ans << '\n';

	return 0;
}
#endif

//완료
#if 0
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
typedef long long ll;
using namespace std;
#define SIZE (int)1e5
int N; ll v;

int main() {
	cin.tie(0); ios::sync_with_stdio(0); cout.tie(0);
	int N; cin >> N; vector<ll> A(N); ll res = 0LL;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		if (A[i] >= 0) res = max(res, i - v);
		v += A[i];
	}
	ll ans = 0LL;
	for (ll i = 0; i < (ll)N; i++) {
		while (A[(int)i]--) {
			ans += pow(res - i, 2LL);
			res++;
		}
	}
	cout << ans << '\n';
}
#endif

//14324 (미완)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define SIZEN 10
#define INF (int)1e9
int T, R, C;
int MAP[SIZEN + 5][SIZEN + 5], check[SIZEN + 5][SIZEN + 5], ans, MAXH;
int backup[SIZEN + 5][SIZEN + 5];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void print() {
	for (int i = 0; i <= R + 1; i++) {
		for (int j = 0; j <= C + 1; j++) {
			cout << MAP[i][j] << " ";
		}
		cout << '\n';
	}
}

void dfs(int r, int c, vector<pii> &area, int num) {
	area.push_back(pii(r, c));
	check[r][c] = num;
	for (int d = 0; d < 4; d++) {
		int nR = r + dr[d], nC = c + dc[d];
		if (check[nR][nC]) continue;
		if (MAP[nR][nC] == MAP[r][c]) {
			dfs(nR, nC, area, num);
		}
	}
}

void solve(int tc) {
	memcpy(backup, MAP, sizeof(MAP));
	int ans = 0, num = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			bool ok = true; 
			for (int d = 0; d < 4; d++) {
				int nR = i + dr[d], nC = j + dc[d];
				if (MAP[nR][nC] < MAP[i][j]) {
					ok = false;
				}
			}
			if (ok && !check[i][j]) {
				int MINH = INF;
				printf("cur pos (%d, %d)\n", i, j);
				//영역 플러드 필로 구하기
				vector<pii> area;
				dfs(i, j, area, ++num);
				cout << area.size() << "\n";

				for (auto &p : area) {
					int r = p.first, c = p.second;
					for (int d = 0; d < 4; d++) {
						int nR = r + dr[d], nC = c + dc[d];
						if (MAP[nR][nC] < MAP[r][c]) ok = false;
						else if (MAP[nR][nC] > MAP[r][c]) MINH = min(MAP[nR][nC], MINH);
					}
				}
				if (ok) {
					printf("minh %d, nowh %d\n", MINH, MAP[i][j]);
				//	ans += (area.size())*(MINH - MAP[i][j]);
					for (auto &p : area) {
						int r = p.first, c = p.second;
						MAP[r][c] = MINH;
						check[r][c] = 0;
					}
					printf("changed\n");
					print();
				}
			}
		}
	}

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (backup[i][j] == MAP[i][j]) continue;
			else ans += (MAP[i][j] - backup[i][j]);
		}
	}

	cout << "Case #" << tc << ": " << ans << '\n';
}

void input() {
	memset(MAP, 0, sizeof(MAP)); memset(check, 0, sizeof(check));
	cin >> R >> C; ans = 0; MAXH = -INF;
	fill(MAP[0], MAP[0] + C + 2, 0);
	fill(MAP[R + 1], MAP[R + 1] + C + 2, 0);
	for (int i = 0; i < R + 1; i++) MAP[i][0] = MAP[i][C + 1] = 0;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> MAP[i][j];
			MAXH = max(MAXH, MAP[i][j]);
		}
	}
}

int main() {
	freopen("14324.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		input();
		solve(tc);
	}
	return 0;
}
#endif

//10653 말아톤2 (아직 다 안품!) - 완료 => 나중에 정리하기
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define SIZE 500
#define INF (int)1e9
typedef pair<int, int> pii;
int N, K; pii p[SIZE + 10]; int dp[SIZE + 10][SIZE + 10];

int calc(pii a, pii b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
	freopen("10655.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> p[i].first >> p[i].second;
	}
	//순서대로
	for (int i = 0; i <= K; i++) fill(dp[i], dp[i] + N, INF);
	dp[0][0] = 0;
	//최대 K개까지 건너뛸 수 있다. => 더 작은거도 가능
	for (int k = 0; k <= K; k++) {
		for (int from = 0; from < N - 1; from++) {
			for (int to = from + 1; to < N, k + (to - from - 1) <= K; to++) { //다음
				int omit = k + (to - from - 1);
				dp[omit][to] = min(dp[omit][to], dp[k][from] + calc(p[from], p[to]));
			}
		}
	}

	cout << dp[K][N-1] << '\n';
	return 0;
}
#endif

//circular barn (다시 풀기)
#if 0
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
typedef long long ll;
using namespace std;
#define SIZE (int)1e5
int N;

ll calc(ll val) {
	return val * (val + 1) * (2 * val + 1) / 6;
}

int main() {
	freopen("ip.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cout.tie(0);
	int N; cin >> N; vector<ll> A(N);
	int c = 0;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		c = max(0LL, c + A[i] - 1);
		cout << A[i] << " " << c << " " << c + A[i] - 1 << '\n';
	}
	cout << " next\n";
	for (int i = 0; ; i++) {
		if (c == 0) {
			rotate(A.begin(), A.begin() + i, A.begin() + N);
			break;
		}
		c = max(0LL, c + A[i] - 1);
		cout << A[i] << " " << c << '\n';
	}

	ll ans = 0;
	for (int i = 0; i < N; i++) {
		ans += calc(A[i] + c - 1) - calc(c - 1);
		c = max(0LL, c + A[i] - 1);
	}
	cout << ans << '\n';
}
#endif

//18808 - 바킹독 모의1 (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef vector<vector<int> > myarr;
#define SIZE 40
#define MAXK 100
int N, M, K, MAP[SIZE + 10][SIZE + 10];
int check[SIZE + 10][SIZE + 10];

#if 0
void print(int idx) {
	printf("idx %d\n", idx + 1);
	for (auto &mv : PAPER[idx]) {
		for (auto &vv : mv) {
			for (int vvv : vv) {
				cout << vvv << " ";
			}
			cout << '\n';
		}
		cout << '\n';
	}
}
#endif

void print(myarr &v) {
	for (auto &vv : v) {
		for (int vvv : vv) {
			cout << vvv << " ";
		}
		cout << '\n';
	}
}

void pp() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << MAP[i][j] << " ";
		}
		cout << '\n';
	}
}

myarr rot(myarr &v, int &R, int &C) {
	myarr ret;
	for (int j = 0; j < C; j++) {
		vector<int> temp;
		for (int i = R - 1; i >= 0; i--) {
			temp.push_back(v[i][j]);
		}
		ret.push_back(temp);
	}
	swap(R, C);
	return ret;
}

int paste(myarr &v, int num, int R, int C, int loop) {
	if (loop > 4) return 0;
//	printf("%d %d\n", R, C);
	bool ok = false;
	for (int i = 0; i < N-R+1; i++) {
		for (int j = 0; j < M-C+1; j++) {
			ok = true;
			for (int k = i; k < i + R; k++) {
				for (int l = j; l < j + C; l++){
				//	printf("%d %d %d %d\n",i, j, k, l);
					int ix = k - i, jx = l - j;
				//	printf("%d, %d\n", ix, jx);

					if (v[ix][jx]) {
						if (MAP[k][l]) { //이미 스티커 붙여짐
							ok = false;
							break;
						}
					}
				}
			}

			if (ok) {
				int cnt = 0;
				for (int k = i; k < i + R; k++) {
					for (int l = j; l < j + C; l++) { //너의 손가락을 탓하라
						int ix = k - i, jx = l - j;
						if (v[ix][jx]) {
							MAP[k][l] = num;
							cnt++;
						}
					}
				}
				return cnt;
			}
//		G1:
		}
	}
	if (!ok) {
	//	printf("failed\n");
		myarr v2 = rot(v, R, C);
		int temp = paste(v2, num, R, C, loop+1);
		if (temp) return temp;
	//	else if (loop >= 4) return 0;
	}

	return 0;
}

int main() {
	freopen("18808.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> N >> M >> K;
	int ans = 0;
	for (int k = 0; k < K; k++) {
		int R, C; cin >> R >> C;
		myarr v(R, vector<int>(C, 0));
		int siz = max(R, C);

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> v[i][j];
			}
		}
		
		//일단 붙여보고, 안되면 돌리기
	//	myarr tmp = rot(v, R, C);
		//paste
		int tmp = paste(v, k + 1, R, C, 1);
		//if (tmp) {
		//	printf("now %d\n", tmp);
		//	pp();
		//}
		ans += tmp;
	}
	cout << ans << '\n';
	return 0;
}
#endif

//2174 로봇시뮬레이션 (완료)
#if 0
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
	freopen("2174.txt", "r", stdin); 
	cin.tie(0); ios::sync_with_stdio(0);
	int T; cin >> T;
	while (T--) {
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
	}

	return 0;
}
#endif

//1495 기타리스트 (완료)
#if 0
#include <cstdio>
#include <algorithm>
using namespace std;
int dp[110][1200], v[110], N, S, M;
int main() {
	scanf("%d %d %d", &N, &S, &M);
	for (int i = 1; i <= N; i++) scanf("%d", &v[i]);
	//i번째 곡에 j볼륨 가능하면 true
	dp[0][S] = true; //초기 볼륨
	int MXidx = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			if (dp[i][j]) {
				if (j + v[i + 1] <= M) {
					dp[i + 1][j + v[i + 1]] = true;
					if(i+1 == N) MXidx = max(j + v[i + 1], MXidx);
				}
				if (j - v[i + 1] >= 0) {
					dp[i + 1][j - v[i + 1]] = true;
				}
			}
		}
	}
#if 0
	printf("%d\n", MXidx);
	for (int i = 0; i <= N; i++) {
		printf("idx %d => ", i);
		for (int j = 0; j <= M; j++) {
			printf("%d ", dp[i][j]);
		}
		printf("\n");
	}
#endif
	printf("%d\n", MXidx);
	return 0;
}
#endif

//17025 - ice parameter (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 1001
char MAP[SIZE + 10][SIZE + 10];
int N, check[SIZE+10][SIZE+10];
int num[SIZE*SIZE + 20], MXN; //넓이 저장하기
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
vector<pii> lands[SIZE*SIZE + 2];
bool ALLfill;

bool inRange(int r, int c) {
	return r >= 1 && c >= 1 && r <= N && c <= N;
}

void dfs(int r, int c, int cnt) {
	check[r][c] = cnt;
	lands[cnt].push_back(make_pair(r, c));
	num[cnt]++;
	for (int d = 0; d < 4; d++) {
		int nR = r + dr[d], nC = c + dc[d];
		if (inRange(nR, nC) && !check[nR][nC] && MAP[nR][nC] == '#') {
			dfs(nR, nC, cnt);
		}
	}
}

void print() {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			printf("%1d", check[i][j]);
		}
		printf("\n");
	}
}

void solve() {
	int cntt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (check[i][j] || MAP[i][j] != '#') continue;
			dfs(i, j, ++cntt);
		}
	}
	MXN = *max_element(num + 1, num + (N*N) + 1);
	int pari = (int)1e9;
//	print();

	vector<int> lgidx;
	//가장 큰 넘버 인덱스 저장
	for (int i = 1; i <= cntt; i++) { //갯수 세놓고 까먹음 -_-
		if (num[i] == MXN) lgidx.push_back(i);
	}

	for (int ix : lgidx) {
		int temp = 0;
		for (auto &p : lands[ix]) {
			for (int d = 0; d < 4; d++) {
				int nR = p.first + dr[d], nC = p.second + dc[d];
				if (!check[nR][nC]) {
					temp++;
				}
			}		
		}
		pari = min(pari, temp);
	}

	printf("%d %d\n", MXN, pari);
}

int main() {
	freopen("17025.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> N;
	ALLfill = true;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == '.') ALLfill = false;
		}
	}
	if (ALLfill) printf("%d %d\n", N*N, N * 4);
	else solve();

	return 0;
}
#endif

//15235 pizza (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 1001
int N, a[SIZE + 1], res[SIZE + 1];

int main() {
	cin.tie(0); ios::sync_with_stdio(0); cin >> N;
	queue<int> q;
	for (int i = 1; i <= N; i++) {
		cin >> a[i]; q.push(i);
	}
	int time = 0;
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		a[cur]--;
		if (a[cur] > 0) {
			q.push(cur);
		}
		printf("now %d, time %d\n", cur, time + 1);
		res[cur] = ++time;
	}
	for (int i = 1; i <= N; i++) printf("%d ", res[i]); printf("\n");
	return 0;
}
#endif

//좋은 수 (완료)
#if 0
#include <cstdio>
#include <set>
using namespace std;
typedef pair<int, pair<int, int> > pii;
const int MAXN = 20000;
int a[5001], N, ans;
bool check[MAXN * 2 + 10];

int main() {
	scanf("%d", &N); for (int i = 0; i < N; i++) scanf("%d", &a[i]);
	int ans = 0;
	//x + y = k - z
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			int KminusZ = a[i] - a[j];
			if (check[KminusZ + MAXN]) {
				ans++;
				break;
			}
		}
		for (int j = 0; j <= i; j++) {
			check[a[i] + a[j] + MAXN] = true;
		}
	}
	printf("%d\n", ans);
	return 0;
}
#endif

//9205 beer (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
int ans, N, enidx; int check[110];
vector<pii> path;
int graph[110][110];

int calc(int cur, int next) {
	pii c = path[cur], n = path[next];
	return abs(c.first - n.first) + abs(c.second - n.second);
}

bool dfs(int cur) {
	if (cur == enidx) return true;
	check[cur] = true;
	for (int next = 1; next <= enidx; next++) {
		if (cur == next || check[next]) continue;
		if (graph[cur][next] == 0 || graph[cur][next] > 50 * 20) continue;
		if (dfs(next)) return true;
	}
	return false;
}

void make_graph() {
	for (int i = 0; i < enidx; i++) {
		for (int j = i + 1; j <= enidx; j++) {
			graph[i][j] = graph[j][i] = calc(i, j);
		}
	}
}

void input() {
	path.clear(); memset(check, 0, sizeof(check));
	ans = (int)1e9; cin >> N; path.resize(N+2); //도착점 = N+1
	enidx = N + 1;
	for (int i = 0; i <= N + 1; i++) {
		cin >> path[i].first >> path[i].second;
	}
	if (calc(0, enidx) <= 50 * 20) {
		printf("happy\n");
		return;
	}
	else {
		if (N == 0) {
			printf("sad\n");
			return;
		}
		make_graph();
		printf("%s\n", dfs(0) ? "happy" : "sad");
	}
}

int main() {
	cin.tie(0); ios::sync_with_stdio(0); int T; cin >> T;
	while (T--) {
		input();
	}
	return 0;
}
#endif

//2638 cheeze (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 100
int MAP[SIZE + 10][SIZE + 10], N, M;
int check[SIZE + 10][SIZE + 10];

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < N && c < M;
}

void print() {
	printf("map now \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << MAP[i][j] << " ";
		}
		cout << '\n';
	}
	printf("check now \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << check[i][j] << " ";
		}
		cout << '\n';
	}
}

void search_line() {
	memset(check, 0, sizeof(check));
	queue<pii> q; q.push(pii(0, 0));
	q.push(pii(0, M - 1)); q.push(pii(N - 1, 0)); q.push(pii(N - 1, M - 1));
	check[0][0] = check[0][M - 1] = check[N - 1][0] = check[N - 1][M - 1] = true;

	while (!q.empty()) {
		int r = q.front().first, c = q.front().second; q.pop();

		for (int d = 0; d < 4; d++) {
			int nR = r + dr[d], nC = c + dc[d];
			if (inRange(nR, nC) && MAP[nR][nC] != 1 && check[nR][nC] == 0) {
				check[nR][nC] = true;
				q.push(make_pair(nR, nC));
			}
		}
	}
}

int melt() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 1) {
				int cnt = 0;
				for (int d = 0; d < 4; d++) {
					int nR = i + dr[d], nC = j + dc[d];
					if (!inRange(nR, nC) || check[nR][nC] == 1) {
						cnt++;
					}
				}
				if (cnt >= 2) {
					MAP[i][j] = 2;
					ret++;
				}
			}
		}
	}
	return ret;
}

void solve(int total) {
	int time = 1;
	//1. 가장자리 탐색하기 -> bfs
	while (true) {
		printf("before total %d\n", total);
		search_line();
		print();
		total -= melt();
		print();
		printf("after total %d\n", total);
		if (total == 0) break;
		time++;
	}
	cout << time << '\n';
}

int main() {
	freopen("2638.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> N >> M;
	int originalcnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 1) originalcnt++;
		}
	}
	solve(originalcnt);
	return 0;
}
#endif

//15591 motuve (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
#include <climits>
#include <cstring>
using namespace std;
#define INF (int)1e9 + 1
#define SIZE 5000
typedef pair<int, int> pii;
vector<pii> graph[SIZE + 10];
int check[SIZE + 10];
int N, Q;

int solve(int K, int pos) {
	int ret = 0;
	memset(check, 0, sizeof(check));
//	fill(check + 1, check + N + 1, INF);
	queue<int> q; q.push(pos); check[pos] = INF;

	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (auto &n : graph[cur]) {
			int next = n.second; int dist = n.first;
			if (!check[next]) {
				check[next] = min(check[cur], dist);
				q.push(next);
			}
		}
	}

//	printf("start %d\n", pos);

	for (int i = 1; i <= N; i++) {
	//	cout << check[i] << " ";
		if (check[i] != INF && check[i] >= K) ret++;
	}
//	cout << '\n';

	return ret;
}

int main() {
	freopen("15591.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); 
	cin >> N >> Q;
	for (int i = 0; i < N-1; i++) {
		int u, v; int cost; cin >> u >> v >> cost;
		graph[u].push_back(pii(cost, v));
		graph[v].push_back(pii(cost, u));
	}
	for (int i = 0; i < Q; i++) {
		int dist; int from; cin >> dist >> from;
	//	cout << dist << " " << from << '\n';
		int tempans = solve(dist, from);
		cout << tempans << '\n';
	}
	return 0;
}
#endif

//13659 robot (완료)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 100
#define NN 0
#define SS 1
#define EE 2
#define WW 3

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

char MAP[SIZE + 10][SIZE + 10];
int check[SIZE + 10][SIZE + 10], N, M, K;

string ord;

struct Info {
	pii p; int dir, cnt;
	Info(pii p, int dir, int cnt) {
		this->p = p;
		this->dir = dir;
		this->cnt = cnt;
	}
	Info() {}
};

Info robot;

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < N && c < M;
}

int turn(int dir) {
	switch (dir) {
	case NN:
		return WW;
	case SS:
		return EE;
	case EE:
		return NN;
	case WW:
		return SS;
	}
}

int solve() {
	MAP[robot.p.first][robot.p.second] = '.';

	for (int i = 0; i<ord.size(); i++) {
		int &r = robot.p.first, &c = robot.p.second, &dir = robot.dir;
		cout << ord[i] << ' ';
		printf("cur %d robot (%d, %d), dir %d\n", i, r, c, dir);
		if (ord[i] == 'F') { //앞으로
			int nR = r + dr[dir], nC = c + dc[dir];
			if (MAP[nR][nC] == '#' || !inRange(nR, nC)) continue;
			else {
				cout << "next => " << MAP[nR][nC] << "\n";
				if (MAP[nR][nC] == '*') {
					MAP[nR][nC] = '.';
					robot.cnt += 1;
					printf("collected %d\n", robot.cnt);
				}
				r = nR, c = nC;
			}
		}
		else { //방향만 전환
			dir = turn(dir);
			if (ord[i] == 'D') dir ^= 1;
		}
	}
	printf("result %d\n", robot.cnt);
	return robot.cnt;
}

int main() {
	freopen("13659.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0);
	while (true) {
		memset(MAP, 0, sizeof(MAP)); ord.clear();
		cin >> N >> M >> K; robot.cnt = 0;
		if (N == 0 && M == 0 && K == 0) break;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> MAP[i][j];
				switch (MAP[i][j]) {
				case 'N':
					robot.p = make_pair(i, j);
					robot.dir = NN;
					break;
				case 'S':
					robot.p = make_pair(i, j);
					robot.dir = SS;
					break;
				case 'L':
					robot.p = make_pair(i, j);
					robot.dir = EE;
					break;
				case 'O':
					robot.p = make_pair(i, j);
					robot.dir = WW;
					break;
				}
			}
		}
		cin >> ord;
		
		cout << solve() << '\n';

	}

	return 0;
}
#endif

//18809 garden 완료
#if 01
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 50
#define GG 0
#define RR 1
#define ORIG 2
//배양액 나타낼 배열
int N, M, G, R, SUM;
int MAP[3][SIZE + 2][SIZE + 2], ans;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
vector<pii> land;

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < N && c < M && MAP[2][r][c];
}

int solve(int Gmsk, int Rmsk) {
	memset(MAP[GG], 0, sizeof(MAP[GG])); //init
	memset(MAP[RR], 0, sizeof(MAP[RR]));

	queue<pii> q;	int cnt = 0;
	set<pii> flower;

	int Rcnt = 0, Gcnt = 0;
	for (int i = 0; i < land.size(); i++) {
		if (Rmsk & (1 << i)) {
			MAP[RR][land[i].first][land[i].second] = 1;
			q.push(land[i]); Rcnt++;
		}
		else if (Gmsk & (1 << i)) {
			MAP[GG][land[i].first][land[i].second] = 1;
			q.push(land[i]); Gcnt++;
		}
	}
	if (Rcnt != R || Gcnt != G) return -1;

#if 01
	while (!q.empty()) {
		int r = q.front().first, c = q.front().second; q.pop();
		bool isRed = MAP[RR][r][c], isGreen = MAP[GG][r][c];

		for (int d = 0; d < 4; d++) {
			int nR = r + dr[d], nC = c + dc[d];
			if (!inRange(nR, nC)) continue;
			if (isRed && !isGreen && !MAP[RR][nR][nC]) {
				if (MAP[GG][nR][nC] == MAP[RR][r][c]) continue;
				MAP[RR][nR][nC] = MAP[RR][r][c] + 1;
				if (!MAP[GG][nR][nC]) q.push(make_pair(nR, nC));
				else flower.insert(make_pair(nR, nC));
			}
			else if (isGreen && !isRed && !MAP[GG][nR][nC]) {
				if (MAP[RR][nR][nC] == MAP[GG][r][c]) continue;
				MAP[GG][nR][nC] = MAP[GG][r][c] + 1;
				if (!MAP[RR][nR][nC]) q.push(make_pair(nR, nC));
				else flower.insert(make_pair(nR, nC));
			}
		}
	}
#endif
	return cnt = flower.size();
}

void go(int idx, int Gcnt, int Rcnt, int Gmsk, int Rmsk) {
	if (Gcnt == G && Rcnt == R) {
		ans = max(ans, solve(Gmsk, Rmsk));
		return;
	}
	if (idx >= land.size()) return;
	if(Gcnt < G) go(idx + 1, Gcnt + 1, Rcnt, Gmsk | (1 << idx), Rmsk);
	if(Rcnt < R) go(idx + 1, Gcnt, Rcnt + 1, Gmsk, Rmsk | (1 << idx));
	go(idx + 1, Gcnt, Rcnt, Gmsk, Rmsk);
}

int main() {
	freopen("18809.txt", "r", stdin);
	cin.tie(0); ios::sync_with_stdio(0); cin >> N >> M >> G >> R;
	SUM = G + R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[2][i][j];
			if (MAP[2][i][j] == 2) {
				land.push_back(make_pair(i, j));
			}
		}
	}
	go(0, 0, 0, 0, 0);
	cout << ans << '\n';

	return 0;
}
#endif

//달팽이 심화 (했지만..)
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
typedef unsigned long long u64;

int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	u64 R, C; cin >> R >> C; u64 crit = min(R - 1, C);
	u64 curve = 1 + (crit - 1) * 2; u64 pos = min(R, C) / 2;
	u64 nR, nC; nR = R / 2 + 1, nC = (C / 2) - ((C + 1) % 2) + 1;
	
	if (R > C) {
		cout << curve << '\n';
		if (C % 2 == 0) cout << pos + 1; else cout << R - pos;
		cout << " " << nC << '\n';
	}
	else if (R == C) {
		cout << curve + 1 << '\n';
		cout << nR << " " << nC << '\n';
	}
	else {
		cout << curve + 1 << '\n';
		cout << nR << " ";
		if (R % 2 == 0) cout << pos; else cout << C - pos;
	}

	return 0;
}
#endif
