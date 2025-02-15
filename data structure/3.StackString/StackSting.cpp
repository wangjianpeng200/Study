#include<stdio.h>
#include<iostream>
#include<cassert>
#include<cstring>
using namespace std;

#define MAXSIZE 20
#define u_char unsigned char
using SString=u_char[MAXSIZE+1];

int Length(SString s);
void Copy(SString &s,SString t);
void Delete(SString &s,int pos,int len);
void Insert(SString &s,int pos,const char *t);

//SString 就等同于使用 u_char[MAXSIZE+1]，同时也方便了对代码的修改和调整。


//0号元素存放数据个数
void Init(SString &s)
{
    s[0]='\0';
}

void Assign(SString &s,char *c)
{
    int len=strlen(c);//b返回不包括null的字符串长度,而且只能求字符串的长度，现在这个string已经是一个数组
    if(len>MAXSIZE)
    {
        cout<<"错误"<<endl;
        return;
    }
    for(int i=0;i<len;i++)
    {
        s[i]=c[i];
    }
    s[len]='\0';
}

void Copy(SString &s,SString t)
{
    int len=Length(t);
    for(int i=0;i<len;i++)
    {
        s[i]=t[i];
    }
    s[len]='\0';
}

bool Empty(SString s)
{
    if(s[0]=='\0')
    {
        return 1;
    }
    return 0;
    
}

int Compare(SString s,SString t)//比较函数,从首位开始比较字符啊ACISS码值
{
    int result=0;
    while(*s!='\0'||*t!='\0')
    {
        result=*s-*t;
        if(result!=0)
        break;
        s++;
        t++;
    }
    if(result>0)
    {
        result =1;
    }
    else if(result<0)
    {
        result =-1;
    }
    return result;
}

int Length(SString s)
{
    int i=0;
    for(;s[i]!='\0';i++)
    {
    }
    return i;
}

void Concat(SString &t,SString s1,SString s2)
{
    //还要考虑t串能否容S1和S2字符串的个数，看是否需要截去数据
    int len1=Length(s1);
    int len2=Length(s2);
    int l=0;
    int b=0;
    if(len1>=MAXSIZE)
    {
        for(int i=0;i<MAXSIZE;i++)
        {
            t[i]=s1[i];
        }
        t[len1]='\0';
    }
    else 
    {
        if((len1+len2)>=MAXSIZE)
    {
        Copy(t,s1);
        int j=len1;
        for(;j<MAXSIZE;j++)
        {
            t[j]=s2[b++];
        } 
        t[MAXSIZE]='\0';
    }
    else //((len1+len2)<MAXSIZE)
    {
        for(int i=0;i<len1;i++)
        {
            t[i]=s1[i];
        }
        for(int h=len1;h<len1+len2;h++)
        {
            t[h]=s2[l];
            l++;
        } 
        t[MAXSIZE]='\0';
    }
}
}

void SubString(SString &s,SString t,int pos,int len)
{
    int len1=Length(t);
    if(Empty(t)||pos>=len1||pos+len>len1)
    {
        cout<<"错误"<<endl;
        return;
    }
    int point_s=0;
    for(int i=pos-1;i<pos+len-1;i++)
    {
        s[point_s++]=t[i];
    }                                                                                                                                                         
}

int Index(SString &s,SString t,int pos)
{
    int i=pos;
    int j=0;
    while(s[i]!='\0' && t[j]!='\0')
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(t[j]=='\0')
    {
        return i-j;
    }
    return -1;
}

void Replace(SString &s,const char *t,const char *v)
{
    int i=0;
    int j=0;
    int s_len=Length(s);
    int t_len=strlen(t);
    int v_len=strlen(v);
        while(s[i]!='\0'&& t[j]!='\0')
        {
           if(s[i]==t[j])
           {
              i++;
              j++;
           }
           else
           {
              i=i-j+1;
              j=0;
           }
        }
        if(t[j]=='\0')
        {
           int pos=i-j;
           Delete(s,pos,t_len);
           Insert(s,pos,v);
       }
    if(t[j!='\0'])
    {
        cout<<"未匹配到字符串"<<endl;
    }
} 

void Insert(SString &s,int pos,const char *t)
{
    int s_len=Length(s);
    int t_len=strlen(t);
    int s_len_point=pos;
    if(s_len+t_len<=MAXSIZE)
    {
        for(int i=s_len;i>=pos;i--)
        {
            s[i+t_len]=s[i];
        }
        for(int j=0;j<t_len;j++)
        {
            s[s_len_point++]=t[j];
        }
    }
    else//空间大小不能满足插入的个数，只能插入部分
    {
        int size=MAXSIZE-s_len;
         for(int i=s_len;i>=pos;i--)
        {
            s[i+size]=s[i];
        }
        for(int j=0;j<size;j++)
        {
            s[pos++]=t[j];
        }
    }
}

void Delete(SString &s,int pos,int len)
{
    int s_len=Length(s);
    if(Empty(s)||len>(s_len-pos))
    {
        cout<<"错误"<<endl;
        return;
    }
    int s_len_point=pos;
   for(int i=pos;i<s_len;++i)
   {
    s[i]=s[i+len];
   }
   s[s_len-len]='\0';
}

void Destory(SString &s)
{
    s[0]='\0';
}

void Show(SString s)
{
    int length=Length(s);
    cout<<"字符串>";
    for(int i=0;i<length;i++)
    {
        cout<<s[i]<<" ";
    }
}

void Test_Insert()
{
    SString s1;
    SString s2;
    Assign(s1,"abcdefghijklmn");
    cout<<"s1长度为:"<<Length(s1)<<"    "<<"插入字符串长度为："<<strlen("abcdefghijklmn")<<endl;
    Insert(s1,2,"sdsasdasdasdasdasdad");
    cout<<"s1的字符个数为:"<<Length(s1)<<"   ";
     Show(s1);
}

void test_delete()
{
    SString s1;
    SString s2;
    Assign(s1,"abcdefghijklmn");
    cout<<"s1长度为:"<<Length(s1)<<"    ";
    Delete(s1,2,1);
    cout<<"s1的字符个数为:"<<Length(s1)<<"   ";
    Show(s1);
}

void test_index()
{
    SString s1;
    SString s2;
    Assign(s1,"abcdefjhij");
    Assign(s2,"ij");
    int index=Index(s1,s2,0);
    cout<<"返回的下标："<<index<<endl;
    cout<<"匹配串为<";
    for (int i=index;i<index+2;i++)
    {
        cout<<s1[i]<<" ";
    }
}

void test_replace()
{
    SString s1;
    Assign(s1,"abdssabsddabsd");
    cout<<"s1长度为:"<<Length(s1)<<"    "<<endl;
    char *s="xx";
    Replace(s1,"ab",s);
    cout<<"替换字符串的长度为："<<strlen(s)<<"     s1的字符个数为:"<<Length(s1)<<"   "<<endl;
    Show(s1);
}


int main()
{
    SString str;
    Assign(str,"cbcdefwewrghi");
    SString copy;
    Assign(copy,"fghisadasdasdasd");
    // Copy(str,copy);
    // Show(str);
    int result=Compare(str,copy);
    //cout<<result;
    SString cat;
    Concat(cat,str,copy);
    SString sub;
    SubString(sub,cat,11,3);
    //Show(sub);
    cout<<"---------------------------------"<<endl;
    //Test_Insert();
    //test_delete();
    //test_index();
    test_replace();
    return 0;
}

    //     if(s_len+v_len-t_len<=MAXSIZE)
    //     {
    //         int move=v_len-t_len;
    //         if(move>0)
    //         {
    //            for(int i=s_len;i>=pos+t_len;i--)
    //            {
    //               s[i+move]=s[i];
    //            }
    //            for(int point=0;point<v_len;point++)
    //            {
    //               s[pos++]=v[point];
    //            }
    //         }
    //         else
    //         {
    //             if(move==0)
    //             {
    //                 for(int j=0;j<t_len;j++)
    //                 {
    //                     s[pos++]=t[j];
    //                 }
    //             }
    //             else
    //             {
    //                  for(int i=pos+t_len;i<=s_len;i++)
    //                 {
    //                    s[i+move]=s[i];
    //                 }
    //                  for(int point=0;point<v_len;point++)
    //                 {
    //                    s[pos++]=v[point];
    //                 }
    //             }
    //         }
    //     }
    //     else
    //     {
    //         int size=MAXSIZE-s_len;
    //         for(int i=s_len;i>=pos+t_len;i--)
    //         {
    //            s[i+size]=s[i];
    //         }
    //         for(int j=0;j<size;j++)
    //         {
    //            s[pos++]=v[j];
    //         }
    //     }