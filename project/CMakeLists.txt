include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(readData)
include_directories(../eigen)

add_executable(runSystem runSystem.cpp solverMethods/NewtonSystem.cpp solverMethods/NewtonSystem.h
        readData/parser/AbstractNode.h readData/parser/NumberNode.h readData/parser/VariableNode.h
        readData/parser/OperatorNode.h readData/parser/OperatorNode.cpp readData/parser/ExtrernalFunctionNode.h
        readData/parser/TokenType.h readData/parser/AbstractToken.h readData/parser/Token.h
        readData/parser/TokenContainer.h
        readData/parser/TokenReader.cpp readData/parser/TokenReader.h
        readData/parser/Parser.cpp readData/parser/Parser.h
        readData/parser/Builder.cpp readData/parser/Builder.h
        readData/ReaderData.cpp readData/ReaderData.h readData/Data.h
        solverMethods/NewtonSystem.cpp solverMethods/NewtonSystem.h
        readData/AbstractInterpreterFunction.h readData/InterpreterMathExpression.h readData/InterpreterCodeC.h
        readData/InterpreterCodeC.cpp)
target_link_libraries(runSystem ${CMAKE_DL_LIBS})

add_executable(run run.cpp solverMethods/AbstractSolver.cpp solverMethods/Newton.cpp
        solverMethods/ClassicChord.cpp solverMethods/Bisection.cpp solverMethods/FixedPoint.cpp
        solverMethods/FixedPoint.h solverMethods/ExceptionIterate.h
        readData/parser/AbstractNode.h readData/parser/NumberNode.h readData/parser/VariableNode.h
        readData/parser/OperatorNode.h readData/parser/OperatorNode.cpp readData/parser/ExtrernalFunctionNode.h
        readData/parser/TokenType.h readData/parser/AbstractToken.h readData/parser/Token.h
        readData/parser/TokenContainer.h
        readData/parser/TokenReader.cpp readData/parser/TokenReader.h
        readData/parser/Parser.cpp readData/parser/Parser.h
        readData/parser/Builder.cpp readData/parser/Builder.h
        readData/ReaderData.cpp readData/ReaderData.h readData/Data.h
        solverMethods/NewtonSystem.cpp solverMethods/NewtonSystem.h
        readData/AbstractInterpreterFunction.h readData/InterpreterMathExpression.h readData/InterpreterCodeC.h
        readData/InterpreterCodeC.cpp)
target_link_libraries(run ${CMAKE_DL_LIBS})

add_subdirectory(readData)
add_subdirectory(solverMethods)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../data.csv data.csv COPYONLY)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../functions.cpp functions.cpp COPYONLY)



