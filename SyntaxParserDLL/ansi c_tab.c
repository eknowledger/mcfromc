
/*  A Bison parser, made from c:\mcfromc\syntaxparserdll\ansi c.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	IDENTIFIER	258
#define	CONSTANT	259
#define	STRING_LITERAL	260
#define	SIZEOF	261
#define	PTR_OP	262
#define	INC_OP	263
#define	DEC_OP	264
#define	LEFT_OP	265
#define	RIGHT_OP	266
#define	LE_OP	267
#define	GE_OP	268
#define	EQ_OP	269
#define	NE_OP	270
#define	AND_OP	271
#define	OR_OP	272
#define	MUL_ASSIGN	273
#define	DIV_ASSIGN	274
#define	MOD_ASSIGN	275
#define	ADD_ASSIGN	276
#define	SUB_ASSIGN	277
#define	LEFT_ASSIGN	278
#define	RIGHT_ASSIGN	279
#define	AND_ASSIGN	280
#define	XOR_ASSIGN	281
#define	OR_ASSIGN	282
#define	TYPE_NAME	283
#define	TYPEDEF	284
#define	EXTERN	285
#define	STATIC	286
#define	AUTO	287
#define	REGISTER	288
#define	CHAR	289
#define	SHORT	290
#define	INT	291
#define	LONG	292
#define	SIGNED	293
#define	UNSIGNED	294
#define	FLOAT	295
#define	DOUBLE	296
#define	CONST	297
#define	VOLATILE	298
#define	VOID	299
#define	STRUCT	300
#define	UNION	301
#define	ENUM	302
#define	ELLIPSIS	303
#define	CASE	304
#define	DEFAULT	305
#define	IF	306
#define	ELSE	307
#define	SWITCH	308
#define	WHILE	309
#define	DO	310
#define	FOR	311
#define	GOTO	312
#define	CONTINUE	313
#define	BREAK	314
#define	RETURN	315

#line 1 "c:\mcfromc\syntaxparserdll\ansi c.y"

#ifdef _MSC_VER
#define alloca( x ) malloc( x )
#endif
#include "SyntaxTree.h"
#include "Logger.h"
#include <conio.h>

Node* root_node;

/* Macro Definitions */
#define ADD_NOOP_NODE_1(p,c)					\
	{										\
		Node *me = createNode(NONE);		\
		appendChild(me,c);					\
		p = me;							\
	}

#line 19 "c:\mcfromc\syntaxparserdll\ansi c.y"
typedef union {
	int value;		/* A constant or expression value */
	char index;		/* an index in the variable symbols */
	char *sVal;		/* string							*/
	Node* node;		/* a pointer to node in the syntax tree */
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		224
#define	YYFLAG		-32768
#define	YYNTBASE	81

#define YYTRANSLATE(x) ((unsigned)(x) <= 315 ? yytranslate[x] : 125)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    65,     2,     2,     2,    68,    71,     2,    61,
    62,    66,    63,    75,    64,     2,    67,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    73,    76,    69,
    74,    70,    72,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    79,     2,    80,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    77,     2,    78,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     8,    10,    13,    16,    18,    21,    24,
    27,    29,    31,    33,    35,    39,    43,    47,    49,    53,
    57,    59,    61,    65,    69,    73,    77,    79,    83,    87,
    89,    93,    95,    97,    99,   103,   105,   109,   111,   117,
   119,   123,   125,   127,   129,   131,   133,   135,   137,   139,
   141,   143,   145,   147,   151,   153,   156,   160,   162,   164,
   168,   170,   174,   176,   178,   180,   182,   184,   186,   188,
   190,   192,   194,   196,   198,   200,   202,   204,   209,   215,
   218,   220,   224,   226,   230,   232,   234,   238,   243,   247,
   252,   257,   261,   263,   267,   269,   273,   276,   278,   280,
   284,   286,   290,   295,   297,   301,   303,   305,   307,   309,
   311,   313,   317,   322,   326,   329,   333,   337,   342,   344,
   347,   349,   352,   354,   357,   363,   371,   377,   383,   391,
   398,   406,   410,   413,   416,   419,   423,   425,   428,   430,
   432,   437,   441,   445
};

static const short yyrhs[] = {     3,
     0,     4,     0,    61,    98,    62,     0,    81,     0,    82,
     8,     0,    82,     9,     0,    82,     0,     8,    83,     0,
     9,    83,     0,    84,    83,     0,    63,     0,    64,     0,
    65,     0,    83,     0,    85,    66,    83,     0,    85,    67,
    83,     0,    85,    68,    83,     0,    85,     0,    86,    63,
    85,     0,    86,    64,    85,     0,    86,     0,    87,     0,
    88,    69,    87,     0,    88,    70,    87,     0,    88,    12,
    87,     0,    88,    13,    87,     0,    88,     0,    89,    14,
    88,     0,    89,    15,    88,     0,    89,     0,    90,    71,
    89,     0,    90,     0,    91,     0,    92,     0,    93,    16,
    92,     0,    93,     0,    94,    17,    93,     0,    94,     0,
    94,    72,    98,    73,    95,     0,    95,     0,    83,    97,
    96,     0,    74,     0,    18,     0,    19,     0,    20,     0,
    21,     0,    22,     0,    23,     0,    24,     0,    25,     0,
    26,     0,    27,     0,    96,     0,    98,    75,    96,     0,
    95,     0,   101,    76,     0,   101,   102,    76,     0,   104,
     0,   103,     0,   102,    75,   103,     0,   105,     0,   105,
    74,   111,     0,    29,     0,    30,     0,    31,     0,    32,
     0,    33,     0,    44,     0,    34,     0,    35,     0,    36,
     0,    37,     0,    40,     0,    41,     0,    38,     0,    39,
     0,   104,     0,    47,    77,     0,    78,     0,    47,     3,
    77,     0,    78,     0,    47,     3,     0,     0,     0,     0,
    75,     0,     0,     3,     0,     3,    74,    99,     0,   106,
     0,     3,     0,    61,   105,    62,     0,   106,    79,    99,
    80,     0,   106,    79,    80,     0,   106,    61,   107,    62,
     0,   106,    61,   110,    62,     0,   106,    61,    62,     0,
   108,     0,   108,    75,    48,     0,   109,     0,   108,    75,
   109,     0,   101,   105,     0,   101,     0,     3,     0,   110,
    75,     3,     0,    96,     0,    77,   112,    78,     0,    77,
   112,    75,    78,     0,   111,     0,   112,    75,   111,     0,
   114,     0,   115,     0,   118,     0,   119,     0,   120,     0,
   121,     0,     3,    73,   113,     0,    49,    99,    73,   113,
     0,    50,    73,   113,     0,    77,    78,     0,    77,   117,
    78,     0,    77,   116,    78,     0,    77,   116,   117,    78,
     0,   100,     0,   116,   100,     0,   113,     0,   117,   113,
     0,    76,     0,    98,    76,     0,    51,    61,    98,    62,
   113,     0,    51,    61,    98,    62,   113,    52,   113,     0,
    53,    61,    98,    62,   113,     0,    54,    61,    98,    62,
   113,     0,    55,   113,    54,    61,    98,    62,    76,     0,
    56,    61,   118,   118,    62,   113,     0,    56,    61,   118,
   118,    98,    62,   113,     0,    57,     3,    76,     0,    58,
    76,     0,    59,    76,     0,    60,    76,     0,    60,    98,
    76,     0,   123,     0,   122,   123,     0,   124,     0,   100,
     0,   101,   105,   116,   115,     0,   101,   105,   115,     0,
   105,   116,   115,     0,   105,   115,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    49,    56,    63,    70,    74,    80,    89,    93,    99,   105,
   114,   118,   122,   129,   133,   140,   147,   157,   161,   168,
   178,   185,   189,   196,   203,   210,   220,   224,   231,   241,
   245,   255,   262,   269,   273,   283,   287,   297,   301,   312,
   316,   326,   327,   328,   329,   330,   331,   332,   333,   334,
   335,   336,   340,   344,   354,   361,   365,   375,   382,   386,
   396,   400,   410,   411,   412,   413,   414,   418,   424,   430,
   436,   442,   448,   454,   460,   466,   475,   482,   483,   484,
   488,   489,   493,   497,   504,   511,   518,   523,   530,   537,
   542,   547,   555,   559,   566,   570,   580,   587,   594,   598,
   606,   610,   614,   621,   625,   635,   639,   646,   653,   660,
   664,   671,   675,   676,   680,   685,   690,   694,   704,   708,
   718,   723,   734,   738,   745,   753,   762,   769,   776,   783,
   791,   803,   804,   805,   806,   807,   811,   815,   827,   832,
   840,   846,   852,   858
};

static const char * const yytname[] = {   "$","error","$undefined.","IDENTIFIER",
"CONSTANT","STRING_LITERAL","SIZEOF","PTR_OP","INC_OP","DEC_OP","LEFT_OP","RIGHT_OP",
"LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP","OR_OP","MUL_ASSIGN","DIV_ASSIGN","MOD_ASSIGN",
"ADD_ASSIGN","SUB_ASSIGN","LEFT_ASSIGN","RIGHT_ASSIGN","AND_ASSIGN","XOR_ASSIGN",
"OR_ASSIGN","TYPE_NAME","TYPEDEF","EXTERN","STATIC","AUTO","REGISTER","CHAR",
"SHORT","INT","LONG","SIGNED","UNSIGNED","FLOAT","DOUBLE","CONST","VOLATILE",
"VOID","STRUCT","UNION","ENUM","ELLIPSIS","CASE","DEFAULT","IF","ELSE","SWITCH",
"WHILE","DO","FOR","GOTO","CONTINUE","BREAK","RETURN","'('","')'","'+'","'-'",
"'!'","'*'","'/'","'%'","'<'","'>'","'&'","'?'","':'","'='","','","';'","'{'",
"'}'","'['","']'","primary_expression","postfix_expression","unary_expression",
"unary_operator","multiplicative_expression","additive_expression","shift_expression",
"relational_expression","equality_expression","and_expression","exclusive_or_expression",
"inclusive_or_expression","logical_and_expression","logical_or_expression","conditional_expression",
"assignment_expression","assignment_operator","expression","constant_expression",
"declaration","declaration_specifiers","init_declarator_list","init_declarator",
"type_specifier","declarator","direct_declarator","parameter_type_list","parameter_list",
"parameter_declaration","identifier_list","initializer","initializer_list","statement",
"labeled_statement","compound_statement","declaration_list","statement_list",
"expression_statement","selection_statement","iteration_statement","jump_statement",
"translation_unit","external_declaration","function_definition","iteration_statement"
};
#endif

static const short yyr1[] = {     0,
    81,    81,    81,    82,    82,    82,    83,    83,    83,    83,
    84,    84,    84,    85,    85,    85,    85,    86,    86,    86,
    87,    88,    88,    88,    88,    88,    89,    89,    89,    90,
    90,    91,    92,    93,    93,    94,    94,    95,    95,    96,
    96,    97,    97,    97,    97,    97,    97,    97,    97,    97,
    97,    97,    98,    98,    99,   100,   100,   101,   102,   102,
   103,   103,    -1,    -1,    -1,    -1,    -1,   104,   104,   104,
   104,   104,   104,   104,   104,   104,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   105,   106,   106,   106,   106,   106,
   106,   106,   107,   107,   108,   108,   109,   109,   110,   110,
   111,   111,   111,   112,   112,   113,   113,   113,   113,   113,
   113,   114,   114,   114,   115,   115,   115,   115,   116,   116,
   117,   117,   118,   118,   119,   119,   119,   120,   120,   120,
   120,   121,   121,   121,   121,   121,   122,   122,   123,   123,
   124,   124,   124,   124
};

static const short yyr2[] = {     0,
     1,     1,     3,     1,     2,     2,     1,     2,     2,     2,
     1,     1,     1,     1,     3,     3,     3,     1,     3,     3,
     1,     1,     3,     3,     3,     3,     1,     3,     3,     1,
     3,     1,     1,     1,     3,     1,     3,     1,     5,     1,
     3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     3,     1,     2,     3,     1,     1,     3,
     1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     4,     5,     2,
     1,     3,     1,     3,     1,     1,     3,     4,     3,     4,
     4,     3,     1,     3,     1,     3,     2,     1,     1,     3,
     1,     3,     4,     1,     3,     1,     1,     1,     1,     1,
     1,     3,     4,     3,     2,     3,     3,     4,     1,     2,
     1,     2,     1,     2,     5,     7,     5,     5,     7,     6,
     7,     3,     2,     2,     2,     3,     1,     2,     1,     1,
     4,     3,     3,     2
};

static const short yydefact[] = {     0,
    86,    69,    70,    71,    72,    75,    76,    73,    74,    68,
     0,   140,     0,    58,     0,    85,     0,   137,   139,     0,
    56,     0,    59,    61,     0,   119,     0,   144,     0,     0,
     0,   138,    87,     0,    57,     0,   142,     0,     1,     2,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    11,    12,    13,   123,   115,     4,
     7,    14,     0,    18,    21,    22,    27,    30,    32,    33,
    34,    36,    38,    40,    53,     0,   121,   106,   107,     0,
     0,   108,   109,   110,   111,    61,   120,   143,    99,    92,
    98,     0,    93,    95,     0,     1,    89,    14,    55,     0,
    60,     0,   101,    62,   141,     0,     8,     9,     0,     0,
     0,     0,     0,     0,     0,     0,   133,   134,   135,     0,
     0,     5,     6,    43,    44,    45,    46,    47,    48,    49,
    50,    51,    52,    42,     0,    10,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   124,   117,     0,   116,   122,    97,    90,     0,
    91,     0,    88,   104,     0,   112,     0,   114,     0,     0,
     0,     0,     0,   132,   136,     3,    41,    15,    16,    17,
    19,    20,    25,    26,    23,    24,    28,    29,    31,    35,
    37,     0,    54,   118,    94,    96,   100,     0,   102,   113,
     0,     0,     0,     0,     0,     0,   103,   105,   125,   127,
   128,     0,     0,     0,    39,     0,     0,   130,     0,   126,
   129,   131,     0,     0
};

static const short yydefgoto[] = {    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    73,    74,    75,   135,    76,   100,    26,    27,
    22,    23,    14,    15,    16,    92,    93,    94,    95,   104,
   165,    77,    78,    79,    29,    81,    82,    83,    84,    85,
    17,    18,    19
};

static const short yypact[] = {   376,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     6,-32768,    20,-32768,   200,   -42,    18,-32768,-32768,   -46,
-32768,   -15,-32768,   405,   152,-32768,    20,-32768,   200,   362,
    65,-32768,-32768,     6,-32768,    85,-32768,   200,   -49,-32768,
    36,    36,    36,    -2,   -19,    14,    19,   317,    41,    43,
    46,    51,   223,    36,-32768,-32768,-32768,-32768,-32768,-32768,
    82,   407,    36,   131,   101,-32768,    17,   110,    88,-32768,
-32768,   116,    -9,-32768,-32768,    67,-32768,-32768,-32768,   215,
   254,-32768,-32768,-32768,-32768,   100,-32768,-32768,-32768,-32768,
     6,   138,   129,-32768,   -27,-32768,-32768,-32768,-32768,   134,
-32768,    85,-32768,-32768,-32768,   317,-32768,-32768,   147,   317,
    36,    36,    36,   167,   293,   146,-32768,-32768,-32768,   102,
    30,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    36,-32768,    36,    36,    36,    36,
    36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
    36,    36,-32768,-32768,   286,-32768,-32768,-32768,-32768,   416,
-32768,   222,-32768,-32768,   -50,-32768,   317,-32768,    61,    69,
    72,   172,   293,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   131,   131,-32768,-32768,-32768,-32768,    17,    17,   110,-32768,
   116,   -24,-32768,-32768,-32768,-32768,-32768,    74,-32768,-32768,
   317,   317,   317,    36,   325,    36,-32768,-32768,   190,-32768,
-32768,    78,   317,    79,-32768,   317,   169,-32768,   317,-32768,
-32768,-32768,   243,-32768
};

static const short yypgoto[] = {-32768,
-32768,   -31,-32768,    40,-32768,    28,    37,    98,-32768,-32768,
    99,    97,-32768,   -30,   -32,-32768,   -47,   217,     5,     3,
-32768,   227,-32768,     4,-32768,-32768,-32768,   107,-32768,  -100,
-32768,   -34,-32768,    12,   170,   201,   -89,-32768,-32768,-32768,
-32768,   265,-32768
};


#define	YYLAST		482


static const short yytable[] = {    98,
    99,   164,    13,   103,    12,   120,   121,   150,     1,   107,
   108,    98,    99,   114,    20,    33,    24,   223,    30,    13,
     1,    12,     1,   106,   198,   173,    28,   199,   142,   143,
    86,   136,    91,    87,   161,    37,    31,    86,    96,    40,
    88,   111,    87,    41,    42,   116,   157,   162,   206,   105,
   152,     2,     3,     4,     5,     6,     7,     8,     9,    34,
    35,    10,   151,   169,   170,   171,    11,    96,    40,   103,
   110,   166,    41,    42,   112,   168,    96,    40,    11,   113,
    11,    41,    42,   205,    87,   144,   145,    96,    40,   122,
   123,   176,    41,    42,   158,    21,    54,   208,    55,    56,
    57,   115,   177,   192,   152,   178,   179,   180,    98,    98,
    98,    98,    98,    98,    98,    98,    98,    98,    98,   193,
   157,   117,   201,   146,   147,    54,   118,    55,    56,    57,
   202,   149,   200,   203,    54,   152,    55,    56,    57,   217,
   219,   152,   153,   152,    97,    54,   152,    55,    56,    57,
   102,   207,   152,   152,    39,    40,   212,   214,   148,    41,
    42,   102,    91,   140,   141,   103,   209,   210,   211,   183,
   184,   185,   186,    36,    98,   215,   152,   175,   218,   181,
   182,   220,   187,   188,   222,     2,     3,     4,     5,     6,
     7,     8,     9,    38,    80,    10,   137,   138,   139,   159,
    43,    44,    45,   160,    46,    47,    48,    49,    50,    51,
    52,    53,    54,   163,    55,    56,    57,    39,    40,   167,
   172,   174,    41,    42,   197,    96,    40,    58,    25,    59,
    41,    42,   204,     2,     3,     4,     5,     6,     7,     8,
     9,   216,   224,    10,   221,   189,   191,   190,     2,     3,
     4,     5,     6,     7,     8,     9,    39,    40,    10,   109,
   101,    41,    42,    43,    44,    45,   196,    46,    47,    48,
    49,    50,    51,    52,    53,    54,    25,    55,    56,    57,
   155,    32,     0,    54,     0,    55,    56,    57,    39,    40,
    58,    25,   154,    41,    42,    96,    40,     0,   119,     0,
    41,    42,    43,    44,    45,     0,    46,    47,    48,    49,
    50,    51,    52,    53,    54,     0,    55,    56,    57,    39,
    40,     0,     0,     0,    41,    42,     0,    96,    40,    58,
    25,   156,    41,    42,    43,    44,    45,     0,    46,    47,
    48,    49,    50,    51,    52,    53,    54,     0,    55,    56,
    57,     0,     0,    54,     0,    55,    56,    57,     0,     0,
     0,    58,    25,   194,    89,    43,    44,    45,    58,    46,
    47,    48,    49,    50,    51,    52,    53,    54,     1,    55,
    56,    57,     0,     0,     0,    54,   213,    55,    56,    57,
     0,     0,    58,    25,     0,     2,     3,     4,     5,     6,
     7,     8,     9,     0,     0,    10,     0,     0,     0,     2,
     3,     4,     5,     6,     7,     8,     9,     0,     0,    10,
     0,     0,     0,    90,   124,   125,   126,   127,   128,   129,
   130,   131,   132,   133,     0,     0,    11,     0,     2,     3,
     4,     5,     6,     7,     8,     9,     0,     0,    10,     2,
     3,     4,     5,     6,     7,     8,     9,     0,     0,    10,
     0,     0,     0,   195,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
   134,    25
};

static const short yycheck[] = {    31,
    31,   102,     0,    36,     0,    53,    54,    17,     3,    41,
    42,    43,    43,    48,    11,    62,    13,     0,    61,    17,
     3,    17,     3,    73,    75,   115,    15,    78,    12,    13,
    27,    63,    30,    29,    62,    24,    79,    34,     3,     4,
    29,    61,    38,     8,     9,     3,    81,    75,    73,    38,
    75,    34,    35,    36,    37,    38,    39,    40,    41,    75,
    76,    44,    72,   111,   112,   113,    61,     3,     4,   102,
    73,   106,     8,     9,    61,   110,     3,     4,    61,    61,
    61,     8,     9,   173,    80,    69,    70,     3,     4,     8,
     9,    62,     8,     9,    91,    76,    61,   198,    63,    64,
    65,    61,   135,   151,    75,   137,   138,   139,   140,   141,
   142,   143,   144,   145,   146,   147,   148,   149,   150,   152,
   155,    76,    62,    14,    15,    61,    76,    63,    64,    65,
    62,    16,   167,    62,    61,    75,    63,    64,    65,    62,
    62,    75,    76,    75,    80,    61,    75,    63,    64,    65,
    77,    78,    75,    75,     3,     4,   204,   205,    71,     8,
     9,    77,   160,    63,    64,   198,   201,   202,   203,   142,
   143,   144,   145,    74,   206,   206,    75,    76,   213,   140,
   141,   216,   146,   147,   219,    34,    35,    36,    37,    38,
    39,    40,    41,    24,    25,    44,    66,    67,    68,    62,
    49,    50,    51,    75,    53,    54,    55,    56,    57,    58,
    59,    60,    61,    80,    63,    64,    65,     3,     4,    73,
    54,    76,     8,     9,     3,     3,     4,    76,    77,    78,
     8,     9,    61,    34,    35,    36,    37,    38,    39,    40,
    41,    52,     0,    44,    76,   148,   150,   149,    34,    35,
    36,    37,    38,    39,    40,    41,     3,     4,    44,    43,
    34,     8,     9,    49,    50,    51,   160,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    77,    63,    64,    65,
    80,    17,    -1,    61,    -1,    63,    64,    65,     3,     4,
    76,    77,    78,     8,     9,     3,     4,    -1,    76,    -1,
     8,     9,    49,    50,    51,    -1,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    -1,    63,    64,    65,     3,
     4,    -1,    -1,    -1,     8,     9,    -1,     3,     4,    76,
    77,    78,     8,     9,    49,    50,    51,    -1,    53,    54,
    55,    56,    57,    58,    59,    60,    61,    -1,    63,    64,
    65,    -1,    -1,    61,    -1,    63,    64,    65,    -1,    -1,
    -1,    76,    77,    78,     3,    49,    50,    51,    76,    53,
    54,    55,    56,    57,    58,    59,    60,    61,     3,    63,
    64,    65,    -1,    -1,    -1,    61,    62,    63,    64,    65,
    -1,    -1,    76,    77,    -1,    34,    35,    36,    37,    38,
    39,    40,    41,    -1,    -1,    44,    -1,    -1,    -1,    34,
    35,    36,    37,    38,    39,    40,    41,    -1,    -1,    44,
    -1,    -1,    -1,    62,    18,    19,    20,    21,    22,    23,
    24,    25,    26,    27,    -1,    -1,    61,    -1,    34,    35,
    36,    37,    38,    39,    40,    41,    -1,    -1,    44,    34,
    35,    36,    37,    38,    39,    40,    41,    -1,    -1,    44,
    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
    74,    77
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 50 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(ID); 
		p->m_name = strdup(yyvsp[0].sVal);
		yyval.node = p;
		WRITE_TO_LOG_1(lDebug,"primary_expression got identifier: %s",yyvsp[0].sVal);
	;
    break;}
case 2:
#line 57 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(CONST_TYPE); 
		p->m_constVal = yyvsp[0].value;
		yyval.node = p;
		WRITE_TO_LOG_1(lDebug,"primary_expression got constant: %d",yyvsp[0].value);
	;
    break;}
case 3:
#line 64 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-1].node;
	;
    break;}
case 4:
#line 71 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 5:
#line 75 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(POST_INCREMENT_EXPR);
		appendChild(p, yyvsp[-1].node);
		yyval.node = p;
	;
    break;}
case 6:
#line 81 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(POST_DECREMENT_EXPR);
		appendChild(p, yyvsp[-1].node);
		yyval.node = p;
	;
    break;}
case 7:
#line 90 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 8:
#line 94 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(PRE_INCREMENT_UNARY_EXPR);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 9:
#line 100 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(PRE_DECREMENT_UNARY_EXPR);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 10:
#line 106 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(PREFIX_OP_UNARY_EXPR);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 11:
#line 115 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(PREFIX_PLUS);
	;
    break;}
case 12:
#line 119 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(PREFIX_MINUS);
	;
    break;}
case 13:
#line 123 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(PREFIX_NOT);
	;
    break;}
case 14:
#line 130 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 15:
#line 134 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(MULT_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 16:
#line 141 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(DIV_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 17:
#line 148 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(MOD_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 18:
#line 158 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 19:
#line 162 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(ADD_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 20:
#line 169 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(SUB_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 21:
#line 179 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 22:
#line 186 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 23:
#line 190 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(LESS_THAN_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 24:
#line 197 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(GREATER_THAN_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 25:
#line 204 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(LESS_EQ_THAN_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 26:
#line 211 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(GREATER_EQ_THAN_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;
	;
    break;}
case 27:
#line 221 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 28:
#line 225 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(EQUAL_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;				
	;
    break;}
case 29:
#line 232 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(NOT_EQUAL_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;				
	;
    break;}
case 30:
#line 242 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 31:
#line 246 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(AND_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;				
	;
    break;}
case 32:
#line 256 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 33:
#line 263 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 34:
#line 270 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 35:
#line 274 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(LOGICAL_AND_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;		
	;
    break;}
case 36:
#line 284 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 37:
#line 288 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(LOGICAL_OR_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);	
		yyval.node = p;	
	;
    break;}
case 38:
#line 298 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 39:
#line 302 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(CONDITIONAL_EXPRESSION);
		appendChild(p, yyvsp[-4].node);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p
	;
    break;}
case 40:
#line 313 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 41:
#line 317 "c:\mcfromc\syntaxparserdll\ansi c.y"
{		
		Node* p = createNode(ASSIGNMENT_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 53:
#line 341 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 54:
#line 345 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(EXPRESSION);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 55:
#line 355 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 56:
#line 362 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-1].node;
	;
    break;}
case 57:
#line 366 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(DECLARATION);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[-1].node);
		yyval.node = p;
	;
    break;}
case 58:
#line 376 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"Type");
	;
    break;}
case 59:
#line 383 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 60:
#line 387 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(INIT_DECLARATOR_LIST);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;		
	;
    break;}
case 61:
#line 397 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 62:
#line 401 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(ASSIGNMENT_EXPR);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;				
	;
    break;}
case 68:
#line 419 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("void");
		yyval.node = p;		
	;
    break;}
case 69:
#line 425 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("char");
		yyval.node = p;	
	;
    break;}
case 70:
#line 431 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("short");
		yyval.node = p;	
	;
    break;}
case 71:
#line 437 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("int");
		yyval.node = p;	
	;
    break;}
case 72:
#line 443 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("long");
		yyval.node = p;	
	;
    break;}
case 73:
#line 449 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("float");
		yyval.node = p;	
	;
    break;}
case 74:
#line 455 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("double");
		yyval.node = p;	
	;
    break;}
case 75:
#line 461 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("signed");
		yyval.node = p;	
	;
    break;}
case 76:
#line 467 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TYPE_SPECIFIER); 
		p->m_name = strdup("unsigned");
		yyval.node = p;	
	;
    break;}
case 77:
#line 476 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 83:
#line 494 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		WRITE_TO_LOG_1(lDebug,"enumerator named:%s",yyvsp[0].sVal);
	;
    break;}
case 84:
#line 498 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		WRITE_TO_LOG_1(lDebug,"enumerator %s = ",yyvsp[-2].sVal);
	;
    break;}
case 85:
#line 505 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 86:
#line 512 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(ID); 
		p->m_name = strdup(yyvsp[0].sVal);
		yyval.node = p;
		WRITE_TO_LOG_1(lDebug,"rule direct_declarator:IDENTIFIER with:%s",yyvsp[0].sVal);
	;
    break;}
case 87:
#line 519 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-1].node;
		WRITE_TO_LOG(lDebug,"Ignored");
	;
    break;}
case 88:
#line 524 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(NONE);
		/*Fixed Array */
		WRITE_TO_LOG(lDebug,"Got Fixed Array");
	;
    break;}
case 89:
#line 531 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(NONE);
		/*Variable Array */
		WRITE_TO_LOG(lDebug,"Got variable array");
	;
    break;}
case 90:
#line 538 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		/*Regular Function declaration*/
		yyval.node = createNode(NONE);
	;
    break;}
case 91:
#line 543 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		/*Regular Function declaration*/
		yyval.node = createNode(NONE);
	;
    break;}
case 92:
#line 548 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		/*Empty Function */
		WRITE_TO_LOG(lDebug,"Got Function Declaration without parameters");
	;
    break;}
case 93:
#line 556 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 94:
#line 560 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-2].node;
	;
    break;}
case 95:
#line 567 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 96:
#line 571 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(PARAM_LIST);
		appendChild(p,yyvsp[-2].node);
		appendChild(p,yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 97:
#line 581 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(PARAM_DECLARATION);
		appendChild(p,yyvsp[-1].node);
		appendChild(p,yyvsp[0].node);
		yyval.node = p;	
	;
    break;}
case 98:
#line 588 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;	
	;
    break;}
case 99:
#line 595 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		WRITE_TO_LOG_1(lDebug,"id list %s",yyvsp[0].sVal);
	;
    break;}
case 100:
#line 599 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		WRITE_TO_LOG_1(lDebug,"id list %s",yyvsp[0].sVal);
	;
    break;}
case 101:
#line 607 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 102:
#line 611 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-1].node;
	;
    break;}
case 103:
#line 615 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-2].node;
	;
    break;}
case 104:
#line 622 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 105:
#line 626 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(NONE);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 106:
#line 636 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(NONE);
	;
    break;}
case 107:
#line 640 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* t = createNode(STATEMENT);
		appendChild(t,yyvsp[0].node);
		yyval.node = t;		
 		WRITE_TO_LOG(lDebug,"Compound statement");
	;
    break;}
case 108:
#line 647 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* t = createNode(STATEMENT);
		appendChild(t,yyvsp[0].node);
		yyval.node = t;		
 		WRITE_TO_LOG(lDebug,"Expression statement");
	  ;
    break;}
case 109:
#line 654 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* t = createNode(STATEMENT);
		appendChild(t,yyvsp[0].node);
		yyval.node = t;		
		WRITE_TO_LOG(lDebug,"Selection statement");
	  ;
    break;}
case 110:
#line 661 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 111:
#line 665 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(NONE);
	;
    break;}
case 112:
#line 672 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		WRITE_TO_LOG_1(lDebug,"Got Label %s",yyvsp[-2].sVal);
	;
    break;}
case 115:
#line 681 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(NOP);
		WRITE_TO_LOG(lDebug,"Empty block");
	;
    break;}
case 116:
#line 686 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		WRITE_TO_LOG(lDebug,"Block With statements only(no declarations)");
		yyval.node = yyvsp[-1].node;
	;
    break;}
case 117:
#line 691 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-1].node;
	;
    break;}
case 118:
#line 695 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(COMPOUND_STATEMENT);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[-1].node);
		yyval.node = p;
	;
    break;}
case 119:
#line 705 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 120:
#line 709 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* t = createNode(DECLARATION_LIST);
		appendChild(t,yyvsp[-1].node);
		appendChild(t,yyvsp[0].node);
		yyval.node = t;		
	;
    break;}
case 121:
#line 719 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"Single Statement")
	  ;
    break;}
case 122:
#line 724 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* t = createNode(STATEMENT_LIST);
		appendChild(t,yyvsp[-1].node);
		appendChild(t,yyvsp[0].node);
		yyval.node = t;		
		WRITE_TO_LOG(lDebug,"Recursive Statement List")
	  ;
    break;}
case 123:
#line 735 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(NONE);
	;
    break;}
case 124:
#line 739 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[-1].node;
	;
    break;}
case 125:
#line 746 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(CONDITION_IF);
		appendChild(p,yyvsp[-2].node);
		appendChild(p,yyvsp[0].node);
		yyval.node = p;
		WRITE_TO_LOG(lDebug,"If withut else");
	;
    break;}
case 126:
#line 754 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(CONDITION_IF_ELSE);
		appendChild(p,yyvsp[-4].node);
		appendChild(p,yyvsp[-2].node);
		appendChild(p,yyvsp[0].node);	
		yyval.node = p;
		WRITE_TO_LOG(lDebug,"If else");
	;
    break;}
case 127:
#line 763 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = createNode(NOP);
	;
    break;}
case 128:
#line 770 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(WHILE_LOOP);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 129:
#line 777 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(DO_WHILE_LOOP);
		appendChild(p, yyvsp[-5].node);
		appendChild(p, yyvsp[-2].node);
		yyval.node = p;
	;
    break;}
case 130:
#line 784 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(FOR_LOOP);
		appendChild(p, yyvsp[-3].node);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 131:
#line 792 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(FOR_LOOP);
		appendChild(p, yyvsp[-4].node);
		appendChild(p, yyvsp[-3].node);
		appendChild(p, yyvsp[-2].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
	;
    break;}
case 137:
#line 812 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
	;
    break;}
case 138:
#line 816 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		Node* p = createNode(TRANSLATION_UNIT);
		appendChild(p, yyvsp[-1].node);
		appendChild(p, yyvsp[0].node);
		yyval.node = p;
		root_node = p;
		print(p,0);
	;
    break;}
case 139:
#line 828 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"Function definition");
	;
    break;}
case 140:
#line 833 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"Declaration");
	;
    break;}
case 141:
#line 841 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		printf("\n");
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"Got Rule: declaration_specifiers declarator declaration_list compound_statement");
	;
    break;}
case 142:
#line 847 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		printf("\n");
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"Type FuncName(Parameters) {}");
	;
    break;}
case 143:
#line 853 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		printf("\n");
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"FuncName(Parameters) {}");
	;
    break;}
case 144:
#line 859 "c:\mcfromc\syntaxparserdll\ansi c.y"
{
		printf("\n");
		yyval.node = yyvsp[0].node;
		WRITE_TO_LOG(lDebug,"FuncName(Parameters) {}");
	;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 866 "c:\mcfromc\syntaxparserdll\ansi c.y"

#include <stdio.h>
extern char yytext[];
extern int column;

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

int parseSyntax(char* filename, Node** root) {
	InitLogger("parseLog.log",lDebug);
	freopen(filename,"r",stdin);
	WRITE_TO_LOG(lDebug,"Started");
	yyparse();
	WRITE_TO_LOG(lDebug,"End");
	TerminateLog();
	*root = root_node;
	_getch();
	return 0;
}
