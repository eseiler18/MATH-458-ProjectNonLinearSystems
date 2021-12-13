include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_parser main_parser.cpp AbstractToken.h AbstractNode.h Builder.cpp Builder.h ExtrernalFunctionNode.h
        FunctionNode.h NumberNode.h OperatorNode.cpp OperatorNode.h Parser.cpp Parser.h ParserException.h Solver.h
        Token.h TokenContainer.h TokenFunction.h TokenReader.cpp TokenReader.h TokenType.h VariableNode.h)





