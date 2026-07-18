


#include "missile.hpp"
#include <iostream>


namespace misl {
    std::ostream& operator<<(std::ostream& os, const Missile &m) {
        os << "MISSILE" << '\n'
           << "position: " << m.position << '\n'
           << "velocity: " << m.velocity << '\n'
           << "rotation: " << m.rotation << '\n'
           << "motor active: " << m.motor.active << '\n'
           << "motor duration: " << m.motor.duration << '\n'
           << "motor force: " << m.motor.force;

        return os;
    }

    Vector<3> force_motor(const Missile &m) {
        if (!m.motor.active || m.motor.duration < 0) {
            return {0.f, 0.f, 0.f};
        
        }
        Vector<3> forward{m.rotation[0][1], m.rotation[1][1], m.rotation[2][1]};
        return forward * m.motor.force; 

    }

    // aerodynamic drag caused by the fuselage body.
    // F_d = 0.5 * p * V^2 * C_d * A
    // density in kg/m^3
    Vector<3> force_body(const Missile &m, float air_density) {
        float speed = m.velocity.length();
        if (speed < 0.0001) {
            return {0.f, 0.f, 0.f};
        }
        float cone_area = M_PI * m.body.radius * m.body.radius;
        Vector<3> forward{m.rotation[0][1], m.rotation[1][1], m.rotation[2][1]};

        
        Vector<3> force = -m.velocity.normalised();
        force *= force.dot(forward) * m.body.nose_cd; // C_d approximation
        force *= 0.5 * air_density * speed * speed * cone_area;

        return force;


    }

    void update_state(Missile &m, const Vector<3> &acc, const Vector<3> &ang, float dt) {
        m.position += m.velocity * dt;
        m.velocity += acc * dt;

        if (m.motor.active && m.motor.duration > 0) {
            m.motor.duration -= dt; // TODO redo motors, should depend on exit speed and mass burn rate, thus decreasing mass with burn

        }
    }
}
