

# Details #

Below you can find the algorithm for converting the C.F.G flow points along with the Syntax Tree to A.C.F.G (Annotated Control Flow Graph, this is a C.F.G that on its edges you can find MCs)

## Assumptions ##
  * We handle expression of the following format x = ay +b (a,b constants, x and y are variables)

## Notations ##
  1. val(**f**)
> > A mapping, : **v** -> **value**, from variable names to their values, which is "attached" to flow point **f**.
  1. **current**
> > A "temporary" mapping, : **v** -> **value** between variable names to their values.
  1. **current(x)**
> > The value of **x** in the **current** map.
  1. **ex(x)**
> > Reference to all occurrences of the variable **x** in the expression **ex**.
> > i.e. **ex(x)** <-- **5** , is equivalent to replacing all occurrences of **x** in **ex** with the value **5**.
  1. **MC(e)**
> > The Monotonicity Constraints graph associated with an edge **e** of the CFG.
  1. **invariants** - tuple in the following form <x1,o,x2> where o is on of {>,>=,<,<=,=}

## Sub Functions/Procedures ##
  1. **UNIQUE\_UNDEFINED\_VALUE**()
> > A function returning a uniquely identified undefined value. Each call to it returns a new never used before identifier which can be recognized as "Undefined". an "Undefined" value for a variable means that the variable has a value, but the value is either not-known or can't be deterministically computed. This can happen, for example, when variables are used without being initialized.
  1. **EVALUATE(ex, val)**
> > A function which evaluates an expression **ex** and returns an expression which can be either:
      1. A constant value.
      1. An undefined uniquely identified value.
      1. A simplified expression containing constant values and/or undefined values at it's leafs. The **val** parameter is a mapping **v** -> **value**, between variable names and their expressions.
> > The function does the following:
    * **EVALUATE(ex, val)**
      1. For each variable **x** in **ex**:
        1. if **val** does not contain a value for **x** Then: **val**(**x**) <-- **UNIQUE\_UNDEFINED\_VALUE**()
        1. **ex**(**x**) <-- **val**(**x**)
      1. **ex2** <-- Simplify and evaluate **ex**
      1. Return **ex2**
      1. END
  1. **MERGE(target, source)**
> > The **target** and **source** parameters are mappings **v -> value**, like **current**. The MERGE function merges **source** into **target**. The procedure does the following:
    * **MERGE(target, source)**
      1. If **target** is empty copy source to target and return.
      1. For each variable **x** which has a value in **source**, Do:
        1. If **target** value for **x** and **target**(**x**) is not identical to **source**(**x**)
          1. **target**(**x**) <-- **UNIQUE\_UNDEFINED\_VALUE**()
      1. END
  1. **COMPUTE\_MC\_GRAPH(e,inValues,outValues)**
> > The **e** is the edge to compute its MC that is attached to the edge,**inValues** and **outValues** are mapping **v** -> **value**, between variable names and their expressions.
    1. For each **xOut** in outValue
      1. For each **yIn** in inValue
        1. diff <- EVALUATE((xOut - yIn),outValue)
        1. if diff is not constant value then continue to next iteration.
        1. if diff > 0 add strict edge xOut -> yIn to MC(e)
        1. if diff < 0 add strict edge yIn -> xOut to MC(e)
        1. if diff = 0 add non stricts edges xOut->yIn and yIn -> xOut to MC(e)

  1. **COMPUTE-LOGICAL-CLOSURE(f,g,mc)** - **f** and **g** are source and target flowpoints, **mc** is the MC that is attached to the edge **f->g**
    1. add arcs that represents f's invariants.
    1. add arcc that represents g's invariants.
    1. for each edge on the mc put weight
      1. if the edge is strict than wight is -1 otherwise 0.
    1. if mc contains negative cycle return error.
    1. for each u,v in mc's vertices do
      1. compute short path between u,v if there is no path continue to next pair.
      1. if the path is negative then add strict arc between u->v to mc
      1. else add non strict arc u->v to mc

## Algorithm ##
  1. emptyMC <- empty MC with all the constants and known variables
  1. For each flow point **f** in the CFG:
    1. val(**f**) <-- {}  (initialize to empty map)
  1. changed <- false.
  1. While edge MC was changed, Do:
    1. chnaged <- false
    1. Perform D.F.S and for each discovered edge **e**:
      1. **start vertex(f)** - if this is the first run of D.F.S initialize all variables of **val(f)** to be undefined values.
      1. **examine edge(e)** -
        1. **f** <-- source(**e**)
        1. **g** <-- target(**e**)
        1. **current** <-- val(**f**)
        1. newMC <- emptyMC
        1. If **f** is an expression block Then:
          1. For each expression **ex**, which changes variable **y**, in the expression block of **f** Do:
            1. For each variable **x** in **ex**:
              1. If **current** does not contain **x** Then: **current(x)** <-- **UNIQUE\_UNDEFINED\_VALUE**()
              1. **ex(x)** <-- **current(x)**
            1. **current(y)** <-- **EVALUATE(ex, current)**
        1. else (this is a branch flowpoint)
          1. logicalExpTree <-- logic(f)
          1. if complement edge (logical expression is false)
            1. logicalExpTree <-- compute complement for the logic tree.
          1. invariants <-- convert tree logical tree to invariants(logicalExpTree)
          1. for each invariant in INVARIANTS(f)
            1. add edge to MC(e)
        1. newMC <- **COMPUTE\_MC\_GRAPH**(**e**,**val(f)**,**current**)
        1. if newMC != MC(e)
          1. MC(e) <- newMC
          1. changed <- true.
        1. **MERGE**(val(**g**), **current**)
  1. For each edge in  CFG do
    1. COMPUTE-LOGICAL-CLOSURE(source(e),target(e),MC(e))
  1. END

## Remarks on Algorithm ##
  1. DFS **Forward**, **Cross**, **Back** and **Tree** edges are defined as in the following image:
> > ![http://upload.wikimedia.org/wikipedia/en/thumb/5/57/Tree_edges.svg/412px-Tree_edges.svg.png](http://upload.wikimedia.org/wikipedia/en/thumb/5/57/Tree_edges.svg/412px-Tree_edges.svg.png)
  1. The line "While there exists a Flow Point **h** s.t. tag(**h**) = **dirty** , Do:" can be implemented by doing exactly 2 runs of the DFS.

## Ideas ##

  1. We check that the in degree of the target flow point is equal to 1 since we cannot know what is the new value for example the following program:
```
      x = y;
      if ()
          x = 100;
      else 
          x = 5;
      z = 3*x - 100;
```
> > then if we got from the if block (x = 100) we know that z > x but if we got from else
> > block then z < x.
  1. If the value of some variable (y) is unknown then assign the recent equation of (y) and simplify the equation. Then, assign the equation to x.
  1. We need to think what to do about back edges. For example, in the following program:
```
     y = 5
     x = 5;
     while (x > 0)
         x--;
     y = x+1;
```
> > If we would not consider the back-edge from '**x--**' FP to the '**while**' FP, it would seem that the value of y has grown after the command '**y = x+5**', where in fact its value is smaller. Since there is a back edge which changes the value of '**x**', the value of '**x**' must be "reset" to "**Undefined**". Since the DFS/BFS edges order is not predetermined we can't guarantee that the loop edge will be examined before the edge going "out" of the loop (from the '**while**' FP to the '**y = x+1**' command FP).