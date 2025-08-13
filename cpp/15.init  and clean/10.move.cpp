//移动构造函数
//std::move 是一个类型转换函数，它将左值转换为右值引用，从而允许调用移动构造函数，std：：move不进行任何的移动
//实际上移动构造函数需要在类中显式定义，编译器不会自动生成移动构造函数

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MyString {
private:
    char* data;
    size_t len;

public:
    // 默认构造函数
    MyString() : data(nullptr), len(0) {
        cout << "默认构造函数调用" << endl;
    }
    
    // 参数构造函数
    MyString(const char* str) {
        if (str) {
            len = strlen(str);
            data = new char[len + 1];
            strcpy(data, str);
        } else {
            len = 0;
            data = nullptr;
        }
        cout << "参数构造函数调用" << endl;
    }
    
    // 拷贝构造函数
    MyString(const MyString& other) {
        if (other.data) {
            len = other.len;
            data = new char[len + 1];
            strcpy(data, other.data);
        } else {
            len = 0;
            data = nullptr;
        }
        cout << "拷贝构造函数调用" << endl;
    }
    
    // 移动构造函数
    MyString(MyString&& other) noexcept {
        // 直接接管other的资源
        data = other.data;
        len = other.len;
        
        // 将other的资源置空
        other.data = nullptr;
        other.len = 0;
        
        cout << "移动构造函数调用" << endl;
    }
    
    // 拷贝赋值运算符
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            // 先释放自己的资源
            delete[] data;
            
            // 拷贝other的资源
            if (other.data) {
                len = other.len;
                data = new char[len + 1];
                strcpy(data, other.data);
            } else {
                len = 0;
                data = nullptr;
            }
        }
        cout << "拷贝赋值运算符调用" << endl;
        return *this;
    }
    
    // 移动赋值运算符
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            // 先释放自己的资源
            delete[] data;
            
            // 直接接管other的资源
            data = other.data;
            len = other.len;
            
            // 将other的资源置空
            other.data = nullptr;
            other.len = 0;
        }
        cout << "移动赋值运算符调用" << endl;
        return *this;
    }
    
    // 析构函数
    ~MyString() {
        delete[] data;
        cout << "析构函数调用" << endl;
    }
    
    // 打印函数
    void print() const {
        if (data)
            cout << "字符串内容: " << data << ", 长度: " << len << endl;
        else
            cout << "空字符串" << endl;
    }
};

int main() {
    cout << "=== 创建原始对象 ===" << endl;
    MyString str1("Hello, World!");
    str1.print();
    
    cout << "\n=== 拷贝构造 ===" << endl;
    MyString str2(str1);
    str2.print();
    
    cout << "\n=== 移动构造 ===" << endl;
    MyString str3(std::move(str1)); // 调用移动构造函数
    str3.print();
    cout << "原始对象状态:" << endl;
    str1.print(); // str1现在应该是空的
    
    cout << "\n=== 移动赋值 ===" << endl;
    MyString str4;
    str4 = std::move(str2); // 调用移动赋值运算符
    str4.print();
    cout << "原始对象状态:" << endl;
    str2.print(); // str2现在应该是空的
    
    return 0;
}