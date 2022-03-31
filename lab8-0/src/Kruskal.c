#include <stdlib.h>
#include "Kruskal.h"

int minSpanningTree(Edge* edges, size_t ecount,
							 unsigned short* colors, size_t vcount,
							 unsigned short* res) {
	if (0 == vcount)
		return -1;
	unsigned int resCount = 0;
	for (size_t ei = 0; ei < ecount; ++ei)
		if (colors[edges[ei].v[0]] != colors[edges[ei].v[1]]) {
			res[resCount] = edges[ei].v[0];
			res[resCount + 1] = edges[ei].v[1];

			unsigned int eatenColor = colors[res[resCount + 1]];
			for (size_t vi = 0; vi < vcount; ++ vi)
				if (colors[vi] == eatenColor)
					colors[vi] = colors[res[resCount]];

			resCount += 2;
		}
	for (size_t vi = 0; vi < vcount; ++vi)
		if (colors[vi] != colors[0])
			return -1;
	return (int)resCount;
}
