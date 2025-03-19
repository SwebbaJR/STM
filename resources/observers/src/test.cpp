#include <iostream>
#include "observers/extended_kalman_filter.hpp"

const size_t TEST_N_STATES = 2;

class TestOberserver : private ExtendedKalmanFilter<TEST_N_STATES>
{
    struct TestObserverIndicies
    {
        static const size_t POSITION = 0;
        static const size_t VELOCITY = 1;
    };

    struct ObservationSizes
    {
        static const size_t POSITION = 1;
    };

    struct StateMap
    {
        Eigen::Map<Eigen::Matrix<float, 1, 1>> p;
        Eigen::Map<Eigen::Matrix<float, 1, 1>> v;

        StateMap(Eigen::Matrix<float, TEST_N_STATES, 1>& x)
            : p(x.data()), 
            v(x.data() + 1)
        {
        }
    };

public:

    TestOberserver()
            : ExtendedKalmanFilter<TEST_N_STATES>(Eigen::Matrix<float, TEST_N_STATES, 1>::Zero(),
                                    Eigen::Matrix<float, TEST_N_STATES, TEST_N_STATES>::Identity(),
                                    Eigen::Matrix<float, TEST_N_STATES, TEST_N_STATES>::Identity()),
            H_position(Eigen::Matrix<float, ObservationSizes::POSITION, TEST_N_STATES>::Zero())
    {
    };

    ~TestOberserver(){};

    void on_position_measurement(const Eigen::Matrix<float, ObservationSizes::POSITION, 1>& z, const float dt)
    {
        predict(dt);

        Eigen::Matrix<float, ObservationSizes::POSITION, 1> z_estimate;
        z_estimate(0,0) = x_estimate(TestObserverIndicies::POSITION);
        update_position_measurement_jacobian();
        update(z, z_estimate, H_position, R);
    };

    void get_position()
    {
        std::cout << "Position: " << x_estimate(TestObserverIndicies::POSITION) << std::endl;
    };

private:    

    void update_state_transition_jacobian(const float& dt) override
    {
        F << 1.0, dt,
            0.0, 1.0;
    };

    void state_prediction(const float& dt) override
    {
        states.p += dt*states.v;
    };

    void update_position_measurement_jacobian()
    {
        H_position(TestObserverIndicies::POSITION, TestObserverIndicies::POSITION) = 1.0;
    };

    Eigen::Matrix<float, ObservationSizes::POSITION, TEST_N_STATES> H_position;
    Eigen::Matrix<float, ObservationSizes::POSITION, ObservationSizes::POSITION> R{1.0};

    StateMap states{x_estimate};
};


int main() 
{
    TestOberserver test_observer;
    Eigen::Matrix<float, 1, 1> z;
    z << 0.0;
    for (size_t i = 0; i < 50; i++)
    {
        if (i == 10)
        {
            z << 1.0;
        }
        test_observer.on_position_measurement(z, 0.005);
        test_observer.get_position();
    }

    return 0;
}