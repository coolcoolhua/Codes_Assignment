#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include "set.h"
#include "queue.h"
#include "readData.h"

#define MAX 999

typedef struct  Urll {
	char* name;
	Set word;
} Urll;

typedef Urll* Url;


char** reorder1(char* text[], int lo, int hi);
void output1(Url u, int n, char** word, int numOfWord);


// read collection.txt, and store them into q
Queue GetCollection() {
    
    Set s = newSet();
    assert(s != NULL);
	Queue q = newQueue();
	assert(q != NULL);
	FILE* fp = fopen("collection.txt", "r");
 	char text[MAX] = "a";
 	while (fscanf(fp, "%s", text) > 0) {
        if (!isElem(s, text)) {
        	insertInto(s, text);
        	enterQueue(q, text);
        }
 	}
    fclose(fp);
    free(s);
    
    return q;
}


// make q connected, and store into g
Graph GetGraph(Queue q) {
    
    assert(q != NULL);
    int count = nQueue(q);
    assert(count != 0);
    Graph g = newGraph(count);
    int i = 0;
    FILE* fp = NULL;
    char* name = malloc(MAX * sizeof(char));
    char text[MAX] = "a";
    char buff[MAX] = "a";
    for (i = 0; i < count; i++) {
        name = findQueue(q, i + 1);
        strcpy(buff, name);
        char* filename = strcat(buff, ".txt");
        fp = fopen(filename, "r");
        fscanf(fp, "%s", text);
        fscanf(fp, "%s", text);  
        fscanf(fp, "%s", text);
        while (strcmp(text, "#end")) {
            addEdge(g, name, text);
            fscanf(fp, "%s", text);            
        }
        fclose(fp);
     }
    
     return g;
}


//the main function of getting inverted list
void GetInvertedList(Queue q) {

	assert(q != NULL);
	Set s = newSet();
	assert(s != NULL);
	Queue allWord = newQueue();
	assert(allWord != NULL);
    int count = nQueue(q);
    int i = 0;
    FILE* fp = NULL;
    char* name = NULL;
    Url u = malloc(count * sizeof(Urll));
    assert(u != NULL);
    char* text = malloc(MAX * sizeof(char));
    char buff[MAX] = "a";
	assert(count != 0);
    for (i = 0; i < count; i++) {	//get all data from collection
    	name = findQueue(q, i + 1);
        strcpy(buff, name);
        char* filename = strcat(buff, ".txt");
        u[i].name = name;
        u[i].word = newSet();
        fp = fopen(filename, "r");
        fscanf(fp, "%s", text);
        while (strcmp(text, "Section-2")) {
        	fscanf(fp, "%s", text);
        }
        fscanf(fp, "%s", text);
        while (strcmp(text, "#end")) {
            text = deal(text);
            insertInto(u[i].word, text);
           	if (!isElem(s, text)) {
        		insertInto(s, text);
      	    	enterQueue(allWord, text);
           	}
            fscanf(fp, "%s", text);
        }
        fclose(fp);
	}
    int numOfWord = nQueue(allWord);
    char** word = malloc(MAX * sizeof(char*));
	for (i = 0; i < numOfWord; i++) {
    	word[i] = leaveQueue(allWord);
	}     
    word = reorder1(word, 0, numOfWord - 1);
    output1(u, count, word, numOfWord);
    disposeQueue(q);
    disposeQueue(allWord);
    disposeSet(s);
	
	return;
}


// make a good format
char* deal(char* text) {

    int i = 0;
    int count = strlen(text);
    for (i = 0; i < count; i++) {
    	text[i] = tolower(text[i]);
    }
    char* fullStop = strchr(text, '.');
    if (fullStop != NULL) {
    	text[count - 1] = '\0';
    }
    
    return text;
}


// reorder reference from  lecture(selection sort), and modified
char** reorder1(char* text[], int lo, int hi) {

    int i, j, min;
    char* buff = malloc(MAX * sizeof(char));
    char* buff2 = malloc(MAX * sizeof(char));
    for (i = lo; i < hi; i++) {
    	min = i;
        for (j = i + 1; j <= hi; j++) {
        	if (strcmp(text[j], text[min]) < 0) min = j;
        }
        strcpy(buff, text[i]);
        strcpy(buff2, text[min]);
        strcpy(text[i], buff2);
        strcpy(text[min], buff);
    }
    
    return text;
}   


void output1(Url u, int n, char** word, int numOfWord) {

	int i = 0;
    int j = 0;
    FILE* fp = fopen("invertedIndex.txt", "w+");
    for (i = 0; i < numOfWord; i++) {
    	fprintf(fp, "%s ", word[i]);
        for (j = 0; j < n; j++) {
        	if (isElem(u[j].word, word[i])) {
        		fprintf(fp, " %s", u[j].name);
			}
        }
    	fprintf(fp, "\n");
	}
    fclose(fp);
    
    return;
}
       
 


