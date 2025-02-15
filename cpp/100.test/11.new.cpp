#include<iostream>
using namespace std;

int main()
{

    int a=10;
    int *b=&a;
    int** c=&b;
    cout << "a:" << a << endl;
    cout << "b:" << *b << endl;
    cout << "c:" << **c << endl;
    cout<<&a<<endl;
    cout<<b<<endl;
    cout<<*c<<endl;
    cout<<&b<<endl;
    cout<<c<<endl;
    cout<<&c<<endl;
    **c=5;
    cout<<a<<endl;
}