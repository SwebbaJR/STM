#ifndef OBSERVERS__EXTENDED_KALMAN_FILTER_HPP
#define OBSERVERS__EXTENDED_KALMAN_FILTER_HPP

#include <Eigen/Dense>

/** @brief
 * Template class for an Extended Kalman Filter
 * Filter includes the generic predict and update functions
 * The user must implement the state transition jacobian and state prediction functions
 * Additonally each measurement update function is defined outside of the class
 */
template<size_t N_STATES>
class ExtendedKalmanFilter
{
public:
   explicit ExtendedKalmanFilter(Eigen::Matrix<float, N_STATES, 1> x0_est,
                                 Eigen::Matrix<float, N_STATES, N_STATES> P0,
                                 Eigen::Matrix<float, N_STATES, N_STATES> Q);

    ~ExtendedKalmanFilter(){};

protected:

    Eigen::Matrix<float, N_STATES, 1> x_estimate;
    Eigen::Matrix<float, N_STATES, N_STATES> F;
    Eigen::Matrix<float, N_STATES, N_STATES> P;
    Eigen::Matrix<float, N_STATES, N_STATES> Q;

    virtual void update_state_transition_jacobian(const float& dt) = 0;
    virtual void state_prediction(const float& dt) = 0;

    template<int N_MEASUREMENTS>
    void update(const Eigen::Matrix<float, N_MEASUREMENTS, 1>& z,
                const Eigen::Matrix<float, N_MEASUREMENTS, 1>& z_estimate,
                const Eigen::Matrix<float, N_MEASUREMENTS, N_STATES>& H,
                const Eigen::Matrix<float, N_MEASUREMENTS, N_MEASUREMENTS>& R);

    void predict(const float& dt);

private:

};

template<size_t N_STATES>
ExtendedKalmanFilter<N_STATES>::ExtendedKalmanFilter(Eigen::Matrix<float, N_STATES, 1> x0_est,
    Eigen::Matrix<float, N_STATES, N_STATES> P0,
    Eigen::Matrix<float, N_STATES, N_STATES> Q)
    : x_estimate(x0_est), 
    P(P0), 
    Q(Q)
{
}

template<size_t N_STATES>
void ExtendedKalmanFilter<N_STATES>::predict(const float& dt)
{
    update_state_transition_jacobian(dt);

    state_prediction(dt);
    P = F * P * F.transpose() + dt*Q;
}

// Can make a vector of measurements descriptions which hold y, S, K, H, R
// so that they are pre allocated every time
// The temporary variables are here stack allocated so they are fast
template<size_t N_STATES>
template<int N_MEASUREMENTS>
void ExtendedKalmanFilter<N_STATES>::update(const Eigen::Matrix<float, N_MEASUREMENTS, 1>& z,
                                            const Eigen::Matrix<float, N_MEASUREMENTS, 1>& z_estimate,
                                            const Eigen::Matrix<float, N_MEASUREMENTS, N_STATES>& H,
                                            const Eigen::Matrix<float, N_MEASUREMENTS, N_MEASUREMENTS>& R)
{
    Eigen::Matrix<float, N_MEASUREMENTS, 1> y;
    y.noalias() = z - z_estimate;

    Eigen::Matrix<float, N_MEASUREMENTS, N_MEASUREMENTS> S;
    S.noalias() = H * P * H.transpose() + R;

    Eigen::Matrix<float, N_STATES, N_MEASUREMENTS> K;
    K.noalias() = P * H.transpose() * S.inverse();

    x_estimate.noalias() += K * y;
    P = (Eigen::Matrix<float, N_STATES, N_STATES>::Identity() - K * H) * P;
}


#endif // OBSERVERS__EXTENDED_KALMAN_FILTER_HPP