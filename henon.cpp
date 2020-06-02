#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include "mpreal.h"
#include <vector> 
#include <array> 
#include <chrono>

using namespace std::chrono;
typedef mpfr::mpreal Float;

#include "tools.hpp"
#include "map.hpp"
#include "simulation.hpp"
#include "simulation_temp.hpp"
#include "mealder.hpp"

int main(int argc,char **argv)
{	
    unsigned tmin = 1;
    unsigned tmax = std::stoi(argv[2]);
    std::string alg_carlo   = "carlo";
    std::string alg_mealder = "mealder";
    mpfr::mpreal::set_default_prec(1024);
    std::cout.precision(8);

    if (argv[1] == alg_carlo){
    Simulation simul(tmin, tmax);
    Simulation_temp simul_temp(tmin, tmax);

    // Monte Carlo Simulation
    for(unsigned count = 0; count < 100; count++)
    {
        while(simul.count < 10)
            simul.MonteCarloStep();

        while(simul_temp.count < 10)
            simul_temp.MonteCarloStep();

//        print_simul(simul);
        print_comparison(simul, simul_temp);
        
        simul.decreasef();
        simul_temp.decreasef();
    }}
    // Nelder-Mead Method
    if (argv[1] == alg_mealder){
    Mealder meal(tmax);

    for (unsigned trie = 0; trie < 1000; trie++){
        meal.TRIANGLE_GEN();
        for (unsigned iter = 0; iter < 1000; iter++){
            meal.NelderMeadStep();
        }
    print_point(meal.verts[0]);
    }}


}	

// g++ -I/usr/local/include -L/usr/local/lib -lgmp -lmpfr -std=c++11 henon.cpp -o henon; ./henon carlo 50
