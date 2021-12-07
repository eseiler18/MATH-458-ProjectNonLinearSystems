include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp AbstractSolver.cpp AbstractSolver.h
        Newton.cpp Newton.h ClassicChord.cpp ClassicChord.h readData/main_readData.cpp)

add_executable(main_louis main_louis.cpp AbstractSolver.cpp AbstractSolver.h Newton.cpp Newton.h
        Bisection.cpp Bisection.h FixedPoint.cpp FixedPoint.h parser/AbstractNode.h parser/NumberNode.h
        parser/VariableNode.h parser/OperatorNode.h parser/OperatorNode.cpp
        parser/TokenType.h parser/AbstractToken.h parser/Token.h parser/TokenContainer.h parser/TokenReader.cpp
        parser/TokenReader.h parser/Parser.cpp parser/Parser.h parser/Builder.cpp parser/Builder.h parser/Solver.h
        readData/ReaderData.cpp readData/ReaderData.h readData/Data.h)


add_subdirectory(parser)
add_subdirectory(readData)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../data.csv data.csv COPYONLY)



