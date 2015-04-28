

# Which expressions are handled ? #
Handled expressions include:
  1. Consecutive command blocks containing commands of the following types:
    1. Assignment commands.
    1. Simple pre/post increment/decrement commands.

  1. Branch conditions(while/for/if):
    1. Order conditions (e.g x < y, y >= z)
    1. Logical conjunction of order conditions (x < y && y >= z && z >= x).

# Assignment Commands Expressions #
Each expression is broken down to a binary tree containing Atom Expressions (AtomExpr) in its leafs and Binary Operator Expressions (BinExpr) in its non-leaf nodes. For example, the following expression:
```
3*x+5*y-7
```

Is interpreted into the following expression:
```
BinExpr(ADD)
  |
  |--BinExpr(MUL)
  |    |
  |    |--AtomExpr(3)
  |    |--AtomExpr(x)
  |
  |--BinExpr(SUB)
       |
       |--BinExpr(MUL)
       |    |
       |    |--AtomExpr(5)
       |    |--AtomExpr(y)
       |
       |--AtomExpr(7)
```
# Expression Evaluation #
  * When expression is evaluated, each variable is substituted with it's value:
    1. If all variable values are known(and numeric), then the expression is evaluated to the computation result.
    1. If some variable's value is Undefined, then an Undefined value will substitute the the variable within the expression. This undefined value is unique and is distinguishable from other undefined values. This enables performing the following analysis. In the following example, assume that the variable 'y' is undefined (has unknown value):
```
   x = y;
   x = x + 5; 
```
Since 'y' is undefined, it has an undefined value of U1.
In the first assignment command, x will assume the undefined value U1 ( AtomExpr(U1) ).
In the second assignment command, x will assume the expression U1+5 :
```
   BinExpr(ADD)
     |
     |--AtomExpr(U1)
     |--AtomExpr(5)
```

  * When substituting a variable with a composite expression (not an AtomExpr), it is possible in some cases to reduce the expression into a simpler form which might be easier to check for size change. This simplification is done using the ExprSimplifier class, which tries to match the expression into a pattern of a predefined set of expression patterns. If such a pattern is found, then the expression is simplified according to the rules defined in ExprSimplifier for the found pattern.
  * We can deduce the relation (<= <, =, >=, >) between two simple BinExpr with only 2 atom expressions below. In this case, since (U1+5) - U1 = 5, we can deduce that x's value increased by 5 during the second assignment command.
  * The order between 2 expressions is determined by subtracting one expression from the other and then trying to evaluate(and simplify) the result expression.

# Limitations #
  * Handled order conditions must contain variables or constants only.
  * Assignment or Conditional expressions with side effects (e.g pre/post increment/decrement within the expression) are not handled - a parsing error is issued if such expressions appear in code.