#include "controllers/pid_controller.hpp"

PIDController::PIDController(ControllerParameters controller_parameters) :
    controller_parameters(controller_parameters)
{
    derivative_filter = std::make_unique<FirstOrderLowpassIIRFilter>(controller_parameters.derivative_filter_time_constant);
}

PIDController::~PIDController()
{

}

float PIDController::update(const float reference, const float measurement, const float deltaT)
{
    float error = reference - measurement;

    // Integral state using Tustin transform
    integral_error += deltaT/2.0*(error + previous_error);

    // Derivative termin using Tustin transform
    float derivative = 2.0/deltaT*(error - previous_error) - previous_derivative;
    float filtered_derivative = derivative_filter->update(derivative, deltaT);

    // Compute controller compontents
    float proportional_output = controller_parameters.Kp*error;
    float integral_output = controller_parameters.Ki*integral_error;
    float derivative_output = controller_parameters.Kd*filtered_derivative;
    float unsaturated_output = proportional_output + integral_output + derivative_output;

    // Saturate output
    float saturated_output = saturate_output(unsaturated_output);

    // Anti-windup: Adjust integral term if output is saturated
    if (saturated_output != unsaturated_output)
    {
        integral_error = anti_windup(saturated_output, proportional_output, derivative_output);
    }

    previous_error = error;
    previous_derivative = derivative;

    return saturated_output;
}

float PIDController::saturate_output(const float unsaturated_output)
{
    return std::max(controller_parameters.min_limit, std::min(unsaturated_output, controller_parameters.max_limit));
}

float PIDController::anti_windup(const float saturated_output, const float proportional_output, const float derivative_output)
{
    return (saturated_output - proportional_output - derivative_output)/controller_parameters.Ki;
}

void PIDController::set_controller_parameters(ControllerParameters new_controller_parameters)
{
    controller_parameters = new_controller_parameters;
}