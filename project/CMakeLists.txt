include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp AbstractSolver.cpp AbstractSolver.h
        Newton.cpp Newton.h ClassicChord.cpp ClassicChord.h readData/main_readData.cpp)

add_executable(main_louis main_louis.cpp AbstractSolver.cpp AbstractSolver.h
        Bisection.cpp Bisection.h FixedPoint.cpp FixedPoint.h)

add_subdirectory(parser)
add_subdirectory(readData)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../data.csv data.csv COPYONLY)



