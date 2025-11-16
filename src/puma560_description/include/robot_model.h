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
        void set_r_next(tf2::Vector3 r_next){
            _r_next = r_next;
            _link_r_next_init = true;
        }
        void set_ri(tf2::Vector3 ri){
            _ri = ri;
            _link_ri_init = true;
        }
        tf2::Vector3 get_ri(void){
            return _ri;
        }
        tf2::Vector3 get_r_next(void){
            return _r_next;
        }
        std::string get_name(void){
            return _link_name;
        }
        bool init(void){
            return (_link_ri_init && _link_r_next_init);
        } 
    private:
        tf2::Matrix3x3 _I;
        tf2::Vector3 _r;
        tf2::Vector3 _ri; // Vector from joint with next link to CoM
        tf2::Vector3 _r_next; // Vector to joint with the next link
        bool _link_ri_init = false;
        bool _link_r_next_init = false;
        double _m;
        std::string _link_name;
};
