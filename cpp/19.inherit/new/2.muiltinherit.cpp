#include <iostream>
#include <string>

// 基类1：学生
class Student {
protected:
    std::string name;
    int studentID;
public:
    Student(std::string n, int id) : name(n), studentID(id) {}
    void study() {
        std::cout << name << "正在学习" << std::endl;
    }
};

// 基类2：工人
class Worker {
protected:
    std::string company;
public:
    Worker(std::string c) : company(c) {}
    void work() {
        std::cout << "在" << company << "工作" << std::endl;
    }
};

// 派生类：学生工人（多重继承）
class StudentWorker : public Student, public Worker {
private:
    int salary;
public:
    // 构造函数需要初始化所有基类
    StudentWorker(std::string n, int id, std::string c, int s)
        : Student(n, id), Worker(c), salary(s) {}

    // 组合基类功能的新方法
    void display() {
        std::cout << "姓名: " << name << ", 学号: " << studentID
                  << ", 公司: " << company << ", 工资: " << salary << std::endl;
    }
};

int main() {
    StudentWorker sw("张三", 1001, "ABC公司", 5000);
    sw.study();  // 继承自Student
    sw.work();   // 继承自Worker
    sw.display();// 派生类自己的方法
    return 0;
}