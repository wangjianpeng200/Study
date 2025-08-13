#include <iostream>
#include <utility>

// 用于演示完美转发的类
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
    
    ~Demo() {
        std::cout << "析构函数: value = " << value << std::endl;
    }
    
    int getValue() const { return value; }
};

// 重载函数，用于接收左值引用
void process(const Demo& d) {
    std::cout << "处理左值引用: value = " << d.getValue() << std::endl;
}

// 重载函数，用于接收右值引用
void process(Demo&& d) {
    std::cout << "处理右值引用: value = " << d.getValue() << std::endl;
}

// 不使用完美转发的函数模板
// 无论传递左值还是右值，都会调用process(const Demo&)
template<typename T>
void wrapperWithoutPerfectForwarding(T&& arg) {
    std::cout << "\n--- 不使用完美转发 ---" << std::endl;
    process(arg);  // arg在这里是左值，总是调用process(const Demo&)
}

// 使用完美转发的函数模板
// 保持参数的值类别（左值或右值）不变
template<typename T>
void wrapperWithPerfectForwarding(T&& arg) {
    std::cout << "\n--- 使用完美转发 ---" << std::endl;
    process(std::forward<T>(arg));  // std::forward保持arg的值类别
}

// 创建临时对象的函数
Demo createDemo() {
    return Demo(42);
}

int main() {
    std::cout << "=== 完美转发演示 ===" << std::endl;
    
    Demo d(100);
    
    // 传递左值
    std::cout << "\n1. 传递左值:" << std::endl;
    wrapperWithoutPerfectForwarding(d);   // 不使用完美转发
    wrapperWithPerfectForwarding(d);     // 使用完美转发
    
    // 传递右值
    std::cout << "\n2. 传递右值:" << std::endl;
    wrapperWithoutPerfectForwarding(createDemo());   // 不使用完美转发
    wrapperWithPerfectForwarding(createDemo());     // 使用完美转发
    
    std::cout << "\n程序结束" << std::endl;
    return 0;
}