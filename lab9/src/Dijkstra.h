#pragma once

#define OVER_INT_MAX	-2
#define INF			-1

#define ERR			-1
#define NOPATH		-2
#define OVERFLOW	-3

int D_shortestPath(int* adjm, int* shortestPaths, unsigned short* path,
					unsigned int st, unsigned int fin,
					unsigned int vcount);
