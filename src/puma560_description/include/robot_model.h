#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf2/LinearMath/Matrix3x3.h>

class LINK{
    public:
        LINK(void);
        void read_config(std::string link_name, const std::string &links_config_path);
        tf2::Matrix3x3 get_inertia(void){
            return _I;
        }
        double get_mass(void){
            return _m;
        }
        tf2::Vector3 get_CoM(void){
            return _r;
        }
        void set_ri(tf2::Vector3 ri){
            _ri = ri;
            link_init_ = true;
        }
        tf2::Vector3 get_ri(void){
            return _ri;
        }
        std::string get_name(void){
            return _link_name;
        }
        bool init(void){
            return link_init_;
        } 
    private:
        tf2::Matrix3x3 _I;
        tf2::Vector3 _r;
        tf2::Vector3 _ri;
        bool link_init_ = false;
        double _m;
        std::string _link_name;
};
