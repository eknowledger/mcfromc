# Introduction #

This page describes the algorithm used for converting the Abstract Syntax Tree(AST), as received by the Syntax Parser, into a Control Flow Graph(CFG).

# Algorithm Details #
  * _Input_: **AST** - an Abstract Syntax Tree.
  * _Output_: **CFG** - a Control Flow Graph, containing Flow Points and directed edges between them.

  1. For each handled node in the AST (mainly expressions and control flow constructs), create a Flow Point in the CFG.
  1. Merge consecutive commands Flow Points into a compound block - a block of commands which are consecutive in the program code. This block does not appear in the CFG.
  1. Merge consecutive expressions Flow Points into a single Flow Point in the CFG(representing an expression block)
  1. Recursively traverse the AST:
    1. Connect each node Flow Point to it's sub-nodes Flow Points.
    1. If current node is a loop node, connect all end-nodes Flow Points to it's Flow Point.
    1. If current node's Flow Point is part of a compound block, connect it's end points (might be the node's Flow Point itself) to the next Flow Point inside the compound block.
    1. Return current end points to the calling level.
  1. If there are consecutive expression blocks, merge them into a single block.

# Remarks #
A For loop of the following form:
```
  for ({Initialization}; {Condition}; {Increment})
  {
    {Body}
  }
```
is interpreted into the following graph:
  * Initialization --> Condition
  * Condition --> Body
  * Body --> Increment
  * Increment --> Condition