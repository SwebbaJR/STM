#include "transforms/park_transformer.hpp"

ParkTransformer::ParkTransformer()
{
}

ParkTransformer::~ParkTransformer()
{
}

void ParkTransformer::ab_to_dq(const ClarkeAlphaBeta& ab, const float rotor_electric_angle, ParkDQ& dq)
{
    dq.d =  std::cos(rotor_electric_angle)*ab.alpha + std::sin(rotor_electric_angle)*ab.beta;
    dq.q = -std::sin(rotor_electric_angle)*ab.alpha + std::cos(rotor_electric_angle)*ab.beta;
}

void ParkTransformer::dq_to_ab(const ParkDQ& dq, const float rotor_electric_angle, ClarkeAlphaBeta& ab)
{
    ab.alpha =  std::cos(rotor_electric_angle)*dq.d - std::sin(rotor_electric_angle)*dq.q;
    ab.beta  =  std::sin(rotor_electric_angle)*dq.d + std::cos(rotor_electric_angle)*dq.q;
}