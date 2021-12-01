include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp AbstractSolver.cpp AbstractSolver.h
        Newton.cpp Newton.h ClassicChord.cpp ClassicChord.h)



