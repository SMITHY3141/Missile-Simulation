
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
    struct Mass {
        float mass;
        float inertia;

    };

    struct Missile {
        Vector<3> position;
        Vector<3> velocity;
        Matrix<3, 3> rotation; // right and forward body vectors
        RocketMotor motor;
        Fins fins;

    };

    std::ostream& operator<<(std::ostream& os, const Missile &m);

    Vector<3> calculate_force(const Missile &m);
    Vector<3> calculate_torque(const Missile &m);
    void update_state(Missile &m, const Vector<3> &acc, const Vector<3> &rot, float dt);

}



#endif // MISSILE_HPP
