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
    integral_error += deltaT*error;
    float filtered_derivative = derivative_filter->update(measurement, deltaT);

    float unsaturated_output = controller_parameters.Kp*error + controller_parameters.Ki*integral_error + controller_parameters.Kd*filtered_derivative;
    
    previous_error = error;

    return saturate_output(unsaturated_output);
}

float PIDController::saturate_output(const float output)
{

}

void PIDController::set_controller_parameters(ControllerParameters new_controller_parameters)
{
    controller_parameters = new_controller_parameters;
}