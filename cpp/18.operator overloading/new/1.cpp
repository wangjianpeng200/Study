#include <iostream>
using namespace std;

class Point {
public:
    // 构造函数
    Point(int x = 0, int y = 0) : x(x), y(y) {
        // std::cout<<"调用构造函数"<<std::endl;
    }
    
    // 重载+运算符
    Point operator+(const Point& p) {
        cout<<x<<"aaaaaaa"<<y<<endl;
        cout<<"操作符重载"<<endl;
        return Point(x + p.x, y + p.y);
    }
    
    // 成员变量
    int x, y;
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2;   //调用p1的运算符重载
    std::cout << "p3.x = " << p3.x << ", p3.y = " << p3.y << std::endl;
    return 0;
}