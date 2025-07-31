cmake_minimum_required(VERSION 3.10)
project(remote_control)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找必要的包
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

# 查找ZeroMQ
pkg_check_modules(PC_ZeroMQ REQUIRED libzmq)

# 包含头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PC_ZeroMQ_INCLUDE_DIRS})

# 链接ZeroMQ库
link_directories(${PC_ZeroMQ_LIBRARY_DIRS})

# 查找nlohmann_json
find_package(nlohmann_json REQUIRED)

# 创建配置加载器库
add_library(config_loader
    config_loader.cpp
)

target_link_libraries(config_loader
    nlohmann_json::nlohmann_json
)

# 创建远程控制程序
add_executable(remote_control
    remote.cpp
)

target_link_libraries(remote_control
    config_loader
    nlohmann_json::nlohmann_json
    ${OpenCV_LIBS}
    ${PC_ZeroMQ_LIBRARIES}
    pthread
)

# 复制配置文件到构建目录
configure_file(config.json config.json COPYONLY)