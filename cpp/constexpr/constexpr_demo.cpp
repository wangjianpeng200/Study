#include <iostream>
#include <cmath>

// constexpr函数：在编译时计算
constexpr int square(int x) {
    return x * x;
}

// constexpr变量：编译时常量
constexpr double pi = 3.14159;

// constexpr构造函数和成员函数
class Circle {
private:
    double radius;
    
public:
    // constexpr构造函数
    constexpr Circle(double r) : radius(r) {}
    
    // constexpr成员函数
    constexpr double getArea() const {
        return pi * radius * radius;
    }
    
    constexpr double getRadius() const {
        return radius;
    }
};

// constexpr if (C++17特性)
template<typename T>
constexpr auto getValue(T t) {
    if constexpr (std::is_integral_v<T>) {
        return t * 2;  // 对整数类型，返回两倍
    } else {
        return t;      // 对非整数类型，返回原值
    }
}

int main() {
    // constexpr变量
    constexpr int x = 5;
    constexpr int x_squared = square(x);
    
    std::cout << "x = " << x << std::endl;
    std::cout << "x squared = " << x_squared << std::endl;
    
    // constexpr对象
    constexpr Circle c(3.0);
    constexpr double area = c.getArea();
    
    std::cout << "Circle radius = " << c.getRadius() << std::endl;
    std::cout << "Circle area = " << area << std::endl;
    
    // constexpr if 的使用
    constexpr int intVal = getValue(10);
    constexpr double doubleVal = getValue(3.14);
    
    std::cout << "getValue(10) = " << intVal << std::endl;
    std::cout << "getValue(3.14) = " << doubleVal << std::endl;
    
    return 0;
}