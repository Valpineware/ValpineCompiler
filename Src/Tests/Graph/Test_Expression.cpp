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


	void assertOperator(Expression::Component *component, const QString &expectedVerbatim)
	{
		auto op = dynamic_cast<Expression::Operator*>(component);
		ASSERT_NOT_NULL(op);
		EXPECT_EQ_STR(expectedVerbatim, op->verbatim());
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
	assertOperator(iter.next(), "++");
}


TEST_CASE(FunctionExpressionNoArguments)
{
	Expression exp("foo ()");
	const auto &cmps = exp.components();
	ASSERT_EQ(2, cmps.count());

	Expression::ComponentListIterator iter(cmps);
	assertId(iter.next(), "foo", Expression::Id::Type::FunctionCall);
	assertArguments(iter.next(), "", 0);
}


TEST_CASE(FunctionExpressionSingleArgument1)
{
	Expression exp("barFoo(size+3)");
	const auto &cmps = exp.components();
	ASSERT_EQ(2, cmps.count());

	Expression::ComponentListIterator iter(cmps);
	assertId(iter.next(), "barFoo", Expression::Id::Type::FunctionCall);
	assertArguments(iter.next(), "size+3", 1);
}


TEST_CASE(FunctionExpressionSingleArgument2)
{
	Expression exp("calculate (99 / (size+ 3))");
	const auto &cmps = exp.components();
	ASSERT_EQ(2, cmps.count());

	Expression::ComponentListIterator iter(cmps);
	assertId(iter.next(), "calculate", Expression::Id::Type::FunctionCall);
	
	{
		auto args = dynamic_cast<Expression::Arguments*>(iter.next());
		ASSERT_NOT_NULL(args);
		EXPECT_EQ(1, args->list().count());

		{
			auto arg1 = dynamic_cast<Expression::Result*>(args->list().first());
			ASSERT_NOT_NULL(arg1);
			ASSERT_EQ(3, arg1->components().count());
			Expression::ComponentListIterator arg1Iter(arg1->components());

			assertId(arg1Iter.next(), "99", Expression::Id::Type::Basic);
			assertOperator(arg1Iter.next(), "/");
		}
	}
}