#include<stdio.h>
#include<iostream>
#include<cassert>
#include<cstring>
using namespace std;

#define MAXSIZE 20

class HString
{
    public:
    char *ch;
    int length;
};

void Init(HString &s)
{
    s.ch=NULL;
    s.length=0; 
    //s.ch=new char(MAXSIZE);
}

void Assign(HString &s,char *t)
{
    int t_len=strlen(t);
}
int main()
{
    HString s;
}