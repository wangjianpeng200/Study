#include<iostream>
using namespace std;

class animal
{
    public:
    void speak()//加了virtueal后变为虚函数
    {
        cout<<"动物在说话"<<endl;//非静态成员才属于类的对象
    }
};

class cat:public animal
{
public:
  void speak()
  {
  cout<<"小猫在说话"<<endl;
  }
};
//在编译阶段就确定了函数的地址
//如果想执行让猫说话，那么这个函数的地址就不能提前绑定，需要在运行的时候再绑定
void Dospeak(animal &animal)
{
    animal.speak();
}

void test01()
{
    cout<<"animal占用的空间为:"<<sizeof(animal);
}

int main()
{
    cat a1;//创建的是子类，但是将父类的引用指向了子类
    Dospeak(a1);
    test01();
    return 0;
}
/*
virtual指针指向一个虚函数表vftable（记录虚函数的进入地址）
*/