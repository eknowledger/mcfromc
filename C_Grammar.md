## Introduction ##

This page describes the subset of the C language grammar which is handled by the algorithm. The grammar is described in Backus-Naur Form.

## Which syntactic structures are handled ? ##

Basically any structure legal in the C language <u><b>except</b></u>, mainly, the following elements:
  1. Pointers.
  1. Arrays.
  1. **goto**, **break**, **continue** and **return** commands.
  1. **switch** statement.
  1. Logical not operator (**!**).
  1. Bitwise operators ( `^`, ~, >>, <<, &, | ) and bitwise assignment operators ( <<=, >>=, ~=, &=, `^`=, |= ).
  1. Enumerators (**enum**).

In addition, the following applies:
  1. Only one function definition is allowed per translation unit (enforced by the BNF structure).
  1. All variables are considered as integers (only int variable declaration is allowed).
  1. Prefix/Postfix decrement/increment expressions (--/++) are not supported within assignment expressions or conditional expressions. This is not enforced by the BNF structure, but later on checked for validity).

## Remarks on BNF Grammar ##
The grammar used has many redundancies, as it was created only by removing unsupported syntactic constructs while not removing constructs which may be an alias of other structures. For example, since bitwise and is not supported, **and\_expression** construct is just an alias to **equality\_expression**, while before it was defined:
**and\_expression** ::= equality\_expression | and\_expression '&' equality\_expression

## The Grammar in BNF ##

**translation\_unit**
> ::= external\_declaration

**external\_declaration**
> ::= function\_definition
> | declaration

**function\_definition**
> ::= declaration\_specifiers declarator declaration\_list compound\_statement
> | declaration\_specifiers declarator compound\_statement
> | declarator declaration\_list compound\_statement
> | declarator compound\_statement

**primary\_expression**
> ::= IDENTIFIER
> | CONSTANT
> | '(' expression ')'

**postfix\_expression**
> ::= primary\_expression
> | postfix\_expression '++'
> | postfix\_expression '--'

**unary\_expression**
> ::= postfix\_expression
> | '++' unary\_expression
> | '--' unary\_expression
> | unary\_operator unary\_expression

**unary\_operator**
> ::= '+'
> | '-'

**multiplicative\_expression**
> ::= unary\_expression
> | multiplicative\_expression '`*`' unary\_expression
> | multiplicative\_expression '/' unary\_expression
> > | multiplicative\_expression '%' unary\_expression

**additive\_expression**

> ::= multiplicative\_expression
> | additive\_expression '+' multiplicative\_expression
> | additive\_expression '-' multiplicative\_expression

**shift\_expression**
> ::= additive\_expression

**relational\_expression**
> ::= shift\_expression
> | relational\_expression '<' shift\_expression
> | relational\_expression '>' shift\_expression
> | relational\_expression '<=' shift\_expression
> | relational\_expression '>=' shift\_expression

**equality\_expression**
> ::= relational\_expression
> | equality\_expression '==' relational\_expression
> | equality\_expression '!=' relational\_expression

**and\_expression**
> ::= equality\_expression

**exclusive\_or\_expression**
> ::= and\_expression

**inclusive\_or\_expression**
> ::= exclusive\_or\_expression

**logical\_and\_expression**
> ::= inclusive\_or\_expression
> | logical\_and\_expression '&&' inclusive\_or\_expression

**logical\_or\_expression**
> ::= logical\_and\_expression
> | logical\_or\_expression '||' logical\_and\_expression

**conditional\_expression**
> ::= logical\_or\_expression

**assignment\_expression**
> ::= conditional\_expression
> | unary\_expression assignment\_operator assignment\_expression

**assignment\_operator**
> ::= '='
> | '**='
> | '/='
> | '+='
> | '-='
> > | '%='**

**expression**

> ::= assignment\_expression
> | expression ',' assignment\_expression

**declaration**
> ::= declaration\_specifiers ';'
> | declaration\_specifiers init\_declarator\_list ';'

**declaration\_specifiers**
> ::= type\_specifier

**init\_declarator\_list**
> ::= init\_declarator
> | init\_declarator\_list ',' init\_declarator

**init\_declarator**
> ::= declarator
> | declarator '=' initializer

**type\_specifier**
> ::= 'int'

**declarator**
> ::= direct\_declarator

**direct\_declarator**
> ::= IDENTIFIER
> | '(' declarator ')'
> | direct\_declarator '(' parameter\_type\_list ')'
> | direct\_declarator '(' identifier\_list ')'
> | direct\_declarator '(' ')'

**parameter\_type\_list**
> ::= parameter\_list

**parameter\_list**
> ::= parameter\_declaration
> | parameter\_list ',' parameter\_declaration

**parameter\_declaration**
> ::= declaration\_specifiers declarator
> | declaration\_specifiers

**identifier\_list**
> ::= IDENTIFIER
> | identifier\_list ',' IDENTIFIER

**initializer**
> ::= assignment\_expression
> | '{' initializer\_list '}'
> | '{' initializer\_list ',' '}'

**initializer\_list**
> ::= initializer
> | initializer\_list ',' initializer

**statement**
> ::= compound\_statement
> | expression\_statement
> | selection\_statement
> | iteration\_statement

**compound\_statement**
> ::= '{' '}'
> | '{' statement\_list '}'
> | '{' declaration\_list '}'
> | '{' declaration\_list statement\_list '}'

**declaration\_list**
> ::= declaration
> | declaration\_list declaration

**statement\_list**
> ::= statement
> | statement\_list statement

**expression\_statement**
> ::= ';'
> | expression ';'

**selection\_statement**
> ::= 'if' '(' expression ')' statement
> | 'if' '(' expression ')' statement 'else' statement

**iteration\_statement**
> ::= 'while' '(' expression ')' statement
> | 'do' statement 'while' '(' expression ')' ';'
> | 'for' '(' expression\_statement expression\_statement expression ')' statement