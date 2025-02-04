#ifndef VOLTAGE_MODULATORS__SIX_STEP_MODULATOR_HPP
#define VOLTAGE_MODULATORS__SIX_STEP_MODULATOR_HPP

#include "transforms/transforms_prims.hpp"

#include <cstddef>

enum class SectorsABC : std::size_t
{
    Sector100 = 0,
    Sector101 = 1,
    Sector001 = 2,
    Sector011 = 3,
    Sector010 = 4,
    Sector110 = 5,
    NUMBER_OF_SECTORS = 6
};

/** 
 * @brief Six step modulator
 * 
 * Uses the complimentary six step modulator technique to generate the PWM signals for the inverter
 * The system used right alligned PWM
 * Output varies between [0, 1] and has -1.0 to set if an output should be floating
 * Where low-side MOSFETS are closed though a full commutation period and high-side is PWM controlled
 * Illustration video with equations: https://www.youtube.com/watch?v=QgcAJpRFj1U and https://www.youtube.com/watch?v=xIORHY8Ii90 
 * The system uses the following configuration of where the Hall sensors are located:
 * - Hall A is between phase U and V
 * - Hall B is between phase U and W
 * - Hall C is between phase V and W
 * Sectors are 60 angle of north pole of magnet with respect to U to V phase 
 */
class SixStepModulator
{
public:
    SixStepModulator();
    ~SixStepModulator();

    void update(const SectorsABC sector, const float voltage_duty_cycle, const bool counter_clock_wise, PhaseUVW& uvw_duty_cycle_output);
private:
};






#endif // VOLTAGE_MODULATORS__SIX_STEP_MODULATOR_HPP