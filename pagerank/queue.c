

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "queue.h"

typedef struct Node *Link;

typedef struct Node {
	char *val;
	Link  next;
} Node;
	
typedef struct QueueRep {
    int n;
	Link  front;
	Link  back;
} QueueRep;

// Function signatures
Queue exchange(Queue q, int n1, int n2);
Queue newQueue();
void disposeQueue(Queue);
void enterQueue(Queue, char *);
char *leaveQueue(Queue);
int  emptyQueue(Queue);
char* findQueue(Queue q, int n);
void showQueue(Queue q);
int nQueue(Queue q);
int findrank(Queue q, char* name);
Queue copyq(Queue q);

Queue copyq(Queue q) {

    Queue q1 = newQueue();
    Link b = q->front;
    int n = nQueue(q);
    int i = 0;
    char* a = malloc(99 * sizeof(char));
    for (i = 0; i < n; i++) {
    	strcpy(a, b->val);
        enterQueue(q1, a);
        b = b->next;
    }
    
    return q1;
}


Queue exchange(Queue q, int n1, int n2) {
    
	char* c = malloc(99 * sizeof(char));
    strcpy(c, findQueue(q, n1));
    strcpy(findQueue(q, n1), findQueue(q, n2));
    strcpy(findQueue(q, n2), c);
    
    return q;
}


int findrank(Queue q, char* name) {

    int i = 0;
    int n = 0;
    for (i = 0; i < nQueue(q); i++) {
    	if (!strcmp(name, findQueue(q, i + 1))) n = i + 1;      
    }
    
    return n;
}

static Link newNode(char *);
static void disposeNode(Link);
//return the number of items in th Queue
int nQueue(Queue q) {
    
    return (q->n);
}
//find the nth item in the Queue
char* findQueue(Queue q,int n) {
    
    int i = 0;
    assert(n <= q->n);
    Link a = q->front;
    for (i = 0; i < n-1; i++) {
        a = a->next;
    }
    
    return (a->val);
}


// newQueue()
// - create an initially empty Queue
Queue newQueue()
{
	Queue new = malloc(sizeof(QueueRep));
	assert(new != NULL);
	new->front = NULL;
	new->back = NULL;
    new->n=0;
	return new;
}

// disposeQueue(Queue)
// - clean up memory associated with Queue
void disposeQueue(Queue q)
{
	if (q == NULL) return;
	Link next, curr = q->front;
    q->n=0;
	while (curr != NULL) {
		next = curr->next;
		disposeNode(curr);	
		curr = next;
	}
}

// enterQueue(Queue,Str)
// - add Str to back of Queue
void enterQueue(Queue q, char *str)
{
	Link new = newNode(str);
    q->n++;
	if (q->front == NULL)
		q->front = q->back = new;
	else {
		// add into list of elems
		q->back->next = new;
		q->back = new;
	}
}

// leaveQueue(Queue)
// - return string at front of Queue
char *leaveQueue(Queue q)
{
	assert (q->front != NULL);
    q->n--;
    char *str = q->front->val;
	Link old = q->front;
	q->front = old->next;
	if (q->front == NULL)
		q->back = NULL;
	free(old);
	return str;
}

// emptyQueue(Queue)
// - check whether Queue is empty
int emptyQueue(Queue q)
{
	return (q->front == NULL);
}

// showQueue(Queue)
// - display Queue (for debugging)
void showQueue(Queue q)
{
	Link curr;
	if (q->front == NULL)
		printf("Queue is empty\n");
	else {
		printf("Queue (front-to-back):\n");
		int id = 0;
		curr = q->front;
		while (curr != NULL) {
			printf("[%03d] %s\n", id, curr->val);
			id++;
			curr = curr->next;
		}
	}
}

// Helper functions

static Link newNode(char *str)
{
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->val = strdup(str);
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr->val);
	free(curr);
}


