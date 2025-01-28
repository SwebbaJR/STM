#ifndef FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_PARAMETERS_HPP
#define FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_PARAMETERS_HPP

#include "controllers/pid_controller.hpp"

struct FocControllerParameters
{
    PIDController::ControllerParameters d_current_controller_parameters;
    PIDController::ControllerParameters q_current_controller_parameters;
};

struct FocData
{
    struct 
    {
        float d_current;
        float q_current;
    }references;
    
    float phase_a_current;
    float phase_b_current;
    float phase_c_current;
    float rotor_position;
    float rotor_velocity;
};


#endif