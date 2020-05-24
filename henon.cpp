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
#include "mealder.hpp"

int main(int argc,char **argv)
{	
    unsigned tmin = 1;
    unsigned tmax = std::stoi(argv[1]);
    mpfr::mpreal::set_default_prec(1024);
    std::cout.precision(8);

//    Mealder meal(tmax);
//    for (unsigned trie = 0; trie < 1000; trie++){
//        meal.TRIANGLE_GEN();
//        for (unsigned iter = 0; iter < 1000; iter++){
//            meal.NelderMeadStep();
//        }
//    print(meal.verts[0]);
//    }

    Simulation simul(tmin, tmax);
    for(unsigned count = 0; count < 100; count++)
      {
        while(simul.count < 10)
            simul.MonteCarloStep();
        
        for(unsigned t = 0; t < simul.tmax; t++)
            std::cout << t << " " << simul.HISTO[t] << " " << simul.SIGMA[t] << std::endl;
        
          simul.decreasef();
      }

}	

// g++ -I/usr/local/include -L/usr/local/lib -lgmp -lmpfr -std=c++11 henon.cpp -o henon; ./henon
