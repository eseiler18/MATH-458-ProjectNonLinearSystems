# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# adding the Google_Tests_run target
add_executable(Google_Tests_run test1.cc ../project/AbstractSolver.cpp ../project/Newton.cpp
        ../project/ClassicChord.cpp ../project/Bisection.cpp ../project/FixedPoint.cpp  ../project/parser/AbstractNode.h
        ../project/parser/NumberNode.h ../project/parser/VariableNode.h ../project/parser/OperatorNode.h
        ../project/parser/OperatorNode.cpp ../project/parser/TokenType.h ../project/parser/AbstractToken.h
        ../project/parser/Token.h ../project/parser/TokenContainer.h ../project/parser/TokenReader.cpp
        ../project/parser/TokenReader.h ../project/parser/Parser.cpp ../project/parser/Parser.h
        ../project/parser/Builder.cpp ../project/parser/Builder.h ../project/parser/Solver.h
        ../project/readData/ReaderData.cpp ../project/readData/ReaderData.h ../project/readData/Data.h
        ../project/ExceptionIterate.h)

target_link_libraries(Google_Tests_run ${CMAKE_DL_LIBS})
target_link_libraries(Google_Tests_run gtest gtest_main)



