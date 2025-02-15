#include<iostream>
#include<string>
#include<cassert>
#include<queue>
#include<unordered_map>
using namespace std;

using Elemtype=int;
#define p 13//一般是素数

class HashNode
{
    private:
    Elemtype data;
    HashNode* link;
    friend class Hash;
};

class Hash
{
    private:
    HashNode **hashtable;
    public:
    Hash()
    {
        hashtable=new HashNode*[p];
    }
    void InitHashTable();
    void Insert(Elemtype x);
    void Show();
    HashNode* Search();

};

void Hash::InitHashTable()
{
    for(int i=0;i<p;i++)
    {
        this->hashtable[i]=NULL;
    }
}

void Hash::Insert(Elemtype x)//插入元素
{
    int key=x%p;
    if(hashtable[key]==NULL)
    {
        hashtable[key]=new HashNode;
        hashtable[key]->data=x;
        hashtable[key]->link=NULL;
    }
    else{
        HashNode* ptr=hashtable[key];
        while(ptr->link!=NULL)
        {
            ptr=ptr->link;
        }
        ptr->link=new HashNode;
        ptr=ptr->link;
        ptr->data=x;
        ptr->link=NULL;
    } 
}

void Hash::Show()
{
    for(int i=0;i<p;i++)
    {
        if(this->hashtable[i]!=NULL)
        {
            cout<<"key="<<i<<"  :"<<this->hashtable[i]->data;
            HashNode* ptr=hashtable[i]->link;
            while(ptr!=NULL)
            {
                cout<<"  "<<ptr->data;
                ptr=ptr->link;
            }
            cout<<endl;
        }
        else{
             cout<<"key="<<i<<"  :"<<"NULL"<<endl;
        }
        
    }
}

HashNode* Hash::Search(Elemtype x)
{
    int key=x%13;
    HashNode* ptr=this->hashtable[key];
    if(this->hashtable[key]=NULL)
    {
        return NULL;
    }
    while(ptr!=NULL && ptr->data!=key)
    {
        ptr=ptr->link;
    }
    return ptr;
}

void test_hash()
{
    Hash h1;
    h1.InitHashTable();
    Elemtype arr[]={19,14,23,1,68,20,84,27,55,11,10,79};
    int size=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<size;i++)
    {
        h1.Insert(arr[i]);
    }
    h1.Show();
}

void tes_unordered_map()
{
    unordered_map<int,vector<string>> hash;
    unordered_map<int,vector<string>>::
}

 int longestConsecutive(vector<int>& nums)
 {
        unordered_set<int> hash;
        for(int &num: nums)
        {
            hash.insert(num);
        }
        int longterm=0;
        int shortterm=0;
        for(auto it=hash.begin();it==hash.end();it++)
        {
            int num=*it;
            if(!hash.count(num-1))
            {
                auto it=hash.find(num+1);
                while(it!=hash.end())
                {
                    shortterm+=1;
                    num+=1;
                    it=hash.find(num);
                }
                longterm=max(longterm,shortterm);
            }
        }
        return longterm;
    }

int main()
{
    test_hash();
}
