# MCfromC #
## A tool for converting C programs into Monotonicity Constraints systems ##
Welcome to MCfromC Wiki. This project is dedicated for the development of a tool which is able to convert programs written using a subset of the C language into a set of Monotonicity Constraints (MC) graphs.

## High Level Design Overview ##
The project consists of 4 different parts (separated into 3 DLL's and one executable):
  1. **SyntaxParserDLL.dll**
    * This module is mostly an auto generated LALR parser for the subset of the C language we are handling.
    * The parser is generated using Flex and Bison tools.
    * The parser's input is a C program file, and it's output is an Abstract Syntax Tree(AST) of the program (given that the program was of correct syntax).
    * This module is written in C.
  1. **CFGGen.dll**
    * This module concentrates all the main algorithm of the projects, and it is written in C++.
    * It includes mainly the following algorithms:
      * Syntax2CFG - Conversion of the AST into a Control Flow Graph(CFG).
      * CFGExprEvaluator - Algorithm for evaluating expressions and expression blocks.
      * Algorithm for generation of MC graphs on the edges of the CFG.
  1. **ParserDotNetBridge.dll**
    * An interop mananged C++ module for bridging the gap between the CFGGen C++ module and .NET applications using the algoritms.
  1. **CFGViewer.exe**
    * An application which enables viewing the C programs and the generated CFGs and MC graphs, side-by-side.