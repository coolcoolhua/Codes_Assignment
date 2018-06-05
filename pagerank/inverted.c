#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include "set.h"
#include "queue.h"
#include "readData.h"


//functions are in readData.c
int main(int argc, char*argv[]) {
    
    Queue q = GetCollection();    
    GetInvertedList(q);
    
    return 0;
}

