#include<iostream>
#include<memory>

using namespace std;

// 封装原始指针 ：智能指针内部持有指向动态分配对象的原始指针。
// 自动释放内存 ：当智能指针超出作用域或引用计数为 0 时，会自动调用 delete 释放内存。
// 防止内存泄漏 ：通过 RAII 机制，确保资源在对象销毁时被正确释放

// void unique()
// {
//     std::unique_ptr<int> ptr= std::make_unique<int>(42);
//     std::unique_ptr<int> ptr3= std::make_unique<int>(35);
//     unique_ptr<int> ptr2=move(ptr);    //独占智能智能 智能使用move不能copy是能有一个指向该对象的智能指针
//     cout<<*ptr2<<endl;
//     cout<<*ptr3<<endl;
// }

// void shared_ptr()
// {
//     //允许多个指针指向同一快内存资源，内部有计数器
//     std::shared_ptr<int> ptr4= std::make_shared<int>(42);
//     std::shared_ptr<int> ptr5(ptr4);      //可以共享
//     cout<<*ptr4<<endl;
//     cout<<*ptr5<<endl;
// }

// void  weak_ptr()
// {

// }

class st
{
    public:
    int num;
    st(){
        cout << "1" << endl;
    };
    ~st(){
        cout << "2" << endl;
    }
};

// void func(int a){}
// void func(int* b){}

int main()
{
    // f + g
    st* a=new st[10];
    delete[] a;

    // f
    st* b=(st*)malloc(sizeof(st));
    // g
    new(b) st;
    // x
    b->~st();
    free(b);

    // f
    st *c = static_cast<st*>(operator new(sizeof(st) * 10));
    // g
    //placement new
    for(int i = 0; i < 10; ++i){
        new(c+i) st;
    }
    // x
    for(int i = 0; i < 10; ++i){
        (c+i)->~st();
    }
    
    operator delete(c);

    char *p;
    st* q = reinterpret_cast<st*>(p);

    // unique();
    return 0;
}


