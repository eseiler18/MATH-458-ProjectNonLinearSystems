include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(readData)

add_executable(main main.cpp)
target_link_libraries(main ${CMAKE_DL_LIBS})

add_executable(main_louis main_louis.cpp solverMethods/AbstractSolver.cpp solverMethods/Newton.cpp
        solverMethods/ClassicChord.cpp solverMethods/Bisection.cpp solverMethods/FixedPoint.cpp
        solverMethods/FixedPoint.h solverMethods/ExceptionIterate.h
        readData/parser/AbstractNode.h readData/parser/NumberNode.h readData/parser/VariableNode.h
        readData/parser/OperatorNode.h readData/parser/OperatorNode.cpp readData/parser/ExtrernalFunctionNode.h
        readData/parser/TokenType.h readData/parser/AbstractToken.h readData/parser/Token.h
        readData/parser/TokenContainer.h
        readData/parser/TokenReader.cpp readData/parser/TokenReader.h
        readData/parser/Parser.cpp readData/parser/Parser.h
        readData/parser/Builder.cpp readData/parser/Builder.h
        readData/ReaderData.cpp readData/ReaderData.h readData/Data.h readData/InterpreterInputFunction.cpp
        readData/InterpreterInputFunction.h)
target_link_libraries(main_louis ${CMAKE_DL_LIBS})

add_subdirectory(readData)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../data.csv data.csv COPYONLY)



#add_executable(Google_Tests_run ggtest.cc)




