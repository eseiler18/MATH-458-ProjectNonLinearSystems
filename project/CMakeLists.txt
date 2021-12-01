include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp AbstractSolver.cpp AbstractSolver.h
        Newton.cpp Newton.h ClassicChord.cpp ClassicChord.h)

add_executable(main_louis main_louis.cpp Bisection.cpp FixedPoint.cpp)



