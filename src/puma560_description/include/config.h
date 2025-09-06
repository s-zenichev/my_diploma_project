#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include "pid.h"

namespace YAML
{
    void decode(const Node &node, PID &pid)
    {
        if (node.size() != 6)
        {
            return;
        }
        pid.setP(node["P"].as<double>());
        pid.setI(node["I"].as<double>());
        pid.setD(node["D"].as<double>());
        pid.setN(node["N"].as<double>());
        pid.setIMin(node["I_min"].as<double>());
        pid.setIMax(node["I_max"].as<double>());
    };

}

void initPID(PID speed_controller[], PID position_controller[],
             const std::string &pid_config_path)
{
    YAML::Node pid_config = YAML::LoadFile(pid_config_path);
    for (int i = 0; i < 6; i++)
    {
        YAML::decode(pid_config["speed"]["j_" + std::to_string(i + 1)], speed_controller[i]);
        YAML::decode(pid_config["position"]["j_" + std::to_string(i + 1)], position_controller[i]);
    }
}