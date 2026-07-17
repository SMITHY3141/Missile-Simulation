


#include "missile.hpp"
#include <iostream>


namespace misl {
    std::ostream& operator<<(std::ostream& os, const Missile &m) {
        os << "MISSILE" << '\n'
           << "position: " << m.position << '\n'
           << "velocity: " << m.velocity << '\n'
           << "rotation: " << m.rotation;

        return os;
    }

    void update_state(Missile &m, const Vector<3> &force, const Vector<3> &torque, float dt) {
        m.position += m.velocity * dt;
        m.velocity += force * dt; // TODO mass too
    }
}
