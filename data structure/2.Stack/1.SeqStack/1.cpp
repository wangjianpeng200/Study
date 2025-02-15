#include"1.h"

void Seqstack::Init(Seqstack &seq)
{
    base=new Elemtype[STACK_INIT_SIZE];//创建容积个数的该数据类型   new Elemtype[n]
    assert(base!=NULL);
    top=0;
    capcaity=STACK_INIT_SIZE;
}

 bool Seqstack::IsFull(Seqstack &seq)
 {
    return top>=STACK_INIT_SIZE;
 }

 bool Seqstack::IsEmpty(Seqstack &seq)
 {
    return top==0;
 }

 void Seqstack::Push(Seqstack &seq,Elemtype x)
 {
   if(IsFull(seq)&&!Inc(seq))
   {
      cout<<"该栈已满,不能入栈"<<endl;
      return;
   }
       seq.base[seq.top++]=x;
} 


 void Seqstack::Show(Seqstack &seq)
 {
   for(int i=this->top-1;i>=0;i--)
   {
      cout<<"该栈中的元素有："<<seq.base[i]<<"  ";
   }
 }


void Seqstack::Pop(Seqstack &seq)
{
   if(IsEmpty)
   {
      cout<<"该栈为空，不能出栈"<<endl;
      return;
   }
   seq.top--;//直接top--，掩盖在top中的数据
}

Elemtype Seqstack::GetTop(Seqstack &seq)
{
   if(IsEmpty)
   {
      cout<<"该栈为空"<<endl;
      return;
   }
   return this->base[--this->top];
}

bool Seqstack::Inc(Seqstack &seq)
{
   Elemtype *newbase=new Elemtype(seq.capcaity+Export);
   delete base;
   if(seq.base!=nullptr)
   {
      std::copy(seq.base, seq.base + seq.capcaity, newbase);
   }
   if(newbase ==NULL)
   {
      cout<<"内存不足，无法申请空间"<<endl;
      return false;
   }
  seq.base=newbase;
  seq.capcaity+=Export;
  return true;
}