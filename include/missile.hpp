
#ifndef MISSILE_HPP
#define MISSILE_HPP

#include <iostream>
#include <VECTORS/vectors.hpp>
#include <VECTORS/matrices.hpp>
#define SAMPLES 10
#define AOA_STEP 4.f

namespace misl {
    struct RocketMotor {
        float force;
        float duration;
        int active;

    };
    struct Aero {
        float C_d;
        float C_l;

    };
    struct Fins {
        float pitch;
        float yaw;

    };
    struct Body {
        float mass;
        Matrix<3, 3> inertia; ///< order of pitch, roll, yaw

    };

    struct Missile {
        Vector<3> position;
        Vector<3> velocity;
        Vector<3> omega;
        Matrix<3, 3> rotation; // right, forward, and up body vectors
        RocketMotor motor;
        Fins fins;
        Body body;
        Aero aero[SAMPLES];
        float daoa;

    };

    std::ostream& operator<<(std::ostream& os, const Missile &m);

    Vector<3> force_motor(const Missile &m);
    Vector<3> force_body(const Missile &m, float air_density);
    Vector<3> force_fins(const Missile &m, float air_density); // TODO

    Vector<3> torque_fins(const Missile &m, float air_density);

    Vector<3> acceleration(const Missile &m, const Vector<3> &force);
    Vector<3> angular_acceleration(const Missile &m, const Vector<3> &torque);

    void update_state(Missile &m, const Vector<3> &acc, const Vector<3> &ang, float dt);

}



#endif // MISSILE_HPP
