#include"linkqueue.h"

void test01()
{
    LinkQueue L1;
    for(int i=0;i<10;i++)
    {
        L1.EnLink(L1,i);
    }
    L1.Show(L1);
}


int main()
{
    test01();
    system("pause");
    return 0;
}