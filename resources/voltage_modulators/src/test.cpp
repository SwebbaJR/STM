/*
#include "voltage_modulators/space_vector_modulator.hpp"
#include "transforms/park_transformer.hpp"

#include <iostream>

#include <cmath>
#include <numbers>

void print_pwm(const PhaseUVW& uvw_pwm_output)
{
    std::cout << "uvw_pwm_output.u: " << uvw_pwm_output.u << std::endl;
    std::cout << "uvw_pwm_output.v: " << uvw_pwm_output.v << std::endl;
    std::cout << "uvw_pwm_output.w: " << uvw_pwm_output.w << std::endl;
}

int main()
{
    SpaceVectorModulator space_vector_modulator;

    ParkTransformer park_transformer;

    ParkDQ park_duty_cycles;
    park_duty_cycles.d = 0.0;
    park_duty_cycles.q = -1.0;

    float rotor_angle = std::numbers::pi/180.0*133.0;

    ClarkeAlphaBeta ab_duty_cycles;

    park_transformer.dq_to_ab(park_duty_cycles, rotor_angle, ab_duty_cycles);

    PhaseUVW uvw_duty_cycles;
    space_vector_modulator.update(ab_duty_cycles, uvw_duty_cycles);

    print_pwm(uvw_duty_cycles);

    return 0;
}
*/