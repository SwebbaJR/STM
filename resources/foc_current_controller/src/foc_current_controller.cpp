#include "foc_current_controller/foc_current_controller.hpp"

FocCurrentController::FocCurrentController(FocDefinitions::FocControllerParameters controller_parameters, 
                                            FocDefinitions::MotorParameters motor_parameters) :
    controller_parameters(controller_parameters),
    motor_parameters(motor_parameters),
    Q_CURRENT_TO_TORQUE_RELATION(3.0/2.0*motor_parameters.n_pole_pairs*motor_parameters.pm_flux_linkage)
{
    d_current_controller = std::make_unique<PIDController>(controller_parameters.d_current_controller_parameters);
    q_current_controller = std::make_unique<PIDController>(controller_parameters.q_current_controller_parameters);
    space_vector_modulator = std::make_unique<SpaceVectorModulator>();
    clarke_transformer = std::make_unique<ClarkTransformer>();
    park_transformer = std::make_unique<ParkTransformer>();
}   

FocCurrentController::~FocCurrentController()
{
    d_current_controller.reset();
    q_current_controller.reset();
    space_vector_modulator.reset();
    clarke_transformer.reset();
    park_transformer.reset();
}

// Should also return the realized torque so that the saturation can be fed back into the velocity controller
void FocCurrentController::update(const FocDefinitions::FocData& foc_data, const float& deltaT, PhaseUVW& uvw_nominal_compare_value)
{
    float max_phase_voltage = foc_data.dc_link_voltage*MAX_DC_LINK_VOLTAGE_TO_PHASE_VOLTAGE_FACTOR;

    ParkDQ dq_current_references;
    compute_current_references(foc_data.torque_reference, max_phase_voltage, dq_current_references);

    // Update d and q current controllers
    float d_phase_voltage_output = d_current_controller->update(dq_current_references.d, foc_data.dq_current.d, deltaT);
    float q_phase_voltage_output = q_current_controller->update(dq_current_references.q, foc_data.dq_current.q, deltaT);

    float d_duty_cycle = d_phase_voltage_output/max_phase_voltage;
    float q_duty_cycle = q_phase_voltage_output/max_phase_voltage;

    // Saturate d and q phase voltage outputs
    // TODO: Test this in script
    float duty_cycle_magnitude = std::sqrt(std::pow(d_duty_cycle, 2) + std::pow(q_duty_cycle, 2));
    if (duty_cycle_magnitude > 1.0)
    {
        // Normalize d and q phase voltage such that the voltage magnitude is between -1 and 1
        // To avoid overmodulation
        d_duty_cycle *= 1.0/duty_cycle_magnitude;
        q_duty_cycle *= 1.0/duty_cycle_magnitude;

        // Feedback the saturation due to both the d and q controllers
        float saturated_d_voltage = d_duty_cycle*max_phase_voltage;
        float saturated_q_voltage = q_duty_cycle*max_phase_voltage;
        d_current_controller->feedback_saturation(saturated_d_voltage);
        q_current_controller->feedback_saturation(saturated_q_voltage);
    }

    // Compute uvw nominal compare values fom the alpha beta duty cycles
    ClarkeAlphaBeta alpha_beta_duty_cycles;
    park_transformer->dq_to_ab({d_duty_cycle, q_duty_cycle}, foc_data.rotor_angle, alpha_beta_duty_cycles);
    space_vector_modulator->update(alpha_beta_duty_cycles, uvw_nominal_compare_value); // TOOD: Dobbel check this modulator to see if it gives a duty cycle which varies correctly
}

void FocCurrentController::compute_current_references(const float& torque_reference, const float& maximum_phase_voltage, ParkDQ& current_references)
{
    float i_q = torque_reference/Q_CURRENT_TO_TORQUE_RELATION;
    if (i_q > controller_parameters.max_curent_reference)
    {
        i_q = controller_parameters.max_curent_reference;
    }
    else if (i_q < -1.0*controller_parameters.max_curent_reference)
    {
        i_q = -1.0*controller_parameters.max_curent_reference;
    }
    current_references.d = 0.0;
    current_references.q = i_q;
    // TODO: Implement MTPA (Maximum Torque Per Ampere) control 
    // and MTVA (Maximum Torque Per Voltage) control on saturation?
}

void FocCurrentController::set_controller_parameters(const FocDefinitions::FocControllerParameters& new_controller_parameters)
{
    controller_parameters = new_controller_parameters;
}

void FocCurrentController::set_d_controller_parameters(const PIDController::ControllerParameters& d_controller_parameters)
{
    controller_parameters.d_current_controller_parameters = d_controller_parameters;
}

void FocCurrentController::set_q_controller_parameters(const PIDController::ControllerParameters& q_controller_parameters)
{
    controller_parameters.q_current_controller_parameters = q_controller_parameters;
}

