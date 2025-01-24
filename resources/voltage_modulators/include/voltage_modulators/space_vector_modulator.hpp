#ifndef VOLTAGE_MODULATORS__SPACE_VECTOR_MODULATOR_HPP
#define VOLTAGE_MODULATORS__SPACE_VECTOR_MODULATOR_HPP

#include <cmath>

#include "transforms/clark_transformer.hpp"

/** 
 * @brief Space vector modulator
 * 
 * Uses the space vector modulation technique to generate the PWM signals for the inverter
 * Based on center aligned PWM
 * Illustration video with equations: https://www.youtube.com/watch?v=nh9TD2M2r-o
 */
class SpaceVectorModulator
{
public:

    SpaceVectorModulator();
    ~SpaceVectorModulator();

    /**
     * @brief Update the UVW PWM duty cycles based on a pwm magnitude and electric angle
     * ab_duty_cycles is the Vref/Vdc ratio and in the range [-1.0, 1.0]
     * uvw_duty_cycle_output is the nominal compare values for the three phases uvw in the range [0.0, 1.0]
     */
    void update(const ClarkeAlphaBeta& ab_duty_cycles, PhaseUVW& uvw_nominal_compare_value);

private:
    ClarkTransformer clark_transformer;
    constexpr static float DUTY_CYCLE_OFFSET = 1.0/std::sqrt(2.0);
    constexpr static float DUTY_CYCLE_GAIN = 1.0/std::sqrt(2.0);
};

#endif // VOLTAGE_MODULATORS__SPACE_VECTOR_MODULATOR_HPP