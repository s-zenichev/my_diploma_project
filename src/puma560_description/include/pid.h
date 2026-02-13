

#ifndef MY_PID
#define MY_PID

#include "std_msgs/msg/float64_multi_array.hpp"

class PID{
    public:
        PID(double P = 0, double I = 0, double D = 0, double N = 0, double I_min = 0, double I_max = 0){
            _p = P;
            _i = I;
            _d = D;
            _n = N;
            _i_min = I_min;
            _i_max = I_max;
        }
        void setP(double P){
            _p = P;
        }
        void setI(double I){
            _i = I;
            _integrator = 0;
        }
        void setIMin(double I_min){
            _i_min = I_min;
            _integrator = 0;
        }
        void setIMax(double I_max){
            _i_max = I_max;
            _integrator = 0;
        }
        void setD(double D){
            _d = D;
        }
        void setN(double N){
            _n = N;
        }
        void setPID(double P, double I, double D, double N){
            _p = P;
            _i = I;
            _d = D;
            _n = N;
        }
        void setPID(std_msgs::msg::Float64MultiArray &msg){
            _p = msg.data[1];
            _i = msg.data[2];
            _d = msg.data[3];
            _n = msg.data[4];
        }
        double getP(void){
            return _p;
        }
        double getI(void){
            return _i;
        }
        double getD(void){
            return _d;
        }
        double getN(void){
            return _n;
        }
        double getDerivative(double eps){
            return (eps*_d - _derivative_integrator)*_n;
        }
        double control(double eps){
            double contr = 0;
            contr += eps * _p;
            contr += _integrator;
            contr += (eps *_d - _derivative_integrator) * _n;
            _integrator += eps * _i;
            if (_integrator > _i_max) _integrator = _i_max;
            if (_integrator < _i_min) _integrator = _i_min;
            _derivative_integrator += (eps * _d - _derivative_integrator) * _n;
            return contr;
        }
    private:
        double _p;
        double _i;
        double _d;
        double _n;
        double _i_min;
        double _i_max;
        double _integrator;
        double _derivative_integrator;
};
#endif //MY_PID