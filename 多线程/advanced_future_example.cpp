#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <chrono>
#include <stdexcept>

// 模拟一个复杂的计算任务，可能成功也可能失败
std::vector<int> complexCalculation(int taskId) {
    // 模拟不同的任务需要不同的时间
    std::this_thread::sleep_for(std::chrono::milliseconds(500 * taskId));
    
    // 模拟某些任务可能失败
    if (taskId == 3) {
        throw std::runtime_error("计算任务 " + std::to_string(taskId) + " 失败！");
    }
    
    // 返回计算结果
    std::vector<int> result;
    for (int i = 0; i < taskId; ++i) {
        result.push_back(taskId * (i + 1));
    }
    return result;
}

// 使用promise传递复杂数据和异常
void performTask(int taskId, std::promise<std::vector<int>>&& prom) {
    try {
        auto result = complexCalculation(taskId);
        prom.set_value(std::move(result));  // 成功时设置结果
    } catch (...) {
        prom.set_exception(std::current_exception());  // 异常时传递异常
    }
}

int main() {
    const int numTasks = 5;
    std::vector<std::future<std::vector<int>>> futures;
    std::vector<std::thread> threads;
    
    // 启动多个异步任务
    std::cout << "启动 " << numTasks << " 个计算任务..." << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i <= numTasks; ++i) {
        std::promise<std::vector<int>> prom;
        futures.push_back(prom.get_future());
        threads.emplace_back(performTask, i, std::move(prom));
    }
    
    // 收集所有结果
    std::cout << "等待所有任务完成..." << std::endl;
    for (int i = 0; i < numTasks; ++i) {
        try {
            auto result = futures[i].get();  // 获取结果（可能抛出异常）
            std::cout << "任务 " << (i+1) << " 完成，结果: [";
            for (size_t j = 0; j < result.size(); ++j) {
                std::cout << result[j];
                if (j < result.size() - 1) std::cout << ", ";
            }
            std::cout << "]" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "任务 " << (i+1) << " 失败: " << e.what() << std::endl;
        }
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "所有任务完成，总耗时: " << duration.count() << " 毫秒" << std::endl;
    
    return 0;
}