# 智能指针演示

这个目录包含了两个演示程序，用于展示C++中weak_ptr的重要性以及它如何解决shared_ptr的循环引用问题。

## 文件说明

1. `shared_ptr_circular_reference.cpp` - 演示shared_ptr导致的循环引用问题
2. `weak_ptr_demo.cpp` - 演示如何使用weak_ptr解决循环引用问题

## 循环引用问题

在C++中，当我们有两个对象需要相互引用时，如果都使用`shared_ptr`，就会导致循环引用问题：

```cpp
class Parent {
public:
    std::shared_ptr<Child> child;
};

class Child {
public:
    std::shared_ptr<Parent> parent;
};
```

在这种情况下，Parent对象持有Child的shared_ptr，Child对象也持有Parent的shared_ptr。当它们离开作用域时，由于引用计数永远不会降到0，两个对象都不会被销毁，从而导致内存泄漏。

### shared_ptr引用计数器变化过程

1. 创建shared_ptr对象时，引用计数为1
2. 当将shared_ptr赋值给另一个shared_ptr时，引用计数增加
3. 当shared_ptr离开作用域或被销毁时，引用计数减少
4. 当引用计数降到0时，对象被自动销毁

在循环引用的情况下：
1. 创建parent对象，引用计数为1
2. 创建child对象，引用计数为1
3. parent->child = child，child的引用计数增加到2
4. child->parent = parent，parent的引用计数增加到2
5. 当离开作用域时，parent和child的引用计数都只减少到1（因为它们相互引用），永远不会降到0

## weak_ptr解决方案

`weak_ptr`是为了解决这个问题而设计的。它是一个观察者，不增加引用计数：

```cpp
class Parent {
public:
    std::weak_ptr<Child> child;  // 使用weak_ptr
};

class Child {
public:
    std::weak_ptr<Parent> parent;  // 使用weak_ptr
};
```

通过使用`weak_ptr`，对象间的引用不会增加引用计数，从而避免了循环引用。当需要访问对象时，可以使用`lock()`方法尝试获取一个`shared_ptr`：

```cpp
if (auto p = parent->child.lock()) {
    // 安全地访问child对象
}
```

### weak_ptr引用计数器变化过程

1. 创建shared_ptr对象时，引用计数为1
2. 当将shared_ptr赋值给weak_ptr时，引用计数不变
3. 当weak_ptr离开作用域时，不影响引用计数
4. 当调用weak_ptr.lock()时，会临时创建一个shared_ptr，引用计数会增加，使用完后临时shared_ptr析构，引用计数减少
5. 当原始shared_ptr离开作用域时，引用计数降到0，对象被销毁

## 编译和运行

```bash
g++ -std=c++11 shared_ptr_circular_reference.cpp -o shared_ptr_demo
./shared_ptr_demo

g++ -std=c++11 weak_ptr_demo.cpp -o weak_ptr_demo
./weak_ptr_demo
```

通过对比两个程序的输出，可以清楚地看到shared_ptr导致的循环引用问题以及weak_ptr如何解决这个问题。