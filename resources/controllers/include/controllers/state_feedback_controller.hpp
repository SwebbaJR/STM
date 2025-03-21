#ifndef CONTROLLER__STATE_FEEDBACK_CONTROLLER_HPP
#define CONTROLLER__STATE_FEEDBACK_CONTROLLER_HPP

#include <Eigen/Dense>

/** @brief
 * This template class implements a state feedback controller with integral action
 * The controller takes in the control matrices Kp, Ki and K_ref 
 * and the reference matrix C_z which is used to calculate the integral states, z_integral
 * The integral estimates are updated using tustin's method
 * The controller output is calculated from the feedback rule: u = -dt * (Kp*x + Ki*z_integral)
 * where: z_integral = integral(C_z*x - z_reference)
 */
template<size_t N_STATES, size_t N_CONTROL_INPUTS, size_t N_REFERENCES>
class StateFeedbackController
{
public:

    explicit StateFeedbackController(const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_p,
        const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_i,
        const Eigen::Matrix<float, N_STATES, N_STATES>& C_z);
    ~StateFeedbackController();

    void set_references(const Eigen::Matrix<float, N_REFERENCES, 1>& z_reference) {this->z_reference = z_reference;};

    Eigen::Matrix<float, N_CONTROL_INPUTS, 1> update(const float dt, const Eigen::Matrix<float, N_STATES, 1>& x);
    void set_controller_gains(const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_p,
        const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_i);

    void set_saturations(const Eigen::Matrix<float, N_CONTROL_INPUTS, 1>& max_limit, const Eigen::Matrix<float, N_CONTROL_INPUTS, 1>& min_limit){this->max_limit = max_limit; this->min_limit = min_limit;};

private:

    Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES> F_p;
    Eigen::Matrix<float, N_CONTROL_INPUTS, N_REFERENCES> F_i;
    Eigen::Matrix<float, N_REFERENCES, N_STATES> C_z;

    Eigen::Matrix<float, N_REFERENCES, 1> z_integral{0.0};
    Eigen::Matrix<float, N_REFERENCES, 1> z_reference;
    Eigen::Matrix<float, N_REFERENCES, 1> dz_integral_previous{0.0};

    Eigen::Matrix<float, N_CONTROL_INPUTS, 1> max_limit;
    Eigen::Matrix<float, N_CONTROL_INPUTS, 1> min_limit;

    Eigen::Matrix<float, N_CONTROL_INPUTS, 1> saturate_output(const Eigen::Matrix<float, N_CONTROL_INPUTS, 1>& unsaturated_u);
};

template<size_t N_STATES, size_t N_CONTROL_INPUTS, size_t N_REFERENCES>
StateFeedbackController<N_STATES, N_CONTROL_INPUTS, N_REFERENCES>::StateFeedbackController(
    const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_p,
    const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_i,
    const Eigen::Matrix<float, N_STATES, N_STATES>& C_z)
    : F_p(F_p), F_i(F_i), C_z(C_z)
{
    z_integral.setZero();
    z_reference.setZero();
}

template<size_t N_STATES, size_t N_CONTROL_INPUTS, size_t N_REFERENCES>
StateFeedbackController<N_STATES, N_CONTROL_INPUTS, N_REFERENCES>::~StateFeedbackController()
{
}

template<size_t N_STATES, size_t N_CONTROL_INPUTS, size_t N_REFERENCES>
Eigen::Matrix<float, N_CONTROL_INPUTS, 1> 
StateFeedbackController<N_STATES, N_CONTROL_INPUTS, N_REFERENCES>::update(const float dt, const Eigen::Matrix<float, N_STATES, 1>& x)
{
    Eigen::Matrix<float, N_REFERENCES, 1> dz_integral = C_z * x - z_reference;
    z_integral += dt * (dz_integral + dz_integral_previous) / 2.0;
    dz_integral_previous = dz_integral;

    Eigen::Matrix<float, N_CONTROL_INPUTS, 1> u = -dt * (F_p * x + F_i * z_integral);

    // TODO: Add anti windup

    return saturate_output(u);
}

template<size_t N_STATES, size_t N_CONTROL_INPUTS, size_t N_REFERENCES>
void StateFeedbackController<N_STATES, N_CONTROL_INPUTS, N_REFERENCES>::set_controller_gains(
    const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_p,
    const Eigen::Matrix<float, N_CONTROL_INPUTS, N_STATES>& F_i)
{
    this->F_p = F_p;
    this->F_i = F_i;
}

template<size_t N_STATES, size_t N_CONTROL_INPUTS, size_t N_REFERENCES>
Eigen::Matrix<float, N_CONTROL_INPUTS, 1> StateFeedbackController<N_STATES, N_CONTROL_INPUTS, N_REFERENCES>::saturate_output(const Eigen::Matrix<float, N_CONTROL_INPUTS, 1>& unsaturated_u)
{
    Eigen::Matrix<float, N_CONTROL_INPUTS, 1> saturated_u = unsaturated_u;

    for (size_t i = 0; i < N_CONTROL_INPUTS; i++)
    {
        if (unsaturated_u(i) > max_limit(i))
        {
            saturated_u(i) = max_limit(i);
        }
        else if (unsaturated_u(i) < min_limit(i))
        {
            saturated_u(i) = min_limit(i);
        }
    }

    return saturated_u;
}



#endif // CONTROLLER__STATE_FEEDBACK_CONTROLLER_HPP