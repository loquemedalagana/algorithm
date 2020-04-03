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
int danger[SIZE + 10]; //������ ���� üũ (���� 1, ���� 2)
ll check[SIZE + 10]; //���߿� �ּ� ��� ����(���ͽ�Ʈ��)

vector<int> graph[SIZE + 10]; //��� ����

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
			if (danger[next]) continue; //�̹� ������ ���� üũ��
			if (dist + 1 <= S) { //S�� ���Ϸ� �̵� ������ ��
				danger[next] = 1;
				q1.push(Info(next, dist + 1));
			}
		}
	}
	//������ ���� üũ Ȯ��
#if 0
	printf("danger city\n");
	for (int i = 1; i <= N; i++) {
		printf("%d ", danger[i]);
	}
	printf("\n");
#endif
}

void solve() { //���ͽ�Ʈ�� ������
	fill(check + 1, check + N + 1, INF); //�ִ밪���� �ʱ�ȭ
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

	//�湮 ��� üũ
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
		cin >> Zombie[i]; //(��� �̰� ���� �迭 �� ����..)
		danger[Zombie[i]] = 2; // ���⿡ üũ�� ���ָ� ����...
		q1.push(Info(Zombie[i], 0)); //�������� ���ɴ��� ���ø� ť�� �־��ش�
	}

	//�׷��� ��� �Է�
	for (int i = 0; i < M; i++) {
		int from, to; cin >> from >> to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	
	check_danger(q1); //������ ������ �޴� ���� �����
	solve(); //���ͽ�Ʈ�� �κ�

	return 0;
}
#endif
