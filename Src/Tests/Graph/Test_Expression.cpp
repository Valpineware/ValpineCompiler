#include "Tests.h"
#include <Graph/Expression.h>

#define CLASS Test_Expression
using namespace vc::graph;

TEST_CLASS
{
protected:
	void assertSingleIdentifier(const QString &expression)
	{
		Expression exp(expression);
		const auto &cmps = exp.components();
		ASSERT_EQ(1, cmps.count());
		
		Expression::ComponentListIterator iter(cmps);
		auto *result = dynamic_cast<Expression::Id*>(iter.next());
		ASSERT_NOT_NULL(result);

		EXPECT_EQ_STR(expression, result->verbatim());
	}


	void assertId(Expression::Component *component, const QString &expectedVerbatim, Expression::Id::Type type)
	{
		auto id = dynamic_cast<Expression::Id*>(component);
		ASSERT_NOT_NULL(id);
		EXPECT_EQ_STR(expectedVerbatim, id->verbatim());
		EXPECT_EQ(type, id->type());
	}


	void assertArguments(Expression::Component *component, const QString &expectedArg, int argCount)
	{
		auto args = dynamic_cast<Expression::Arguments*>(component);
		ASSERT_NOT_NULL(args);
		EXPECT_EQ_STR(expectedArg, args->verbatim());
		EXPECT_EQ(argCount, args->list().count());
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
	const auto &cmps = exp.components();
	ASSERT_EQ(2, cmps.count());

	Expression::ComponentListIterator iter(cmps);
	assertId(iter.next(), "bar", Expression::Id::Type::Basic);

	auto op = dynamic_cast<Expression::Operator*>(iter.next());
	ASSERT_NOT_NULL(op);
	EXPECT_EQ_STR("++", op->verbatim());
}


TEST_CASE(FunctionExpressionNoArguments)
{
	Expression exp("foo ()");
	const auto &cmps = exp.components();
	ASSERT_EQ(2, cmps.count());

	Expression::ComponentListIterator iter(cmps);
	assertId(iter.next(), "foo", Expression::Id::Type::Function);
	assertArguments(iter.next(), "", 0);
}


TEST_CASE(FunctionExpressionSingleArgument)
{
	Expression exp("barFoo(size+3)");
	const Expression::ComponentList &cmps = exp.components();
	ASSERT_EQ(2, cmps.count());

	Expression::ComponentListIterator iter(cmps);
	assertId(iter.next(), "barFoo", Expression::Id::Type::Function);
	assertArguments(iter.next(), "size+3", 1);
}