#include "Tests.h"
#include "Ext/Expression.h"

#define CLASS Test_Expression
using namespace vc::graph::expression;
using namespace ext;

TEST_CLASS
{
protected:
	void assertSingleIdentifier(const QString &expression)
	{
		Expression exp("");
			addId(&exp, expression, Id::Type::Basic);

		assertEqualExpression(exp, Expression(expression));
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
	Expression exp("");
		addId(&exp, "bar", Id::Type::Basic);
		addOperator(&exp, "++");

	assertEqualExpression(exp, Expression("bar++"));
}


TEST_CASE(FunctionExpressionNoArguments)
{
	Expression exp("");
		addId(&exp, "foo", Id::Type::FunctionCall);
		addArguments(&exp);

	assertEqualExpression(exp, Expression("foo ()"));
}


TEST_CASE(FunctionExpressionSingleArgument1)
{
	Expression exp("");
		addId(&exp, "barFoo", Id::Type::FunctionCall);
		auto args = addArguments(&exp);
			auto arg1 = addExpression(args);
				addId(arg1, "size", Id::Type::Basic);
				addOperator(arg1, "+");
				addId(arg1, "3", Id::Type::Basic);

	assertEqualExpression(exp, Expression("barFoo(size+3)"));
}


TEST_CASE(FunctionExpressionSingleArgument2)
{
	Expression exp("");
		addId(&exp, "calculate", Id::Type::FunctionCall);
		auto args = addArguments(&exp);
			auto arg1 = addExpression(args);
				addId(arg1, "99", Id::Type::Basic);
				addOperator(arg1, "/");
				auto res = addResult(arg1);
					addId(res, "size", Id::Type::Basic);
					addOperator(res, "+");
					addId(res, "3", Id::Type::Basic);

	assertEqualExpression(exp, Expression("calculate (99 /(size + 3))"));
}


TEST_CASE(FunctionExpressionMultipleArguments)
{
	Expression exp("");
		addId(&exp, "get_total_amount", Id::Type::FunctionCall);
		auto args = addArguments(&exp);
			auto arg1 = addExpression(args);
				addId(arg1, "65", Id::Type::Basic);
			auto arg2 = addExpression(args);
				addId(arg2, "value", Id::Type::Basic);

	assertEqualExpression(exp, Expression("get_total_amount(65, value)"));
}


TEST_CASE(FunctionExpressionMultipleArgumentsNested)
{
	Expression("foo(a,b,c)");

	Expression exp("");
		addId(&exp, "turnOn", Id::Type::FunctionCall);
		auto args = addArguments(&exp);
			auto arg1 = addExpression(args);
				addId(arg1, "true", Id::Type::Basic);
			auto arg2 = addExpression(args);
				addId(arg2, "foo", Id::Type::FunctionCall);
				auto args2 = addArguments(arg2);
					auto arg2_1 = addExpression(args2);
						addId(arg2_1, "44", Id::Type::Basic);
					auto arg2_2 = addExpression(args2);
						addId(arg2_2, "alpha", Id::Type::Basic);

	assertEqualExpression(exp, Expression("turnOn(true, foo(44, alpha))"));
}