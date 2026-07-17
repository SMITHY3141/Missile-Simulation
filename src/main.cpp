

#include "parser.hpp"
#include "missile.hpp"
#include "sim.hpp"
#include <iostream>

int main(int argc, char **argv) {
    argc--;
    argv++;

    char* save_path = find_save(argc, argv);
    Conditions conditions = parse_params(save_path);
    std::cout << '\n' << conditions << '\n' << '\n';

    misl::Missile m = sim::missile(conditions);
    std::cout << m << '\n';


}




