
#include "parser.hpp"
#include "missile.hpp"

#include <VECTORS/matrices.hpp>
#include <iostream>
#include <fstream>

#define SAVE_DEFAULT "params.txt"
#define SAVE_COMMENT "//"


std::ostream& operator<<(std::ostream& os, const Conditions &c) {
    os << "CONDITIONS" << '\n'
       << "end: " << c.end << '\n'
       << "dt: " << c.dt << '\n'
       << c.m;
    return os;

}

// parse the command line args for the save location (if none given use defualt)
char* find_save(int argc, char **argv) {
    if (!argc) {
        return SAVE_DEFAULT;
    }
    return argv[0];

}


// in-place, strips comments from a line
void strip_comment(std::string &string) {
    size_t pos = string.find(SAVE_COMMENT);
    if (pos == std::string::npos) {
        return; // pos returned -1, substring was not found
    }
    string.erase(pos); // removes everything past the pos. erase(0,5) removes in range

}


// splits a string in two at the first instance of a colon
// "key: value"
std::array<std::string, 2> split(const std::string& line, char letter) {
    std::array<std::string, 2> delimited; // "" in each string
    
    size_t pos = line.find(letter);
    if (pos == std::string::npos) {
        delimited[0] = line;
        return delimited;

    }
    std::string key = line.substr(0, pos); // everything up until pos
    std::string val = line.substr(pos + 1); // everything beyond pos
    
    delimited[0] = key;
    delimited[1] = val;

    return delimited;

}

// parses a save file into a blstc::Conditions struct.
Conditions parse_params(char *save_path) {
    Conditions c;
    
    // how to process the value of each key into the struct
    std::unordered_map<std::string, std::function<void(const std::string&)>> setters = {
        {"yaw", [&](const std::string &v){c.yaw = std::stof(v);}},
        {"pitch", [&](const std::string &v){c.pitch = std::stof(v);}},
        {"roll", [&](const std::string &v){c.roll = std::stof(v);}},
        {"x", [&](const std::string &v){c.m.position[0] = std::stof(v);}},
        {"y", [&](const std::string &v){c.m.position[1] = std::stof(v);}},
        {"z", [&](const std::string &v){c.m.position[2] = std::stof(v);}},
        {"vx", [&](const std::string &v){c.m.velocity[0] = std::stof(v);}},
        {"vy", [&](const std::string &v){c.m.velocity[1] = std::stof(v);}},
        {"vz", [&](const std::string &v){c.m.velocity[2] = std::stof(v);}},

        {"end", [&](const std::string &v){c.end = std::stof(v);}},
        {"dt", [&](const std::string &v){c.dt = std::stof(v);}},
        {"gravity", [&](const std::string &v){c.gravity = std::stof(v);}},
        {"rho", [&](const std::string &v){c.rho = std::stof(v);}},

        {"burn_active", [&](const std::string &v){c.m.motor.active = std::stoi(v);}},
        {"burn_time", [&](const std::string &v){c.m.motor.duration = std::stof(v);}},
        {"burn_force", [&](const std::string &v){c.m.motor.force = std::stof(v);}},

        {"mass", [&](const std::string &v){c.m.body.mass = std::stof(v);}},
        {"inertia_pitch", [&](const std::string &v){c.m.body.inertia[0] = std::stof(v);}},
        {"inertia_roll", [&](const std::string &v){c.m.body.inertia[1] = std::stof(v);}},
        {"inertia_yaw", [&](const std::string &v){c.m.body.inertia[2] = std::stof(v);}},

        {"nose_cd", [&](const std::string &v){c.m.body.nose_cd = std::stof(v);}},
        {"side_cd", [&](const std::string &v){c.m.body.side_cd = std::stof(v);}},

        {"radius", [&](const std::string &v){c.m.body.radius = std::stof(v);}},
        {"length", [&](const std::string &v){c.m.body.length = std::stof(v);}}
    };

    std::ifstream file(save_path);
    if (!file) {
        std::cerr << "FAILED TO FIND INITIAL CONDITIONS FILE: " << save_path << std::endl;
        return c;
    }

    std::string line;
    while (std::getline(file, line)) {
        strip_comment(line);
        std::array<std::string, 2> key_value = split(line, ':');
        std::string key = key_value[0];
        std::string val = key_value[1];

        if (!key.length()) {
            continue; // if key empty (most likely line was empty)
        }

        auto it = setters.find(key); // iterator of key value pair
        if (it != setters.end()) {
            it->second(val);
        }
    }

    c.m.rotation = matrix_from_euler(c.yaw, c.pitch, c.roll);


    return c;

}

