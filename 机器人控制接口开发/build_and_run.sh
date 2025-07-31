#!/bin/bash

# 创建构建目录
mkdir -p build
cd build

# 运行CMake配置
cmake ..

# 编译项目
make

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo ""
    echo "Compilation successful!"
    echo ""
    echo "Running remote_control..."
    echo ""
    ./remote_control
else
    echo ""
    echo "Compilation failed!"
    echo ""
fi