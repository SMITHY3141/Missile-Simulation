

#include "sim.hpp"
#include "parser.hpp"
#include "missile.hpp"

#include <iostream>
#include <fstream>

#define LOG_DEFAULT "logs/log.csv"

namespace sim {
    misl::Missile missile(const Conditions& c) {
        misl::Missile m = c.m;

        // setup file we'll log to
        std::ofstream log(LOG_DEFAULT); // file used to log data
        if (!log) {
            return m;
        }
        log_header_missile(log);

        
        for (float t = 0; t < c.end; t += c.dt) {
            log_missile(log, t, m);
            
            // Calculate forces
            Vector<3> force{0};
            Vector<3> torque{0};

            force += misl::force_motor(m);
            force += misl::force_body(m, c.rho);
            /*force += misl::force_fins(m);

            torque += misl::torque_body(m);
            torque += misl::torque_fins(m);*/


            // Calculate linear and angular acceleration from forces
            Vector<3> acc = force / m.body.mass;
            Vector<3> ang = torque / m.body.inertia;

            // acc[2] += c.gravity; // gravity

            misl::update_state(m, acc, ang, c.dt);

        }
        log_missile(log, c.end, m); // otherwise we miss last log


        log.close();
        return m;

    }

    void log_missile(std::ofstream &out, float t, const misl::Missile &m) {
        out << t << ','
            << m.position[0] << ','
            << m.position[1] << ','
            << m.position[2];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                out << ',' << m.rotation[j][i];
        
            }
        }
        out << std::endl;

    }

    void log_header_missile(std::ofstream &out) {
        out << "t,x,y,z,r_x,r_y,r_z,f_x,f_y,f_z,u_x,u_y,u_z" << std::endl;

    }
}
