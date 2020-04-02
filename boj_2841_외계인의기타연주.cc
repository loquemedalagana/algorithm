#include <iostream>
#include <stack>
using namespace std;
#define SIZE (int)5e5
int N, P;
int main() {
	cin.tie(0); ios::sync_with_stdio(0); cin >> N >> P; int ans = 0;
	stack<int> s[7]; //라인별로 있는 스택
	for (int i = 0; i < N; i++) {
		int curline, curP; cin >> curline >> curP;
		while (!s[curline].empty() && s[curline].top() > curP) {
			s[curline].pop();
			ans++;
		}
		if (s[curline].empty() || s[curline].top() < curP) {
			s[curline].push(curP);
			ans++;
		}
	}
	cout << ans << '\n';
	return 0;
}