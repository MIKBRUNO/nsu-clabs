#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dijkstra.h"

#define BUFSIZE 1024

int main(void) {
	char buf[BUFSIZE];

	if (NULL == fgets(buf, BUFSIZE, stdin)) {
		puts("bad number of lines");
		return 0;
	}
	unsigned int vcount = atoi(buf);
	if (5000 < vcount) {
		puts("bad number of vertices");
		return 0;
	}

	int v0 = 0;
	int v1 = 0;

	if (NULL == fgets(buf, BUFSIZE, stdin)) {
		puts("bad number of lines");
		return 0;
	} 
	v0 = atoi(buf);
	if ((int)vcount < v0 || 1 > v0) {
		puts("bad vertex");
		return 0;
	}
	unsigned int st = (unsigned int)v0 - 1u;

	char* b1 = strchr(buf, ' ') + 1;
	if (NULL == b1) {
		puts("bad number of lines");
		return 0;
	}
	v1 = atoi(b1);
	if ((int)vcount < v1 || 1 > v1) {
		puts("bad vertex");
		return 0;
	}
	unsigned fin = (unsigned int)v1 - 1u;

	if (NULL == fgets(buf, BUFSIZE, stdin)) {
		puts("bad number of lines");
		return 0;
	}
	unsigned int ecount = atoi(buf);
	if (ecount > vcount * (vcount - 1) / 2) {
		puts("bad number of edges");
		return 0;
	}

	int* adjm = malloc(vcount * vcount * sizeof(int));
	if (NULL == adjm) {
		puts("cant allocate");
		return 0;
	}
	for (size_t i = 0; i < vcount * vcount; ++i)
		adjm[i] = -1;

	for (size_t i = 0; i < ecount; ++i) {
		if (NULL == fgets(buf, BUFSIZE, stdin)) {
			puts("bad number of lines");
			free(adjm);
			return 0;
		}
		char* b1 = strchr(buf, ' ') + 1;
		if (NULL == b1) {
			puts("bad number of lines");
			free(adjm);
			return 0;
		}
		char* b2 = strchr(b1, ' ') + 1;
		if (NULL == b2) {
			puts("bad number of lines");
			free(adjm);
			return 0;
		}
		v0 = atoi(buf);
		if ((int)vcount < v0 || 1 > v0) {
			puts("bad vertex");
			free(adjm);
			return 0;
		}
		v0 -= 1;
		v1 = atoi(b1);
		if ((int)vcount < v1 || 1 > v1) {
			puts("bad vertex");
			free(adjm);
			return 0;
		}
		v1 -= 1;
		adjm[v0 * vcount + v1] = atoi(b2);
		if (0 > adjm[v0 * vcount + v1] ||
			strlen(b2) > 11 ||
			(strlen(b2) == 11 && strcmp("2147483647\n", b2) < 0)) {
			puts("bad length");
			free(adjm);
			return 0;
		}
		adjm[v1 * vcount + v0] = adjm[v0 * vcount + v1];
	}

	int* shortestPaths = malloc(vcount * sizeof(int));
	if (NULL == shortestPaths) {
		puts("cant allocate");
		free(adjm);
		return 0;
	}
	for (size_t i = 0; i < vcount; ++i)
		shortestPaths[i] = INF;

	unsigned short* prevInPath = malloc(vcount * sizeof(unsigned short));
	if (NULL == prevInPath) {
		puts("cant allocate");
		free(adjm);
		free(shortestPaths);
		return 0;
	}
	memset(prevInPath, 0, (vcount * sizeof(unsigned short)));

	int res = shortestPath_Dijkstra(adjm, shortestPaths, prevInPath, st, fin, vcount);
	if (ERR == res) {
		free(adjm);
		free(shortestPaths);
		free(prevInPath);
		return 0;
	}

	for (unsigned int v = 0; v < vcount; ++v)
		if (INF == shortestPaths[v])
			printf("%s ", "oo");
		else if (OVER_INT_MAX == shortestPaths[v])
			printf("%s ", "INT_MAX+");
		else
			printf("%d ", shortestPaths[v]);

	putc('\n', stdout);

	if (INF == shortestPaths[fin])
		puts("no path");
	else if (OVERFLOW == res)
		puts("overflow");
	else {
		unsigned int i = fin;
		do {
			printf("%u ", i + 1);
			i = prevInPath[i];
		} while (prevInPath[i] != i);
		printf("%u ", i + 1);
	}

	free(adjm);
	free(shortestPaths);
	free(prevInPath);
	return 0;
}
