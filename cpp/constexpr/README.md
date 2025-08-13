# constexpr 详解

`constexpr` 是C++11引入的关键字，用于声明可以在编译时计算的常量表达式。它扩展了`const`的功能，不仅可以在编译时检查常量表达式的合法性，还可以在编译时进行计算。

## 编译和运行

### 方法1：命令行编译和运行

```bash
g++ -std=c++17 constexpr_demo.cpp -o constexpr_demo
./constexpr_demo
```

注意：示例代码使用了C++17的特性，因此需要使用`-std=c++17`编译选项。

### 方法2：使用批处理文件运行（Windows）

双击运行 `run_demo.bat` 文件，它会自动编译并运行程序，并在程序结束后暂停，方便查看输出结果。

## constexpr 的使用

### 1. constexpr 变量

`constexpr`变量必须在编译时初始化，并且其值在程序运行期间不能改变。

```cpp
constexpr double pi = 3.14159;
constexpr int x = 5;
```

### 2. constexpr 函数

`constexpr`函数可以在编译时计算结果，前提是传入的参数也是常量表达式。

```cpp
constexpr int square(int x) {
    return x * x;
}

// 在编译时计算
constexpr int result = square(5); 
```

### 3. constexpr 构造函数和成员函数

类的构造函数和成员函数也可以标记为`constexpr`，使得对象可以在编译时创建和使用。

```cpp
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
};

// 在编译时创建对象和计算结果
constexpr Circle c(3.0);
constexpr double area = c.getArea();
```

### 4. constexpr if (C++17)

C++17引入了`constexpr if`，允许在编译时进行条件判断，不满足条件的分支会被完全移除。

```cpp
template<typename T>
constexpr auto getValue(T t) {
    if constexpr (std::is_integral_v<T>) {
        return t * 2;  // 对整数类型，返回两倍
    } else {
        return t;      // 对非整数类型，返回原值
    }
}
```

## constexpr 的优势

1. **性能提升**：在编译时计算，减少运行时开销
2. **类型安全**：编译时检查，避免运行时错误
3. **模板编程**：在模板元编程中提供更强大的功能
4. **内存优化**：constexpr对象可能不会占用运行时内存