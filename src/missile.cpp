


#include "missile.hpp"
#include <iostream>

#define RIGHT 0
#define FORWARD 1
#define UP 2

namespace misl {
    std::ostream& operator<<(std::ostream& os, const Missile &m) {
        os << "MISSILE" << '\n'
           << "position: " << m.position << '\n'
           << "velocity: " << m.velocity << '\n'
           << "omega: " << m.omega << '\n'
           << "rotation: " << m.rotation << '\n'
           << "inertia: " << m.body.inertia << '\n'
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
    // TODO add a lookup function for C_d coefficients (they should depend
    // with things like aoa and speed too).
    Vector<3> force_body(const Missile &m, float air_density) {
        float speed = m.velocity.length();
        if (speed < 1e-6) {
            return {0.f, 0.f, 0.f};
        }

        Vector<3> vel_hat = m.velocity.normalised();
        Vector<3> right = get_column(m.rotation, RIGHT);
        Vector<3> forward = get_column(m.rotation, FORWARD);
        Vector<3> up = get_column(m.rotation, UP);
        float aoa = -std::atan2(up.dot(m.velocity), forward.dot(m.velocity));
        float slip = std::atan2(right.dot(m.velocity), forward.dot(m.velocity));

        float pressure = 0.5 * air_density * speed * speed; // dynamic pressure

        return {0.f, 0.f, 0.f};

    }
    
    Vector<3> acceleration(const Missile &m, const Vector<3> &force) {
        return force / m.body.mass;
    
    }

    Vector<3> angular_acceleration(const Missile &m, const Vector<3> &torque) {
        return m.body.inertia.inverse() * (torque - m.omega.cross(m.body.inertia * m.omega));

    }

    void update_state(Missile &m, const Vector<3> &acc, const Vector<3> &ang, float dt) {
        m.position += m.velocity * dt;
        m.velocity += acc * dt;

        m.rotation = rotate(m.rotation, m.omega * dt);
        //normalise_gram(m.rotation); // probably doesn't have to be every tick
        m.omega += ang * dt;


        if (m.motor.active && m.motor.duration > 0) {
            m.motor.duration -= dt; // TODO redo motors, should depend on exit speed and mass burn rate, thus decreasing mass with burn

        }
    }
}
