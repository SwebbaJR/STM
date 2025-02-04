#ifndef TRANSFORMS__PARK_TRANSFORMER_HPP
#define TRANSFORMS__PARK_TRANSFORMER_HPP

#include <cmath>

#include "transforms/transforms_prims.hpp"

class ParkTransformer
{
public:
    ParkTransformer();
    ~ParkTransformer();

    void ab_to_dq(const ClarkeAlphaBeta& ab, const float rotor_electric_angle, ParkDQ& dq);
    void dq_to_ab(const ParkDQ& dq, const float rotor_electric_angle, ClarkeAlphaBeta& ab);

private:
};

#endif // TRANSFORMS__PARK_TRANSFORMER_HPP