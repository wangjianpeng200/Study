#include<iostream>
using namespace std;

class CPU
{
    public:
    virtual void calculator()=0;
};
class GPU
{
    public:
    virtual void dispaly()=0;
};
class me
{
    public:
    virtual void memory()=0;
};

class inter:public CPU
{
    public:
    virtual void calculator()
    {
        cout<<"这是英伟达的CPU"<<endl;
    }
};

class AMD:public GPU
{
   public:
   virtual void dispaly()
   {
    cout<<"这是英伟达的显卡"<<endl;
   }
};

class kingston:public me
{
    public:
    virtual void memory()
    {
        cout<<"这是金士顿的CPU"<<endl;
    }
};

class computer
{
    public:
    computer(CPU *a,GPU *b,me *c):m_cpu(a),m_gpu(b),m_me(c)
    {

    }
    void work()
    {
        m_cpu->calculator();
        m_gpu->dispaly();
        m_me->memory();
    }
    //提供一个析构函数，释放三个电脑零件
    ~computer()
    {
        if(m_cpu!=NULL)
        {
            delete m_cpu;
            m_cpu=NULL;
        }
         if(m_gpu!=NULL)
        {
            delete m_gpu;
            m_gpu=NULL;
        }
         if(m_me!=NULL)
        {
            delete m_me;
            m_me=NULL;
        }
        cout<<"执行析构函数"<<endl;
    }

    private:
    CPU *m_cpu;
    GPU *m_gpu;
    me *m_me;
};

void test01()
{
    CPU *cpu=new inter;
    GPU *gpu=new AMD;
    me *me=new kingston;
    computer c1(cpu,gpu,me);
    c1.work();
}

int main()
{
    test01();
    system("pause");
    return 0;
}