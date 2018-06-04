//
//  main.cpp
//  Nei_gojobori
//
//  Created by zh on 15/5/12.
//  Copyright (c) 2015年 zh. All rights reserved.
//
using namespace std;
#include <iostream>
#include <string>
float sd=0,nd=0,sum=0;
void scan();
float calculate(string A);
void transcript1(string A);
void transcript2(string A);
float Sn(string A);
int counting=1;
float S=0,N=0;
float S1,S2;
float trans=0;
float transSum=0,R;
void countTrans();
string A2301="GCCTCCCACTCCATGAGGTATTCCACATCCCTGTCCCGGDCCGGCCGCGGGGAGCCCCGCTTCATCGCCGTGGGCTACGTGGACGACACGCAGTTCGTGCGGTTCGACAGCGACGCCGCGAGCCAGAGGATGGAGCCGCGGGCGCCGTGGATAGAGCAGGAGGGGCCGGAGTATTCGGACGAGGAGACAGGGAAAGTGAAGGCCCACTCACAGACTGACCGAGAGAACCTGCGGATCGCGCTCCGCTACTACAACCAGAGCGAGGCCGGTTCTCACACCCTCCAGATGATGTTTGGCTGCGACGTGGGGTCGGACGGGCGCTTCCTCCGCGGGTACCACCAGTACGCCTACGACGGCAAGGATTACATCGCCCTGAAAGAGGACCTGCGCTCTTGGACCGCGGCGGACATGGCGGCTCAGATCACCCAGCGCAAGTGGGAGGCGGCCCGTGTGGCGGAGCAGTTGAGAGCCTACCTGGAGGGCACGTGCGCCGACGGGCTCCGCAGATACCTGGAGAACGGGAAGGAGACGCTGCAGCGCACGGACCCCCCCAAGACACATATGACCCACCACCCCATCTCTGACCATGAGGCCACTCTGAGATGCTGGGCCCTGGGCTTCTACCCTGAGGAGATCACACTGACCTGGCAGCGGGATGGGGAGGACCAGACCCAGGACACGGAGCTTGTGGAGACCAGGCCTGCAGGGGATGGAACCTTCCAGAAGTGGGCAGCTGTGGTGGTACCTGCTGGAGAGGAGCAGAGATACACCTGCCATGTGCAGCATGAGGGTCTGCCCAAGCCCCTCACCCTGAGATGGTGG";
string A2501="GCCTCCCACTCCATGAGGTATTACACCTCCCTGTCCCGGDCCGGCCGCGGGGAGCCCCGCTTCATCGCCGTGGGCTACGTGGACGACACGCAGTTCGTGCGGTTCGACAGCGACGCCGCGAGCCAGAGGATGGAGCCGCGGGCGCCGTGGATAGAGCAGGAGGGGCCGGAGTATTCGGACCGGAACACACGGAATGTGAAGGCCCACTCACAGACTGACCGAGAGAGCCTGCGGATCGCGCTCCGCTACTACAACCAGAGCGAGGACGGTTCTCACACCATCCAGAGGATGTATGGCTGCGACGTGGGGCCGGACGGGCGCTTCCTCCGCGGGTACCAGCAGGACGCTTACGACGGCAAGGATTACATCGCCCTGAACGAGGACCTGCGCTCTTGGACCGCGGCGGACATGGCGGCTCAGATCACCCAGCGCAAGTGGGAGACGGCCCATGAGGCGGAGCAGTGGAGAGCCTACCTGGAGGGCCGGTGCGCCGAGTGGCTCCGCAGATACCTGGAGAACGGGAAGGAGACGCTGCAGCGCACGGAGCCCCCCAAGACGCATATGACTCACCACGCTGTCTCTGACCATGAGGCCACCCTGAGGTGCTGGGCCCTGAGCTTCTACCCTGAGGAGATCACACTGACCTGGCAGCGGGATGGGGAGGACCAGACCCAGGACACGGAGCTCGTGGAGACCAGGCCTGCAGGGGATGGGACCTTCCAGAAGTGGGCGTCTGTGGTGGTGCCTGCTGCACAGGAGCAGAGATACACCTGCCATGTGCAGCATGAGGGTCTGCCCAAGCCCCTCACCCTGAGATGGTGG";
string A3301="GCCTCCCACTCCATGAGGTATACCACATCCCTGTCCCGGDCCGGCCGCGGGGAGCCCCGCTTCATCGCCGTGGGCTACGTGGACGACACGCAGTTCGTGCGGTTCGACAGCGACGCCGCGAGCCAGAGGATGGAGCCGCGGGCGCCGTGGATAGAGCAGGAGGGGCCGGAGTATTCGGACCGCAACACACGGAATGTGAAGGCCCACTCACAGATTGACCGAGTGGACCTGGGGACCCTGCGCGGCTACTACAACCAGAGCGAGGCCGGTTCTCACACACTCCAGATGATGTATGGCTGCGACGTGGGGTCGGACGGGCGCTTCCTCCGCGGGTACCAGCAGTACGCCTACGACGGCAAGGATTACATCGCCTTGAACGAGGACCTGCGCTCTTGGACCGCGGCGGACATGGCGGCTCAGATCACCCAGCGCAAGTGGGAGGCGGCCCGTGTGGCGGAGCAGTTGAGAGCCTACCTGGAGGGCACGTGCGCCGAGTGGCTCCGCAGACACCTGGAGAACGGGAAGGAGACGCTGCAGCGCACGGACCCCCCCAGGACGCATATGACTCACCACGCTGTCTCTGACCATGAGGCCACTCTGAGGTGCTGGGCCCTGAGCTTCTACCCTGAGGAGATCACACTGACCTGGCAGCGGGATGGGGAGGACCAGACCCAGGACACGGAGCTCGTGGAGACCAGGCCTGCAGGGGATGGGACCTTCCAGAAGTGGGCGTCTGTGGTGGTGCCTGCTGCACAGGAGCAGAGATACACCTGCCATGTGCAGCATGAGGGTCTCCCCAAGCCCCTCACCCTGAGATGGTGG";
string AA2301,AA2501,AA3301;
int main(int argc, const char * argv[]) {
    cout<<"sd"<<"   "<<"sn"<<endl;
    scan();
    countTrans();
    R=trans/(2*transSum);
    cout<<"转换数 颠换数 转换数/2倍颠换数"<<endl;
    cout<<trans<<"    "<<transSum<<"    "<<R<<endl;
    transcript1(A2301);
    transcript2(A2501);
    S1=Sn(A2301);
    S2=Sn(A2501);
    S=(S1+S2)/2;
    N=822-S;
    cout<<"S"<<"       "<<"N"<<endl;
    cout<<S<<" "<<N<<endl;
    cout<<"Ps"<<"        "<<"Pn"<<endl;
    cout<<sd/S<<" "<<nd/N<<endl;
    
}

void scan(){
    int i;
    string temp1,temp2;
    string temp="";
    for(i=0;i<822;i++){
        temp1=temp1+A2301[i];
        temp2=temp2+A2501[i];
            if((strlen(temp1.c_str())==3)){
                counting++;
                if(temp1=="TCC"&temp2=="TAC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="ACA"&temp2=="ACC"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="GAG"&temp2=="CGG"){
                    nd++;nd++;temp1="";temp2="";
                }
                if(temp1=="GAG"&temp2=="AAC"){
                    nd++;nd++;temp1="";temp2="";
                }
                if(temp1=="GGG"&temp2=="CGG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="AAA"&temp2=="AAT"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="AAC"&temp2=="AGC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="GCC"&temp2=="GAC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="CTC"&temp2=="ATC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="ATG"&temp2=="AGG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="TTT"&temp2=="TAT"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="TCG"&temp2=="CCG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="CAC"&temp2=="CAG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="TAC"&temp2=="GAC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="GCC"&temp2=="GCT"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="AAA"&temp2=="AAC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="GCG"&temp2=="ACG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="CGT"&temp2=="CAT"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="GTG"&temp2=="GAG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="TTG"&temp2=="TGG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="ACG"&temp2=="CGG"){
                    nd=nd+1.5;sd=sd+0.5;temp1="";temp2="";
                }
                if(temp1=="GAC"&temp2=="GAG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="GGG"&temp2=="TGG"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="CCC"&temp2=="GCC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="ACA"&temp2=="ACG"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="ACC"&temp2=="ACT"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="CCC"&temp2=="GCT"){
                    nd++;temp1="";temp2="";sd++;
                }
                if(temp1=="ATC"&temp2=="GTC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="ACT"&temp2=="ACC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="AGA"&temp2=="AGG"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="TCC"&temp2=="TAC"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="GGC"&temp2=="AGC"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="CTT"&temp2=="CTC"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="GGA"&temp2=="GGG"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="GCA"&temp2=="GCG"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="GCT"&temp2=="TCT"){
                    nd++;temp1="";temp2="";
                }
                if(temp1=="GTA"&temp2=="GTG"){
                    sd++;temp1="";temp2="";
                }
                if(temp1=="GAG"&temp2=="CAG"){
                    nd++;temp1="";temp2="";
                }
                
                temp1="";
                temp2="";
            }
    }
    cout<<sd<<" "<<nd<<endl;
    sum=sd+nd;
}

float calculate(string A){
    if(A=="UUU"){                      //Phe
        return 0.333;
    }
    if(A=="UUC"){
        return 0.333;
    }
    if(A=="UUA"){                      //Leu
        return 0.333;
    }
    if(A=="UUG"){
         return 0.333;
    }
    if(A=="CUU"){
        return 1;
    }
    if(A=="CUC"){
        return 1;
    }
    if(A=="CUA"){
        return 1.332;
    }
    if(A=="CUG"){
       return 1.332;
    }
    if(A=="AUU"){                     //ILE
        return 0.666;
    }
    if(A=="AUC"){
        return 0.666;
    }
    if(A=="AUA"){
        return 0.666;
    }
    if(A=="AUG"){                     //Met
        return 0;
    }
    if(A=="GUU"){                     //Val
        return 1;
    }
    if(A=="GUC"){
        return 1;
    }
    if(A=="GUA"){
        return 1;
    }
    if(A=="GUG"){
        return 1;
    }
    if(A=="UCU"){                    //Ser
        return 1;
    }
    if(A=="UCC"){
        return 1;
    }
    if(A=="UCA"){
        return 1;
    }
    if(A=="UCG"){
        return 1;
    }
    if(A=="CCU"){                   //Pro
        return 1;
    }
    if(A=="CCC"){
        return 1;
    }
    if(A=="CCA"){
        return 1;
    }
    if(A=="CCG"){
        return 1;
    }
    if(A=="ACU"){                   //Thr
        return 1;
    }
    if(A=="ACC"){
        return 1;
    }
    if(A=="ACA"){
        return 1;
    }
    if(A=="ACG"){
        return 1;
    }
    if(A=="GCU"){                   //Ala
        return 1;
    }
    if(A=="ACU"){
        return 1;
    }
    if(A=="ACU"){
        return 1;
    }
    if(A=="ACU"){
        return 1;
    }
    if(A=="UAU"){                   //Tyr     有疑问
        return 1;
    }
    if(A=="UAC"){
        return 1;
    }
    if(A=="UAA"){
         return 0.333;
    }
    if(A=="UAG"){
         return 0.333;
    }
    if(A=="CAU"){                   //His
         return 0.333;
    }
    if(A=="CAC"){
         return 0.333;
    }
    if(A=="CAA"){                   //Gln
        return 0.333;
    }
    if(A=="CAG"){
        return 0.333;
    }
    if(A=="AAU"){                   //Asn
         return 0.333;
    }
    if(A=="AAC"){
         return 0.333;
    }
    if(A=="AAA"){                   //Lys
         return 0.333;
    }
    if(A=="AAG"){
         return 0.333;
    }
    if(A=="GAU"){                   //Asp
         return 0.333;
    }
    if(A=="GAC"){
         return 0.333;
    }
    if(A=="GAA"){                   //Glu
         return 0.333;
    }
    if(A=="GAG"){
         return 0.333;
    }
    if(A=="UGU"){                   //Cys
        return 0.5;
    }
    if(A=="UGC"){
        return 0.5;
    }
    if(A=="UGA"){                   //stop
        return 0;
    }
    if(A=="UGG"){                   //Trp
        return 0.5;
    }
    if(A=="CGU"){                   //Arg
        return 1;
    }
    if(A=="CGC"){
        return 1;
    }
    if(A=="CGA"){
         return 1.333;
    }
    if(A=="CGG"){
         return 1.333;
    }
    if(A=="AGA"){
         return 1.333;
    }
    if(A=="AGG"){
         return 1.333;
    }
    if(A=="AGU"){                   //Ser
        return 1;
    }
    if(A=="AGC"){
        return 1;
    }
    if(A=="GGU"){                   //Thr
        return 1;
    }
    if(A=="GGC"){
        return 1;
    }
    if(A=="GGA"){
        return 1;
    }
    if(A=="GGG"){
        return 1;
    }
    return 0;
}

void transcript1(string A){
    int i;
    for(i=0;i<822;i++){
        if(A[i]=='A'){
            A2301[i]='U';
        }
        if(A[i]=='T'){
            A2301[i]='A';
        }
        if(A[i]=='C'){
           A2301[i]='G';
        }
        if(A[i]=='G'){
           A2301[i]='C';
        }

    }
    
}
void transcript2(string A){
    int i;
    for(i=0;i<822;i++){
        if(A[i]=='A'){
            A2501[i]='U';
        }
        if(A[i]=='T'){
            A2501[i]='A';
        }
        if(A[i]=='C'){
            A2501[i]='G';
        }
        if(A[i]=='G'){
            A2501[i]='C';
        }
        
    }
    
}



float Sn(string A){
    int i;
    string temp;
    float tt=0;
    for(i=0;i<822;i++){
        temp=temp+A[i];
        if(strlen(temp.c_str())==3){
            tt=tt+calculate(temp);
            temp="";
        }
    }
    return tt;
}

void countTrans(){
    for(int i=0;i<822;i++){
        if(A2301[i]!=A2501[i]){
            transSum++;
            if(A2301[i]=='A'){
                if(A2501[i]=='G'){
                    trans++;
                }
            }
            if(A2301[i]=='C'){
                if(A2501[i]=='T'){
                    trans++;
                }
            }
            if(A2301[i]=='T'){
                if(A2501[i]=='C'){
                    trans++;
                }
            }
            if(A2301[i]=='G'){
                if(A2501[i]=='A'){
                    trans++;
                }
            }
        }
    }
}