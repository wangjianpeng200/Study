//#include"pcl/features/normal_3d.h"
#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"//ROS中的点云数据类型
#include "pcl/point_cloud.h"//点云数据结构的定义
#include "pcl/point_types.h"//点云数据结构的定义
#include "pcl/search/kdtree.h"// 引入Kd树
#include "pcl/filters/extract_indices.h"//从点云中提取指定索引的点的工具
#include "pcl/ModelCoefficients.h"
#include "pcl_conversions/pcl_conversions.h"
#include "pcl/segmentation/sac_segmentation.h"//平面拟合和分割点云的工具
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"//用于在可视化工具中发布和显示标记的ROS消息类型

ros::Publisher ground_pub;
ros::Publisher marker_pub;
pcl::KdTree<pcl::PointXYZ>::Ptr kd_tree(new pcl::KdTreeFLANN<pcl::PointXYZ>); 
// pcl::KdTreeFLANN<pcl::PointXYZ>是模板化的kd树类，用处理pcl::pointxyz类型的数据，创建了一个指向该内存的指针

// 定义你的目标提取函数（提取地面）
void extractGround(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud_in,pcl::PointCloud<pcl::PointXYZ>::Ptr& ground_out) 
// pcl::PointCloud<pcl::PointXYZ>表示一个三位点的点云数据结构，这里表示将点云数据提取到cloud——in里，从ground——out输出/
{
    //将clound_in中的输入kd树中进行搜索
    kd_tree->setInputCloud(cloud_in);

    // 实现提取地面的算法
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);//创建了一个指针指向modelcoefficients类型
    //用于存储分割模型的系数，例如平面方程的系数（A、B、C、D），用于表示检测到的平面。这个指针会在后续的点云分割中用于存储平面模型的系数
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);//用于存储被分割模型包含的点的索引。在点云分割后，这个指针会用于存储属于分割模型的点的索引
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    //pcl::SACSegmentation 是 PCL 中用于平面分割的工具，可以检测点云中的平面模型，并返回该平面模型的系数和包含在其中的点的索引。
    seg.setOptimizeCoefficients(true);//分割算法是否尝试优化模型系数
    seg.setModelType(pcl::SACMODEL_PLANE);//分割算法要拟合的模型类型为平面。也就是说，它会尝试找到最适合点云数据的平面
    seg.setMethodType(pcl::SAC_RANSAC);//RANSAC是一种估计参数的统计方法，它可以从数据中找到最佳的模型参数；
    seg.setDistanceThreshold(0.05); //在这里，距离阈值为0.05，表示距离平面模型0.05个单位以内的点将被认为是内点。
    seg.setInputCloud(cloud_in);//设置了算法输入点云数据
    seg.segment(*inliers, *coefficients);//执行分割操作，根据给点的距离阈值和输入点云数据，拟合出平面模型，将内点的索引存入inliers
    //参数存入coefficients

    // 创建提取器并提取地面
    pcl::ExtractIndices<pcl::PointXYZ> extract;//
    extract.setInputCloud(cloud_in);//原始点云
    extract.setIndices(inliers);//从已经拟合过的数据中提取索引
    extract.setNegative(false); // 提取地面，false表示提取指定索引的点集
    extract.filter(*ground_out);//将提取到的数据存入ground_out
}
// 订阅回调函数
void cloudCallback(const sensor_msgs::PointCloud2::ConstPtr& msg) 
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>);//创建云点数据类型
    pcl::fromROSMsg(*msg, *cloud_in);//解析ROS消息中的点云数据，并存入cloud_in
    pcl::PointCloud<pcl::PointXYZ>::Ptr ground_out(new pcl::PointCloud<pcl::PointXYZ>);
    extractGround(cloud_in, ground_out);//调用extractground函数输入点云，输出拟合过的ground_out
    sensor_msgs::PointCloud2 ground_out_msg;//创建ros标准消息类型
    //它以一种通用的方式表示点云，可以包含 XYZ 坐标、RGB 颜色、法线等信息，通过字段来存储这些数据
    //pcl::PointCloud<pcl::PointXYZ> 是 PCL（Point Cloud Library）库中的数据结构，用于表示点云。
    //它通常只包含 XYZ 坐标信息，不包含其他元信息
    /*
    用途:
    sensor_msgs::PointCloud2 通常用于 ROS 中，可以轻松地在不同的 ROS 节点之间传递点云数据，
    适用于 ROS 生态系统中的各种应用。
    pcl::PointCloud<pcl::PointXYZ> 主要用于点云处理，例如，使用 PCL 库中的点云滤波、分割、
    配准等算法。它更适合在点云处理流程中进行内部计算和临时数据存储。

    消息发布:
    sensor_msgs::PointCloud2 可以直接由 ROS 节点发布，使用 ROS 的发布者（Publisher）将点云数据发送到 ROS 主题（Topic）中，以便其他节点订阅。
    pcl::PointCloud<pcl::PointXYZ> 通常需要转换为 sensor_msgs::PointCloud2 类型才能发布到 ROS 主题中，然后其他节点可以从主题订阅并进行处理。

    */
    pcl::toROSMsg(*ground_out, ground_out_msg);//将plc数据类型转化为ros标准消息类型
    ground_out_msg.header = msg->header;//输出的消息与原数据有相同的时间戳

    // 发布提取的地面点云作为 PointCloud2
    ground_pub.publish(ground_out_msg);

    // 发布 RViz 中可视化的标记
    visualization_msgs::MarkerArray marker_array;//创建一种消息类型，做可视化标记
    for (size_t i = 0; i < ground_out->size(); i++)
    {
        visualization_msgs::Marker marker; //maker用于设置和定义在rviz总显示标记的颜色
        marker.header = msg->header;
        //将 marker 对象的 header 属性设置为与输入消息 msg 的头部相同。这意味着标记将与输入消息共享相同的时间戳和坐标系
        marker.ns = "ground_markers";//标记命名空间
        marker.id = i;//创建唯一标记符
        marker.type = visualization_msgs::Marker::SPHERE;
        //这一行代码定义了标记的类型。在这里，标记的类型被设置为 SPHERE，这意味着它将显示为一个球体
        marker.action = visualization_msgs::Marker::ADD;
        //如果之前已经存在相同 ID 的标记，将其替换。这通常用于创建新标记。
        marker.pose.position.x = ground_out->points[i].x;
        marker.pose.position.y = ground_out->points[i].y;
        marker.pose.position.z = ground_out->points[i].z;
        //以上的X,Y,Z传入的是提取出来的msgs消息
        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;
        //X,Y,Z的缩放度
        marker.color.a = 1.0;//透明
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        //设置颜色
        marker_array.markers.push_back(marker);
    }

    marker_pub.publish(marker_array);//创建发布发消息
}

int main(int argc, char*argv[]) 
{
    ros::init(argc, argv, "ground_extraction_node");
    ros::NodeHandle nh;
    // 创建发布者
    ground_pub = nh.advertise<sensor_msgs::PointCloud2>("output_ground",10);//发布地面点云数据
    marker_pub = nh.advertise<visualization_msgs::MarkerArray>("ground_markers", 10);//发布可视化标记makerarry类型数据
    // 创建订阅者，将回调函数指定为 cloudCallback
    ros::Subscriber cloud_sub = nh.subscribe("/lslidar_point_cloud", 1, cloudCallback);//订阅雷达数据包的点云数据
    ros::spin();
    return 0;
}