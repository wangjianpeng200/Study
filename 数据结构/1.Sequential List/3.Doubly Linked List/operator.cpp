#include<iostream>
#include"DList.h"
using namespace std;



int main()
{
List list;
Node node;
node.InitDList(list);
 while(1)
    {
        int x=0;
        cout<<"请输入编号，选择功能"<<endl;
        cin>>x;
        switch (x)
        {
        case 1: //尾插
            cout<<"请输入需要尾插的值"<<endl;
            int s;cin>>s;
            node.Push_back(list,s);break;
        case 2: //头插
            cout<<"请输入需要头插的值"<<endl;
            int s;cin>>s;
            node.Push_front(list,s);break;
        case 3:node.Pop_bcak (list);break;//尾删
        case 4:node.Pop_front(list);break;//头删
        case 5://中插
           cout<<"请输入需要中间插入的值"<<endl;
           int s;cin>>s;
           node.Insert(list,s);;break;
        case 6://按照值删除
           cout<<"请输入需要删除的值"<<endl;
           int s;cin>>s;
           node.Delete_val(list,s);;break;
        case 7:node.Sort(list);break;//排序
        case 8:node.Resver(list);break;//倒置
        case 9:node.Clear(list);break;//清空
        case 10:node.Length(list);break;//返回长度
        case 11:node.ShowList(list);break;//显示
        default:
            break;
        }
    }
}
