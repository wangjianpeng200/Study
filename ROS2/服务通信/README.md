# ROS2服务通信Demo

这个Demo展示了ROS2中的服务通信机制，包括服务端和客户端两个节点。服务端提供一个加法服务，客户端发送两个整数，服务端返回它们的和。

## 文件结构
- `server.cpp`: 服务端实现，提供`add_two_ints`服务
- `client.cpp`: 客户端实现，调用`add_two_ints`服务

## 依赖
- ROS2 (Foxy或更新版本)
- `example_interfaces`包 (包含`AddTwoInts`服务定义)

## 编译
1. 创建一个ROS2工作空间(如果还没有):
   ```bash
   mkdir -p ~/ros2_ws/src
   cd ~/ros2_ws/src
   ```

2. 将这个Demo复制到工作空间:
   ```bash
   cp -r /path/to/ROS2/服务通信 ~/ros2_ws/src/
   ```

3. 创建`CMakeLists.txt`和`package.xml`文件:
   
   `CMakeLists.txt`:
   ```cmake
   cmake_minimum_required(VERSION 3.5)
   project(service_demo)

   find_package(ament_cmake REQUIRED)
   find_package(rclcpp REQUIRED)
   find_package(example_interfaces REQUIRED)

   add_executable(server src/server.cpp)
   ament_target_dependencies(server rclcpp example_interfaces)

   add_executable(client src/client.cpp)
   ament_target_dependencies(client rclcpp example_interfaces)

   install(TARGETS
     server
     client
     DESTINATION lib/${PROJECT_NAME})

   ament_package()
   ```

   `package.xml`:
   ```xml
   <?xml version="1.0"?>
   <?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
   <package format="3">
     <name>service_demo</name>
     <version>0.0.0</version>
     <description>ROS2 Service Communication Demo</description>
     <maintainer email="you@example.com">Your Name</maintainer>
     <license>Apache License 2.0</license>

     <buildtool_depend>ament_cmake</buildtool_depend>

     <depend>rclcpp</depend>
     <depend>example_interfaces</depend>

     <test_depend>ament_lint_auto</test_depend>
     <test_depend>ament_lint_common</test_depend>

     <export>
       <build_type>ament_cmake</build_type>
     </export>
   </package>
   ```

4. 编译工作空间:
   ```bash
   cd ~/ros2_ws
   colcon build --packages-select service_demo
   ```

## 运行
1. 打开一个终端，运行服务端:
   ```bash
   source ~/ros2_ws/install/setup.bash
   ros2 run service_demo server
   ```

2. 打开另一个终端，运行客户端:
   ```bash
   source ~/ros2_ws/install/setup.bash
   ros2 run service_demo client [a] [b]
   ```
   其中`[a]`和`[b]`是可选的整数参数，默认值为5和3。

## 工作原理
1. 服务端创建一个名为`add_two_ints`的服务，并注册回调函数`handle_add_two_ints`
2. 客户端创建一个服务客户端，连接到`add_two_ints`服务
3. 客户端发送两个整数a和b作为请求
4. 服务端接收到请求后，计算a+b，并返回结果
5. 客户端接收到响应后，打印结果

这个Demo展示了ROS2中基于请求-响应模型的服务通信机制，适用于需要即时反馈的场景。