#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Expr.h"

///Expression pattern matching data struct
struct E
{
	///c'tor for Atoms
	E(size_t _id, AtomType _t);

	///copy c'tor
	E(const E& other);

	///c'tor for Binary Expressions
	E(OperatorType _o,E _l, E _r);

	~E();

	///id used for linking Atom expressions to pattern. 
	///Must be unique within the same pattern.
	int id;
	AtomType t;
	ExprType et;

	///members specific for Binary Operator expression pattern
	OperatorType o;
	E* l;
	E* r;
};

//////////////////////////////////////////////////////////////////////////
/// This class simplifies expressions using pattern matching.
/// Each expression is compares against several patterns. If a match is found,
/// Each sub-expression is linked to an identifier, and expressions are then
/// reordered according to a target pattern.
//////////////////////////////////////////////////////////////////////////
class ExprSimplifier
{
public:
	ExprSimplifier();

	SPExpr Simplify(SPExpr expr, bool& wasSimplified);

	void AddPattern(const E& src, const E& tgt);

private:
	bool isMatch(SPExpr expr, const E& pat, std::map<int,SPExpr>& linked) const;

	SPExpr reorderExpr(const E& pat, std::map<int, SPExpr>& linked);

	void initializeCommonPatterns();

	std::vector<std::pair<E,E>> m_patterns;
};
