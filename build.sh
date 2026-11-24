#!/bin/bash
g++ dropsim.cpp -o dropsim -std=c++17 -O3 -pthread -march=native
g++ dropsim.cpp -o dropsimbase -D"BASETC=1" -std=c++17 -O3 -pthread -march=native
g++ dropsolver.cpp -o dropsolver -std=c++17 -O3 -pthread -march=native
g++ dropsolver.cpp -o dropsolverbase -D"BASETC=1" -std=c++17 -O3 -pthread -march=native
g++ test.cpp txtrotw.cpp -o test -std=c++17 -g -O3 -pthread -march=native
g++ sorcbuild.cpp sorcskills.cpp monsters.cpp txtrotw.cpp -o sorcbuild -std=c++17 -O3 -pthread -march=native
