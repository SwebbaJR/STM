#ifndef FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP
#define FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP

#include <memory>
#include <cmath>

#include "foc_current_controller/foc_current_controller_definitions.hpp"
#include "controllers/pid_controller.hpp"
#include "voltage_modulators/space_vector_modulator.hpp"
#include "transforms/park_transformer.hpp"

class FocCurrentController
{
public:
    explicit FocCurrentController(FocDefinitions::FocControllerParameters parameters);
    ~FocCurrentController();

    void update(const FocDefinitions::FocData& foc_data, const float& deltaT, PhaseUVW& uvw_nominal_compare_value);

    void set_parameters(const FocDefinitions::FocControllerParameters& parameters);
    void set_d_controller_parameters(const PIDController::ControllerParameters& d_controller_parameters);
    void set_q_controller_parameters(const PIDController::ControllerParameters& q_controller_parameters);

private:
    std::unique_ptr<PIDController> d_current_controller;
    std::unique_ptr<PIDController> q_current_controller;
    std::unique_ptr<SpaceVectorModulator> space_vector_modulator;

    std::unique_ptr<ClarkTransformer> clarke_transformer;
    std::unique_ptr<ParkTransformer> park_transformer;

    FocDefinitions::FocControllerParameters parameters;

    constexpr static float PEAK_PHASE_VOLTAGE_DC_LINK_FACTOR = 1.0/std::sqrt(6.0);
};

#endif // FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP