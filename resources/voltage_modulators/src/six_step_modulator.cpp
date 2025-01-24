#include "voltage_modulators/six_step_modulator.hpp"

SixStepModulator::SixStepModulator()
{
}

SixStepModulator::~SixStepModulator()
{
}

void SixStepModulator::update(const SectorsABC sector, const float voltage_duty_cycle, const bool counter_clock_wise, PhaseUVW& uvw_duty_cycle_output)
{
    if (counter_clock_wise)
    {
        switch (sector)
        {
        case SectorsABC::Sector100:
            uvw_duty_cycle_output.u = -1.0;
            uvw_duty_cycle_output.v = 0.0;
            uvw_duty_cycle_output.w = voltage_duty_cycle;
            break;
        case SectorsABC::Sector101:
            uvw_duty_cycle_output.u = voltage_duty_cycle;
            uvw_duty_cycle_output.v = 0.0;
            uvw_duty_cycle_output.w = -1.0;
            break;
        case SectorsABC::Sector001:
            uvw_duty_cycle_output.u = voltage_duty_cycle;
            uvw_duty_cycle_output.v = -1.0;
            uvw_duty_cycle_output.w = 0.0;
            break;
        case SectorsABC::Sector011:
            uvw_duty_cycle_output.u = -1.0;
            uvw_duty_cycle_output.v = voltage_duty_cycle;
            uvw_duty_cycle_output.w = 0.0;
            break;
        case SectorsABC::Sector010:
            uvw_duty_cycle_output.u = 0.0;
            uvw_duty_cycle_output.v = voltage_duty_cycle;
            uvw_duty_cycle_output.w = -1.0;
            break;
        case SectorsABC::Sector110:
            uvw_duty_cycle_output.u = 0.0;
            uvw_duty_cycle_output.v = -1.0;
            uvw_duty_cycle_output.w = voltage_duty_cycle;
            break;
        default:
            uvw_duty_cycle_output.u = 0.0;
            uvw_duty_cycle_output.v = 0.0;
            uvw_duty_cycle_output.w = 0.0;
            break;
        }
    }
    else
    {
        switch (sector)
        {
        case SectorsABC::Sector100:
            uvw_duty_cycle_output.u = -1.0;
            uvw_duty_cycle_output.v = voltage_duty_cycle;
            uvw_duty_cycle_output.w = 0.0;
            break;
        case SectorsABC::Sector101:
            uvw_duty_cycle_output.u = 0.0;
            uvw_duty_cycle_output.v = voltage_duty_cycle;
            uvw_duty_cycle_output.w = -1.0;
            break;
        case SectorsABC::Sector001:
            uvw_duty_cycle_output.u = 0.0;
            uvw_duty_cycle_output.v = -1.0;
            uvw_duty_cycle_output.w = voltage_duty_cycle;
            break;
        case SectorsABC::Sector011:
            uvw_duty_cycle_output.u = -1.0;
            uvw_duty_cycle_output.v = 0.0;
            uvw_duty_cycle_output.w = voltage_duty_cycle;
            break;
        case SectorsABC::Sector010:
            uvw_duty_cycle_output.u = voltage_duty_cycle;
            uvw_duty_cycle_output.v = 0.0;
            uvw_duty_cycle_output.w = -1.0;
            break;
        case SectorsABC::Sector110:
            uvw_duty_cycle_output.u = voltage_duty_cycle;
            uvw_duty_cycle_output.v = -1.0;
            uvw_duty_cycle_output.w = 0.0;
            break;
        default:
            uvw_duty_cycle_output.u = 0.0;
            uvw_duty_cycle_output.v = 0.0;
            uvw_duty_cycle_output.w = 0.0;
            break;
        }
    }
    
}