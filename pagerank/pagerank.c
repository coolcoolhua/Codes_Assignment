#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "set.h"
#include "queue.h"
#include "readData.h"

#define MAX 1001
#define MAXI 150

typedef struct PRValue {
    char* name;
	double value[MAX];
} PRValue;

typedef PRValue* Pr;


int outdegree(Graph g, Queue q, char* name);
void PageRank(double d, double diffPR, int maxIterations);
double findValue(Queue q, Pr p, char* name, int j);
double sumOfPrevious(Graph g, Queue q, Pr p, int j, char* name);
double diffr(Queue q, Pr p, int j);
double* reorder(double data[], int lo, int hi);
void output(Pr p, Graph g, Queue q, double* data, int iteration);

int main(int argc, char* argv[]) {

    PageRank(atof(argv[1]), atof(argv[2]), atoi(argv[3]));
    
    return 0;
}


//this function is the main function of pagerank
void PageRank(double d, double diffPR, int maxIterations) {

	Queue q = GetCollection();
	assert(q != NULL);
    Graph g = GetGraph(q);
	Pr p = malloc(MAXI * sizeof(PRValue));
    int count = nQueue(q);
	int i = 0;
	for (i = 0; i < count; i++) { // store first round of pagerank value into p[i].value[0]
		p[i].name = findQueue(q, i + 1);
	    p[i].value[0] = 1.0 / count;  
	}
	int iteration = 0;
	double diff = diffPR;
	// b is the constant number (1-d)/count
	double b = (1.0 - d) / count;
	while (iteration < maxIterations && diff >= diffPR) { // calculate the final pr value
		iteration++;
	    for (i = 0; i < count; i++) {
        	p[i].value[iteration] = b + d * sumOfPrevious(g, q, p, iteration - 1, p[i].name);
	    }
	    diff = diffr(q, p, iteration);
	}
    double final[MAXI];
    double buff = 0;
    for (i = 0; i < count; i++) { // store the final pr value
        buff = p[i].value[iteration];
        final[i] = buff;
    }
    double* finall = malloc(count * sizeof(double));
    finall = reorder(final, 0, count - 1);
    output(p, g, q, finall, iteration);
    disposeQueue(q);
    disposeGraph(g);
    free(p);
    
    return;
}


//use name to find pr value
double findValue(Queue q, Pr p, char* name, int j) {

    int i = 0;
    int count = nQueue(q);
    for (i = 0; i < count; i++) {
    	if(!strcmp(p[i].name, name)) return p[i].value[j];
    }
    
    return 0;
}


// part of pr formula
double sumOfPrevious(Graph g, Queue q, Pr p, int j, char* name) {

    double sum = 0;
    int count = nQueue(q);
    int i = 0;
    for (i = 0; i < count; i++) {
    	if (strcmp(name, findQueue(q, i + 1))) {
        	if (isConnected(g, findQueue(q, i + 1), name)) {
            	sum = sum + findValue(q, p, findQueue(q, i + 1), j) / outdegree(g, q, findQueue(q, i + 1));
            }
        }
    }
    
    return sum;
}


//calculate diff value
double diffr(Queue q, Pr p, int j) {

    double diff = 0;
    double single = 0;
    int i = 0;
    int count = nQueue(q);
    for (i = 0; i < count; i++) {
        single = p[i].value[j] - p[i].value[j - 1];
        if (single < 0) single = (-1) * single;
        diff = diff + single;
    }
    
    return diff;
}


// count the number of out degree
int outdegree(Graph g, Queue q, char* name) {

    int count = 0;
    int i = 0;
    int n = nQueue(q);
    for (i = 0; i < n; i++) {
    	if (strcmp(name, findQueue(q, i + 1))) {
            if (isConnected(g, name, findQueue(q, i + 1))) count++;
        }
    }
    
    return count;
}


// reorder reference from  lecture(selection sort), and modified
double* reorder(double data[], int lo, int hi) {

    int i, j, max;
    double buff = 0;
    for (i = lo; i < hi; i++) {
        max = i;
        for (j = i + 1; j <= hi; j++) {
        	if (data[j] > data[max]) max = j;
        }
        buff = data[i];
        data[i] = data[max];
        data[max] = buff;
    }
    
    return data;
}


void output(Pr p, Graph g, Queue q, double* data, int iteration) {

    int n = nQueue(q);
    int pint = 0;
    char* pchar = NULL;
    int i = 0;
    int j = 0;
    Set s = newSet();
    FILE* fp = fopen("pagerankList.txt", "w+");
    for (i = 0; i < n; i++) {
        for(j = 0;j < n; j++) {
            if (p[j].value[iteration] == data[i] && !isElem(s, p[j].name)) {
                pchar = p[j].name;
                insertInto(s, pchar);
                pint = outdegree(g, q, pchar);
            }
        }
        fprintf(fp, "%s, %d, %10.8lf\n", pchar, pint, data[i]);
    }
    fclose(fp);
    
    return;
}
	    
    


