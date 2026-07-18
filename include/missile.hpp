
#ifndef MISSILE_HPP
#define MISSILE_HPP

#include <iostream>
#include <VECTORS/vectors.hpp>
#include <VECTORS/matrices.hpp>

namespace misl {
    struct RocketMotor {
        float force;
        float duration;
        int active;

    };

    struct Fins {
        float pitch;
        float yaw;
        float offset;

    };
    struct Fuselage {
        float length;
        float radius;
        float mass;
        float nose_cd;
        float side_cd;
        Vector<3> inertia; ///< order of pitch, roll, yaw

    };

    struct Missile {
        Vector<3> position;
        Vector<3> velocity;
        Matrix<3, 3> rotation; // right, forward, and up body vectors
        RocketMotor motor;
        Fins fins;
        Fuselage body;

    };

    std::ostream& operator<<(std::ostream& os, const Missile &m);

    Vector<3> force_motor(const Missile &m);
    Vector<3> force_body(const Missile &m, float air_density);
    Vector<3> force_fins(const Missile &m, float air_density);

    Vector<3> torque_body(const Missile &m, float air_density);
    Vector<3> torque_fins(const Missile &m, float air_density);

    void update_state(Missile &m, const Vector<3> &acc, const Vector<3> &ang, float dt);

}



#endif // MISSILE_HPP
