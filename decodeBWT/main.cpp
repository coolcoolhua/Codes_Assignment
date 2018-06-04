//
//  main.cpp
//  decodeBWT
//
//  Created by zh on 15/6/9.
//  Copyright (c) 2015年 zh. All rights reserved.
//
using namespace std;
#include <iostream>
#include<string>
#include <fstream>
#include<stdlib.h>
#include <iostream>
#include<time.h>
#include <algorithm>
#include<vector>
#include <limits>
void encodeByLong();
void encodeByString();
void decode();
void test();
long counting=0;
long changeFromBinary(char* temp);
int main(int argc, const char * argv[]) {
    //encodeByLong();
    decode();
    //test();
    //encodeByString();
    //char temp[64];
    //cout<<"输入"<<endl;
    //cin>>temp;
    //changeFromBinary(temp);
    //cout<<ULONG_MAX<<" "<<sizeof(unsigned long)<<endl;
    //cout<<INT64_MAX<<" "<<sizeof(int64_t)<<endl;
}




void test(){
    std::ofstream fout("/Users/zhuhua/Desktop/a.dat", std::ios::binary);
    int nNum = 50;
    fout.write((char*)&nNum, sizeof(int));
    cout<<(char*)&nNum;
    fout.close();
    
    
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