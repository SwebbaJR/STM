#ifndef FILTERS__FIRST_ORDER_LOWPASS_IIR_FILTER_HPP
#define FILTERS__FIRST_ORDER_LOWPASS_IIR_FILTER_HPP

#include <cmath>

/**
 * @brief This implementation is of a first order IIR filter 
 * The filter is based on the billinear discretization technique  
 */

class FirstOrderLowpassIIRFilter
{
public:
    struct FilterDynamicsCoefficient
    {
        float time_constant;
    };

    explicit FirstOrderLowpassIIRFilter(FilterDynamicsCoefficient filter_dynamics_coefficients);
    ~FirstOrderLowpassIIRFilter();

    float update(const float input, const float deltaT);
    void set_filter_dynamics(FilterDynamicsCoefficient filter_dynamics_coefficients);
    
private:
    FilterDynamicsCoefficient filter_dynamics_coefficient;
    float previous_output{0.0};
    float previous_input{0.0};
};


#endif // FILTERS__FIRST_ORDER_LOWPASS_IIR_FILTER