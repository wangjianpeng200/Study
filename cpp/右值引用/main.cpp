#include <iostream>
#include <utility>
#include <vector>

// 简单的演示类
class Demo {
private:
    int value;
    
public:
    Demo(int v = 0) : value(v) {
        std::cout << "构造函数: value = " << value << std::endl;
    }
    
    // 拷贝构造函数
    Demo(const Demo& other) : value(other.value) {
        std::cout << "拷贝构造函数: value = " << value << std::endl;
    }
    
    // 移动构造函数
    Demo(Demo&& other) noexcept : value(other.value) {
        other.value = 0;
        std::cout << "移动构造函数: value = " << value << std::endl;
    }
    
    // 拷贝赋值运算符
    Demo& operator=(const Demo& other) {
        if (this != &other) {
            value = other.value;
            std::cout << "拷贝赋值运算符: value = " << value << std::endl;
        }
        return *this;
    }
    
    // 移动赋值运算符
    Demo& operator=(Demo&& other) noexcept {
        if (this != &other) {
            value = other.value;
            other.value = 0;
            std::cout << "移动赋值运算符: value = " << value << std::endl;
        }
        return *this;
    }
    
    ~Demo() {
        std::cout << "析构函数: value = " << value << std::endl;
    }
    
    int getValue() const { return value; }
};

// 完美转发演示函数模板
template<typename T>
void wrapper(T&& arg) {
    std::cout << "\n=== 完美转发演示 ===" << std::endl;
    forwardDemo(std::forward<T>(arg));
}

void forwardDemo(Demo& d) {
    std::cout << "处理左值, value = " << d.getValue() << std::endl;
}

void forwardDemo(Demo&& d) {
    std::cout << "处理右值, value = " << d.getValue() << std::endl;
}

// 创建临时对象的函数
Demo createDemo() {
    return Demo(42);
}

int main() {
    std::cout << "=== 右值引用、移动语义和完美转发演示 ===" << std::endl;
    
    // 1. 右值引用演示
    std::cout << "\n1. 右值引用演示:" << std::endl;
    int a = 10;
    int& lref = a;           // 左值引用
    int&& rref = 20;         // 右值引用
    
    std::cout << "左值引用 lref = " << lref << std::endl;
    std::cout << "右值引用 rref = " << rref << std::endl;
    
    // 2. 移动语义演示
    std::cout << "\n2. 移动语义演示:" << std::endl;
    Demo d1(100);
    
    // 拷贝构造
    std::cout << "\n--- 拷贝构造 ---" << std::endl;
    Demo d2 = d1;  // 调用拷贝构造函数
    
    // 移动构造
    std::cout << "\n--- 移动构造 ---" << std::endl;
    Demo d3 = std::move(d1);  // 调用移动构造函数
    
    // 拷贝赋值
    std::cout << "\n--- 拷贝赋值 ---" << std::endl;
    Demo d4;
    d4 = d2;  // 调用拷贝赋值运算符
    
    // 移动赋值
    std::cout << "\n--- 移动赋值 ---" << std::endl;
    Demo d5;
    d5 = std::move(d2);  // 调用移动赋值运算符
    
    // 3. 完美转发演示
    std::cout << "\n3. 完美转发演示:" << std::endl;
    Demo d6(200);
    
    // 传递左值
    wrapper(d6);  // 调用处理左值的函数
    
    // 传递右值
    wrapper(createDemo());  // 调用处理右值的函数
    
    std::cout << "\n程序结束" << std::endl;
    return 0;
}