#include "Tests.h"
#include <Graph/Expression.h>

#define CLASS Test_Expression
using namespace vc::graph;

TEST_CLASS
{
protected:
	void assertSingleIdentifier(const QString &expression)
	{
		Expression *exp = Expression::createFromVerbatimSignature(expression);
		const Expression::ComponentList &cmps = exp->components();
		ASSERT_EQ(1, cmps.count());
		
		Expression::ComponentListIterator iter(cmps);
		Expression::Identifier *id = dynamic_cast<Expression::Identifier*>(iter.next());
		ASSERT_NOT_NULL(id);

		EXPECT_EQ_STR(expression, id->verbatim());
	}
};


TEST_CASE(SingleIdentifier)
{
	assertSingleIdentifier("10");
	assertSingleIdentifier("foo");
}


