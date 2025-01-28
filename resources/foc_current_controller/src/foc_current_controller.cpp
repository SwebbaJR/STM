#include "foc_current_controller/foc_current_controller.hpp"

FocCurrentController::FocCurrentController(FocControllerParameters parameters) :
    parameters(parameters)
{
    d_current_controller = std::make_unique<PIDController>(parameters.d_current_controller_parameters);
    q_current_controller = std::make_unique<PIDController>(parameters.q_current_controller_parameters);
    space_vector_modulator = std::make_unique<SpaceVectorModulator>();
}   

FocCurrentController::~FocCurrentController()
{
    d_current_controller.reset();
    q_current_controller.reset();
}

void FocCurrentController::set_parameters(const FocControllerParameters& new_parameters)
{
    parameters = parameters;
}

void FocCurrentController::set_d_controller_parameters(const PIDController::ControllerParameters& d_controller_parameters)
{
    parameters.d_current_controller_parameters = d_controller_parameters;
}

void FocCurrentController::set_q_controller_parameters(const PIDController::ControllerParameters& q_controller_parameters)
{
    parameters.q_current_controller_parameters = q_controller_parameters;
}