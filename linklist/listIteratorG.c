//Xinpei Zhang
//z5092041
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

typedef struct Node {  //create the struct of a node
    void *value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct IteratorGRep {  //create the struct of a list
    int flag;
    Node *first;
    Node *last;
    Node *cursorPrev;
    Node *cursorNext;
    Node *curr;  //use in the *next,*prev,findnext,findprev function
    ElmCompareFp cmp;  //compare two values v1 v2.if v1=v2,return 0;if v1<v2,return -1
	ElmNewFp new;  //copy value to a new pointer
	ElmFreeFp free;  //free the pointer
} IteratorGRep;

IteratorG IteratorGNew(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp){  //create a list
    IteratorGRep *it;
    it=malloc(sizeof(IteratorGRep));
    assert(it != NULL);
    it->flag=0;
    it->first=NULL;
    it->last=NULL;
    it->cursorPrev=NULL;
    it->cursorNext=NULL;
    it->curr=NULL;
    it->cmp=cmpFp;  //used to compare value
    it->new=newFp; //used to copy value
    it->free=freeFp;
    return it;    
}


int  add(IteratorG it, void *vp){
    //printf("add add add\n");
    assert(it != NULL);
    Node *pt=malloc(sizeof(Node));;
    //pt->value=vp;
    pt->value=it->new(vp);
    
    if(it->cursorPrev == NULL){ //add to the first node
        it->first=pt;
        pt->next=it->cursorNext;
        if(it->cursorNext != NULL){
            it->cursorNext->prev=pt;
        }
        it->cursorPrev=pt;
    }
    else{  //add in the middle
        pt->next=it->cursorNext;
        pt->prev=it->cursorPrev;
        it->cursorPrev->next=pt;
        if(it->cursorNext != NULL){  //if it is not at the last node
            it->cursorNext->prev=pt;
        }
        it->cursorPrev=pt;
    }
    it->curr=NULL;
    it->flag=0;
    
    return 1;
}
int  hasNext(IteratorG it){
    //printf("has \n");
    assert(it != NULL);
    if(it->cursorNext==NULL){
        return 0;
    }else{
        return 1;
    }
    it->flag=0;
    it->curr=NULL;
    
}
int  hasPrevious(IteratorG it){
    //printf("has previous\n");
    assert(it != NULL);
    if(it->cursorPrev==NULL){
        return 0;
    }else{
        return 1;
    }
    it->flag=0;
    it->curr=NULL;
    
}

void *next(IteratorG it){
    //printf("next\n");
    assert(it != NULL);
    Node *pt1;
    pt1=malloc(sizeof(Node));
    if(it->cursorNext==NULL){  //when the cursor is at the last position
        it->flag=0;
        it->curr=NULL;
        return NULL;
    }else{//need correct
        pt1=it->new(it->cursorNext->value);
        it->curr=it->cursorNext;
        it->cursorPrev=it->cursorNext;
        it->cursorNext=it->cursorNext->next;
        it->flag=1;
        
    }
    return pt1;
}

void *previous(IteratorG it){
    //printf("previous\n");
    assert(it != NULL);
    Node *pt2;
    pt2=malloc(sizeof(Node));
    if(it->cursorPrev == NULL){
        it->flag=0;
        it->curr=NULL;
        return NULL;
    }else{
        pt2=it->new(it->cursorPrev->value);
        it->curr=it->cursorPrev;
        it->cursorNext=it->cursorPrev;
        it->cursorPrev=it->cursorPrev->prev;
        it->flag=1;
        //it->curr=pt2;
    }
    return pt2;
}
int  delete(IteratorG it){
    //printf("delete\n");
    assert(it != NULL);
    Node *pt3=it->curr;
    if(it->cursorPrev==NULL && it->cursorNext==NULL){  //the empty list,delete nothing
        return 0;
    }else{
        if(it->cursorPrev->prev==NULL && it->cursorNext==NULL){  //only one number in the list
            it->first=NULL;
            it->last=NULL;
            it->cursorPrev=NULL;
            it->cursorNext=NULL;
            it->flag=0;
        }else if(pt3->prev==NULL){  //delete the first node
            it->first=pt3->next;
            it->cursorNext=pt3->next;
            it->cursorPrev=pt3->next->prev=NULL;
            
        }else if(pt3->next==NULL){  //delete the last node
            it->last=pt3->prev;
            it->cursorPrev=pt3->prev;
            it->cursorNext=pt3->prev->next=NULL;
        }else{  //delete number in the middle
            pt3->next->prev=pt3->prev;
            pt3->prev->next=pt3->next;
            
        }
    }
    free(pt3);
    it->flag=0;
    it->curr=NULL;
    return 1;  
}
int  set(IteratorG it, void *vp){
    assert(it != NULL);
    if(it->curr != NULL){
        it->curr->value=it->new(vp);  //can replace
        return 1;
    }else{
        it->flag=0;
        it->curr=NULL;
        return 0;
    }
}
void *findNext(IteratorG it, void *vp){
    printf("find next\n");
    assert(it != NULL);
    Node *pt4=it->cursorNext;
    if(it->flag==1){
    while(pt4 != NULL){
        if(it->cmp(pt4->value,vp)==0){
            it->last=pt4;
            it->cursorPrev=pt4;
            it->cursorNext=pt4->next;
            it->flag=1;    
        }
        else{
            it->flag=0;
            pt4=pt4->next;
        }
    }
    }
    return pt4;
}
void *findPrevious(IteratorG it, void *vp){
    //printf("find previous\n");
    assert(it != NULL);
    Node *pt5=it->cursorPrev;
    if(it->flag==1){
    while(pt5 != NULL){
        if(it->cmp(pt5->value,vp)==0){
            it->last=pt5;
            it->cursorPrev=pt5->prev;
            it->cursorNext=pt5;
            it->flag=1;
        }else{
            it->flag=0;
            pt5=pt5->prev;
        }
    }
    }
    return pt5;
}
void freeIt(IteratorG it){
    Node *pt6=it->first;
    while(pt6 != NULL){
        Node *copy=pt6;
        free(copy);
        pt6=pt6->next;
    }
}

void reset(IteratorG it){  //reset the list to the start position
    if(it->cursorPrev != NULL){
        it->cursorPrev->next=it->cursorNext;
    }
    if(it->cursorNext != NULL){
        it->cursorNext->prev=it->cursorPrev;
    }
    it->cursorPrev=NULL;
    it->cursorNext=it->first;
    it->curr=NULL;
    it->flag=0;
}

