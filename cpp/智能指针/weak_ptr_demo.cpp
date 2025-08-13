#include <iostream>
#include <memory>

class Child;

void test_unique_ptr() 
{
    std::unique_ptr<Parent> parent = std::make_unique<Parent>();
}


class Parent {
public:
    Parent() {
        std::cout << "Parent constructed" << std::endl;
    }
    
    ~Parent() {
        std::cout << "Parent destructed" << std::endl;
    }
    
    // 使用shared_ptr会导致循环引用
    // std::shared_ptr<Child> child;
    
    // 使用weak_ptr避免循环引用
    std::weak_ptr<Child> child;
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
    // std::shared_ptr<Parent> parent;
    
    // 使用weak_ptr避免循环引用
    std::weak_ptr<Parent> parent;
};

int main() {
    std::cout << "=== 演示weak_ptr解决循环引用问题 ===" << std::endl;
    
    {
        std::cout << "\n--- 创建shared_ptr对象 ---" << std::endl;
        // 创建shared_ptr对象
        std::shared_ptr<Parent> parent = std::make_shared<Parent>();  // parent引用计数: 1
        std::shared_ptr<Child> child = std::make_shared<Child>();      // child引用计数: 1
        
        std::cout << "创建后 - Parent's reference count: " << parent.use_count() << std::endl;  // 输出: 1
        std::cout << "创建后 - Child's reference count: " << child.use_count() << std::endl;    // 输出: 1
        
        std::cout << "\n--- 使用weak_ptr建立引用关系 ---" << std::endl;
        // 使用weak_ptr建立引用关系 (不会增加引用计数)
        parent->child = child;  // child引用计数仍为: 1 (weak_ptr不增加引用计数)
        child->parent = parent; // parent引用计数仍为: 1 (weak_ptr不增加引用计数)
        
        std::cout << "建立weak_ptr引用后 - Parent's reference count: " << parent.use_count() << std::endl;  // 输出: 1
        std::cout << "建立weak_ptr引用后 - Child's reference count: " << child.use_count() << std::endl;    // 输出: 1
        
        std::cout << "\n--- 演示如何安全地访问weak_ptr指向的对象 ---" << std::endl;
        // 演示如何安全地访问weak_ptr指向的对象
        if (auto p = parent->child.lock()) {  // lock()会创建一个临时的shared_ptr，增加引用计数
            std::cout << "成功访问child对象，临时引用计数增加" << std::endl;
            std::cout << "访问期间 - Child's reference count: " << child.use_count() << std::endl;  // 输出: 2
            // 使用完后临时shared_ptr析构，引用计数减回1
        } else {
            std::cout << "Child is no longer valid" << std::endl;
        }
        
        std::cout << "访问结束后 - Child's reference count: " << child.use_count() << std::endl;  // 输出: 1
        
        if (auto c = child->parent.lock()) {  // lock()会创建一个临时的shared_ptr，增加引用计数
            std::cout << "成功访问parent对象，临时引用计数增加" << std::endl;
            std::cout << "访问期间 - Parent's reference count: " << parent.use_count() << std::endl;  // 输出: 2
            // 使用完后临时shared_ptr析构，引用计数减回1
        } else {
            std::cout << "Parent is no longer valid" << std::endl;
        }
        
        std::cout << "访问结束后 - Parent's reference count: " << parent.use_count() << std::endl;  // 输出: 1
        
        std::cout << "\n--- 离开作用域前 ---" << std::endl;
        std::cout << "离开作用域前 - Parent's reference count: " << parent.use_count() << std::endl;  // 输出: 1
        std::cout << "离开作用域前 - Child's reference count: " << child.use_count() << std::endl;    // 输出: 1
    }
    
    std::cout << "\n--- 离开作用域后 ---" << std::endl;
    std::cout << "离开作用域，由于weak_ptr不增加引用计数，对象会被正确析构" << std::endl;
    
    return 0;
}