#include "robot_model.h"
#include <stdio.h>


LINK::LINK(void){
    
}

void LINK::read_config(std::string link_name, const std::string &links_config_path){
    YAML::Node links_config = YAML::LoadFile(links_config_path);
    _link_name = link_name;
    _m = links_config["inertia_parameters"][link_name+"_mass"].as<double>();
    _r[0] = links_config["inertia_parameters"]["center_of_mass"][link_name+"_cog"]
            ["x"].as<double>();
    _r[1] = links_config["inertia_parameters"]["center_of_mass"][link_name+"_cog"]
            ["y"].as<double>();
    _r[2] = links_config["inertia_parameters"]["center_of_mass"][link_name+"_cog"]
            ["z"].as<double>();
    _I[0][0] = links_config["inertia_parameters"]["tensor"][link_name]["ixx"].as<double>();
    _I[0][1] = links_config["inertia_parameters"]["tensor"][link_name]["ixy"].as<double>();
    _I[0][2] = links_config["inertia_parameters"]["tensor"][link_name]["ixz"].as<double>();
    _I[1][1] = links_config["inertia_parameters"]["tensor"][link_name]["iyy"].as<double>();
    _I[1][2] = links_config["inertia_parameters"]["tensor"][link_name]["iyz"].as<double>();
    _I[2][2] = links_config["inertia_parameters"]["tensor"][link_name]["izz"].as<double>();
    _I[1][0] = _I[0][1];
    _I[2][0] = _I[0][2];
    _I[2][1] = _I[1][2];
}
