

#include "sim.hpp"
#include "parser.hpp"
#include "missile.hpp"

#include <iostream>
#include <fstream>

#define LOG_DEFAULT "logs/log.csv"

namespace sim {
    misl::Missile missile(const Conditions& c) {
        misl::Missile m = c.m;

        std::ofstream out(LOG_DEFAULT); // file used to log data
        if (!out) {
            return m;
        }
        log_header_missile(out);

        
        for (float t = 0; t < c.end; t += c.dt) {
            log_missile(out, t, m);
            update_state(m, {0.f, 0.f, -9.8f}, {0.f, 0.f, 0.f}, c.dt);

        }
        log_missile(out, c.end, m);

        out.close();

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
