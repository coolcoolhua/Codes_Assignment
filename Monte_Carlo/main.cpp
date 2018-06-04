//
//  main.cpp
//  Monte Carlo
//
//  Created by zh on 15/8/6.
//  Copyright (c) 2015年 zh. All rights reserved.
//
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    int i;
    double x,y;
    double count;
    for(i=0;i<1000000;i++){
        x=(double)rand()/RAND_MAX;
        y=(double)rand()/RAND_MAX;
        if(x*x+y*y<=1){
            count++;
        }
    }
    cout<<"count="<<count<<endl;
    cout<<"Pi="<<4*count/1000000<<endl;
}
