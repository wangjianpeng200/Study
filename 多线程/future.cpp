#include <iostream>
#include <future>
#include <thread>


int compute() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 42;
}

int main() {
    // 启动异步任务，返回 std::future<int>
    std::future<int> fut = std::async(std::launch::async, compute);  
    // 做其他事情...
    std::cout << "Waiting for result..." << std::endl;
    // 获取结果（阻塞直到任务完成）
    int result = fut.get();
    std::cout << "Result: " << result << std::endl;
    return 0;
}



#include <iostream>
#include <future>
#include <thread>

void setData(std::promise<int>&& prom) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    prom.set_value(100);  // 设置结果
}

int main() {
    // 创建 promise/future 对
    std::promise<int> prom;    //promise对象只能用move不能用copy
    std::future<int> fut = prom.get_future();

    // 启动线程，传递 promise
    std::thread t(setData, std::move(prom));

    // 等待结果
    std::cout << "Future get: " << fut.get() << std::endl;

    t.join();
    return 0;
}