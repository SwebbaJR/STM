#ifndef FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_PARAMETERS_HPP
#define FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_PARAMETERS_HPP

#include "controllers/pid_controller.hpp"
#include "transforms/transforms_prims.hpp"

namespace FocDefinitions
{
    struct FocControllerParameters
    {
        PIDController::ControllerParameters d_current_controller_parameters;
        PIDController::ControllerParameters q_current_controller_parameters;
        float max_curent_reference;
    };

    struct FocData
    {
        float torque_reference;
        ParkDQ dq_current_references;
        ParkDQ dq_current;
        float rotor_angle;
        float angular_velocity;
        float dc_link_voltage;
    };

    struct MotorParameters
    {
        size_t n_pole_pairs;
        float pm_flux_linkage;
        float Ld;
        float Lq;
        float Rs;
    };
}

#endif