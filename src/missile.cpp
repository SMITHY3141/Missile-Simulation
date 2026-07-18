


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
        float body_area = 2 * m.body.radius * m.body.length;

        Vector<3> forward{m.rotation[0][1], m.rotation[1][1], m.rotation[2][1]};
        Vector<3> dir = m.velocity.normalised();

        //TODO C_d should change with speed

        // calculate area * c_d for nose and side
        float cone_drag = cone_area;
        cone_drag *= dir.dot(forward) * m.body.nose_cd; // C_d approximation

        float body_drag = body_area;
        body_drag *= (1 - dir.dot(forward)) * m.body.side_cd;

        // combine for full drag force
        return -dir * 0.5 * air_density * speed * speed * (cone_drag + body_drag);

    }

    void update_state(Missile &m, const Vector<3> &acc, const Vector<3> &ang, float dt) {
        m.position += m.velocity * dt;
        m.velocity += acc * dt;

        if (m.motor.active && m.motor.duration > 0) {
            m.motor.duration -= dt; // TODO redo motors, should depend on exit speed and mass burn rate, thus decreasing mass with burn

        }
    }
}
