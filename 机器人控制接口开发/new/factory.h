#include <unordered_map>
#include <memory>
#include "camera.h"
#include "arm.h"
#include "Chassis.h"



// class robot
// {
// public:
//     Ship(ShipBody* body, Weapon* weapon, Engine* engine) :
//         m_body(body), m_weapon(weapon), m_engine(engine) 
//     {
//     }
//     string getProperty()
//     {
//         string info = m_body->getShipBody() + m_weapon->getWeapon() + m_engine->getEngine();
//         return info;
//     }
//     ~Ship() 
//     {
//         delete m_body;
//         delete m_engine;
//         delete m_weapon;
//     }
// private:
//     ShipBody* m_body = nullptr;
//     Weapon* m_weapon = nullptr;
//     Engine* m_engine = nullptr;
// };

// // 工厂类
// class AbstractFactory
// {
// public:
//     virtual Ship* createShip() = 0;
//     virtual ~AbstractFactory() {}
// };



std::unordered_map<std::string, std::unique_ptr<Camera>>
make_cameras_from_configs(const std::unordered_map<std::string,CameraConfig> &configs)
{
    std::unordered_map<std::string, std::unique_ptr<Camera>> cameras;
    for (const auto &[name, config] : configs)
    {
        // 检查配置类型是否为OpenCV相机
        if (config.type == "opencv")
        {
            try
            {
                cameras[name] = std::make_unique<OpenCVCamera>(
                    config.device,
                    config.fps,
                    config.width,
                    config.height,
                    config.rotation);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Failed to create camera: " << name << " - " << e.what() << std::endl;
            }
        }
        else
        {
            std::cerr << "Unsupported config type for camera: " << name << std::endl;
        }
    }
    return cameras;
}

std::unordered_map<std::string, std::unique_ptr<RoboticArm>>
make_arms_from_configs(const std::unordered_map<std::string, ArmConfig> &configs)
{
    std::unordered_map<std::string, std::unique_ptr<RoboticArm>> arms;
    for (const auto &[name, config] : configs)
    {
        // 检查配置类型是否为RoboticArm
        if (config.type == "gen72")
        {
            try
            {
                arms[name] = std::make_unique<Gen72>(configs);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Failed to create arm: " << name << " - " << e.what() << std::endl;
            }
        }
    }
    return arms;
}



std::unique_ptr<Chassis> make_chassis_from_config(const ChassiConfig &config)
{
    // 检查配置类型是否为mick底盘
    if (config.type == "mick")
    {
        try
        {
            return std::make_unique<Mick_Chassis>(config);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Failed to create chassis: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cerr << "Unsupported chassis type: " << config.type << std::endl;
    }
    return nullptr;
}