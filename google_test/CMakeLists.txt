# 'Google_test' is the subproject name
project(Google_tests)

# 'googletest' is the folder with Google Test sources
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# adding the Google_Tests_run target
add_executable(Google_Tests_run test1.cc ../project/solverMethods/AbstractSolver.cpp ../project/solverMethods/Newton.cpp
        ../project/solverMethods/ClassicChord.cpp ../project/solverMethods/Bisection.cpp
        ../project/solverMethods/FixedPoint.cpp ../project/solverMethods/ExceptionIterate.h
        ../project/readData/parser/AbstractNode.h ../project/readData/parser/NumberNode.h
        ../project/readData/parser/VariableNode.h ../project/readData/parser/OperatorNode.h
        ../project/readData/parser/OperatorNode.cpp
        ../project/readData/parser/TokenType.h ../project/readData/parser/AbstractToken.h
        ../project/readData/parser/Token.h ../project/readData/parser/TokenContainer.h
        ../project/readData/parser/TokenReader.cpp ../project/readData/parser/TokenReader.h
        ../project/readData/parser/Parser.cpp ../project/readData/parser/Parser.h
        ../project/readData/parser/Builder.cpp ../project/readData/parser/Builder.h ../project/readData/parser/Solver.h
        ../project/readData/ReaderData.cpp ../project/readData/ReaderData.h ../project/readData/Data.h
        ../project/readData/InterpreterInputFunction.cpp
        FixtureMethod.h FixtureInterpreter.h)

target_link_libraries(Google_Tests_run ${CMAKE_DL_LIBS})
target_link_libraries(Google_Tests_run gtest gtest_main)



