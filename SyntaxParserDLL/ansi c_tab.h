typedef union {
	int value;		/* A constant or expression value */
	char index;		/* an index in the variable symbols */
	char *sVal;		/* string							*/
	NodeData* node;		/* a pointer to node in the syntax tree */
} YYSTYPE;
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


extern YYSTYPE yylval;
