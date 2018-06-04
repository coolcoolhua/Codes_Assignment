#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
#include<string>
#include <cstring>
#include <string.h>
#pragma once
using namespace std;
#define M 2   // M为B树的度

typedef struct btree_node {
    int k[2 * M - 1];
    struct btree_node *p[2 * M];
    int num;
    bool is_leaf;
} btree_node;


btree_node *btree_delete(btree_node *root, int target);


int judge(int A){
    if (A<10){
        return 6;
    }
    if (10 <= A&&A<100){
        return 5;
    }
    if (100 <= A&&A<1000){
        return 4;
    }
    if (1000 <= A&&A<10000){
        return 3;
    }
    if (10000 <= A&&A<100000){
        return 2;
    }
    if (100000 <= A&&A<1000000){
        return 1;
    }
    return 0;
}

int sort_first()
{
    ifstream fin("Btree.txt");
    int count = 0;
    int i,j;
    while (fin.peek() != EOF)
    {
        char **sequence;
        sequence = (char**)malloc(sizeof(char *)* 40000);  //行数
        for (i = 0; i<40000; i++)
        {
            sequence[i] = (char*)malloc(sizeof(char)* 129);  //为每行申请空间
            
        }
        
        for (i = 0; i < 40000; i++)
        {
            char ch[129];
            fin.getline(ch, 129);
            memcpy(sequence[i], ch, 129);
            //cout << sequence[i][0]<<endl;
        }
        //cout << "asdf";
        for (i = 0; i < 40000; i++)
        {
            //cout << i << endl;
            
            int flat = 0;
            int Min = i;
            char min[8];
            memcpy(min, sequence[i], 7);
            min[7] = '\0';
            //string s = min1;
            //int min = std::atoi(s.c_str());
            int leng1=0;
            for (int k = 0; k < 7; k++)
            {
                if ((min[k]>='0')&&(min[k]<='9'))
                {
                    leng1++;
                }
            }
            //cout << min<<endl;
            
            for (int j = i + 1; j < 40000; j++)
            {
                char temp[8];
                memcpy(temp, sequence[j], 7);
                temp[7] = '\0';
                int leng2 = 0;
                for (int k = 0; k < 7; k++)
                {
                    if ((temp[k] >= '0')&&(temp[k] <= '9'))
                    {
                        leng2++;
                    }
                }
                
                
                //cout << temp<<endl;
                //cout << leng2 << " " << leng1 << endl;
                if (leng2 < leng1)
                {
                    //	cout << temp << " " << min << endl;
                    memcpy(min, temp, 7);
                    Min = j;
                    flat = 1;
                    leng1 = leng2;
                }
                else if ((strcmp(temp, min)<0) && (leng2 == leng1))
                {
                    //	cout << temp << " " << min << endl;
                    memcpy(min, temp, 7);
                    Min = j;
                    flat = 1;
                    leng1 = leng2;
                }
                
            }
            
            if (flat == 1)
            {
                //cout << "asdfasdf";
                char ch[129];
                memcpy(ch, sequence[i], 129);
                //cout << ch<<endl;
                memcpy(sequence[i], sequence[Min], 129);
                //cout << sequence[i]<<endl;
                memcpy(sequence[Min], ch, 129);
                //cout << sequence[Min] << endl;
            }
            
        }
        
        char buffer[20];
        sprintf(buffer, "%d", ++count);
        string resultpath = string(buffer) + "_0.txt";
        ofstream fout(resultpath);
        for (i = 0; i < 40000; i++)
        {
            for (j = 0; j < 129; j++)
            {
                fout << sequence[i][j];
            }
            fout<<endl;
        }
        
        fout.close();
        for (i = 0; i<40000; i++)
        {
            delete sequence[i];  //为每行申请空间
        }
        delete []sequence;
        
    }
    return 0;
    
}

void filemerge(int index, int num, string pathprefix)
{
    
    ifstream * fin = new ifstream[num];
    bool flag = true;//文件是否都结束标志变量
    bool * isend = new bool[num];
    string *kmer = new string[num];//存储kmer
    char ch[150];
    sprintf(ch, "%d", index);
    string filepath;
    char buffer[20];
    filepath = "2_0.txt";
    ofstream fout(filepath);
    //先打开文件
    for (int i = 0; i < num; i++)
    {
        sprintf(ch, "%d", index++);
        filepath = pathprefix + ch + ".txt";
        fin[i].open(filepath);
    }
    
    
    
    
    //扫描文件列表,将未到末尾文件从中取出一条记录存到kmer数组里，并将isend[i]设为真，否则设为假；
    for (int i = 0; i < num; i++)
    {
        //如果不是文件末尾
        if (fin[i].peek() != EOF)
        {
            isend[i] = true;
            fin[i].getline(ch, 150);
            //cout << ch << endl;
            kmer[i] = ch;
        }
        else
        {
            isend[i] = false;
        }
        
    }
    
    
    
    
    while (flag)
    {
        flag = false;
        
        //扫描kmer数组，将里面最小的kmer存入结果文件，并更新kmer
        
        //初始化j
        int j = 0;
        for (int i = 0; i < num; i++)
        {
            if (isend[i])
            {
                j = i;
                break;
            }
        }
        
        
        //挑出最小kmer
        for (int i = j+1; i < num; i++)
        {
            string s = kmer[i].substr(0, 7);
            int xi = std::atoi(s.c_str());
            s = kmer[j].substr(0, 7);
            int xj = std::atoi(s.c_str());
            if (!isend[i])
            {
                continue;
            }
            if (xi<xj)
            {
                j = i;
            }
        }
        
        //将最小kmer写入文件并更新
        fout << kmer[j] << endl;
        //cout << kmer[j] << endl;
        if (fin[j].peek() != EOF)
        {
            flag = true;
            fin[j].getline(ch, 150);
            kmer[j] = ch;
        }
        else
        {
            isend[j] = false;
            for (int m = 0; m < num; m++)
            {
                if (isend[m])
                {
                    flag = true;
                    break;
                }
            }
        }
        
        
    }
    
    
    
    fout.close();
    for (int i = 0; i < num; i++)
    {
        fin[i].close();
    }
    delete[]kmer;
    delete[]isend;
    delete[]fin;
    return;
}


void CreateTXT()
{
    ofstream fout(""/Users/zhuhua/Desktop/Btree.txt");
    //fout << "A" << "      " << "B" << endl;
    
    srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
    for (int i = 0; i<1000000; i++)
    {
        int key = int(((double)rand() / RAND_MAX)*(1000000) + 1);
        fout << key;
        int length = judge(key);
        for (int j = 0; j < length; j++)
        {
            fout << " ";
        }
        for (int j = 0; j < 128 - 7; j++)
        {
            char ch = char(rand() % 26 + 'a');
            fout << ch;
        }
        fout << endl;
    }
}







btree_node *btree_node_new()
{
    btree_node *node = (btree_node *)malloc(sizeof(btree_node));
    if (NULL == node) {
        return NULL;
    }
    
    for (int i = 0; i < 2 * M - 1; i++) {  // 初始化key
        node->k[i] = 0;
    }
    
    for (int i = 0; i < 2 * M; i++) {     // 初始化pointer
        node->p[i] = NULL;
    }
    
    node->num = 0;
    node->is_leaf = true;  // 默认为叶子
    return node;
    
}

btree_node *btree_create()
{
    btree_node *node = btree_node_new();
    if (NULL == node) {
        return NULL;
    }
    
    return node;
}

int btree_split_child(btree_node *parent, int pos, btree_node *child)
{
    // 创建新的节点
    btree_node *new_child = btree_node_new();
    if (NULL == new_child) {
        return -1;
    }
    
    
    // 新节点的is_leaf与child相同，key的个数为M-1
    
    new_child->is_leaf = child->is_leaf;
    new_child->num = M - 1;
    
    // 将child后半部分的key拷贝给新节点
    for (int i = 0; i < M - 1; i++) {
        new_child->k[i] = child->k[i + M];
    }
    
    
    // 如果child不是叶子，还需要把指针拷过去，指针比节点多1
    
    if (false == new_child->is_leaf) {
        for (int i = 0; i < M; i++) {
            new_child->p[i] = child->p[i + M];
        }
    }
    
    child->num = M - 1;
    
    
    // child的中间节点需要插入parent的pos处，更新parent的key和pointer
    
    for (int i = parent->num; i > pos; i--) {
        parent->p[i + 1] = parent->p[i];
    }
    parent->p[pos + 1] = new_child;
    
    for (int i = parent->num - 1; i >= pos; i--) {
        parent->k[i + 1] = parent->k[i];
    }
    parent->k[pos] = child->k[M - 1];
    
    parent->num += 1;
    return 1;
}


// 执行该操作时，node->num < 2M-1

void btree_insert_nonfull(btree_node *node, int target)
{
    if (1 == node->is_leaf) { // 如果在叶子中找到，直接删除
        int pos = node->num;
        while (pos >= 1 && target < node->k[pos - 1]) {
            node->k[pos] = node->k[pos - 1];
            pos--;
        }
        
        node->k[pos] = target;
        node->num += 1;
        
    }
    else {   // 沿着查找路径下降
        int pos = node->num;
        while (pos > 0 && target < node->k[pos - 1]) {
            pos--;
        }
        
        if (2 * M - 1 == node->p[pos]->num) {
            btree_split_child(node, pos, node->p[pos]); // 如果路径上有满节点则分裂
            if (target > node->k[pos]) {
                pos++;
            }
        }
        
        btree_insert_nonfull(node->p[pos], target);
    }
}

//插入入口

btree_node* btree_insert(btree_node *root, int target)
{
    if (NULL == root) {
        return NULL;
    }
    
    // 对根节点的特殊处理，如果根是满的，唯一使得树增高的情形
    // 先申请一个新的
    if (2 * M - 1 == root->num) {
        btree_node *node = btree_node_new();
        if (NULL == node) {
            return root;
        }
        
        node->is_leaf = 0;
        node->p[0] = root;
        btree_split_child(node, 0, root);
        btree_insert_nonfull(node, target);
        return node;
    }
    else {
        btree_insert_nonfull(root, target);
        return root;
    }
}


















void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z)
{
    // 将z中节点拷贝到y的后半部分
    y->num = 2 * M - 1;
    for (int i = M; i < 2 * M - 1; i++) {
        y->k[i] = z->k[i - M];
    }
    y->k[M - 1] = root->k[pos]; // k[pos]下降为y的中间节点
    
    // 如果z非叶子，需要拷贝pointer
    if (false == z->is_leaf) {
        for (int i = M; i < 2 * M; i++) {
            y->p[i] = z->p[i - M];
        }
    }
    
    
    // k[pos]下降到y中，更新key和pointer
    
    for (int j = pos + 1; j < root->num; j++) {
        root->k[j - 1] = root->k[j];
        root->p[j] = root->p[j + 1];
    }
    
    root->num -= 1;
    free(z);
}

//寻找rightmost，以root为根的最大关键字

int btree_search_predecessor(btree_node *root)
{
    btree_node *y = root;
    while (false == y->is_leaf) {
        y = y->p[y->num];
    }
    return y->k[y->num - 1];
}

// 寻找leftmost，以root为根的最小关键字

int btree_search_successor(btree_node *root)
{
    btree_node *z = root;
    while (false == z->is_leaf) {
        z = z->p[0];
    }
    return z->k[0];
}


void btree_shift_to_right_child(btree_node *root, int pos,
                                btree_node *y, btree_node *z)
{
    z->num += 1;
    for(int i = z->num -1; i > 0; i--) {
        z->k[i] = z->k[i-1];
    }
    z->k[0]= root->k[pos];
    root->k[pos] = y->k[y->num-1];
    
    if(false == z->is_leaf) {
        for(int i = z->num; i > 0; i--) {
            z->p[i] = z->p[i-1];
        }
        z->p[0] = y->p[y->num];
    }
    
    y->num -= 1;
}


// y向借节点，将root->k[pos]下降至y，将z的最小关键字上升至root的pos处

void btree_shift_to_left_child(btree_node *root, int pos,
                               btree_node *y, btree_node *z)
{
    y->num += 1;
    y->k[y->num-1] = root->k[pos];
    root->k[pos] = z->k[0];
    
    for(int j = 1; j < z->num; j++) {
        z->k[j-1] = z->k[j];
    }
    
    if(false == z->is_leaf) {
        y->p[y->num] = z->p[0];
        for(int j = 1; j <= z->num; j++) {
            z->p[j-1] = z->p[j];
        }
    }
    
    z->num -= 1;
}
void btree_delete_nonone(btree_node *root, int target)
{
    if (true == root->is_leaf) {  // 如果在叶子节点，直接删除
        int i = 0;
        while (i < root->num && target > root->k[i]) i++;
        if (target == root->k[i]) {
            for (int j = i + 1; j < 2 * M - 1; j++) {
                root->k[j - 1] = root->k[j];
            }
            root->num -= 1;
        }
        else {
            printf("target not found\n");
        }
    }
    else {  // 在分支中
        int i = 0;
        btree_node *y = NULL, *z = NULL;
        while (i < root->num && target > root->k[i]) i++;
        if (i < root->num && target == root->k[i]) { // 如果在分支节点找到target
            y = root->p[i];
            z = root->p[i + 1];
            if (y->num > M - 1) {
                // 如果左分支关键字多于M-1，则找到左分支的最右节点prev，替换target
                // 并在左分支中递归删除prev,情况2（a)
                int pre = btree_search_predecessor(y);
                root->k[i] = pre;
                btree_delete_nonone(y, pre);
            }
            else if (z->num > M - 1) {
                // 如果右分支关键字多于M-1，则找到右分支的最左节点next，替换target
                // 并在右分支中递归删除next,情况2(b)
                int next = btree_search_successor(z);
                root->k[i] = next;
                btree_delete_nonone(z, next);
            }
            else {
                // 两个分支节点数都为M-1，则合并至y，并在y中递归删除target,情况2(c)
                btree_merge_child(root, i, y, z);
                btree_delete(y, target);
            }
        }
        else {   // 在分支没有找到，肯定在分支的子节点中
            y = root->p[i];
            if (i < root->num) {
                z = root->p[i + 1];
            }
            btree_node *p = NULL;
            if (i > 0) {
                p = root->p[i - 1];
            }
            
            if (y->num == M - 1) {
                if (i > 0 && p->num > M - 1) {
                    // 左邻接节点关键字个数大于M-1
                    btree_shift_to_right_child(root, i - 1, p, y); //情况3(a)
                }
                else if (i < root->num && z->num > M - 1) {
                    // 右邻接节点关键字个数大于M-1
                    btree_shift_to_left_child(root, i, y, z); // 情况3(b)
                }
                else if (i > 0) {
                    btree_merge_child(root, i - 1, p, y);  // 情况3（c)
                    y = p;
                }
                else {
                    btree_merge_child(root, i, y, z); // 情况3(c)
                }
                btree_delete_nonone(y, target);
            }
            else {
                btree_delete_nonone(y, target);
            }
        }
        
    }
}
// 删除入口

btree_node *btree_delete(btree_node *root, int target)
{
    // 特殊处理，当根只有两个子女，切两个子女的关键字个数都为M-1时，合并根与两个子女
    // 这是唯一能降低树高的情形
    if (1 == root->num) {
        btree_node *y = root->p[0];
        btree_node *z = root->p[1];
        if (NULL != y && NULL != z &&
            M - 1 == y->num && M - 1 == z->num) {
            btree_merge_child(root, 0, y, z);
            free(root);
            btree_delete_nonone(y, target);
            return y;
        }
        else {
            btree_delete_nonone(root, target);
            return root;
        }
    }
    else {
        btree_delete_nonone(root, target);
        return root;
    }
}

void btreeDisplay(btree_node *root){
    int i, queueNum = 0;
    int j;
    btree_node *queue[20];
    btree_node *current;
    //加入队列 
    queue[queueNum] = root;
    queueNum++;
    while (queueNum>0){
        //出队 
        current = queue[0];
        queueNum--;
        //移出第一个元素后后面的元素往前移动一个位置 
        for (i = 0; i<queueNum; i++)
            queue[i] = queue[i + 1];
        //显示节点 
        j = current->num;
        printf("[ ");
        for (i = 0; i<j; i++){
            printf("%d ", current->k[i]);
        }
        printf("] ");
        //子节点入队 
        if (current != NULL && current->is_leaf != 1){
            for (i = 0; i <= (current->num); i++){
                queue[queueNum] = current->p[i];
                queueNum++;
            }
        }
    }
    cout << endl;
}


int main()
{
    //built_txt();
    //sort_first();
    //string pathprefix = "D:\\B树\\B树\\";
    //filemerge(1, 25, pathprefix);
    
    btree_node *node;
    node = btree_create();
    for (int i = 0; i < 10; i++)
    {
        node = btree_insert(node, i);
        btreeDisplay(node);
        
    }
    
    
    
    
    for (int i = 0; i < 10; i++)
    {
        node = btree_delete(node, i);
    }
    
    system("pause");
    return 0;
}


