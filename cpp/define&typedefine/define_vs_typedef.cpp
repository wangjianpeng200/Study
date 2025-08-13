#include <iostream>

// 使用#define定义宏
#define PI 3.14159
#define INTEGER int

// 使用typedef定义类型别名
typedef double AREA;
typedef const char* STRING;

int main() {
    // 使用#define定义的宏
    double radius = 5.0;
    double circumference = 2 * PI * radius;
    std::cout << "圆的周长: " << circumference << std::endl;
    
    INTEGER num = 42;  // INTEGER实际上是int
    std::cout << "整数: " << num << std::endl;
    
    // 使用typedef定义的类型别名
    AREA area = PI * radius * radius;  // AREA实际上是double
    std::cout << "圆的面积: " << area << std::endl;
    
    STRING str = "Hello, World!";  // STRING实际上是char*
    std::cout << "字符串: " << str << std::endl;
    
    return 0;
}