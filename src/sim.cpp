

#include "sim.hpp"
#include "parser.hpp"
#include "missile.hpp"

namespace sim {
    misl::Missile missile(const Conditions& c) {
        misl::Missile m = c.m;
        
        for (float t = 0; t < c.end; t += c.dt) {
            update_state(m, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, c.dt);

        }
        return m;
    }
}
