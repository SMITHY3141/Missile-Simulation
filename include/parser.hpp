
#ifndef PARSER_HPP
#define PARSER_HPP

#include "missile.hpp"
#include <iostream>

struct Conditions {
    misl::Missile m;
    float end = 1.f;
    float dt = 0.1f;

    float yaw = 0.f;
    float pitch = 0.f;
    float roll = 0.f;

};

std::ostream& operator<<(std::ostream& os, const Conditions &c);

char* find_save(int argc, char **argv);
Conditions parse_params(char *save_path);

#endif // PARSER_HPP
