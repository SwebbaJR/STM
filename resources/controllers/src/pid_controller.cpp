#include "controllers/pid_controller.hpp"

PIDController::PIDController(ControllerParameters controller_parameters) :
    controller_parameters(controller_parameters)
{
    derivative_filter = std::make_unique<FirstOrderLowpassIIRFilter>(controller_parameters.derivative_filter_time_constant);
}

PIDController::~PIDController()
{

}

float PIDController::update(const float& reference, const float& measurement, const float& deltaT)
{
    float error = reference - measurement;

    // Integral state using Tustin transform
    integral_error += deltaT/2.0*(error + previous_error);

    // Derivative termin using Tustin transform
    float derivative = 2.0/deltaT*(error - previous_error) - previous_derivative;
    float filtered_derivative = derivative_filter->update(derivative, deltaT);

    // Compute controller compontents
    float unsaturated_output = controller_parameters.Kp*error + controller_parameters.Ki*integral_error + controller_parameters.Kd*filtered_derivative;

    // Saturate output
    float saturated_output = saturate_output(unsaturated_output);

    // Anti-windup: Adjust integral term if output is saturated
    if (saturated_output != unsaturated_output)
    {
        integral_error = anti_windup(unsaturated_output, saturated_output);
    }

    // Update parameters
    previous_error = error;
    previous_derivative = derivative;

    return saturated_output;
}

void PIDController::feedback_saturation(const float& saturated_output)
{
    integral_error = anti_windup(previous_output, saturated_output);
}

float PIDController::saturate_output(const float& unsaturated_output)
{
    if (unsaturated_output > controller_parameters.max_limit)
    {
        return controller_parameters.max_limit;
    }
    else if (unsaturated_output < controller_parameters.min_limit)
    {
        return controller_parameters.min_limit;
    }
    return unsaturated_output;
}

float PIDController::anti_windup(const float unsaturated_output, const float& saturated_output)
{   
    if (controller_parameters.Ki == 0.0)
    {
        return 0.0;
    }
    return (integral_error*controller_parameters.Ki - unsaturated_output + saturated_output)/controller_parameters.Ki;
}

void PIDController::set_controller_parameters(const ControllerParameters& new_controller_parameters)
{
    controller_parameters = new_controller_parameters;
}

void PIDController::set_min_max_limits(const float& min_limit, const float& max_limit)
{
    controller_parameters.min_limit = min_limit;
    controller_parameters.max_limit = max_limit;
}