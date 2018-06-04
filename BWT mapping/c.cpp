//
//  main.cpp
//  BWT mapping
//
//  Created by zh on 15/3/13.
//  Copyright (c) 2015年 zh. All rights reserved.
//




//AGCTAGGGTC
//CTAGGG


using namespace std;
#include<string.h>
#include <fstream>
#include<stdlib.h>
#include <iostream>
#include<time.h>
#include <algorithm>
string origin="AGCTAGGGTC";
string sequence="AGCTAGGGTC$";
string BWT,BWTfirst;
string matrix[11];
void Unpermute();
int main(int argc, const char * argv[]) {
    int i=0;
    for(i=0;i<11;i++){
        matrix[i]=sequence.substr(i,11-i)+sequence.substr(0,i);
        //cout<<matrix[i]<<endl;
    }
    sort(matrix,matrix+11);
    for(i=0;i<11;i++){
        BWT=BWT+matrix[i][10];
        BWTfirst=BWTfirst+matrix[i][0];
    }
    cout<<BWT<<endl;
    Unpermute();
    
    
    return 0;
}


int Occ(char c,int r)//求BWT序列中，第r个字符前  字符c出现的次数
{
    int count = 0;
    for (int i=0; i < r; i++)//第r个字符前  字符c出现的次数
    {
        if (c==BWT[i])
        {
            count++;
        }
        
    }
    return count;
}


int C(char c)
{
    int i;
    string BWTfirst;
    for (i=0;i<11; i++)
    {
        if (BWTfirst[i]==c)
        {
            break;
        }
    }
    cout<<"Ci="<<i<<endl;
    return i;
}

int LF(int r)
{
    char c=BWT[r];
    cout<<"c="<<c<<endl;
    int i=C(c)+Occ(c,r) ;
    return i;
}

void Unpermute()
{
        int r = 0;
        string sequence;
        while (BWT[r]!='$')
        {
            sequence = BWT[r] + sequence;
            r = LF(r);
        }
    cout<<sequence;
}


