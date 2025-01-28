#include "foc_current_controller/foc_current_controller.hpp"

FocCurrentController::FocCurrentController(FocDefinitions::FocControllerParameters parameters) :
    parameters(parameters)
{
    d_current_controller = std::make_unique<PIDController>(parameters.d_current_controller_parameters);
    q_current_controller = std::make_unique<PIDController>(parameters.q_current_controller_parameters);
    space_vector_modulator = std::make_unique<SpaceVectorModulator>();
    clarke_transformer = std::make_unique<ClarkTransformer>();
    park_transformer = std::make_unique<ParkTransformer>();
}   

FocCurrentController::~FocCurrentController()
{
    d_current_controller.reset();
    q_current_controller.reset();
}

void FocCurrentController::update(const FocDefinitions::FocData& foc_data, const float& deltaT, PhaseUVW& uvw_nominal_compare_value)
{
    float peak_phase_voltage = foc_data.dc_link_voltage*PEAK_PHASE_VOLTAGE_DC_LINK_FACTOR;

    // Update d and q current controllers
    float d_phase_voltage_output = d_current_controller->update(foc_data.dq_current_references.d, foc_data.dq_current.d, deltaT);
    float q_phase_voltage_output = q_current_controller->update(foc_data.dq_current_references.q, foc_data.dq_current.q, deltaT);

    float d_duty_cycle = d_phase_voltage_output/peak_phase_voltage;
    float q_duty_cycle = q_phase_voltage_output/peak_phase_voltage;

    // Saturate d and q phase voltage outputs
    float duty_cycle_magnitude = std::sqrt(std::pow(d_duty_cycle, 2) + std::pow(q_duty_cycle, 2));
    if (duty_cycle_magnitude > 1.0)
    {
        // Normalize d and q phase voltage magnitude between -1 and 1
        d_duty_cycle *= 1.0/duty_cycle_magnitude;
        q_duty_cycle *= 1.0/duty_cycle_magnitude;

        // Feedback the saturation due to both the d and q controllers
        float saturated_d_voltage = d_duty_cycle*peak_phase_voltage;
        float saturated_q_voltage = q_duty_cycle*peak_phase_voltage;
        d_current_controller->feedback_saturation(saturated_d_voltage);
        q_current_controller->feedback_saturation(saturated_q_voltage);
    }

    // Compute uvw nominal compare values fom the alpha beta duty cycles
    ClarkeAlphaBeta alpha_beta_duty_cycles;
    park_transformer->dq_to_ab({d_duty_cycle, q_duty_cycle}, foc_data.rotor_angle, alpha_beta_duty_cycles);
    space_vector_modulator->update(alpha_beta_duty_cycles, uvw_nominal_compare_value);
}

void FocCurrentController::set_parameters(const FocDefinitions::FocControllerParameters& new_parameters)
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

