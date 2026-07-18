
#include "parser.hpp"
#include "missile.hpp"
#include <iostream>
#include <fstream>


namespace sim {
    misl::Missile missile(const Conditions& c);
    void log_missile(std::ofstream &out, float t, const misl::Missile &m);
    void log_header_missile(std::ofstream &out);

}
