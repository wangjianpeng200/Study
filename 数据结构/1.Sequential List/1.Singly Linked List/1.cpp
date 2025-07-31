#include<stdio.h>
#include<iostream>
#include<cassert>
using namespace std;

class ListNode;
typedef ListNode *List;
typedef int ElemType;

class MyList
{
private:
    List first;
    List last;
    int size;
public:
friend class ListNode;//设置友元保护头节点
};

class ListNode
{
public:
  ElemType data;
  ListNode *next;


  //初始化链表
  void InitList(MyList &mylist)
  {
    mylist.first=mylist.last=new(ListNode);
    assert(mylist.first!=NULL);//如果条件为真，程序将继续执行
    mylist.size=0;
    mylist.first->next=NULL;
  }

  //尾插法
  void push_back(MyList &mylist,ElemType x)
  {
    ListNode *s=new(ListNode);
    assert(s!=NULL);
    s->data=x;
    s->next=NULL;
    mylist.last->next=s;
    mylist.last=s;   
    mylist.size++;
  }

  //头插法
  void push_front(MyList &mylist,ElemType x)
  {
    ListNode *s=new(ListNode);
    assert(s!=NULL);
    s->data=x;
    //此时有额外节点的情况
    if(mylist.size!=0)
    {
        s->next=mylist.first->next;
        mylist.first->next=s; 
    }
    //只有头节点
    else
    {
        mylist.last=s;
        mylist.first->next=s; 
        s->next=NULL;
    }
    mylist.size++;
  }


//插入节点，核心是从头开始检索，且好好利用p->next.data
  void insert_val(MyList &mylist,ElemType x)
  {
    //先创建一个节点
    ListNode *s=new(ListNode);
    assert(s!=NULL);
    s->data=x;
    s->next=NULL;
    //创建一个指向节点的，可以移动的，管理链表的指针
    ListNode *p=mylist.first;
    //判断指向的数据不为空，且要插入值要小于x
    while(p->next!=NULL&&p->next->data<x)
    {
        p=p->next;
    }
    //如果已经指向了最后一个，说明没有找到比他大的，需要插入在队尾
    if(p->next==NULL)
    {
        mylist.last=s;
    }
    s->next=p->next;//next指向下一个节点
    p->next=s;//前一个节点指向它
    mylist.size++;
  }

//删除尾部数据
void pop_back(MyList &mylist)
{
  if(mylist.size==0)
  {
    cout<<"该链表为空，不能删除数据"<<endl;
  }
  else if(mylist.size==1)
  {
    delete mylist.last;
    mylist.last=mylist.first;
  }
  else
  {
  ListNode *p=mylist.first;
  while(p->next!=mylist.last)
  {
    p=p->next;
  }
  delete mylist.last;
  mylist.last=p;
  p->next=NULL;
  }
}

  //查找数据
  ListNode* Find(const MyList &mylist,ElemType key)
  {
    ListNode *p=mylist.first;
    while(p->next!=NULL && p->data!=key)
    {
      p=p->next;  
    }
    return p;
  }
//返回链表长度
int Length(MyList &mylist)
{
  return mylist.size;
}

//按值删除数据
void Delete(MyList &mylist,ElemType key)
{
  if(mylist.size==0)
  {
    cout<<"该链表为空，不能删除"<<endl;
    return;
  }
    ListNode *p=Find(mylist,key);
    if(p->next==NULL)
    {
      cout<<"要删除的数据不存在"<<endl;
      return;
    }
    else
    {
      if(p==mylist.last)
      {
        pop_back(mylist);
      }
      else
      {
      ListNode *q=p->next;//将数据粘贴到上一个节点的思想
      p->data=q->data;
      p->next=q->next;
      delete q;
      mylist.size--;
      }
    }
  }

  //排序 
  void sort(MyList &mylist)
  {
    if(mylist.size==0 || mylist.size==1)
    {
      return;
    }
    else
    {
      ListNode *s=mylist.first->next;
      ListNode *q=s->next;
      mylist.last=s;
      mylist.last->next=NULL;
      
      while(q!=NULL)
      {
        s=q;
        q=q->next;
        ListNode *s1=mylist.first;
        while(s1->next!=NULL && s1->next->data<s->data)
        {
          s1=s1->next;
        }
        if(s1==NULL)
        {
          mylist.last=s;
        }
        s->next=s1->next;
        s1->next=s;
      }
    }
  }
//将链表逆置
void resver(MyList &mylist)
{
  if(mylist.size==0 || mylist.size==1)
  {
    cout<<"该表无需逆置"<<endl;
  }
  else
  {
    ListNode *p=mylist.first->next;
    ListNode *q=p->next;

    mylist.last=p;
    mylist.last->next=NULL;

    while(q!=NULL)
    {
      p=q;
      q=q->next;
      p->next=mylist.first->next;
      mylist.first->next=p;
    }
  }
}

//清除链表
void clear(MyList &mylist)
{
  ListNode *p=mylist.first->next;
  while(p!=NULL)
  {
    mylist.first->next=p->next;
    delete p;
    p=mylist.first->next;
  }
  mylist.last=mylist.first;
}

//摧毁链表
void destory(MyList &mylist)
{
  clear(mylist);
  delete mylist.first;
  mylist.first=mylist.last=NULL;
}

  //创建链表
  void CreatList(List &head)
  {
    head=new(ListNode);
    head->next=NULL;
    for(int i=0;i<10;i++)
    {
        head->data;
        List s=new(ListNode);

        s->data=i;
        s->next=head->next;
        head->next=s;
    }
  }
  //输出链表(不能影响链表本身)
  void ShowList(MyList mylist)
  {
    while(mylist.first->next!=NULL)
    {
        mylist.first=mylist.first->next;
        cout<<mylist.first->data<<"  ";
    }
  }

};

int main()
{
    MyList list;
    ListNode L1;
    L1.InitList(list);
    // int select;
    // while(1)
    // {
    // cout<<"请选择功能"<<endl;
    // cin>>select;
    // switch (select)
    // {
    // case 1:
    // cout<<"请输入想要插入的数据"<<endl;
    // ElemType x;
    // while(x!=-1)
    // {
    // L1.push_front(list,x);
    // cin>>x;
    // }
    // L1.ShowList(list);

    // case 2:
    // cout<<"请输入想要插入的数据"<<endl;
    // ElemType x1;
    // while(x!=-1)
    // {
    // L1.insert_val(list,x1);
    // cin>>x;
    // }
    // L1.ShowList(list);
    // case 3:break;
    // }
    // return 0;
    // }
    L1.push_front(list,9);
    L1.push_front(list,4);
    L1.push_front(list,1);
    L1.push_front(list,3);
    L1.push_front(list,1);
    L1.ShowList(list);
    cout<<endl;
    L1.insert_val(list,23);
    L1.insert_val(list,11);
    L1.ShowList(list);
    ListNode *p=L1.Find(list,12);
    cout<<endl;
    cout<<p->data<<endl;
    //L1.pop_back(list);
    //L1.Delete(list,23);
    L1.sort(list);
    L1.ShowList(list);
    cout<<endl;
    L1.resver(list);
    L1.ShowList(list);
    L1.clear(list);
    cout<<endl<<"清空"<<endl;
    L1.ShowList(list);
    //cout<<"下一个数据为："<<(p->next)->data<<endl;
    

}