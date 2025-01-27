#ifndef CONTROLLERS__PID_CONTROLLER_HPP
#define CONTROLLERS__PID_CONTROLLER_HPP

// TODO: Make low pass filter
#include <memory>
#include <cmath>
#include "filters/first_order_lowpass_iir_filter.hpp"

class PIDController
{
public:
    struct ControllerParameters
    {
        float Kp;
        float Ki;
        float Kd;
        float max_limit;
        float min_limit;
        FirstOrderLowpassIIRFilter::FilterDynamicsCoefficient derivative_filter_time_constant;
    };

    explicit PIDController(ControllerParameters controller_parameters);
    ~PIDController();

    float update(const float reference, const float measurement, const float deltaT);
    void set_controller_parameters(ControllerParameters controller_parameters);
private:
    float anti_windup(const float saturated_output, const float proportional_output, const float derivative_output);
    float saturate_output(const float output);

    ControllerParameters controller_parameters;
    float integral_error{0.0};
    float previous_error{0.0};
    float previous_derivative{0.0};
    std::unique_ptr<FirstOrderLowpassIIRFilter> derivative_filter;
};


#endif // CONTROLLERS__PID_CONTROLLER_HPP