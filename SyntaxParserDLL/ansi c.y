%{
#ifdef _MSC_VER
#define alloca( x ) malloc( x )
#endif
#include "SyntaxTree.h"
#include "Logger.h"

NodeData* root_node;

/* Macro Definitions */
#define ADD_NOOP_NODE_1(p,c)					\
	{										\
		NodeData *me = createNode(NONE);		\
		appendChild(me,c);					\
		p = me;							\
	}
%}
%union {
	int value;		/* A constant or expression value */
	char index;		/* an index in the variable symbols */
	char *sVal;		/* string							*/
	NodeData* node;		/* a pointer to node in the syntax tree */
}

%token <sVal> IDENTIFIER
%token <value> CONSTANT

%token STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token <sVal> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> postfix_expression and_expression equality_expression relational_expression shift_expression exclusive_or_expression inclusive_or_expression unary_operator multiplicative_expression additive_expression logical_and_expression statement_list statement compound_statement selection_statement conditional_expression expression expression_statement assignment_expression unary_expression logical_or_expression
%type <node> primary_expression constant_expression initializer initializer_list
%type <node> iteration_statement function_definition translation_unit external_declaration parameter_type_list declaration_list parameter_declaration parameter_list type_specifier init_declarator init_declarator_list declaration declaration_specifiers specifier_qualifier_list declarator direct_declarator

%start translation_unit
%%

primary_expression
	: IDENTIFIER
	{
		NodeData* p = createNode(ID); 
		p->m_name = strdup($1);
		$$ = p;
		WRITE_TO_LOG_1(lDebug,"primary_expression got identifier: %s",$1);
	}
	| CONSTANT
	{
		NodeData* p = createNode(CONST_TYPE); 
		p->m_constVal = $1;
		$$ = p;
		WRITE_TO_LOG_1(lDebug,"primary_expression got constant: %d",$1);
	}
	| '(' expression ')'
	{
		$$ = $2;
	}
	;

postfix_expression
	: primary_expression
	{
		$$ = $1;
	}
	| postfix_expression INC_OP
	{
		NodeData* p = createNode(POST_INCREMENT_EXPR);
		appendChild(p, $1);
		$$ = p;
	}
	| postfix_expression DEC_OP
	{
		NodeData* p = createNode(POST_DECREMENT_EXPR);
		appendChild(p, $1);
		$$ = p;
	}
	;

unary_expression
	: postfix_expression
	{
		$$ = $1;
	}
	| INC_OP unary_expression 
	{
		NodeData* p = createNode(PRE_INCREMENT_UNARY_EXPR);
		appendChild(p, $2);
		$$ = p;
	}
	| DEC_OP unary_expression
	{
		NodeData* p = createNode(PRE_DECREMENT_UNARY_EXPR);
		appendChild(p, $2);
		$$ = p;
	}
	| unary_operator unary_expression
	{
		NodeData* p = createNode(PREFIX_OP_UNARY_EXPR);
		appendChild(p, $2);
		$$ = p;
	}
	;

unary_operator
	: '+'
	{
		$$ = createNode(PREFIX_PLUS);
	}
	| '-'
	{
		$$ = createNode(PREFIX_MINUS);
	}
	| '!'
	{
		$$ = createNode(PREFIX_NOT);
	}
	;

multiplicative_expression
	: unary_expression
	{
		$$ = $1;
	}
	| multiplicative_expression '*' unary_expression
	{
		NodeData* p = createNode(MULT_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	| multiplicative_expression '/' unary_expression
	{
		NodeData* p = createNode(DIV_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	| multiplicative_expression '%' unary_expression
	{
		NodeData* p = createNode(MOD_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	;

additive_expression
	: multiplicative_expression
	{
		$$ = $1;
	}
	| additive_expression '+' multiplicative_expression
	{
		NodeData* p = createNode(ADD_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	| additive_expression '-' multiplicative_expression
	{
		NodeData* p = createNode(SUB_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	;

shift_expression
	: additive_expression
	{
		$$ = $1;
	}
	;

relational_expression
	: shift_expression
	{
		$$ = $1;
	}
	| relational_expression '<' shift_expression
	{
		NodeData* p = createNode(LESS_THAN_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}				
	| relational_expression '>' shift_expression
	{
		NodeData* p = createNode(GREATER_THAN_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	| relational_expression LE_OP shift_expression
	{
		NodeData* p = createNode(LESS_EQ_THAN_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	| relational_expression GE_OP shift_expression
	{
		NodeData* p = createNode(GREATER_EQ_THAN_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;
	}
	;

equality_expression
	: relational_expression
	{
		$$ = $1;
	}
	| equality_expression EQ_OP relational_expression
	{
		NodeData* p = createNode(EQUAL_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;				
	}
	| equality_expression NE_OP relational_expression
	{
		NodeData* p = createNode(NOT_EQUAL_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;				
	}
	;

and_expression
	: equality_expression
	{
		$$ = $1;
	}
	| and_expression '&' equality_expression
	{
		NodeData* p = createNode(AND_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;				
	}
	;

exclusive_or_expression
	: and_expression
	{
		$$ = $1;
	}
	;

inclusive_or_expression
	: exclusive_or_expression
	{
		$$ = $1;
	}
	;

logical_and_expression
	: inclusive_or_expression
	{
		$$ = $1;
	}
	| logical_and_expression AND_OP inclusive_or_expression
	{
		NodeData* p = createNode(LOGICAL_AND_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;		
	}
	;

logical_or_expression
	: logical_and_expression
	{
		$$ = $1;
	}
	| logical_or_expression OR_OP logical_and_expression
	{
		NodeData* p = createNode(LOGICAL_OR_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);	
		$$ = p;	
	}
	;

conditional_expression
	: logical_or_expression
	{
		$$ = $1;
	}
	| logical_or_expression '?' expression ':' conditional_expression
	{
		NodeData* p = createNode(CONDITIONAL_EXPRESSION);
		appendChild(p, $1);
		appendChild(p, $3);
		appendChild(p, $5);
		$$ = p
	}
	;

assignment_expression
	: conditional_expression
	{
		$$ = $1;
	}
	| unary_expression assignment_operator assignment_expression
	{		
		NodeData* p = createNode(ASSIGNMENT_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);
		$$ = p;
	}
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	{
		$$ = $1;
	}
	| expression ',' assignment_expression
	{
		NodeData* p = createNode(EXPRESSION);
		appendChild(p, $1);
		appendChild(p, $3);
		$$ = p;
	}
	;

constant_expression
	: conditional_expression
	{
		$$ = $1;
	}
	;

declaration
	: declaration_specifiers ';'
	{
		$$ = $1;
	}
	| declaration_specifiers init_declarator_list ';'
	{
		NodeData* p = createNode(DECLARATION);
		appendChild(p, $1);
		appendChild(p, $2);
		$$ = p;
	}
	;

declaration_specifiers	/*Type and decleration for example Static int*/
	: type_specifier
	{
		$$ = $1;
		WRITE_TO_LOG(lDebug,"Type");
	}	

init_declarator_list
	: init_declarator
	{
		$$ = $1;
	}
	| init_declarator_list ',' init_declarator
	{
		NodeData* p = createNode(INIT_DECLARATOR_LIST);
		appendChild(p, $1);
		appendChild(p, $3);
		$$ = p;		
	}
	;

init_declarator
	: declarator
	{
		$$ = $1;
	}
	| declarator '=' initializer
	{
		NodeData* p = createNode(ASSIGNMENT_EXPR);
		appendChild(p, $1);
		appendChild(p, $3);
		$$ = p;				
	}
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("void");
		$$ = p;		
	}
	| CHAR
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("char");
		$$ = p;	
	}	
	| SHORT
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("short");
		$$ = p;	
	}	
	| INT
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("int");
		$$ = p;	
	}	
	| LONG
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("long");
		$$ = p;	
	}	
	| FLOAT
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("float");
		$$ = p;	
	}	
	| DOUBLE
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("double");
		$$ = p;	
	}	
	| SIGNED
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("signed");
		$$ = p;	
	}	
	| UNSIGNED
	{
		NodeData* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("unsigned");
		$$ = p;	
	}		
	;

specifier_qualifier_list
	: type_specifier
	{
		$$ = $1;
	}
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	{
		WRITE_TO_LOG_1(lDebug,"enumerator named:%s",$1);
	}
	| IDENTIFIER '=' constant_expression
	{
		WRITE_TO_LOG_1(lDebug,"enumerator %s = ",$1);
	}
	;

declarator
	: direct_declarator
	{
		$$ = $1;
	}
	;

direct_declarator
	: IDENTIFIER
	{
		NodeData* p = createNode(ID); 
		p->m_name = strdup($1);
		$$ = p;
		WRITE_TO_LOG_1(lDebug,"rule direct_declarator:IDENTIFIER with:%s",$1);
	}
	| '(' declarator ')'
	{
		$$ = $2;
		WRITE_TO_LOG(lDebug,"Ignored");
	}
	| direct_declarator '[' constant_expression ']'
	{
		$$ = createNode(NONE);
		/*Fixed Array */
		WRITE_TO_LOG(lDebug,"Got Fixed Array");
	}
	
	| direct_declarator '[' ']'
	{
		$$ = createNode(NONE);
		/*Variable Array */
		WRITE_TO_LOG(lDebug,"Got variable array");
	}
	/*Function Decleration with just types*/
	| direct_declarator '(' parameter_type_list ')'
	{
		/*Regular Function declaration*/
		$$ = createNode(NONE);
	}
	| direct_declarator '(' identifier_list ')'
	{
		/*Regular Function declaration*/
		$$ = createNode(NONE);
	}
	| direct_declarator '(' ')'
	{
		/*Empty Function */
		WRITE_TO_LOG(lDebug,"Got Function Declaration without parameters");
	}
	;

parameter_type_list
	: parameter_list
	{
		$$ = $1;
	}
	| parameter_list ',' ELLIPSIS
	{
		$$ = $1;
	}
	;

parameter_list
	: parameter_declaration
	{
		$$ = $1;
	}
	| parameter_list ',' parameter_declaration
	{
		NodeData* p = createNode(PARAM_LIST);
		appendChild(p,$1);
		appendChild(p,$3);
		$$ = p;
	}
	;

parameter_declaration
	: declaration_specifiers declarator
	{
		NodeData* p = createNode(PARAM_DECLARATION);
		appendChild(p,$1);
		appendChild(p,$2);
		$$ = p;	
	}
	| declaration_specifiers
	{
		$$ = $1;	
	}
	;

identifier_list
	: IDENTIFIER
	{
		WRITE_TO_LOG_1(lDebug,"id list %s",$1);
	}
	| identifier_list ',' IDENTIFIER
	{
		WRITE_TO_LOG_1(lDebug,"id list %s",$3);
	}

	;

initializer
	: assignment_expression
	{
		$$ = $1;
	}
	| '{' initializer_list '}'
	{
		$$ = $2;
	}
	| '{' initializer_list ',' '}'
	{
		$$ = $2;
	}
	;

initializer_list
	: initializer
	{
		$$ = $1;
	}
	| initializer_list ',' initializer
	{
		NodeData* p = createNode(NONE);
		appendChild(p, $1);
		appendChild(p, $3);
		$$ = p;
	}
	;

statement
	: labeled_statement
	{
		$$ = createNode(NONE);
	}
	| compound_statement
	{
		NodeData* t = createNode(STATEMENT);
		appendChild(t,$1);
		$$ = t;		
 		WRITE_TO_LOG(lDebug,"Compound statement");
	}
	| expression_statement
	  {
		NodeData* t = createNode(STATEMENT);
		appendChild(t,$1);
		$$ = t;		
 		WRITE_TO_LOG(lDebug,"Expression statement");
	  }
	| selection_statement
	  {
		NodeData* t = createNode(STATEMENT);
		appendChild(t,$1);
		$$ = t;		
		WRITE_TO_LOG(lDebug,"Selection statement");
	  }
	| iteration_statement
	{
		$$ = $1;
	}
	| jump_statement
	{
		$$ = createNode(NONE);
	}
	;

labeled_statement
	: IDENTIFIER ':' statement
	{
		WRITE_TO_LOG_1(lDebug,"Got Label %s",$1);
	}
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	{
		$$ = createNode(NOP);
		WRITE_TO_LOG(lDebug,"Empty block");
	}
	| '{' statement_list '}'
	{
		WRITE_TO_LOG(lDebug,"Block With statements only(no declarations)");
		$$ = $2;
	}
	| '{' declaration_list '}'
	{
		$$ = $2;
	}
	| '{' declaration_list statement_list '}'
	{
		NodeData* p = createNode(COMPOUND_STATEMENT);
		appendChild(p, $2);
		appendChild(p, $3);
		$$ = p;
	}
	;

declaration_list
	: declaration
	{
		$$ = $1;
	}
	| declaration_list declaration
	{
		NodeData* t = createNode(DECLARATION_LIST);
		appendChild(t,$1);
		appendChild(t,$2);
		$$ = t;		
	}
	;

statement_list
	: statement
	  {
		$$ = $1;
		WRITE_TO_LOG(lDebug,"Single Statement")
	  }
	| statement_list statement
	  {
		NodeData* t = createNode(STATEMENT_LIST);
		appendChild(t,$1);
		appendChild(t,$2);
		$$ = t;		
		WRITE_TO_LOG(lDebug,"Recursive Statement List")
	  }
	;

expression_statement
	: ';' 
	{
		$$ = createNode(NONE);
	}
	| expression ';'
	{
		$$ = $1;
	}
	;

selection_statement
	: IF '(' expression ')' statement
	{
		NodeData* p = createNode(CONDITION_IF);
		appendChild(p,$3);
		appendChild(p,$5);
		$$ = p;
		WRITE_TO_LOG(lDebug,"If withut else");
	}
	| IF '(' expression ')' statement ELSE statement
	{
		NodeData* p = createNode(CONDITION_IF_ELSE);
		appendChild(p,$3);
		appendChild(p,$5);
		appendChild(p,$7);	
		$$ = p;
		WRITE_TO_LOG(lDebug,"If else");
	}
	| SWITCH '(' expression ')' statement
	{
		$$ = createNode(NOP);
	}
	;

iteration_statement
	: WHILE '(' expression ')' statement
	{
		NodeData* p = createNode(WHILE_LOOP);
		appendChild(p, $3);
		appendChild(p, $5);
		$$ = p;
	}
	| DO statement WHILE '(' expression ')' ';'
	{
		NodeData* p = createNode(DO_WHILE_LOOP);
		appendChild(p, $2);
		appendChild(p, $5);
		$$ = p;
	}
	| FOR '(' expression_statement expression_statement ')' statement
	{
		NodeData* p = createNode(FOR_LOOP);
		appendChild(p, $3);
		appendChild(p, $4);
		appendChild(p, $6);
		$$ = p;
	}
	| FOR '(' expression_statement expression_statement expression ')' statement
	{
		NodeData* p = createNode(FOR_LOOP);
		appendChild(p, $3);
		appendChild(p, $4);
		appendChild(p, $5);
		appendChild(p, $7);
		$$ = p;
	}
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit	/* We begin here the tree */
	: external_declaration
	{
		$$ = $1;
	}
	| translation_unit external_declaration
	{
		NodeData* p = createNode(TRANSLATION_UNIT);
		appendChild(p, $1);
		appendChild(p, $2);
		$$ = p;
		root_node = p;
	}
	;

external_declaration
	: function_definition
	{
		$$ = $1;
		WRITE_TO_LOG(lDebug,"Function definition");
	}
	| declaration
	{
		$$ = $1;
		WRITE_TO_LOG(lDebug,"Declaration");
	}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	{
		printf("\n");
		$$ = $4;
		WRITE_TO_LOG(lDebug,"Got Rule: declaration_specifiers declarator declaration_list compound_statement");
	}
	| declaration_specifiers declarator compound_statement
	{
		printf("\n");
		$$ = $3;
		WRITE_TO_LOG(lDebug,"Type FuncName(Parameters) {}");
	}
	| declarator declaration_list compound_statement
	{
		printf("\n");
		$$ = $3;
		WRITE_TO_LOG(lDebug,"FuncName(Parameters) {}");
	}
	| declarator compound_statement
	{
		printf("\n");
		$$ = $2;
		WRITE_TO_LOG(lDebug,"FuncName(Parameters) {}");
	}
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;
extern int row;
int errorFlag;

yyerror(s)
char *s;
{
    errorFlag = 1;
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

int parseSyntax(char* filename, NodeData** root) {
    row = 0;
    column = 0;
    errorFlag = 0;

	InitLogger("parseLog.log",lDebug);
	freopen(filename,"r", stdin);
	WRITE_TO_LOG(lDebug,"Started");
	yyparse();
	WRITE_TO_LOG(lDebug,"End");
	TerminateLog();
	*root = root_node;
	return errorFlag;
}
