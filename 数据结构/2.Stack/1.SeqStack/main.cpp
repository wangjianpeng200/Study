#include"1.h"

void Conert_8(int value)
{
    Seqstack st;
    st.Init(st);
    while(value)
    {
        st.Push(st,value%8);
        value/=8;
    }
    st.Show(st);
}

int main()
{
    int value=47183;
    Conert_8(value);
    return 0;
}