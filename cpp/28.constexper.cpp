#include<iostream>
#include<algorithm>
using namespace std;

//允许变量或函数在编译时计算结果，而非运行时
constexpr int func(int n) {
    return n * 2;
}


//构造函数和成员函数必须用 constexpr 标记
class Point {
    public:
        constexpr Point(double x, double y) : x(x), y(y) {}
        constexpr double length() const {
            return sqrt(x*x + y*y);
        }
    private:
        double x, y;
    };


    constexpr Point p(3.0, 4.0);
    constexpr double len = p.length();  // 编译时计算 5.0

int test() {
    int a=std::rand();   //在运行时计算
    constexpr int b = func(5);

    int arr[a];   //非法
    int arr[b];
    
}


int main() {
    constexpr int a = func(5);
    cout << a;
    return 0;
}