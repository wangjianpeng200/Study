#include"seqqueue.h"

void test01()
{
    SeqQueue s1;
    for(int i=0;i<8;i++)
    {
        s1.EnLink(s1,i);
    }
    s1.Show(s1);
}

int main()
{
    test01();
    system("pause");
    return 0;
}