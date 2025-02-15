#include<iostream>
using namespace std;

//判断点和圆的关系
//如果点到圆心的距离等于r：则点在圆上
//点到圆的距离大于r:在圆外
//点在圆的距离小于r：在圆内
//如何求点到圆的距离？

class point
{
private:
    int m_x;
    int m_y;
public:
void setx(int x)
{
    m_x=x;
}

int getx()
{
    return m_x;
}

void sety(int y)
{
    m_y=y;
}

int gety()
{
    return m_y;
}

};

class circle
{
private:
    int m_r;
    point m_center;
public:
void setr(int r)
{
    m_r=r;
}

int getr()
{
    return m_r;
}

void setcenter(point c)
{
    m_center=c;
}

point getcenter()
{
    return m_center;
}

};

void isincircle(circle a,point p)
{
    //计算两点间距离的平方
    int distance=
    (a.getcenter().getx()-p.getx())*(a.getcenter().getx()-p.getx())+
    (a.getcenter().gety()-p.gety())*(a.getcenter().gety()-p.gety());
    //计算半径的平方
    int r2=a.getr()*a.getr();
    //判断关系
    if(distance==r2)
    {
        cout<<"该点在圆上"<<endl;
    }
    else
    {
        if(distance>r2)
        {
            cout<<"该点在圆外"<<endl;
            return;
        }
        cout<<"该点在圆内"<<endl;
    }
}

int main()
{
    circle c;
    c.setr(5);
    point cen;
    cen.setx(0);
    cen.sety(0);
    c.setcenter(cen);
    point p;
    p.setx(0);
    p.sety(5);
    isincircle(c,p);
    system("pause");
    return 0;
}