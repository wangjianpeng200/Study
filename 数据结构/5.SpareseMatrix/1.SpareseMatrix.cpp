#include<stdio.h>
#include<iostream>
#include<cassert>
#include<cstring>
#include<fstream>
#include<memory.h>
using namespace std;

using Elemtype=int;
#define MAXSIZE 10

class Triple;
class SMatrix;

void Init(SMatrix &sm);
void Show(SMatrix &sm);
void CopyMatrix(SMatrix &s,SMatrix sm);
void AddMatrix(SMatrix m,SMatrix n,SMatrix &sm);
void SubMatrix(SMatrix m,SMatrix n,SMatrix &sm);
void MulMatrix(SMatrix m,SMatrix n,SMatrix &sm);//在进行矩阵运算前，需要判断行列是否相等
void TransposeMatrix(SMatrix m,SMatrix &T);//转置，行变列，列变行
void FastTransposeMatrix(SMatrix m,SMatrix &t);//快速矩阵转置

class Triple//三元组
{
    public:
    int i;
    int j;
    Elemtype e;
};

class SMatrix
{
    public:
    Triple data[MAXSIZE];
    int mu;//行数
    int nu;//列数
    int num;//非零元素个数
};


void Init(SMatrix &sm)
{
    memset(&sm,0,sizeof(sm)); 
    ifstream ifs;
    ifs.open("test.txt",ios::in);
    if(!ifs.is_open())//判断是否打开成功，如果打开成功返回1；没有打开成功返回0
    {
        cout<<"该文件打开失败"<<endl;
        return;
    }
    ifs>>sm.mu >> sm.nu;//将文件中的行和列读取到稀疏矩阵中
        int value;
        int key_triple=0;
        int num_triple=0;
        //i，j的作用不是在矩阵中为了换行，而是为了表示读取文件时已经自动换行了
    for(int i=0;i<sm.mu;++i)
    {
        for(int j=0;j<sm.nu;++j)
        {
            ifs>>value;
            if(value!=0)
            {
                sm.data[key_triple].e=value;//非零元素的值
                sm.data[key_triple].i=i;//行的值
                sm.data[key_triple].j=j;//列的值
                key_triple++;
                num_triple++;
            }
        }
    }
    sm.num=num_triple;
    ifs.close();
}

void Show(SMatrix &sm)
{
    if(sm.data[0].e==0)
    {
        cout<<"该稀疏矩阵为空"<<endl;
    }
    for(int i=0;i<sm.num;++i)
    {
        cout<<"行数："<<sm.data[i].i<<"  列数："<<sm.data[i].j<<" 值："<<sm.data[i].e<<endl;
    }
}

void CopyMatrix(SMatrix &s,SMatrix sm)
{
    s=sm;
}

void TransposeMatrix(SMatrix m,SMatrix &t)//转置
{
    int tem_nu;
    t.mu=m.nu;
    t.nu=m.mu;
    t.num=m.num;
    int key_t;
    if(m.num!=0)
    {
        for(int col=0;col<m.nu;++col)
        {
            for(int i=0;i<m.num;++i)
            {
                if(m.data[i].j==col)
                {
                    t.data[key_t].j=col;
                    t.data[key_t].i=m.data[i].j;
                    t.data[key_t].e=m.data[i].e;
                    key_t++;
                }
            }
        }
    }
}

void FastTransposeMatrix(SMatrix m,SMatrix &t)//第二种矩阵转置的方法
{
    //简单的拷贝
    t.mu=m.nu;
    t.nu=m.mu;
    t.num=m.num;
    //创建两个堆区存放两个数组
    // int *num_m=new int(m.nu);
    // assert(num_m!=NULL);
    int num_m[10];
    // int *cpot=new int(m.nu);
    // assert(cpot!=NULL);
    int cpot[10];
    //判断边界条件
    if(m.num!=0)
    {
        for(int i=0;i<m.nu;++i)
        {
            num_m[i]=0;
        }
        for(int j=0;j<m.num;++j)
        {
            num_m[m.data[j].j]++;//使用的是数据的元素
        }
        cpot[0]=0;
        for(int col=1;col<m.nu;++col)
        {
            cpot[col]=cpot[col-1]+num_m[col-1];//前一列的起始位置，加上前一列非零元素的个数
        }
        int q=0;
        int col;
        for(int p=0;p<m.num;++p)
        {
            col=m.data[p].j;//先得到该元素的列
            q=cpot[col];//得到该列非零元素的起始位置
            t.data[q].i=m.data[p].j;
            t.data[q].j=m.data[p].i;
            t.data[q].e=m.data[p].e;
            cpot[col]++;//当该列已经存放了一个数据，则下一次存放应该++
        }
    }
}

void testinit()
{
    SMatrix sm;
    memset(&sm,0,sizeof(sm)); 
    Init(sm);
    cout<<"行数："<<sm.mu<<"    列数："<<sm.nu<<endl;
    Show(sm);
}

void testrans()
{
    SMatrix sm1;
    SMatrix sm;
    Init(sm);
    Show(sm);
    cout<<endl<<endl;
    TransposeMatrix(sm,sm1);
    Show(sm1);
}

void TestFastTransposeMatrix()
{
    SMatrix sm1;
    SMatrix sm;
    Init(sm);
    Show(sm);
    cout<<endl<<endl;
    FastTransposeMatrix(sm,sm1);
    Show(sm1);
}

int main()
{
    testrans();
    cout<<"----------------------------------------------------------"<<endl;
    TestFastTransposeMatrix();
    return 0;
}




