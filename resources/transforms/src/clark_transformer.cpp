#include <cmath>

#include "transforms/clark_transformer.hpp"

#include <iostream>

ClarkTransformer::ClarkTransformer()
{

}

ClarkTransformer::~ClarkTransformer()
{
}

void ClarkTransformer::uvw_to_ab(const PhaseUVW& uvw, ClarkeAlphaBeta& ab0)
{
    ab0.alpha    = scale_factors.u_alpha * uvw.u + scale_factors.v_alpha * uvw.v + scale_factors.w_alpha * uvw.w;
    ab0.beta     =                                 scale_factors.v_beta * uvw.v  + scale_factors.w_beta * uvw.w;
}

void ClarkTransformer::ab_to_uvw(const ClarkeAlphaBeta& ab, PhaseUVW& uvw)
{
    uvw.u = scale_factors.alpha_u * ab.alpha;                        
    uvw.v = scale_factors.alpha_v * ab.alpha + scale_factors.beta_v * ab.beta;
    uvw.w = scale_factors.alpha_w * ab.alpha + scale_factors.beta_w * ab.beta;
}