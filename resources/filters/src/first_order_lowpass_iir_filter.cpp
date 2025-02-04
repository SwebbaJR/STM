#include "filters/first_order_lowpass_iir_filter.hpp"

FirstOrderLowpassIIRFilter::FirstOrderLowpassIIRFilter(FilterDynamicsCoefficient filter_dynamics_coefficients) :
    filter_dynamics_coefficient(filter_dynamics_coefficients)
{
    
}

FirstOrderLowpassIIRFilter::~FirstOrderLowpassIIRFilter()
{

}

float FirstOrderLowpassIIRFilter::update(const float input, const float deltaT)
{
    float unscalled_output = input + previous_input + (2.0*filter_dynamics_coefficient.time_constant/deltaT - 1.0)*previous_output;
    float new_output = (1.0/(1.0 + 2.0*filter_dynamics_coefficient.time_constant/deltaT))*unscalled_output;

    previous_input = input;
    previous_output = new_output;

    return new_output;
}

void FirstOrderLowpassIIRFilter::set_filter_dynamics(FilterDynamicsCoefficient new_filter_dynamics_coefficient)
{
    filter_dynamics_coefficient = new_filter_dynamics_coefficient;
}