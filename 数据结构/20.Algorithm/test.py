import rospy
from std_msgs.msg import String
from your_package.msg import DetectedObject

if __name__ == '__main__':
    print("[INFO] YoloV5目标检测-程序启动")
    print("[INFO] 开始YoloV5模型加载")
    # YOLOV5模型配置文件(YAML格式)的路径 yolov5_yaml_path
    model = YoloV5(yolov5_yaml_path='/home/nvidia/RMl/RML_robot/src/yolov5_detect/scripts/config/yolov5s.yaml')
    print("[INFO] 完成YoloV5模型加载")

    rospy.init_node('object_detector')
    pub = rospy.Publisher('/detected_objects', DetectedObject, queue_size=10)

    try:
        while not rospy.is_shutdown():    # 修改循环条件为rospy没有关闭
            intr, depth_intrin, color_image, depth_image, aligned_depth_frame = get_aligned_images()
            if not depth_image.any() or not color_image.any():
                continue

            depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(
                depth_image, alpha=0.03), cv2.COLORMAP_JET)

            images = np.hstack((color_image, depth_colormap))
            
            t_start = time.time()  
            canvas, class_id_list, xyxy_list, conf_list = model.detect(
                color_image)

            t_end = time.time()  

            if xyxy_list:
                for i in range(len(xyxy_list)):
                    ux = int((xyxy_list[i][0]+xyxy_list[i][2])/2)
                    uy = int((xyxy_list[i][1]+xyxy_list[i][3])/2)
                    dis = aligned_depth_frame.get_distance(ux, uy)
                    camera_xyz = rs.rs2_deproject_pixel_to_point(
                        depth_intrin, (ux, uy), dis)
                    camera_xyz = np.round(np.array(camera_xyz), 3)
                    camera_xyz = camera_xyz.tolist()

                    # 添加ROS发布消息部分
                    detected_object = DetectedObject()
                    detected_object.class_id = class_id_list[i]
                    detected_object