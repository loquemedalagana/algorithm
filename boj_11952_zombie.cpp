#if 01
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
#include <functional>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;

#define SIZE (int)1e5
#define INF LLONG_MAX

int N, M, K, S; ll P, Q;
vector<int> Zombie;
int danger[SIZE + 10]; //위험한 도시 체크 (위험 1, 좀비 2)
ll check[SIZE + 10]; //나중에 최소 비용 저장(다익스트라)

vector<int> graph[SIZE + 10]; //경로 저장

struct Info {
	int pos, dist;
	Info(int pos, int dist) {
		this->pos = pos;
		this->dist = dist;
	}
	Info() {}
};

void check_danger(queue<Info> &q1) {
	while (!q1.empty()) {
		int cur = q1.front().pos, dist = q1.front().dist; q1.pop();
		for (int next : graph[cur]) {
			if (danger[next]) continue; //이미 위험한 도시 체크됨
			if (dist + 1 <= S) { //S번 이하로 이동 가능할 때
				danger[next] = 1;
				q1.push(Info(next, dist + 1));
			}
		}
	}
	//감염된 도시 체크 확인
#if 0
	printf("danger city\n");
	for (int i = 1; i <= N; i++) {
		printf("%d ", danger[i]);
	}
	printf("\n");
#endif
}

void solve() { //다익스트라 돌리기
	fill(check + 1, check + N + 1, INF); //최대값으로 초기화
	check[1] = 0LL;

	priority_queue<pli, vector<pli>, greater<pli> > pq; pq.push(make_pair(check[1], 1));

	while (!pq.empty()) {
		int cur = pq.top().second; ll cost = pq.top().first; pq.pop();

		for (int next : graph[cur]) {
			if (danger[next] == 2) {
				continue;
			}
			ll pay = danger[next] ? Q : P;
			
			if (check[next] > check[cur] + pay) {
				check[next] = check[cur] + pay;
				pq.push(make_pair(check[next], next));
			}
		}
	}

	//방문 경로 체크
#if 0
	for (int i = 1; i <= N; i++) {
		cout << check[i] << " ";
	}
	cout << '\n';
#endif

	ll ans = check[N];
	if (danger[N] == 1) ans -= Q;
	else ans -= P;

	cout << ans << '\n';
}

int main() {
	cin.tie(0); ios::sync_with_stdio(0); cin >> N >> M >> K >> S;
	cin >> P >> Q; Zombie.resize(K); 

	queue<Info> q1;

	for (int i = 0; i < K; i++) {
		cin >> Zombie[i]; //(사실 이건 굳이 배열 안 만들어도..)
		danger[Zombie[i]] = 2; // 여기에 체크만 해주면 됐음...
		q1.push(Info(Zombie[i], 0)); //좀비한테 점령당한 도시를 큐에 넣어준다
	}

	//그래프 경로 입력
	for (int i = 0; i < M; i++) {
		int from, to; cin >> from >> to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	
	check_danger(q1); //좀비의 영향을 받는 도시 만들기
	solve(); //다익스트라 부분

	return 0;
}
#endif
