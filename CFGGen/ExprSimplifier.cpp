#include "ExprSimplifier.h"
#include "AtomExpr.h"
#include "BinExpr.h"

ExprSimplifier::ExprSimplifier()
{
	initializeCommonPatterns();
}

void ExprSimplifier::AddPattern( const E& src, const E& tgt )
{
	m_patterns.push_back(std::pair<E,E>(src,tgt));
}

/// Reorders expression according to pattern and expressions contained within
/// the linked map.
SPExpr ExprSimplifier::reorderExpr( const E& pat, std::map<int, SPExpr>& linked )
{
	SPExpr res;
	if (pat.t == A_NONE)
	{
		//BinExpr
		SPExpr left = reorderExpr(*(pat.l), linked);
		SPExpr right = reorderExpr(*(pat.r), linked);
		res = SPExpr(new BinExpr(pat.o, left, right));
	}
	else
	{
		//AtomExpr
		res = linked[pat.id]->Clone();	
	}

	return res;
}

bool ExprSimplifier::isMatch( SPExpr expr, const E& pat, std::map<int,SPExpr>& linked ) const
{
	bool rc = expr->Type() == pat.et;

	if (rc)
	{
		if (expr->Type() == E_BINOP)
		{	
			BinExpr* be = (BinExpr*)expr.get();
			rc = be->OpType() == pat.o;
			if (rc) {
				rc = isMatch(be->Left(), *(pat.l), linked) && 
					isMatch(be->Right(), *(pat.r), linked);
			}
		}
		else if (expr->Type() == E_ATOM)
		{
			AtomExpr* ae = (AtomExpr*)expr.get();
			rc = ae->AType() == pat.t || pat.t == A_ANY;
		}
	}

	if (rc && pat.id >= 0)
	{
		linked[pat.id] = expr;			
	}

	return rc;
}

///The Simplify method is responsible for the actual expression simplification.
///It gets an expression and tries to find a matching pattern.
///If found, it links the expression sub-expressions to the target expression
///pattern and returns this expression.
///If not found, it returns a copy of the expression itself, untouched.
SPExpr ExprSimplifier::Simplify( SPExpr expr, bool& wasSimplified)
{
	wasSimplified = false;
	for (size_t i = 0; i < m_patterns.size(); ++i)
	{
		E pat(m_patterns[i].first);
		std::map<int,SPExpr> linked;
		if (isMatch(expr, pat, linked))
		{
			wasSimplified = true;
			return reorderExpr(m_patterns[i].second, linked);
		}
	}

	return expr->Clone();
}

///Adds several basic patterns(and their simplification)
///to the known look-up patterns.
void ExprSimplifier::initializeCommonPatterns()
{
	// $ represents a "wild-card" - matches any type of Atom Expressions (A_ANY).
	// c1*($+c2) => c1*$+c1*c2 
	E x1 = E(OP_MUL,
				E(1,A_CONST),
				E(OP_ADD,
					E(2,A_ANY),
					E(3,A_CONST)));

	E y1 = E(OP_ADD,
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)),
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)));

	// c1*($-c2) => c1*$-c1*c2 
	E x2 = E(OP_MUL,
				E(1,A_CONST),
				E(OP_SUB,
					E(2,A_ANY),
					E(3,A_CONST)));

	E y2 = E(OP_SUB,
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)),
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)));

	// ($+c2)*c1 => c1*$+c1*c2 
	E x3 = E(OP_MUL,
				E(OP_ADD,
					E(2,A_ANY),
					E(3,A_CONST)),
				E(1,A_CONST));

	E y3 = E(OP_ADD,
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)),
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)));

	// ($-c2)*c1 => c1*$-c1*c2 
	E x4 = E(OP_MUL,
				E(OP_SUB,
					E(2,A_ANY),
					E(3,A_CONST)),
				E(1,A_CONST));

	E y4 = E(OP_SUB,
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)),
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)));

	// (c2+$)*c1 => c1*$+c1*c2 
	E x5 = E(OP_MUL,
				E(OP_ADD,
					E(3,A_CONST),
					E(2,A_ANY)),
				E(1,A_CONST));

	E y5 = E(OP_ADD,
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)),
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)));

	// (c2-$)*c1 => c1*c2-c1*$ 
	E x6 = E(OP_MUL,
				E(OP_SUB,
					E(3,A_CONST),
					E(2,A_ANY)),
				E(1,A_CONST));

	E y6 = E(OP_SUB,
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)),
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)));

	// c1*(c2+$) => c1*$+c1*c2 
	E x7 = E(OP_MUL,
				E(1,A_CONST),
				E(OP_ADD,
					E(3,A_CONST),
					E(2,A_ANY)));

	E y7 = E(OP_ADD,
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)),
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)));

	// c1*(c2-$) => c1*c2-c1*$ 
	E x8 = E(OP_MUL,
				E(1,A_CONST),
				E(OP_SUB,
					E(3,A_CONST),
					E(2,A_ANY)));

	E y8 = E(OP_SUB,
				E(OP_MUL,
					E(1,A_CONST),
					E(3,A_CONST)),
				E(OP_MUL,
					E(1,A_CONST),
					E(2,A_ANY)));

	// c1+($+c2) => $+(c1+c2)
	E x9 = E(OP_ADD,
				E(1,A_CONST),
				E(OP_ADD,
					E(2,A_ANY),
					E(3,A_CONST)));

	E y9 = E(OP_ADD,
				E(2,A_ANY),
				E(OP_ADD,
					E(1,A_CONST),
					E(3,A_CONST)));

	// c1+(c2+$) => $+(c1+c2)
	E x10 = E(OP_ADD,
				E(1,A_CONST),
				E(OP_ADD,
					E(3,A_CONST),
					E(2,A_ANY)));

	E y10 = E(OP_ADD,
				E(2,A_ANY),
				E(OP_ADD,
					E(1,A_CONST),
					E(3,A_CONST)));

	// ($+c2)+c1 => $+(c1+c2)
	E x11 = E(OP_ADD,
				E(OP_ADD,
					E(2,A_ANY),
					E(3,A_CONST)),
				E(1,A_CONST));

	E y11 = E(OP_ADD,
				E(2,A_ANY),
				E(OP_ADD,
					E(1,A_CONST),
					E(3,A_CONST)));


	// (c2+$)+c1 => $+(c1+c2)
	E x12 = E(OP_ADD,
				E(OP_ADD,
					E(3,A_CONST),
					E(2,A_ANY)),
				E(1,A_CONST));

	E y12 = E(OP_ADD,
				E(2,A_ANY),
				E(OP_ADD,
					E(1,A_CONST),
					E(3,A_CONST)));

	// c1+($-c2) => $+(c1-c2)
	E x13 = E(OP_ADD,
				E(1,A_CONST),
				E(OP_SUB,
					E(2,A_ANY),
					E(3,A_CONST)));

	E y13 = E(OP_ADD,
				E(2,A_ANY),
				E(OP_SUB,
					E(1,A_CONST),
					E(3,A_CONST)));

	// c1+(c2-$) => (c1+c2)-$
	E x14 = E(OP_ADD,
				E(1,A_CONST),
				E(OP_SUB,
					E(3,A_CONST),
					E(2,A_ANY)));

	E y14 = E(OP_SUB,
				E(OP_ADD,
					E(1,A_CONST),
					E(3,A_CONST)),
				E(2,A_ANY));

	// ($-c2)+c1 => $+(c1-c2)
	E x15 = E(OP_ADD,
				E(OP_SUB,
					E(2,A_ANY),
					E(3,A_CONST)),
				E(1,A_CONST));

	E y15 = E(OP_ADD,
				E(2,A_ANY),
				E(OP_SUB,
					E(1,A_CONST),
					E(3,A_CONST)));


	// (c2-$)+c1 => (c1+c2)-$
	E x16 = E(OP_ADD,
				E(OP_SUB,
					E(3,A_CONST),
					E(2,A_ANY)),
				E(1,A_CONST));

	E y16 = E(OP_SUB,
				E(OP_ADD,
					E(1,A_CONST),
					E(3,A_CONST)),
				E(2,A_ANY));

	AddPattern(x1,y1);
	AddPattern(x2,y2);
	AddPattern(x3,y3);
	AddPattern(x4,y4);
	AddPattern(x5,y5);
	AddPattern(x6,y6);
	AddPattern(x7,y7);
	AddPattern(x8,y8);
	AddPattern(x9,y9);
	AddPattern(x10,y10);
	AddPattern(x11,y11);
	AddPattern(x12,y12);
	AddPattern(x13,y13);
	AddPattern(x14,y14);
	AddPattern(x15,y15);
	AddPattern(x16,y16);
}

E::E( size_t _id, AtomType _t ) :
	id((int)_id), t(_t), o(OP_NOP), l(NULL), r(NULL), et(E_ATOM)
{
}

E::E( const E& other ) :
	o(other.o), id(other.id), t(other.t), l(NULL), r(NULL),
	et(other.et)
{
	if (other.l && other.r)
	{
		l = new E(*(other.l));
		r = new E(*(other.r));
	}
}

E::E( OperatorType _o,E _l, E _r ) : 
	l(new E(_l)), r(new E(_r)), o(_o), t(A_NONE), id(-1),
	et(E_BINOP)
{

}

E::~E()
{
	if (l)
		delete l;
	if (r)
		delete r;
}