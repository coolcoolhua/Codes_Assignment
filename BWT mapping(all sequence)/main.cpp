//
//  main.cpp
//  BWT mapping(all sequence)
//
//  Created by zh on 15/4/24.
//  Copyright (c) 2015年 zh. All rights reserved.
//
using namespace std;
#include<string>
#include <fstream>
#include<stdlib.h>
#include <iostream>
#include<time.h>
#include <algorithm>
#include<vector>
#include<cmath>
#include<cstring>
#include <thread>
#include <limits.h>
#define N 78126
#define THREADNUM 8
int countm=0;
const int MAXS = 300 * 1024 * 1024;
char buf[MAXS];
long counting=0;
const int MAXN = 224999720;
int numbers[MAXN];
long times;
long positionA=0,positionT=0,positionC=0,positionG=0;
long beforeA=0,beforeC=0,beforeG=0,beforeT=0;
long matchStart,matchEnd;
long final=-1;
long A=0,T=0,C=0,G=0;


void fC();
void OC();
long Occ(char c,long r);
long LF(long r);
long functionC(char c);
int judge(long A);
void Unpermute();
void textMerge();
void radixSort(vector<string>  * kmers, int num);
void getbwt();
string getNtimes21(long number, long n);
void nextSort(int nl);
void filemerge(int index, int num, string pathprefix);
void  radixSort(vector<string>  * kmers, int num);
long getradix(string s);
fstream* sort();
void match();
long OccForMatch(char c, long long r);
void beforePosition();
long functionCforMatch(char c);
long LFC(char temp,long r);
void change();
void initiate();
void encodeByLong();
int main(int argc, const char * argv[]) {
    long start = clock();
    //change();
    //initiate();
    //sort();
    //nextSort(21);
    //OC();
    //textMerge();
    //Unpermute();
    //cout<<LONG_LONG_MAX<<endl;
    match();
    //encodeByLong();
    printf("%.3lf\n",double(clock()-start)/CLOCKS_PER_SEC);
    
}

void OC()
{
    ifstream filein("/Users/zhuhua/Desktop/BWTresult.txt");
    if (!filein.is_open()){
        std::cout << "文件未打开成功" << std::endl;
        exit(0);
    }
    ofstream fileout("/Users/zhuhua/Desktop/OCresult.txt");
    char temp;
    int i=0;
    int j = 0;
    int judgeA=0,judgeT=0,judgeC=0,judgeG=0,judgeJ=0;
    fileout<<"A"<<"         "<<"T"<<"         "<<"C"<<"         "<<"G"<<"         "<<"j         "<<"\n";
    while(j<224998620){
        filein.get(temp);
        if(temp=='A'){
            A++;
        }
        if(temp=='T'){
            T++;
        }
        if(temp=='C'){
            C++;
        }
        if(temp=='G'){
            G++;
        }
        judgeA=judge(A);
        judgeT=judge(T);
        judgeC=judge(C);
        judgeG=judge(G);
        judgeJ=judge(j);
        fileout<<A;
        for(i=0;i<judgeA;i++){
            fileout<<" ";
        }
        fileout<<T;
        for(i=0;i<judgeT;i++){
            fileout<<" ";
        }
        fileout<<C;
        for(i=0;i<judgeC;i++){
            fileout<<" ";
        }
        fileout<<G;
        for(i=0;i<judgeG;i++){
            fileout<<" ";
        }
        fileout << j;
        for(i=0;i<judgeJ;i++){
            fileout<<" ";
        }
        fileout<<"\n";
        j++;
    }
}
int judge(long A){
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
    if(1000000<=A&&A<10000000){
        return 3;
    }
    if(10000000<=A&&A<100000000){
        return 2;
    }
    if(A>=100000000){
        return 1;
    }
    return 0;
}
long Occ(char c,long r)//求BWT序列中，第r个字符前  字符c出现的次数
{
    ifstream filein("/Users/zhuhua/Desktop/OCresult.txt");
    char temp[10];
    long position=0;
    int i=judge(r);
    int j=0;
    long count=0;
    string line;
    if(r==-1){
        r=0;
    }
    //cout<<"OCCr="<<r<<endl;
    if(c=='A')
    {
        position=(r)*51;
        filein.seekg(position,ios::beg);
        for(;i<10;i++){
            filein.get(temp[j]);
            j++;
        }
        count=atol(temp);
    }
    if(c=='T')
    {
        position=(r)*51+10;
        filein.seekg(position,ios::beg);
        for(;i<10;i++){
            filein.get(temp[j]);
            j++;
        }
        count=atol(temp);
    }
    
    if(c=='C')
    {
        position=(r)*51+20;
        filein.seekg(position,ios::beg);
        for(;i<10;i++){
            filein.get(temp[j]);
            j++;
        }
        count=atol(temp);
    }
    
    if(c=='G')
    {
        position=(r)*51+30;
        filein.seekg(position,ios::beg);
        for(;i<10;i++){
            filein.get(temp[j]);
            j++;
        }
        count=atol(temp);
    }
    //cout<<"count="<<count<<endl;
    return count;
}



long functionC(char c)
{
    ifstream filein("/Users/zhuhua/Desktop/BWTfirstletter.txt");
    char temp;
    long i;
    long length=224999720;
    if((positionA!=0)&&(c=='A')){
        //cout<<"C="<<positionA<<endl;
        return positionA;
    }
    if((positionC!=0)&&(c=='C')){
        //cout<<"C="<<positionC<<endl;
        return positionC;
    }
    if((positionG!=0)&&(c=='G')){
        //cout<<"C="<<positionG<<endl;
        return positionG;
    }
    if((positionT!=0)&&(c=='T')){
        //cout<<"C="<<positionT<<endl;
        return positionT;
    }
    
    for (i=0;i<length; i++)
    {
        filein.get(temp);
        if (temp==c)
        {
            if(temp=='A'){
                positionA=i;
                //cout<<"C="<<positionA<<endl;
            }
            if(temp=='T'){
                positionT=i;
                //cout<<"C="<<positionT<<endl;
            }
            if(temp=='C'){
                positionC=i;
                //cout<<"C="<<positionC<<endl;
            }
            if(temp=='G'){
                positionG=i;
                //cout<<"C="<<positionG<<endl;
            }
            break;
        }
    }
    return i;
}

long LF(long r)
{
    ifstream filein("/Users/zhuhua/Desktop/BWTresult.txt");
    char temp;
    filein.seekg(r,ios::beg);
    filein.get(temp);
    long i=functionC(temp)+Occ(temp,r);
    //cout<<"LFi="<<i<<endl;
    return i;
}

void Unpermute()
{
    ifstream filein("/Users/zhuhua/Desktop/BWTresult.txt");
    ofstream fileout("/Users/zhuhua/Desktop/unpermuteSequence.txt");
    long r = 0;
    string sequence;
    char BwtSequenceR;
    filein.get(BwtSequenceR);
    while (BwtSequenceR!='$')
    {
        fileout<<BwtSequenceR;
        //sequence = BwtSequenceR+sequence;
        r = LF(r);
        filein.seekg(r, ios::beg);
        filein.get(BwtSequenceR);
    }
    
    fileout.close();
    
    
    ifstream rewrite("/Users/zhuhua/Desktop/unpermuteSequence.txt",ios::ate);
    if (!rewrite.is_open()){
        std::cout << "文件未打开成功" << std::endl;
        exit(0);
    }
    long position=rewrite.tellg();
    
    position=position-1;
    cout<<position<<endl;
    rewrite.seekg(position,ios::beg);
    ofstream finalResult("/Users/zhuhua/Desktop/finalResult.txt");
    for( long start=position;start>=0;start--){
        rewrite.get(BwtSequenceR);
        cout<<BwtSequenceR;
        finalResult<<BwtSequenceR;
        position=position-1;
        rewrite.seekg(position,ios::beg);
    }
    //fileout<<sequence;
    
}

void textMerge(){
    char temp;
    ifstream filein[24];
    ofstream fileout("/Users/zhuhua/Desktop/BWTresult.txt");
    char ch[23];
    string pathprefix="/Users/zhuhua/Desktop/bwt/";
    for(int i=1;i<=23;i++)
    {
        sprintf(ch, "%d", i);
        string filepath = pathprefix + ch + ".txt";
        filein[i].open(filepath);
        while(filein[i].peek() != EOF){
            filein[i].get(temp);
            fileout<<temp;
        }
        filein[i].close();
    }
    
}
long changeFromBinary(char* temp){
    int n=0;        // 二进制位数
    long w=1;        // 当前位权重
    unsigned long number=0;    // 十进制值
    char* p=temp;
    while(*p>='0' && *p++<='1')
    {
        n++; // 只能是1或0----这里注意：后缀++的优先级高于解引用*的优先级
    }
    while(n--)
    {
        number += (temp[n]-'0')*w;
        w*=2;
    }
    return number;
}
void encodeByLong(){
    ifstream filein("/Users/zhuhua/Desktop/BWTresult.txt");
    char temp;
    string combine;
    long result;
    int j=0;
    char numbers[64];
    unsigned long binary;
    ofstream rs("/Users/zhuhua/Desktop/EncodeTest.bin",ios::binary);
    while(counting<224998617){
        filein.get(temp);
        if(temp=='A'){
            numbers[j*2]='0';
            numbers[j*2+1]='0';
            combine=combine+"0";
            //cout<<numbers[j]<<numbers[j+1];
        }
        if(temp=='C'){
            numbers[j*2]='0';
            numbers[j*2+1]='1';
            combine=combine+"1";
            //cout<<numbers[j]<<numbers[j+1];
        }
        if(temp=='G'){
            numbers[j*2]='1';
            numbers[j*2+1]='0';
            combine=combine+"2";
            //cout<<numbers[j]<<numbers[j+1];
        }
        if(temp=='T'){
            numbers[j*2]='1';
            numbers[j*2+1]='1';
            combine=combine+"3";
            //cout<<numbers[j]<<numbers[j+1];
        }
        counting++;
        j++;
        if(j%32==0){
            result=(long)atol(combine.c_str());
            //cout<<result<<endl;
            binary=changeFromBinary(numbers);
            rs.write((char*)&binary,sizeof(unsigned long));
            combine="";
            j=0;
        }
        
        
        
    }
    rs.close();
}
void encodeByString(){
    ifstream filein("/Users/zhuhua/Desktop/BWTresult.txt");
    char temp;
    string combine;
    long result;
    int j=0;
    ofstream rs("/Users/zhuhua/Desktop/EncodeTestByString.bin",ios::binary);
    while(counting<224998617){
        filein.get(temp);
        if(temp=='A'){
            combine=combine+"0";
        }
        if(temp=='C'){
            combine=combine+"1";
        }
        if(temp=='G'){
            combine=combine+"2";
        }
        if(temp=='T'){
            combine=combine+"3";
        }
        counting++;
        j++;
        if(j%16==0){
            //result=(long)atol(combine.c_str());
            //cout<<combine<<endl;
            rs.write((char*)&combine,sizeof(long));
            combine="";
            j=0;
        }
        
        
    }
    rs.close();
}
void decode(){
    ifstream filein("/Users/zhuhua/Desktop/EncodeTest.bin",ios::binary);
    ofstream fileout("/Users/zhuhua/Desktop/DecodeTest.txt");
    string temp;
    while(filein.peek()!=EOF){
        filein>>temp;
        cout<<temp<<endl;
        //fileout<<temp<<endl;
        
    }
}
void change(){
    ifstream filein("/Users/zhuhua/Desktop/sequence.txt");
    ofstream fileout("/Users/zhuhua/Desktop/sequenceTemp.txt");
    if (!filein.is_open()){
        std::cout << "文件未打开成功" << std::endl;
        exit(0);
    }
    char temp;
    int i = 0;
    while (filein.get(temp)){
        if (temp == 'A' || temp == 'T' || temp == 'C' || temp == 'G')
        {
            i++;
            fileout << temp;
        }
    }
    fileout << '$';
    filein.close();
    ifstream filein1("/Users/zhuhua/Desktop/sequenceTemp.txt");
    for (int i = 0; i<210; i++)
    {
        filein1.get(temp);
        if (temp != 'N'&&temp != '\n')
        {
            fileout << temp;
        }
    }
    
}


void initiate()
{
    ifstream filein("/Users/zhuhua/Desktop/sequenceWith$.txt");
    if (!filein.is_open()){
        std::cout << "文件未打开成功" << std::endl;
        exit(0);
    }
    ofstream fileout("/Users/zhuhua/Desktop/reads.txt");
    char temp;
    long j = 0;
    int k = 0;
    while (j < 224999720)
    {
        filein.get(temp);
        fileout << temp;
        k++;
        if (k % 21 == 0)
        {
            k = 0;
            fileout << " ";
            fileout << j;
            j++;
            fileout << "\n";
            filein.seekg(j, ios::beg);
        }
    }
}
string getNtimes21(long number, long n)
{
    string str;
    ifstream filein("/Users/zhuhua/Desktop/reads.txt");
    if (!filein.is_open()){
        std::cout << "文件未打开成功" << std::endl;
        exit(0);
    }
    char temp;
    filein.seekg(number+(n-1)*21, ios::beg);
    char s[21];
    for (int i = 0; i < 21; i++)
    {
        filein.get(temp);
        s[i] = temp;
    }
    str = string(s);
    return str;
}


fstream* sort()
{
    
    string filepath;
    filepath = "/Users/zhuhua/Desktop/reads.txt";
    vector<string>kmers1;
    ifstream fin(filepath);
    int num = 0;
    int count = 0;
    thread t[THREADNUM];
    int i;
    while (fin.peek() != EOF)
    {
        num = 0;
        while (num < THREADNUM)
        {
            num++;
            vector<string>* kmers = new vector<string>;
            for (i = 0; i < 5000000; i++)
            {
                char ch[60];
                fin.getline(ch, 60);
                if (strcmp(ch, "") == 0)
                {
                    for (int m = 0; m < num - 1; m++)
                    {
                        t[m].join();
                    }
                    thread(radixSort, kmers, ++count).join();
                    return NULL;
                }
                
                (*kmers).push_back(ch);
            }
            t[num - 1] = thread(radixSort, kmers, ++count);
        }
        for (int i = 0; i < THREADNUM; i++)
        {
            t[i].join();
        }
    }
    return NULL;
}

long getradix(string s)
{
    long value[7];
    long result = 0;
    int i = 0;
    for (i = 0; i < 7; i++)
    {
        //cout << s[i];
        if (s[i] == '$')
        {
            value[i] = 0;
        }
        if (s[i] == 'A')
        {
            value[i] = 1;
        }
        else if (s[i] == 'C')
        {
            value[i] = 2;
        }
        else if (s[i] == 'G')
        {
            value[i] = 3;
        }
        else if (s[i] == 'T')
        {
            value[i] = 4;
        }
    }
    result = value[0] * 15625 + value[1] * 3125 + value[2] * 625 + value[3] * 125 + value[4] * 25 + value[5] * 5 + value[6] * 1;
    return result;
}

void  radixSort(vector<string>  * kmers, int num)
{
    long length = (*kmers).size();
    vector<string>kmers1(length);
    long  radixcount[N];
    long *radix = new long[length];
    string s1, s2, temp_s,flat,str;
    //后7
    for (int i = 0; i <N; i++)
    {
        radixcount[i] = 0;
    }
    for (int i = 0; i < length; i++)
    {
        
        radix[i] = getradix((*kmers)[i].substr(14, 7));
        radixcount[radix[i]]++;
    }
    for (long i = 1; i < N; i++)
    {
        radixcount[i] += radixcount[i - 1];
    }
    for (long i = length - 1; i >= 0; i--)
    {
        kmers1[radixcount[radix[i]] - 1] = (*kmers)[i];
        radixcount[radix[i]]--;
        
    }

    
    //中间7
    for (int i = 0; i <N; i++)
    {
        radixcount[i] = 0;
    }
    for (int i = 0; i < length; i++)
    {
        radix[i] = getradix(kmers1[i].substr(7, 7));
        radixcount[radix[i]]++;
    }
    
    for (int i = 1; i < N; i++)
    {
        radixcount[i] += radixcount[i - 1];
    }
    
    for (long i = length - 1; i >= 0; i--)
    {
        (*kmers)[radixcount[radix[i]] - 1] = kmers1[i];
        radixcount[radix[i]]--;
    }
    
    //前7
    for (int i = 0; i <N; i++)
    {
        radixcount[i] = 0;
    }
    for (int i = 0; i < length; i++)
    {
        radix[i] = getradix((*kmers)[i].substr(0, 7));
        radixcount[radix[i]]++;
    }
    
    for (int i = 1; i < N; i++)
    {
        radixcount[i] += radixcount[i - 1];
    }
    
    for (long i = length - 1; i >= 0; i--)
    {
        kmers1[radixcount[radix[i]] - 1] = (*kmers)[i];
        radixcount[radix[i]]--;
    }

    char buffer[20];
    sprintf(buffer, "%d", num);
    string resultpath = string(buffer) + ".txt";
    ofstream fout(resultpath);
    for (int i = 0; i < length; i++)
    {
        fout << kmers1[i] << endl;
    }
    fout.close();
    delete[]radix;
    delete kmers;
    return;
    
    
}

void filemerge(int index, int num, string pathprefix)
{
    ifstream * fin = new ifstream[num];
    bool flag = true;//文件是否都结束标志变量
    bool * isend = new bool[num];
    string *kmer = new string[num];//存储kmer
    char ch[100];
    sprintf(ch, "%d", index);
    string filepath = pathprefix + "0.txt";
    char buffer[20];
    filepath ="1_0.txt";
    ofstream fout(filepath);
    //先打开文件
    for (int i = 0; i < num; i++)
    {
        sprintf(ch, "%d", index++);
        filepath = pathprefix + ch + ".txt";
        fin[i].open(filepath);
        //cout << filepath;
        
    }
    //扫描文件列表,将未到末尾文件从中取出一条记录存到kmer数组里，并将isend[i]设为真，否则设为假；
    for (int i = 0; i < num; i++)
    {
        //如果不是文件末尾
        if (fin[i].peek() != EOF)
        {
            isend[i] = true;
            fin[i].getline(ch, 100);
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
        for (int i = j + 1; i < num; i++)
        {
            if (!isend[i])
            {
                continue;
            }
            if (kmer[j].compare(0, 21, kmer[i], 0, 21)>0)
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
            fin[j].getline(ch, 100);
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



void nextSort(int nl)
{
    int m = 1, k = 1, number;
    int length = 5000;
    string kmers3[5000];
    string kmers2[5000];
    string stri[5000];
    long h[5000];
    int64_t linem = 0, linek = 0;
    char buffer[20];
    string s1, s2, temp_s;
    string flag = "NNNNNNNNNNNNNNNNNNNNN";
    string str;
    sprintf(buffer, "%d", 7);
    string resultpath = string(buffer) + "_0.txt";
    ofstream fout(resultpath);
    sprintf(buffer, "%d", 6);
    string inpath = string(buffer) + "_0.txt";
    ifstream finm(inpath);
    ifstream fink(inpath);
    while (m == 1)
    {
        flag = "NNNNNNNNNNNNNNNNNNNNN";
        linem = finm.tellg();
        char ch1[60];
        finm.getline(ch1, 60);
        if (strcmp(ch1, "") == 0)
        {
            break;
        }
        string sm = string(ch1);
        s1 = sm.substr(0, 21);
        linek = finm.tellg();
        number = 1;
        //96099145
        fink.seekg(linek, ios::beg);
        while (k == 1)
        {
            if (s1 == flag)
            {
                break;
            }
            char ch2[60];
            fink.getline(ch2, 60);
            if (strcmp(ch2, "") == 0)
            {
                break;
            }
            string sk = string(ch2);
            s2 = sk.substr(0, 21);
            if (s1 == s2)
            {
                number++;
                
            }
            if (number > 1 && s1 != s2)
            {
                break;
            }
            
            if (s1 != s2)
            {
                break;
            }
            
            
        }
        
        
        if (number == 1)
        {
            
            flag = "NNNNNNNNNNNNNNNNNNNNN";
            str = sm.substr(22, 60);
            flag = flag + " " + str;
            fout << flag << endl;
        }
        
        if (number > 1)
        {
            //	cout << number<<" ";
            finm.seekg(linem, ios::beg);
            for (int j = 0; j < number; j++)//取出序号和字符
            {
                //cout << j << endl;
                char ch1[60];
                finm.getline(ch1, 60);
                string sm = string(ch1);
                stri[j] = sm.substr(22, 60);
                
                //str = jumpline(m, inpath).substr(22, 60);
                h[j] = std::atoi(stri[j].c_str());
                
                
                temp_s = getNtimes21(h[j], nl);
                kmers3[j] = temp_s;
                
                
                
            }
            
            
            
            int temp_f=1;
            int count = 0;
            
            
            
            
            do
            {
                temp_f = 1;
                for (int j = 0; j < number; j++)
                {
                    
                    for (int k = 1; k <= 10; k++)
                    {
                        string fu = getNtimes21(h[j],nl+10*count+k);
                        //cout << fu << endl;
                        kmers3[j] = kmers3[j] + fu;
                        //cout << kmers3[j] << endl;
                    }
                    
                }
                
                for (int j = 0; j < number; j++)
                {
                    kmers2[j] = kmers3[j] + " " + stri[j];
                }
                
                sort(kmers2, kmers2 + number);
                sort(kmers3, kmers3 + number);
                
                for (int j = 0; j < number - 1; j++)
                {
                    if (kmers3[j] == kmers3[j + 1])
                    {
                        temp_f = 0;
                        break;
                    }
                }
                
                count++;
                
            } while (temp_f == 0);
            
            
            int length = 21 + count*10*21;
            long str_len = kmers2[0].length();
            for (int j = 0; j < number; j++)
            {
                string s = kmers2[j].substr(length + 1, str_len);
                s = flag + " " + s;
                fout << s<<endl;
            }
        }
    }
    
    
}


void getbwt()
{
    ifstream filein1("/Users/zhuhua/Desktop/7_0.txt");
    ifstream filein2("/Users/zhuhua/Desktop/sequenceWith$.txt");
    ofstream fileout1("/Users/zhuhua/Desktop/BWTresult.txt");
    ofstream fileout2("/Users/zhuhua/Desktop/BWTfirstletter.txt");
    ofstream fileout3("/Users/zhuhua/Desktop/number.txt");
    char ch[60];
    filein1.getline(ch, 60);
    while (strcmp(ch,"")!=0)
    {
        string s;
        s = ch;
        s = s.substr(22, 60);
        fileout3 << s << endl;
        long num = std::atoi(s.c_str());
        filein2.seekg(num, ios::beg);
        char c;
        filein2.get(c);
        fileout2 << c;//输出first
        if (num == 0)
        {
            fileout1 << '$';
        }
        else
        {
            num = num - 1;
            filein2.seekg(num, ios::beg);
            filein2.get(c);
            fileout1 << c;
        }
        filein1.getline(ch, 60);
    }
    
    
    
    
}


void beforePosition()
{
    ifstream filein("/Users/zhuhua/Desktop/BWTfirstletter.txt");
    char temp;
    long i=-1;
    while (filein.get(temp))
    {
        i++;
        if (temp == 'A'&&positionA==0){
            positionA = i;
            if (beforeA == 0){
                beforeA = i - 1;
            }
        }
        if (temp == 'T'&&positionT==0){
            positionT = i;
            if (beforeT == 0){
                beforeT = i - 1;
            }
        }
        if (temp == 'C'&&positionC==0){
            positionC = i;
            if (beforeC == 0){
                beforeC = i - 1;
            }
        }
        if (temp == 'G'&&positionG==0){
            positionG = i;
            if (beforeG == 0){
                beforeG = i - 1;
            }
        }
        final++;		
    }
    
}


long LFC(char temp,long r)
{
    
    long i = functionC(temp)-1 + Occ(temp, r+1);
    //cout<<"LFi="<<i<<endl;
    return i;
}


void match()
{
    beforePosition();//初始化position before
    ifstream fin("/Users/zhuhua/Desktop/search.txt");
    string p;
    char c;
    long len = 0;
    while (fin.get(c))
    {
        p = p + c;
        len++;
    }
    len = len - 1;
    c = p[len];
    long long sp = 0, ep = 0;
    sp = functionC(c);
    //cout << sp;
    if (c == 'A')
    {
        if (beforeC != 0)
        {
            ep = beforeC;
        }
        if (beforeC == 0&&beforeG!=0)
        {
            ep = beforeG;
        }
        if (beforeC == 0 && beforeG == 0&&beforeT!=0)
        {
            ep = beforeT;
        }
        if (beforeC == 0 && beforeG == 0 && beforeT == 0)
        {
            ep = final;
        }
    }
    if (c == 'C')
    {
        if (beforeG != 0)
        {
            ep = beforeG;
        }
        if (beforeG == 0 && beforeT != 0)
        {
            ep = beforeT;
        }
        if (beforeG == 0 && beforeT == 0)
        {
            ep = final;
        }
    }
    if (c == 'G')
    {
        if (beforeT != 0)
        {
            ep = beforeT;
        }
        if (beforeT == 0)
        {
            ep = final;
        }
    }
    if (c == 'T')
    {
        ep =final;
    }
    long long i = len - 1;
    while (sp<=ep&&i>=0)
    {
        
        c = p[i];
        sp = LFC(c, sp);
        ep = LFC(c, ep);
        //cout << sp << " "<<ep << endl;
        i = i - 1;
    }
    ifstream fin2("/Users/zhuhua/Desktop/number.txt");
    char ch[60];
    for (long i = 0; i <=ep; i++)
    {
        fin2.getline(ch, 60);
        if (i >=sp)
        {
            cout << "匹配序列在原序列的位置是"<<ch<<endl;
        }
    }
    
    
    
}


