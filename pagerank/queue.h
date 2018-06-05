#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueRep *Queue;

// Function signatures

Queue newQueue();
Queue exchange(Queue q,int n1,int n2);
void disposeQueue(Queue);
void enterQueue(Queue,char *);
char *leaveQueue(Queue);
int  emptyQueue(Queue);
void showQueue(Queue q);
char* findQueue(Queue q,int n);
int nQueue(Queue q);
int findrank(Queue q,char* name);
Queue copyq(Queue q);

#endif

