#include <iostream>
#include <memory>

class Child;

class Parent {
public:
    Parent() {
        std::cout << "Parent constructed" << std::endl;
    }
    
    ~Parent() {
        std::cout << "Parent destructed" << std::endl;
    }
    
    // 使用shared_ptr会导致循环引用
    std::shared_ptr<Child> child;
};

class Child {
public:
    Child() {
        std::cout << "Child constructed" << std::endl;
    }
    
    ~Child() {
        std::cout << "Child destructed" << std::endl;
    }
    
    // 使用shared_ptr会导致循环引用
    std::shared_ptr<Parent> parent;
};

int main() {
    std::cout << "=== 演示shared_ptr导致的循环引用问题 ===" << std::endl;
    
    {
        std::cout << "\n--- 创建shared_ptr对象 ---" << std::endl;
        // 创建shared_ptr对象
        std::shared_ptr<Parent> Parent = std::make_shared<Parent>();  // parent引用计数: 1
        std::shared_ptr<Child> Child = std::make_shared<Child>();      // child引用计数: 1
        
        std::cout << "创建后 - Parent's reference count: " << Parent.use_count() << std::endl;  // 输出: 1
        std::cout << "创建后 - Child's reference count: " << Child.use_count() << std::endl;    // 输出: 1
        
        std::cout << "\n--- 建立双向引用，导致循环引用 ---" << std::endl;
        // 建立双向引用，导致循环引用
        Parent->child = Child;  // child引用计数增加到: 2 (child对象本身1 + parent->child引用1)
        Child->parent = Parent; // parent引用计数增加到: 2 (parent对象本身1 + child->parent引用1)
        
        std::cout << "建立循环引用后 - Parent's reference count: " << Parent.use_count() << std::endl;  // 输出: 2
        std::cout << "建立循环引用后 - Child's reference count: " << Child.use_count() << std::endl;    // 输出: 2
        
        std::cout << "\n--- 离开作用域前 ---" << std::endl;
        std::cout << "离开作用域前 - Parent's reference count: " << Parent.use_count() << std::endl;  // 输出: 2
        std::cout << "离开作用域前 - Child's reference count: " << Child.use_count() << std::endl;    // 输出: 2
    }
    
    std::cout << "\n--- 离开作用域后 --- Parent,Child先被销毁，但是计数器依然不为0" << std::endl;
    std::cout << "离开作用域，但由于循环引用，对象不会被析构" << std::endl;
    std::cout << "parent和child的引用计数都为1(彼此相互引用)，永远不会降到0" << std::endl;
    std::cout << "程序结束时会发现Parent和Child的析构函数没有被调用" << std::endl;
    
    return 0;
}