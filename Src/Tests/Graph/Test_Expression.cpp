#include "Tests.h"
#include <Graph/Expression.h>

#define CLASS Test_Expression
using namespace vc::graph;

TEST_CLASS
{
protected:
	void assertSingleIdentifier(const QString &expression)
	{
		Expression exp = Expression(expression);
		const Expression::ComponentList &cmps = exp.result().components();
		ASSERT_EQ(1, cmps.count());
		
		Expression::ComponentListIterator iter(cmps);
		Expression::Value *result = dynamic_cast<Expression::Value*>(iter.next());
		ASSERT_NOT_NULL(result);

		EXPECT_EQ_STR(expression, result->verbatim());
	}
};


TEST_CASE(SingleResult1)
{
	assertSingleIdentifier("10");
}


TEST_CASE(SingleResult2)
{
	assertSingleIdentifier("foo");
}


TEST_CASE(IdentifierAndOperator)
{
	Expression exp("bar++");
	const Expression::ComponentList &cmps = exp.result().components();
	ASSERT_EQ(2, cmps.count());

	Expression::ComponentListIterator iter(cmps);

	Expression::Value *id = dynamic_cast<Expression::Value*>(iter.next());
	ASSERT_NOT_NULL(id);
	EXPECT_EQ_STR("bar", id->verbatim());

	Expression::Operator *op = dynamic_cast<Expression::Operator*>(iter.next());
	ASSERT_NOT_NULL(op);
	EXPECT_EQ_STR("++", op->verbatim());
}