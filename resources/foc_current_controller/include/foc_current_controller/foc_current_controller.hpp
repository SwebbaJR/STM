#ifndef FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP
#define FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP

#include <memory>

#include "foc_current_controller/foc_current_controller_parameters.hpp"
#include "controllers/pid_controller.hpp"
#include "voltage_modulators/space_vector_modulator.hpp"

class FocCurrentController
{
public:
    explicit FocCurrentController(FocControllerParameters parameters);
    ~FocCurrentController();

    //update (const FocData& foc_data, const FocData& reference, const float deltaT);

    void set_parameters(const FocControllerParameters& parameters);
    void set_d_controller_parameters(const PIDController::ControllerParameters& d_controller_parameters);
    void set_q_controller_parameters(const PIDController::ControllerParameters& q_controller_parameters);

private:
    std::unique_ptr<PIDController> d_current_controller;
    std::unique_ptr<PIDController> q_current_controller;
    std::unique_ptr<SpaceVectorModulator> space_vector_modulator;
    FocControllerParameters parameters;
};

#endif // FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP