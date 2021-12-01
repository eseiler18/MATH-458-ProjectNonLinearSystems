cmake_minimum_required(VERSION 3.20)
project(PCSC-project)
set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp AbstractSolver.cpp AbstractSolver.h
        Newton.cpp Newton.h ClassicChord.cpp ClassicChord.h)



