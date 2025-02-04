/*
#include "transforms/clark_transformer.hpp"
#include "transforms/park_transformer.hpp"

#include <iostream>

int main()
{
    ClarkTransformer clark_transformer;
    ParkTransformer park_transformer;

    PhaseUVW uvw;
    uvw.u = 1.0;
    uvw.v = 2.0;
    uvw.w = -3.0;

    ClarkeAlphaBeta ab;

    clark_transformer.uvw_to_ab(uvw, ab);

    std::cout << "ab.alpha: " << ab.alpha << std::endl;
    std::cout << "ab.beta: " << ab.beta << std::endl;

    ParkDQ dq;

    park_transformer.ab_to_dq(ab, 1.2, dq);

    std::cout << "dq.d: " << dq.d << std::endl;
    std::cout << "dq.q: " << dq.q << std::endl;

    ClarkeAlphaBeta ab2;

    park_transformer.dq_to_ab(dq, 1.2, ab2);

    std::cout << "ab2.alpha: " << ab2.alpha << std::endl;
    std::cout << "ab2.beta: " << ab2.beta << std::endl;

    PhaseUVW uvw2;

    clark_transformer.ab_to_uvw(ab2, uvw2);

    std::cout << "uvw2.u: " << uvw2.u << std::endl;
    std::cout << "uvw2.v: " << uvw2.v << std::endl;
    std::cout << "uvw2.w: " << uvw2.w << std::endl;

    return 0;
}

*/