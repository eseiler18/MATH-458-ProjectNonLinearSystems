include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_readData main_readData.cpp ReaderData.cpp ReaderData.h Data.h ../parser/AbstractNode.h
        ../parser/NumberNode.h ../parser/VariableNode.h ../parser/OperatorNode.h ../parser/OperatorNode.cpp
        ../parser/TokenType.h ../parser/AbstractToken.h ../parser/Token.h ../parser/TokenContainer.h
        ../parser/TokenReader.cpp ../parser/TokenReader.h ../parser/Parser.cpp
        ../parser/Parser.h ../parser/Builder.cpp ../parser/Builder.h ../parser/Solver.h)