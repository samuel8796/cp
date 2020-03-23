#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Vertex {
	int sp;
	char kind[5];
	int visit;
} vertexs;

// global variable
char transfer[1000][1000][4] = {'\0'};
int dot[1000][1000] = {0};

int transferTime(char *sourceKind, int from, int to) {

	if (strcmp(sourceKind, transfer[from][to]) == 0 || sourceKind[0] == '\0') {
		return 0;
	}
	else if (isupper(sourceKind[0]) && !isupper(transfer[from][to][0])) {
		return 5;
	}
	else if (!isupper(sourceKind[0]) && isupper(transfer[from][to][0])) {
		return 10;
	}
	else if (isupper(sourceKind[0]) && isupper(transfer[from][to][0])) {
		return 10;
	}
	else {
		return 5;
	}
}

int Dijkstra(int start, int end) {
	int i = 0;
	vertexs vertex[1000];

	for (i = 0; i < 1000; i++) {
		vertex[i].sp = 10000;
		vertex[i].visit = 0;
		strcpy(vertex[i].kind, "\0\0\0\0\0");
	}
	vertex[start].sp = 0;
	while (1) {
		int minValue = 10000;
		int minDot = 0;

		for (i = 0; i < 1000; i++) {
			if (!vertex[i].visit && vertex[i].sp < minValue) {
				minDot = i;
				minValue = vertex[i].sp;
			}
		}
		if (minValue == 10000)
			break;
		vertex[minDot].visit = 1;
		for (i = 0; i < 1000; i++) {
			if (dot[minDot][i] != 0 && !vertex[i].visit && (vertex[minDot].sp + dot[minDot][i] + transferTime(vertex[minDot].kind, minDot, i) < vertex[i].sp)) {
				vertex[i].sp = vertex[minDot].sp + dot[minDot][i] + transferTime(vertex[minDot].kind, minDot, i);
				strcpy(vertex[i].kind, transfer[minDot][i]);
			}
		}
	}

	return vertex[end].sp;
}

int main() {
	char symbol = '\0', kind[5] = {'\0'};
	int stationNum = 0;

	while (scanf("\n%c %s %d", &symbol, kind, &stationNum) != EOF) {
		int i = 0;

		if (symbol == 'L') {
			int start = 0, end = 0, time = 0;

			for (i = 0; i < stationNum; i++) {
				scanf("%d %d %d", &start, &end, &time);
				start--;
				end--;
				dot[start][end] = time;
				strcpy(transfer[start][end], kind);
			}
		}
		else if (symbol == 'Q') {
			int qStart = 0, qEnd = 0;
			int i = 0, k = 0, j = 0;
			int shortTime = -1;

			qStart = atoi(kind) - 1;
			qEnd = stationNum - 1;

			shortTime = Dijkstra(qStart, qEnd);
			if (shortTime == 10000) {
				printf("%d\n", -1);
			}
			else {
				printf("%d\n", shortTime);
			}
		}
	}

	return 0;
}
