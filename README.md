<h1 align="center">Finding rare trajectories in transiently chaotic systems</h1>
<p align="center">
    <img width="500" alt="Henon Landscape" src="extra/colormap.png">
</p>

## About

The aim of this project is to study the properties of trasiently chaotic dynamical systems, like the Henon map. 
Given a certain point of a chosen domain, we can map it into another point using the Henon Map. This mapping is generally not inifintesimal. We can do this again to the latter. How many times do we have to repeat this process in order to obtain a point which fell outside our domain? That is the definition of escape time. In the picture shown above, the x-y plane is our domain, and in the z-axis is represented the escape time. We want to have a grasp of some general properties of this system in order to develop an efficient and fast algorithm that finds domain points with the highest escape time possible.

## How to run the code

### Compile and run command

For example, to compile and run henon.cpp, with a maximum escape time of 50 iterations, run:

```sh
g++  -I/opt/local/include -L/opt/local/lib -lgmp -lmpfr -std=c++11 henon.cpp -o henon -Wall ; ./henon 50
```

### mpreal

The mpreal.h and mpreal0.h files are wrappers which make the use of GNU MPFR (GNU Multiple Precision Floating-Point Reliably) much easier. All the proper credits are contained in the files themselves. If the compiler outputs "deprecated" warnings, just switch the names of the mpreal files, that should fix it:

```sh
mv mpreal.h temp.h && mv mpreal0.h mpreal.h && mv temp.h mpreal0.h
```

If you lose track of which one is which, the most up-to-date version has a "modified version" flag in the beginning of the file itself.

