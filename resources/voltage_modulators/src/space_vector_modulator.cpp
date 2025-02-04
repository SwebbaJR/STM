#include "voltage_modulators/space_vector_modulator.hpp"

#include <algorithm>

SpaceVectorModulator::SpaceVectorModulator()
{
}

SpaceVectorModulator::~SpaceVectorModulator()
{
}   

void SpaceVectorModulator::update(const ClarkeAlphaBeta& ab_duty_cycles, PhaseUVW& uvw_nominal_compare_value)
{
    clark_transformer.ab_to_uvw(ab_duty_cycles, uvw_nominal_compare_value);

    float max_element = std::max({uvw_nominal_compare_value.u, uvw_nominal_compare_value.v, uvw_nominal_compare_value.w});
    float min_element = std::min({uvw_nominal_compare_value.u, uvw_nominal_compare_value.v, uvw_nominal_compare_value.w});

    float common_mode_duty_cycle = -(max_element + min_element)/2.0;

    uvw_nominal_compare_value.u += common_mode_duty_cycle + DUTY_CYCLE_OFFSET;
    uvw_nominal_compare_value.v += common_mode_duty_cycle + DUTY_CYCLE_OFFSET;
    uvw_nominal_compare_value.w += common_mode_duty_cycle + DUTY_CYCLE_OFFSET;

    uvw_nominal_compare_value.u *= DUTY_CYCLE_GAIN;
    uvw_nominal_compare_value.v *= DUTY_CYCLE_GAIN;
    uvw_nominal_compare_value.w *= DUTY_CYCLE_GAIN; 
}   