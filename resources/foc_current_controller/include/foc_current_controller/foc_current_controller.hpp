#ifndef FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP
#define FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP

#include <memory>
#include <cmath>

#include "foc_current_controller/foc_current_controller_definitions.hpp"
#include "controllers/pid_controller.hpp"
#include "voltage_modulators/space_vector_modulator.hpp"
#include "transforms/park_transformer.hpp"

/**
 * @brief The following class implements an FOC controller which utilizes:
 * Two PID controllers to control D and Q currents
 * Feedback of saturation from combined controllers
 * Space vector PWM as modulator
 * Based on the dynamical model in: https://www.mathworks.com/help/sps/ref/bldc.html 
 */
class FocCurrentController
{
public:
    explicit FocCurrentController(FocDefinitions::FocControllerParameters controller_parameters, 
                                    FocDefinitions::MotorParameters motor_parameters);
    ~FocCurrentController();

    void update(const FocDefinitions::FocData& foc_data, const float& deltaT, PhaseUVW& uvw_nominal_compare_value);

    void set_controller_parameters(const FocDefinitions::FocControllerParameters& new_controller_parameters);
    void set_d_controller_parameters(const PIDController::ControllerParameters& d_controller_parameters);
    void set_q_controller_parameters(const PIDController::ControllerParameters& q_controller_parameters);

private:
    void compute_current_references(const float& torque_reference, const float& maximum_phase_voltage, ParkDQ& current_references);

    std::unique_ptr<PIDController> d_current_controller;
    std::unique_ptr<PIDController> q_current_controller;
    std::unique_ptr<SpaceVectorModulator> space_vector_modulator;

    std::unique_ptr<ClarkTransformer> clarke_transformer;
    std::unique_ptr<ParkTransformer> park_transformer;

    FocDefinitions::FocControllerParameters controller_parameters;
    FocDefinitions::MotorParameters motor_parameters;

    constexpr static float MAX_DC_LINK_VOLTAGE_TO_PHASE_VOLTAGE_FACTOR = 1.0/std::sqrt(6.0);
    const float Q_CURRENT_TO_TORQUE_RELATION;
};

#endif // FOC_CURRENT_CONTROLLER__FOC_CURRENT_CONTROLLER_HPP