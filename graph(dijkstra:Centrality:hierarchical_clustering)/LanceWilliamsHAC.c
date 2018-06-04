#include "LanceWilliamsHAC.h"
#include <stdio.h>
#include <stdlib.h>

Dendrogram createDNode(int v, Dendrogram left, Dendrogram right) {
	Dendrogram p = malloc(sizeof(Dendrogram));

	p->left = left;
	p->right = right;
	p->vertex = v;
}

int *get_closest(double **ds, int size) {
	int r[2] = {0};
	double distance = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) continue;
			if (ds[i][j] < distance) {
				r[0] = i;
				r[1] = j;
				distance = ds[i][j];
			}
		}
	}
	return r;
}

double helpFunc(double i, double j, int method) {
	double r;
	if (method == 1) {
		r = i < j ? i : j;
	} else {
		r = i > j ? i : j;
	}
	return r;
}

double **func1(double **distances, int size, int v, int w, int method) {
	double **new_distances = malloc((size-1)*(size-1)*sizeof(double));

	int ir = 0, ic = 0, jr = 0, jc = 0;
	for (ir = 0; ir < size; ir++) {
		if (ir != v && ir != w) {
			for (ic = 0; ic < size; ic++) {
				if (ic != v && ic != w) {
					new_distances[jr][jc] = distances[ir][ic];
					jc++;
				}
			}
			jr++;
		}
	}

	int j = 0;
	for (int i = 0; i < size; i++) {
		if (i == v || i == w) continue;
		new_distances[size-2][j] = helpFunc(distances[v][i], distances[w][i], method);
		j++;
	}

	for (int i = 0; i < size-2; i++) {
		new_distances[i][size-2] = new_distances[size-2][i];
	}
	new_distances[size-2][size-2] = INT_MAX;

	free(distances);
	return new_distances;
}

Dendrogram *func2(Dendrogram *dgrams, int size, int v, int w) {
	Dendrogram new = createDNode(-1, dgrams[v], dgrams[w]);
	Dendrogram *p = malloc((size-1)*sizeof(Dendrogram));

	int j = 0;
	for (int i = 0; i < size; i++) {
		if (i == v || i == w) continue;
		p[j] = dgrams[i];
		j++;
	}
	free(dgrams);
	p[size-2] = new;
	return p;
}

Dendrogram LanceWilliamsHAC(Graph g, int method) {
	double **distances = malloc(g->n * g->n * sizeof(double));

	int m, n;
	for (m = 0; m < g->n; m++) {
		for (n = 0; n < g->n; n++) {
			distances[m][n] = INT_MAX; //set distances to infinity by default
		}
	}

	for (int v = 0; v < g->n; v++) {
		AdjList a = outIncident(g, v);
		if (a != NULL && (1/(a->weight) < distances[v][a->w])) {
			distances[a->w][v] = 1.0 / (a->weight);
			distances[v][a->w] = 1.0 / (a->weight);
		}
		a = inIncident(g, v);
		if (a != NULL && (1/(a->weight) < distances[v][a->w])) {
			distances[a->w][v] = (double)1/(a->weight);
			distances[v][a->w] = (double)1/(a->weight);
		}
	}

	Dendrogram *ds = malloc(g->n * sizeof(Dendrogram));
	for (m = 0; m < g->n; m++) {
		ds[m] = createDNode(m, NULL, NULL);
	}

	int closest[2] = {0};
	int size = g->n;
	for (int k = 0; k < g->n; k++) {
		closest = get_closest(distances, size);
		distances = func1(distances, size, closest[0], closest[1], method);
		ds = func2(ds, size, closest[0], closest[1]);
		size--;
	}

	return ds[0];
}

void freeDendrogram(Dendrogram d) {
	free(d->right);
	free(d->left);
	free(d);
}