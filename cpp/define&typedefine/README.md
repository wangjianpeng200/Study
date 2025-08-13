# #define 和 typedef 的区别

在C++中，`#define`和`typedef`都可以用来创建别名，但它们有重要的区别。本项目演示了这两种方式的使用方法和区别。

## 编译和运行

### 方法1：命令行编译和运行

```bash
g++ -std=c++11 define_vs_typedef.cpp -o define_vs_typedef
./define_vs_typedef
```

### 方法2：使用批处理文件运行（Windows）

双击运行 `run_demo.bat` 文件，它会自动编译并运行程序，并在程序结束后暂停，方便查看输出结果。

## #define 和 typedef 的区别

### 1. #define（宏定义）

`#define`是C++中的预处理指令，在编译预处理阶段进行简单的文本替换。

```cpp
#define PI 3.14159
#define INTEGER int
```

特点：
- 简单的文本替换，没有类型检查
- 在预处理阶段处理
- 可以定义常量、宏函数等
- 不占用内存空间

### 2. typedef（类型别名）

`typedef`用于为已有的数据类型创建一个新的名字（别名）。

```cpp
typedef double AREA;
typedef const char* STRING;
```

特点：
- 为类型创建别名，有类型检查
- 在编译阶段处理
- 只能用于数据类型
- 会占用内存空间（对于复杂类型）

### 3. 主要区别

| 特性 | #define | typedef |
|------|---------|---------|
| 处理阶段 | 预处理阶段 | 编译阶段 |
| 类型检查 | 无 | 有 |
| 功能 | 文本替换，可定义常量和宏函数 | 仅为类型创建别名 |
| 作用域 | 从定义点到文件末尾 | 遵循正常的作用域规则 |
| 调试 | 较困难，因为是文本替换 | 较容易，因为是真正的类型 |

### 4. 现代C++的替代方案

在现代C++中，推荐使用`using`关键字来替代`typedef`：

```cpp
using AREA = double;
using STRING = const char*;
```

`using`相比`typedef`的优势：
- 语法更清晰易读
- 支持模板别名（template alias）
- 更符合现代C++的编程风格