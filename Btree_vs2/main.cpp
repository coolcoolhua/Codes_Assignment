//
//  main.cpp
//  Btree
//
//  Created by zh on 15/5/21.
//  Copyright (c) 2015年 zh. All rights reserved.
//
using namespace std;
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
int keys[1000000];
int judge(int A);





#define DU 3                       //DU代表B树的度
typedef struct _page{
    int data[DU*2-1];          //节点关键字数组，最多有DU*2-1个关键字
    struct _page *child[DU*2]; //子节点指针数组，最多有DU*2个指针
    struct _page *parent;      //指向父节点
    int isLeaf;                //标志节点是否是叶子节点
}page;
page* pm(){
    page* p=(page *)malloc(sizeof(page));
    int index=0;
    for(;index<sizeof(p->data)/sizeof(int);index++)
        p->data[index]=0;                      //每个关键字置为0
    p->isLeaf=1;                                  //初始化是叶子节点
    return p;
}
int pageSize(page* p){
    if(p==NULL)
        return 0;
    int result=0;
    int i=0;
    for(;i<DU*2-1;i++){
        if(p->data[i]!=0)
            result++;
    }
    return result;
}
page* pm();
int maxIndex(page* p){
    int i=0;
    int result;
    for(;i<2*DU-1;i++){
        if(p->data[i]==0)
            return i-1;   //如果遇到了0说明前一个下标是最大的下标
    }
    return 2*DU-2;           //如果到了这里说明该节点是满节点，最大关键字下标是2*DU-2
}

void shiftLeft(page* p,int start,int offset){ //start是开始移动的位置，offset 移动的位移
    int tmp=start;
    int max=maxIndex(p);
    if(start+offset>max+1){
        printf("out of bound");
        exit(0);
    }
    if(max==0)
        max=1;
    for(;tmp<max;tmp++){                 //左移关键字
        p->data[tmp]=p->data[tmp+offset];
        p->data[tmp+offset]=0;       //将无用的关键字置为0
    }
    tmp=start;
    for(;tmp<max+1;tmp++){
        p->child[tmp]=p->child[tmp+offset]; //左移子节点指针
        p->child[tmp+offset]=NULL;          //将无用的子节点指针置为NULL
    }
}

void shiftRight(page* p,int start,int offset){
    int max=maxIndex(p);
    if(offset+max>2*DU-2){
        printf("out of bound");
        exit(0);
    }
    int index=max;
    for(;index>=start;index--){
        p->data[index+offset]=p->data[index]; //右移关键字数组
        p->data[index]=0;
    }
    index=max+1;
    for(;index>=start;index--){
        p->child[index+offset]=p->child[index]; //右移子节点指针数组
        p->child[index]=NULL;
    }
}
page* splitPage(page* p,int val){
    //p节点为满节点，需要分裂，val是用来决定返回递归的新节点，B节点（原来的递归节点），C节点
    int mid=p->data[DU-1];        //取得p中间位置的节点，它被分裂到父节点中
    page* right=pm();             //新建C节点
    int index=DU;
    int i=0;
    for(;index<DU*2-1;index++){   //开始复制B节点的关键字数组和子节点指针数组，
        right->data[i]=p->data[index];
        p->data[index]=0;
        right->child[i]=p->child[index];
        p->child[index]=NULL;
        if(right->child[i]!=NULL)
            right->child[i]->parent=right;
        //B节点的子节点的父节点原来是B，由于一部分子节点迁移到了C节点上，所以要重新设置子节点的父节点指针
        i++;
    }
    right->child[i]=p->child[2*DU-1];         //子节点指针数组比关键字数组个数多一个
    if(right->child[DU-1]!=NULL)
        right->child[DU-1]->parent=right; //同时设置最后一个子节点指针的父节点
    p->child[2*DU-1]=NULL;
    p->data[DU-1]=0;
    page* result=p;
    right->isLeaf=p->isLeaf;                  //设置C节点是否是叶子节点，
    int isNew=0;
    if(val>mid)                         //如果新节点大于mid，新递归的节点就是C节点
        result=right;
    if(p->parent==NULL){//如果p节点就是根节点了，那么需要新生成Root节点
        page* root=pm();
        p->parent=root;
        isNew=1;
        root->isLeaf=0;
    }
    page* parent=p->parent;
    int first=0;
    for(;first<2*DU-1;first++){//取得父节点中mid可插入的位置
        if(parent->data[first]>mid||parent->data[first]==0)
            break;
    }
    index=2*DU-3;
    for(;index>=first;index--){//关键字和子节点指针数组右移1位
        parent->data[index+1]=parent->data[index];
        parent->child[index+2]=parent->child[index+1];
    }
    parent->data[first]=mid;  //插入新的关键字mid，和新的子节点指针right
    parent->child[first+1]=right;
    if(isNew){
        parent->child[0]=p;
    }
    right->parent=parent;
    return result;
}

void insertData(page* p,int val){ //p表示目的节点，val表示要插入的值
    if(pageSize(p)==DU*2-1){  //如果递归的过程中碰到满节点，就先分裂p节点
        p=splitPage(p,val); //分裂的过程后，从新设置p节点
    }
    int index=0;
    for(;index<sizeof(p->data)/sizeof(int);index++){ //寻找子节点的位置，因为分裂节点保证了p节点不是满节点，所以不用考虑满节点的情况（满节点的话index需要加1）
        if(p->data[index]==0||p->data[index]>val){
            break;
        }
    }
    
    if(p->isLeaf==0){ //如果不是叶子节点，递归插入到子节点
        insertData(p->child[index],val);
        return;
    }
    if(pageSize(p)>0) //如果节点中有关键字则右移1个位置
        shiftRight(p,index,1);
    p->data[index]=val; //把新的关键字插入到相应的位置
}


void createText(){
    long start = clock();
    int lengthtxt;
    int num;
    srand((int)time(0));
    ofstream fileout("/Users/zhuhua/Desktop/Btree.txt");
    fileout<<"A"<<"          "<<"B"<<endl;
    for(int i=0;i<1000000;i++){
        num= int( ((double)rand()/RAND_MAX)*(1000000-0) + 0);
        keys[i]=num;
        fileout<<num;
        lengthtxt=judge(num);
        for(int j=0;j<lengthtxt;j++){
            fileout<<" ";
        }
        for(int j=0;j<128-lengthtxt;j++){
            fileout<<char( rand()%26+'a');
        }
        fileout<<endl;
    }
    cout<<"创建文本花费时间："<<endl;
    printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
    
    
    
}

int judge(int A){
    if(A<10){
        return 9;
    }
    if(10<=A&&A<100){
        return 8;
    }
    if(100<=A&&A<1000){
        return 7;
    }
    if(1000<=A&&A<10000){
        return 6;
    }
    if(10000<=A&&A<100000){
        return 5;
    }
    if(100000<=A&&A<1000000){
        return 4;
    }
    return 0;
}




int main(int argc, const char * argv[]) {
    long start = clock();
    page* root = pm();
    createText();
    for(int i=0;i<1000000;i++){
        insertData(root,keys[i]);
    }
    cout<<"插入数据花费时间"<<endl;
    printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
}



