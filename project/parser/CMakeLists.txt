include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_parser main_parser.cpp AbstractNode.h NumberNode.h VariableNode.h OperatorNode.h OperatorNode.cpp TokenType.h AbstractToken.h Token.h TokenContainer.h TokenReader.cpp TokenReader.h Parser.cpp Parser.h Builder.cpp Builder.h Solver.h)



