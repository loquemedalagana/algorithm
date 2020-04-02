#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define bool int
#define true 1
#define false 0

int dice[11]; //점수판 적힌거
int ord[11], ans; //순서 저장하기

typedef struct node {
	int num;
	int exist; //그냥 주사위 말 수로 기록;;;
	struct node *next1;
	struct node *next2; //10, 20, 30일때 외엔 NULL
} Node; //윷판에 적힐 것

Node way1[20]; //2~40 
Node way2[5]; //22~35
Node way3[3]; //13~19
Node way4[3]; //28~26
Node Head, Tail;

typedef struct p {
	int score;
	Node *pos; //pos->tail이면 도착함 이미
} Player;

Player player[5];

/*-------------------------여기까지 변수------------------------*/

void make_graph() {
	Head.num = 1, Tail.num = 41;
	Head.next2 = NULL, Head.next1 = &way1[0];
	Tail.next1 = NULL, Tail.next2 = NULL;

	//1. 맨 가에꺼 먼저 만들기
	for (int i = 0; i < 20; i++) {
		int val = (i + 1) * 2;
		way1[i].num = val;
		way1[i].exist = false;
		way1[i].next2 = NULL;

		if (i < 19) {
			way1[i].next1 = &way1[i + 1];
			//		printf("%x\n", way1[i].next1);
		}
		else if (i == 19) {
			way1[i].next1 = &Tail;
		}
	}
	way1[4].next2 = &way3[0];
	way1[9].next2 = &way2[0];
	way1[14].next2 = &way4[0];

	way1[19].next1 = way1[19].next2 = &Tail; //멈추는거 까먹음;;;;;;

	//2. 가운데꺼 만들기
	//구현의 편리성을 위하여 next2포인터를 살림
	way2[0].num = 22, way2[1].num = 24, way2[2].num = 25, way2[3].num = 30, way2[4].num = 35;
	for (int i = 0; i < 5; i++) {
		if (i == 4) {
			way2[i].next2 = &way1[19];
		}
		else {
			way2[i].next2 = &way2[i + 1];
		}
		way2[i].next1 = NULL;
	}

	way3[0].num = 13, way3[1].num = 16, way3[2].num = 19;
	way4[0].num = 28, way4[1].num = 27, way4[2].num = 26;

	way3[2].next2 = way4[2].next2 = &way2[2];
	way3[2].next1 = way4[2].next1 = NULL;

	for (int i = 0; i < 2; i++) {
		way3[i].next2 = &way3[i + 1];
		way4[i].next2 = &way4[i + 1];
		way3[i].next1 = way4[i].next1 = NULL;
	}

}

void init() { // 윷놀이 false처리, player 초기화
	//1. player 초기화
	for (int i = 1; i <= 4; i++) {
		player[i].pos = &Head; //시작점으로 돌리기
		player[i].score = 0;
	}

	Head.exist = false, Tail.exist = false;

	for (int i = 0; i < 20; i++) {
		way1[i].exist = false;
		if (i < 5) {
			way2[i].exist = false;
		}
		if (i < 3) {
			way3[i].exist = false;
			way4[i].exist = false;
		}
	}
}


#if 01
//갠적으로 중복 처리가 어려웠음....
void play(int cur, int loop, bool *flag) {
	Node *ptr = player[cur].pos; //일단 현재 위치 포인터로 받기.
	if (ptr == &Tail) return;

	//1. 현재 위치가 40일 때
	if (ptr->num == 40) {
		*flag = true;
		ptr->exist = false;
		player[cur].pos = &Tail; //도착처리
		return;
	}

	if (ptr == &Head) {
		for (int i = 0; i < loop; i++) {
			ptr = ptr->next1;
		}
	}
	else {
		if (ptr->next1 != NULL && ptr->next2 != NULL) {
			for (int i = 0; i < loop; i++) {
				if (ptr == &Tail) break;
				ptr = ptr->next2;
			}
		}
		else if (ptr->next1 != NULL && ptr->next2 == NULL) {
			for (int i = 0; i < loop; i++) {
				if (ptr == &Tail) break;
				ptr = ptr->next1;
			}
		}
		else if (ptr->next1 == NULL && ptr->next2 != NULL) {
			for (int i = 0; i < loop; i++) {
				if (ptr == &Tail) break;
				ptr = ptr->next2;
			}
		}
	}

	if (ptr->exist == false || ptr == &Tail) {
	//	printf("--moved--");
		player[cur].pos->exist = false;
		if (ptr != &Tail) {
			player[cur].score += (ptr->num);
			ptr->exist = cur;
		}
		player[cur].pos = ptr;
		*flag = true;
	}
	else {
		*flag = false;
	//	printf("---error----");
	}

}

//게임 진행 - int형으로 점수 출력
int solve() {
	int ret = 0; init();

	for (int i = 1; i <= 10; i++) {
		if (player[ord[i]].pos == &Tail) {
			continue;
		}
		bool okis = true;

		play(ord[i], dice[i], &okis);
		if (!okis) return -1;
	}

	for (int i = 1; i <= 4; i++) {
		ret += player[i].score;
	}

	return ret;
}
#endif

//순열 만들기
void go(int idx) {
	if (idx > 10) {
		init();
		int tempans = solve();
		
		if (ans <= tempans) {
			ans = tempans;
		}
		return;
	}

	for (int i = 1; i <= 4; i++) {
		ord[idx] = i;
		go(idx + 1);
	}
}

void input() {
	for (int i = 1; i <= 10; i++) scanf("%d", &dice[i]);
}


int main() {
	make_graph();
//	freopen("1.txt", "r", stdin);
	//입력
	input();
	go(1);
	printf("%d\n", ans);

	return 0;
}