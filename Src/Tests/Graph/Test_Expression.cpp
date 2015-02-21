#include "Tests.h"
#include <Graph/Expression.h>

#define CLASS Test_Expression
using namespace vc::graph;

TEST_CLASS
{
};


TEST_CASE(Operators)
{
	Expression *exp = Expression::createFromVerbatimSignature("10");

	ASSERT_EQ(1, exp->components().count());
}