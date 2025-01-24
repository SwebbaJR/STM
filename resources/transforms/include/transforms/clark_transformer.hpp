#ifndef TRANSFORMS__CLARK_TRANSFORMER_HPP
#define TRANSFORMS__CLARK_TRANSFORMER_HPP

#include <cmath>

#include "transforms/transforms_prims.hpp"

class ClarkTransformer
{
public:
    ClarkTransformer();
    ~ClarkTransformer();

    void uvw_to_ab(const PhaseUVW& uvw, ClarkeAlphaBeta& ab);
    void ab_to_uvw(const ClarkeAlphaBeta& ab, PhaseUVW& uvw);

private:
    struct ScaleFactors
    {
        // For transform from uvw to ab
        constexpr static float uvw_to_ab_current_scale_factor = std::sqrt(2.0/3.0);

        constexpr static float u_alpha = 1.0*uvw_to_ab_current_scale_factor;
        constexpr static float v_alpha = -0.5*uvw_to_ab_current_scale_factor;
        constexpr static float w_alpha = -0.5*uvw_to_ab_current_scale_factor;

        constexpr static float v_beta = std::sqrt(3.0)/2.0*uvw_to_ab_current_scale_factor;
        constexpr static float w_beta = -std::sqrt(3.0)/2.0*uvw_to_ab_current_scale_factor;

        // For transform from ab to uvw
        constexpr static float ab_to_uvw_current_scale_factor = std::sqrt(2.0/3.0);

        constexpr static float alpha_u = 1.0*ab_to_uvw_current_scale_factor;
        
        constexpr static float alpha_v = -0.5*ab_to_uvw_current_scale_factor;
        constexpr static float beta_v  = std::sqrt(3.0)/2.0*ab_to_uvw_current_scale_factor;

        constexpr static float alpha_w = -0.5*ab_to_uvw_current_scale_factor;
        constexpr static float beta_w  = -std::sqrt(3.0)/2.0*ab_to_uvw_current_scale_factor;
    }scale_factors;
};



#endif // TRANSFORMS__CLARK_TRANSFORMER_HPP