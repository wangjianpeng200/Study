//const修饰指针
//1.const修饰指针———常量指针   const int *p=&a;指针的指向可以修改，但是指针指向的值不能改:p=&a
//2.const修饰常量———指针常量   int * const p=&a； 指针的指向不能修改，但是指针指向的值可以修改。
//3，const既修饰指针又修饰常量  const int * const p=&a; 

#include<iostream>
using namespace std;

int main()
{
    int a=10;
    const int * const p=&a;
}